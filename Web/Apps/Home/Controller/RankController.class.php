<?php
namespace Home\Controller;
use Think\Controller;
//调整页面编码
header("Content-Type: text/html;charset=utf-8");

class RankController extends Controller {
        public function index(){
            $page_get = I("get.page");
            $page = empty($page_get) ? 1 : $page_get;

            $passport = D("passport");
            $userinfo = D("judge");

            $res = $passport->getuserlist();
            
            $info_rank=$res;
            unset($info_rank["num_total"]);

            for($i = 0; $i < $res["num_total"]; $i++){
                $res_ratio = $userinfo->getuserratio($info_rank[$i]["user_id"]);
                $info_rank[$i]["num_ac"] = $res_ratio["num_ac"];
                $info_rank[$i]["num_total"] = $res_ratio["num_total"];
                $info_rank[$i]["num_pro"] = $res_ratio["num_pro"];
                $info_rank[$i]["ratio"] = round(100*$res_ratio["num_ac"]/$res_ratio["num_total"],2);
            }

            /*自定义的数组排序,使用匿名函数*/
            usort($info_rank, function($a, $b){
                 if($a["num_ac"] == $b["num_ac"]){
                         if($a["num_pro"] == $b["num_pro"]){
                                return $a["ratio"] < $b["ratio"];
                        }else{
                            return $a["num_pro"] < $b["num_pro"];
                        }
                }else{
                    return $a["num_ac"] < $b["num_ac"];
                }
            });
            
            $this->assign("info_rank",$info_rank);
            $this->assign("rank","nav");
            $this->display("default/rank/index");
        }

        
         
}