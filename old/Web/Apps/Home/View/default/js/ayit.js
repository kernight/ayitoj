//获取cookie
function getCookie(c_name) {
    if (document.cookie.length > 0) {
        c_start = document.cookie.indexOf(c_name + '=');
        if (c_start != -1) {
            c_start = c_start + c_name.length + 1;
            c_end = document.cookie.indexOf(';', c_start);
            if (c_end == -1) {
                c_end = document.cookie.length;
            }
            return unescape(document.cookie.substring(c_start, c_end));
        }
    }
    return '';
}

//设置cookie
function setCookie(c_name, value, expiredays, isPath) {
    var path = "";
    if(("undefined" == typeof(isPath)) || "true" == isPath){
        path=";path=/";
    }

    var exdate = new Date();
    exdate.setDate(exdate.getDate() + expiredays);
    document.cookie = c_name + '=' + escape(value) + 
        ((expiredays == null) ? '': '; expires=' + exdate.toGMTString())
        //设置全局
        + path;
}

//删除cookies
function delCookie(cname) {
    var exdate = new Date();
    exdate.setTime(exdate.getTime() - 1);
    var cval=getCookie(cname);
    if(cval!=null)
        document.cookie= cname + '='+cval+';expires=' + exdate.toGMTString()
        //设置全局
        +";path=/";
}


//检查cookie是否存在
function checkCookie(cname) {
    value = getCookie(cname);
    if (value != null && value != '') {
        return value;
    } else {
        return null;
    }
}

