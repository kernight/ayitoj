<?php
namespace Home\Model;
use Think\Model;

/*
*通行证相关模型
*/
class PassportModel extends Model {
    //指定数据库表名
    protected $tableName = 'user'; 

    /*检查用户是否存在*/
    public function checkUsername($username){
        $query['username'] = $username;

        $res = $this->where($query)
                      ->field(array('user_id'))
              ->find();

        if(empty($res['user_id'])){
            return false;
        }

        return true;
    }

     /*检查昵称是否存在*/
    public function checknickname($nickname){
        $query['nickname'] = $nickname;

        $res = $this->where($query)
                      ->field(array('user_id'))
              ->find();

        if(empty($res['user_id'])){
            return false;
        }

        return true;
    }

    /*账号密码登录*/
    public function login($info_login){
        $res = $this->where($info_login)
                    ->field(array('user_id,password,nickname'))
                    ->find();

        if(empty($res['user_id'])){
            return false;
        }

        if($info_login['password'] == $res['password']){
             $res["user_token"] = $this->loginTokenSet($res['user_id']);
             if(false == $res["user_token"]){
                return false;
             }else{
                return $res;
             }
        }else{
            return false; 
        }
    }

    /*用户结束登陆
    @param $userid 用户id
    @return 无
    */
    public function logout($usertoken){
        $this->loginTokenSet($userid, -7);
    }

    /*用户注册*/
    public function register($info_register){
            $info_register['email_status'] = "未验证";

            return $this->data($info_register)->add();
    }

    /*设置登录token
    @param $userid 用户ＩＤ
                    $day token有效期
    @return token 登陆码
    */
    public function loginTokenSet($userid){
        $StringEncode = new \Org\Util\StringEncode;
        $day = 1;

        $data['user_id'] = $userid;
        $data['token'] = $StringEncode->login_token_Encode($userid);
        $data['token_date']= date('Y-m-d H:i:sa',strtotime('+'.$day.' day'));

        $this->save($data);

        return $data['token'];
    }

    /*验证登录token
    @param $token 登陆码
    @return 返回预设CODE
                    无误返回 用户id
    */
    public function loginTokenCheck($token){   
        $StringEncode = new \Org\Util\StringEncode;

        $userid = $StringEncode->login_token_Decode($token);
        $date = date('Y-m-d');

        if(empty($userid)){
            return false;
        }

        $query['user_id'] = $userid;
        $res = $this->where($query)
                            ->field(array("token, token_date"))
                            ->find();


        $token_db = $res['token'];
        $token_date_db = $res['token_date'];

        if(0 != strcmp($token, $token_db)){
            return false;
        }

        if(0 < strcmp($date, $token_date_db)){
            return false;
        }

        return $userid;
    }

     /*获取用户评测信息*/
        public function getuserinfo($userid){
            $query["user_id"] = $userid;

            $res = $this->where($query)
                                        ->field(array('nickname,email'))
                                        ->select();

            if(false == $res){
                return false;
            }else{
                return $res;
            }
        }

        /*获取所有用户列表*/
        public function getuserlist(){
            $num_total = $this -> count();
            $res = $this -> field(array("user_id","nickname"))
                                -> select();

            if(false == $res){
                return false;
            }

            $res["num_total"] = $num_total;

            return $res;
        }
}

?>

