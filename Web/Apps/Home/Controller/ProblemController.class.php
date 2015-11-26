<?php
namespace Home\Controller;
use Think\Controller;
//调整页面编码
header("Content-Type: text/html;charset=utf-8");

class ProblemController extends Controller {
    public function index(){
             $problem = D("Problem");
             $judge = D("Judge");

             $page_get = I("get.page");
             $page = empty($page_get) ? 1 : $page_get;

             $info_list = $problem->pro_list($page);

             /*获取分页的信息*/
             $info_page["now"] = $page;
             $info_page['num_list'] = $info_list["num_list"];
             $info_page['num_total'] = $info_list["num_total"];
             $info_page['num_page'] = round(1 + $info_list["num_total"]/C("PAGE_NUM"));

              /*剔除题目列表附加信息，只留下题目信息*/
             unset($info_list["num_list"]);
             unset($info_list["num_total"]);
             
             /*获取用户ID*/

             /*获取题目提交和通过率,如果用户登录，获取提交状态*/
             $judge = D("Judge");
             for( $i = 0; $i < (int)$info_page['num_list']; $i++) {
                     $res = $judge -> get_pro_ratio($info_list[$i]["pro_id"]);
                     $info_list[$i]['num_total'] = $res["num_total"];
                     $info_list[$i]['num_ac'] = $res["num_ac"];
                     $info_list[$i]["num_ratio"] = round(100*$res["num_ac"]/$res["num_total"],2);
                      $info_list[$i]['status'] = "-1";

                     if(false == empty(cookie("user_id"))){
                         $info_list[$i]['status'] = $judge->getuserstatus($info_list[$i]["pro_id"],cookie("user_id"));
                     }
             }

           if($info_page['now'] < 10){
                $info_page["start"] = 1;
                $info_page["backfront"] = false;    //直达第一页
            }else{
                $info_page["start"] = $info_page["now"] - 5;
                $info_page["backfront"] = true;
            }

            if($info_page['num_page'] >= $info_page["start"]+10){
                $info_page["end"] = $info_page["start"]+10;
                $info_page["backend"] = true; //直达最后页
            }else{
                $info_page["end"] = $info_page["num_page"]+1;
                $info_page["backend"] = false;    //直达最后页
            }

             $this->assign("info_page",$info_page);
             $this->assign("info_list",$info_list);
             $this->assign("nav","problem");

       	$this->display("default/problem/index");
    }

    public function detail($pro_id){
            $problem = D("Problem");
            $detail['pro_id'] = I("get.pro_id");

            $res = $problem -> detail($detail['pro_id']);
            if(false == $res){
                $this->redirect('problem/index', NULL, 1, '问题暂未开放.<br />正在跳转题目列表界面……');
            }

            $detail['pro_title'] = $res["title"];
            $detail['pro_timelim'] = $res["time_lim"];
            $detail['pro_memlim'] = $res["mem_lim"];

            $judge = D("Judge");
            $res = $judge -> get_pro_ratio($detail["pro_id"]);
            $detail['num_total'] = $res["num_total"];
            $detail['num_ac'] = $res["num_ac"];
            $detail['num_ratio'] = round(100*$res["num_ac"]/ $res["num_total"], 2);

            $dir_pro = C("PATH_PROBLEM").$detail['pro_id']."/";
            $path_descri = $dir_pro."descri.html";
            $path_input = $dir_pro."input.html";
            $path_output = $dir_pro."output.html";
            $path_input_data = $dir_pro."input_data.html";
            $path_output_data = $dir_pro."output_data.html";
            $path_hint = $dir_pro."hint.html";
            
            $detail["descri"] = file_get_contents($path_descri);
            $detail["input"] = file_get_contents($path_input);
            $detail["output"] = file_get_contents($path_output);
            $detail["input_data"] = file_get_contents($path_input_data);
            $detail["output_data"] = file_get_contents($path_output_data);
            $detail["hint"] = file_get_contents($path_hint);

            $this->assign("nav","problem");
            $this->assign("detail", $detail);

            $this->display("default/problem/detail");
    }

    /*处理代码提交的操作*/
    public function submit(){
        $judge = D("Judge");
        $res = cookie("user_token");
        

       if(true == $res){
            $passport = D("passport");
            $res = $passport->loginTokenCheck($res);

            if(true == $res){
                $detail['user_id'] = $res;
                $detail['pro_id']  =  I("post.pro_id");

                

                do{
                    $detail['run_id']  =  time()+rand()+time();
                }while(false == $judge->check_run_id($detail["run_id"]));

                $detail['code'] = $_POST["code"];
                $detail['nickname'] = cookie("nickname");
                $detail['date'] = date("Y-m-d H:i:sa");
                $detail['codelength'] = strlen($detail['code']);

                //把代码保存到data的running目录  
                $path_data = C("DATA_RUNING");
                $res = mkdir($path_data.$detail["run_id"]);
            }
        }

        if(false == $res){
            $this->redirect('passport/login', array("pro_id"=> $detail['pro_id']), 1, '提交失败，请登录.<br />正在跳转登录界面……');
        }

        if(true == $res){
            //创建代码文件
            $res = fopen($path_data.$detail["run_id"]."/Main.cpp", "w");
            if(true == $res){
                //将代码写入文件
                if(false == fwrite($res, $detail["code"], 102400)){
                    $res = false;
                }else{
                    fclose($res); 
                }

                 if(true == $res){
                     //往数据库写数据
                    $judge = D("Judge");
                    $res = $judge->submit($detail);
                }
            }
        }

        if(false == $res){
            $this->redirect('problem/detail', array("pro_id"=> $detail['pro_id']), 1, '提交失败，请联系管理员.<br />正在跳转回题目……');
        }else{
            $this->redirect('judge/index');
        }   
    }
}