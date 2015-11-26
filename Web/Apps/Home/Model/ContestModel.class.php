<?php
namespace Home\Model;
use Think\Model;
/*
*竞赛相关数据库模型
*/
class ContestModel extends Model {
        protected $tableName = 'contest_info'; 
        /*获取竞赛列表*/
        public function getcontestlist(){
            $res = $this -> select();

            if(false == $res){
                return false;
            }

            return $res;
        }

        /*获取竞赛详细信息*/
        public function getcontestdetail($contest_id){
            $query["contest_id"] = $contest_id;

            $res["contest"] = $this  -> where($query) 
                                -> select();

            if(false == $res["contest"]){
                return false;
            }

            $res["pro"] = $this -> table("oj_contest_problem") 
                                -> where($query) 
                                -> select();
            return $res;
        }

        /*获取竞赛题目正确率*/
        public function getproratio($contest_id,$pro_id){
            $query["contest_id"] = $contest_id;
            $query["pro_id"] = $pro_id;

            $res = $this -> table("oj_judge") 
                                -> where($query) 
                                -> select();
            $ans["num_total"] = sizeof($res);

            $query["status"] = "AC ";
            $res = $this -> table("oj_judge") 
                                -> where($query) 
                                -> select();
            $ans["num_ac"] = sizeof($res);

            return $ans;
        }

        /*获取用户的竞赛题目状态*/
        public function getprostatus($contest_id,$pro_id,$user_id){
            $query["contest_id"] = $contest_id;
            $query["pro_id"] = $pro_id;
            $query["user_id"] = $user_id;

            $res = $this -> table("oj_judge") 
                                -> where($query) 
                                -> select();
           if(false == sizeof($res)){
                return -1;
           }

            $query["status"] = "AC ";
            $res = $this -> table("oj_judge") 
                                -> where($query) 
                                -> select();
            if(false == sizeof($res)){
                return 0;
            }else{
                return 1;
            }
        }

        /*获取竞赛所有题目状态*/
        public function getconteststatus($page,$query){
            $num_page = (int)C(PAGE_NUM);

            //获取题目总数
            $total_num = $this -> table("oj_judge") 
                                          -> where($query) 
                                          ->count();

             //获取当前题目数
            if( $total_num/20 >= $page){
                    $list_num =  20;
            }else{
                    $list_num = $total_num%20;
            }
            
            //根据时间排序
            $res = $this -> table("oj_judge") 
                                -> where($query)
                                -> order("date desc")
                                -> field(array("run_id,pro_id,user_id,nickname,status,time,memory,codelength,date"))
                                -> limit(($page-1)*$num_page,$num_page)
                                -> select();
            
            if(false == $res){
                return false;
            }

            $res['num_total'] = $total_num;
            $res['num_list'] = $list_num;
            return $res;
        }

        /*获取竞赛排行榜相关数据*/
        public function getcontestrank($contest_id){
            $query["contest_id"] = $contest_id;
            $res = $this  -> where($query)
                                -> field(array("date_start")) 
                                -> select();

            $date_start = $res[0]["date_start"];

            //获取题目总信息
            $res["pro_info"] = $this -> table("oj_contest_problem") 
                                          -> where($query) 
                                          -> field(array("pro_id,title"))
                                          -> select();

            //获取提交过的所有用户id和nickname
            $res["user_info"] = $this -> table("oj_judge") 
                                          -> where($query)
                                          -> field(array("user_id,nickname"))
                                          ->distinct(true)
                                          -> select();

            //检测用户各个题目的情况，ac则计算时间
            for ($i=0; $i < sizeof($res["user_info"]); $i++) { 
                $query["user_id"] = $res["user_info"][$i]["user_id"];
                 $res["user_info"][$i]["pro"]["num_ac"] = 0;
                 $res["user_info"][$i]["pro"]["time_ac"] = 0;

                foreach ($res["pro_info"] as $value) {
                     $pro_id = $value["pro_id"];
                     $query["pro_id"] = $pro_id;
                     $query["status"] = "AC ";

                     $info_ac = $this -> table("oj_judge") 
                                                -> where($query)
                                                -> field(array("date"))
                                                -> select();

                    if(false == $info_ac){
                         $res["user_info"][$i]["pro"][$pro_id] = "wa";
                    }else{
                         $res["user_info"][$i]["pro"][$pro_id] = round((strtotime($info_ac[0]["date"]) -strtotime($date_start))/60);
                         $res["user_info"][$i]["pro"]["num_ac"] += 1;
                         $res["user_info"][$i]["pro"]["time_ac"] +=  $res["user_info"][$i]["pro"][$pro_id];
                    }
                }
               
            }
            
            return $res;
        }
        
}


?>

