<?php
namespace Home\Controller;
use Think\Controller;

header("Content-Type:text/html;charset=utf-8");

class JudgeController extends Controller {
	public function index(){
	             $judge = D("Judge");

	             $page_get = I("get.page");
	             $page = empty($page_get) ? 1 : $page_get;

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

	             $info_list = $judge->status_list($page,$query);

	             /*获取分页的信息*/
	             $info_page["now"] = $page;
	             $info_page['num_list'] = $info_list["num_list"];
	             $info_page['num_total'] = $info_list["num_total"];
	             $info_page['num_page'] = (int)(1 + $info_list["num_total"]/C("PAGE_NUM"));

	              /*剔除题目列表附加信息，只留下题目信息*/
	             unset($info_list["num_list"]);
	             unset($info_list["num_total"]);
	             
	             /*修改评测结果，转换为全文字显示*/
	             $judge = D("Judge");
	             for( $i = 0; $i < (int)$info_page['num_list']; $i++) {
             		$info_list[$i]["status"] = rtrim($info_list[$i]["status"]);
    
	                    switch ($info_list[$i]["status"]) {
	                    	case 'AC':
	                    		$info_list[$i]["info"] = "Accepted (答案正确)";
	                    		break;
			case "WA":
				$info_list[$i]["info"] = "Wrong Answer (答案错误)";
				break;
			case "CE":
				$info_list[$i]["info"] = "Compile Error (编译出错)";
				break;
			case "PE":
				$info_list[$i]["info"] = "Presentation Error (格式错误)";
				break;
			case "RE":
				$info_list[$i]["info"] = "Runtime Error (运行时出错)";
				break;
			case "RF":
				$info_list[$i]["info"] = "Restricted Function (非法程序)";
				break;
			case "MLE":
				$info_list[$i]["info"] = "Memory Limit Exceeded (内存超限)";
				break;
			case "OLE":
				$info_list[$i]["info"] = "Output Limit Exceeded (输出超限)";
				break;
			case "TLE":
				$info_list[$i]["info"] = "Time Limit Exceeded (时间超限)";
				break;
			case "Judging":
				$info_list[$i]["info"] = "Judging (正在评判)";
				break;
			case "WAIT":
				$info_list[$i]["info"] = "Waiting (等待评判)";
				break;

			default:
				$info_list[$i]["info"] = "System Error (系统运行出错,联系管理员)";
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
		
	             $this->assign("info_query",$query);
	             $this->assign("info_page",$info_page);
	             $this->assign("info_list",$info_list);

		$this->assign("nav","status");
		$this->display("default/judge/index");
	}

	public function compile()
	{
		$info_compile["run_id"] = I("get.run_id");
		$info_compile["nickname"] = I("get.nickname");
		$info_compile["user_id"] = I("get.user_id");
		$info_compile["date"] = I("get.date");

		if(false == empty($info_compile["run_id"])){
			$info_compile["run_id"] = htmlspecialchars($info_compile["run_id"]);
			$info_path = C("DATA_RUNING").$info_compile["run_id"]."/result.info";

			$res = fopen($info_path, "r");

			if(false == $res){
				$this->redirect('Judge/index', NULL, 1, '加载编译信息错误.<br />正在跳转回状态列表……');
			}
			$info_compile["info"] = fread($res, 102400);
			$info_compile["info"] = htmlspecialchars($info_compile["info"]);//转换为实体字符
			fclose($res);
		}else{
			$this->redirect('Judge/index', NULL, 1, '无效的运行编号.<br />正在跳转回状态列表……');
		}
		$this->assign("info_compile", $info_compile);

		$this->assign("nav","status");
		$this->display("default/judge/compile");
	}

	public function code()
	{
		$info_code["run_id"] = I("get.run_id");
		$info_code["nickname"] = I("get.nickname");
		$info_code["user_id"] = I("get.user_id");
		$info_code["date"] = I("get.date");

		if(false == empty($info_code["run_id"])){
			$info_code["run_id"] = htmlspecialchars($info_code["run_id"]);
			$info_path = C("DATA_RUNING").$info_code["run_id"]."/Main.cpp";

			$res = fopen($info_path, "r");

			if(false == $res){
				$this->redirect('Judge/index', NULL, 1, '加载编译信息错误.<br />正在跳转回状态列表……');
			}
			$info_code["info"] = fread($res, 102400);
			$info_code["info"] = htmlspecialchars($info_code["info"]);	//转换为实体字符
			fclose($res);
		}else{
			$this->redirect('Judge/index', NULL, 1, '无效的运行编号.<br />正在跳转回状态列表……');
		}
		$this->assign("info_code", $info_code);

		$this->assign("nav","status");
		$this->display("default/judge/code");
	}
}