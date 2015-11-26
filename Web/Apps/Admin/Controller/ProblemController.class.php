<?php
namespace Admin\Controller;
use Think\Controller;

header("Content-Type:text/html;charset=utf-8");

class ProblemController extends Controller {
	public function index(){
		$problem = D("problem");
		$info_pro = $problem->getlist();

		usort($info_pro, function($a, $b){
			return $a["pro_id"] < $b["pro_id"];
		});

		$this->assign("info_pro",$info_pro);

		$this->display("default/problem/index");
	}

	/*添加题目界面*/
	public function add(){
		$this->display("default/problem/add");
	}

	/*添加题目界面*/
	public function form_add(){
		$pro_id = I("post.pro_id");
		if(false == empty($pro_id)){
			$data["pro_id"] = $pro_id;
		}

		$data["title"] = I("post.title");
		$data["time_lim"] = I("post.time_lim");
		$data["mem_lim"] = I("post.mem_lim");
		$data["status"] = I("post.status");
		
		$problem = D("problem");
		$pro_id = $problem->addpro($data);

		$dir_pro = C("PATH_PROBLEM").$pro_id."/";
		$path_descri = $dir_pro."descri.html";
		$path_input = $dir_pro."input.html";
		$path_output = $dir_pro."output.html";
		$path_input_data = $dir_pro."input_data.html";
		$path_output_data = $dir_pro."output_data.html";
		$path_hint = $dir_pro."hint.html";


		$res = mkdir($dir_pro);
		if(true == $res){
			$res = fopen($path_descri, "w");
			if(true == $res){
				$str = $_POST["desc"];
				$res = file_put_contents($path_descri, $str);

				$res = fopen($path_input, "w");
				if(true == $res){
					$str = $_POST["input"];
					$res = file_put_contents($path_input, $str);

					$res = fopen($path_output, "w");
					if(true == $res){
						$str = $_POST["output"];
						$res = file_put_contents($path_output, $str);
						
						$res = fopen($path_input_data, "w");
						if(true == $res){
							$str = $_POST["input_data"];
							$res = file_put_contents($path_input_data, $str);

							$res = fopen($path_output_data, "w");
							if(true == $res){
								$str = $_POST["output_data"];
								$res = file_put_contents($path_output_data, $str);

								$res = fopen($path_hint, "w");
								if(true == $res){
									$str = $_POST["hint"];
									$res = file_put_contents($path_hint, $str);
								}
							}
						}
					}
				}
			}
		}

		if(false == $res){
			dump($dir_pro);
			//删除冗余文件，清除数据库条目
			$problem->delpro($pro_id);

			unlink($path_descri);
			unlink($path_input);
			unlink($path_output);
			unlink($path_input_data);
			unlink($path_output_data);
			unlink($path_hint);
			rmdir($dir_pro);

			$this->redirect('problem/index', NULL, 2, '创建题目失败，检查文件夹权限.<br />正在跳转题目列表界面…');
		}

		$this->index();
	}

	/*修改题目状态*/
	public function changestatus(){
		$pro_id = I("get.pro_id");
		$status = I("get.status");

		var_dump($pro_id);
		$problem = D("problem");
		$res = $problem-> changestatus($pro_id,$status);

		if(false == $res){
			 $this->redirect('problem/index', NULL, 1, '切换失败.<br />正在跳转题目列表界面…');
		}else{
			 $this->redirect('problem/index', NULL, 0, '切换成功`.<br />正在跳转题目列表界面…');
		}
	}

	/*更新题目*/
	public function update(){
		$pro_id = I("get.pro_id");

		$problem = D("problem");
		$info_pro = $problem-> proinfo($pro_id);

		$dir_pro = C("PATH_PROBLEM").$pro_id."/";
		$path_descri = $dir_pro."descri.html";
		$path_input = $dir_pro."input.html";
		$path_output = $dir_pro."output.html";
		$path_input_data = $dir_pro."input_data.html";
		$path_output_data = $dir_pro."output_data.html";
		$path_hint = $dir_pro."hint.html";

		$info_pro["descri"] = file_get_contents($path_descri);
		$info_pro["input"] = file_get_contents($path_input);
		$info_pro["output"] = file_get_contents($path_output);
		$info_pro["input_data"] = file_get_contents($path_input_data);
		$info_pro["output_data"] = file_get_contents($path_output_data);
		$info_pro["hint"] = file_get_contents($path_hint);

		$this->assign("info_pro", $info_pro);
		$this->display("default/problem/update");
	}

	/*修改题目的表单*/
	public function form_update(){
		$data["pro_id"] = I("post.pro_id");
		$data["title"] = I("post.title");
		$data["time_lim"] = I("post.time_lim");
		$data["mem_lim"] = I("post.mem_lim");
		$data["status"] = I("post.status");
		$data["date"] = I("post.date");

		$problem = D("problem");

		$info_pro = $problem-> proinfo($data["pro_id"]);
		
		if($data != $info_pro){
			$res = $problem->updatepro($data);;
		}
		
		$res = true;

		if(true == $res){
			$dir_pro = C("PATH_PROBLEM").$data["pro_id"]."/";

			$path_descri = $dir_pro."descri.html";
			$path_input = $dir_pro."input.html";
			$path_output = $dir_pro."output.html";
			$path_input_data = $dir_pro."input_data.html";
			$path_output_data = $dir_pro."output_data.html";
			$path_hint = $dir_pro."hint.html";

			$res = fopen($path_descri, "w");
			if(true == $res){
				$str = $_POST["desc"];
				$res = file_put_contents($path_descri, $str);

				$res = fopen($path_input, "w");
				if(true == $res){
					$str = $_POST["input"];
					$res = file_put_contents($path_input, $str);

					$res = fopen($path_output, "w");
					if(true == $res){
						$str = $_POST["output"];
						$res = file_put_contents($path_output, $str);
						
						$res = fopen($path_input_data, "w");
						if(true == $res){
							$str = $_POST["input_data"];
							$res = file_put_contents($path_input_data, $str);

							$res = fopen($path_output_data, "w");
							if(true == $res){
								$str = $_POST["output_data"];
								$res = file_put_contents($path_output_data, $str);

								$res = fopen($path_hint, "w");
								if(true == $res){
									$str = $_POST["hint"];
									$res = file_put_contents($path_hint, $str);
								}
							}
						}
					}
				}
			}
		}


		if(false == $res){
			var_dump($dir_pro);
			$this->redirect('problem/index', NULL, 2, '更新题目失败，检查文件夹权限.<br />正在跳转题目列表界面…');
		}

		$this->redirect('problem/index', NULL, 0, '更新成功.<br />正在跳转题目列表界面…');
	}


	/*删除题目*/
	public function delpro(){
		$pro_id = I("get.pro_id");

		$problem = D("problem");
		$res = $problem-> delpro($pro_id);

		$dir_pro = C("PATH_PROBLEM").$pro_id."/";
		$path_descri = $dir_pro."descri.html";
		$path_input = $dir_pro."input.html";
		$path_output = $dir_pro."output.html";
		$path_input_data = $dir_pro."input_data.html";
		$path_output_data = $dir_pro."output_data.html";
		$path_hint = $dir_pro."hint.html";

		unlink($path_descri);
		unlink($path_input);
		unlink($path_output);
		unlink($path_input_data);
		unlink($path_output_data);
		unlink($path_hint);
		rmdir($dir_pro);

		$this->index();
	}
}