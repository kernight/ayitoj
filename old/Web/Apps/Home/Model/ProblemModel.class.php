<?php
namespace Home\Model;
use Think\Model;
/*
*题目相关模型
*/
class ProblemModel extends Model {

        /*获取题目详细信息*/
        public function detail($pro_id){
            $insert['pro_id'] = $pro_id;
            $insert['status'] = "open";

            $res = $this->where($insert)
                                    ->field(array("title, time_lim, mem_lim"))
                                    ->find();
            if(false == $res){
                return false;
            }

            return $res;
        }

        /*根据页数获取题目列表*/
         public function pro_list($page){
            $num_page = (int)C(PAGE_NUM);

            $query["status"] = "open";

            //获取题目总数
            $total_num = $this -> where($query)
                                          -> count();

             //获取当前题目数
              if( $total_num/20 >= $page){
                    $list_num =  20;
            }else{
                    $list_num = $total_num%20;
            }
                                
            //根据pro_id排序
            $res = $this -> where($query)
                                -> order("pro_id")
                                -> field(array("pro_id,title,date"))
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