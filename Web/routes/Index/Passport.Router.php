<?php
/**
 * 通行证相关路由器
 */
Route::group(['middleware' => ['web'],'namespace' => 'Index','prefix'=>'/'], function(){
    Route::group(['namespace' => 'Passport','prefix'=>'passport'], function(){
        Route::get('/login',function (){
            return view("index.passport.login");
        });
        Route::get('/register',function (){
            return view("index.passport.register");
        });
    });
});