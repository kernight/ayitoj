@section("footer_js")
    <script src="//cdn.bootcss.com/jquery/1.11.3/jquery.min.js"></script>
    <script src="//cdn.bootcss.com/bootstrap/3.3.7/js/bootstrap.min.js"></script>
    <script src="//cdn.bootcss.com/jquery.pjax/1.9.6/jquery.pjax.min.js"></script>
    <script src="//cdn.bootcss.com/nprogress/0.2.0/nprogress.min.js"></script>
    <script>
        $(document).ready(function() {
            $(document).pjax('a', 'body');
            $(document).on('pjax:start', function() {
                NProgress.start();
            });
            $(document).on('pjax:end', function() {
                NProgress.done();
                self.siteBootUp();
            });
        });
    </script>
@show

@section("footer_custom_js")
@show