<!DOCTYPE html>
<html lang="en">
<head>
@include('admin.partials.head')
<title>@yield("name","后台管理")-@section('title')@show</title>
@yield("token","")
</head>
<body>
@include('admin.partials.header')

<div class="container-fluid">
    <div class="row">
        @include('admin.partials.lefter')
        <div class="col-sm-10 right-main" id="content">
            <iframe src="{{ url('admin/info') }}" frameborder="0" id="appiframe-0" name="appiframe-0" class="appiframe" style="width:100%; min-height:100%;"></iframe>
        </div>
    </div>
</div>

@include('admin.partials.footer')
<script>
    $content = $('#content');
    $nav = $('.left-nav');
    $content.height($(window).height()-40);
    $nav.height($(window).height()-40);
</script>
</body>
</html>