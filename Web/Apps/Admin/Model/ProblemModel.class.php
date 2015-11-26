<?php
namespace Admin\Model;
use Think\Model;

/*题目相关的操作
*/
class ProblemModel extends Model{
	/*添加题目*/
	public  function addpro($pro_data){
		$pro_data["date"] = date("Y-m-d");

		$res = $this -> data($pro_data)-> add();

		return $res;
	}

	/*删除题目*/
	public  function delpro($pro_id){
		$query["pro_id"] = $pro_id;

		$res = $this -> where($query)
				-> delete();

		$res = $this -> table("oj_judge")
				-> where($query)
				-> delete();

		$res = $this -> table("oj_contest_problem")
				-> where($query)
				-> delete();

		return $res;
	}

	/*获取题目信息*/
	public  function proinfo($pro_id){
		$query["pro_id"] = $pro_id;

		$res = $this -> where($query)
			        -> select();

		return $res[0];
	}


	/*修改题目*/
	public  function updatepro($data){
		$res = $this -> save($data);

		$res = $this->table("oj_contest_problem")	//更新竞赛中的题目标题
				->field(array("pro_id","title"))
				-> save($data);

		return $res;
	}

	/*获取题目列表*/
	public  function getlist($query){
		$res = $this -> where($query)
			      -> select();

		return $res;
	}

	/*修改题目状态*/
	public function changestatus($pro_id,$status){
		$query["pro_id"] = $pro_id;
		
		if("open" == $status){
			$query["status"] = "close";
		}else{
			$query["status"] = "open";
		}

		$res = $this -> save($query);

		return $res;
	}
}
?>