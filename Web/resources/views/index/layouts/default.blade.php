<!DOCTYPE html>
<html lang="zh-cn">
<head>
@include('index.partials.head')
<title>@yield("name","安阳工学院在线评测系统")-@section('title')@show</title>
@yield("token","")
</head>
<body>
@include('index.partials.header')
<div id="page-content" class="container">
    @section("page_content")
    @show
</div>
@include('index.partials.footer')
</body>
@include('index.partials.foot')
</html>