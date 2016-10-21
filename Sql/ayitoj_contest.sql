
DROP TABLE IF EXISTS `ayitoj_contest`;
CREATE TABLE `ayitoj_contest` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `title` varchar(255) NOT NULL COMMENT '竞赛名称',
  `password` varchar(512) NULL COMMENT '竞赛密码',
  `status` int(5) NOT NULL DEFAULT 0 COMMENT '竞赛状态 0 禁用 1 启用',
  `problem_list` varchar(1024) NOT NULL DEFAULT '' COMMENT '竞赛题目id',
  `date_start` varchar(255) NOT NULL COMMENT '开始时间',
  `date_end` varchar(255) NOT NULL COMMENT '结束时间',
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=1 DEFAULT CHARSET=utf8;

