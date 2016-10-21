DROP TABLE IF EXISTS `ayitoj_user`;
CREATE TABLE `ayitoj_user` (
  `user_id` int(11) NOT NULL AUTO_INCREMENT COMMENT '用户id',
  `username` varchar(255) NOT NULL COMMENT '用户名',
  `password` varchar(512) NOT NULL COMMENT '密码',
  `nickname` varchar(255) NOT NULL COMMENT '昵称',
  `email` varchar(512) NOT NULL COMMENT '邮箱',
  `signtext` varchar(512) NULL COMMENT '个性签名',
  `sex` int(1) NOT NULL DEFAULT -1 COMMENT '性别 -1 未知 0 女 1 男',
  `tel` int(11) NOT NULL COMMENT '手机号码',
  `tel_status` int(1) NOT NULL DEFAULT 0 COMMENT  '手机号码',
  `email_status` int(1) NOT NULL DEFAULT 0 COMMENT '邮箱验证状态',
  `truthname` varchar(255) NOT NULL COMMENT '真实姓名',
  `admin` int(1) NOT NULL DEFAULT 0 COMMENT '是否为管理员 0 不是 1 是',
  `status` int(1) NOT NULL DEFAULT 1 COMMENT '是否启用 0 禁用 1 启用',
  PRIMARY KEY (`user_id`)
) ENGINE=InnoDB AUTO_INCREMENT=0 DEFAULT CHARSET=utf8;
