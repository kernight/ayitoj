<?php
namespace Home\Controller;
use Think\Controller;

header("Content-Type:text/html;charset=utf-8");

class ContestController extends Controller {
	public function index(){
		$contest = D("contest");
		$info_contest = $contest->getcontestlist();

		/*根据开始时间和结束时间排序，时间越往靠近现在越在前面*/
		usort($info_contest, function($a,$b){
			if($a["date_start"] == $b["date_start"]){
				return $a["date_end"] < $b["date_end"];
			}else{
				return $a["date_start"] < $b["date_start"];
			}
		});

		$this->assign("info_contest",$info_contest);
		$this->assign("nav","contest");
		$this->display("default/contest/index");
	}

	public function showlist(){
		$contest_id = I("get.contest_id");
		$contest = D("contest");
		$info = $contest->getcontestdetail($contest_id);

		$info_contest = $info["contest"][0];
		$info_problem = $info["pro"];

		if("lock" != $info_contest["status"]){			
			if(false == empty(cookie("user_id"))){
				$user_id = cookie("user_id");
			}

			/*计算正确率*/
			for ($i=0; $i < sizeof($info_problem); $i++) { 
				$pro_id = $info_problem[$i]["pro_id"];
				$res = $contest->getproratio($contest_id,$pro_id);
				$info_problem[$i]["num_total"] = $res["num_total"];
				$info_problem[$i]["num_ac"] = $res["num_ac"];
				$info_problem[$i]["num_ratio"] = round(100*$res["num_ac"]/$res["num_total"],2);

				if(false == empty($user_id)){
					$info_problem[$i]["status"] = $contest->getprostatus($contest_id,$pro_id,$user_id);
				}else{
					$info_problem[$i]["status"] = -1;
				}
			}

			$this->assign("info_contest",$info_contest);
			$this->assign("info_problem",$info_problem);
			$this->assign("nav","contest");
			$this->assign("nav_contest","list");
			$this->assign("contest_id",$contest_id);
			$this->display("default/contest/list");
		}else{
			$this->redirect('contest/index', NULL, 1, '竞赛未开放.<br />正在跳转竞赛列表界面……');
		}
	}

	public function detail(){

		$contest_id = I("get.contest_id");
		$pro_id = I("get.pro_id");
		$contest = D("contest");
		$problem = D("problem");
		$info = $contest->getcontestdetail($contest_id);

		$info_contest = $info["contest"][0];

		$detail["pro_id"] = $pro_id;
		$detail["contest_id"] = $contest_id;

        $res = $problem -> detail($detail['pro_id']);
        if(false == $res){
            $this->redirect('problem/index', NULL, 1, '问题暂未开放.<br />正在跳转题目列表界面……');
        }

        $detail['pro_title'] = $res["title"];
        $detail['pro_timelim'] = $res["time_lim"];
        $detail['pro_memlim'] = $res["mem_lim"];

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


		$this->assign("detail", $detail);
		$this->assign("info_contest",$info_contest);
		$this->assign("contest_id",$contest_id);
		$this->assign("nav","contest");
		$this->display("default/contest/detail");
	}

	/*处理代码提交的操作*/
	public function submit(){
		$judge = D("Judge");
		$res = cookie("user_token");
		$contest_id = I("post.contest_id");
		
		$contest = D("contest");
		$pro_id = I("post.pro_id");
		$info = $contest->getcontestdetail($contest_id);

		if("open" != $info["contest"][0]["status"]){
			 $this->redirect('contest/detail', array("contest_id"=>$contest_id,"pro_id"=>$pro_id), 1, '竞赛关闭.<br />正在跳转题目列表界面……');
		}
		if(true == $res){
			$passport = D("passport");
			$res = $passport->loginTokenCheck($res);
			if(true == $res){
				$detail['user_id'] = $res;
				$detail['pro_id']  =  $pro_id;
				$detail['contest_id']  =  $contest_id;

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
			$this->redirect('contest/detail', array("pro_id"=> $detail['pro_id'],"contest_id"=> $contest_id), 1, '提交失败，请联系管理员.<br />正在跳转回题目……');
		}else{
			$this->redirect('contest/status',array("contest_id"=> $contest_id));
		}   
	}

	public function status(){
		$page_get = I("get.page");
	             $page = empty($page_get) ? 1 : $page_get;

		$contest_id = I("get.contest_id");

		$contest = D("contest");
		$info = $contest->getcontestdetail($contest_id);

		$info_contest = $info["contest"][0];

		$query["contest_id"] = $contest_id;
		if( !empty( I("get.run_id"))){
	             	$query["run_id"] = I("get.run_id");
	             }

	             if( !empty( I("get.pro_id"))){
	             	$query["pro_id"] = I("get.pro_id");
	             }

	             if( !empty( I("get.nickname"))){
	             	$query["nickname"] = I("get.nickname");
	             }

	             if( !empty( I("get.status"))){
	             	$query["status"] = I("get.status");
	             }

		$info_status = $contest->getconteststatus($page,$query);
		if(true == $info_status){
			$info_page["now"] = $page;
		             $info_page['num_list'] = $info_status["num_list"];
		             $info_page['num_total'] = $info_status["num_total"];
		             $info_page['num_page'] = (int)(1 + $info_status["num_total"]/C("PAGE_NUM"));
			unset($info_status["num_total"]);
			unset($info_status["num_list"]);

			/*修改评测结果，转换为全文字显示*/
		             for( $i = 0; $i < sizeof($info_status); $i++) {
	             	      $info_status[$i]["status"] = rtrim($info_status[$i]["status"]);

		                    switch ($info_status[$i]["status"]) {
		                    	case 'AC':
		                    		$info_status[$i]["info"] = "Accepted (答案正确)";
		                    		break;
				case "WA":
					$info_status[$i]["info"] = "Wrong Answer (答案错误)";
					break;
				case "CE":
					$info_status[$i]["info"] = "Compile Error (编译出错)";
					break;
				case "PE":
					$info_status[$i]["info"] = "Presentation Error (格式错误)";
					break;
				case "RE":
					$info_status[$i]["info"] = "Runtime Error (运行时出错)";
					break;
				case "RF":
					$info_status[$i]["info"] = "Restricted Function (非法程序)";
					break;
				case "MLE":
					$info_status[$i]["info"] = "Memory Limit Exceeded (内存超限)";
					break;
				case "OLE":
					$info_status[$i]["info"] = "Output Limit Exceeded (输出超限)";
					break;
				case "TLE":
					$info_status[$i]["info"] = "Time Limit Exceeded (时间超限)";
					break;
				case "Judging":
					$info_status[$i]["info"] = "Judging (正在评判)";
					break;
				case "WAIT":
					$info_status[$i]["info"] = "Waiting (等待评判)";
					break;

				default:
					$info_status[$i]["info"] = "System Error (系统运行出错,联系管理员)";
					break;
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
		}

		$this->assign("info_contest",$info_contest);
		$this->assign("info_status",$info_status);
		$this->assign("info_query",$query);
		$this->assign("contest_id",$contest_id);
		$this->assign("nav","contest");
		$this->assign("nav_contest","status");
		$this->assign("info_page",$info_page);
		$this->display("default/contest/status");
	}

	public function rank(){
		$contest_id = I("get.contest_id");
		$contest = D("contest");
		$info = $contest->getcontestdetail($contest_id);

		$info_contest = $info["contest"][0];

		$info_rank = $contest->getcontestrank($contest_id);
		$info_pro = $info_rank["pro_info"];
		$info_user = $info_rank["user_info"];
		usort($info_user,function($a, $b){
			if($a["pro"]["num_ac"] == $b["pro"]["num_ac"]){
				return $a["pro"]["time_ac"] > $b["pro"]["time_ac"];
			}else{
				return $a["pro"]["num_ac"] < $b["pro"]["num_ac"];
			}
		});

		$this->assign("info_contest",$info_contest);
		$this->assign("info_pro",$info_pro);
		$this->assign("info_user",$info_user);
		$this->assign("contest_id",$contest_id);
		$this->assign("nav","contest");
		$this->assign("nav_contest","rank");
		$this->display("default/contest/rank");
	}
}

?>