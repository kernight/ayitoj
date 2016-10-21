<?php
namespace Admin\Controller;
use Think\Controller;

header("Content-Type:text/html;charset=utf-8");

class ContestController extends Controller {
	public function index(){
		$contest = D("contest");
		$info_contest = $contest->getlist();

		usort($info_contest, function($a, $b){
			return $a["contest_id"] < $b["contest_id"];
		});

		$this->assign("info_contest",$info_contest);

		$this->display("default/contest/index");
	}

	public function add(){
		$this->display("default/contest/add");
	}

	public function form_add(){
		$contest_id = I("post.contest_id");

		if(false == empty($contest_id)){
			$data["contest_id"] = $contest_id;
		}

		$data["title"] = I("post.title");
		$data["date_start"] = I("post.date_start");
		$data["date_end"] = I("post.date_end");
		$data["status"] = I("post.status");

		$contest = D("contest");
		$res = $contest->addcontest($data);

		if(true == $res){
			$pro = I("post.pro_id");
			$key = 0;
			$problem = D("problem");
			
			if(true == $pro){
				foreach ($pro as $value) {
					$pro_id = $value;
					$info_pro = $problem->proinfo($pro_id);
					if(true == $info_pro){
						$data_pro[$key]["contest_id"] = $contest_id;
						$data_pro[$key]["pro_id"] = $value;
						$data_pro[$key]["title"] = $info_pro["title"];

						$key++;
					}
				}

				$contest->contestaddpro($contest_id,$data_pro);
			}
		}
		
		if(false == $res){
			 $this->redirect('contest/add', NULL, 1, '添加失败.<br />正在跳转回原来界面…');
		}else{
			 $this->redirect('contest/index', NULL, 0, '添加成功`.<br />正在跳转竞赛列表…');
		}
	}

	public function update(){
		$contest_id = I("get.contest_id");

		$contest = D("contest");
		$info_contest = $contest->contestinfo($contest_id);

		if(false == $info_contest){
			$this->redirect('contest/index', NULL, 1, '获取竞赛信息失败.<br />正在跳转回竞赛列表…');
		}

		$info_pro = $contest->getprolist($contest_id);

		$this->assign("info_contest",$info_contest);
		$this->assign("info_pro",$info_pro);

		$this->display("default/contest/update");
	}

	public function form_update(){
		$contest_id = I("post.contest_id");
		$data["contest_id"] = I("post.contest_id");
		$data["title"] = I("post.title");
		$data["date_start"] = I("post.date_start");
		$data["date_end"] = I("post.date_end");
		$data["status"] = I("post.status");

		$contest = D("contest");
		$info_contest = $contest->contestinfo($contest_id);

		if($info_contest != $data){
			$res = $contest->updatecontest($data);
		}else{
			$res = true;
		}

		if(true == $res){
			$pro = I("post.pro_id");

			$key = 0;
			$problem = D("problem");
			
			if(true == $pro){
				foreach ($pro as $value) {
					$pro_id = $value;
					$info_pro = $problem->proinfo($pro_id);
					if(true == $info_pro){
						var_dump($value);
						$data_pro[$key]["contest_id"] = $contest_id;
						$data_pro[$key]["pro_id"] = $value;
						$data_pro[$key]["title"] = $info_pro["title"];

						$key++;
					}
				}
				$contest->contestaddpro($contest_id,$data_pro);
			}
		}

		if(false == $res){
			 $this->redirect('contest/index', NULL, 1, '修改失败.<br />正在跳转竞赛列表…');
		}else{
			 $this->redirect('contest/index', NULL, 0, '修改成功`.<br />正在跳转竞赛列表…');
		}
	}

	public function delcontest(){
		$contest_id = I("get.contest_id");

		$contest = D("contest");
		$res = $contest->delcontest($contest_id);

		if(false == $res){
			 $this->redirect('contest/index', NULL, 1, '删除失败.<br />正在跳转竞赛列表…');
		}else{
			 $this->redirect('contest/index', NULL, 0, '删除成功`.<br />正在跳转竞赛列表…');
		}
	}
	public function changestatus(){
		$contest_id = I("get.contest_id");
		$status = I("get.status");

		var_dump($contest_id);
		$contest = D("contest");
		$res = $contest-> changestatus($contest_id,$status);

		if(false == $res){
			 $this->redirect('contest/index', NULL, 1, '切换失败.<br />正在跳转竞赛列表…');
		}else{
			 $this->redirect('contest/index', NULL, 0, '切换成功`.<br />正在跳转竞赛列表…');
		}
	}

}