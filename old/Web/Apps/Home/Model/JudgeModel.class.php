<?php
namespace Home\Model;
use Think\Model;
/*
*评测机相关模型
*/
class JudgeModel extends Model {

        /*把提交信息存入数据库*/
        public function submit($data){
            $data['status'] = "WAIT";

            if(false == $this->data($data)->add()){
                return false;
            }

            return true;
        }

        /*获取单条题目的评测结果*/
        public function getuserstatus($pro_id,$user_id){
            $query["pro_id"] = $pro_id;
            $query["user_id"] = $user_id;

            $res = $this -> where($query)
                               -> field(array("status"))
                               -> select();

            if(false == $res){
                return -1;
            }

            foreach ($res as $value) {
                if("AC " == $value["status"]){
                    return 1;
                }
            }

            return 0;
        }

        /*检查run_id是否已经存在*/
        public function check_run_id($run_id){
            $query['run_id'] = $run_id;

            if(NULL == $this->where($query)
                                     ->field(array("run_id"))
                                    ->select()){
                return true;
            }

            return false;
        }

        /*获取指定题目的通过数、总提交数和通过率*/
        public function get_pro_ratio($pro_id){
            $query['pro_id'] = $pro_id;
            $res['num_total'] = $this->where($query)
                                                    ->count(); //总提交数
            $query['status'] = "AC";
            $res['num_ac'] = $this->where($query)
                                                    ->count(); //总AC数

             $num_total = (int)$res["num_total"];
             $num_ac = (int)$res["num_ac"];

            return $res;
        }

        /*获取用户评测信息*/
        public function getuserinfo($userid){
            $query["user_id"] = $userid;

            $num_total = $this->where($query)
                                ->count();

            $query["status"] = "AC ";
            $num_ac = $this->where($query)
                                        ->count();

            $res = $this->where($query)
                                        ->distinct(true)
                                        ->field(array('pro_id'))
                                        ->select();
                                        
            $num_pro = sizeof($res);

            if(false == $res){
                return false;
            }else{
                $res["num_total"] = $num_total;
                $res["num_ac"] = $num_ac;
                $res["num_pro"] = $num_pro;

                return $res;
            }
        }

         /*获取用户正确率相关信息*/
        public function getuserratio($userid){
             $query["user_id"] = $userid;

            $num_total = $this->where($query)
                                ->count();

            $query["status"] = "AC ";
            $num_ac = $this->where($query)
                                        ->count();

            $res = $this->where($query)
                                        ->distinct(true)
                                        ->field(array('pro_id'))
                                        ->select();
            
            $num_pro = sizeof($res);
            $res["num_total"] = $num_total;
            $res["num_ac"] = $num_ac;
            $res["num_pro"] = $num_pro;

            return $res; 
        }

        /*根据页数获取评测信息列表*/
         public function status_list($page,$query){
            $num_page = (int)C(PAGE_NUM);

            //获取题目总数
            $total_num = $this -> where($query) 
                                          ->count();

             //获取当前题目数
            if( $total_num/20 >= $page){
                    $list_num =  20;
            }else{
                    $list_num = $total_num%20;
            }
            
            //根据时间排序
            $res = $this -> where($query)
                                -> order("date desc")
                                -> limit(($page-1)*$num_page,$num_page)
                                -> select();
            
            if(false == $res){
                return false;
            }

            $res['num_total'] = $total_num;
            $res['num_list'] = $list_num;
            return $res;
        }
}
?>