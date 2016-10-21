DROP TABLE IF EXISTS `ayitoj_valid_info`;
CREATE TABLE `ayitoj_valid_info` (
  `id` int(11) NOT NULL  AUTO_INCREMENT COMMENT '序列id',
  `user_id` bigint(20) NOT NULL  COMMENT '用户id',
  `type` int(4) NOT NULL DEFAULT 0 COMMENT '验证类型 0 邮箱验证码 1 手机验证码',
  `code` varchar(255) NOT NULL COMMENT '验证码',
  `status` int(1) NOT NULL DEFAULT 0 COMMENT  '是否验证过 0 未验证 1 已验证',
  `create_time` int(11) NOT NULL DEFAULT 0 COMMENT '创建时间',
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=0 DEFAULT CHARSET=utf8;
