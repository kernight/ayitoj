<div id="area-header" class="container-fluid">
    <div class="container">
        <a class="navbar-brand" href="{{ url('/') }}"><span style="font-family: 'Microsoft YaHei UI Light';color: white">AYITOJ</span></a>
        <ul>
            <li @if($_SERVER["PATH_INFO"] == "/") class="active" @endif><a href="/">主页</a></li>
            <li @if(starts_with($_SERVER["PATH_INFO"],"/problem")) class="active" @endif ><a href="{{url("/problem/list")}}">问题</a></li>
            <li @if(starts_with($_SERVER["PATH_INFO"],"/status")) class="active" @endif ><a href="{{url("/status")}}">状态</a></li>
            <li @if(starts_with($_SERVER["PATH_INFO"],"/rank")) class="active" @endif ><a href="{{url("/rank/user")}}">排名</a></li>
            <li @if(starts_with($_SERVER["PATH_INFO"],"/contest")) class="active" @endif ><a href="{{url("/contest")}}">比赛</a></li>
        </ul>
        <ul class="pull-right">
            <li @if(starts_with($_SERVER["PATH_INFO"],"/passport/login")) class="active" @endif><a href="{{url("/passport/login")}}" data-no-turbolink="">登录</a></li>
            <li @if(starts_with($_SERVER["PATH_INFO"],"/passport/register")) class="active" @endif><a href="{{url("/passport/register")}}" data-no-turbolink="">注册</a></li>
        </ul>
    </div>
</div>