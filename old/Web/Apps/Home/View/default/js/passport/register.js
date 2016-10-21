$(document).ready(function() {
	$("#form_register").submit(function() {
		var username = $("#in_username").val();
		var password = $("#in_password").val();
		var repassword = $("#in_repassword").val();
		var email = $("#in_email").val();
		var nickname = $("#in_nickname").val();
		if(6 > password.length) {
			alert("密码不能小于6位");
			return false;
		}
		if(password != repassword){
			alert("两次密码填写不相同");
			return false;
		}else{
			alert("表单还没填写完全");
			return false;
		}
	});
});