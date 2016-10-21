<?php
namespace Home\Controller;
use Think\Controller;

header("Content-Type:text/html;charset=utf-8");

class IndexController extends Controller {
    public function index(){
        $this->assign("nav","index");
        $this->display("default/index");
    }
}