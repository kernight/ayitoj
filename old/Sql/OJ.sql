/*
Navicat MySQL Data Transfer

Source Server         : 本地
Source Server Version : 50505
Source Host           : localhost:3306
Source Database       : oj

Target Server Type    : MYSQL
Target Server Version : 50505
File Encoding         : 65001

Date: 2016-06-09 20:31:47
*/

SET FOREIGN_KEY_CHECKS=0;

-- ----------------------------
-- Table structure for oj_contest_info
-- ----------------------------
DROP TABLE IF EXISTS `oj_contest_info`;
CREATE TABLE `oj_contest_info` (
  `contest_id` int(11) NOT NULL AUTO_INCREMENT,
  `title` text NOT NULL,
  `status` text NOT NULL,
  `date_start` datetime NOT NULL,
  `date_end` datetime NOT NULL,
  PRIMARY KEY (`contest_id`),
  UNIQUE KEY `contest_id` (`contest_id`)
) ENGINE=InnoDB AUTO_INCREMENT=5 DEFAULT CHARSET=utf8;

-- ----------------------------
-- Table structure for oj_contest_problem
-- ----------------------------
DROP TABLE IF EXISTS `oj_contest_problem`;
CREATE TABLE `oj_contest_problem` (
  `index` int(11) NOT NULL AUTO_INCREMENT,
  `contest_id` int(11) NOT NULL,
  `pro_id` int(11) NOT NULL,
  `title` text NOT NULL,
  PRIMARY KEY (`index`)
) ENGINE=InnoDB AUTO_INCREMENT=59 DEFAULT CHARSET=utf8;

-- ----------------------------
-- Table structure for oj_judge
-- ----------------------------
DROP TABLE IF EXISTS `oj_judge`;
CREATE TABLE `oj_judge` (
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
) ENGINE=InnoDB AUTO_INCREMENT=4289219691 DEFAULT CHARSET=utf8;

-- ----------------------------
-- Table structure for oj_problem
-- ----------------------------
DROP TABLE IF EXISTS `oj_problem`;
CREATE TABLE `oj_problem` (
  `pro_id` int(11) NOT NULL AUTO_INCREMENT,
  `status` text NOT NULL,
  `title` text NOT NULL,
  `date` date NOT NULL,
  `time_lim` int(11) NOT NULL,
  `mem_lim` int(11) NOT NULL,
  PRIMARY KEY (`pro_id`),
  UNIQUE KEY `pro_id` (`pro_id`)
) ENGINE=InnoDB AUTO_INCREMENT=4 DEFAULT CHARSET=utf8;

-- ----------------------------
-- Table structure for oj_user
-- ----------------------------
DROP TABLE IF EXISTS `oj_user`;
CREATE TABLE `oj_user` (
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
) ENGINE=InnoDB AUTO_INCREMENT=28 DEFAULT CHARSET=utf8;
