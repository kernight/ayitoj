-- phpMyAdmin SQL Dump
-- version 4.0.10deb1
-- http://www.phpmyadmin.net
--
-- 主机: localhost
-- 生成日期: 2015-09-22 11:33:55
-- 服务器版本: 5.5.44-0ubuntu0.14.04.1
-- PHP 版本: 5.5.9-1ubuntu4.11

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;

--
-- 数据库: `OJ`
--

-- --------------------------------------------------------

--
-- 表的结构 `oj_contest_info`
--

CREATE TABLE IF NOT EXISTS `oj_contest_info` (
  `contest_id` int(11) NOT NULL AUTO_INCREMENT,
  `title` text NOT NULL,
  `status` text NOT NULL,
  `date_start` datetime NOT NULL,
  `date_end` datetime NOT NULL,
  PRIMARY KEY (`contest_id`),
  UNIQUE KEY `contest_id` (`contest_id`)
) ENGINE=InnoDB  DEFAULT CHARSET=utf8 AUTO_INCREMENT=5 ;

--
-- 转存表中的数据 `oj_contest_info`
--

INSERT INTO `oj_contest_info` (`contest_id`, `title`, `status`, `date_start`, `date_end`) VALUES
(1, '1', 'open', '0000-00-00 00:00:00', '0000-00-00 00:00:00'),
(2, '2', 'open', '0000-00-00 00:00:00', '0000-00-00 00:00:00');

-- --------------------------------------------------------

--
-- 表的结构 `oj_contest_problem`
--

CREATE TABLE IF NOT EXISTS `oj_contest_problem` (
  `index` int(11) NOT NULL AUTO_INCREMENT,
  `contest_id` int(11) NOT NULL,
  `pro_id` int(11) NOT NULL,
  `title` text NOT NULL,
  PRIMARY KEY (`index`)
) ENGINE=InnoDB  DEFAULT CHARSET=utf8 AUTO_INCREMENT=59 ;

--
-- 转存表中的数据 `oj_contest_problem`
--

INSERT INTO `oj_contest_problem` (`index`, `contest_id`, `pro_id`, `title`) VALUES
(56, 1, 2, '2我asd'),
(57, 2, 1, 'A + B Problem I'),
(58, 2, 2, '2我asd');

-- --------------------------------------------------------

--
-- 表的结构 `oj_judge`
--

CREATE TABLE IF NOT EXISTS `oj_judge` (
  `run_id` bigint(20) NOT NULL AUTO_INCREMENT,
  `pro_id` int(11) NOT NULL,
  `user_id` int(11) NOT NULL,
  `contest_id` int(11) NOT NULL,
  `nickname` text NOT NULL,
  `time` int(11) NOT NULL,
  `memory` int(11) NOT NULL,
  `codelength` int(11) NOT NULL,
  `status` text,
  `date` datetime NOT NULL,
  PRIMARY KEY (`run_id`),
  UNIQUE KEY `run_id` (`run_id`)
) ENGINE=InnoDB  DEFAULT CHARSET=utf8 AUTO_INCREMENT=4289219691 ;

--
-- 转存表中的数据 `oj_judge`
--

INSERT INTO `oj_judge` (`run_id`, `pro_id`, `user_id`, `contest_id`, `nickname`, `time`, `memory`, `codelength`, `status`, `date`) VALUES
(2912465678, 1, 17, 1, '刘旭', 0, 0, 3, 'CE ', '2015-09-22 08:00:40'),
(3177642116, 1, 17, 1, '刘旭', 0, 1696, 113, 'AC ', '2015-09-21 10:23:30'),
(3275565084, 1, 21, 1, '13软工_刘旭', 0, 1696, 113, 'AC ', '2015-09-21 10:24:21'),
(4003028035, 2, 17, 1, '刘旭', 0, 1696, 113, 'AC ', '2015-09-22 08:01:50'),
(4258909397, 1, 17, 1, '刘旭', 0, 0, 5, 'CE ', '2015-09-22 07:55:43'),
(4289219690, 1, 21, 0, '13软工_刘旭', 0, 1696, 113, 'AC ', '2015-09-21 10:24:05');

-- --------------------------------------------------------

--
-- 表的结构 `oj_problem`
--

CREATE TABLE IF NOT EXISTS `oj_problem` (
  `pro_id` int(11) NOT NULL AUTO_INCREMENT,
  `status` text NOT NULL,
  `title` text NOT NULL,
  `date` date NOT NULL,
  `time_lim` int(11) NOT NULL,
  `mem_lim` int(11) NOT NULL,
  PRIMARY KEY (`pro_id`),
  UNIQUE KEY `pro_id` (`pro_id`)
) ENGINE=InnoDB  DEFAULT CHARSET=utf8 AUTO_INCREMENT=3 ;

--
-- 转存表中的数据 `oj_problem`
--

INSERT INTO `oj_problem` (`pro_id`, `status`, `title`, `date`, `time_lim`, `mem_lim`) VALUES
(1, 'open', 'A + B Problem I', '2015-09-16', 1000, 65535),
(2, 'open', '2我asd', '2015-09-22', 1000, 65535);

-- --------------------------------------------------------

--
-- 表的结构 `oj_user`
--

CREATE TABLE IF NOT EXISTS `oj_user` (
  `user_id` bigint(20) NOT NULL AUTO_INCREMENT,
  `token` text NOT NULL,
  `token_date` datetime NOT NULL,
  `username` text NOT NULL,
  `password` text NOT NULL,
  `nickname` text NOT NULL,
  `email` text NOT NULL,
  `tel` int(11) NOT NULL,
  `email_status` text NOT NULL,
  `truthname` text NOT NULL,
  `admin` int(11) NOT NULL,
  PRIMARY KEY (`user_id`)
) ENGINE=InnoDB  DEFAULT CHARSET=utf8 AUTO_INCREMENT=26 ;

--
-- 转存表中的数据 `oj_user`
--

INSERT INTO `oj_user` (`user_id`, `token`, `token_date`, `username`, `password`, `nickname`, `email`, `tel`, `email_status`, `truthname`, `admin`) VALUES
(1, '', '0000-00-00 00:00:00', 'test', 'test', '测试账户', '', 0, '', '', 0),
(17, '258dV3BSsd3J+oFHgUKCVscgRCHbWrjA3MyLWY1Ru34i9qwNSVfu+/y+70sJNnNK+E5a8Cr1ioP7PII78zpB72t4Hg9lxh3z+fl0x+I4QZg/8A', '2015-09-22 10:26:30', '刘旭', 'SHOUhuYh', '刘旭', '1836608435@qq.com', 0, '未验证', '', 0),
(21, '72a59MbMEjMILtvxA8NCquoUwdg2XtgT9Bw6MtCHIP5yOun9YzAUQW5JNynDqMRj/jeJDVWnmmRvCvU0VwENiqakbQLX0sEozdwELoJkhqyUNA', '2015-09-22 10:23:51', 'test2', 'test2', '13软工_刘旭', '1836608435@qq.com', 0, '未验证', '', 0),
(24, '87e5UHgPFND6+vZgOUwsHrHcIn+RNYhDhzEd98x936EwIVheoaEefOV8SosSdHniN3hpKPxH0yEZYekc3l59d79C2Df2ng6j62h/JfV3QUjwbA', '2015-09-22 07:01:41', 'test3', 'test3', 'test3', 'test3@qq.com', 0, '未验证', '', 0),
(25, '2213rCtDIs/kXJbN9+26Z24tFQU7T3fMCe1JoOB6px/Dny16SvQ8WYHhn9Ybf9+NFHA9Tm4LZPL/jgyOkVPNsNgwUrCnXDiPYOIpE7pqXf6K/w', '2015-09-22 07:02:55', 'test4', 'test4', 'test4', 'test4@qqcom', 0, '未验证', '', 0);

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
