<?php
namespace Home\Controller;
//header("Content-Type: text/html;charset=utf-8");
use Think\Controller;

header("Content-Type:text/html;charset=utf-8");

//通行证相关控制器
class PassportController extends Controller {
	/*检测用户名是否存在*/
	public function checkUsername($username){
		$user = D("Passport");
		return $user->checkUsername($username);
	}

	/*检测昵称是否存在*/
	public function checknickname($nickname){
		$user = D("Passport");
		return $user->checknickname($nickname);
	}

	/*登录界面*/
	public function login(){
		$this->assign("nav","login");
		$this->display("default/passport/login");
	}

	/*登录表单处理*/
	public function fromlogin(){
		$info_login['username'] = I("post.username");
		$info_login['password'] = I("post.password");

		$passport = D("Passport");
		$res = $passport->login($info_login);

		if(false == $res){
			$this->redirect('Index/index', NULL, 1, '登录失败，请检查用户名或密码.<br />正在跳转回首页……');
		}else{
			cookie("user_token", $res['user_token'], 24*60*60);
			cookie("nickname", $res['nickname'], 24*60*60);
			cookie("user_id", $res['user_id'], 24*60*60);
			$this->redirect('Index/index', NULL, 0);
		}
		var_dump($res);
	}

	/*用户结束登陆*/
	public function logout(){
		cookie("user_token", null);
		cookie("nickname", null);
		cookie("user_id", null);

		$passport = D("Passport");
		$res = $passport->logout(cookie("user_token"));
		$this->redirect('Index/index', NULL, 1, '注销成功.<br />正在跳转回首页……');
	}

	/*用户中心*/
	public function ucenter(){
		$user_id = I("get.user_id");

		$judge = D("judge");
		$info_judge = $judge->getuserinfo($user_id);
		if(false == $info_judge){
			$info_judge["num_total"] = 0;
			$info_judge["num_ac"] = 0;
			$info_judge["num_pro"] = 0;
		}
		
		$info_ac = $info_judge;

		unset($info_ac["num_total"]);
		unset($info_ac["num_ac"]);
		asort($info_ac);

		$userinfo = D("passport");
		$res = $userinfo->getuserinfo($user_id);
		if(false == $res){
			$this->redirect('status/index', NULL, 1, '获取用户信息失败.<br />正在跳转回状态页……');
		}
		$info_user["nickname"] = $res[0]["nickname"];
		$info_user["email"] = $res[0]["email"];

		$this->assign("info_judge", $info_judge);
		$this->assign("info_ac", $info_ac);
		$this->assign("info_user", $info_user);
		$this->display("default/passport/ucenter");
	}
	 /*用户注册的表单处理*/
	public function register(){
		$this->assign("nav","register");
		$this->display("default/passport/register");
	}

	 /*用户注册的表单处理*/
	public function formregister(){
		$info_register['username'] = rtrim(I("post.username"));
		$info_register['password'] = rtrim(I("post.password"));
		$info_register['email'] = rtrim(I("post.email"));
		$info_register['nickname'] = rtrim(I("post.nickname"));

		foreach ($info_register as $value) {
			if(empty($value)){
				$this->redirect('Passport/register', NULL, 2, '不能以单纯地空格为单个项.<br />正在跳转回上一页……');
			}
		}
		$res = $this->checkUsername($info_register["username"]);

		if(false == $res){
			$res = $this->checknickname($info_register["nickname"]);
			if(false == $res){
				$passport = D("Passport");
				$res = $passport->register($info_register);
				if(false == $res){
					$this->redirect('Passport/register', NULL, 1, '注册失败，请联系管理员.<br />正在跳转回上一页……');
				}
			}else{
			 $this->redirect('Passport/register', NULL, 2, '昵称已经存在.<br />正在跳转回上一页……');
			}
		}else{
			 $this->redirect('Passport/register', NULL, 2, '用户名已经存在.<br />正在跳转回上一页……');
		}

		 $this->redirect('Passport/login', NULL, 1, '注册成功.<br />正在跳转到登录页……');
	}


	/*用户token验证
	@param $token 用户token
		  $isId 是否返回用户id
	@return 返回预设CODE
		  无误还可返回 用户id
	*/
	public function loginTokenCheck($token,$isId=false){
		$response['code'] = "1000";

		if(empty($token)){
			$response['code'] = "4001";
		}else{
			$user = D("Passport");
			$res = $user->loginTokenCheck($token);
			
			if(2011 != $res && 2012 != $res){
				if(true == $isId){
					$response['userid'] =  $res;
				}
			}else{
				$response['code'] = $res;
			}
		}

		return $response;
	}
}
?>



