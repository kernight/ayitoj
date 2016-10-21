<?php
/**
 * 通行证相关路由器
 */
Route::group(['middleware' => ['web'],'namespace' => 'Index','prefix'=>'/'], function(){
        Route::get('/', function (){
            return view("index.index");
        });
});