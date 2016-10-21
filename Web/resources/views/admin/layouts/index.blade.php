<!DOCTYPE html>
<html lang="en">
<head>
    @include('admin.partials.head')
    <title>@section('title')@show</title>
    @yield("token","")
</head>
<body>
<div class="container-fluid" style="min-height:100%;">
    <div class="row" style="min-height:100%;">
        <div class="col-sm-12" style="margin-top:15px;">
            @include('admin.partials.notifications')
        </div>
        @section('page_content')
            <div class="col-sm-12">
                <div class="page-header">
                    <h2>欢迎使用车省心<small>Ver 1.0.0</small></h2>
                </div>
            </div>
        @show
    </div>
</div>
@include('admin.partials.footer')
@section('custom_js')
    <script>
        function confirmurl(url,message)
        {
            if(confirm(message)) {
                location.href = url;
            }
        }
    </script>
@show
</body>
</html>