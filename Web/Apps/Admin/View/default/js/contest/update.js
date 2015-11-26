$(document).ready(function() {
	var pro_index = $('#pro_area').children().length+1;

	$("#pro_add").click(function() {
		var div_pro = "<div id='div_pro_"+pro_index+"'><span>题目"+pro_index+"：</span><input name='pro_id_"+pro_index+"' type='number'/></div>";
		$("#pro_area").append(div_pro);
		pro_index += 1;
		// alert(div_pro);
	});
	$("#pro_del").click(function() {
		pro_index -= 1;
		if(0 >= pro_index){
			pro_index = 1;
		}
		$("#div_pro_"+pro_index).remove();
		// alert(div_pro);
	});
});