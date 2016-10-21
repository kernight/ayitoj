-- phpMyAdmin SQL Dump
-- version 4.0.10deb1
-- http://www.phpmyadmin.net
--
-- 主机: localhost
-- 生成日期: 2015-09-15 04:41:15
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
-- 表的结构 `oj_judge`
--

CREATE TABLE IF NOT EXISTS `oj_judge` (
  `index` int(11) NOT NULL AUTO_INCREMENT,
  `run_id` int(11) NOT NULL,
  `pro_id` int(11) NOT NULL,
  `user_id` int(11) NOT NULL,
  `time_lim` int(11) NOT NULL,
  `mem_lim` int(11) NOT NULL,
  `result` text,
  `info` text,
  PRIMARY KEY (`index`),
  UNIQUE KEY `run_id` (`run_id`),
  UNIQUE KEY `index` (`index`)
) ENGINE=InnoDB  DEFAULT CHARSET=utf8 AUTO_INCREMENT=2 ;

--
-- 转存表中的数据 `oj_judge`
--

INSERT INTO `oj_judge` (`index`, `run_id`, `pro_id`, `user_id`, `time_lim`, `mem_lim`, `result`, `info`) VALUES
(1, 123456, 1, 1, 1000, 65535, 'CE', 'Main.cpp: In function â€˜int main(int, const char**)â€™:\nMain.cpp:7:10: error: â€˜asdasâ€™ was not declared in this scope\n  int a,b;asdas\n          ^\nMain.cpp:8:2: error: expected â€˜;â€™ before â€˜whileâ€™\n  while(cin>>a>>b){\n  ^\nMain.cpp:7:6: warning: unused variable â€˜aâ€™ [-Wunused-variable]\n  int a,b;asdas\n      ^\nMain.cpp:7:8: warning: unused variable â€˜bâ€™ [-Wunused-variable]\n  int a,b;asdas\n        ^\nÿ');

-- --------------------------------------------------------

--
-- 表的结构 `oj_problem`
--

CREATE TABLE IF NOT EXISTS `oj_problem` (
  `index` int(11) NOT NULL AUTO_INCREMENT,
  `pro_id` int(11) NOT NULL,
  `title` text NOT NULL,
  `time_lim` int(11) NOT NULL,
  `mem_lim` int(11) NOT NULL,
  `num_data` int(11) NOT NULL,
  PRIMARY KEY (`index`),
  UNIQUE KEY `index` (`index`)
) ENGINE=InnoDB  DEFAULT CHARSET=utf8 AUTO_INCREMENT=10001 ;

--
-- 转存表中的数据 `oj_problem`
--

INSERT INTO `oj_problem` (`index`, `pro_id`, `title`, `time_lim`, `mem_lim`, `num_data`) VALUES
(10000, 1, 'A+B(一)', 1000, 65535, 1);

-- --------------------------------------------------------

--
-- 表的结构 `oj_user`
--

CREATE TABLE IF NOT EXISTS `oj_user` (
  `index` int(11) NOT NULL AUTO_INCREMENT,
  `user_id` int(11) NOT NULL,
  `username` text NOT NULL,
  `password` text NOT NULL,
  `nickname` text NOT NULL,
  `email` text NOT NULL,
  `tel` int(11) NOT NULL,
  `truthname` text NOT NULL,
  `admin` int(11) NOT NULL,
  PRIMARY KEY (`index`)
) ENGINE=InnoDB  DEFAULT CHARSET=utf8 AUTO_INCREMENT=10001 ;

--
-- 转存表中的数据 `oj_user`
--

INSERT INTO `oj_user` (`index`, `user_id`, `username`, `password`, `nickname`, `email`, `tel`, `truthname`, `admin`) VALUES
(10000, 1, 'test', 'test', '测试账户', '', 0, '', 0);

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
