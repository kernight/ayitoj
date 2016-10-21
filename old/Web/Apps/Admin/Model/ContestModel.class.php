<?php
namespace Admin\Model;
use Think\Model;

/*竞赛相关的操作
*/
class ContestModel extends Model{
	protected $tableName = 'contest_info'; 

	/*获取单个竞赛信息*/
	public function contestinfo($contest_id){
		$query["contest_id"] = $contest_id;

		$res = $this -> where($query)
				->select();
		return $res[0];
	}

	/*获取竞赛列表*/
	public  function getlist($query){
		$res = $this -> where($query)
				-> select();

		return $res;
	}

	/*获取竞赛的题目列表*/
	public  function getprolist($contest_id){
		$query["contest_id"] = $contest_id;

		$res = $this ->table("oj_contest_problem")
				-> where($query)
				->field(array("pro_id"))
				-> select();

		return $res;
	}

	/*添加竞赛*/
	public  function addcontest($data){
		$res = $this -> add($data);

		return $res;
	}

	/*竞赛中添加题目*/
	public  function contestaddpro($contest_id,$data){
		$query["contest_id"] = $contest_id;

		$this ->table("oj_contest_problem")
			-> where($query)	//删除原来的题目
			-> delete();

		foreach ($data as $value) {
			$res = $this->table("oj_contest_problem")
				->field(array("pro_id","title","contest_id"))
				->add($value);
		}
		

		return $res;
	}

	/*修改竞赛*/
	public  function updatecontest($query){
		$res = $this -> save($query);

		return $res;
	}


	/*删除竞赛*/
	public  function delcontest($contest_id){
		$query["contest_id"] = $contest_id;

		$res = $this -> data($query)
				-> delete();

		$this ->table("oj_contest_problem")
			-> data($query)
			-> delete();

		return $res;
	}

	/*修改竞赛状态*/
	public function changestatus($contest_id,$status){
		$query["contest_id"] = $contest_id;
		
		if("open" == $status){
			$query["status"] = "close";
		}else if("close" == $status){
			$query["status"] = "lock";
		}else{
			$query["status"] = "open";
		}

		$res = $this -> save($query);

		if(true == $res){
			if("lock" == $query["status"]){
				$query_pro["contest_id"] = $contest_id;
				$info_pro = $this->table("oj_contest_problem")
						->where($query_pro)
						->field(array("pro_id"))
						->select();
				foreach ($info_pro as $value) {
					$query_info["pro_id"] = $value["pro_id"];
					$data["status"] = "close";
					$this->table("oj_problem")
						->where($query_info)
						->save($data);
				}
			}else{
				$query_pro["contest_id"] = $contest_id;
				$info_pro = $this->table("oj_contest_problem")
						->where($query_pro)
						->field(array("pro_id"))
						->select();

				foreach ($info_pro as $value) {
					$query_info["pro_id"] = $value["pro_id"];
					$data["status"] = "open";
					$this->table("oj_problem")
						->where($query_info)
						->save($data);
				}
			}
		}

		return $res;
	}
}
?>