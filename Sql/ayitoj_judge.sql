DROP TABLE IF EXISTS `ayitoj_judge`;
CREATE TABLE `ayitoj_judge` (
  `id` int(11) NOT NULL AUTO_INCREMENT COMMENT '运行id',
  `pro_id` int(11) NOT NULL COMMENT '问题id',
  `user_id` int(11) NOT NULL COMMENT '用户id',
  `contest_id` int(11)  NULL COMMENT '竞赛id',
  `time` int(11) NOT NULL COMMENT '所用时间',
  `memory` int(11) NOT NULL COMMENT '所用内存',
  `codelength` int(11) NOT NULL COMMENT '代码长度',
  `status` varchar(255)NOT NULL DEFAULT 0 COMMENT '评判结果',
  `create_time` varchar(255) NOT NULL COMMENT '创建时间',
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=0 DEFAULT CHARSET=utf8;

