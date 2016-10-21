DROP TABLE IF EXISTS `ayitoj_problem`;
CREATE TABLE `ayitoj_problem` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `status` int(5) NOT NULL DEFAULT 0 COMMENT '题目状态 0 锁定 1 开放',
  `title` varchar(255) NOT NULL DEFAULT '' COMMENT '题目标题',
  `descri` text NOT NULL  COMMENT '题目描述',
  `input_data` text NOT NULL  COMMENT '输入',
  `output_data` text NOT NULL  COMMENT '输出',
  `tips` text NOT NULL  COMMENT '提示',
  `from` varchar(255) NOT NULL  COMMENT '来源',
  `create_time` text NOT NULL  COMMENT '创建时间',
  `time_lim` int(11) NOT NULL  COMMENT '时间限制',
  `mem_lim` int(11) NOT NULL  COMMENT '空间限制',
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=1000 DEFAULT CHARSET=utf8;

