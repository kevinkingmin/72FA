/*
Navicat MySQL Data Transfer

Source Server         : localhost_3306
Source Server Version : 50720
Source Host           : localhost:3306
Source Database       : humablotpro

Target Server Type    : MYSQL
Target Server Version : 50720
File Encoding         : 65001

Date: 2024-04-15 09:22:25
*/

SET FOREIGN_KEY_CHECKS=0;

-- ----------------------------
-- Table structure for request_lis_data
-- ----------------------------
DROP TABLE IF EXISTS `request_lis_data`;
CREATE TABLE `request_lis_data` (
  `pkid` int(11) NOT NULL AUTO_INCREMENT,
  `sample_id` varchar(255) DEFAULT NULL,
  `paper_id` int(11) DEFAULT '0' COMMENT '0为未获取',
  `request_statue` int(11) DEFAULT '0' COMMENT '0,未得到模条编号，1得到膜条编号',
  `paper_pos` int(11) DEFAULT NULL,
  `sample_pos` int(11) DEFAULT NULL,
  PRIMARY KEY (`pkid`)
) ENGINE=InnoDB AUTO_INCREMENT=18 DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of request_lis_data
-- ----------------------------

-- ----------------------------
-- Table structure for tageunit
-- ----------------------------
DROP TABLE IF EXISTS `tageunit`;
CREATE TABLE `tageunit` (
  `ID` int(10) unsigned NOT NULL AUTO_INCREMENT,
  `AgeName` varchar(16) NOT NULL DEFAULT '',
  `orderNo` tinyint(3) unsigned NOT NULL DEFAULT '0',
  PRIMARY KEY (`ID`) USING BTREE,
  UNIQUE KEY `ID_UNIQUE` (`ID`) USING BTREE,
  UNIQUE KEY `Name_UNIQUE` (`AgeName`) USING BTREE
) ENGINE=InnoDB AUTO_INCREMENT=5 DEFAULT CHARSET=utf8 ROW_FORMAT=DYNAMIC COMMENT='年龄单位表。';

-- ----------------------------
-- Records of tageunit
-- ----------------------------
INSERT INTO `tageunit` VALUES ('1', '岁', '1');
INSERT INTO `tageunit` VALUES ('2', '月', '2');
INSERT INTO `tageunit` VALUES ('3', '日', '3');
INSERT INTO `tageunit` VALUES ('4', '小时', '4');

-- ----------------------------
-- Table structure for tbedno
-- ----------------------------
DROP TABLE IF EXISTS `tbedno`;
CREATE TABLE `tbedno` (
  `ID` int(10) unsigned NOT NULL AUTO_INCREMENT,
  `BedNoName` varchar(64) NOT NULL,
  `shortKey` varchar(32) DEFAULT '',
  `remark` varchar(255) DEFAULT '',
  PRIMARY KEY (`ID`) USING BTREE,
  UNIQUE KEY `ID_UNIQUE` (`ID`) USING BTREE,
  UNIQUE KEY `Name_UNIQUE` (`shortKey`) USING BTREE
) ENGINE=InnoDB AUTO_INCREMENT=3 DEFAULT CHARSET=utf8 ROW_FORMAT=DYNAMIC COMMENT='医院科室表。';

-- ----------------------------
-- Records of tbedno
-- ----------------------------
INSERT INTO `tbedno` VALUES ('1', '202bed', '202', '');
INSERT INTO `tbedno` VALUES ('2', '204bed', '203', '');

-- ----------------------------
-- Table structure for tdepartment
-- ----------------------------
DROP TABLE IF EXISTS `tdepartment`;
CREATE TABLE `tdepartment` (
  `ID` int(10) unsigned NOT NULL AUTO_INCREMENT,
  `DepartmentName` varchar(64) NOT NULL,
  `shortKey` varchar(32) DEFAULT '',
  `remark` varchar(255) DEFAULT '',
  PRIMARY KEY (`ID`) USING BTREE,
  UNIQUE KEY `ID_UNIQUE` (`ID`) USING BTREE,
  UNIQUE KEY `Name_UNIQUE` (`shortKey`) USING BTREE
) ENGINE=InnoDB AUTO_INCREMENT=4 DEFAULT CHARSET=utf8 ROW_FORMAT=DYNAMIC COMMENT='医院科室表。';

-- ----------------------------
-- Records of tdepartment
-- ----------------------------
INSERT INTO `tdepartment` VALUES ('1', '内科', 'rk', '');
INSERT INTO `tdepartment` VALUES ('2', '外科', 'wk', '');
INSERT INTO `tdepartment` VALUES ('3', '消化科', 'xhk', '');

-- ----------------------------
-- Table structure for tdiagnosis
-- ----------------------------
DROP TABLE IF EXISTS `tdiagnosis`;
CREATE TABLE `tdiagnosis` (
  `ID` int(10) unsigned NOT NULL AUTO_INCREMENT,
  `StrDiagnosis` text NOT NULL,
  `shortKey` varchar(32) DEFAULT '',
  `remark` varchar(255) DEFAULT NULL,
  PRIMARY KEY (`ID`) USING BTREE,
  UNIQUE KEY `ID_UNIQUE` (`ID`) USING BTREE,
  UNIQUE KEY `Name_UNIQUE` (`shortKey`) USING BTREE
) ENGINE=InnoDB AUTO_INCREMENT=2 DEFAULT CHARSET=utf8 ROW_FORMAT=DYNAMIC COMMENT='医院科室表。';

-- ----------------------------
-- Records of tdiagnosis
-- ----------------------------
INSERT INTO `tdiagnosis` VALUES ('1', '诊断信息测试，诊断信息测试诊断信息测试。', 'zd', '');

-- ----------------------------
-- Table structure for tinstrument_paras_set
-- ----------------------------
DROP TABLE IF EXISTS `tinstrument_paras_set`;
CREATE TABLE `tinstrument_paras_set` (
  `id` int(10) unsigned NOT NULL,
  `paras` varchar(255) DEFAULT '' COMMENT 'id,name,para',
  `preIntFileld1` int(255) DEFAULT '-1',
  `remark` varchar(255) DEFAULT '',
  PRIMARY KEY (`id`) USING BTREE
) ENGINE=InnoDB DEFAULT CHARSET=utf8 ROW_FORMAT=DYNAMIC;

-- ----------------------------
-- Records of tinstrument_paras_set
-- ----------------------------
INSERT INTO `tinstrument_paras_set` VALUES ('1', '[{\"id\":1,\"paraName\":\"外壁清洗时间\",\"para\":1000},{\"id\":2,\"paraName\":\"内壁清洗时间\",\"para\":3000},{\"id\":3,\"paraName\":\"抽废液时间\",\"para\":4500}]', '-1', '样本臂清洗（100ms为1个单位）');
INSERT INTO `tinstrument_paras_set` VALUES ('2', '[{\"id\":1,\"paraName\":\"样本针吸样使能\",\"para\":1},{\"id\":2,\"paraName\":\"样本针吐样使能\",\"para\":1}]', '-1', '');
INSERT INTO `tinstrument_paras_set` VALUES ('3', '[{\"id\":1,\"paraName\":\"system\",\"para\":1000}]', '-1', '');

-- ----------------------------
-- Table structure for titem
-- ----------------------------
DROP TABLE IF EXISTS `titem`;
CREATE TABLE `titem` (
  `ID` int(5) unsigned NOT NULL AUTO_INCREMENT,
  `TestPaperID` int(10) unsigned NOT NULL,
  `itemName` varchar(45) DEFAULT NULL,
  `PositionNo` int(10) unsigned NOT NULL,
  `RulesId` int(255) DEFAULT NULL COMMENT '临界区间：0.2,-,阴性;0.8,-,阴性;1.1,O,灰区;2.5,+,弱阳;4.0,++,阳性;5.6,O,强阳;',
  `position` double NOT NULL DEFAULT '0' COMMENT '与计算点距离 单位毫米',
  `IsNull` int(10) unsigned NOT NULL DEFAULT '0',
  PRIMARY KEY (`ID`) USING BTREE
) ENGINE=InnoDB AUTO_INCREMENT=19686 DEFAULT CHARSET=utf8 ROW_FORMAT=DYNAMIC;

-- ----------------------------
-- Records of titem
-- ----------------------------
INSERT INTO `titem` VALUES ('101', '1', 'Nucleosomes', '1', '1', '18', '0');
INSERT INTO `titem` VALUES ('102', '1', 'dsDNA', '2', '1', '22', '0');
INSERT INTO `titem` VALUES ('103', '1', 'Histones', '3', '1', '26', '0');
INSERT INTO `titem` VALUES ('104', '1', 'SmD1', '4', '1', '30', '0');
INSERT INTO `titem` VALUES ('105', '1', 'U1-snRNP', '5', '1', '34', '0');
INSERT INTO `titem` VALUES ('106', '1', 'SSA/Ro 60 kD', '6', '1', '38', '0');
INSERT INTO `titem` VALUES ('107', '1', 'SSA/Ro 52 kD', '7', '1', '42', '0');
INSERT INTO `titem` VALUES ('108', '1', 'SSB/La', '8', '1', '46', '0');
INSERT INTO `titem` VALUES ('109', '1', 'Scl 70', '9', '1', '50', '0');
INSERT INTO `titem` VALUES ('110', '1', 'CENP-B', '10', '1', '54', '0');
INSERT INTO `titem` VALUES ('111', '1', 'Jo-1', '11', '1', '58', '0');
INSERT INTO `titem` VALUES ('112', '1', 'RPP/P0', '12', '1', '62', '0');
INSERT INTO `titem` VALUES ('201', '2', 'Nucleosomes', '1', '1', '11', '0');
INSERT INTO `titem` VALUES ('202', '2', 'SmD1', '2', '1', '23', '0');
INSERT INTO `titem` VALUES ('203', '2', 'U1-snRNP', '3', '1', '27', '0');
INSERT INTO `titem` VALUES ('204', '2', 'SSA/Ro 60', '4', '1', '31', '0');
INSERT INTO `titem` VALUES ('205', '2', 'SSA/Ro 52', '5', '1', '35', '0');
INSERT INTO `titem` VALUES ('206', '2', 'SSB/La', '6', '1', '39', '0');
INSERT INTO `titem` VALUES ('207', '2', 'Scl 70', '7', '1', '43', '0');
INSERT INTO `titem` VALUES ('208', '2', 'Jo-1', '8', '1', '51', '0');
INSERT INTO `titem` VALUES ('209', '2', 'RPP/P0', '9', '1', '55', '0');
INSERT INTO `titem` VALUES ('301', '3', 'dsDNA', '1', '1', '15.5', '0');
INSERT INTO `titem` VALUES ('302', '3', 'SmD1', '2', '1', '23', '0');
INSERT INTO `titem` VALUES ('303', '3', 'U1-snRNP', '3', '1', '27', '0');
INSERT INTO `titem` VALUES ('304', '3', 'SSA/Ro 60', '4', '1', '31', '0');
INSERT INTO `titem` VALUES ('305', '3', 'SSA/Ro 52', '5', '1', '35', '0');
INSERT INTO `titem` VALUES ('306', '3', 'SSB/La', '6', '1', '39', '0');
INSERT INTO `titem` VALUES ('307', '3', 'Scl 70', '7', '1', '43', '0');
INSERT INTO `titem` VALUES ('308', '3', 'CENP-B', '8', '1', '47', '0');
INSERT INTO `titem` VALUES ('309', '3', 'Jo-1', '9', '1', '51', '0');
INSERT INTO `titem` VALUES ('701', '7', '11', '1', '1', '0', '0');
INSERT INTO `titem` VALUES ('702', '7', '12', '2', '1', '0', '0');
INSERT INTO `titem` VALUES ('703', '7', '13', '3', '1', '0', '0');
INSERT INTO `titem` VALUES ('1301', '13', '5677', '1', '1', '0', '0');
INSERT INTO `titem` VALUES ('1302', '13', '0689', '2', '1', '0', '0');
INSERT INTO `titem` VALUES ('1303', '13', '443', '3', '1', '0', '0');
INSERT INTO `titem` VALUES ('1304', '13', '2245', '4', '1', '0', '0');
INSERT INTO `titem` VALUES ('1305', '13', '76544', '5', '1', '0', '0');
INSERT INTO `titem` VALUES ('1401', '14', '77881123', '1', '1', '0', '0');
INSERT INTO `titem` VALUES ('1402', '14', '445677', '2', '1', '0', '0');
INSERT INTO `titem` VALUES ('1501', '15', '88999', '1', '1', '0', '0');
INSERT INTO `titem` VALUES ('1502', '15', '96633', '2', '1', '0', '0');
INSERT INTO `titem` VALUES ('1601', '16', '11', '1', '1', '0', '0');
INSERT INTO `titem` VALUES ('1602', '16', '12', '2', '1', '0', '0');
INSERT INTO `titem` VALUES ('1603', '16', '13', '3', '1', '0', '0');
INSERT INTO `titem` VALUES ('1701', '17', 'Jo-1', '1', '1', '0', '0');
INSERT INTO `titem` VALUES ('1702', '17', 'Mi-2', '2', '1', '0', '0');
INSERT INTO `titem` VALUES ('1703', '17', 'PM-Scl', '3', '1', '0', '0');
INSERT INTO `titem` VALUES ('1704', '17', 'U1-snRNP', '4', '1', '0', '0');
INSERT INTO `titem` VALUES ('1705', '17', 'Ku', '5', '1', '0', '0');
INSERT INTO `titem` VALUES ('1801', '18', 'AMA M2', '1', '1', '11.5', '0');
INSERT INTO `titem` VALUES ('1802', '18', 'sp100', '2', '1', '15.5', '0');
INSERT INTO `titem` VALUES ('1803', '18', 'LKM1', '3', '1', '19.5', '0');
INSERT INTO `titem` VALUES ('1804', '18', 'gp210', '4', '1', '23.5', '0');
INSERT INTO `titem` VALUES ('1805', '18', 'LC1', '5', '1', '27.5', '0');
INSERT INTO `titem` VALUES ('1806', '18', 'SLA', '6', '1', '31.5', '0');
INSERT INTO `titem` VALUES ('1901', '19', 'dsDNA', '1', '1', '9', '0');
INSERT INTO `titem` VALUES ('1902', '19', 'Nucleosomes', '2', '1', '12', '0');
INSERT INTO `titem` VALUES ('1903', '19', 'Histones', '3', '1', '15', '0');
INSERT INTO `titem` VALUES ('1904', '19', 'SmD1', '4', '1', '18', '0');
INSERT INTO `titem` VALUES ('1905', '19', 'PCNA', '5', '1', '21', '0');
INSERT INTO `titem` VALUES ('1906', '19', 'RPP/P0', '6', '1', '24', '0');
INSERT INTO `titem` VALUES ('1907', '19', 'SSA/Ro 60', '7', '1', '27', '0');
INSERT INTO `titem` VALUES ('1908', '19', 'SSA/Ro 52', '8', '1', '30', '0');
INSERT INTO `titem` VALUES ('1909', '19', 'SSB/La', '9', '1', '33', '0');
INSERT INTO `titem` VALUES ('1910', '19', 'CENP-B', '10', '1', '36', '0');
INSERT INTO `titem` VALUES ('1911', '19', 'Scl 70', '11', '1', '39', '0');
INSERT INTO `titem` VALUES ('1912', '19', 'U1-snRNP', '12', '1', '42', '0');
INSERT INTO `titem` VALUES ('1913', '19', 'AMA M2', '13', '1', '45', '0');
INSERT INTO `titem` VALUES ('1914', '19', 'Jo-1', '14', '1', '48', '0');
INSERT INTO `titem` VALUES ('1915', '19', 'PM-Scl', '15', '1', '51', '0');
INSERT INTO `titem` VALUES ('1916', '19', 'Mi-2', '16', '1', '54', '0');
INSERT INTO `titem` VALUES ('1917', '19', 'Ku', '17', '1', '57', '0');
INSERT INTO `titem` VALUES ('2001', '20', 'PR3', '1', '1', '19', '0');
INSERT INTO `titem` VALUES ('2002', '20', 'MPO', '2', '1', '23', '0');
INSERT INTO `titem` VALUES ('2003', '20', 'GBM', '3', '1', '27', '0');
INSERT INTO `titem` VALUES ('2101', '921', 'GBM', '1', '1', '78.5', '0');
INSERT INTO `titem` VALUES ('2102', '921', 'PR3', '2', '1', '85.5', '0');
INSERT INTO `titem` VALUES ('2103', '921', 'MPO', '3', '1', '92.5', '0');
INSERT INTO `titem` VALUES ('2701', '27', 'OJ', '1', '1', '25.5', '0');
INSERT INTO `titem` VALUES ('2702', '27', 'EJ', '2', '1', '27.5', '0');
INSERT INTO `titem` VALUES ('2703', '27', 'PL-7', '3', '1', '32.5', '0');
INSERT INTO `titem` VALUES ('2704', '27', 'PL-12', '4', '1', '34.5', '0');
INSERT INTO `titem` VALUES ('2705', '27', 'SRP', '5', '1', '39.5', '0');
INSERT INTO `titem` VALUES ('2706', '27', 'PM-Scl75', '6', '1', '41.5', '0');
INSERT INTO `titem` VALUES ('2707', '27', 'PM-Scl100', '7', '1', '47.5', '0');
INSERT INTO `titem` VALUES ('2708', '27', 'Jo-1', '8', '1', '54.5', '0');
INSERT INTO `titem` VALUES ('2709', '27', 'Scl-70', '9', '1', '61.5', '0');
INSERT INTO `titem` VALUES ('2710', '27', 'HMGCR', '10', '1', '67.5', '0');
INSERT INTO `titem` VALUES ('2711', '27', 'Mi-2α', '11', '1', '69.5', '0');
INSERT INTO `titem` VALUES ('2712', '27', 'Ku', '12', '1', '74.5', '0');
INSERT INTO `titem` VALUES ('2713', '27', 'Mi-2β', '13', '1', '76.5', '0');
INSERT INTO `titem` VALUES ('2714', '27', 'HA', '14', '1', '81.5', '0');
INSERT INTO `titem` VALUES ('2715', '27', 'TIF1γ', '15', '1', '83.5', '0');
INSERT INTO `titem` VALUES ('2716', '27', 'MDA5', '16', '1', '88.5', '0');
INSERT INTO `titem` VALUES ('2717', '27', 'NXP2', '17', '1', '90.5', '0');
INSERT INTO `titem` VALUES ('2718', '27', 'SAE1', '18', '1', '95.5', '0');
INSERT INTO `titem` VALUES ('2719', '27', 'SAE-2', '19', '1', '97.5', '0');
INSERT INTO `titem` VALUES ('2720', '27', 'KS', '20', '1', '102.5', '0');
INSERT INTO `titem` VALUES ('2721', '27', 'Zo', '21', '1', '104.5', '0');
INSERT INTO `titem` VALUES ('2722', '27', 'SS-A/ Ro52', '22', '1', '109.5', '0');
INSERT INTO `titem` VALUES ('2723', '27', 'RNA-POL3', '23', '1', '111.5', '0');
INSERT INTO `titem` VALUES ('2724', '27', 'Th/To', '24', '1', '116.5', '0');
INSERT INTO `titem` VALUES ('2725', '27', 'Fibrillarin', '25', '1', '118.5', '0');
INSERT INTO `titem` VALUES ('2801', '28', 'AMA-M2', '1', '1', '26.5', '0');
INSERT INTO `titem` VALUES ('2802', '28', 'P0', '2', '1', '33.5', '0');
INSERT INTO `titem` VALUES ('2803', '28', 'Histones', '3', '1', '40.5', '0');
INSERT INTO `titem` VALUES ('2804', '28', 'Nucleosomes', '4', '1', '46.5', '0');
INSERT INTO `titem` VALUES ('2805', '28', 'dsDNA', '5', '1', '48.5', '0');
INSERT INTO `titem` VALUES ('2806', '28', 'PCNA', '6', '1', '54.5', '0');
INSERT INTO `titem` VALUES ('2807', '28', 'CENP-B', '7', '1', '61.5', '0');
INSERT INTO `titem` VALUES ('2808', '28', 'Jo-1', '8', '1', '68.5', '0');
INSERT INTO `titem` VALUES ('2809', '28', 'PM-Scl', '9', '1', '75.5', '0');
INSERT INTO `titem` VALUES ('2810', '28', 'Scl-70', '10', '1', '82.5', '0');
INSERT INTO `titem` VALUES ('2811', '28', 'SSB', '11', '1', '88.5', '0');
INSERT INTO `titem` VALUES ('2812', '28', 'α-fodrin', '12', '1', '90.5', '0');
INSERT INTO `titem` VALUES ('2813', '28', 'Ro-52', '13', '1', '95.5', '0');
INSERT INTO `titem` VALUES ('2814', '28', 'SS-A/Ro', '14', '1', '97.5', '0');
INSERT INTO `titem` VALUES ('2815', '28', 'Sm', '15', '1', '103.5', '0');
INSERT INTO `titem` VALUES ('2816', '28', 'Sm/RNP', '16', '1', '110.5', '0');
INSERT INTO `titem` VALUES ('2817', '28', 'Ku', '17', '1', '116.5', '0');
INSERT INTO `titem` VALUES ('2818', '28', 'Mi-2', '18', '1', '118.5', '0');
INSERT INTO `titem` VALUES ('2901', '29', 'AMA-M2', '1', '1', '26.5', '0');
INSERT INTO `titem` VALUES ('2902', '29', 'P0', '2', '1', '33.5', '0');
INSERT INTO `titem` VALUES ('2903', '29', 'Histones', '3', '1', '40.5', '0');
INSERT INTO `titem` VALUES ('2904', '29', 'Nucleosomes', '4', '1', '46.5', '0');
INSERT INTO `titem` VALUES ('2905', '29', 'dsDNA', '5', '1', '48.5', '0');
INSERT INTO `titem` VALUES ('2906', '29', 'PCNA', '6', '1', '54.5', '0');
INSERT INTO `titem` VALUES ('2907', '29', 'CENP-B', '7', '1', '61.5', '0');
INSERT INTO `titem` VALUES ('2908', '29', 'Jo-1', '8', '1', '68.5', '0');
INSERT INTO `titem` VALUES ('2909', '29', 'PM-Scl', '9', '1', '75.5', '0');
INSERT INTO `titem` VALUES ('2910', '29', 'Scl-70', '10', '1', '82.5', '0');
INSERT INTO `titem` VALUES ('2911', '29', 'SSB', '11', '1', '88.5', '0');
INSERT INTO `titem` VALUES ('2912', '29', 'Ro-52', '12', '1', '95.5', '0');
INSERT INTO `titem` VALUES ('2913', '29', 'SS-A/Ro', '13', '1', '97.5', '0');
INSERT INTO `titem` VALUES ('2914', '29', 'Sm', '14', '1', '103.5', '0');
INSERT INTO `titem` VALUES ('2915', '29', 'Sm/RNP', '15', '1', '110.5', '0');
INSERT INTO `titem` VALUES ('2916', '29', 'Ku', '16', '1', '116.5', '0');
INSERT INTO `titem` VALUES ('2917', '29', 'Mi-2', '17', '1', '118.5', '0');
INSERT INTO `titem` VALUES ('3001', '30', 'AMA-M2', '1', '1', '26.5', '0');
INSERT INTO `titem` VALUES ('3002', '30', 'P0\n', '2', '1', '33.5', '0');
INSERT INTO `titem` VALUES ('3003', '30', 'Histones\n', '3', '1', '40.5', '0');
INSERT INTO `titem` VALUES ('3004', '30', 'Nucleosomes\n', '4', '1', '46.5', '0');
INSERT INTO `titem` VALUES ('3005', '30', 'dsDNA\n', '5', '1', '48.5', '0');
INSERT INTO `titem` VALUES ('3006', '30', 'PCNA\n', '6', '1', '54.5', '0');
INSERT INTO `titem` VALUES ('3007', '30', 'CENP-B\n', '7', '1', '61.5', '0');
INSERT INTO `titem` VALUES ('3008', '30', 'Jo-1\n', '8', '1', '68.5', '0');
INSERT INTO `titem` VALUES ('3009', '30', 'PM-Scl\n', '9', '1', '75.5', '0');
INSERT INTO `titem` VALUES ('3010', '30', 'Scl-70\n', '10', '1', '82.5', '0');
INSERT INTO `titem` VALUES ('3011', '30', 'SSB\n', '11', '1', '88.5', '0');
INSERT INTO `titem` VALUES ('3012', '30', 'Ro-52\n', '12', '1', '95.5', '0');
INSERT INTO `titem` VALUES ('3013', '30', 'SS-A/Ro\n', '13', '1', '97.5', '0');
INSERT INTO `titem` VALUES ('3014', '30', 'Sm\n', '14', '1', '103.5', '0');
INSERT INTO `titem` VALUES ('3015', '30', 'Sm/RNP\n', '15', '1', '110.5', '0');
INSERT INTO `titem` VALUES ('3101', '31', 'P0', '1', '1', '33.5', '0');
INSERT INTO `titem` VALUES ('3102', '31', 'Histones\n', '2', '1', '40.5', '0');
INSERT INTO `titem` VALUES ('3103', '31', 'Nucleosomes\n', '3', '1', '46.5', '0');
INSERT INTO `titem` VALUES ('3104', '31', 'dsDNA\n', '4', '1', '48.5', '0');
INSERT INTO `titem` VALUES ('3105', '31', 'CENP-B', '5', '1', '61.5', '0');
INSERT INTO `titem` VALUES ('3106', '31', 'Jo-1\n', '6', '1', '68.5', '0');
INSERT INTO `titem` VALUES ('3107', '31', 'Scl-70\n', '7', '1', '82.5', '0');
INSERT INTO `titem` VALUES ('3108', '31', 'SSB\n', '8', '1', '88.5', '0');
INSERT INTO `titem` VALUES ('3109', '31', 'α-fodrin\n', '9', '1', '90.5', '0');
INSERT INTO `titem` VALUES ('3110', '31', 'Ro-52\n', '10', '1', '95.5', '0');
INSERT INTO `titem` VALUES ('3111', '31', 'SS-A/Ro\n', '11', '1', '97.5', '0');
INSERT INTO `titem` VALUES ('3112', '31', 'Sm\n', '12', '1', '103.5', '0');
INSERT INTO `titem` VALUES ('3113', '31', 'Sm/RNP\n', '13', '1', '110.5', '0');
INSERT INTO `titem` VALUES ('3201', '32', 'P0', '1', '1', '33.5', '0');
INSERT INTO `titem` VALUES ('3202', '32', 'Histones\n', '2', '1', '40.5', '0');
INSERT INTO `titem` VALUES ('3203', '32', 'Nucleosomes\n', '3', '1', '46.5', '0');
INSERT INTO `titem` VALUES ('3204', '32', 'dsDNA\n', '4', '1', '48.5', '0');
INSERT INTO `titem` VALUES ('3205', '32', 'CENP-B\n', '5', '1', '61.5', '0');
INSERT INTO `titem` VALUES ('3206', '32', 'Jo-1\n', '6', '1', '68.5', '0');
INSERT INTO `titem` VALUES ('3207', '32', 'Scl-70\n', '7', '1', '82.5', '0');
INSERT INTO `titem` VALUES ('3208', '32', 'SSB\n', '8', '1', '88.5', '0');
INSERT INTO `titem` VALUES ('3209', '32', 'Ro-52\n', '9', '1', '95.5', '0');
INSERT INTO `titem` VALUES ('3210', '32', 'SS-A/Ro\n', '10', '1', '97.5', '0');
INSERT INTO `titem` VALUES ('3211', '32', 'Sm\n', '11', '1', '103.5', '0');
INSERT INTO `titem` VALUES ('3212', '32', 'Sm/RNP\n', '12', '1', '110.5', '0');
INSERT INTO `titem` VALUES ('3301', '33', 'P0', '1', '1', '33.5', '0');
INSERT INTO `titem` VALUES ('3302', '33', 'Nucleosomes\n', '2', '1', '46.5', '0');
INSERT INTO `titem` VALUES ('3303', '33', 'Jo-1\n', '3', '1', '68.5', '0');
INSERT INTO `titem` VALUES ('3304', '33', 'Scl-70\n', '4', '1', '82.5', '0');
INSERT INTO `titem` VALUES ('3305', '33', 'SSB\n', '5', '1', '88.5', '0');
INSERT INTO `titem` VALUES ('3306', '33', 'Ro-52\n', '6', '1', '95.5', '0');
INSERT INTO `titem` VALUES ('3307', '33', 'SS-A/Ro\n', '7', '1', '97.5', '0');
INSERT INTO `titem` VALUES ('3308', '33', 'Sm\n', '8', '1', '103.5', '0');
INSERT INTO `titem` VALUES ('3309', '33', 'Sm/RNP\n', '9', '1', '110.5', '0');
INSERT INTO `titem` VALUES ('3401', '34', 'dsDNA\n', '1', '1', '48.5', '0');
INSERT INTO `titem` VALUES ('3402', '34', 'CENP-B\n', '2', '1', '61.5', '0');
INSERT INTO `titem` VALUES ('3403', '34', 'Jo-1\n', '3', '1', '68.5', '0');
INSERT INTO `titem` VALUES ('3404', '34', 'Scl-70\n', '4', '1', '82.5', '0');
INSERT INTO `titem` VALUES ('3405', '34', 'SSB\n', '5', '1', '88.5', '0');
INSERT INTO `titem` VALUES ('3406', '34', 'Ro-52\n', '6', '1', '95.5', '0');
INSERT INTO `titem` VALUES ('3407', '34', 'SS-A/Ro\n', '7', '1', '97.5', '0');
INSERT INTO `titem` VALUES ('3408', '34', 'Sm\n', '8', '1', '103.5', '0');
INSERT INTO `titem` VALUES ('3409', '34', 'Sm/RNP\n', '9', '1', '110.5', '0');
INSERT INTO `titem` VALUES ('9101', '921', 'dsDNA', '1', '1', '9', '0');
INSERT INTO `titem` VALUES ('9102', '921', 'Nucleosomes', '2', '1', '12', '0');
INSERT INTO `titem` VALUES ('9103', '921', 'Histones', '3', '1', '15', '0');
INSERT INTO `titem` VALUES ('9104', '921', 'SmD1', '4', '1', '18', '0');
INSERT INTO `titem` VALUES ('9105', '921', 'PCNA', '5', '1', '21', '0');
INSERT INTO `titem` VALUES ('9106', '921', 'RPP/P0', '6', '1', '24', '0');
INSERT INTO `titem` VALUES ('9107', '921', 'SSA/Ro 60', '7', '1', '27', '0');
INSERT INTO `titem` VALUES ('9108', '921', 'SSA/Ro 52', '8', '1', '30', '0');
INSERT INTO `titem` VALUES ('9109', '921', 'SSB/La', '9', '1', '33', '0');
INSERT INTO `titem` VALUES ('9110', '921', 'CENP-B', '10', '1', '36', '0');
INSERT INTO `titem` VALUES ('9111', '921', 'Scl 70', '11', '1', '39', '0');
INSERT INTO `titem` VALUES ('9112', '921', 'U1-snRNP', '12', '1', '42', '0');
INSERT INTO `titem` VALUES ('9113', '921', 'AMA M2', '13', '1', '45', '0');
INSERT INTO `titem` VALUES ('9114', '921', 'Jo-1', '14', '1', '48', '0');
INSERT INTO `titem` VALUES ('9115', '921', 'PM-Scl', '15', '1', '51', '0');
INSERT INTO `titem` VALUES ('9116', '921', 'Mi-2', '16', '1', '54', '0');
INSERT INTO `titem` VALUES ('9117', '921', 'Ku', '17', '1', '57', '0');
INSERT INTO `titem` VALUES ('9201', '922', 'dsDNA', '1', '1', '14.5', '0');
INSERT INTO `titem` VALUES ('9202', '922', 'SmD1', '2', '1', '22.5', '0');
INSERT INTO `titem` VALUES ('9203', '922', 'U1-snRNP', '3', '1', '26.5', '0');
INSERT INTO `titem` VALUES ('9204', '922', 'SSA/Ro 60', '4', '1', '30.5', '0');
INSERT INTO `titem` VALUES ('9205', '922', 'SSA/Ro 52', '5', '1', '34.5', '0');
INSERT INTO `titem` VALUES ('9206', '922', 'SSB/La', '6', '1', '38.5', '0');
INSERT INTO `titem` VALUES ('9207', '922', 'Scl 70', '7', '1', '42.5', '0');
INSERT INTO `titem` VALUES ('9208', '922', 'CENP-B', '8', '1', '46.5', '0');
INSERT INTO `titem` VALUES ('9209', '922', 'Jo-1', '9', '1', '50.5', '0');
INSERT INTO `titem` VALUES ('9301', '923', 'Nucleosomes', '1', '1', '10.5', '0');
INSERT INTO `titem` VALUES ('9302', '923', 'SmD1', '2', '1', '22.5', '0');
INSERT INTO `titem` VALUES ('9303', '923', 'U1-snRNP', '3', '1', '26.5', '0');
INSERT INTO `titem` VALUES ('9304', '923', 'SSA/Ro 60', '4', '1', '30.5', '0');
INSERT INTO `titem` VALUES ('9305', '923', 'SSA/Ro 52', '5', '1', '34.5', '0');
INSERT INTO `titem` VALUES ('9306', '923', 'SSB/La', '6', '1', '38.5', '0');
INSERT INTO `titem` VALUES ('9307', '923', 'Scl 70', '7', '1', '42.5', '0');
INSERT INTO `titem` VALUES ('9308', '923', 'Jo-1', '8', '1', '50.5', '0');
INSERT INTO `titem` VALUES ('9309', '923', 'RPP/P0', '9', '1', '54.5', '0');
INSERT INTO `titem` VALUES ('9401', '924', 'Nucleosomes', '1', '1', '17.5', '0');
INSERT INTO `titem` VALUES ('9402', '924', 'dsDNA', '2', '1', '21.5', '0');
INSERT INTO `titem` VALUES ('9403', '924', 'Histones', '3', '1', '25.5', '0');
INSERT INTO `titem` VALUES ('9404', '924', 'SmD1', '4', '1', '29.5', '0');
INSERT INTO `titem` VALUES ('9405', '924', 'U1-snRNP', '5', '1', '33.5', '0');
INSERT INTO `titem` VALUES ('9406', '924', 'SSA/Ro 60 kD', '6', '1', '37.5', '0');
INSERT INTO `titem` VALUES ('9407', '924', 'SSA/Ro 52 kD', '7', '1', '41.5', '0');
INSERT INTO `titem` VALUES ('9408', '924', 'SSB/La', '8', '1', '45.5', '0');
INSERT INTO `titem` VALUES ('9409', '924', 'Scl 70', '9', '1', '49.5', '0');
INSERT INTO `titem` VALUES ('9410', '924', 'CENP-B', '10', '1', '53.5', '0');
INSERT INTO `titem` VALUES ('9411', '924', 'Jo-1', '11', '1', '57.5', '0');
INSERT INTO `titem` VALUES ('9412', '924', 'RPP/P0', '12', '1', '61.5', '0');
INSERT INTO `titem` VALUES ('9501', '925', 'AMA M2', '1', '1', '10.5', '0');
INSERT INTO `titem` VALUES ('9502', '925', 'sp100', '2', '1', '14.5', '0');
INSERT INTO `titem` VALUES ('9503', '925', 'LKM1', '3', '1', '18.5', '0');
INSERT INTO `titem` VALUES ('9504', '925', 'gp210', '4', '1', '22.5', '0');
INSERT INTO `titem` VALUES ('9505', '925', 'LC1', '5', '1', '26.5', '0');
INSERT INTO `titem` VALUES ('9506', '925', 'SLA', '6', '1', '30.5', '0');
INSERT INTO `titem` VALUES ('9601', '926', 'PR3', '1', '1', '19', '0');
INSERT INTO `titem` VALUES ('9602', '926', 'MPO', '2', '1', '23', '0');
INSERT INTO `titem` VALUES ('9603', '926', 'GBM', '3', '1', '27', '0');
INSERT INTO `titem` VALUES ('12101', '21', 'GBM', '1', '2', '78.5', '0');
INSERT INTO `titem` VALUES ('12102', '21', 'PR3', '2', '2', '85.5', '0');
INSERT INTO `titem` VALUES ('12103', '21', 'MPO', '3', '2', '92.5', '0');
INSERT INTO `titem` VALUES ('12701', '27', 'OJ', '1', '2', '25.5', '0');
INSERT INTO `titem` VALUES ('12702', '27', 'EJ', '2', '2', '27.5', '0');
INSERT INTO `titem` VALUES ('12703', '27', 'PL-7', '3', '2', '32.5', '0');
INSERT INTO `titem` VALUES ('12704', '27', 'PL-12', '4', '2', '34.5', '0');
INSERT INTO `titem` VALUES ('12705', '27', 'SRP', '5', '2', '39.5', '0');
INSERT INTO `titem` VALUES ('12706', '27', 'PM-Scl75', '6', '2', '41.5', '0');
INSERT INTO `titem` VALUES ('12707', '27', 'PM-Scl100', '7', '2', '47.5', '0');
INSERT INTO `titem` VALUES ('12708', '27', 'Jo-1', '8', '2', '54.5', '0');
INSERT INTO `titem` VALUES ('12709', '27', 'Scl-70', '9', '2', '61.5', '0');
INSERT INTO `titem` VALUES ('12710', '27', 'HMGCR', '10', '2', '67.5', '0');
INSERT INTO `titem` VALUES ('12711', '27', 'Mi-2α', '11', '2', '69.5', '0');
INSERT INTO `titem` VALUES ('12712', '27', 'Ku', '12', '2', '74.5', '0');
INSERT INTO `titem` VALUES ('12713', '27', 'Mi-2β', '13', '2', '76.5', '0');
INSERT INTO `titem` VALUES ('12714', '27', 'HA', '14', '2', '81.5', '0');
INSERT INTO `titem` VALUES ('12715', '27', 'TIF1γ', '15', '2', '83.5', '0');
INSERT INTO `titem` VALUES ('12716', '27', 'MDA5', '16', '2', '88.5', '0');
INSERT INTO `titem` VALUES ('12717', '27', 'NXP2', '17', '2', '90.5', '0');
INSERT INTO `titem` VALUES ('12718', '27', 'SAE1', '18', '2', '95.5', '0');
INSERT INTO `titem` VALUES ('12719', '27', 'SAE-2', '19', '2', '97.5', '0');
INSERT INTO `titem` VALUES ('12720', '27', 'KS', '20', '2', '102.5', '0');
INSERT INTO `titem` VALUES ('12721', '27', 'Zo', '21', '2', '104.5', '0');
INSERT INTO `titem` VALUES ('12722', '27', 'SS-A/ Ro52', '22', '2', '109.5', '0');
INSERT INTO `titem` VALUES ('12723', '27', 'RNA-POL3', '23', '2', '111.5', '0');
INSERT INTO `titem` VALUES ('12724', '27', 'Th/To', '24', '2', '116.5', '0');
INSERT INTO `titem` VALUES ('12725', '27', 'Fibrillarin', '25', '2', '118.5', '0');
INSERT INTO `titem` VALUES ('12801', '28', 'AMA-M2', '1', '1', '26.5', '0');
INSERT INTO `titem` VALUES ('12802', '28', 'P0', '2', '1', '33.5', '0');
INSERT INTO `titem` VALUES ('12803', '28', 'Histones', '3', '1', '40.5', '0');
INSERT INTO `titem` VALUES ('12804', '28', 'Nucleosomes', '4', '1', '46.5', '0');
INSERT INTO `titem` VALUES ('12805', '28', 'dsDNA', '5', '1', '48.5', '0');
INSERT INTO `titem` VALUES ('12806', '28', 'PCNA', '6', '1', '54.5', '0');
INSERT INTO `titem` VALUES ('12807', '28', 'CENP-B', '7', '1', '61.5', '0');
INSERT INTO `titem` VALUES ('12808', '28', 'Jo-1', '8', '1', '68.5', '0');
INSERT INTO `titem` VALUES ('12809', '28', 'PM-Scl', '9', '1', '75.5', '0');
INSERT INTO `titem` VALUES ('12810', '28', 'Scl-70', '10', '1', '82.5', '0');
INSERT INTO `titem` VALUES ('12811', '28', 'SSB', '11', '1', '88.5', '0');
INSERT INTO `titem` VALUES ('12812', '28', 'α-fodrin', '12', '1', '90.5', '0');
INSERT INTO `titem` VALUES ('12813', '28', 'Ro-52', '13', '1', '95.5', '0');
INSERT INTO `titem` VALUES ('12814', '28', 'SS-A/Ro', '14', '1', '97.5', '0');
INSERT INTO `titem` VALUES ('12815', '28', 'Sm', '15', '1', '103.5', '0');
INSERT INTO `titem` VALUES ('12816', '28', 'Sm/RNP', '16', '1', '110.5', '0');
INSERT INTO `titem` VALUES ('12817', '28', 'Ku', '17', '1', '116.5', '0');
INSERT INTO `titem` VALUES ('12818', '28', 'Mi-2', '18', '1', '118.5', '0');
INSERT INTO `titem` VALUES ('12901', '29', 'AMA-M2', '1', '2', '26.5', '0');
INSERT INTO `titem` VALUES ('12902', '29', 'P0', '2', '2', '33.5', '0');
INSERT INTO `titem` VALUES ('12903', '29', 'Histones', '3', '2', '40.5', '0');
INSERT INTO `titem` VALUES ('12904', '29', 'Nucleosomes', '4', '2', '46.5', '0');
INSERT INTO `titem` VALUES ('12905', '29', 'dsDNA', '5', '2', '48.5', '0');
INSERT INTO `titem` VALUES ('12906', '29', 'PCNA', '6', '2', '54.5', '0');
INSERT INTO `titem` VALUES ('12907', '29', 'CENP-B', '7', '2', '61.5', '0');
INSERT INTO `titem` VALUES ('12908', '29', 'Jo-1', '8', '2', '68.5', '0');
INSERT INTO `titem` VALUES ('12909', '29', 'PM-Scl', '9', '2', '75.5', '0');
INSERT INTO `titem` VALUES ('12910', '29', 'Scl-70', '10', '2', '82.5', '0');
INSERT INTO `titem` VALUES ('12911', '29', 'SSB', '11', '2', '88.5', '0');
INSERT INTO `titem` VALUES ('12912', '29', 'Ro-52', '12', '2', '95.5', '0');
INSERT INTO `titem` VALUES ('12913', '29', 'SS-A/Ro', '13', '2', '97.5', '0');
INSERT INTO `titem` VALUES ('12914', '29', 'Sm', '14', '2', '103.5', '0');
INSERT INTO `titem` VALUES ('12915', '29', 'Sm/RNP', '15', '2', '110.5', '0');
INSERT INTO `titem` VALUES ('12916', '29', 'Ku', '16', '2', '116.5', '0');
INSERT INTO `titem` VALUES ('12917', '29', 'Mi-2', '17', '2', '118.5', '0');
INSERT INTO `titem` VALUES ('13001', '30', 'AMA-M2', '1', '2', '26.5', '0');
INSERT INTO `titem` VALUES ('13002', '30', 'P0', '2', '2', '33.5', '0');
INSERT INTO `titem` VALUES ('13003', '30', 'Histones', '3', '2', '40.5', '0');
INSERT INTO `titem` VALUES ('13004', '30', 'Nucleosomes', '4', '2', '46.5', '0');
INSERT INTO `titem` VALUES ('13005', '30', 'dsDNA', '5', '2', '48.5', '0');
INSERT INTO `titem` VALUES ('13006', '30', 'PCNA', '6', '2', '54.5', '0');
INSERT INTO `titem` VALUES ('13007', '30', 'CENP-B', '7', '2', '61.5', '0');
INSERT INTO `titem` VALUES ('13008', '30', 'Jo-1', '8', '2', '68.5', '0');
INSERT INTO `titem` VALUES ('13009', '30', 'PM-Scl', '9', '2', '75.5', '0');
INSERT INTO `titem` VALUES ('13010', '30', 'Scl-70', '10', '2', '82.5', '0');
INSERT INTO `titem` VALUES ('13011', '30', 'SSB', '11', '2', '88.5', '0');
INSERT INTO `titem` VALUES ('13012', '30', 'Ro-52', '12', '2', '95.5', '0');
INSERT INTO `titem` VALUES ('13013', '30', 'SS-A/Ro', '13', '2', '97.5', '0');
INSERT INTO `titem` VALUES ('13014', '30', 'Sm', '14', '2', '103.5', '0');
INSERT INTO `titem` VALUES ('13015', '30', 'Sm/RNP', '15', '2', '110.5', '0');
INSERT INTO `titem` VALUES ('13101', '31', 'P0', '1', '2', '33.5', '0');
INSERT INTO `titem` VALUES ('13102', '31', 'Histones', '2', '2', '40.5', '0');
INSERT INTO `titem` VALUES ('13103', '31', 'Nucleosomes', '3', '2', '46.5', '0');
INSERT INTO `titem` VALUES ('13104', '31', 'dsDNA', '4', '2', '48.5', '0');
INSERT INTO `titem` VALUES ('13105', '31', 'CENP-B', '5', '2', '61.5', '0');
INSERT INTO `titem` VALUES ('13106', '31', 'Jo-1', '6', '2', '68.5', '0');
INSERT INTO `titem` VALUES ('13107', '31', 'Scl-70', '7', '2', '82.5', '0');
INSERT INTO `titem` VALUES ('13108', '31', 'SSB', '8', '2', '88.5', '0');
INSERT INTO `titem` VALUES ('13109', '31', 'α-fodrin', '9', '2', '90.5', '0');
INSERT INTO `titem` VALUES ('13110', '31', 'Ro-52', '10', '2', '95.5', '0');
INSERT INTO `titem` VALUES ('13111', '31', 'SS-A/Ro', '11', '2', '97.5', '0');
INSERT INTO `titem` VALUES ('13112', '31', 'Sm', '12', '2', '103.5', '0');
INSERT INTO `titem` VALUES ('13113', '31', 'Sm/RNP', '13', '2', '110.5', '0');
INSERT INTO `titem` VALUES ('13201', '32', 'P0', '1', '2', '33.5', '0');
INSERT INTO `titem` VALUES ('13202', '32', 'Histones', '2', '2', '40.5', '0');
INSERT INTO `titem` VALUES ('13203', '32', 'Nucleosomes', '3', '2', '46.5', '0');
INSERT INTO `titem` VALUES ('13204', '32', 'dsDNA', '4', '2', '48.5', '0');
INSERT INTO `titem` VALUES ('13205', '32', 'CENP-B', '5', '2', '61.5', '0');
INSERT INTO `titem` VALUES ('13206', '32', 'Jo-1', '6', '2', '68.5', '0');
INSERT INTO `titem` VALUES ('13207', '32', 'Scl-70', '7', '2', '82.5', '0');
INSERT INTO `titem` VALUES ('13208', '32', 'SSB', '8', '2', '88.5', '0');
INSERT INTO `titem` VALUES ('13209', '32', 'Ro-52', '9', '2', '95.5', '0');
INSERT INTO `titem` VALUES ('13210', '32', 'SS-A/Ro', '10', '2', '97.5', '0');
INSERT INTO `titem` VALUES ('13211', '32', 'Sm', '11', '2', '103.5', '0');
INSERT INTO `titem` VALUES ('13212', '32', 'Sm/RNP', '12', '2', '110.5', '0');
INSERT INTO `titem` VALUES ('13401', '34', 'dsDNA', '1', '2', '48.5', '0');
INSERT INTO `titem` VALUES ('13402', '34', 'CENP-B', '2', '2', '61.5', '0');
INSERT INTO `titem` VALUES ('13403', '34', 'Jo-1', '3', '2', '68.5', '0');
INSERT INTO `titem` VALUES ('13404', '34', 'Scl-70', '4', '2', '82.5', '0');
INSERT INTO `titem` VALUES ('13405', '34', 'SSB', '5', '2', '88.5', '0');
INSERT INTO `titem` VALUES ('13406', '34', 'Ro-52', '6', '2', '95.5', '0');
INSERT INTO `titem` VALUES ('13407', '34', 'SS-A/Ro', '7', '2', '97.5', '0');
INSERT INTO `titem` VALUES ('13408', '34', 'Sm', '8', '2', '103.5', '0');
INSERT INTO `titem` VALUES ('13409', '34', 'Sm/RNP', '9', '2', '110.5', '0');
INSERT INTO `titem` VALUES ('19616', '33', 'P0', '1', '1', '33.5', '0');
INSERT INTO `titem` VALUES ('19617', '33', 'Nucleosomes', '2', '1', '46.5', '0');
INSERT INTO `titem` VALUES ('19618', '33', 'Jo-1', '3', '1', '68.5', '0');
INSERT INTO `titem` VALUES ('19619', '33', 'Scl-70', '4', '1', '82.5', '0');
INSERT INTO `titem` VALUES ('19620', '33', 'SSB', '5', '1', '88.5', '0');
INSERT INTO `titem` VALUES ('19621', '33', 'Ro-52', '6', '1', '95.5', '0');
INSERT INTO `titem` VALUES ('19622', '33', 'SS-A/Ro', '7', '1', '97.5', '0');
INSERT INTO `titem` VALUES ('19623', '33', 'Sm', '8', '1', '103.5', '0');
INSERT INTO `titem` VALUES ('19624', '33', 'Sm/RNP', '9', '1', '110.5', '0');
INSERT INTO `titem` VALUES ('19625', '35', 'Jo-1', '1', '2', '68.5', '0');
INSERT INTO `titem` VALUES ('19626', '35', 'Scl-70', '2', '2', '82.5', '0');
INSERT INTO `titem` VALUES ('19627', '35', 'SSB', '3', '2', '88.5', '0');
INSERT INTO `titem` VALUES ('19628', '35', 'Ro-52', '4', '2', '95.5', '0');
INSERT INTO `titem` VALUES ('19629', '35', 'SS-A/Ro', '5', '2', '97.5', '0');
INSERT INTO `titem` VALUES ('19630', '35', 'Sm', '6', '2', '103.5', '0');
INSERT INTO `titem` VALUES ('19631', '35', 'Sm/RNP', '7', '2', '110.5', '0');
INSERT INTO `titem` VALUES ('19674', '927', 'GAD65', '1', '1', '11.5', '0');
INSERT INTO `titem` VALUES ('19675', '927', 'HU', '2', '1', '15.5', '0');
INSERT INTO `titem` VALUES ('19676', '927', 'YO', '3', '1', '19.5', '0');
INSERT INTO `titem` VALUES ('19677', '927', 'RI', '4', '1', '23.5', '0');
INSERT INTO `titem` VALUES ('19678', '927', 'CV2', '5', '1', '27.5', '0');
INSERT INTO `titem` VALUES ('19679', '927', 'Amp', '6', '1', '31.5', '0');
INSERT INTO `titem` VALUES ('19680', '928', 'GAD65', '1', '1', '11.5', '0');
INSERT INTO `titem` VALUES ('19681', '928', 'HU', '2', '1', '15.5', '0');
INSERT INTO `titem` VALUES ('19682', '928', 'YO', '3', '1', '19.5', '0');
INSERT INTO `titem` VALUES ('19683', '928', 'Ri', '4', '1', '23.5', '0');
INSERT INTO `titem` VALUES ('19684', '928', 'CV2', '5', '1', '27.5', '0');
INSERT INTO `titem` VALUES ('19685', '928', 'Amphiphysin', '6', '1', '31.5', '0');

-- ----------------------------
-- Table structure for tprocess
-- ----------------------------
DROP TABLE IF EXISTS `tprocess`;
CREATE TABLE `tprocess` (
  `id` int(10) unsigned NOT NULL,
  `pName` varchar(255) NOT NULL DEFAULT '',
  `isDefault` tinyint(255) DEFAULT '0',
  `addUser` varchar(255) DEFAULT '',
  `addTime` bigint(20) DEFAULT '0',
  `remark` varchar(511) DEFAULT '',
  PRIMARY KEY (`id`) USING BTREE
) ENGINE=InnoDB DEFAULT CHARSET=utf8 ROW_FORMAT=DYNAMIC;

-- ----------------------------
-- Records of tprocess
-- ----------------------------
INSERT INTO `tprocess` VALUES ('1', '胡曼智造', '1', '', '0', '');

-- ----------------------------
-- Table structure for tprocess_para
-- ----------------------------
DROP TABLE IF EXISTS `tprocess_para`;
CREATE TABLE `tprocess_para` (
  `id` int(11) NOT NULL,
  `companyId` int(11) DEFAULT '0',
  `groupId` int(11) DEFAULT '0',
  `groupName` varchar(255) DEFAULT '',
  `groupNameCode` varchar(255) DEFAULT '',
  `stepName` varchar(255) DEFAULT '',
  `stepNameCode` varchar(255) DEFAULT '',
  `actIndex` int(11) DEFAULT '0',
  `actId` int(11) DEFAULT '0',
  `actName` varchar(255) DEFAULT '',
  `actNameCode` varchar(255) DEFAULT '',
  `paras` varchar(1023) DEFAULT '',
  `isPopWindow` tinyint(255) DEFAULT '0',
  `popWindowDes` varchar(255) DEFAULT '',
  `popWindowDesCode` varchar(255) DEFAULT '',
  PRIMARY KEY (`id`) USING BTREE
) ENGINE=InnoDB DEFAULT CHARSET=utf8 ROW_FORMAT=DYNAMIC;

-- ----------------------------
-- Records of tprocess_para
-- ----------------------------
INSERT INTO `tprocess_para` VALUES ('1', '1', '1', '润湿', 'L1084', '摇床电机初始化', 'L1060', '1', '1', '摇床电机初始化', 'L1060', '[{\"id\":1,\"paraName\":\"初始化延时时间(s)\",\"paraValue\":1000}]', '0', null, null);
INSERT INTO `tprocess_para` VALUES ('2', '1', '1', '润湿', 'L1084', '蠕动泵加液(洗涤缓冲液)', 'L1093', '2', '2', '排废液及蠕动泵加液', 'L1128', '[{\"id\":1,\"paraName\":\"RID\",\"paraValue\":9},{\"id\":2,\"paraName\":\"加液量(ul)\",\"paraValue\":1000},{\"id\":3,\"paraName\":\"排废液(s)\",\"paraValue\":0}]', '0', null, null);
INSERT INTO `tprocess_para` VALUES ('3', '1', '1', '润湿', 'L1084', '摇床震荡孵育', 'L1094', '3', '3', '摇床工作', 'L1129', '[{\"id\":1,\"paraName\":\"摇床速度\",\"paraValue\":2},{\"id\":2,\"paraName\":\"震荡孵育时间(s)\",\"paraValue\":60},{\"id\":3,\"paraName\":\"X轴电机初始化\",\"paraValue\":1}]', '0', null, null);
INSERT INTO `tprocess_para` VALUES ('4', '1', '2', '加样本', 'L1085', '摇床电机初始化', 'L1060', '1', '1', '摇床电机初始化', 'L1060', '[{\"id\":1,\"paraName\":\"初始化延时时间(s)\",\"paraValue\":1000}]', '0', null, null);
INSERT INTO `tprocess_para` VALUES ('5', '1', '2', '加样本', 'L1085', '排废液及蠕动泵加液(稀释缓冲液)', 'L1095', '2', '2', '排废液及蠕动泵加液', 'L1128', '[{\"id\":1,\"paraName\":\"RID\",\"paraValue\":5},{\"id\":2,\"paraName\":\"加液量(ul)\",\"paraValue\":1000},{\"id\":3,\"paraName\":\"排废液(s)\",\"paraValue\":3}]', '0', null, null);
INSERT INTO `tprocess_para` VALUES ('6', '1', '2', '加样本', 'L1085', '回流(稀释缓冲液回流)', 'L1096', '3', '4', '蠕动泵回流', 'L1130', '[{\"id\":1,\"paraName\":\"回流类型\",\"paraValue\":5},{\"id\":2,\"paraName\":\"回流体积\",\"paraValue\":3000}]', '0', null, null);
INSERT INTO `tprocess_para` VALUES ('7', '1', '2', '加样本', 'L1085', '样本臂移液', 'L1008', '4', '5', '样本臂移液', 'L1008', '[{\"id\":1,\"paraName\":\"加样量\",\"paraValue\":10}]', '0', null, null);
INSERT INTO `tprocess_para` VALUES ('8', '1', '2', '加样本', 'L1085', '摇床震荡孵育', 'L1094', '5', '3', '摇床工作', 'L1129', '[{\"id\":1,\"paraName\":\"摇床速度\",\"paraValue\":2},{\"id\":2,\"paraName\":\"震荡孵育时间(s)\",\"paraValue\":1800},{\"id\":3,\"paraName\":\"X轴电机初始化\",\"paraValue\":1}]', '0', null, null);
INSERT INTO `tprocess_para` VALUES ('9', '1', '3', '第一次清洗', 'L1086', '第一次摇床电机初始化', 'L1098', '1', '1', '摇床电机初始化', 'L1060', '[{\"id\":1,\"paraName\":\"初始化延时时间(s)\",\"paraValue\":1000}]', '0', null, null);
INSERT INTO `tprocess_para` VALUES ('10', '1', '3', '第一次清洗', 'L1086', '第一次排废液及蠕动泵加液(洗涤缓冲液)', 'L1099', '2', '2', '排废液及蠕动泵加液', 'L1128', '[{\"id\":1,\"paraName\":\"RID\",\"paraValue\":9},{\"id\":2,\"paraName\":\"加液量(ul)\",\"paraValue\":1500},{\"id\":3,\"paraName\":\"排废液(s)\",\"paraValue\":3}]', '0', null, null);
INSERT INTO `tprocess_para` VALUES ('11', '1', '3', '第一次清洗', 'L1086', '第一次摇床震荡孵育', 'L1100', '3', '3', '摇床工作', 'L1129', '[{\"id\":1,\"paraName\":\"摇床速度\",\"paraValue\":2},{\"id\":2,\"paraName\":\"震荡孵育时间(s)\",\"paraValue\":300},{\"id\":3,\"paraName\":\"X轴电机初始化\",\"paraValue\":1}]', '0', null, null);
INSERT INTO `tprocess_para` VALUES ('12', '1', '3', '第一次清洗', 'L1086', '第二次摇床电机初始化', 'L1101', '4', '1', '摇床电机初始化', 'L1060', '[{\"id\":1,\"paraName\":\"初始化延时时间(s)\",\"paraValue\":1000}]', '0', null, null);
INSERT INTO `tprocess_para` VALUES ('13', '1', '3', '第一次清洗', 'L1086', '第二次排废液及蠕动泵加液(洗涤缓冲液)', 'L1102', '5', '2', '排废液及蠕动泵加液', 'L1128', '[{\"id\":1,\"paraName\":\"RID\",\"paraValue\":9},{\"id\":2,\"paraName\":\"加液量(ul)\",\"paraValue\":1500},{\"id\":3,\"paraName\":\"排废液(s)\",\"paraValue\":3}]', '0', null, null);
INSERT INTO `tprocess_para` VALUES ('14', '1', '3', '第一次清洗', 'L1086', '第二次摇床震荡孵育', 'L1103', '6', '3', '摇床工作', 'L1129', '[{\"id\":1,\"paraName\":\"摇床速度\",\"paraValue\":2},{\"id\":2,\"paraName\":\"震荡孵育时间(s)\",\"paraValue\":300},{\"id\":3,\"paraName\":\"X轴电机初始化\",\"paraValue\":1}]', '0', null, null);
INSERT INTO `tprocess_para` VALUES ('15', '1', '3', '第一次清洗', 'L1086', '第三次摇床电机初始化', 'L1104', '7', '1', '摇床电机初始化', 'L1060', '[{\"id\":1,\"paraName\":\"初始化延时时间(s)\",\"paraValue\":1000}]', '0', null, null);
INSERT INTO `tprocess_para` VALUES ('16', '1', '3', '第一次清洗', 'L1086', '第三次排废液及蠕动泵加液(洗涤缓冲液)', 'L1105', '8', '2', '排废液及蠕动泵加液', 'L1128', '[{\"id\":1,\"paraName\":\"RID\",\"paraValue\":9},{\"id\":2,\"paraName\":\"加液量(ul)\",\"paraValue\":1500},{\"id\":3,\"paraName\":\"排废液(s)\",\"paraValue\":3}]', '0', null, null);
INSERT INTO `tprocess_para` VALUES ('17', '1', '3', '第一次清洗', 'L1086', '第三次摇床震荡孵育', 'L1106', '9', '3', '摇床工作', 'L1129', '[{\"id\":1,\"paraName\":\"摇床速度\",\"paraValue\":2},{\"id\":2,\"paraName\":\"震荡孵育时间(s)\",\"paraValue\":300},{\"id\":3,\"paraName\":\"X轴电机初始化\",\"paraValue\":1}]', '0', null, null);
INSERT INTO `tprocess_para` VALUES ('18', '1', '4', '加酶', 'L1087', '摇床电机初始化', 'L1060', '1', '1', '摇床电机初始化', 'L1060', '[{\"id\":1,\"paraName\":\"初始化延时时间(s)\",\"paraValue\":1000}]', '0', null, null);
INSERT INTO `tprocess_para` VALUES ('19', '1', '4', '加酶', 'L1087', '排废液及蠕动泵加液(结合物)', 'L1107', '2', '2', '排废液及蠕动泵加液', 'L1128', '[{\"id\":1,\"paraName\":\"RID\",\"paraValue\":-1},{\"id\":2,\"paraName\":\"加酶量(ul)\",\"paraValue\":1000},{\"id\":3,\"paraName\":\"排废液(s)\",\"paraValue\":3}]', '0', null, null);
INSERT INTO `tprocess_para` VALUES ('20', '1', '4', '加酶', 'L1087', '回流(结合物)', 'L1108', '3', '4', '蠕动泵回流', 'L1130', '[{\"id\":1,\"paraName\":\"回流\",\"paraValue\":-1},{\"id\":2,\"paraName\":\"回流体积\",\"paraValue\":3000}]', '0', null, null);
INSERT INTO `tprocess_para` VALUES ('21', '1', '4', '加酶', 'L1087', '摇床震荡孵育', 'L1094', '4', '3', '摇床工作', 'L1129', '[{\"id\":1,\"paraName\":\"摇床速度\",\"paraValue\":2},{\"id\":2,\"paraName\":\"震荡孵育时间(s)\",\"paraValue\":1800},{\"id\":3,\"paraName\":\"X轴电机初始化\",\"paraValue\":1}]', '0', null, null);
INSERT INTO `tprocess_para` VALUES ('22', '1', '5', '第二次清洗', 'L1088', '第一次摇床电机初始化', 'L1098', '1', '1', '摇床电机初始化', 'L1060', '[{\"id\":1,\"paraName\":\"初始化延时时间(s)\",\"paraValue\":1000}]', '0', null, null);
INSERT INTO `tprocess_para` VALUES ('23', '1', '5', '第二次清洗', 'L1088', '第一次排废液及蠕动泵加液(洗涤缓冲液)', 'L1099', '2', '2', '排废液及蠕动泵加液', 'L1128', '[{\"id\":1,\"paraName\":\"RID\",\"paraValue\":9},{\"id\":2,\"paraName\":\"加液量(ul)\",\"paraValue\":1500},{\"id\":3,\"paraName\":\"排废液(s)\",\"paraValue\":3}]', '0', null, null);
INSERT INTO `tprocess_para` VALUES ('24', '1', '5', '第二次清洗', 'L1088', '第一次摇床震荡孵育', 'L1100', '3', '3', '摇床工作', 'L1129', '[{\"id\":1,\"paraName\":\"摇床速度\",\"paraValue\":2},{\"id\":2,\"paraName\":\"震荡孵育时间(s)\",\"paraValue\":300},{\"id\":3,\"paraName\":\"X轴电机初始化\",\"paraValue\":1}]', '0', null, null);
INSERT INTO `tprocess_para` VALUES ('25', '1', '5', '第二次清洗', 'L1088', '第二次摇床电机初始化', 'L1101', '4', '1', '摇床电机初始化', 'L1060', '[{\"id\":1,\"paraName\":\"初始化延时时间(s)\",\"paraValue\":1000}]', '0', null, null);
INSERT INTO `tprocess_para` VALUES ('26', '1', '5', '第二次清洗', 'L1088', '第二次排废液及蠕动泵加液(洗涤缓冲液)', 'L1102', '5', '2', '排废液及蠕动泵加液', 'L1128', '[{\"id\":1,\"paraName\":\"RID\",\"paraValue\":9},{\"id\":2,\"paraName\":\"加液量(ul)\",\"paraValue\":1500},{\"id\":3,\"paraName\":\"排废液(s)\",\"paraValue\":3}]', '0', null, null);
INSERT INTO `tprocess_para` VALUES ('27', '1', '5', '第二次清洗', 'L1088', '第二次摇床震荡孵育', 'L1103', '6', '3', '摇床工作', 'L1129', '[{\"id\":1,\"paraName\":\"摇床速度\",\"paraValue\":2},{\"id\":2,\"paraName\":\"震荡孵育时间(s)\",\"paraValue\":300},{\"id\":3,\"paraName\":\"X轴电机初始化\",\"paraValue\":1}]', '0', null, null);
INSERT INTO `tprocess_para` VALUES ('28', '1', '5', '第二次清洗', 'L1088', '第三次摇床电机初始化', 'L1104', '7', '1', '摇床电机初始化', 'L1060', '[{\"id\":1,\"paraName\":\"初始化延时时间(s)\",\"paraValue\":1000}]', '0', null, null);
INSERT INTO `tprocess_para` VALUES ('29', '1', '5', '第二次清洗', 'L1088', '第三次排废液及蠕动泵加液(洗涤缓冲液)', 'L1105', '8', '2', '排废液及蠕动泵加液', 'L1128', '[{\"id\":1,\"paraName\":\"RID\",\"paraValue\":9},{\"id\":2,\"paraName\":\"加液量(ul)\",\"paraValue\":1500},{\"id\":3,\"paraName\":\"排废液(s)\",\"paraValue\":3}]', '0', null, null);
INSERT INTO `tprocess_para` VALUES ('30', '1', '5', '第二次清洗', 'L1088', '第三次回流(洗涤缓冲液)', 'L1109', '9', '4', '蠕动泵回流', 'L1130', '[{\"id\":1,\"paraName\":\"回流\",\"paraValue\":9},{\"id\":2,\"paraName\":\"回流体积\",\"paraValue\":3000}]', '0', null, null);
INSERT INTO `tprocess_para` VALUES ('31', '1', '5', '第二次清洗', 'L1088', '第三次摇床震荡孵育', 'L1106', '10', '3', '摇床工作', 'L1129', '[{\"id\":1,\"paraName\":\"摇床速度\",\"paraValue\":2},{\"id\":2,\"paraName\":\"震荡孵育时间(s)\",\"paraValue\":300},{\"id\":3,\"paraName\":\"X轴电机初始化\",\"paraValue\":1}]', '0', null, null);
INSERT INTO `tprocess_para` VALUES ('32', '1', '6', '加底物', 'L1089', '摇床电机初始化', 'L1060', '1', '1', '摇床电机初始化', 'L1060', '[{\"id\":1,\"paraName\":\"初始化延时时间(s)\",\"paraValue\":1000}]', '0', null, null);
INSERT INTO `tprocess_para` VALUES ('33', '1', '6', '加底物', 'L1089', '排废液及蠕动泵加液(底物液)', 'L1110', '2', '2', '排废液及蠕动泵加液', 'L1128', '[{\"id\":1,\"paraName\":\"RID\",\"paraValue\":6},{\"id\":2,\"paraName\":\"加液量(ul)\",\"paraValue\":1000},{\"id\":3,\"paraName\":\"排废液(s)\",\"paraValue\":3}]', '0', null, null);
INSERT INTO `tprocess_para` VALUES ('34', '1', '6', '加底物', 'L1089', '回流(底物液)', 'L1111', '3', '4', '蠕动泵回流', 'L1130', '[{\"id\":1,\"paraName\":\"回流\",\"paraValue\":6},{\"id\":2,\"paraName\":\"回流体积\",\"paraValue\":3000}]', '0', null, null);
INSERT INTO `tprocess_para` VALUES ('35', '1', '6', '加底物', 'L1089', '摇床震荡孵育', 'L1094', '4', '3', '摇床工作', 'L1129', '[{\"id\":1,\"paraName\":\"摇床速度\",\"paraValue\":2},{\"id\":2,\"paraName\":\"震荡孵育时间(s)\",\"paraValue\":600},{\"id\":3,\"paraName\":\"X轴电机初始化\",\"paraValue\":1}]', '0', null, null);
INSERT INTO `tprocess_para` VALUES ('36', '1', '7', '加蒸馏水', 'L1090', '摇床电机初始化', 'L1060', '1', '1', '摇床电机初始化', 'L1060', '[{\"id\":1,\"paraName\":\"初始化延时时间(s)\",\"paraValue\":1000}]', '0', null, null);
INSERT INTO `tprocess_para` VALUES ('37', '1', '7', '加蒸馏水', 'L1090', '排废液及加入蒸馏水', 'L1112', '2', '2', '排废液及蠕动泵加液', 'L1128', '[{\"id\":1,\"paraName\":\"RID\",\"paraValue\":8},{\"id\":2,\"paraName\":\"加液量(ul)\",\"paraValue\":1000},{\"id\":3,\"paraName\":\"排废液(s)\",\"paraValue\":3}]', '0', null, null);
INSERT INTO `tprocess_para` VALUES ('38', '1', '7', '加蒸馏水', 'L1090', '摇床震荡孵育', 'L1094', '3', '3', '摇床工作', 'L1129', '[{\"id\":1,\"paraName\":\"摇床速度\",\"paraValue\":2},{\"id\":2,\"paraName\":\"震荡孵育时间(s)\",\"paraValue\":60},{\"id\":3,\"paraName\":\"X轴电机初始化\",\"paraValue\":1}]', '0', null, null);
INSERT INTO `tprocess_para` VALUES ('39', '1', '8', '加终止液', 'L1091', '摇床电机初始化', 'L1060', '1', '1', '摇床电机初始化', 'L1060', '[{\"id\":1,\"paraName\":\"初始化延时时间(s)\",\"paraValue\":1000}]', '0', null, null);
INSERT INTO `tprocess_para` VALUES ('40', '1', '8', '加终止液', 'L1091', '排废液及加入中止液STOP', 'L1113', '2', '2', '排废液及蠕动泵加液', 'L1128', '[{\"id\":1,\"paraName\":\"RID\",\"paraValue\":7},{\"id\":2,\"paraName\":\"加液量(ul)\",\"paraValue\":1000},{\"id\":3,\"paraName\":\"排废液(s)\",\"paraValue\":3}]', '0', null, null);
INSERT INTO `tprocess_para` VALUES ('41', '1', '8', '加终止液', 'L1091', '回流(中止液)', 'L1114', '3', '4', '蠕动泵回流', 'L1130', '[{\"id\":1,\"paraName\":\"回流\",\"paraValue\":7},{\"id\":2,\"paraName\":\"回流体积\",\"paraValue\":3000}]', '0', null, null);
INSERT INTO `tprocess_para` VALUES ('42', '1', '8', '加终止液', 'L1091', '摇床震荡孵育', 'L1094', '4', '3', '摇床工作', 'L1129', '[{\"id\":1,\"paraName\":\"摇床速度\",\"paraValue\":2},{\"id\":2,\"paraName\":\"震荡孵育时间(s)\",\"paraValue\":300},{\"id\":3,\"paraName\":\"X轴电机初始化\",\"paraValue\":1}]', '0', null, null);
INSERT INTO `tprocess_para` VALUES ('43', '1', '9', '干燥', 'L1092', '摇床电机初始化', 'L1060', '1', '1', '摇床电机初始化', 'L1060', '[{\"id\":1,\"paraName\":\"初始化延时时间(s)\",\"paraValue\":1000}]', '0', null, null);
INSERT INTO `tprocess_para` VALUES ('44', '1', '9', '干燥', 'L1092', '排废液', 'L1115', '2', '2', '排废液及蠕动泵加液', 'L1128', '[{\"id\":1,\"paraName\":\"RID\",\"paraValue\":7},{\"id\":2,\"paraName\":\"加液量(ul)\",\"paraValue\":0},{\"id\":3,\"paraName\":\"排废液(s)\",\"paraValue\":3}]', '0', null, null);
INSERT INTO `tprocess_para` VALUES ('45', '1', '9', '干燥', 'L1092', '打开加热', 'L1116', '3', '6', '加热', 'L1131', '[{\"id\":1,\"paraName\":\"温控开关(0=关,1=开)\",\"paraValue\":1},{\"id\":2,\"paraName\":\"目标温度\",\"paraValue\":30}]', '0', null, null);
INSERT INTO `tprocess_para` VALUES ('46', '1', '9', '干燥', 'L1092', '摇床震荡+风扇干燥', 'L1117', '4', '7', '摇床震荡+风扇干燥', 'L1117', '[{\"id\":1,\"paraName\":\"时间(s)\",\"paraValue\":900},{\"id\":2,\"paraName\":\"风扇速度\",\"paraValue\":4},{\"id\":3,\"paraName\":\"摇床速度\",\"paraValue\":2},{\"id\":4,\"paraName\":\"风扇时间(s)\",\"paraValue\":5},{\"id\":5,\"paraName\":\"X轴电机初始化\",\"paraValue\":0}]', '0', null, null);
INSERT INTO `tprocess_para` VALUES ('47', '1', '9', '干燥', 'L1092', '关闭加热', 'L1118', '5', '6', '加热', 'L1131', '[{\"id\":1,\"paraName\":\"温控开关(0=关,1=开)\",\"paraValue\":0},{\"id\":2,\"paraName\":\"目标温度\",\"paraValue\":25}]', '0', null, null);
INSERT INTO `tprocess_para` VALUES ('48', '1', '9', '干燥', 'L1092', '摇床震荡+风扇干燥', 'L1117', '6', '7', '摇床震荡+风扇干燥', 'L1117', '[{\"id\":1,\"paraName\":\"时间(s)\",\"paraValue\":900},{\"id\":2,\"paraName\":\"风扇速度\",\"paraValue\":4},{\"id\":3,\"paraName\":\"摇床速度\",\"paraValue\":2},{\"id\":4,\"paraName\":\"风扇时间(s)\",\"paraValue\":5},{\"id\":5,\"paraName\":\"X轴电机初始化\",\"paraValue\":1}]', '0', null, null);
INSERT INTO `tprocess_para` VALUES ('49', '1', '9', '干燥', 'L1092', '摇床电机初始化', 'L1060', '7', '1', '摇床电机初始化', 'L1060', '[{\"id\":1,\"paraName\":\"初始化延时时间(s)\",\"paraValue\":1000}]', '0', null, null);
INSERT INTO `tprocess_para` VALUES ('60', '2', '1', '润湿', 'L1084', '摇床电机初始化', 'L1060', '1', '1', '摇床电机初始化', 'L1060', '[]', '0', null, null);
INSERT INTO `tprocess_para` VALUES ('63', '2', '1', '润湿', 'L1084', '蠕动泵加液(稀释液)', 'L1119', '2', '2', '排废液及蠕动泵加液', 'L1128', '[{\"id\":1,\"paraName\":\"RID\",\"paraValue\":5},{\"id\":2,\"paraName\":\"加液量(ul)\",\"paraValue\":1500},{\"id\":3,\"paraName\":\"排废液(s)\",\"paraValue\":0}]', '0', null, null);
INSERT INTO `tprocess_para` VALUES ('65', '2', '1', '润湿', 'L1084', '摇床震荡孵育', 'L1094', '3', '3', '摇床工作', 'L1129', '[{\"id\":1,\"paraName\":\"摇床速度\",\"paraValue\":2},{\"id\":2,\"paraName\":\"震荡孵育时间(s)\",\"paraValue\":300},{\"id\":3,\"paraName\":\"X轴电机初始化\",\"paraValue\":1}]', '0', null, null);
INSERT INTO `tprocess_para` VALUES ('67', '2', '2', '加样本', 'L1085', '摇床电机初始化', 'L1060', '1', '1', '摇床电机初始化', 'L1060', '[]', '0', null, null);
INSERT INTO `tprocess_para` VALUES ('69', '2', '2', '加样本', 'L1085', '排废液及蠕动泵加液(稀释液)', 'L1120', '2', '2', '排废液及蠕动泵加液', 'L1128', '[{\"id\":1,\"paraName\":\"RID\",\"paraValue\":5},{\"id\":2,\"paraName\":\"加液量(ul)\",\"paraValue\":1500},{\"id\":3,\"paraName\":\"排废液(s)\",\"paraValue\":3}]', '0', null, null);
INSERT INTO `tprocess_para` VALUES ('71', '2', '2', '加样本', 'L1085', '回流(稀释液)', 'L1121', '3', '4', '蠕动泵回流', 'L1130', '[{\"id\":1,\"paraName\":\"RID\",\"paraValue\":5},{\"id\":2,\"paraName\":\"回流体积\",\"paraValue\":3000}]', '0', null, null);
INSERT INTO `tprocess_para` VALUES ('73', '2', '2', '加样本', 'L1085', '样本臂移液', 'L1008', '4', '5', '样本臂移液', 'L1008', '[{\"id\":1,\"paraName\":\"加样量\",\"paraValue\":15}]', '0', null, null);
INSERT INTO `tprocess_para` VALUES ('75', '2', '2', '加样本', 'L1085', '摇床震荡孵育', 'L1094', '5', '3', '摇床工作', 'L1129', '[{\"id\":1,\"paraName\":\"摇床速度\",\"paraValue\":2},{\"id\":2,\"paraName\":\"震荡孵育时间(s)\",\"paraValue\":1800},{\"id\":3,\"paraName\":\"X轴电机初始化\",\"paraValue\":1}]', '0', null, null);
INSERT INTO `tprocess_para` VALUES ('77', '2', '3', '第一次清洗', 'L1086', '第一次摇床电机初始化', 'L1098', '1', '1', '摇床电机初始化', 'L1060', '[]', '0', null, null);
INSERT INTO `tprocess_para` VALUES ('79', '2', '3', '第一次清洗', 'L1086', '第一次排废液及蠕动泵加液(清洗液)', 'L1122', '2', '2', '排废液及蠕动泵加液', 'L1128', '[{\"id\":1,\"paraName\":\"RID\",\"paraValue\":9},{\"id\":2,\"paraName\":\"加液量(ul)\",\"paraValue\":1500},{\"id\":3,\"paraName\":\"排废液(s)\",\"paraValue\":3}]', '0', null, null);
INSERT INTO `tprocess_para` VALUES ('81', '2', '3', '第一次清洗', 'L1086', '第一次摇床震荡孵育', 'L1100', '3', '3', '摇床工作', 'L1129', '[{\"id\":1,\"paraName\":\"摇床速度\",\"paraValue\":2},{\"id\":2,\"paraName\":\"震荡孵育时间(s)\",\"paraValue\":600},{\"id\":3,\"paraName\":\"X轴电机初始化\",\"paraValue\":1}]', '0', null, null);
INSERT INTO `tprocess_para` VALUES ('83', '2', '3', '第一次清洗', 'L1086', '第二次摇床电机初始化', 'L1101', '4', '1', '摇床电机初始化', 'L1060', '[]', '0', null, null);
INSERT INTO `tprocess_para` VALUES ('85', '2', '3', '第一次清洗', 'L1086', '第二次排废液及蠕动泵加液(清洗液)', 'L1123', '5', '2', '排废液及蠕动泵加液', 'L1128', '[{\"id\":1,\"paraName\":\"RID\",\"paraValue\":9},{\"id\":2,\"paraName\":\"加液量(ul)\",\"paraValue\":1500},{\"id\":3,\"paraName\":\"排废液(s)\",\"paraValue\":3}]', '0', null, null);
INSERT INTO `tprocess_para` VALUES ('87', '2', '3', '第一次清洗', 'L1086', '第二次摇床震荡孵育', 'L1103', '6', '3', '摇床工作', 'L1129', '[{\"id\":1,\"paraName\":\"摇床速度\",\"paraValue\":2},{\"id\":2,\"paraName\":\"震荡孵育时间(s)\",\"paraValue\":600},{\"id\":3,\"paraName\":\"X轴电机初始化\",\"paraValue\":1}]', '0', null, null);
INSERT INTO `tprocess_para` VALUES ('89', '2', '3', '第一次清洗', 'L1086', '第三次摇床电机初始化', 'L1104', '7', '1', '摇床电机初始化', 'L1060', '[]', '0', null, null);
INSERT INTO `tprocess_para` VALUES ('91', '2', '3', '第一次清洗', 'L1086', '第三次排废液及蠕动泵加液(清洗液)', 'L1124', '8', '2', '排废液及蠕动泵加液', 'L1128', '[{\"id\":1,\"paraName\":\"RID\",\"paraValue\":9},{\"id\":2,\"paraName\":\"加液量(ul)\",\"paraValue\":1500},{\"id\":3,\"paraName\":\"排废液(s)\",\"paraValue\":3}]', '0', null, null);
INSERT INTO `tprocess_para` VALUES ('93', '2', '3', '第一次清洗', 'L1086', '第三次摇床震荡孵育', 'L1106', '9', '3', '摇床工作', 'L1129', '[{\"id\":1,\"paraName\":\"摇床速度\",\"paraValue\":2},{\"id\":2,\"paraName\":\"震荡孵育时间(s)\",\"paraValue\":600},{\"id\":3,\"paraName\":\"X轴电机初始化\",\"paraValue\":1}]', '0', null, null);
INSERT INTO `tprocess_para` VALUES ('95', '2', '4', '加酶', 'L1087', '摇床电机初始化', 'L1060', '1', '1', '摇床电机初始化', 'L1060', '[]', '0', null, null);
INSERT INTO `tprocess_para` VALUES ('97', '2', '4', '加酶', 'L1087', '排废液及蠕动泵加液(结合物)', 'L1107', '2', '2', '排废液及蠕动泵加液', 'L1128', '[{\"id\":1,\"paraName\":\"RID\",\"paraValue\":-1},{\"id\":2,\"paraName\":\"加酶量(ul)\",\"paraValue\":1500},{\"id\":3,\"paraName\":\"排废液(s)\",\"paraValue\":3}]', '0', null, null);
INSERT INTO `tprocess_para` VALUES ('99', '2', '4', '加酶', 'L1087', '回流(结合物)', 'L1108', '3', '4', '蠕动泵回流', 'L1130', '[{\"id\":1,\"paraName\":\"RID\",\"paraValue\":-1},{\"id\":2,\"paraName\":\"回流体积\",\"paraValue\":3000}]', '0', null, null);
INSERT INTO `tprocess_para` VALUES ('101', '2', '4', '加酶', 'L1087', '摇床震荡孵育', 'L1094', '4', '3', '摇床工作', 'L1129', '[{\"id\":1,\"paraName\":\"摇床速度\",\"paraValue\":2},{\"id\":2,\"paraName\":\"震荡孵育时间(s)\",\"paraValue\":1800},{\"id\":3,\"paraName\":\"X轴电机初始化\",\"paraValue\":1}]', '0', null, null);
INSERT INTO `tprocess_para` VALUES ('103', '2', '5', '第二次清洗', 'L1088', '第一次摇床电机初始化', 'L1098', '1', '1', '摇床电机初始化', 'L1060', '[]', '0', null, null);
INSERT INTO `tprocess_para` VALUES ('105', '2', '5', '第二次清洗', 'L1088', '第一次排废液及蠕动泵加液(清洗液)', 'L1122', '2', '2', '排废液及蠕动泵加液', 'L1128', '[{\"id\":1,\"paraName\":\"RID\",\"paraValue\":9},{\"id\":2,\"paraName\":\"加液量(ul)\",\"paraValue\":1500},{\"id\":3,\"paraName\":\"排废液(s)\",\"paraValue\":3}]', '0', null, null);
INSERT INTO `tprocess_para` VALUES ('107', '2', '5', '第二次清洗', 'L1088', '第一次摇床震荡孵育', 'L1100', '3', '3', '摇床工作', 'L1129', '[{\"id\":1,\"paraName\":\"摇床速度\",\"paraValue\":2},{\"id\":2,\"paraName\":\"震荡孵育时间(s)\",\"paraValue\":600},{\"id\":3,\"paraName\":\"X轴电机初始化\",\"paraValue\":1}]', '0', null, null);
INSERT INTO `tprocess_para` VALUES ('109', '2', '5', '第二次清洗', 'L1088', '第二次摇床电机初始化', 'L1101', '4', '1', '摇床电机初始化', 'L1060', '[]', '0', null, null);
INSERT INTO `tprocess_para` VALUES ('111', '2', '5', '第二次清洗', 'L1088', '第二次排废液及蠕动泵加液(清洗液)', 'L1123', '5', '2', '排废液及蠕动泵加液', 'L1128', '[{\"id\":1,\"paraName\":\"RID\",\"paraValue\":9},{\"id\":2,\"paraName\":\"加液量(ul)\",\"paraValue\":1500},{\"id\":3,\"paraName\":\"排废液(s)\",\"paraValue\":3}]', '0', null, null);
INSERT INTO `tprocess_para` VALUES ('113', '2', '5', '第二次清洗', 'L1088', '第二次摇床震荡孵育', 'L1103', '6', '3', '摇床工作', 'L1129', '[{\"id\":1,\"paraName\":\"摇床速度\",\"paraValue\":2},{\"id\":2,\"paraName\":\"震荡孵育时间(s)\",\"paraValue\":600},{\"id\":3,\"paraName\":\"X轴电机初始化\",\"paraValue\":1}]', '0', null, null);
INSERT INTO `tprocess_para` VALUES ('115', '2', '5', '第二次清洗', 'L1088', '第二次摇床电机初始化', 'L1101', '7', '1', '摇床电机初始化', 'L1060', '[]', '0', null, null);
INSERT INTO `tprocess_para` VALUES ('117', '2', '5', '第二次清洗', 'L1088', '第二次排废液及蠕动泵加液(清洗液)', 'L1123', '8', '2', '排废液及蠕动泵加液', 'L1128', '[{\"id\":1,\"paraName\":\"RID\",\"paraValue\":9},{\"id\":2,\"paraName\":\"加液量(ul)\",\"paraValue\":1500},{\"id\":3,\"paraName\":\"排废液(s)\",\"paraValue\":3}]', '0', null, null);
INSERT INTO `tprocess_para` VALUES ('119', '2', '5', '第二次清洗', 'L1088', '回流(清洗液)', 'L1125', '9', '4', '蠕动泵回流', 'L1130', '[{\"id\":1,\"paraName\":\"RID\",\"paraValue\":9},{\"id\":2,\"paraName\":\"回流体积\",\"paraValue\":3000}]', '0', null, null);
INSERT INTO `tprocess_para` VALUES ('121', '2', '5', '第二次清洗', 'L1088', '第二次摇床震荡孵育', 'L1103', '10', '3', '摇床工作', 'L1129', '[{\"id\":1,\"paraName\":\"摇床速度\",\"paraValue\":2},{\"id\":2,\"paraName\":\"震荡孵育时间(s)\",\"paraValue\":600},{\"id\":3,\"paraName\":\"X轴电机初始化\",\"paraValue\":1}]', '0', null, null);
INSERT INTO `tprocess_para` VALUES ('123', '2', '6', '加底物', 'L1089', '摇床电机初始化', 'L1060', '1', '1', '摇床电机初始化', 'L1060', '[]', '0', null, null);
INSERT INTO `tprocess_para` VALUES ('125', '2', '6', '加底物', 'L1089', '排废液及蠕动泵加液(底物液)', 'L1110', '2', '2', '排废液及蠕动泵加液', 'L1128', '[{\"id\":1,\"paraName\":\"RID\",\"paraValue\":6},{\"id\":2,\"paraName\":\"加液量(ul)\",\"paraValue\":1500},{\"id\":3,\"paraName\":\"排废液(s)\",\"paraValue\":3}]', '0', null, null);
INSERT INTO `tprocess_para` VALUES ('127', '2', '6', '加底物', 'L1089', '回流(底物液)', 'L1111', '3', '4', '蠕动泵回流', 'L1130', '[{\"id\":1,\"paraName\":\"RID\",\"paraValue\":6},{\"id\":2,\"paraName\":\"回流体积\",\"paraValue\":3000}]', '0', null, null);
INSERT INTO `tprocess_para` VALUES ('129', '2', '6', '加底物', 'L1089', '摇床震荡孵育', 'L1094', '4', '3', '摇床工作', 'L1129', '[{\"id\":1,\"paraName\":\"摇床速度\",\"paraValue\":2},{\"id\":2,\"paraName\":\"震荡孵育时间(s)\",\"paraValue\":600},{\"id\":3,\"paraName\":\"X轴电机初始化\",\"paraValue\":1}]', '0', null, null);
INSERT INTO `tprocess_para` VALUES ('131', '2', '7', '加蒸馏水', 'L1090', '摇床电机初始化', 'L1060', '1', '1', '摇床电机初始化', 'L1060', '[]', '0', null, null);
INSERT INTO `tprocess_para` VALUES ('133', '2', '7', '加蒸馏水', 'L1090', '排废液及加入蒸馏水', 'L1112', '2', '2', '排废液及蠕动泵加液', 'L1128', '[{\"id\":1,\"paraName\":\"RID\",\"paraValue\":8},{\"id\":2,\"paraName\":\"加液量(ul)\",\"paraValue\":1500},{\"id\":3,\"paraName\":\"排废液(s)\",\"paraValue\":3}]', '0', null, null);
INSERT INTO `tprocess_para` VALUES ('135', '2', '7', '加蒸馏水', 'L1090', '摇床震荡孵育', 'L1094', '3', '3', '摇床工作', 'L1129', '[{\"id\":1,\"paraName\":\"摇床速度\",\"paraValue\":2},{\"id\":2,\"paraName\":\"震荡孵育时间(s)\",\"paraValue\":60},{\"id\":3,\"paraName\":\"X轴电机初始化\",\"paraValue\":1}]', '0', null, null);
INSERT INTO `tprocess_para` VALUES ('137', '2', '7', '加蒸馏水', 'L1090', '摇床电机初始化', 'L1060', '4', '1', '摇床电机初始化', 'L1060', '[]', '0', null, null);
INSERT INTO `tprocess_para` VALUES ('139', '2', '7', '加蒸馏水', 'L1090', '排废液及加入蒸馏水', 'L1112', '5', '2', '排废液及蠕动泵加液', 'L1128', '[{\"id\":1,\"paraName\":\"RID\",\"paraValue\":8},{\"id\":2,\"paraName\":\"加液量(ul)\",\"paraValue\":1500},{\"id\":3,\"paraName\":\"排废液(s)\",\"paraValue\":3}]', '0', null, null);
INSERT INTO `tprocess_para` VALUES ('141', '2', '7', '加蒸馏水', 'L1090', '摇床震荡孵育', 'L1094', '6', '3', '摇床工作', 'L1129', '[{\"id\":1,\"paraName\":\"摇床速度\",\"paraValue\":2},{\"id\":2,\"paraName\":\"震荡孵育时间(s)\",\"paraValue\":60},{\"id\":3,\"paraName\":\"X轴电机初始化\",\"paraValue\":1}]', '0', null, null);
INSERT INTO `tprocess_para` VALUES ('143', '2', '7', '加蒸馏水', 'L1090', '摇床电机初始化', 'L1060', '7', '1', '摇床电机初始化', 'L1060', '[]', '0', null, null);
INSERT INTO `tprocess_para` VALUES ('145', '2', '7', '加蒸馏水', 'L1090', '排废液及加入蒸馏水', 'L1112', '8', '2', '排废液及蠕动泵加液', 'L1128', '[{\"id\":1,\"paraName\":\"RID\",\"paraValue\":8},{\"id\":2,\"paraName\":\"加液量(ul)\",\"paraValue\":1500},{\"id\":3,\"paraName\":\"排废液(s)\",\"paraValue\":3}]', '0', null, null);
INSERT INTO `tprocess_para` VALUES ('147', '2', '7', '加蒸馏水', 'L1090', '摇床震荡孵育', 'L1094', '9', '3', '摇床工作', 'L1129', '[{\"id\":1,\"paraName\":\"摇床速度\",\"paraValue\":2},{\"id\":2,\"paraName\":\"震荡孵育时间(s)\",\"paraValue\":60},{\"id\":3,\"paraName\":\"X轴电机初始化\",\"paraValue\":1}]', '0', null, null);
INSERT INTO `tprocess_para` VALUES ('149', '2', '9', '干燥', 'L1092', '摇床电机初始化', 'L1060', '1', '1', '摇床电机初始化', 'L1060', '[]', '0', null, null);
INSERT INTO `tprocess_para` VALUES ('150', '2', '9', '干燥', 'L1092', '排废液', 'L1115', '2', '2', '排废液及蠕动泵加液', 'L1128', '[{\"id\":1,\"paraName\":\"RID\",\"paraValue\":8},{\"id\":2,\"paraName\":\"加液量(ul)\",\"paraValue\":0},{\"id\":3,\"paraName\":\"排废液(s)\",\"paraValue\":3}]', '0', null, null);
INSERT INTO `tprocess_para` VALUES ('151', '2', '9', '干燥', 'L1092', '打开加热', 'L1116', '3', '6', '加热', 'L1131', '[{\"id\":1,\"paraName\":\"温控开关\",\"paraValue\":1},{\"id\":2,\"paraName\":\"目标温度\",\"paraValue\":37}]', '0', null, null);
INSERT INTO `tprocess_para` VALUES ('153', '2', '9', '干燥', 'L1092', '摇床震荡及加热+风扇干燥', 'L1127', '4', '7', '摇床震荡及加热+风扇干燥', 'L1127', '[{\"id\":1,\"paraName\":\"时间\",\"paraValue\":1800},{\"id\":2,\"paraName\":\"风扇速度\",\"paraValue\":5},{\"id\":3,\"paraName\":\"摇床速度\",\"paraValue\":2},{\"id\":4,\"paraName\":\"风扇时间(s)\",\"paraValue\":5},{\"id\":5,\"paraName\":\"X轴电机初始化\",\"paraValue\":1}]', '0', null, null);
INSERT INTO `tprocess_para` VALUES ('154', '2', '9', '干燥', 'L1092', '关闭加热', 'L1118', '5', '6', '加热', 'L1131', '[{\"id\":1,\"paraName\":\"温控开关\",\"paraValue\":0},{\"id\":2,\"paraName\":\"目标温度\",\"paraValue\":25}]', '0', null, null);
INSERT INTO `tprocess_para` VALUES ('180', '3', '1', '润湿', 'L1084', '摇床电机初始化', 'L1060', '1', '1', '摇床电机初始化', 'L1060', '[{\"id\":1,\"paraName\":\"初始化延时时间(s)\",\"paraValue\":1000}]', '0', null, null);
INSERT INTO `tprocess_para` VALUES ('181', '3', '1', '润湿', 'L1084', '蠕动泵加液(洗涤缓冲液)', 'L1093', '2', '2', '排废液及蠕动泵加液', 'L1128', '[{\"id\":1,\"paraName\":\"RID\",\"paraValue\":9},{\"id\":2,\"paraName\":\"加液量(ul)\",\"paraValue\":1000},{\"id\":3,\"paraName\":\"排废液(s)\",\"paraValue\":0}]', '0', null, null);
INSERT INTO `tprocess_para` VALUES ('182', '3', '1', '润湿', 'L1084', '摇床震荡孵育', 'L1094', '3', '3', '摇床工作', 'L1129', '[{\"id\":1,\"paraName\":\"摇床速度\",\"paraValue\":2},{\"id\":2,\"paraName\":\"震荡孵育时间(s)\",\"paraValue\":60},{\"id\":3,\"paraName\":\"X轴电机初始化\",\"paraValue\":1}]', '0', null, null);
INSERT INTO `tprocess_para` VALUES ('183', '3', '2', '加样本', 'L1085', '摇床电机初始化', 'L1060', '1', '1', '摇床电机初始化', 'L1060', '[{\"id\":1,\"paraName\":\"初始化延时时间(s)\",\"paraValue\":1000}]', '0', null, null);
INSERT INTO `tprocess_para` VALUES ('184', '3', '2', '加样本', 'L1085', '排废液及蠕动泵加液(稀释缓冲液)', 'L1095', '2', '2', '排废液及蠕动泵加液', 'L1128', '[{\"id\":1,\"paraName\":\"RID\",\"paraValue\":5},{\"id\":2,\"paraName\":\"加液量(ul)\",\"paraValue\":1000},{\"id\":3,\"paraName\":\"排废液(s)\",\"paraValue\":3}]', '0', null, null);
INSERT INTO `tprocess_para` VALUES ('185', '3', '2', '加样本', 'L1085', '回流(稀释缓冲液回流)', 'L1096', '3', '4', '蠕动泵回流', 'L1130', '[{\"id\":1,\"paraName\":\"回流类型\",\"paraValue\":5},{\"id\":2,\"paraName\":\"回流体积\",\"paraValue\":3000}]', '0', null, null);
INSERT INTO `tprocess_para` VALUES ('186', '3', '2', '加样本', 'L1085', '样本臂移液', 'L1008', '4', '5', '样本臂移液', 'L1008', '[{\"id\":1,\"paraName\":\"加样量\",\"paraValue\":10}]', '0', null, null);
INSERT INTO `tprocess_para` VALUES ('187', '3', '2', '加样本', 'L1085', '摇床震荡孵育', 'L1094', '5', '3', '摇床工作', 'L1129', '[{\"id\":1,\"paraName\":\"摇床速度\",\"paraValue\":2},{\"id\":2,\"paraName\":\"震荡孵育时间(s)\",\"paraValue\":60},{\"id\":3,\"paraName\":\"X轴电机初始化\",\"paraValue\":1}]', '0', null, null);
INSERT INTO `tprocess_para` VALUES ('188', '3', '3', '第一次清洗', 'L1086', '第一次摇床电机初始化', 'L1098', '1', '1', '摇床电机初始化', 'L1060', '[{\"id\":1,\"paraName\":\"初始化延时时间(s)\",\"paraValue\":1000}]', '0', null, null);
INSERT INTO `tprocess_para` VALUES ('189', '3', '3', '第一次清洗', 'L1086', '第一次排废液及蠕动泵加液(洗涤缓冲液)', 'L1099', '2', '2', '排废液及蠕动泵加液', 'L1128', '[{\"id\":1,\"paraName\":\"RID\",\"paraValue\":9},{\"id\":2,\"paraName\":\"加液量(ul)\",\"paraValue\":1500},{\"id\":3,\"paraName\":\"排废液(s)\",\"paraValue\":3}]', '0', null, null);
INSERT INTO `tprocess_para` VALUES ('190', '3', '3', '第一次清洗', 'L1086', '第一次摇床震荡孵育', 'L1100', '3', '3', '摇床工作', 'L1129', '[{\"id\":1,\"paraName\":\"摇床速度\",\"paraValue\":2},{\"id\":2,\"paraName\":\"震荡孵育时间(s)\",\"paraValue\":60},{\"id\":3,\"paraName\":\"X轴电机初始化\",\"paraValue\":1}]', '0', null, null);
INSERT INTO `tprocess_para` VALUES ('191', '3', '3', '第一次清洗', 'L1086', '第二次摇床电机初始化', 'L1101', '4', '1', '摇床电机初始化', 'L1060', '[{\"id\":1,\"paraName\":\"初始化延时时间(s)\",\"paraValue\":1000}]', '0', null, null);
INSERT INTO `tprocess_para` VALUES ('192', '3', '3', '第一次清洗', 'L1086', '第二次排废液及蠕动泵加液(洗涤缓冲液)', 'L1102', '5', '2', '排废液及蠕动泵加液', 'L1128', '[{\"id\":1,\"paraName\":\"RID\",\"paraValue\":9},{\"id\":2,\"paraName\":\"加液量(ul)\",\"paraValue\":1500},{\"id\":3,\"paraName\":\"排废液(s)\",\"paraValue\":3}]', '0', null, null);
INSERT INTO `tprocess_para` VALUES ('193', '3', '3', '第一次清洗', 'L1086', '第二次摇床震荡孵育', 'L1103', '6', '3', '摇床工作', 'L1129', '[{\"id\":1,\"paraName\":\"摇床速度\",\"paraValue\":2},{\"id\":2,\"paraName\":\"震荡孵育时间(s)\",\"paraValue\":60},{\"id\":3,\"paraName\":\"X轴电机初始化\",\"paraValue\":1}]', '0', null, null);
INSERT INTO `tprocess_para` VALUES ('194', '3', '3', '第一次清洗', 'L1086', '第三次摇床电机初始化', 'L1104', '7', '1', '摇床电机初始化', 'L1060', '[{\"id\":1,\"paraName\":\"初始化延时时间(s)\",\"paraValue\":1000}]', '0', null, null);
INSERT INTO `tprocess_para` VALUES ('195', '3', '3', '第一次清洗', 'L1086', '第三次排废液及蠕动泵加液(洗涤缓冲液)', 'L1105', '8', '2', '排废液及蠕动泵加液', 'L1128', '[{\"id\":1,\"paraName\":\"RID\",\"paraValue\":9},{\"id\":2,\"paraName\":\"加液量(ul)\",\"paraValue\":1500},{\"id\":3,\"paraName\":\"排废液(s)\",\"paraValue\":3}]', '0', null, null);
INSERT INTO `tprocess_para` VALUES ('196', '3', '3', '第一次清洗', 'L1086', '第三次摇床震荡孵育', 'L1106', '9', '3', '摇床工作', 'L1129', '[{\"id\":1,\"paraName\":\"摇床速度\",\"paraValue\":2},{\"id\":2,\"paraName\":\"震荡孵育时间(s)\",\"paraValue\":60},{\"id\":3,\"paraName\":\"X轴电机初始化\",\"paraValue\":1}]', '0', null, null);
INSERT INTO `tprocess_para` VALUES ('197', '3', '4', '加酶', 'L1087', '摇床电机初始化', 'L1060', '1', '1', '摇床电机初始化', 'L1060', '[{\"id\":1,\"paraName\":\"初始化延时时间(s)\",\"paraValue\":1000}]', '0', null, null);
INSERT INTO `tprocess_para` VALUES ('198', '3', '4', '加酶', 'L1087', '排废液及蠕动泵加液(结合物)', 'L1107', '2', '2', '排废液及蠕动泵加液', 'L1128', '[{\"id\":1,\"paraName\":\"RID\",\"paraValue\":-1},{\"id\":2,\"paraName\":\"加酶量(ul)\",\"paraValue\":1000},{\"id\":3,\"paraName\":\"排废液(s)\",\"paraValue\":3}]', '0', null, null);
INSERT INTO `tprocess_para` VALUES ('199', '3', '4', '加酶', 'L1087', '回流(结合物)', 'L1108', '3', '4', '蠕动泵回流', 'L1130', '[{\"id\":1,\"paraName\":\"回流\",\"paraValue\":-1},{\"id\":2,\"paraName\":\"回流体积\",\"paraValue\":3000}]', '0', null, null);
INSERT INTO `tprocess_para` VALUES ('200', '3', '4', '加酶', 'L1087', '摇床震荡孵育', 'L1094', '4', '3', '摇床工作', 'L1129', '[{\"id\":1,\"paraName\":\"摇床速度\",\"paraValue\":2},{\"id\":2,\"paraName\":\"震荡孵育时间(s)\",\"paraValue\":60},{\"id\":3,\"paraName\":\"X轴电机初始化\",\"paraValue\":1}]', '0', null, null);
INSERT INTO `tprocess_para` VALUES ('201', '3', '5', '第二次清洗', 'L1088', '第一次摇床电机初始化', 'L1098', '1', '1', '摇床电机初始化', 'L1060', '[{\"id\":1,\"paraName\":\"初始化延时时间(s)\",\"paraValue\":1000}]', '0', null, null);
INSERT INTO `tprocess_para` VALUES ('202', '3', '5', '第二次清洗', 'L1088', '第一次排废液及蠕动泵加液(洗涤缓冲液)', 'L1099', '2', '2', '排废液及蠕动泵加液', 'L1128', '[{\"id\":1,\"paraName\":\"RID\",\"paraValue\":9},{\"id\":2,\"paraName\":\"加液量(ul)\",\"paraValue\":1500},{\"id\":3,\"paraName\":\"排废液(s)\",\"paraValue\":3}]', '0', null, null);
INSERT INTO `tprocess_para` VALUES ('203', '3', '5', '第二次清洗', 'L1088', '第一次摇床震荡孵育', 'L1100', '3', '3', '摇床工作', 'L1129', '[{\"id\":1,\"paraName\":\"摇床速度\",\"paraValue\":2},{\"id\":2,\"paraName\":\"震荡孵育时间(s)\",\"paraValue\":60},{\"id\":3,\"paraName\":\"X轴电机初始化\",\"paraValue\":1}]', '0', null, null);
INSERT INTO `tprocess_para` VALUES ('204', '3', '5', '第二次清洗', 'L1088', '第二次摇床电机初始化', 'L1101', '4', '1', '摇床电机初始化', 'L1060', '[{\"id\":1,\"paraName\":\"初始化延时时间(s)\",\"paraValue\":1000}]', '0', null, null);
INSERT INTO `tprocess_para` VALUES ('205', '3', '5', '第二次清洗', 'L1088', '第二次排废液及蠕动泵加液(洗涤缓冲液)', 'L1102', '5', '2', '排废液及蠕动泵加液', 'L1128', '[{\"id\":1,\"paraName\":\"RID\",\"paraValue\":9},{\"id\":2,\"paraName\":\"加液量(ul)\",\"paraValue\":1500},{\"id\":3,\"paraName\":\"排废液(s)\",\"paraValue\":3}]', '0', null, null);
INSERT INTO `tprocess_para` VALUES ('206', '3', '5', '第二次清洗', 'L1088', '第二次摇床震荡孵育', 'L1103', '6', '3', '摇床工作', 'L1129', '[{\"id\":1,\"paraName\":\"摇床速度\",\"paraValue\":2},{\"id\":2,\"paraName\":\"震荡孵育时间(s)\",\"paraValue\":60},{\"id\":3,\"paraName\":\"X轴电机初始化\",\"paraValue\":1}]', '0', null, null);
INSERT INTO `tprocess_para` VALUES ('207', '3', '5', '第二次清洗', 'L1088', '第三次摇床电机初始化', 'L1104', '7', '1', '摇床电机初始化', 'L1060', '[{\"id\":1,\"paraName\":\"初始化延时时间(s)\",\"paraValue\":1000}]', '0', null, null);
INSERT INTO `tprocess_para` VALUES ('208', '3', '5', '第二次清洗', 'L1088', '第三次排废液及蠕动泵加液(洗涤缓冲液)', 'L1105', '8', '2', '排废液及蠕动泵加液', 'L1128', '[{\"id\":1,\"paraName\":\"RID\",\"paraValue\":9},{\"id\":2,\"paraName\":\"加液量(ul)\",\"paraValue\":1500},{\"id\":3,\"paraName\":\"排废液(s)\",\"paraValue\":3}]', '0', null, null);
INSERT INTO `tprocess_para` VALUES ('209', '3', '5', '第二次清洗', 'L1088', '第三次回流(洗涤缓冲液)', 'L1109', '9', '4', '蠕动泵回流', 'L1130', '[{\"id\":1,\"paraName\":\"回流\",\"paraValue\":9},{\"id\":2,\"paraName\":\"回流体积\",\"paraValue\":3000}]', '0', null, null);
INSERT INTO `tprocess_para` VALUES ('210', '3', '5', '第二次清洗', 'L1088', '第三次摇床震荡孵育', 'L1106', '10', '3', '摇床工作', 'L1129', '[{\"id\":1,\"paraName\":\"摇床速度\",\"paraValue\":2},{\"id\":2,\"paraName\":\"震荡孵育时间(s)\",\"paraValue\":60},{\"id\":3,\"paraName\":\"X轴电机初始化\",\"paraValue\":1}]', '0', null, null);
INSERT INTO `tprocess_para` VALUES ('211', '3', '6', '加底物', 'L1089', '摇床电机初始化', 'L1060', '1', '1', '摇床电机初始化', 'L1060', '[{\"id\":1,\"paraName\":\"初始化延时时间(s)\",\"paraValue\":1000}]', '0', null, null);
INSERT INTO `tprocess_para` VALUES ('212', '3', '6', '加底物', 'L1089', '排废液及蠕动泵加液(底物液)', 'L1110', '2', '2', '排废液及蠕动泵加液', 'L1128', '[{\"id\":1,\"paraName\":\"RID\",\"paraValue\":6},{\"id\":2,\"paraName\":\"加液量(ul)\",\"paraValue\":1000},{\"id\":3,\"paraName\":\"排废液(s)\",\"paraValue\":3}]', '0', null, null);
INSERT INTO `tprocess_para` VALUES ('213', '3', '6', '加底物', 'L1089', '回流(底物液)', 'L1111', '3', '4', '蠕动泵回流', 'L1130', '[{\"id\":1,\"paraName\":\"回流\",\"paraValue\":6},{\"id\":2,\"paraName\":\"回流体积\",\"paraValue\":3000}]', '0', null, null);
INSERT INTO `tprocess_para` VALUES ('214', '3', '6', '加底物', 'L1089', '摇床震荡孵育', 'L1094', '4', '3', '摇床工作', 'L1129', '[{\"id\":1,\"paraName\":\"摇床速度\",\"paraValue\":2},{\"id\":2,\"paraName\":\"震荡孵育时间(s)\",\"paraValue\":60},{\"id\":3,\"paraName\":\"X轴电机初始化\",\"paraValue\":1}]', '0', null, null);
INSERT INTO `tprocess_para` VALUES ('215', '3', '7', '加蒸馏水', 'L1090', '摇床电机初始化', 'L1060', '1', '1', '摇床电机初始化', 'L1060', '[{\"id\":1,\"paraName\":\"初始化延时时间(s)\",\"paraValue\":1000}]', '0', null, null);
INSERT INTO `tprocess_para` VALUES ('216', '3', '7', '加蒸馏水', 'L1090', '排废液及加入蒸馏水', 'L1112', '2', '2', '排废液及蠕动泵加液', 'L1128', '[{\"id\":1,\"paraName\":\"RID\",\"paraValue\":8},{\"id\":2,\"paraName\":\"加液量(ul)\",\"paraValue\":1000},{\"id\":3,\"paraName\":\"排废液(s)\",\"paraValue\":3}]', '0', null, null);
INSERT INTO `tprocess_para` VALUES ('217', '3', '7', '加蒸馏水', 'L1090', '摇床震荡孵育', 'L1094', '3', '3', '摇床工作', 'L1129', '[{\"id\":1,\"paraName\":\"摇床速度\",\"paraValue\":2},{\"id\":2,\"paraName\":\"震荡孵育时间(s)\",\"paraValue\":60},{\"id\":3,\"paraName\":\"X轴电机初始化\",\"paraValue\":1}]', '0', null, null);
INSERT INTO `tprocess_para` VALUES ('218', '3', '8', '加终止液', 'L1091', '摇床电机初始化', 'L1060', '1', '1', '摇床电机初始化', 'L1060', '[{\"id\":1,\"paraName\":\"初始化延时时间(s)\",\"paraValue\":1000}]', '0', null, null);
INSERT INTO `tprocess_para` VALUES ('219', '3', '8', '加终止液', 'L1091', '排废液及加入中止液STOP', 'L1113', '2', '2', '排废液及蠕动泵加液', 'L1128', '[{\"id\":1,\"paraName\":\"RID\",\"paraValue\":7},{\"id\":2,\"paraName\":\"加液量(ul)\",\"paraValue\":1000},{\"id\":3,\"paraName\":\"排废液(s)\",\"paraValue\":3}]', '0', null, null);
INSERT INTO `tprocess_para` VALUES ('220', '3', '8', '加终止液', 'L1091', '回流(中止液)', 'L1114', '3', '4', '蠕动泵回流', 'L1130', '[{\"id\":1,\"paraName\":\"回流\",\"paraValue\":7},{\"id\":2,\"paraName\":\"回流体积\",\"paraValue\":3000}]', '0', null, null);
INSERT INTO `tprocess_para` VALUES ('221', '3', '8', '加终止液', 'L1091', '摇床震荡孵育', 'L1094', '4', '3', '摇床工作', 'L1129', '[{\"id\":1,\"paraName\":\"摇床速度\",\"paraValue\":2},{\"id\":2,\"paraName\":\"震荡孵育时间(s)\",\"paraValue\":60},{\"id\":3,\"paraName\":\"X轴电机初始化\",\"paraValue\":1}]', '0', null, null);
INSERT INTO `tprocess_para` VALUES ('222', '3', '9', '干燥', 'L1092', '摇床电机初始化', 'L1060', '1', '1', '摇床电机初始化', 'L1060', '[{\"id\":1,\"paraName\":\"初始化延时时间(s)\",\"paraValue\":1000}]', '0', null, null);
INSERT INTO `tprocess_para` VALUES ('223', '3', '9', '干燥', 'L1092', '排废液', 'L1115', '2', '2', '排废液及蠕动泵加液', 'L1128', '[{\"id\":1,\"paraName\":\"RID\",\"paraValue\":7},{\"id\":2,\"paraName\":\"加液量(ul)\",\"paraValue\":0},{\"id\":3,\"paraName\":\"排废液(s)\",\"paraValue\":3}]', '0', null, null);
INSERT INTO `tprocess_para` VALUES ('224', '3', '9', '干燥', 'L1092', '打开加热', 'L1116', '3', '6', '加热', 'L1131', '[{\"id\":1,\"paraName\":\"温控开关(0=关,1=开)\",\"paraValue\":1},{\"id\":2,\"paraName\":\"目标温度\",\"paraValue\":30}]', '0', null, null);
INSERT INTO `tprocess_para` VALUES ('225', '3', '9', '干燥', 'L1092', '摇床震荡+风扇干燥', 'L1117', '4', '7', '摇床震荡+风扇干燥', 'L1117', '[{\"id\":1,\"paraName\":\"时间(s)\",\"paraValue\":60},{\"id\":2,\"paraName\":\"风扇速度\",\"paraValue\":4},{\"id\":3,\"paraName\":\"摇床速度\",\"paraValue\":2},{\"id\":4,\"paraName\":\"风扇时间(s)\",\"paraValue\":5},{\"id\":5,\"paraName\":\"X轴电机初始化\",\"paraValue\":0}]', '0', null, null);
INSERT INTO `tprocess_para` VALUES ('226', '3', '9', '干燥', 'L1092', '关闭加热', 'L1118', '5', '6', '加热', 'L1131', '[{\"id\":1,\"paraName\":\"温控开关(0=关,1=开)\",\"paraValue\":0},{\"id\":2,\"paraName\":\"目标温度\",\"paraValue\":25}]', '0', null, null);
INSERT INTO `tprocess_para` VALUES ('227', '3', '9', '干燥', 'L1092', '摇床震荡+风扇干燥', 'L1117', '6', '7', '摇床震荡+风扇干燥', 'L1117', '[{\"id\":1,\"paraName\":\"时间(s)\",\"paraValue\":60},{\"id\":2,\"paraName\":\"风扇速度\",\"paraValue\":4},{\"id\":3,\"paraName\":\"摇床速度\",\"paraValue\":2},{\"id\":4,\"paraName\":\"风扇时间(s)\",\"paraValue\":5},{\"id\":5,\"paraName\":\"X轴电机初始化\",\"paraValue\":1}]', '0', null, null);
INSERT INTO `tprocess_para` VALUES ('228', '3', '9', '干燥', 'L1092', '摇床电机初始化', 'L1060', '7', '1', '摇床电机初始化', 'L1060', '[{\"id\":1,\"paraName\":\"初始化延时时间(s)\",\"paraValue\":1000}]', '0', null, null);
INSERT INTO `tprocess_para` VALUES ('258', '4', '2', '加样本', 'L1085', '摇床电机初始化', 'L1060', '1', '1', '摇床电机初始化', 'L1060', '[{\"id\":1,\"paraName\":\"初始化延时时间(s)\",\"paraValue\":1000}]', '0', null, null);
INSERT INTO `tprocess_para` VALUES ('261', '4', '2', '加样本', 'L1085', '排废液及蠕动泵加液(稀释缓冲液)', 'L1095', '2', '2', '排废液及蠕动泵加液', 'L1128', '[{\"id\":1,\"paraName\":\"RID\",\"paraValue\":5},{\"id\":2,\"paraName\":\"加液量(ul)\",\"paraValue\":1000},{\"id\":3,\"paraName\":\"排废液(s)\",\"paraValue\":3}]', '0', null, null);
INSERT INTO `tprocess_para` VALUES ('264', '4', '2', '加样本', 'L1085', '回流(稀释缓冲液回流)', 'L1096', '3', '4', '蠕动泵回流', 'L1130', '[{\"id\":1,\"paraName\":\"回流类型\",\"paraValue\":5},{\"id\":2,\"paraName\":\"回流体积\",\"paraValue\":3000}]', '0', null, null);
INSERT INTO `tprocess_para` VALUES ('267', '4', '2', '加样本', 'L1085', '样本臂移液', 'L1008', '4', '5', '样本臂移液', 'L1008', '[{\"id\":1,\"paraName\":\"加样量(ul)\",\"paraValue\":5}]', '0', null, null);
INSERT INTO `tprocess_para` VALUES ('270', '4', '2', '加样本', 'L1085', '摇床震荡孵育', 'L1094', '5', '3', '摇床工作', 'L1129', '[{\"id\":1,\"paraName\":\"摇床速度\",\"paraValue\":2},{\"id\":2,\"paraName\":\"震荡孵育时间(s)\",\"paraValue\":1800},{\"id\":3,\"paraName\":\"X轴电机初始化\",\"paraValue\":1}]', '0', null, null);
INSERT INTO `tprocess_para` VALUES ('273', '4', '3', '第一次清洗', 'L1086', '第一次摇床电机初始化', 'L1098', '1', '1', '摇床电机初始化', 'L1060', '[{\"id\":1,\"paraName\":\"初始化延时时间(s)\",\"paraValue\":1000}]', '0', null, null);
INSERT INTO `tprocess_para` VALUES ('276', '4', '3', '第一次清洗', 'L1086', '第一次排废液及蠕动泵加液(洗涤缓冲液)', 'L1099', '2', '2', '排废液及蠕动泵加液', 'L1128', '[{\"id\":1,\"paraName\":\"RID\",\"paraValue\":9},{\"id\":2,\"paraName\":\"加液量(ul)\",\"paraValue\":1000},{\"id\":3,\"paraName\":\"排废液(s)\",\"paraValue\":3}]', '0', null, null);
INSERT INTO `tprocess_para` VALUES ('279', '4', '3', '第一次清洗', 'L1086', '第一次摇床震荡孵育', 'L1100', '3', '3', '摇床工作', 'L1129', '[{\"id\":1,\"paraName\":\"摇床速度\",\"paraValue\":2},{\"id\":2,\"paraName\":\"震荡孵育时间(s)\",\"paraValue\":30},{\"id\":3,\"paraName\":\"X轴电机初始化\",\"paraValue\":1}]', '0', null, null);
INSERT INTO `tprocess_para` VALUES ('282', '4', '3', '第一次清洗', 'L1086', '第二次摇床电机初始化', 'L1101', '4', '1', '摇床电机初始化', 'L1060', '[{\"id\":1,\"paraName\":\"初始化延时时间(s)\",\"paraValue\":1000}]', '0', null, null);
INSERT INTO `tprocess_para` VALUES ('285', '4', '3', '第一次清洗', 'L1086', '第二次排废液及蠕动泵加液(洗涤缓冲液)', 'L1102', '5', '2', '排废液及蠕动泵加液', 'L1128', '[{\"id\":1,\"paraName\":\"RID\",\"paraValue\":9},{\"id\":2,\"paraName\":\"加液量(ul)\",\"paraValue\":1000},{\"id\":3,\"paraName\":\"排废液(s)\",\"paraValue\":3}]', '0', null, null);
INSERT INTO `tprocess_para` VALUES ('288', '4', '3', '第一次清洗', 'L1086', '第二次摇床震荡孵育', 'L1103', '6', '3', '摇床工作', 'L1129', '[{\"id\":1,\"paraName\":\"摇床速度\",\"paraValue\":2},{\"id\":2,\"paraName\":\"震荡孵育时间(s)\",\"paraValue\":30},{\"id\":3,\"paraName\":\"X轴电机初始化\",\"paraValue\":1}]', '0', null, null);
INSERT INTO `tprocess_para` VALUES ('291', '4', '3', '第一次清洗', 'L1086', '第三次摇床电机初始化', 'L1104', '7', '1', '摇床电机初始化', 'L1060', '[{\"id\":1,\"paraName\":\"初始化延时时间(s)\",\"paraValue\":1000}]', '0', null, null);
INSERT INTO `tprocess_para` VALUES ('294', '4', '3', '第一次清洗', 'L1086', '第三次排废液及蠕动泵加液(洗涤缓冲液)', 'L1105', '8', '2', '排废液及蠕动泵加液', 'L1128', '[{\"id\":1,\"paraName\":\"RID\",\"paraValue\":9},{\"id\":2,\"paraName\":\"加液量(ul)\",\"paraValue\":1000},{\"id\":3,\"paraName\":\"排废液(s)\",\"paraValue\":3}]', '0', null, null);
INSERT INTO `tprocess_para` VALUES ('297', '4', '3', '第一次清洗', 'L1086', '第三次摇床震荡孵育', 'L1106', '9', '3', '摇床工作', 'L1129', '[{\"id\":1,\"paraName\":\"摇床速度\",\"paraValue\":2},{\"id\":2,\"paraName\":\"震荡孵育时间(s)\",\"paraValue\":30},{\"id\":3,\"paraName\":\"X轴电机初始化\",\"paraValue\":1}]', '0', null, null);
INSERT INTO `tprocess_para` VALUES ('300', '4', '3', '第一次清洗', 'L1086', '第四次摇床电机初始化', 'L1132', '10', '1', '摇床电机初始化', 'L1060', '[{\"id\":1,\"paraName\":\"初始化延时时间(s)\",\"paraValue\":1000}]', '0', null, null);
INSERT INTO `tprocess_para` VALUES ('303', '4', '3', '第一次清洗', 'L1086', '第四次排废液及蠕动泵加液(洗涤缓冲液)', 'L1133', '11', '2', '排废液及蠕动泵加液', 'L1128', '[{\"id\":1,\"paraName\":\"RID\",\"paraValue\":9},{\"id\":2,\"paraName\":\"加液量(ul)\",\"paraValue\":1000},{\"id\":3,\"paraName\":\"排废液(s)\",\"paraValue\":3}]', '0', null, null);
INSERT INTO `tprocess_para` VALUES ('306', '4', '3', '第一次清洗', 'L1086', '第四次摇床震荡孵育', 'L1134', '12', '3', '摇床工作', 'L1129', '[{\"id\":1,\"paraName\":\"摇床速度\",\"paraValue\":2},{\"id\":2,\"paraName\":\"震荡孵育时间(s)\",\"paraValue\":30},{\"id\":3,\"paraName\":\"X轴电机初始化\",\"paraValue\":1}]', '0', null, null);
INSERT INTO `tprocess_para` VALUES ('309', '4', '3', '第一次清洗', 'L1086', '第五次摇床电机初始化', 'L1135', '13', '1', '摇床电机初始化', 'L1060', '[{\"id\":1,\"paraName\":\"初始化延时时间(s)\",\"paraValue\":1000}]', '0', null, null);
INSERT INTO `tprocess_para` VALUES ('312', '4', '3', '第一次清洗', 'L1086', '第五次排废液及蠕动泵加液(洗涤缓冲液)', 'L1136', '14', '2', '排废液及蠕动泵加液', 'L1128', '[{\"id\":1,\"paraName\":\"RID\",\"paraValue\":9},{\"id\":2,\"paraName\":\"加液量(ul)\",\"paraValue\":1000},{\"id\":3,\"paraName\":\"排废液(s)\",\"paraValue\":3}]', '0', null, null);
INSERT INTO `tprocess_para` VALUES ('315', '4', '3', '第一次清洗', 'L1086', '第五次摇床震荡孵育', 'L1137', '15', '3', '摇床工作', 'L1129', '[{\"id\":1,\"paraName\":\"摇床速度\",\"paraValue\":2},{\"id\":2,\"paraName\":\"震荡孵育时间(s)\",\"paraValue\":30},{\"id\":3,\"paraName\":\"X轴电机初始化\",\"paraValue\":1}]', '0', null, null);
INSERT INTO `tprocess_para` VALUES ('318', '4', '4', '加酶', 'L1087', '摇床电机初始化', 'L1060', '1', '1', '摇床电机初始化', 'L1060', '[{\"id\":1,\"paraName\":\"初始化延时时间(s)\",\"paraValue\":1000}]', '0', null, null);
INSERT INTO `tprocess_para` VALUES ('321', '4', '4', '加酶', 'L1087', '排废液及蠕动泵加液(结合物)', 'L1107', '2', '2', '排废液及蠕动泵加液', 'L1128', '[{\"id\":1,\"paraName\":\"RID\",\"paraValue\":-1},{\"id\":2,\"paraName\":\"加酶量(ul)\",\"paraValue\":1000},{\"id\":3,\"paraName\":\"排废液(s)\",\"paraValue\":3}]', '0', null, null);
INSERT INTO `tprocess_para` VALUES ('324', '4', '4', '加酶', 'L1087', '回流(结合物)', 'L1108', '3', '4', '蠕动泵回流', 'L1130', '[{\"id\":1,\"paraName\":\"回流\",\"paraValue\":-1},{\"id\":2,\"paraName\":\"回流体积\",\"paraValue\":3000}]', '0', null, null);
INSERT INTO `tprocess_para` VALUES ('327', '4', '4', '加酶', 'L1087', '摇床震荡孵育', 'L1094', '4', '3', '摇床工作', 'L1129', '[{\"id\":1,\"paraName\":\"摇床速度\",\"paraValue\":2},{\"id\":2,\"paraName\":\"震荡孵育时间(s)\",\"paraValue\":1800},{\"id\":3,\"paraName\":\"X轴电机初始化\",\"paraValue\":1}]', '0', null, null);
INSERT INTO `tprocess_para` VALUES ('330', '4', '5', '第二次清洗', 'L1088', '第一次摇床电机初始化', 'L1098', '1', '1', '摇床电机初始化', 'L1060', '[{\"id\":1,\"paraName\":\"初始化延时时间(s)\",\"paraValue\":1000}]', '0', null, null);
INSERT INTO `tprocess_para` VALUES ('333', '4', '5', '第二次清洗', 'L1088', '第一次排废液及蠕动泵加液(洗涤缓冲液)', 'L1099', '2', '2', '排废液及蠕动泵加液', 'L1128', '[{\"id\":1,\"paraName\":\"RID\",\"paraValue\":9},{\"id\":2,\"paraName\":\"加液量(ul)\",\"paraValue\":1000},{\"id\":3,\"paraName\":\"排废液(s)\",\"paraValue\":3}]', '0', null, null);
INSERT INTO `tprocess_para` VALUES ('336', '4', '5', '第二次清洗', 'L1088', '第一次摇床震荡孵育', 'L1100', '3', '3', '摇床工作', 'L1129', '[{\"id\":1,\"paraName\":\"摇床速度\",\"paraValue\":2},{\"id\":2,\"paraName\":\"震荡孵育时间(s)\",\"paraValue\":30},{\"id\":3,\"paraName\":\"X轴电机初始化\",\"paraValue\":1}]', '0', null, null);
INSERT INTO `tprocess_para` VALUES ('339', '4', '5', '第二次清洗', 'L1088', '第二次摇床电机初始化', 'L1101', '4', '1', '摇床电机初始化', 'L1060', '[{\"id\":1,\"paraName\":\"初始化延时时间(s)\",\"paraValue\":1000}]', '0', null, null);
INSERT INTO `tprocess_para` VALUES ('342', '4', '5', '第二次清洗', 'L1088', '第二次排废液及蠕动泵加液(洗涤缓冲液)', 'L1102', '5', '2', '排废液及蠕动泵加液', 'L1128', '[{\"id\":1,\"paraName\":\"RID\",\"paraValue\":9},{\"id\":2,\"paraName\":\"加液量(ul)\",\"paraValue\":1000},{\"id\":3,\"paraName\":\"排废液(s)\",\"paraValue\":3}]', '0', null, null);
INSERT INTO `tprocess_para` VALUES ('345', '4', '5', '第二次清洗', 'L1088', '第二次摇床震荡孵育', 'L1103', '6', '3', '摇床工作', 'L1129', '[{\"id\":1,\"paraName\":\"摇床速度\",\"paraValue\":2},{\"id\":2,\"paraName\":\"震荡孵育时间(s)\",\"paraValue\":30},{\"id\":3,\"paraName\":\"X轴电机初始化\",\"paraValue\":1}]', '0', null, null);
INSERT INTO `tprocess_para` VALUES ('348', '4', '5', '第二次清洗', 'L1088', '第三次摇床电机初始化', 'L1104', '7', '1', '摇床电机初始化', 'L1060', '[{\"id\":1,\"paraName\":\"初始化延时时间(s)\",\"paraValue\":1000}]', '0', null, null);
INSERT INTO `tprocess_para` VALUES ('351', '4', '5', '第二次清洗', 'L1088', '第三次排废液及蠕动泵加液(洗涤缓冲液)', 'L1105', '8', '2', '排废液及蠕动泵加液', 'L1128', '[{\"id\":1,\"paraName\":\"RID\",\"paraValue\":9},{\"id\":2,\"paraName\":\"加液量(ul)\",\"paraValue\":1000},{\"id\":3,\"paraName\":\"排废液(s)\",\"paraValue\":3}]', '0', null, null);
INSERT INTO `tprocess_para` VALUES ('354', '4', '5', '第二次清洗', 'L1088', '第三次摇床震荡孵育', 'L1106', '9', '3', '摇床工作', 'L1129', '[{\"id\":1,\"paraName\":\"摇床速度\",\"paraValue\":2},{\"id\":2,\"paraName\":\"震荡孵育时间(s)\",\"paraValue\":30},{\"id\":3,\"paraName\":\"X轴电机初始化\",\"paraValue\":1}]', '0', null, null);
INSERT INTO `tprocess_para` VALUES ('357', '4', '5', '第二次清洗', 'L1088', '第四次摇床电机初始化', 'L1132', '10', '1', '摇床电机初始化', 'L1060', '[{\"id\":1,\"paraName\":\"初始化延时时间(s)\",\"paraValue\":1000}]', '0', null, null);
INSERT INTO `tprocess_para` VALUES ('360', '4', '5', '第二次清洗', 'L1088', '第四次排废液及蠕动泵加液(洗涤缓冲液)', 'L1133', '11', '2', '排废液及蠕动泵加液', 'L1128', '[{\"id\":1,\"paraName\":\"RID\",\"paraValue\":9},{\"id\":2,\"paraName\":\"加液量(ul)\",\"paraValue\":1000},{\"id\":3,\"paraName\":\"排废液(s)\",\"paraValue\":3}]', '0', null, null);
INSERT INTO `tprocess_para` VALUES ('363', '4', '5', '第二次清洗', 'L1088', '第四次摇床震荡孵育', 'L1134', '12', '3', '摇床工作', 'L1129', '[{\"id\":1,\"paraName\":\"摇床速度\",\"paraValue\":2},{\"id\":2,\"paraName\":\"震荡孵育时间(s)\",\"paraValue\":30},{\"id\":3,\"paraName\":\"X轴电机初始化\",\"paraValue\":1}]', '0', null, null);
INSERT INTO `tprocess_para` VALUES ('366', '4', '5', '第二次清洗', 'L1088', '第五次摇床电机初始化', 'L1135', '13', '1', '摇床电机初始化', 'L1060', '[{\"id\":1,\"paraName\":\"初始化延时时间(s)\",\"paraValue\":1000}]', '0', null, null);
INSERT INTO `tprocess_para` VALUES ('369', '4', '5', '第二次清洗', 'L1088', '第五次排废液及蠕动泵加液(洗涤缓冲液)', 'L1136', '14', '2', '排废液及蠕动泵加液', 'L1128', '[{\"id\":1,\"paraName\":\"RID\",\"paraValue\":9},{\"id\":2,\"paraName\":\"加液量(ul)\",\"paraValue\":1000},{\"id\":3,\"paraName\":\"排废液(s)\",\"paraValue\":3}]', '0', null, null);
INSERT INTO `tprocess_para` VALUES ('372', '4', '5', '第二次清洗', 'L1088', '回流(洗涤缓冲液)', 'L1138', '15', '4', '蠕动泵回流', 'L1130', '[{\"id\":1,\"paraName\":\"回流\",\"paraValue\":9},{\"id\":2,\"paraName\":\"回流体积\",\"paraValue\":3000}]', '0', null, null);
INSERT INTO `tprocess_para` VALUES ('375', '4', '5', '第二次清洗', 'L1088', '第五次摇床震荡孵育', 'L1137', '16', '3', '摇床工作', 'L1129', '[{\"id\":1,\"paraName\":\"摇床速度\",\"paraValue\":2},{\"id\":2,\"paraName\":\"震荡孵育时间(s)\",\"paraValue\":30},{\"id\":3,\"paraName\":\"X轴电机初始化\",\"paraValue\":1}]', '0', null, null);
INSERT INTO `tprocess_para` VALUES ('378', '4', '6', '加底物', 'L1089', '摇床电机初始化', 'L1060', '1', '1', '摇床电机初始化', 'L1060', '[{\"id\":1,\"paraName\":\"初始化延时时间(s)\",\"paraValue\":1000}]', '0', null, null);
INSERT INTO `tprocess_para` VALUES ('381', '4', '6', '加底物', 'L1089', '排废液及蠕动泵加液(底物液)', 'L1110', '2', '2', '排废液及蠕动泵加液', 'L1128', '[{\"id\":1,\"paraName\":\"RID\",\"paraValue\":6},{\"id\":2,\"paraName\":\"加液量(ul)\",\"paraValue\":1000},{\"id\":3,\"paraName\":\"排废液(s)\",\"paraValue\":3}]', '0', null, null);
INSERT INTO `tprocess_para` VALUES ('384', '4', '6', '加底物', 'L1089', '回流(底物液)', 'L1111', '3', '4', '蠕动泵回流', 'L1130', '[{\"id\":1,\"paraName\":\"回流\",\"paraValue\":6},{\"id\":2,\"paraName\":\"回流体积\",\"paraValue\":3000}]', '0', null, null);
INSERT INTO `tprocess_para` VALUES ('387', '4', '6', '加底物', 'L1089', '摇床震荡孵育', 'L1094', '4', '3', '摇床工作', 'L1129', '[{\"id\":1,\"paraName\":\"摇床速度\",\"paraValue\":2},{\"id\":2,\"paraName\":\"震荡孵育时间(s)\",\"paraValue\":1200},{\"id\":3,\"paraName\":\"X轴电机初始化\",\"paraValue\":1}]', '0', null, null);
INSERT INTO `tprocess_para` VALUES ('390', '4', '7', '加蒸馏水', 'L1090', '摇床电机初始化', 'L1060', '1', '1', '摇床电机初始化', 'L1060', '[{\"id\":1,\"paraName\":\"初始化延时时间(s)\",\"paraValue\":1000}]', '0', null, null);
INSERT INTO `tprocess_para` VALUES ('393', '4', '7', '加蒸馏水', 'L1090', '排废液及加入蒸馏水', 'L1112', '2', '2', '排废液及蠕动泵加液', 'L1128', '[{\"id\":1,\"paraName\":\"RID\",\"paraValue\":8},{\"id\":2,\"paraName\":\"加液量(ul)\",\"paraValue\":1000},{\"id\":3,\"paraName\":\"排废液(s)\",\"paraValue\":3}]', '0', null, null);
INSERT INTO `tprocess_para` VALUES ('396', '4', '7', '加蒸馏水', 'L1090', '摇床震荡孵育', 'L1094', '3', '3', '摇床工作', 'L1129', '[{\"id\":1,\"paraName\":\"摇床速度\",\"paraValue\":2},{\"id\":2,\"paraName\":\"震荡孵育时间(s)\",\"paraValue\":30},{\"id\":3,\"paraName\":\"X轴电机初始化\",\"paraValue\":1}]', '0', null, null);
INSERT INTO `tprocess_para` VALUES ('399', '4', '7', '加蒸馏水', 'L1090', '摇床电机初始化', 'L1060', '4', '1', '摇床电机初始化', 'L1060', '[{\"id\":1,\"paraName\":\"初始化延时时间(s)\",\"paraValue\":1000}]', '0', null, null);
INSERT INTO `tprocess_para` VALUES ('402', '4', '7', '加蒸馏水', 'L1090', '排废液及加入蒸馏水', 'L1112', '5', '2', '排废液及蠕动泵加液', 'L1128', '[{\"id\":1,\"paraName\":\"RID\",\"paraValue\":8},{\"id\":2,\"paraName\":\"加液量(ul)\",\"paraValue\":1000},{\"id\":3,\"paraName\":\"排废液(s)\",\"paraValue\":3}]', '0', null, null);
INSERT INTO `tprocess_para` VALUES ('405', '4', '7', '加蒸馏水', 'L1090', '摇床震荡孵育', 'L1094', '6', '3', '摇床工作', 'L1129', '[{\"id\":1,\"paraName\":\"摇床速度\",\"paraValue\":2},{\"id\":2,\"paraName\":\"震荡孵育时间(s)\",\"paraValue\":30},{\"id\":3,\"paraName\":\"X轴电机初始化\",\"paraValue\":1}]', '0', null, null);
INSERT INTO `tprocess_para` VALUES ('408', '4', '7', '加蒸馏水', 'L1090', '摇床电机初始化', 'L1060', '7', '1', '摇床电机初始化', 'L1060', '[{\"id\":1,\"paraName\":\"初始化延时时间(s)\",\"paraValue\":1000}]', '0', null, null);
INSERT INTO `tprocess_para` VALUES ('411', '4', '7', '加蒸馏水', 'L1090', '排废液及加入蒸馏水', 'L1112', '8', '2', '排废液及蠕动泵加液', 'L1128', '[{\"id\":1,\"paraName\":\"RID\",\"paraValue\":8},{\"id\":2,\"paraName\":\"加液量(ul)\",\"paraValue\":1000},{\"id\":3,\"paraName\":\"排废液(s)\",\"paraValue\":3}]', '0', null, null);
INSERT INTO `tprocess_para` VALUES ('414', '4', '7', '加蒸馏水', 'L1090', '摇床震荡孵育', 'L1094', '9', '3', '摇床工作', 'L1129', '[{\"id\":1,\"paraName\":\"摇床速度\",\"paraValue\":2},{\"id\":2,\"paraName\":\"震荡孵育时间(s)\",\"paraValue\":30},{\"id\":3,\"paraName\":\"X轴电机初始化\",\"paraValue\":1}]', '0', null, null);
INSERT INTO `tprocess_para` VALUES ('417', '4', '7', '加蒸馏水', 'L1090', '摇床电机初始化', 'L1060', '10', '1', '摇床电机初始化', 'L1060', '[{\"id\":1,\"paraName\":\"初始化延时时间(s)\",\"paraValue\":1000}]', '0', null, null);
INSERT INTO `tprocess_para` VALUES ('420', '4', '7', '加蒸馏水', 'L1090', '排废液及加入蒸馏水', 'L1112', '11', '2', '排废液及蠕动泵加液', 'L1128', '[{\"id\":1,\"paraName\":\"RID\",\"paraValue\":8},{\"id\":2,\"paraName\":\"加液量(ul)\",\"paraValue\":1000},{\"id\":3,\"paraName\":\"排废液(s)\",\"paraValue\":3}]', '0', null, null);
INSERT INTO `tprocess_para` VALUES ('423', '4', '7', '加蒸馏水', 'L1090', '摇床震荡孵育', 'L1094', '12', '3', '摇床工作', 'L1129', '[{\"id\":1,\"paraName\":\"摇床速度\",\"paraValue\":2},{\"id\":2,\"paraName\":\"震荡孵育时间(s)\",\"paraValue\":30},{\"id\":3,\"paraName\":\"X轴电机初始化\",\"paraValue\":1}]', '0', null, null);
INSERT INTO `tprocess_para` VALUES ('426', '4', '7', '加蒸馏水', 'L1090', '摇床电机初始化', 'L1060', '13', '1', '摇床电机初始化', 'L1060', '[{\"id\":1,\"paraName\":\"初始化延时时间(s)\",\"paraValue\":1000}]', '0', null, null);
INSERT INTO `tprocess_para` VALUES ('429', '4', '7', '加蒸馏水', 'L1090', '排废液及加入蒸馏水', 'L1112', '14', '2', '排废液及蠕动泵加液', 'L1128', '[{\"id\":1,\"paraName\":\"RID\",\"paraValue\":8},{\"id\":2,\"paraName\":\"加液量(ul)\",\"paraValue\":1000},{\"id\":3,\"paraName\":\"排废液(s)\",\"paraValue\":3}]', '0', null, null);
INSERT INTO `tprocess_para` VALUES ('432', '4', '7', '加蒸馏水', 'L1088', '回流(加蒸馏水)', 'L1109', '15', '4', '蠕动泵回流', 'L1130', '[{\"id\":1,\"paraName\":\"回流\",\"paraValue\":8},{\"id\":2,\"paraName\":\"回流体积\",\"paraValue\":3000}]', '0', null, null);
INSERT INTO `tprocess_para` VALUES ('435', '4', '7', '加蒸馏水', 'L1090', '摇床震荡孵育', 'L1094', '15', '3', '摇床工作', 'L1129', '[{\"id\":1,\"paraName\":\"摇床速度\",\"paraValue\":2},{\"id\":2,\"paraName\":\"震荡孵育时间(s)\",\"paraValue\":30},{\"id\":3,\"paraName\":\"X轴电机初始化\",\"paraValue\":1}]', '0', null, null);
INSERT INTO `tprocess_para` VALUES ('438', '4', '9', '干燥', 'L1092', '摇床电机初始化', 'L1060', '1', '1', '摇床电机初始化', 'L1060', '[{\"id\":1,\"paraName\":\"初始化延时时间(s)\",\"paraValue\":1000}]', '0', null, null);
INSERT INTO `tprocess_para` VALUES ('441', '4', '9', '干燥', 'L1092', '排废液', 'L1115', '2', '2', '排废液及蠕动泵加液', 'L1128', '[{\"id\":1,\"paraName\":\"RID\",\"paraValue\":8},{\"id\":2,\"paraName\":\"加液量(ul)\",\"paraValue\":0},{\"id\":3,\"paraName\":\"排废液(s)\",\"paraValue\":3}]', '0', null, null);
INSERT INTO `tprocess_para` VALUES ('444', '4', '9', '干燥', 'L1092', '打开加热', 'L1116', '3', '6', '加热', 'L1131', '[{\"id\":1,\"paraName\":\"温控开关(0=关,1=开)\",\"paraValue\":0},{\"id\":2,\"paraName\":\"目标温度\",\"paraValue\":25}]', '0', null, null);
INSERT INTO `tprocess_para` VALUES ('447', '4', '9', '干燥', 'L1092', '摇床震荡+风扇干燥', 'L1117', '4', '7', '摇床震荡+风扇干燥', 'L1117', '[{\"id\":1,\"paraName\":\"时间(s)\",\"paraValue\":7200},{\"id\":2,\"paraName\":\"风扇速度\",\"paraValue\":0},{\"id\":3,\"paraName\":\"摇床速度\",\"paraValue\":2},{\"id\":4,\"paraName\":\"风扇时间(s)\",\"paraValue\":30},{\"id\":5,\"paraName\":\"X轴电机初始化\",\"paraValue\":1}]', '0', null, null);
INSERT INTO `tprocess_para` VALUES ('450', '4', '9', '干燥', 'L1092', '关闭加热', 'L1118', '5', '6', '加热', 'L1131', '[{\"id\":1,\"paraName\":\"温控开关(0=关,1=开)\",\"paraValue\":0},{\"id\":2,\"paraName\":\"目标温度\",\"paraValue\":25}]', '0', null, null);
INSERT INTO `tprocess_para` VALUES ('453', '4', '9', '干燥', 'L1092', '摇床电机初始化', 'L1060', '6', '1', '摇床电机初始化', 'L1060', '[{\"id\":1,\"paraName\":\"初始化延时时间(s)\",\"paraValue\":1000}]', '0', null, null);
INSERT INTO `tprocess_para` VALUES ('488', '5', '2', '加样本', 'L1085', '摇床电机初始化', 'L1060', '1', '1', '摇床电机初始化', 'L1060', '[{\"id\":1,\"paraName\":\"初始化延时时间(s)\",\"paraValue\":1000}]', '0', null, null);
INSERT INTO `tprocess_para` VALUES ('491', '5', '2', '加样本', 'L1085', '排废液及蠕动泵加液(稀释缓冲液)', 'L1095', '2', '2', '排废液及蠕动泵加液', 'L1128', '[{\"id\":1,\"paraName\":\"RID\",\"paraValue\":5},{\"id\":2,\"paraName\":\"加液量(ul)\",\"paraValue\":750},{\"id\":3,\"paraName\":\"排废液(s)\",\"paraValue\":3}]', '0', null, null);
INSERT INTO `tprocess_para` VALUES ('494', '5', '2', '加样本', 'L1085', '回流(稀释缓冲液回流)', 'L1096', '3', '4', '蠕动泵回流', 'L1130', '[{\"id\":1,\"paraName\":\"回流类型\",\"paraValue\":5},{\"id\":2,\"paraName\":\"回流体积\",\"paraValue\":3000}]', '0', null, null);
INSERT INTO `tprocess_para` VALUES ('497', '5', '2', '加样本', 'L1085', '样本臂移液', 'L1008', '4', '5', '样本臂移液', 'L1008', '[{\"id\":1,\"paraName\":\"加样量(ul)\",\"paraValue\":120}]', '0', null, null);
INSERT INTO `tprocess_para` VALUES ('500', '5', '2', '加样本', 'L1085', '样本臂移液', 'L1008', '5', '5', '样本臂移液', 'L1008', '[{\"id\":1,\"paraName\":\"加样量(ul)\",\"paraValue\":130}]', '0', null, null);
INSERT INTO `tprocess_para` VALUES ('503', '5', '2', '加样本', 'L1085', '摇床震荡孵育', 'L1094', '6', '3', '摇床工作', 'L1129', '[{\"id\":1,\"paraName\":\"摇床速度\",\"paraValue\":2},{\"id\":2,\"paraName\":\"震荡孵育时间(s)\",\"paraValue\":1800},{\"id\":3,\"paraName\":\"X轴电机初始化\",\"paraValue\":1}]', '0', null, null);
INSERT INTO `tprocess_para` VALUES ('506', '5', '3', '第一次清洗', 'L1086', '第一次摇床电机初始化', 'L1098', '1', '1', '摇床电机初始化', 'L1060', '[{\"id\":1,\"paraName\":\"初始化延时时间(s)\",\"paraValue\":1000}]', '0', null, null);
INSERT INTO `tprocess_para` VALUES ('509', '5', '3', '第一次清洗', 'L1086', '第一次排废液及蠕动泵加液(洗涤缓冲液)', 'L1099', '2', '2', '排废液及蠕动泵加液', 'L1128', '[{\"id\":1,\"paraName\":\"RID\",\"paraValue\":9},{\"id\":2,\"paraName\":\"加液量(ul)\",\"paraValue\":1000},{\"id\":3,\"paraName\":\"排废液(s)\",\"paraValue\":3}]', '0', null, null);
INSERT INTO `tprocess_para` VALUES ('512', '5', '3', '第一次清洗', 'L1086', '第一次摇床震荡孵育', 'L1100', '3', '3', '摇床工作', 'L1129', '[{\"id\":1,\"paraName\":\"摇床速度\",\"paraValue\":2},{\"id\":2,\"paraName\":\"震荡孵育时间(s)\",\"paraValue\":30},{\"id\":3,\"paraName\":\"X轴电机初始化\",\"paraValue\":1}]', '0', null, null);
INSERT INTO `tprocess_para` VALUES ('515', '5', '3', '第一次清洗', 'L1086', '第二次摇床电机初始化', 'L1101', '4', '1', '摇床电机初始化', 'L1060', '[{\"id\":1,\"paraName\":\"初始化延时时间(s)\",\"paraValue\":1000}]', '0', null, null);
INSERT INTO `tprocess_para` VALUES ('518', '5', '3', '第一次清洗', 'L1086', '第二次排废液及蠕动泵加液(洗涤缓冲液)', 'L1102', '5', '2', '排废液及蠕动泵加液', 'L1128', '[{\"id\":1,\"paraName\":\"RID\",\"paraValue\":9},{\"id\":2,\"paraName\":\"加液量(ul)\",\"paraValue\":1000},{\"id\":3,\"paraName\":\"排废液(s)\",\"paraValue\":3}]', '0', null, null);
INSERT INTO `tprocess_para` VALUES ('521', '5', '3', '第一次清洗', 'L1086', '第二次摇床震荡孵育', 'L1103', '6', '3', '摇床工作', 'L1129', '[{\"id\":1,\"paraName\":\"摇床速度\",\"paraValue\":2},{\"id\":2,\"paraName\":\"震荡孵育时间(s)\",\"paraValue\":30},{\"id\":3,\"paraName\":\"X轴电机初始化\",\"paraValue\":1}]', '0', null, null);
INSERT INTO `tprocess_para` VALUES ('524', '5', '3', '第一次清洗', 'L1086', '第三次摇床电机初始化', 'L1104', '7', '1', '摇床电机初始化', 'L1060', '[{\"id\":1,\"paraName\":\"初始化延时时间(s)\",\"paraValue\":1000}]', '0', null, null);
INSERT INTO `tprocess_para` VALUES ('527', '5', '3', '第一次清洗', 'L1086', '第三次排废液及蠕动泵加液(洗涤缓冲液)', 'L1105', '8', '2', '排废液及蠕动泵加液', 'L1128', '[{\"id\":1,\"paraName\":\"RID\",\"paraValue\":9},{\"id\":2,\"paraName\":\"加液量(ul)\",\"paraValue\":1000},{\"id\":3,\"paraName\":\"排废液(s)\",\"paraValue\":3}]', '0', null, null);
INSERT INTO `tprocess_para` VALUES ('530', '5', '3', '第一次清洗', 'L1086', '第三次摇床震荡孵育', 'L1106', '9', '3', '摇床工作', 'L1129', '[{\"id\":1,\"paraName\":\"摇床速度\",\"paraValue\":2},{\"id\":2,\"paraName\":\"震荡孵育时间(s)\",\"paraValue\":30},{\"id\":3,\"paraName\":\"X轴电机初始化\",\"paraValue\":1}]', '0', null, null);
INSERT INTO `tprocess_para` VALUES ('533', '5', '3', '第一次清洗', 'L1086', '第四次摇床电机初始化', 'L1132', '10', '1', '摇床电机初始化', 'L1060', '[{\"id\":1,\"paraName\":\"初始化延时时间(s)\",\"paraValue\":1000}]', '0', null, null);
INSERT INTO `tprocess_para` VALUES ('536', '5', '3', '第一次清洗', 'L1086', '第四次排废液及蠕动泵加液(洗涤缓冲液)', 'L1133', '11', '2', '排废液及蠕动泵加液', 'L1128', '[{\"id\":1,\"paraName\":\"RID\",\"paraValue\":9},{\"id\":2,\"paraName\":\"加液量(ul)\",\"paraValue\":1000},{\"id\":3,\"paraName\":\"排废液(s)\",\"paraValue\":3}]', '0', null, null);
INSERT INTO `tprocess_para` VALUES ('539', '5', '3', '第一次清洗', 'L1086', '第四次摇床震荡孵育', 'L1134', '12', '3', '摇床工作', 'L1129', '[{\"id\":1,\"paraName\":\"摇床速度\",\"paraValue\":2},{\"id\":2,\"paraName\":\"震荡孵育时间(s)\",\"paraValue\":30},{\"id\":3,\"paraName\":\"X轴电机初始化\",\"paraValue\":1}]', '0', null, null);
INSERT INTO `tprocess_para` VALUES ('542', '5', '3', '第一次清洗', 'L1086', '第五次摇床电机初始化', 'L1135', '13', '1', '摇床电机初始化', 'L1060', '[{\"id\":1,\"paraName\":\"初始化延时时间(s)\",\"paraValue\":1000}]', '0', null, null);
INSERT INTO `tprocess_para` VALUES ('545', '5', '3', '第一次清洗', 'L1086', '第五次排废液及蠕动泵加液(洗涤缓冲液)', 'L1136', '14', '2', '排废液及蠕动泵加液', 'L1128', '[{\"id\":1,\"paraName\":\"RID\",\"paraValue\":9},{\"id\":2,\"paraName\":\"加液量(ul)\",\"paraValue\":1000},{\"id\":3,\"paraName\":\"排废液(s)\",\"paraValue\":3}]', '0', null, null);
INSERT INTO `tprocess_para` VALUES ('548', '5', '3', '第一次清洗', 'L1086', '第五次摇床震荡孵育', 'L1137', '15', '3', '摇床工作', 'L1129', '[{\"id\":1,\"paraName\":\"摇床速度\",\"paraValue\":2},{\"id\":2,\"paraName\":\"震荡孵育时间(s)\",\"paraValue\":30},{\"id\":3,\"paraName\":\"X轴电机初始化\",\"paraValue\":1}]', '0', null, null);
INSERT INTO `tprocess_para` VALUES ('551', '5', '4', '加酶', 'L1087', '摇床电机初始化', 'L1060', '1', '1', '摇床电机初始化', 'L1060', '[{\"id\":1,\"paraName\":\"初始化延时时间(s)\",\"paraValue\":1000}]', '0', null, null);
INSERT INTO `tprocess_para` VALUES ('554', '5', '4', '加酶', 'L1087', '排废液及蠕动泵加液(结合物)', 'L1107', '2', '2', '排废液及蠕动泵加液', 'L1128', '[{\"id\":1,\"paraName\":\"RID\",\"paraValue\":-1},{\"id\":2,\"paraName\":\"加酶量(ul)\",\"paraValue\":1000},{\"id\":3,\"paraName\":\"排废液(s)\",\"paraValue\":3}]', '0', null, null);
INSERT INTO `tprocess_para` VALUES ('557', '5', '4', '加酶', 'L1087', '回流(结合物)', 'L1108', '3', '4', '蠕动泵回流', 'L1130', '[{\"id\":1,\"paraName\":\"回流\",\"paraValue\":-1},{\"id\":2,\"paraName\":\"回流体积\",\"paraValue\":3000}]', '0', null, null);
INSERT INTO `tprocess_para` VALUES ('560', '5', '4', '加酶', 'L1087', '摇床震荡孵育', 'L1094', '4', '3', '摇床工作', 'L1129', '[{\"id\":1,\"paraName\":\"摇床速度\",\"paraValue\":2},{\"id\":2,\"paraName\":\"震荡孵育时间(s)\",\"paraValue\":1800},{\"id\":3,\"paraName\":\"X轴电机初始化\",\"paraValue\":1}]', '0', null, null);
INSERT INTO `tprocess_para` VALUES ('563', '5', '5', '第二次清洗', 'L1088', '第一次摇床电机初始化', 'L1098', '1', '1', '摇床电机初始化', 'L1060', '[{\"id\":1,\"paraName\":\"初始化延时时间(s)\",\"paraValue\":1000}]', '0', null, null);
INSERT INTO `tprocess_para` VALUES ('566', '5', '5', '第二次清洗', 'L1088', '第一次排废液及蠕动泵加液(洗涤缓冲液)', 'L1099', '2', '2', '排废液及蠕动泵加液', 'L1128', '[{\"id\":1,\"paraName\":\"RID\",\"paraValue\":9},{\"id\":2,\"paraName\":\"加液量(ul)\",\"paraValue\":1000},{\"id\":3,\"paraName\":\"排废液(s)\",\"paraValue\":3}]', '0', null, null);
INSERT INTO `tprocess_para` VALUES ('569', '5', '5', '第二次清洗', 'L1088', '第一次摇床震荡孵育', 'L1100', '3', '3', '摇床工作', 'L1129', '[{\"id\":1,\"paraName\":\"摇床速度\",\"paraValue\":2},{\"id\":2,\"paraName\":\"震荡孵育时间(s)\",\"paraValue\":30},{\"id\":3,\"paraName\":\"X轴电机初始化\",\"paraValue\":1}]', '0', null, null);
INSERT INTO `tprocess_para` VALUES ('572', '5', '5', '第二次清洗', 'L1088', '第二次摇床电机初始化', 'L1101', '4', '1', '摇床电机初始化', 'L1060', '[{\"id\":1,\"paraName\":\"初始化延时时间(s)\",\"paraValue\":1000}]', '0', null, null);
INSERT INTO `tprocess_para` VALUES ('575', '5', '5', '第二次清洗', 'L1088', '第二次排废液及蠕动泵加液(洗涤缓冲液)', 'L1102', '5', '2', '排废液及蠕动泵加液', 'L1128', '[{\"id\":1,\"paraName\":\"RID\",\"paraValue\":9},{\"id\":2,\"paraName\":\"加液量(ul)\",\"paraValue\":1000},{\"id\":3,\"paraName\":\"排废液(s)\",\"paraValue\":3}]', '0', null, null);
INSERT INTO `tprocess_para` VALUES ('578', '5', '5', '第二次清洗', 'L1088', '第二次摇床震荡孵育', 'L1103', '6', '3', '摇床工作', 'L1129', '[{\"id\":1,\"paraName\":\"摇床速度\",\"paraValue\":2},{\"id\":2,\"paraName\":\"震荡孵育时间(s)\",\"paraValue\":30},{\"id\":3,\"paraName\":\"X轴电机初始化\",\"paraValue\":1}]', '0', null, null);
INSERT INTO `tprocess_para` VALUES ('581', '5', '5', '第二次清洗', 'L1088', '第三次摇床电机初始化', 'L1104', '7', '1', '摇床电机初始化', 'L1060', '[{\"id\":1,\"paraName\":\"初始化延时时间(s)\",\"paraValue\":1000}]', '0', null, null);
INSERT INTO `tprocess_para` VALUES ('584', '5', '5', '第二次清洗', 'L1088', '第三次排废液及蠕动泵加液(洗涤缓冲液)', 'L1105', '8', '2', '排废液及蠕动泵加液', 'L1128', '[{\"id\":1,\"paraName\":\"RID\",\"paraValue\":9},{\"id\":2,\"paraName\":\"加液量(ul)\",\"paraValue\":1000},{\"id\":3,\"paraName\":\"排废液(s)\",\"paraValue\":3}]', '0', null, null);
INSERT INTO `tprocess_para` VALUES ('587', '5', '5', '第二次清洗', 'L1088', '第三次摇床震荡孵育', 'L1106', '9', '3', '摇床工作', 'L1129', '[{\"id\":1,\"paraName\":\"摇床速度\",\"paraValue\":2},{\"id\":2,\"paraName\":\"震荡孵育时间(s)\",\"paraValue\":30},{\"id\":3,\"paraName\":\"X轴电机初始化\",\"paraValue\":1}]', '0', null, null);
INSERT INTO `tprocess_para` VALUES ('590', '5', '5', '第二次清洗', 'L1088', '第四次摇床电机初始化', 'L1132', '10', '1', '摇床电机初始化', 'L1060', '[{\"id\":1,\"paraName\":\"初始化延时时间(s)\",\"paraValue\":1000}]', '0', null, null);
INSERT INTO `tprocess_para` VALUES ('593', '5', '5', '第二次清洗', 'L1088', '第四次排废液及蠕动泵加液(洗涤缓冲液)', 'L1133', '11', '2', '排废液及蠕动泵加液', 'L1128', '[{\"id\":1,\"paraName\":\"RID\",\"paraValue\":9},{\"id\":2,\"paraName\":\"加液量(ul)\",\"paraValue\":1000},{\"id\":3,\"paraName\":\"排废液(s)\",\"paraValue\":3}]', '0', null, null);
INSERT INTO `tprocess_para` VALUES ('596', '5', '5', '第二次清洗', 'L1088', '第四次摇床震荡孵育', 'L1134', '12', '3', '摇床工作', 'L1129', '[{\"id\":1,\"paraName\":\"摇床速度\",\"paraValue\":2},{\"id\":2,\"paraName\":\"震荡孵育时间(s)\",\"paraValue\":30},{\"id\":3,\"paraName\":\"X轴电机初始化\",\"paraValue\":1}]', '0', null, null);
INSERT INTO `tprocess_para` VALUES ('599', '5', '5', '第二次清洗', 'L1088', '第五次摇床电机初始化', 'L1135', '13', '1', '摇床电机初始化', 'L1060', '[{\"id\":1,\"paraName\":\"初始化延时时间(s)\",\"paraValue\":1000}]', '0', null, null);
INSERT INTO `tprocess_para` VALUES ('602', '5', '5', '第二次清洗', 'L1088', '第五次排废液及蠕动泵加液(洗涤缓冲液)', 'L1136', '14', '2', '排废液及蠕动泵加液', 'L1128', '[{\"id\":1,\"paraName\":\"RID\",\"paraValue\":9},{\"id\":2,\"paraName\":\"加液量(ul)\",\"paraValue\":1000},{\"id\":3,\"paraName\":\"排废液(s)\",\"paraValue\":3}]', '0', null, null);
INSERT INTO `tprocess_para` VALUES ('605', '5', '5', '第二次清洗', 'L1088', '回流(洗涤缓冲液)', 'L1138', '15', '4', '蠕动泵回流', 'L1130', '[{\"id\":1,\"paraName\":\"回流\",\"paraValue\":9},{\"id\":2,\"paraName\":\"回流体积\",\"paraValue\":3000}]', '0', null, null);
INSERT INTO `tprocess_para` VALUES ('608', '5', '5', '第二次清洗', 'L1088', '第五次摇床震荡孵育', 'L1137', '16', '3', '摇床工作', 'L1129', '[{\"id\":1,\"paraName\":\"摇床速度\",\"paraValue\":2},{\"id\":2,\"paraName\":\"震荡孵育时间(s)\",\"paraValue\":30},{\"id\":3,\"paraName\":\"X轴电机初始化\",\"paraValue\":1}]', '0', null, null);
INSERT INTO `tprocess_para` VALUES ('611', '5', '6', '加底物', 'L1089', '摇床电机初始化', 'L1060', '1', '1', '摇床电机初始化', 'L1060', '[{\"id\":1,\"paraName\":\"初始化延时时间(s)\",\"paraValue\":1000}]', '0', null, null);
INSERT INTO `tprocess_para` VALUES ('614', '5', '6', '加底物', 'L1089', '排废液及蠕动泵加液(底物液)', 'L1110', '2', '2', '排废液及蠕动泵加液', 'L1128', '[{\"id\":1,\"paraName\":\"RID\",\"paraValue\":6},{\"id\":2,\"paraName\":\"加液量(ul)\",\"paraValue\":1000},{\"id\":3,\"paraName\":\"排废液(s)\",\"paraValue\":3}]', '0', null, null);
INSERT INTO `tprocess_para` VALUES ('617', '5', '6', '加底物', 'L1089', '回流(底物液)', 'L1111', '3', '4', '蠕动泵回流', 'L1130', '[{\"id\":1,\"paraName\":\"回流\",\"paraValue\":6},{\"id\":2,\"paraName\":\"回流体积\",\"paraValue\":3000}]', '0', null, null);
INSERT INTO `tprocess_para` VALUES ('620', '5', '6', '加底物', 'L1089', '摇床震荡孵育', 'L1094', '4', '3', '摇床工作', 'L1129', '[{\"id\":1,\"paraName\":\"摇床速度\",\"paraValue\":2},{\"id\":2,\"paraName\":\"震荡孵育时间(s)\",\"paraValue\":1200},{\"id\":3,\"paraName\":\"X轴电机初始化\",\"paraValue\":1}]', '0', null, null);
INSERT INTO `tprocess_para` VALUES ('623', '5', '7', '加蒸馏水', 'L1090', '摇床电机初始化', 'L1060', '1', '1', '摇床电机初始化', 'L1060', '[{\"id\":1,\"paraName\":\"初始化延时时间(s)\",\"paraValue\":1000}]', '0', null, null);
INSERT INTO `tprocess_para` VALUES ('626', '5', '7', '加蒸馏水', 'L1090', '排废液及加入蒸馏水', 'L1112', '2', '2', '排废液及蠕动泵加液', 'L1128', '[{\"id\":1,\"paraName\":\"RID\",\"paraValue\":8},{\"id\":2,\"paraName\":\"加液量(ul)\",\"paraValue\":1000},{\"id\":3,\"paraName\":\"排废液(s)\",\"paraValue\":3}]', '0', null, null);
INSERT INTO `tprocess_para` VALUES ('629', '5', '7', '加蒸馏水', 'L1090', '摇床震荡孵育', 'L1094', '3', '3', '摇床工作', 'L1129', '[{\"id\":1,\"paraName\":\"摇床速度\",\"paraValue\":2},{\"id\":2,\"paraName\":\"震荡孵育时间(s)\",\"paraValue\":30},{\"id\":3,\"paraName\":\"X轴电机初始化\",\"paraValue\":1}]', '0', null, null);
INSERT INTO `tprocess_para` VALUES ('632', '5', '7', '加蒸馏水', 'L1090', '摇床电机初始化', 'L1060', '4', '1', '摇床电机初始化', 'L1060', '[{\"id\":1,\"paraName\":\"初始化延时时间(s)\",\"paraValue\":1000}]', '0', null, null);
INSERT INTO `tprocess_para` VALUES ('635', '5', '7', '加蒸馏水', 'L1090', '排废液及加入蒸馏水', 'L1112', '5', '2', '排废液及蠕动泵加液', 'L1128', '[{\"id\":1,\"paraName\":\"RID\",\"paraValue\":8},{\"id\":2,\"paraName\":\"加液量(ul)\",\"paraValue\":1000},{\"id\":3,\"paraName\":\"排废液(s)\",\"paraValue\":3}]', '0', null, null);
INSERT INTO `tprocess_para` VALUES ('638', '5', '7', '加蒸馏水', 'L1090', '摇床震荡孵育', 'L1094', '6', '3', '摇床工作', 'L1129', '[{\"id\":1,\"paraName\":\"摇床速度\",\"paraValue\":2},{\"id\":2,\"paraName\":\"震荡孵育时间(s)\",\"paraValue\":30},{\"id\":3,\"paraName\":\"X轴电机初始化\",\"paraValue\":1}]', '0', null, null);
INSERT INTO `tprocess_para` VALUES ('641', '5', '7', '加蒸馏水', 'L1090', '摇床电机初始化', 'L1060', '7', '1', '摇床电机初始化', 'L1060', '[{\"id\":1,\"paraName\":\"初始化延时时间(s)\",\"paraValue\":1000}]', '0', null, null);
INSERT INTO `tprocess_para` VALUES ('644', '5', '7', '加蒸馏水', 'L1090', '排废液及加入蒸馏水', 'L1112', '8', '2', '排废液及蠕动泵加液', 'L1128', '[{\"id\":1,\"paraName\":\"RID\",\"paraValue\":8},{\"id\":2,\"paraName\":\"加液量(ul)\",\"paraValue\":1000},{\"id\":3,\"paraName\":\"排废液(s)\",\"paraValue\":3}]', '0', null, null);
INSERT INTO `tprocess_para` VALUES ('647', '5', '7', '加蒸馏水', 'L1090', '摇床震荡孵育', 'L1094', '9', '3', '摇床工作', 'L1129', '[{\"id\":1,\"paraName\":\"摇床速度\",\"paraValue\":2},{\"id\":2,\"paraName\":\"震荡孵育时间(s)\",\"paraValue\":30},{\"id\":3,\"paraName\":\"X轴电机初始化\",\"paraValue\":1}]', '0', null, null);
INSERT INTO `tprocess_para` VALUES ('650', '5', '7', '加蒸馏水', 'L1090', '摇床电机初始化', 'L1060', '10', '1', '摇床电机初始化', 'L1060', '[{\"id\":1,\"paraName\":\"初始化延时时间(s)\",\"paraValue\":1000}]', '0', null, null);
INSERT INTO `tprocess_para` VALUES ('653', '5', '7', '加蒸馏水', 'L1090', '排废液及加入蒸馏水', 'L1112', '11', '2', '排废液及蠕动泵加液', 'L1128', '[{\"id\":1,\"paraName\":\"RID\",\"paraValue\":8},{\"id\":2,\"paraName\":\"加液量(ul)\",\"paraValue\":1000},{\"id\":3,\"paraName\":\"排废液(s)\",\"paraValue\":3}]', '0', null, null);
INSERT INTO `tprocess_para` VALUES ('656', '5', '7', '加蒸馏水', 'L1090', '摇床震荡孵育', 'L1094', '12', '3', '摇床工作', 'L1129', '[{\"id\":1,\"paraName\":\"摇床速度\",\"paraValue\":2},{\"id\":2,\"paraName\":\"震荡孵育时间(s)\",\"paraValue\":30},{\"id\":3,\"paraName\":\"X轴电机初始化\",\"paraValue\":1}]', '0', null, null);
INSERT INTO `tprocess_para` VALUES ('659', '5', '7', '加蒸馏水', 'L1090', '摇床电机初始化', 'L1060', '13', '1', '摇床电机初始化', 'L1060', '[{\"id\":1,\"paraName\":\"初始化延时时间(s)\",\"paraValue\":1000}]', '0', null, null);
INSERT INTO `tprocess_para` VALUES ('662', '5', '7', '加蒸馏水', 'L1090', '排废液及加入蒸馏水', 'L1112', '14', '2', '排废液及蠕动泵加液', 'L1128', '[{\"id\":1,\"paraName\":\"RID\",\"paraValue\":8},{\"id\":2,\"paraName\":\"加液量(ul)\",\"paraValue\":1000},{\"id\":3,\"paraName\":\"排废液(s)\",\"paraValue\":3}]', '0', null, null);
INSERT INTO `tprocess_para` VALUES ('665', '5', '7', '加蒸馏水', 'L1088', '回流(加蒸馏水)', 'L1109', '15', '4', '蠕动泵回流', 'L1130', '[{\"id\":1,\"paraName\":\"回流\",\"paraValue\":8},{\"id\":2,\"paraName\":\"回流体积\",\"paraValue\":3000}]', '0', null, null);
INSERT INTO `tprocess_para` VALUES ('668', '5', '7', '加蒸馏水', 'L1090', '摇床震荡孵育', 'L1094', '15', '3', '摇床工作', 'L1129', '[{\"id\":1,\"paraName\":\"摇床速度\",\"paraValue\":2},{\"id\":2,\"paraName\":\"震荡孵育时间(s)\",\"paraValue\":30},{\"id\":3,\"paraName\":\"X轴电机初始化\",\"paraValue\":1}]', '0', null, null);
INSERT INTO `tprocess_para` VALUES ('671', '5', '9', '干燥', 'L1092', '摇床电机初始化', 'L1060', '1', '1', '摇床电机初始化', 'L1060', '[{\"id\":1,\"paraName\":\"初始化延时时间(s)\",\"paraValue\":1000}]', '0', null, null);
INSERT INTO `tprocess_para` VALUES ('674', '5', '9', '干燥', 'L1092', '排废液', 'L1115', '2', '2', '排废液及蠕动泵加液', 'L1128', '[{\"id\":1,\"paraName\":\"RID\",\"paraValue\":8},{\"id\":2,\"paraName\":\"加液量(ul)\",\"paraValue\":0},{\"id\":3,\"paraName\":\"排废液(s)\",\"paraValue\":3}]', '0', null, null);
INSERT INTO `tprocess_para` VALUES ('677', '5', '9', '干燥', 'L1092', '打开加热', 'L1116', '3', '6', '加热', 'L1131', '[{\"id\":1,\"paraName\":\"温控开关(0=关,1=开)\",\"paraValue\":0},{\"id\":2,\"paraName\":\"目标温度\",\"paraValue\":25}]', '0', null, null);
INSERT INTO `tprocess_para` VALUES ('680', '5', '9', '干燥', 'L1092', '摇床震荡+风扇干燥', 'L1117', '4', '7', '摇床震荡+风扇干燥', 'L1117', '[{\"id\":1,\"paraName\":\"时间(s)\",\"paraValue\":7200},{\"id\":2,\"paraName\":\"风扇速度\",\"paraValue\":0},{\"id\":3,\"paraName\":\"摇床速度\",\"paraValue\":2},{\"id\":4,\"paraName\":\"风扇时间(s)\",\"paraValue\":30},{\"id\":5,\"paraName\":\"X轴电机初始化\",\"paraValue\":1}]', '0', null, null);
INSERT INTO `tprocess_para` VALUES ('683', '5', '9', '干燥', 'L1092', '关闭加热', 'L1118', '5', '6', '加热', 'L1131', '[{\"id\":1,\"paraName\":\"温控开关(0=关,1=开)\",\"paraValue\":0},{\"id\":2,\"paraName\":\"目标温度\",\"paraValue\":25}]', '0', null, null);
INSERT INTO `tprocess_para` VALUES ('686', '5', '9', '干燥', 'L1092', '摇床电机初始化', 'L1060', '6', '1', '摇床电机初始化', 'L1060', '[{\"id\":1,\"paraName\":\"初始化延时时间(s)\",\"paraValue\":1000}]', '0', null, null);

-- ----------------------------
-- Table structure for tprocess_para_copy1
-- ----------------------------
DROP TABLE IF EXISTS `tprocess_para_copy1`;
CREATE TABLE `tprocess_para_copy1` (
  `id` int(11) NOT NULL,
  `companyId` int(11) DEFAULT '0',
  `groupId` int(11) DEFAULT '0',
  `groupName` varchar(255) DEFAULT '',
  `groupNameCode` varchar(255) DEFAULT '',
  `stepName` varchar(255) DEFAULT '',
  `stepNameCode` varchar(255) DEFAULT '',
  `actIndex` int(11) DEFAULT '0',
  `actId` int(11) DEFAULT '0',
  `actName` varchar(255) DEFAULT '',
  `actNameCode` varchar(255) DEFAULT '',
  `paras` varchar(1023) DEFAULT '',
  `isPopWindow` tinyint(255) DEFAULT '0',
  `popWindowDes` varchar(255) DEFAULT '',
  `popWindowDesCode` varchar(255) DEFAULT '',
  PRIMARY KEY (`id`) USING BTREE
) ENGINE=InnoDB DEFAULT CHARSET=utf8 ROW_FORMAT=DYNAMIC;

-- ----------------------------
-- Records of tprocess_para_copy1
-- ----------------------------
INSERT INTO `tprocess_para_copy1` VALUES ('1', '1', '1', '润湿', 'L1084', '摇床电机初始化', 'L1060', '1', '1', '摇床电机初始化', 'L1060', '[{\"id\":1,\"paraName\":\"初始化延时时间(s)\",\"paraValue\":1000}]', '0', '', '');
INSERT INTO `tprocess_para_copy1` VALUES ('2', '1', '1', '润湿', 'L1084', '蠕动泵加液(洗涤缓冲液)', 'L1093', '2', '2', '排废液及蠕动泵加液', 'L1128', '[{\"id\":1,\"paraName\":\"RID\",\"paraValue\":9},{\"id\":2,\"paraName\":\"加液量(ul)\",\"paraValue\":1000},{\"id\":3,\"paraName\":\"排废液(s)\",\"paraValue\":0}]', '0', '', '');
INSERT INTO `tprocess_para_copy1` VALUES ('3', '1', '1', '润湿', 'L1084', '摇床震荡孵育', 'L1094', '3', '3', '摇床工作', 'L1129', '[{\"id\":1,\"paraName\":\"摇床速度\",\"paraValue\":2},{\"id\":2,\"paraName\":\"震荡孵育时间(s)\",\"paraValue\":60},{\"id\":3,\"paraName\":\"X轴电机初始化\",\"paraValue\":1}]', '0', '', '');
INSERT INTO `tprocess_para_copy1` VALUES ('4', '1', '2', '加样本', 'L1085', '摇床电机初始化', 'L1060', '1', '1', '摇床电机初始化', 'L1060', '[{\"id\":1,\"paraName\":\"初始化延时时间(s)\",\"paraValue\":1000}]', '0', '', '');
INSERT INTO `tprocess_para_copy1` VALUES ('5', '1', '2', '加样本', 'L1085', '排废液及蠕动泵加液(稀释缓冲液)', 'L1095', '2', '2', '排废液及蠕动泵加液', 'L1128', '[{\"id\":1,\"paraName\":\"RID\",\"paraValue\":5},{\"id\":2,\"paraName\":\"加液量(ul)\",\"paraValue\":1000},{\"id\":3,\"paraName\":\"排废液(s)\",\"paraValue\":3}]', '0', '', '');
INSERT INTO `tprocess_para_copy1` VALUES ('6', '1', '2', '加样本', 'L1085', '回流(稀释缓冲液回流)', 'L1096', '3', '4', '蠕动泵回流', 'L1130', '[{\"id\":1,\"paraName\":\"回流类型\",\"paraValue\":5},{\"id\":2,\"paraName\":\"回流体积\",\"paraValue\":3000}]', '0', '', '');
INSERT INTO `tprocess_para_copy1` VALUES ('7', '1', '2', '加样本', 'L1085', '样本臂移液', 'L1008', '4', '5', '样本臂移液', 'L1008', '[{\"id\":1,\"paraName\":\"加样量\",\"paraValue\":10}]', '0', '', '');
INSERT INTO `tprocess_para_copy1` VALUES ('8', '1', '2', '加样本', 'L1085', '摇床震荡孵育', 'L1094', '5', '3', '摇床工作', 'L1129', '[{\"id\":1,\"paraName\":\"摇床速度\",\"paraValue\":2},{\"id\":2,\"paraName\":\"震荡孵育时间(s)\",\"paraValue\":1800},{\"id\":3,\"paraName\":\"X轴电机初始化\",\"paraValue\":1}]', '0', '', '');
INSERT INTO `tprocess_para_copy1` VALUES ('9', '1', '3', '第一次清洗', 'L1086', '第一次摇床电机初始化', 'L1098', '1', '1', '摇床电机初始化', 'L1060', '[{\"id\":1,\"paraName\":\"初始化延时时间(s)\",\"paraValue\":1000}]', '0', '', '');
INSERT INTO `tprocess_para_copy1` VALUES ('10', '1', '3', '第一次清洗', 'L1086', '第一次排废液及蠕动泵加液(洗涤缓冲液)', 'L1099', '2', '2', '排废液及蠕动泵加液', 'L1128', '[{\"id\":1,\"paraName\":\"RID\",\"paraValue\":9},{\"id\":2,\"paraName\":\"加液量(ul)\",\"paraValue\":1500},{\"id\":3,\"paraName\":\"排废液(s)\",\"paraValue\":3}]', '0', '', '');
INSERT INTO `tprocess_para_copy1` VALUES ('11', '1', '3', '第一次清洗', 'L1086', '第一次摇床震荡孵育', 'L1100', '3', '3', '摇床工作', 'L1129', '[{\"id\":1,\"paraName\":\"摇床速度\",\"paraValue\":2},{\"id\":2,\"paraName\":\"震荡孵育时间(s)\",\"paraValue\":300},{\"id\":3,\"paraName\":\"X轴电机初始化\",\"paraValue\":1}]', '0', '', '');
INSERT INTO `tprocess_para_copy1` VALUES ('12', '1', '3', '第一次清洗', 'L1086', '第二次摇床电机初始化', 'L1101', '4', '1', '摇床电机初始化', 'L1060', '[{\"id\":1,\"paraName\":\"初始化延时时间(s)\",\"paraValue\":1000}]', '0', '', '');
INSERT INTO `tprocess_para_copy1` VALUES ('13', '1', '3', '第一次清洗', 'L1086', '第二次排废液及蠕动泵加液(洗涤缓冲液)', 'L1102', '5', '2', '排废液及蠕动泵加液', 'L1128', '[{\"id\":1,\"paraName\":\"RID\",\"paraValue\":9},{\"id\":2,\"paraName\":\"加液量(ul)\",\"paraValue\":1500},{\"id\":3,\"paraName\":\"排废液(s)\",\"paraValue\":3}]', '0', '', '');
INSERT INTO `tprocess_para_copy1` VALUES ('14', '1', '3', '第一次清洗', 'L1086', '第二次摇床震荡孵育', 'L1103', '6', '3', '摇床工作', 'L1129', '[{\"id\":1,\"paraName\":\"摇床速度\",\"paraValue\":2},{\"id\":2,\"paraName\":\"震荡孵育时间(s)\",\"paraValue\":300},{\"id\":3,\"paraName\":\"X轴电机初始化\",\"paraValue\":1}]', '0', '', '');
INSERT INTO `tprocess_para_copy1` VALUES ('15', '1', '3', '第一次清洗', 'L1086', '第三次摇床电机初始化', 'L1104', '7', '1', '摇床电机初始化', 'L1060', '[{\"id\":1,\"paraName\":\"初始化延时时间(s)\",\"paraValue\":1000}]', '0', '', '');
INSERT INTO `tprocess_para_copy1` VALUES ('16', '1', '3', '第一次清洗', 'L1086', '第三次排废液及蠕动泵加液(洗涤缓冲液)', 'L1105', '8', '2', '排废液及蠕动泵加液', 'L1128', '[{\"id\":1,\"paraName\":\"RID\",\"paraValue\":9},{\"id\":2,\"paraName\":\"加液量(ul)\",\"paraValue\":1500},{\"id\":3,\"paraName\":\"排废液(s)\",\"paraValue\":3}]', '0', '', '');
INSERT INTO `tprocess_para_copy1` VALUES ('17', '1', '3', '第一次清洗', 'L1086', '第三次摇床震荡孵育', 'L1106', '9', '3', '摇床工作', 'L1129', '[{\"id\":1,\"paraName\":\"摇床速度\",\"paraValue\":2},{\"id\":2,\"paraName\":\"震荡孵育时间(s)\",\"paraValue\":300},{\"id\":3,\"paraName\":\"X轴电机初始化\",\"paraValue\":1}]', '0', '', '');
INSERT INTO `tprocess_para_copy1` VALUES ('18', '1', '4', '加酶', 'L1087', '摇床电机初始化', 'L1060', '1', '1', '摇床电机初始化', 'L1060', '[{\"id\":1,\"paraName\":\"初始化延时时间(s)\",\"paraValue\":1000}]', '0', '', '');
INSERT INTO `tprocess_para_copy1` VALUES ('19', '1', '4', '加酶', 'L1087', '排废液及蠕动泵加液(结合物)', 'L1107', '2', '2', '排废液及蠕动泵加液', 'L1128', '[{\"id\":1,\"paraName\":\"RID\",\"paraValue\":-1},{\"id\":2,\"paraName\":\"加酶量(ul)\",\"paraValue\":1000},{\"id\":3,\"paraName\":\"排废液(s)\",\"paraValue\":3}]', '0', '', '');
INSERT INTO `tprocess_para_copy1` VALUES ('20', '1', '4', '加酶', 'L1087', '回流(结合物)', 'L1108', '3', '4', '蠕动泵回流', 'L1130', '[{\"id\":1,\"paraName\":\"回流\",\"paraValue\":-1},{\"id\":2,\"paraName\":\"回流体积\",\"paraValue\":3000}]', '0', '', '');
INSERT INTO `tprocess_para_copy1` VALUES ('21', '1', '4', '加酶', 'L1087', '摇床震荡孵育', 'L1094', '4', '3', '摇床工作', 'L1129', '[{\"id\":1,\"paraName\":\"摇床速度\",\"paraValue\":2},{\"id\":2,\"paraName\":\"震荡孵育时间(s)\",\"paraValue\":1800},{\"id\":3,\"paraName\":\"X轴电机初始化\",\"paraValue\":1}]', '0', '', '');
INSERT INTO `tprocess_para_copy1` VALUES ('22', '1', '5', '第二次清洗', 'L1088', '第一次摇床电机初始化', 'L1098', '1', '1', '摇床电机初始化', 'L1060', '[{\"id\":1,\"paraName\":\"初始化延时时间(s)\",\"paraValue\":1000}]', '0', '', '');
INSERT INTO `tprocess_para_copy1` VALUES ('23', '1', '5', '第二次清洗', 'L1088', '第一次排废液及蠕动泵加液(洗涤缓冲液)', 'L1099', '2', '2', '排废液及蠕动泵加液', 'L1128', '[{\"id\":1,\"paraName\":\"RID\",\"paraValue\":9},{\"id\":2,\"paraName\":\"加液量(ul)\",\"paraValue\":1500},{\"id\":3,\"paraName\":\"排废液(s)\",\"paraValue\":3}]', '0', '', '');
INSERT INTO `tprocess_para_copy1` VALUES ('24', '1', '5', '第二次清洗', 'L1088', '第一次摇床震荡孵育', 'L1100', '3', '3', '摇床工作', 'L1129', '[{\"id\":1,\"paraName\":\"摇床速度\",\"paraValue\":2},{\"id\":2,\"paraName\":\"震荡孵育时间(s)\",\"paraValue\":300},{\"id\":3,\"paraName\":\"X轴电机初始化\",\"paraValue\":1}]', '0', '', '');
INSERT INTO `tprocess_para_copy1` VALUES ('25', '1', '5', '第二次清洗', 'L1088', '第二次摇床电机初始化', 'L1101', '4', '1', '摇床电机初始化', 'L1060', '[{\"id\":1,\"paraName\":\"初始化延时时间(s)\",\"paraValue\":1000}]', '0', '', '');
INSERT INTO `tprocess_para_copy1` VALUES ('26', '1', '5', '第二次清洗', 'L1088', '第二次排废液及蠕动泵加液(洗涤缓冲液)', 'L1102', '5', '2', '排废液及蠕动泵加液', 'L1128', '[{\"id\":1,\"paraName\":\"RID\",\"paraValue\":9},{\"id\":2,\"paraName\":\"加液量(ul)\",\"paraValue\":1500},{\"id\":3,\"paraName\":\"排废液(s)\",\"paraValue\":3}]', '0', '', '');
INSERT INTO `tprocess_para_copy1` VALUES ('27', '1', '5', '第二次清洗', 'L1088', '第二次摇床震荡孵育', 'L1103', '6', '3', '摇床工作', 'L1129', '[{\"id\":1,\"paraName\":\"摇床速度\",\"paraValue\":2},{\"id\":2,\"paraName\":\"震荡孵育时间(s)\",\"paraValue\":300},{\"id\":3,\"paraName\":\"X轴电机初始化\",\"paraValue\":1}]', '0', '', '');
INSERT INTO `tprocess_para_copy1` VALUES ('28', '1', '5', '第二次清洗', 'L1088', '第三次摇床电机初始化', 'L1104', '7', '1', '摇床电机初始化', 'L1060', '[{\"id\":1,\"paraName\":\"初始化延时时间(s)\",\"paraValue\":1000}]', '0', '', '');
INSERT INTO `tprocess_para_copy1` VALUES ('29', '1', '5', '第二次清洗', 'L1088', '第三次排废液及蠕动泵加液(洗涤缓冲液)', 'L1105', '8', '2', '排废液及蠕动泵加液', 'L1128', '[{\"id\":1,\"paraName\":\"RID\",\"paraValue\":9},{\"id\":2,\"paraName\":\"加液量(ul)\",\"paraValue\":1500},{\"id\":3,\"paraName\":\"排废液(s)\",\"paraValue\":3}]', '0', '', '');
INSERT INTO `tprocess_para_copy1` VALUES ('30', '1', '5', '第二次清洗', 'L1088', '第三次回流(洗涤缓冲液)', 'L1109', '9', '4', '蠕动泵回流', 'L1130', '[{\"id\":1,\"paraName\":\"回流\",\"paraValue\":9},{\"id\":2,\"paraName\":\"回流体积\",\"paraValue\":3000}]', '0', '', '');
INSERT INTO `tprocess_para_copy1` VALUES ('31', '1', '5', '第二次清洗', 'L1088', '第三次摇床震荡孵育', 'L1106', '10', '3', '摇床工作', 'L1129', '[{\"id\":1,\"paraName\":\"摇床速度\",\"paraValue\":2},{\"id\":2,\"paraName\":\"震荡孵育时间(s)\",\"paraValue\":300},{\"id\":3,\"paraName\":\"X轴电机初始化\",\"paraValue\":1}]', '0', '', '');
INSERT INTO `tprocess_para_copy1` VALUES ('32', '1', '6', '加底物', 'L1089', '摇床电机初始化', 'L1060', '1', '1', '摇床电机初始化', 'L1060', '[{\"id\":1,\"paraName\":\"初始化延时时间(s)\",\"paraValue\":1000}]', '0', '', '');
INSERT INTO `tprocess_para_copy1` VALUES ('33', '1', '6', '加底物', 'L1089', '排废液及蠕动泵加液(底物液)', 'L1110', '2', '2', '排废液及蠕动泵加液', 'L1128', '[{\"id\":1,\"paraName\":\"RID\",\"paraValue\":6},{\"id\":2,\"paraName\":\"加液量(ul)\",\"paraValue\":1000},{\"id\":3,\"paraName\":\"排废液(s)\",\"paraValue\":3}]', '0', '', '');
INSERT INTO `tprocess_para_copy1` VALUES ('34', '1', '6', '加底物', 'L1089', '回流(底物液)', 'L1111', '3', '4', '蠕动泵回流', 'L1130', '[{\"id\":1,\"paraName\":\"回流\",\"paraValue\":6},{\"id\":2,\"paraName\":\"回流体积\",\"paraValue\":3000}]', '0', '', '');
INSERT INTO `tprocess_para_copy1` VALUES ('35', '1', '6', '加底物', 'L1089', '摇床震荡孵育', 'L1094', '4', '3', '摇床工作', 'L1129', '[{\"id\":1,\"paraName\":\"摇床速度\",\"paraValue\":2},{\"id\":2,\"paraName\":\"震荡孵育时间(s)\",\"paraValue\":900},{\"id\":3,\"paraName\":\"X轴电机初始化\",\"paraValue\":1}]', '0', '', '');
INSERT INTO `tprocess_para_copy1` VALUES ('36', '1', '7', '加蒸馏水', 'L1090', '摇床电机初始化', 'L1060', '1', '1', '摇床电机初始化', 'L1060', '[{\"id\":1,\"paraName\":\"初始化延时时间(s)\",\"paraValue\":1000}]', '0', '', '');
INSERT INTO `tprocess_para_copy1` VALUES ('37', '1', '7', '加蒸馏水', 'L1090', '排废液及加入蒸馏水', 'L1112', '2', '2', '排废液及蠕动泵加液', 'L1128', '[{\"id\":1,\"paraName\":\"RID\",\"paraValue\":8},{\"id\":2,\"paraName\":\"加液量(ul)\",\"paraValue\":1000},{\"id\":3,\"paraName\":\"排废液(s)\",\"paraValue\":3}]', '0', '', '');
INSERT INTO `tprocess_para_copy1` VALUES ('38', '1', '7', '加蒸馏水', 'L1090', '摇床震荡孵育', 'L1094', '3', '3', '摇床工作', 'L1129', '[{\"id\":1,\"paraName\":\"摇床速度\",\"paraValue\":2},{\"id\":2,\"paraName\":\"震荡孵育时间(s)\",\"paraValue\":60},{\"id\":3,\"paraName\":\"X轴电机初始化\",\"paraValue\":1}]', '0', '', '');
INSERT INTO `tprocess_para_copy1` VALUES ('39', '1', '8', '加终止液', 'L1091', '摇床电机初始化', 'L1060', '1', '1', '摇床电机初始化', 'L1060', '[{\"id\":1,\"paraName\":\"初始化延时时间(s)\",\"paraValue\":1000}]', '0', '', '');
INSERT INTO `tprocess_para_copy1` VALUES ('40', '1', '8', '加终止液', 'L1091', '排废液及加入中止液STOP', 'L1113', '2', '2', '排废液及蠕动泵加液', 'L1128', '[{\"id\":1,\"paraName\":\"RID\",\"paraValue\":7},{\"id\":2,\"paraName\":\"加液量(ul)\",\"paraValue\":1000},{\"id\":3,\"paraName\":\"排废液(s)\",\"paraValue\":3}]', '0', '', '');
INSERT INTO `tprocess_para_copy1` VALUES ('41', '1', '8', '加终止液', 'L1091', '回流(中止液)', 'L1114', '3', '4', '蠕动泵回流', 'L1130', '[{\"id\":1,\"paraName\":\"回流\",\"paraValue\":7},{\"id\":2,\"paraName\":\"回流体积\",\"paraValue\":3000}]', '0', '', '');
INSERT INTO `tprocess_para_copy1` VALUES ('42', '1', '8', '加终止液', 'L1091', '摇床震荡孵育', 'L1094', '4', '3', '摇床工作', 'L1129', '[{\"id\":1,\"paraName\":\"摇床速度\",\"paraValue\":2},{\"id\":2,\"paraName\":\"震荡孵育时间(s)\",\"paraValue\":300},{\"id\":3,\"paraName\":\"X轴电机初始化\",\"paraValue\":1}]', '0', '', '');
INSERT INTO `tprocess_para_copy1` VALUES ('43', '1', '9', '干燥', 'L1092', '摇床电机初始化', 'L1060', '1', '1', '摇床电机初始化', 'L1060', '[{\"id\":1,\"paraName\":\"初始化延时时间(s)\",\"paraValue\":1000}]', '0', '', '');
INSERT INTO `tprocess_para_copy1` VALUES ('44', '1', '9', '干燥', 'L1092', '排废液', 'L1115', '2', '2', '排废液及蠕动泵加液', 'L1128', '[{\"id\":1,\"paraName\":\"RID\",\"paraValue\":7},{\"id\":2,\"paraName\":\"加液量(ul)\",\"paraValue\":0},{\"id\":3,\"paraName\":\"排废液(s)\",\"paraValue\":3}]', '0', '', '');
INSERT INTO `tprocess_para_copy1` VALUES ('45', '1', '9', '干燥', 'L1092', '打开加热', 'L1116', '3', '6', '加热', 'L1131', '[{\"id\":1,\"paraName\":\"温控开关(0=关,1=开)\",\"paraValue\":1},{\"id\":2,\"paraName\":\"目标温度\",\"paraValue\":30}]', '0', '', '');
INSERT INTO `tprocess_para_copy1` VALUES ('46', '1', '9', '干燥', 'L1092', '摇床震荡+风扇干燥', 'L1117', '4', '7', '摇床震荡+风扇干燥', 'L1117', '[{\"id\":1,\"paraName\":\"时间(s)\",\"paraValue\":900},{\"id\":2,\"paraName\":\"风扇速度\",\"paraValue\":4},{\"id\":3,\"paraName\":\"摇床速度\",\"paraValue\":2},{\"id\":4,\"paraName\":\"风扇时间(s)\",\"paraValue\":5},{\"id\":5,\"paraName\":\"X轴电机初始化\",\"paraValue\":0}]', '0', '', '');
INSERT INTO `tprocess_para_copy1` VALUES ('47', '1', '9', '干燥', 'L1092', '关闭加热', 'L1118', '5', '6', '加热', 'L1131', '[{\"id\":1,\"paraName\":\"温控开关(0=关,1=开)\",\"paraValue\":0},{\"id\":2,\"paraName\":\"目标温度\",\"paraValue\":25}]', '0', '', '');
INSERT INTO `tprocess_para_copy1` VALUES ('48', '1', '9', '干燥', 'L1092', '摇床震荡+风扇干燥', 'L1117', '6', '7', '摇床震荡+风扇干燥', 'L1117', '[{\"id\":1,\"paraName\":\"时间(s)\",\"paraValue\":900},{\"id\":2,\"paraName\":\"风扇速度\",\"paraValue\":4},{\"id\":3,\"paraName\":\"摇床速度\",\"paraValue\":2},{\"id\":4,\"paraName\":\"风扇时间(s)\",\"paraValue\":5},{\"id\":5,\"paraName\":\"X轴电机初始化\",\"paraValue\":1}]', '0', '', '');
INSERT INTO `tprocess_para_copy1` VALUES ('49', '1', '9', '干燥', 'L1092', '摇床电机初始化', 'L1060', '7', '1', '摇床电机初始化', 'L1060', '[{\"id\":1,\"paraName\":\"初始化延时时间(s)\",\"paraValue\":1000}]', '0', '', '');
INSERT INTO `tprocess_para_copy1` VALUES ('60', '2', '1', '润湿', 'L1084', '摇床电机初始化', 'L1060', '1', '1', '摇床电机初始化', 'L1060', '[]', '0', '', '');
INSERT INTO `tprocess_para_copy1` VALUES ('63', '2', '1', '润湿', 'L1084', '蠕动泵加液(稀释液)', 'L1119', '2', '2', '排废液及蠕动泵加液', 'L1128', '[{\"id\":1,\"paraName\":\"RID\",\"paraValue\":5},{\"id\":2,\"paraName\":\"加液量(ul)\",\"paraValue\":1500},{\"id\":3,\"paraName\":\"排废液(s)\",\"paraValue\":0}]', '0', '', '');
INSERT INTO `tprocess_para_copy1` VALUES ('65', '2', '1', '润湿', 'L1084', '摇床震荡孵育', 'L1094', '3', '3', '摇床工作', 'L1129', '[{\"id\":1,\"paraName\":\"摇床速度\",\"paraValue\":2},{\"id\":2,\"paraName\":\"震荡孵育时间(s)\",\"paraValue\":300},{\"id\":3,\"paraName\":\"X轴电机初始化\",\"paraValue\":1}]', '0', '', '');
INSERT INTO `tprocess_para_copy1` VALUES ('67', '2', '2', '加样本', 'L1085', '摇床电机初始化', 'L1060', '1', '1', '摇床电机初始化', 'L1060', '[]', '0', '', '');
INSERT INTO `tprocess_para_copy1` VALUES ('69', '2', '2', '加样本', 'L1085', '排废液及蠕动泵加液(稀释液)', 'L1120', '2', '2', '排废液及蠕动泵加液', 'L1128', '[{\"id\":1,\"paraName\":\"RID\",\"paraValue\":5},{\"id\":2,\"paraName\":\"加液量(ul)\",\"paraValue\":1500},{\"id\":3,\"paraName\":\"排废液(s)\",\"paraValue\":3}]', '0', '', '');
INSERT INTO `tprocess_para_copy1` VALUES ('71', '2', '2', '加样本', 'L1085', '回流(稀释液)', 'L1121', '3', '4', '蠕动泵回流', 'L1130', '[{\"id\":1,\"paraName\":\"RID\",\"paraValue\":5},{\"id\":2,\"paraName\":\"回流体积\",\"paraValue\":3000}]', '0', '', '');
INSERT INTO `tprocess_para_copy1` VALUES ('73', '2', '2', '加样本', 'L1085', '样本臂移液', 'L1008', '4', '5', '样本臂移液', 'L1008', '[{\"id\":1,\"paraName\":\"加样量\",\"paraValue\":15}]', '0', '', '');
INSERT INTO `tprocess_para_copy1` VALUES ('75', '2', '2', '加样本', 'L1085', '摇床震荡孵育', 'L1094', '5', '3', '摇床工作', 'L1129', '[{\"id\":1,\"paraName\":\"摇床速度\",\"paraValue\":2},{\"id\":2,\"paraName\":\"震荡孵育时间(s)\",\"paraValue\":1800},{\"id\":3,\"paraName\":\"X轴电机初始化\",\"paraValue\":1}]', '0', '', '');
INSERT INTO `tprocess_para_copy1` VALUES ('77', '2', '3', '第一次清洗', 'L1086', '第一次摇床电机初始化', 'L1098', '1', '1', '摇床电机初始化', 'L1060', '[]', '0', '', '');
INSERT INTO `tprocess_para_copy1` VALUES ('79', '2', '3', '第一次清洗', 'L1086', '第一次排废液及蠕动泵加液(清洗液)', 'L1122', '2', '2', '排废液及蠕动泵加液', 'L1128', '[{\"id\":1,\"paraName\":\"RID\",\"paraValue\":9},{\"id\":2,\"paraName\":\"加液量(ul)\",\"paraValue\":1500},{\"id\":3,\"paraName\":\"排废液(s)\",\"paraValue\":3}]', '0', '', '');
INSERT INTO `tprocess_para_copy1` VALUES ('81', '2', '3', '第一次清洗', 'L1086', '第一次摇床震荡孵育', 'L1100', '3', '3', '摇床工作', 'L1129', '[{\"id\":1,\"paraName\":\"摇床速度\",\"paraValue\":2},{\"id\":2,\"paraName\":\"震荡孵育时间(s)\",\"paraValue\":600},{\"id\":3,\"paraName\":\"X轴电机初始化\",\"paraValue\":1}]', '0', '', '');
INSERT INTO `tprocess_para_copy1` VALUES ('83', '2', '3', '第一次清洗', 'L1086', '第二次摇床电机初始化', 'L1101', '4', '1', '摇床电机初始化', 'L1060', '[]', '0', '', '');
INSERT INTO `tprocess_para_copy1` VALUES ('85', '2', '3', '第一次清洗', 'L1086', '第二次排废液及蠕动泵加液(清洗液)', 'L1123', '5', '2', '排废液及蠕动泵加液', 'L1128', '[{\"id\":1,\"paraName\":\"RID\",\"paraValue\":9},{\"id\":2,\"paraName\":\"加液量(ul)\",\"paraValue\":1500},{\"id\":3,\"paraName\":\"排废液(s)\",\"paraValue\":3}]', '0', '', '');
INSERT INTO `tprocess_para_copy1` VALUES ('87', '2', '3', '第一次清洗', 'L1086', '第二次摇床震荡孵育', 'L1103', '6', '3', '摇床工作', 'L1129', '[{\"id\":1,\"paraName\":\"摇床速度\",\"paraValue\":2},{\"id\":2,\"paraName\":\"震荡孵育时间(s)\",\"paraValue\":600},{\"id\":3,\"paraName\":\"X轴电机初始化\",\"paraValue\":1}]', '0', '', '');
INSERT INTO `tprocess_para_copy1` VALUES ('89', '2', '3', '第一次清洗', 'L1086', '第三次摇床电机初始化', 'L1104', '7', '1', '摇床电机初始化', 'L1060', '[]', '0', '', '');
INSERT INTO `tprocess_para_copy1` VALUES ('91', '2', '3', '第一次清洗', 'L1086', '第三次排废液及蠕动泵加液(清洗液)', 'L1124', '8', '2', '排废液及蠕动泵加液', 'L1128', '[{\"id\":1,\"paraName\":\"RID\",\"paraValue\":9},{\"id\":2,\"paraName\":\"加液量(ul)\",\"paraValue\":1500},{\"id\":3,\"paraName\":\"排废液(s)\",\"paraValue\":3}]', '0', '', '');
INSERT INTO `tprocess_para_copy1` VALUES ('93', '2', '3', '第一次清洗', 'L1086', '第三次摇床震荡孵育', 'L1106', '9', '3', '摇床工作', 'L1129', '[{\"id\":1,\"paraName\":\"摇床速度\",\"paraValue\":2},{\"id\":2,\"paraName\":\"震荡孵育时间(s)\",\"paraValue\":600},{\"id\":3,\"paraName\":\"X轴电机初始化\",\"paraValue\":1}]', '0', '', '');
INSERT INTO `tprocess_para_copy1` VALUES ('95', '2', '4', '加酶', 'L1087', '摇床电机初始化', 'L1060', '1', '1', '摇床电机初始化', 'L1060', '[]', '0', '', '');
INSERT INTO `tprocess_para_copy1` VALUES ('97', '2', '4', '加酶', 'L1087', '排废液及蠕动泵加液(结合物)', 'L1107', '2', '2', '排废液及蠕动泵加液', 'L1128', '[{\"id\":1,\"paraName\":\"RID\",\"paraValue\":-1},{\"id\":2,\"paraName\":\"加酶量(ul)\",\"paraValue\":1500},{\"id\":3,\"paraName\":\"排废液(s)\",\"paraValue\":3}]', '0', '', '');
INSERT INTO `tprocess_para_copy1` VALUES ('99', '2', '4', '加酶', 'L1087', '回流(结合物)', 'L1108', '3', '4', '蠕动泵回流', 'L1130', '[{\"id\":1,\"paraName\":\"RID\",\"paraValue\":-1},{\"id\":2,\"paraName\":\"回流体积\",\"paraValue\":3000}]', '0', '', '');
INSERT INTO `tprocess_para_copy1` VALUES ('101', '2', '4', '加酶', 'L1087', '摇床震荡孵育', 'L1094', '4', '3', '摇床工作', 'L1129', '[{\"id\":1,\"paraName\":\"摇床速度\",\"paraValue\":2},{\"id\":2,\"paraName\":\"震荡孵育时间(s)\",\"paraValue\":1800},{\"id\":3,\"paraName\":\"X轴电机初始化\",\"paraValue\":1}]', '0', '', '');
INSERT INTO `tprocess_para_copy1` VALUES ('103', '2', '5', '第二次清洗', 'L1088', '第一次摇床电机初始化', 'L1098', '1', '1', '摇床电机初始化', 'L1060', '[]', '0', '', '');
INSERT INTO `tprocess_para_copy1` VALUES ('105', '2', '5', '第二次清洗', 'L1088', '第一次排废液及蠕动泵加液(清洗液)', 'L1122', '2', '2', '排废液及蠕动泵加液', 'L1128', '[{\"id\":1,\"paraName\":\"RID\",\"paraValue\":9},{\"id\":2,\"paraName\":\"加液量(ul)\",\"paraValue\":1500},{\"id\":3,\"paraName\":\"排废液(s)\",\"paraValue\":3}]', '0', '', '');
INSERT INTO `tprocess_para_copy1` VALUES ('107', '2', '5', '第二次清洗', 'L1088', '第一次摇床震荡孵育', 'L1100', '3', '3', '摇床工作', 'L1129', '[{\"id\":1,\"paraName\":\"摇床速度\",\"paraValue\":2},{\"id\":2,\"paraName\":\"震荡孵育时间(s)\",\"paraValue\":600},{\"id\":3,\"paraName\":\"X轴电机初始化\",\"paraValue\":1}]', '0', '', '');
INSERT INTO `tprocess_para_copy1` VALUES ('109', '2', '5', '第二次清洗', 'L1088', '第二次摇床电机初始化', 'L1101', '4', '1', '摇床电机初始化', 'L1060', '[]', '0', '', '');
INSERT INTO `tprocess_para_copy1` VALUES ('111', '2', '5', '第二次清洗', 'L1088', '第二次排废液及蠕动泵加液(清洗液)', 'L1123', '5', '2', '排废液及蠕动泵加液', 'L1128', '[{\"id\":1,\"paraName\":\"RID\",\"paraValue\":9},{\"id\":2,\"paraName\":\"加液量(ul)\",\"paraValue\":1500},{\"id\":3,\"paraName\":\"排废液(s)\",\"paraValue\":3}]', '0', '', '');
INSERT INTO `tprocess_para_copy1` VALUES ('113', '2', '5', '第二次清洗', 'L1088', '第二次摇床震荡孵育', 'L1103', '6', '3', '摇床工作', 'L1129', '[{\"id\":1,\"paraName\":\"摇床速度\",\"paraValue\":2},{\"id\":2,\"paraName\":\"震荡孵育时间(s)\",\"paraValue\":600},{\"id\":3,\"paraName\":\"X轴电机初始化\",\"paraValue\":1}]', '0', '', '');
INSERT INTO `tprocess_para_copy1` VALUES ('115', '2', '5', '第二次清洗', 'L1088', '第二次摇床电机初始化', 'L1101', '7', '1', '摇床电机初始化', 'L1060', '[]', '0', '', '');
INSERT INTO `tprocess_para_copy1` VALUES ('117', '2', '5', '第二次清洗', 'L1088', '第二次排废液及蠕动泵加液(清洗液)', 'L1123', '8', '2', '排废液及蠕动泵加液', 'L1128', '[{\"id\":1,\"paraName\":\"RID\",\"paraValue\":9},{\"id\":2,\"paraName\":\"加液量(ul)\",\"paraValue\":1500},{\"id\":3,\"paraName\":\"排废液(s)\",\"paraValue\":3}]', '0', '', '');
INSERT INTO `tprocess_para_copy1` VALUES ('119', '2', '5', '第二次清洗', 'L1088', '回流(清洗液)', 'L1125', '9', '4', '蠕动泵回流', 'L1130', '[{\"id\":1,\"paraName\":\"RID\",\"paraValue\":9},{\"id\":2,\"paraName\":\"回流体积\",\"paraValue\":3000}]', '0', '', '');
INSERT INTO `tprocess_para_copy1` VALUES ('121', '2', '5', '第二次清洗', 'L1088', '第二次摇床震荡孵育', 'L1103', '10', '3', '摇床工作', 'L1129', '[{\"id\":1,\"paraName\":\"摇床速度\",\"paraValue\":2},{\"id\":2,\"paraName\":\"震荡孵育时间(s)\",\"paraValue\":600},{\"id\":3,\"paraName\":\"X轴电机初始化\",\"paraValue\":1}]', '0', '', '');
INSERT INTO `tprocess_para_copy1` VALUES ('123', '2', '6', '加底物', 'L1089', '摇床电机初始化', 'L1060', '1', '1', '摇床电机初始化', 'L1060', '[]', '0', '', '');
INSERT INTO `tprocess_para_copy1` VALUES ('125', '2', '6', '加底物', 'L1089', '排废液及蠕动泵加液(底物液)', 'L1110', '2', '2', '排废液及蠕动泵加液', 'L1128', '[{\"id\":1,\"paraName\":\"RID\",\"paraValue\":6},{\"id\":2,\"paraName\":\"加液量(ul)\",\"paraValue\":1500},{\"id\":3,\"paraName\":\"排废液(s)\",\"paraValue\":3}]', '0', '', '');
INSERT INTO `tprocess_para_copy1` VALUES ('127', '2', '6', '加底物', 'L1089', '回流(底物液)', 'L1111', '3', '4', '蠕动泵回流', 'L1130', '[{\"id\":1,\"paraName\":\"RID\",\"paraValue\":6},{\"id\":2,\"paraName\":\"回流体积\",\"paraValue\":3000}]', '0', '', '');
INSERT INTO `tprocess_para_copy1` VALUES ('129', '2', '6', '加底物', 'L1089', '摇床震荡孵育', 'L1094', '4', '3', '摇床工作', 'L1129', '[{\"id\":1,\"paraName\":\"摇床速度\",\"paraValue\":2},{\"id\":2,\"paraName\":\"震荡孵育时间(s)\",\"paraValue\":600},{\"id\":3,\"paraName\":\"X轴电机初始化\",\"paraValue\":1}]', '0', '', '');
INSERT INTO `tprocess_para_copy1` VALUES ('131', '2', '7', '加蒸馏水', 'L1090', '摇床电机初始化', 'L1060', '1', '1', '摇床电机初始化', 'L1060', '[]', '0', '', '');
INSERT INTO `tprocess_para_copy1` VALUES ('133', '2', '7', '加蒸馏水', 'L1090', '排废液及加入蒸馏水', 'L1112', '2', '2', '排废液及蠕动泵加液', 'L1128', '[{\"id\":1,\"paraName\":\"RID\",\"paraValue\":8},{\"id\":2,\"paraName\":\"加液量(ul)\",\"paraValue\":1500},{\"id\":3,\"paraName\":\"排废液(s)\",\"paraValue\":3}]', '0', '', '');
INSERT INTO `tprocess_para_copy1` VALUES ('135', '2', '7', '加蒸馏水', 'L1090', '摇床震荡孵育', 'L1094', '3', '3', '摇床工作', 'L1129', '[{\"id\":1,\"paraName\":\"摇床速度\",\"paraValue\":2},{\"id\":2,\"paraName\":\"震荡孵育时间(s)\",\"paraValue\":60},{\"id\":3,\"paraName\":\"X轴电机初始化\",\"paraValue\":1}]', '0', '', '');
INSERT INTO `tprocess_para_copy1` VALUES ('137', '2', '7', '加蒸馏水', 'L1090', '摇床电机初始化', 'L1060', '4', '1', '摇床电机初始化', 'L1060', '[]', '0', '', '');
INSERT INTO `tprocess_para_copy1` VALUES ('139', '2', '7', '加蒸馏水', 'L1090', '排废液及加入蒸馏水', 'L1112', '5', '2', '排废液及蠕动泵加液', 'L1128', '[{\"id\":1,\"paraName\":\"RID\",\"paraValue\":8},{\"id\":2,\"paraName\":\"加液量(ul)\",\"paraValue\":1500},{\"id\":3,\"paraName\":\"排废液(s)\",\"paraValue\":3}]', '0', '', '');
INSERT INTO `tprocess_para_copy1` VALUES ('141', '2', '7', '加蒸馏水', 'L1090', '摇床震荡孵育', 'L1094', '6', '3', '摇床工作', 'L1129', '[{\"id\":1,\"paraName\":\"摇床速度\",\"paraValue\":2},{\"id\":2,\"paraName\":\"震荡孵育时间(s)\",\"paraValue\":60},{\"id\":3,\"paraName\":\"X轴电机初始化\",\"paraValue\":1}]', '0', '', '');
INSERT INTO `tprocess_para_copy1` VALUES ('143', '2', '7', '加蒸馏水', 'L1090', '摇床电机初始化', 'L1060', '7', '1', '摇床电机初始化', 'L1060', '[]', '0', '', '');
INSERT INTO `tprocess_para_copy1` VALUES ('145', '2', '7', '加蒸馏水', 'L1090', '排废液及加入蒸馏水', 'L1112', '8', '2', '排废液及蠕动泵加液', 'L1128', '[{\"id\":1,\"paraName\":\"RID\",\"paraValue\":8},{\"id\":2,\"paraName\":\"加液量(ul)\",\"paraValue\":1500},{\"id\":3,\"paraName\":\"排废液(s)\",\"paraValue\":3}]', '0', '', '');
INSERT INTO `tprocess_para_copy1` VALUES ('147', '2', '7', '加蒸馏水', 'L1090', '摇床震荡孵育', 'L1094', '9', '3', '摇床工作', 'L1129', '[{\"id\":1,\"paraName\":\"摇床速度\",\"paraValue\":2},{\"id\":2,\"paraName\":\"震荡孵育时间(s)\",\"paraValue\":60},{\"id\":3,\"paraName\":\"X轴电机初始化\",\"paraValue\":1}]', '0', '', '');
INSERT INTO `tprocess_para_copy1` VALUES ('149', '2', '9', '干燥', 'L1092', '摇床电机初始化', 'L1060', '1', '1', '摇床电机初始化', 'L1060', '[]', '0', '', '');
INSERT INTO `tprocess_para_copy1` VALUES ('150', '2', '9', '干燥', 'L1092', '排废液', 'L1115', '2', '2', '排废液及蠕动泵加液', 'L1128', '[{\"id\":1,\"paraName\":\"RID\",\"paraValue\":8},{\"id\":2,\"paraName\":\"加液量(ul)\",\"paraValue\":0},{\"id\":3,\"paraName\":\"排废液(s)\",\"paraValue\":3}]', '0', '', '');
INSERT INTO `tprocess_para_copy1` VALUES ('151', '2', '9', '干燥', 'L1092', '打开加热', 'L1116', '3', '6', '加热', 'L1131', '[{\"id\":1,\"paraName\":\"温控开关\",\"paraValue\":1},{\"id\":2,\"paraName\":\"目标温度\",\"paraValue\":37}]', '0', '', '');
INSERT INTO `tprocess_para_copy1` VALUES ('153', '2', '9', '干燥', 'L1092', '摇床震荡及加热+风扇干燥', 'L1127', '4', '7', '摇床震荡及加热+风扇干燥', 'L1127', '[{\"id\":1,\"paraName\":\"时间\",\"paraValue\":1800},{\"id\":2,\"paraName\":\"风扇速度\",\"paraValue\":5},{\"id\":3,\"paraName\":\"摇床速度\",\"paraValue\":2},{\"id\":4,\"paraName\":\"风扇时间(s)\",\"paraValue\":5},{\"id\":5,\"paraName\":\"X轴电机初始化\",\"paraValue\":1}]', '0', '', '');
INSERT INTO `tprocess_para_copy1` VALUES ('154', '2', '9', '干燥', 'L1092', '关闭加热', 'L1118', '5', '6', '加热', 'L1131', '[{\"id\":1,\"paraName\":\"温控开关\",\"paraValue\":0},{\"id\":2,\"paraName\":\"目标温度\",\"paraValue\":25}]', '0', '', '');
INSERT INTO `tprocess_para_copy1` VALUES ('180', '3', '1', '润湿', 'L1084', '摇床电机初始化', 'L1060', '1', '1', '摇床电机初始化', 'L1060', '[{\"id\":1,\"paraName\":\"初始化延时时间(s)\",\"paraValue\":1000}]', '0', '', '');
INSERT INTO `tprocess_para_copy1` VALUES ('181', '3', '1', '润湿', 'L1084', '蠕动泵加液(洗涤缓冲液)', 'L1093', '2', '2', '排废液及蠕动泵加液', 'L1128', '[{\"id\":1,\"paraName\":\"RID\",\"paraValue\":9},{\"id\":2,\"paraName\":\"加液量(ul)\",\"paraValue\":1000},{\"id\":3,\"paraName\":\"排废液(s)\",\"paraValue\":0}]', '0', '', '');
INSERT INTO `tprocess_para_copy1` VALUES ('182', '3', '1', '润湿', 'L1084', '摇床震荡孵育', 'L1094', '3', '3', '摇床工作', 'L1129', '[{\"id\":1,\"paraName\":\"摇床速度\",\"paraValue\":2},{\"id\":2,\"paraName\":\"震荡孵育时间(s)\",\"paraValue\":60},{\"id\":3,\"paraName\":\"X轴电机初始化\",\"paraValue\":1}]', '0', '', '');
INSERT INTO `tprocess_para_copy1` VALUES ('183', '3', '2', '加样本', 'L1085', '摇床电机初始化', 'L1060', '1', '1', '摇床电机初始化', 'L1060', '[{\"id\":1,\"paraName\":\"初始化延时时间(s)\",\"paraValue\":1000}]', '0', '', '');
INSERT INTO `tprocess_para_copy1` VALUES ('184', '3', '2', '加样本', 'L1085', '排废液及蠕动泵加液(稀释缓冲液)', 'L1095', '2', '2', '排废液及蠕动泵加液', 'L1128', '[{\"id\":1,\"paraName\":\"RID\",\"paraValue\":5},{\"id\":2,\"paraName\":\"加液量(ul)\",\"paraValue\":1000},{\"id\":3,\"paraName\":\"排废液(s)\",\"paraValue\":3}]', '0', '', '');
INSERT INTO `tprocess_para_copy1` VALUES ('185', '3', '2', '加样本', 'L1085', '回流(稀释缓冲液回流)', 'L1096', '3', '4', '蠕动泵回流', 'L1130', '[{\"id\":1,\"paraName\":\"回流类型\",\"paraValue\":5},{\"id\":2,\"paraName\":\"回流体积\",\"paraValue\":3000}]', '0', '', '');
INSERT INTO `tprocess_para_copy1` VALUES ('186', '3', '2', '加样本', 'L1085', '样本臂移液', 'L1008', '4', '5', '样本臂移液', 'L1008', '[{\"id\":1,\"paraName\":\"加样量\",\"paraValue\":10}]', '0', '', '');
INSERT INTO `tprocess_para_copy1` VALUES ('187', '3', '2', '加样本', 'L1085', '摇床震荡孵育', 'L1094', '5', '3', '摇床工作', 'L1129', '[{\"id\":1,\"paraName\":\"摇床速度\",\"paraValue\":2},{\"id\":2,\"paraName\":\"震荡孵育时间(s)\",\"paraValue\":60},{\"id\":3,\"paraName\":\"X轴电机初始化\",\"paraValue\":1}]', '0', '', '');
INSERT INTO `tprocess_para_copy1` VALUES ('188', '3', '3', '第一次清洗', 'L1086', '第一次摇床电机初始化', 'L1098', '1', '1', '摇床电机初始化', 'L1060', '[{\"id\":1,\"paraName\":\"初始化延时时间(s)\",\"paraValue\":1000}]', '0', '', '');
INSERT INTO `tprocess_para_copy1` VALUES ('189', '3', '3', '第一次清洗', 'L1086', '第一次排废液及蠕动泵加液(洗涤缓冲液)', 'L1099', '2', '2', '排废液及蠕动泵加液', 'L1128', '[{\"id\":1,\"paraName\":\"RID\",\"paraValue\":9},{\"id\":2,\"paraName\":\"加液量(ul)\",\"paraValue\":1500},{\"id\":3,\"paraName\":\"排废液(s)\",\"paraValue\":3}]', '0', '', '');
INSERT INTO `tprocess_para_copy1` VALUES ('190', '3', '3', '第一次清洗', 'L1086', '第一次摇床震荡孵育', 'L1100', '3', '3', '摇床工作', 'L1129', '[{\"id\":1,\"paraName\":\"摇床速度\",\"paraValue\":2},{\"id\":2,\"paraName\":\"震荡孵育时间(s)\",\"paraValue\":60},{\"id\":3,\"paraName\":\"X轴电机初始化\",\"paraValue\":1}]', '0', '', '');
INSERT INTO `tprocess_para_copy1` VALUES ('191', '3', '3', '第一次清洗', 'L1086', '第二次摇床电机初始化', 'L1101', '4', '1', '摇床电机初始化', 'L1060', '[{\"id\":1,\"paraName\":\"初始化延时时间(s)\",\"paraValue\":1000}]', '0', '', '');
INSERT INTO `tprocess_para_copy1` VALUES ('192', '3', '3', '第一次清洗', 'L1086', '第二次排废液及蠕动泵加液(洗涤缓冲液)', 'L1102', '5', '2', '排废液及蠕动泵加液', 'L1128', '[{\"id\":1,\"paraName\":\"RID\",\"paraValue\":9},{\"id\":2,\"paraName\":\"加液量(ul)\",\"paraValue\":1500},{\"id\":3,\"paraName\":\"排废液(s)\",\"paraValue\":3}]', '0', '', '');
INSERT INTO `tprocess_para_copy1` VALUES ('193', '3', '3', '第一次清洗', 'L1086', '第二次摇床震荡孵育', 'L1103', '6', '3', '摇床工作', 'L1129', '[{\"id\":1,\"paraName\":\"摇床速度\",\"paraValue\":2},{\"id\":2,\"paraName\":\"震荡孵育时间(s)\",\"paraValue\":60},{\"id\":3,\"paraName\":\"X轴电机初始化\",\"paraValue\":1}]', '0', '', '');
INSERT INTO `tprocess_para_copy1` VALUES ('194', '3', '3', '第一次清洗', 'L1086', '第三次摇床电机初始化', 'L1104', '7', '1', '摇床电机初始化', 'L1060', '[{\"id\":1,\"paraName\":\"初始化延时时间(s)\",\"paraValue\":1000}]', '0', '', '');
INSERT INTO `tprocess_para_copy1` VALUES ('195', '3', '3', '第一次清洗', 'L1086', '第三次排废液及蠕动泵加液(洗涤缓冲液)', 'L1105', '8', '2', '排废液及蠕动泵加液', 'L1128', '[{\"id\":1,\"paraName\":\"RID\",\"paraValue\":9},{\"id\":2,\"paraName\":\"加液量(ul)\",\"paraValue\":1500},{\"id\":3,\"paraName\":\"排废液(s)\",\"paraValue\":3}]', '0', '', '');
INSERT INTO `tprocess_para_copy1` VALUES ('196', '3', '3', '第一次清洗', 'L1086', '第三次摇床震荡孵育', 'L1106', '9', '3', '摇床工作', 'L1129', '[{\"id\":1,\"paraName\":\"摇床速度\",\"paraValue\":2},{\"id\":2,\"paraName\":\"震荡孵育时间(s)\",\"paraValue\":60},{\"id\":3,\"paraName\":\"X轴电机初始化\",\"paraValue\":1}]', '0', '', '');
INSERT INTO `tprocess_para_copy1` VALUES ('197', '3', '4', '加酶', 'L1087', '摇床电机初始化', 'L1060', '1', '1', '摇床电机初始化', 'L1060', '[{\"id\":1,\"paraName\":\"初始化延时时间(s)\",\"paraValue\":1000}]', '0', '', '');
INSERT INTO `tprocess_para_copy1` VALUES ('198', '3', '4', '加酶', 'L1087', '排废液及蠕动泵加液(结合物)', 'L1107', '2', '2', '排废液及蠕动泵加液', 'L1128', '[{\"id\":1,\"paraName\":\"RID\",\"paraValue\":-1},{\"id\":2,\"paraName\":\"加酶量(ul)\",\"paraValue\":1000},{\"id\":3,\"paraName\":\"排废液(s)\",\"paraValue\":3}]', '0', '', '');
INSERT INTO `tprocess_para_copy1` VALUES ('199', '3', '4', '加酶', 'L1087', '回流(结合物)', 'L1108', '3', '4', '蠕动泵回流', 'L1130', '[{\"id\":1,\"paraName\":\"回流\",\"paraValue\":-1},{\"id\":2,\"paraName\":\"回流体积\",\"paraValue\":3000}]', '0', '', '');
INSERT INTO `tprocess_para_copy1` VALUES ('200', '3', '4', '加酶', 'L1087', '摇床震荡孵育', 'L1094', '4', '3', '摇床工作', 'L1129', '[{\"id\":1,\"paraName\":\"摇床速度\",\"paraValue\":2},{\"id\":2,\"paraName\":\"震荡孵育时间(s)\",\"paraValue\":60},{\"id\":3,\"paraName\":\"X轴电机初始化\",\"paraValue\":1}]', '0', '', '');
INSERT INTO `tprocess_para_copy1` VALUES ('201', '3', '5', '第二次清洗', 'L1088', '第一次摇床电机初始化', 'L1098', '1', '1', '摇床电机初始化', 'L1060', '[{\"id\":1,\"paraName\":\"初始化延时时间(s)\",\"paraValue\":1000}]', '0', '', '');
INSERT INTO `tprocess_para_copy1` VALUES ('202', '3', '5', '第二次清洗', 'L1088', '第一次排废液及蠕动泵加液(洗涤缓冲液)', 'L1099', '2', '2', '排废液及蠕动泵加液', 'L1128', '[{\"id\":1,\"paraName\":\"RID\",\"paraValue\":9},{\"id\":2,\"paraName\":\"加液量(ul)\",\"paraValue\":1500},{\"id\":3,\"paraName\":\"排废液(s)\",\"paraValue\":3}]', '0', '', '');
INSERT INTO `tprocess_para_copy1` VALUES ('203', '3', '5', '第二次清洗', 'L1088', '第一次摇床震荡孵育', 'L1100', '3', '3', '摇床工作', 'L1129', '[{\"id\":1,\"paraName\":\"摇床速度\",\"paraValue\":2},{\"id\":2,\"paraName\":\"震荡孵育时间(s)\",\"paraValue\":60},{\"id\":3,\"paraName\":\"X轴电机初始化\",\"paraValue\":1}]', '0', '', '');
INSERT INTO `tprocess_para_copy1` VALUES ('204', '3', '5', '第二次清洗', 'L1088', '第二次摇床电机初始化', 'L1101', '4', '1', '摇床电机初始化', 'L1060', '[{\"id\":1,\"paraName\":\"初始化延时时间(s)\",\"paraValue\":1000}]', '0', '', '');
INSERT INTO `tprocess_para_copy1` VALUES ('205', '3', '5', '第二次清洗', 'L1088', '第二次排废液及蠕动泵加液(洗涤缓冲液)', 'L1102', '5', '2', '排废液及蠕动泵加液', 'L1128', '[{\"id\":1,\"paraName\":\"RID\",\"paraValue\":9},{\"id\":2,\"paraName\":\"加液量(ul)\",\"paraValue\":1500},{\"id\":3,\"paraName\":\"排废液(s)\",\"paraValue\":3}]', '0', '', '');
INSERT INTO `tprocess_para_copy1` VALUES ('206', '3', '5', '第二次清洗', 'L1088', '第二次摇床震荡孵育', 'L1103', '6', '3', '摇床工作', 'L1129', '[{\"id\":1,\"paraName\":\"摇床速度\",\"paraValue\":2},{\"id\":2,\"paraName\":\"震荡孵育时间(s)\",\"paraValue\":60},{\"id\":3,\"paraName\":\"X轴电机初始化\",\"paraValue\":1}]', '0', '', '');
INSERT INTO `tprocess_para_copy1` VALUES ('207', '3', '5', '第二次清洗', 'L1088', '第三次摇床电机初始化', 'L1104', '7', '1', '摇床电机初始化', 'L1060', '[{\"id\":1,\"paraName\":\"初始化延时时间(s)\",\"paraValue\":1000}]', '0', '', '');
INSERT INTO `tprocess_para_copy1` VALUES ('208', '3', '5', '第二次清洗', 'L1088', '第三次排废液及蠕动泵加液(洗涤缓冲液)', 'L1105', '8', '2', '排废液及蠕动泵加液', 'L1128', '[{\"id\":1,\"paraName\":\"RID\",\"paraValue\":9},{\"id\":2,\"paraName\":\"加液量(ul)\",\"paraValue\":1500},{\"id\":3,\"paraName\":\"排废液(s)\",\"paraValue\":3}]', '0', '', '');
INSERT INTO `tprocess_para_copy1` VALUES ('209', '3', '5', '第二次清洗', 'L1088', '第三次回流(洗涤缓冲液)', 'L1109', '9', '4', '蠕动泵回流', 'L1130', '[{\"id\":1,\"paraName\":\"回流\",\"paraValue\":9},{\"id\":2,\"paraName\":\"回流体积\",\"paraValue\":3000}]', '0', '', '');
INSERT INTO `tprocess_para_copy1` VALUES ('210', '3', '5', '第二次清洗', 'L1088', '第三次摇床震荡孵育', 'L1106', '10', '3', '摇床工作', 'L1129', '[{\"id\":1,\"paraName\":\"摇床速度\",\"paraValue\":2},{\"id\":2,\"paraName\":\"震荡孵育时间(s)\",\"paraValue\":60},{\"id\":3,\"paraName\":\"X轴电机初始化\",\"paraValue\":1}]', '0', '', '');
INSERT INTO `tprocess_para_copy1` VALUES ('211', '3', '6', '加底物', 'L1089', '摇床电机初始化', 'L1060', '1', '1', '摇床电机初始化', 'L1060', '[{\"id\":1,\"paraName\":\"初始化延时时间(s)\",\"paraValue\":1000}]', '0', '', '');
INSERT INTO `tprocess_para_copy1` VALUES ('212', '3', '6', '加底物', 'L1089', '排废液及蠕动泵加液(底物液)', 'L1110', '2', '2', '排废液及蠕动泵加液', 'L1128', '[{\"id\":1,\"paraName\":\"RID\",\"paraValue\":6},{\"id\":2,\"paraName\":\"加液量(ul)\",\"paraValue\":1000},{\"id\":3,\"paraName\":\"排废液(s)\",\"paraValue\":3}]', '0', '', '');
INSERT INTO `tprocess_para_copy1` VALUES ('213', '3', '6', '加底物', 'L1089', '回流(底物液)', 'L1111', '3', '4', '蠕动泵回流', 'L1130', '[{\"id\":1,\"paraName\":\"回流\",\"paraValue\":6},{\"id\":2,\"paraName\":\"回流体积\",\"paraValue\":3000}]', '0', '', '');
INSERT INTO `tprocess_para_copy1` VALUES ('214', '3', '6', '加底物', 'L1089', '摇床震荡孵育', 'L1094', '4', '3', '摇床工作', 'L1129', '[{\"id\":1,\"paraName\":\"摇床速度\",\"paraValue\":2},{\"id\":2,\"paraName\":\"震荡孵育时间(s)\",\"paraValue\":60},{\"id\":3,\"paraName\":\"X轴电机初始化\",\"paraValue\":1}]', '0', '', '');
INSERT INTO `tprocess_para_copy1` VALUES ('215', '3', '7', '加蒸馏水', 'L1090', '摇床电机初始化', 'L1060', '1', '1', '摇床电机初始化', 'L1060', '[{\"id\":1,\"paraName\":\"初始化延时时间(s)\",\"paraValue\":1000}]', '0', '', '');
INSERT INTO `tprocess_para_copy1` VALUES ('216', '3', '7', '加蒸馏水', 'L1090', '排废液及加入蒸馏水', 'L1112', '2', '2', '排废液及蠕动泵加液', 'L1128', '[{\"id\":1,\"paraName\":\"RID\",\"paraValue\":8},{\"id\":2,\"paraName\":\"加液量(ul)\",\"paraValue\":1000},{\"id\":3,\"paraName\":\"排废液(s)\",\"paraValue\":3}]', '0', '', '');
INSERT INTO `tprocess_para_copy1` VALUES ('217', '3', '7', '加蒸馏水', 'L1090', '摇床震荡孵育', 'L1094', '3', '3', '摇床工作', 'L1129', '[{\"id\":1,\"paraName\":\"摇床速度\",\"paraValue\":2},{\"id\":2,\"paraName\":\"震荡孵育时间(s)\",\"paraValue\":60},{\"id\":3,\"paraName\":\"X轴电机初始化\",\"paraValue\":1}]', '0', '', '');
INSERT INTO `tprocess_para_copy1` VALUES ('218', '3', '8', '加终止液', 'L1091', '摇床电机初始化', 'L1060', '1', '1', '摇床电机初始化', 'L1060', '[{\"id\":1,\"paraName\":\"初始化延时时间(s)\",\"paraValue\":1000}]', '0', '', '');
INSERT INTO `tprocess_para_copy1` VALUES ('219', '3', '8', '加终止液', 'L1091', '排废液及加入中止液STOP', 'L1113', '2', '2', '排废液及蠕动泵加液', 'L1128', '[{\"id\":1,\"paraName\":\"RID\",\"paraValue\":7},{\"id\":2,\"paraName\":\"加液量(ul)\",\"paraValue\":1000},{\"id\":3,\"paraName\":\"排废液(s)\",\"paraValue\":3}]', '0', '', '');
INSERT INTO `tprocess_para_copy1` VALUES ('220', '3', '8', '加终止液', 'L1091', '回流(中止液)', 'L1114', '3', '4', '蠕动泵回流', 'L1130', '[{\"id\":1,\"paraName\":\"回流\",\"paraValue\":7},{\"id\":2,\"paraName\":\"回流体积\",\"paraValue\":3000}]', '0', '', '');
INSERT INTO `tprocess_para_copy1` VALUES ('221', '3', '8', '加终止液', 'L1091', '摇床震荡孵育', 'L1094', '4', '3', '摇床工作', 'L1129', '[{\"id\":1,\"paraName\":\"摇床速度\",\"paraValue\":2},{\"id\":2,\"paraName\":\"震荡孵育时间(s)\",\"paraValue\":60},{\"id\":3,\"paraName\":\"X轴电机初始化\",\"paraValue\":1}]', '0', '', '');
INSERT INTO `tprocess_para_copy1` VALUES ('222', '3', '9', '干燥', 'L1092', '摇床电机初始化', 'L1060', '1', '1', '摇床电机初始化', 'L1060', '[{\"id\":1,\"paraName\":\"初始化延时时间(s)\",\"paraValue\":1000}]', '0', '', '');
INSERT INTO `tprocess_para_copy1` VALUES ('223', '3', '9', '干燥', 'L1092', '排废液', 'L1115', '2', '2', '排废液及蠕动泵加液', 'L1128', '[{\"id\":1,\"paraName\":\"RID\",\"paraValue\":7},{\"id\":2,\"paraName\":\"加液量(ul)\",\"paraValue\":0},{\"id\":3,\"paraName\":\"排废液(s)\",\"paraValue\":3}]', '0', '', '');
INSERT INTO `tprocess_para_copy1` VALUES ('224', '3', '9', '干燥', 'L1092', '打开加热', 'L1116', '3', '6', '加热', 'L1131', '[{\"id\":1,\"paraName\":\"温控开关(0=关,1=开)\",\"paraValue\":1},{\"id\":2,\"paraName\":\"目标温度\",\"paraValue\":30}]', '0', '', '');
INSERT INTO `tprocess_para_copy1` VALUES ('225', '3', '9', '干燥', 'L1092', '摇床震荡+风扇干燥', 'L1117', '4', '7', '摇床震荡+风扇干燥', 'L1117', '[{\"id\":1,\"paraName\":\"时间(s)\",\"paraValue\":60},{\"id\":2,\"paraName\":\"风扇速度\",\"paraValue\":4},{\"id\":3,\"paraName\":\"摇床速度\",\"paraValue\":2},{\"id\":4,\"paraName\":\"风扇时间(s)\",\"paraValue\":5},{\"id\":5,\"paraName\":\"X轴电机初始化\",\"paraValue\":0}]', '0', '', '');
INSERT INTO `tprocess_para_copy1` VALUES ('226', '3', '9', '干燥', 'L1092', '关闭加热', 'L1118', '5', '6', '加热', 'L1131', '[{\"id\":1,\"paraName\":\"温控开关(0=关,1=开)\",\"paraValue\":0},{\"id\":2,\"paraName\":\"目标温度\",\"paraValue\":25}]', '0', '', '');
INSERT INTO `tprocess_para_copy1` VALUES ('227', '3', '9', '干燥', 'L1092', '摇床震荡+风扇干燥', 'L1117', '6', '7', '摇床震荡+风扇干燥', 'L1117', '[{\"id\":1,\"paraName\":\"时间(s)\",\"paraValue\":60},{\"id\":2,\"paraName\":\"风扇速度\",\"paraValue\":4},{\"id\":3,\"paraName\":\"摇床速度\",\"paraValue\":2},{\"id\":4,\"paraName\":\"风扇时间(s)\",\"paraValue\":5},{\"id\":5,\"paraName\":\"X轴电机初始化\",\"paraValue\":1}]', '0', '', '');
INSERT INTO `tprocess_para_copy1` VALUES ('228', '3', '9', '干燥', 'L1092', '摇床电机初始化', 'L1060', '7', '1', '摇床电机初始化', 'L1060', '[{\"id\":1,\"paraName\":\"初始化延时时间(s)\",\"paraValue\":1000}]', '0', '', '');
INSERT INTO `tprocess_para_copy1` VALUES ('258', '4', '2', '加样本', 'L1085', '摇床电机初始化', 'L1060', '1', '1', '摇床电机初始化', 'L1060', '[{\"id\":1,\"paraName\":\"初始化延时时间(s)\",\"paraValue\":1000}]', '0', '', '');
INSERT INTO `tprocess_para_copy1` VALUES ('261', '4', '2', '加样本', 'L1085', '排废液及蠕动泵加液(稀释缓冲液)', 'L1095', '2', '2', '排废液及蠕动泵加液', 'L1128', '[{\"id\":1,\"paraName\":\"RID\",\"paraValue\":5},{\"id\":2,\"paraName\":\"加液量(ul)\",\"paraValue\":1000},{\"id\":3,\"paraName\":\"排废液(s)\",\"paraValue\":3}]', '0', '', '');
INSERT INTO `tprocess_para_copy1` VALUES ('264', '4', '2', '加样本', 'L1085', '回流(稀释缓冲液回流)', 'L1096', '3', '4', '蠕动泵回流', 'L1130', '[{\"id\":1,\"paraName\":\"回流类型\",\"paraValue\":5},{\"id\":2,\"paraName\":\"回流体积\",\"paraValue\":3000}]', '0', '', '');
INSERT INTO `tprocess_para_copy1` VALUES ('267', '4', '2', '加样本', 'L1085', '样本臂移液', 'L1008', '4', '5', '样本臂移液', 'L1008', '[{\"id\":1,\"paraName\":\"加样量(ul)\",\"paraValue\":10}]', '0', '', '');
INSERT INTO `tprocess_para_copy1` VALUES ('270', '4', '2', '加样本', 'L1085', '摇床震荡孵育', 'L1094', '5', '3', '摇床工作', 'L1129', '[{\"id\":1,\"paraName\":\"摇床速度\",\"paraValue\":2},{\"id\":2,\"paraName\":\"震荡孵育时间(s)\",\"paraValue\":1800},{\"id\":3,\"paraName\":\"X轴电机初始化\",\"paraValue\":1}]', '0', '', '');
INSERT INTO `tprocess_para_copy1` VALUES ('273', '4', '3', '第一次清洗', 'L1086', '第一次摇床电机初始化', 'L1098', '1', '1', '摇床电机初始化', 'L1060', '[{\"id\":1,\"paraName\":\"初始化延时时间(s)\",\"paraValue\":1000}]', '0', '', '');
INSERT INTO `tprocess_para_copy1` VALUES ('276', '4', '3', '第一次清洗', 'L1086', '第一次排废液及蠕动泵加液(洗涤缓冲液)', 'L1099', '2', '2', '排废液及蠕动泵加液', 'L1128', '[{\"id\":1,\"paraName\":\"RID\",\"paraValue\":9},{\"id\":2,\"paraName\":\"加液量(ul)\",\"paraValue\":1000},{\"id\":3,\"paraName\":\"排废液(s)\",\"paraValue\":3}]', '0', '', '');
INSERT INTO `tprocess_para_copy1` VALUES ('279', '4', '3', '第一次清洗', 'L1086', '第一次摇床震荡孵育', 'L1100', '3', '3', '摇床工作', 'L1129', '[{\"id\":1,\"paraName\":\"摇床速度\",\"paraValue\":2},{\"id\":2,\"paraName\":\"震荡孵育时间(s)\",\"paraValue\":30},{\"id\":3,\"paraName\":\"X轴电机初始化\",\"paraValue\":1}]', '0', '', '');
INSERT INTO `tprocess_para_copy1` VALUES ('282', '4', '3', '第一次清洗', 'L1086', '第二次摇床电机初始化', 'L1101', '4', '1', '摇床电机初始化', 'L1060', '[{\"id\":1,\"paraName\":\"初始化延时时间(s)\",\"paraValue\":1000}]', '0', '', '');
INSERT INTO `tprocess_para_copy1` VALUES ('285', '4', '3', '第一次清洗', 'L1086', '第二次排废液及蠕动泵加液(洗涤缓冲液)', 'L1102', '5', '2', '排废液及蠕动泵加液', 'L1128', '[{\"id\":1,\"paraName\":\"RID\",\"paraValue\":9},{\"id\":2,\"paraName\":\"加液量(ul)\",\"paraValue\":1000},{\"id\":3,\"paraName\":\"排废液(s)\",\"paraValue\":3}]', '0', '', '');
INSERT INTO `tprocess_para_copy1` VALUES ('288', '4', '3', '第一次清洗', 'L1086', '第二次摇床震荡孵育', 'L1103', '6', '3', '摇床工作', 'L1129', '[{\"id\":1,\"paraName\":\"摇床速度\",\"paraValue\":2},{\"id\":2,\"paraName\":\"震荡孵育时间(s)\",\"paraValue\":30},{\"id\":3,\"paraName\":\"X轴电机初始化\",\"paraValue\":1}]', '0', '', '');
INSERT INTO `tprocess_para_copy1` VALUES ('291', '4', '3', '第一次清洗', 'L1086', '第三次摇床电机初始化', 'L1104', '7', '1', '摇床电机初始化', 'L1060', '[{\"id\":1,\"paraName\":\"初始化延时时间(s)\",\"paraValue\":1000}]', '0', '', '');
INSERT INTO `tprocess_para_copy1` VALUES ('294', '4', '3', '第一次清洗', 'L1086', '第三次排废液及蠕动泵加液(洗涤缓冲液)', 'L1105', '8', '2', '排废液及蠕动泵加液', 'L1128', '[{\"id\":1,\"paraName\":\"RID\",\"paraValue\":9},{\"id\":2,\"paraName\":\"加液量(ul)\",\"paraValue\":1000},{\"id\":3,\"paraName\":\"排废液(s)\",\"paraValue\":3}]', '0', '', '');
INSERT INTO `tprocess_para_copy1` VALUES ('297', '4', '3', '第一次清洗', 'L1086', '第三次摇床震荡孵育', 'L1106', '9', '3', '摇床工作', 'L1129', '[{\"id\":1,\"paraName\":\"摇床速度\",\"paraValue\":2},{\"id\":2,\"paraName\":\"震荡孵育时间(s)\",\"paraValue\":30},{\"id\":3,\"paraName\":\"X轴电机初始化\",\"paraValue\":1}]', '0', '', '');
INSERT INTO `tprocess_para_copy1` VALUES ('300', '4', '3', '第一次清洗', 'L1086', '第四次摇床电机初始化', 'L1104', '10', '1', '摇床电机初始化', 'L1060', '[{\"id\":1,\"paraName\":\"初始化延时时间(s)\",\"paraValue\":1000}]', '0', '', '');
INSERT INTO `tprocess_para_copy1` VALUES ('303', '4', '3', '第一次清洗', 'L1086', '第四次排废液及蠕动泵加液(洗涤缓冲液)', 'L1105', '11', '2', '排废液及蠕动泵加液', 'L1128', '[{\"id\":1,\"paraName\":\"RID\",\"paraValue\":9},{\"id\":2,\"paraName\":\"加液量(ul)\",\"paraValue\":1000},{\"id\":3,\"paraName\":\"排废液(s)\",\"paraValue\":3}]', '0', '', '');
INSERT INTO `tprocess_para_copy1` VALUES ('306', '4', '3', '第一次清洗', 'L1086', '第四次摇床震荡孵育', 'L1106', '12', '3', '摇床工作', 'L1129', '[{\"id\":1,\"paraName\":\"摇床速度\",\"paraValue\":2},{\"id\":2,\"paraName\":\"震荡孵育时间(s)\",\"paraValue\":30},{\"id\":3,\"paraName\":\"X轴电机初始化\",\"paraValue\":1}]', '0', '', '');
INSERT INTO `tprocess_para_copy1` VALUES ('309', '4', '3', '第一次清洗', 'L1086', '第五次摇床电机初始化', 'L1104', '13', '1', '摇床电机初始化', 'L1060', '[{\"id\":1,\"paraName\":\"初始化延时时间(s)\",\"paraValue\":1000}]', '0', '', '');
INSERT INTO `tprocess_para_copy1` VALUES ('312', '4', '3', '第一次清洗', 'L1086', '第五次排废液及蠕动泵加液(洗涤缓冲液)', 'L1105', '14', '2', '排废液及蠕动泵加液', 'L1128', '[{\"id\":1,\"paraName\":\"RID\",\"paraValue\":9},{\"id\":2,\"paraName\":\"加液量(ul)\",\"paraValue\":1000},{\"id\":3,\"paraName\":\"排废液(s)\",\"paraValue\":3}]', '0', '', '');
INSERT INTO `tprocess_para_copy1` VALUES ('315', '4', '3', '第一次清洗', 'L1086', '第五次摇床震荡孵育', 'L1106', '15', '3', '摇床工作', 'L1129', '[{\"id\":1,\"paraName\":\"摇床速度\",\"paraValue\":2},{\"id\":2,\"paraName\":\"震荡孵育时间(s)\",\"paraValue\":30},{\"id\":3,\"paraName\":\"X轴电机初始化\",\"paraValue\":1}]', '0', '', '');
INSERT INTO `tprocess_para_copy1` VALUES ('318', '4', '4', '加酶', 'L1087', '摇床电机初始化', 'L1060', '1', '1', '摇床电机初始化', 'L1060', '[{\"id\":1,\"paraName\":\"初始化延时时间(s)\",\"paraValue\":1000}]', '0', '', '');
INSERT INTO `tprocess_para_copy1` VALUES ('321', '4', '4', '加酶', 'L1087', '排废液及蠕动泵加液(结合物)', 'L1107', '2', '2', '排废液及蠕动泵加液', 'L1128', '[{\"id\":1,\"paraName\":\"RID\",\"paraValue\":-1},{\"id\":2,\"paraName\":\"加酶量(ul)\",\"paraValue\":1000},{\"id\":3,\"paraName\":\"排废液(s)\",\"paraValue\":3}]', '0', '', '');
INSERT INTO `tprocess_para_copy1` VALUES ('324', '4', '4', '加酶', 'L1087', '回流(结合物)', 'L1108', '3', '4', '蠕动泵回流', 'L1130', '[{\"id\":1,\"paraName\":\"回流\",\"paraValue\":-1},{\"id\":2,\"paraName\":\"回流体积\",\"paraValue\":3000}]', '0', '', '');
INSERT INTO `tprocess_para_copy1` VALUES ('327', '4', '4', '加酶', 'L1087', '摇床震荡孵育', 'L1094', '4', '3', '摇床工作', 'L1129', '[{\"id\":1,\"paraName\":\"摇床速度\",\"paraValue\":2},{\"id\":2,\"paraName\":\"震荡孵育时间(s)\",\"paraValue\":1800},{\"id\":3,\"paraName\":\"X轴电机初始化\",\"paraValue\":1}]', '0', '', '');
INSERT INTO `tprocess_para_copy1` VALUES ('330', '4', '5', '第二次清洗', 'L1088', '第一次摇床电机初始化', 'L1098', '1', '1', '摇床电机初始化', 'L1060', '[{\"id\":1,\"paraName\":\"初始化延时时间(s)\",\"paraValue\":1000}]', '0', '', '');
INSERT INTO `tprocess_para_copy1` VALUES ('333', '4', '5', '第二次清洗', 'L1088', '第一次排废液及蠕动泵加液(洗涤缓冲液)', 'L1099', '2', '2', '排废液及蠕动泵加液', 'L1128', '[{\"id\":1,\"paraName\":\"RID\",\"paraValue\":9},{\"id\":2,\"paraName\":\"加液量(ul)\",\"paraValue\":1000},{\"id\":3,\"paraName\":\"排废液(s)\",\"paraValue\":3}]', '0', '', '');
INSERT INTO `tprocess_para_copy1` VALUES ('336', '4', '5', '第二次清洗', 'L1088', '第一次摇床震荡孵育', 'L1100', '3', '3', '摇床工作', 'L1129', '[{\"id\":1,\"paraName\":\"摇床速度\",\"paraValue\":2},{\"id\":2,\"paraName\":\"震荡孵育时间(s)\",\"paraValue\":30},{\"id\":3,\"paraName\":\"X轴电机初始化\",\"paraValue\":1}]', '0', '', '');
INSERT INTO `tprocess_para_copy1` VALUES ('339', '4', '5', '第二次清洗', 'L1088', '第二次摇床电机初始化', 'L1101', '4', '1', '摇床电机初始化', 'L1060', '[{\"id\":1,\"paraName\":\"初始化延时时间(s)\",\"paraValue\":1000}]', '0', '', '');
INSERT INTO `tprocess_para_copy1` VALUES ('342', '4', '5', '第二次清洗', 'L1088', '第二次排废液及蠕动泵加液(洗涤缓冲液)', 'L1102', '5', '2', '排废液及蠕动泵加液', 'L1128', '[{\"id\":1,\"paraName\":\"RID\",\"paraValue\":9},{\"id\":2,\"paraName\":\"加液量(ul)\",\"paraValue\":1000},{\"id\":3,\"paraName\":\"排废液(s)\",\"paraValue\":3}]', '0', '', '');
INSERT INTO `tprocess_para_copy1` VALUES ('345', '4', '5', '第二次清洗', 'L1088', '第二次摇床震荡孵育', 'L1103', '6', '3', '摇床工作', 'L1129', '[{\"id\":1,\"paraName\":\"摇床速度\",\"paraValue\":2},{\"id\":2,\"paraName\":\"震荡孵育时间(s)\",\"paraValue\":30},{\"id\":3,\"paraName\":\"X轴电机初始化\",\"paraValue\":1}]', '0', '', '');
INSERT INTO `tprocess_para_copy1` VALUES ('348', '4', '5', '第二次清洗', 'L1088', '第三次摇床电机初始化', 'L1104', '7', '1', '摇床电机初始化', 'L1060', '[{\"id\":1,\"paraName\":\"初始化延时时间(s)\",\"paraValue\":1000}]', '0', '', '');
INSERT INTO `tprocess_para_copy1` VALUES ('351', '4', '5', '第二次清洗', 'L1088', '第三次排废液及蠕动泵加液(洗涤缓冲液)', 'L1105', '8', '2', '排废液及蠕动泵加液', 'L1128', '[{\"id\":1,\"paraName\":\"RID\",\"paraValue\":9},{\"id\":2,\"paraName\":\"加液量(ul)\",\"paraValue\":1000},{\"id\":3,\"paraName\":\"排废液(s)\",\"paraValue\":3}]', '0', '', '');
INSERT INTO `tprocess_para_copy1` VALUES ('354', '4', '5', '第二次清洗', 'L1088', '第三次摇床震荡孵育', 'L1106', '9', '3', '摇床工作', 'L1129', '[{\"id\":1,\"paraName\":\"摇床速度\",\"paraValue\":2},{\"id\":2,\"paraName\":\"震荡孵育时间(s)\",\"paraValue\":30},{\"id\":3,\"paraName\":\"X轴电机初始化\",\"paraValue\":1}]', '0', '', '');
INSERT INTO `tprocess_para_copy1` VALUES ('357', '4', '5', '第二次清洗', 'L1088', '第四次摇床电机初始化', 'L1098', '10', '1', '摇床电机初始化', 'L1060', '[{\"id\":1,\"paraName\":\"初始化延时时间(s)\",\"paraValue\":1000}]', '0', '', '');
INSERT INTO `tprocess_para_copy1` VALUES ('360', '4', '5', '第二次清洗', 'L1088', '第四次排废液及蠕动泵加液(洗涤缓冲液)', 'L1099', '11', '2', '排废液及蠕动泵加液', 'L1128', '[{\"id\":1,\"paraName\":\"RID\",\"paraValue\":9},{\"id\":2,\"paraName\":\"加液量(ul)\",\"paraValue\":1000},{\"id\":3,\"paraName\":\"排废液(s)\",\"paraValue\":3}]', '0', '', '');
INSERT INTO `tprocess_para_copy1` VALUES ('363', '4', '5', '第二次清洗', 'L1088', '第四次摇床震荡孵育', 'L1100', '12', '3', '摇床工作', 'L1129', '[{\"id\":1,\"paraName\":\"摇床速度\",\"paraValue\":2},{\"id\":2,\"paraName\":\"震荡孵育时间(s)\",\"paraValue\":30},{\"id\":3,\"paraName\":\"X轴电机初始化\",\"paraValue\":1}]', '0', '', '');
INSERT INTO `tprocess_para_copy1` VALUES ('366', '4', '5', '第二次清洗', 'L1088', '第五次摇床电机初始化', 'L1098', '13', '1', '摇床电机初始化', 'L1060', '[{\"id\":1,\"paraName\":\"初始化延时时间(s)\",\"paraValue\":1000}]', '0', '', '');
INSERT INTO `tprocess_para_copy1` VALUES ('369', '4', '5', '第二次清洗', 'L1088', '第五次排废液及蠕动泵加液(洗涤缓冲液)', 'L1099', '14', '2', '排废液及蠕动泵加液', 'L1128', '[{\"id\":1,\"paraName\":\"RID\",\"paraValue\":9},{\"id\":2,\"paraName\":\"加液量(ul)\",\"paraValue\":1000},{\"id\":3,\"paraName\":\"排废液(s)\",\"paraValue\":3}]', '0', '', '');
INSERT INTO `tprocess_para_copy1` VALUES ('372', '4', '5', '第二次清洗', 'L1088', '回流(洗涤缓冲液)', 'L1138', '15', '4', '蠕动泵回流', 'L1130', '[{\"id\":1,\"paraName\":\"回流\",\"paraValue\":9},{\"id\":2,\"paraName\":\"回流体积\",\"paraValue\":3000}]', '0', '', '');
INSERT INTO `tprocess_para_copy1` VALUES ('375', '4', '5', '第二次清洗', 'L1088', '第五次摇床震荡孵育', 'L1100', '16', '3', '摇床工作', 'L1129', '[{\"id\":1,\"paraName\":\"摇床速度\",\"paraValue\":2},{\"id\":2,\"paraName\":\"震荡孵育时间(s)\",\"paraValue\":30},{\"id\":3,\"paraName\":\"X轴电机初始化\",\"paraValue\":1}]', '0', '', '');
INSERT INTO `tprocess_para_copy1` VALUES ('378', '4', '6', '加底物', 'L1089', '摇床电机初始化', 'L1060', '1', '1', '摇床电机初始化', 'L1060', '[{\"id\":1,\"paraName\":\"初始化延时时间(s)\",\"paraValue\":1000}]', '0', '', '');
INSERT INTO `tprocess_para_copy1` VALUES ('381', '4', '6', '加底物', 'L1089', '排废液及蠕动泵加液(底物液)', 'L1110', '2', '2', '排废液及蠕动泵加液', 'L1128', '[{\"id\":1,\"paraName\":\"RID\",\"paraValue\":6},{\"id\":2,\"paraName\":\"加液量(ul)\",\"paraValue\":1000},{\"id\":3,\"paraName\":\"排废液(s)\",\"paraValue\":3}]', '0', '', '');
INSERT INTO `tprocess_para_copy1` VALUES ('384', '4', '6', '加底物', 'L1089', '回流(底物液)', 'L1111', '3', '4', '蠕动泵回流', 'L1130', '[{\"id\":1,\"paraName\":\"回流\",\"paraValue\":6},{\"id\":2,\"paraName\":\"回流体积\",\"paraValue\":3000}]', '0', '', '');
INSERT INTO `tprocess_para_copy1` VALUES ('387', '4', '6', '加底物', 'L1089', '摇床震荡孵育', 'L1094', '4', '3', '摇床工作', 'L1129', '[{\"id\":1,\"paraName\":\"摇床速度\",\"paraValue\":2},{\"id\":2,\"paraName\":\"震荡孵育时间(s)\",\"paraValue\":1200},{\"id\":3,\"paraName\":\"X轴电机初始化\",\"paraValue\":1}]', '0', '', '');
INSERT INTO `tprocess_para_copy1` VALUES ('390', '4', '7', '加蒸馏水', 'L1090', '摇床电机初始化', 'L1060', '1', '1', '摇床电机初始化', 'L1060', '[{\"id\":1,\"paraName\":\"初始化延时时间(s)\",\"paraValue\":1000}]', '0', '', '');
INSERT INTO `tprocess_para_copy1` VALUES ('393', '4', '7', '加蒸馏水', 'L1090', '排废液及加入蒸馏水', 'L1112', '2', '2', '排废液及蠕动泵加液', 'L1128', '[{\"id\":1,\"paraName\":\"RID\",\"paraValue\":8},{\"id\":2,\"paraName\":\"加液量(ul)\",\"paraValue\":1000},{\"id\":3,\"paraName\":\"排废液(s)\",\"paraValue\":3}]', '0', '', '');
INSERT INTO `tprocess_para_copy1` VALUES ('396', '4', '7', '加蒸馏水', 'L1090', '摇床震荡孵育', 'L1094', '3', '3', '摇床工作', 'L1129', '[{\"id\":1,\"paraName\":\"摇床速度\",\"paraValue\":2},{\"id\":2,\"paraName\":\"震荡孵育时间(s)\",\"paraValue\":30},{\"id\":3,\"paraName\":\"X轴电机初始化\",\"paraValue\":1}]', '0', '', '');
INSERT INTO `tprocess_para_copy1` VALUES ('399', '4', '7', '加蒸馏水', 'L1090', '摇床电机初始化', 'L1060', '4', '1', '摇床电机初始化', 'L1060', '[{\"id\":1,\"paraName\":\"初始化延时时间(s)\",\"paraValue\":1000}]', '0', '', '');
INSERT INTO `tprocess_para_copy1` VALUES ('402', '4', '7', '加蒸馏水', 'L1090', '排废液及加入蒸馏水', 'L1112', '5', '2', '排废液及蠕动泵加液', 'L1128', '[{\"id\":1,\"paraName\":\"RID\",\"paraValue\":8},{\"id\":2,\"paraName\":\"加液量(ul)\",\"paraValue\":1000},{\"id\":3,\"paraName\":\"排废液(s)\",\"paraValue\":3}]', '0', '', '');
INSERT INTO `tprocess_para_copy1` VALUES ('405', '4', '7', '加蒸馏水', 'L1090', '摇床震荡孵育', 'L1094', '6', '3', '摇床工作', 'L1129', '[{\"id\":1,\"paraName\":\"摇床速度\",\"paraValue\":2},{\"id\":2,\"paraName\":\"震荡孵育时间(s)\",\"paraValue\":30},{\"id\":3,\"paraName\":\"X轴电机初始化\",\"paraValue\":1}]', '0', '', '');
INSERT INTO `tprocess_para_copy1` VALUES ('408', '4', '7', '加蒸馏水', 'L1090', '摇床电机初始化', 'L1060', '7', '1', '摇床电机初始化', 'L1060', '[{\"id\":1,\"paraName\":\"初始化延时时间(s)\",\"paraValue\":1000}]', '0', '', '');
INSERT INTO `tprocess_para_copy1` VALUES ('411', '4', '7', '加蒸馏水', 'L1090', '排废液及加入蒸馏水', 'L1112', '8', '2', '排废液及蠕动泵加液', 'L1128', '[{\"id\":1,\"paraName\":\"RID\",\"paraValue\":8},{\"id\":2,\"paraName\":\"加液量(ul)\",\"paraValue\":1000},{\"id\":3,\"paraName\":\"排废液(s)\",\"paraValue\":3}]', '0', '', '');
INSERT INTO `tprocess_para_copy1` VALUES ('414', '4', '7', '加蒸馏水', 'L1090', '摇床震荡孵育', 'L1094', '9', '3', '摇床工作', 'L1129', '[{\"id\":1,\"paraName\":\"摇床速度\",\"paraValue\":2},{\"id\":2,\"paraName\":\"震荡孵育时间(s)\",\"paraValue\":30},{\"id\":3,\"paraName\":\"X轴电机初始化\",\"paraValue\":1}]', '0', '', '');
INSERT INTO `tprocess_para_copy1` VALUES ('417', '4', '7', '加蒸馏水', 'L1090', '摇床电机初始化', 'L1060', '10', '1', '摇床电机初始化', 'L1060', '[{\"id\":1,\"paraName\":\"初始化延时时间(s)\",\"paraValue\":1000}]', '0', '', '');
INSERT INTO `tprocess_para_copy1` VALUES ('420', '4', '7', '加蒸馏水', 'L1090', '排废液及加入蒸馏水', 'L1112', '11', '2', '排废液及蠕动泵加液', 'L1128', '[{\"id\":1,\"paraName\":\"RID\",\"paraValue\":8},{\"id\":2,\"paraName\":\"加液量(ul)\",\"paraValue\":1000},{\"id\":3,\"paraName\":\"排废液(s)\",\"paraValue\":3}]', '0', '', '');
INSERT INTO `tprocess_para_copy1` VALUES ('423', '4', '7', '加蒸馏水', 'L1090', '摇床震荡孵育', 'L1094', '12', '3', '摇床工作', 'L1129', '[{\"id\":1,\"paraName\":\"摇床速度\",\"paraValue\":2},{\"id\":2,\"paraName\":\"震荡孵育时间(s)\",\"paraValue\":30},{\"id\":3,\"paraName\":\"X轴电机初始化\",\"paraValue\":1}]', '0', '', '');
INSERT INTO `tprocess_para_copy1` VALUES ('426', '4', '7', '加蒸馏水', 'L1090', '摇床电机初始化', 'L1060', '13', '1', '摇床电机初始化', 'L1060', '[{\"id\":1,\"paraName\":\"初始化延时时间(s)\",\"paraValue\":1000}]', '0', '', '');
INSERT INTO `tprocess_para_copy1` VALUES ('429', '4', '7', '加蒸馏水', 'L1090', '排废液及加入蒸馏水', 'L1112', '14', '2', '排废液及蠕动泵加液', 'L1128', '[{\"id\":1,\"paraName\":\"RID\",\"paraValue\":8},{\"id\":2,\"paraName\":\"加液量(ul)\",\"paraValue\":1000},{\"id\":3,\"paraName\":\"排废液(s)\",\"paraValue\":3}]', '0', '', '');
INSERT INTO `tprocess_para_copy1` VALUES ('432', '4', '7', '加蒸馏水', 'L1088', '回流(加蒸馏水)', 'L1109', '15', '4', '蠕动泵回流', 'L1130', '[{\"id\":1,\"paraName\":\"回流\",\"paraValue\":8},{\"id\":2,\"paraName\":\"回流体积\",\"paraValue\":3000}]', '0', '', '');
INSERT INTO `tprocess_para_copy1` VALUES ('435', '4', '7', '加蒸馏水', 'L1090', '摇床震荡孵育', 'L1094', '15', '3', '摇床工作', 'L1129', '[{\"id\":1,\"paraName\":\"摇床速度\",\"paraValue\":2},{\"id\":2,\"paraName\":\"震荡孵育时间(s)\",\"paraValue\":30},{\"id\":3,\"paraName\":\"X轴电机初始化\",\"paraValue\":1}]', '0', '', '');
INSERT INTO `tprocess_para_copy1` VALUES ('438', '4', '9', '干燥', 'L1092', '摇床电机初始化', 'L1060', '1', '1', '摇床电机初始化', 'L1060', '[{\"id\":1,\"paraName\":\"初始化延时时间(s)\",\"paraValue\":1000}]', '0', '', '');
INSERT INTO `tprocess_para_copy1` VALUES ('441', '4', '9', '干燥', 'L1092', '排废液', 'L1115', '2', '2', '排废液及蠕动泵加液', 'L1128', '[{\"id\":1,\"paraName\":\"RID\",\"paraValue\":8},{\"id\":2,\"paraName\":\"加液量(ul)\",\"paraValue\":0},{\"id\":3,\"paraName\":\"排废液(s)\",\"paraValue\":3}]', '0', '', '');
INSERT INTO `tprocess_para_copy1` VALUES ('444', '4', '9', '干燥', 'L1092', '摇床震荡孵育', 'L1094', '1', '3', '摇床工作', 'L1129', '[{\"id\":1,\"paraName\":\"摇床速度\",\"paraValue\":2},{\"id\":2,\"paraName\":\"震荡孵育时间(s)\",\"paraValue\":7200},{\"id\":3,\"paraName\":\"X轴电机初始化\",\"paraValue\":1}]', '0', '', '');
INSERT INTO `tprocess_para_copy1` VALUES ('453', '5', '2', '加样本', 'L1085', '摇床电机初始化', 'L1060', '1', '1', '摇床电机初始化', 'L1060', '[{\"id\":1,\"paraName\":\"初始化延时时间(s)\",\"paraValue\":1000}]', '0', '', '');
INSERT INTO `tprocess_para_copy1` VALUES ('456', '5', '2', '加样本', 'L1085', '排废液及蠕动泵加液(稀释缓冲液)', 'L1095', '2', '2', '排废液及蠕动泵加液', 'L1128', '[{\"id\":1,\"paraName\":\"RID\",\"paraValue\":5},{\"id\":2,\"paraName\":\"加液量(ul)\",\"paraValue\":750},{\"id\":3,\"paraName\":\"排废液(s)\",\"paraValue\":3}]', '0', '', '');
INSERT INTO `tprocess_para_copy1` VALUES ('459', '5', '2', '加样本', 'L1085', '回流(稀释缓冲液回流)', 'L1096', '3', '4', '蠕动泵回流', 'L1130', '[{\"id\":1,\"paraName\":\"回流类型\",\"paraValue\":5},{\"id\":2,\"paraName\":\"回流体积\",\"paraValue\":3000}]', '0', '', '');
INSERT INTO `tprocess_para_copy1` VALUES ('462', '5', '2', '加样本', 'L1085', '样本臂移液', 'L1008', '4', '5', '样本臂移液', 'L1008', '[{\"id\":1,\"paraName\":\"加样量(ul)\",\"paraValue\":120}]', '0', '', '');
INSERT INTO `tprocess_para_copy1` VALUES ('465', '5', '2', '加样本', 'L1085', '样本臂移液', 'L1008', '5', '5', '样本臂移液', 'L1008', '[{\"id\":1,\"paraName\":\"加样量(ul)\",\"paraValue\":130}]', '0', '', '');
INSERT INTO `tprocess_para_copy1` VALUES ('468', '5', '2', '加样本', 'L1085', '摇床震荡孵育', 'L1094', '6', '3', '摇床工作', 'L1129', '[{\"id\":1,\"paraName\":\"摇床速度\",\"paraValue\":2},{\"id\":2,\"paraName\":\"震荡孵育时间(s)\",\"paraValue\":1800},{\"id\":3,\"paraName\":\"X轴电机初始化\",\"paraValue\":1}]', '0', '', '');
INSERT INTO `tprocess_para_copy1` VALUES ('471', '5', '3', '第一次清洗', 'L1086', '第一次摇床电机初始化', 'L1098', '1', '1', '摇床电机初始化', 'L1060', '[{\"id\":1,\"paraName\":\"初始化延时时间(s)\",\"paraValue\":1000}]', '0', '', '');
INSERT INTO `tprocess_para_copy1` VALUES ('474', '5', '3', '第一次清洗', 'L1086', '第一次排废液及蠕动泵加液(洗涤缓冲液)', 'L1099', '2', '2', '排废液及蠕动泵加液', 'L1128', '[{\"id\":1,\"paraName\":\"RID\",\"paraValue\":9},{\"id\":2,\"paraName\":\"加液量(ul)\",\"paraValue\":1000},{\"id\":3,\"paraName\":\"排废液(s)\",\"paraValue\":3}]', '0', '', '');
INSERT INTO `tprocess_para_copy1` VALUES ('477', '5', '3', '第一次清洗', 'L1086', '第一次摇床震荡孵育', 'L1100', '3', '3', '摇床工作', 'L1129', '[{\"id\":1,\"paraName\":\"摇床速度\",\"paraValue\":2},{\"id\":2,\"paraName\":\"震荡孵育时间(s)\",\"paraValue\":30},{\"id\":3,\"paraName\":\"X轴电机初始化\",\"paraValue\":1}]', '0', '', '');
INSERT INTO `tprocess_para_copy1` VALUES ('480', '5', '3', '第一次清洗', 'L1086', '第二次摇床电机初始化', 'L1101', '4', '1', '摇床电机初始化', 'L1060', '[{\"id\":1,\"paraName\":\"初始化延时时间(s)\",\"paraValue\":1000}]', '0', '', '');
INSERT INTO `tprocess_para_copy1` VALUES ('483', '5', '3', '第一次清洗', 'L1086', '第二次排废液及蠕动泵加液(洗涤缓冲液)', 'L1102', '5', '2', '排废液及蠕动泵加液', 'L1128', '[{\"id\":1,\"paraName\":\"RID\",\"paraValue\":9},{\"id\":2,\"paraName\":\"加液量(ul)\",\"paraValue\":1000},{\"id\":3,\"paraName\":\"排废液(s)\",\"paraValue\":3}]', '0', '', '');
INSERT INTO `tprocess_para_copy1` VALUES ('486', '5', '3', '第一次清洗', 'L1086', '第二次摇床震荡孵育', 'L1103', '6', '3', '摇床工作', 'L1129', '[{\"id\":1,\"paraName\":\"摇床速度\",\"paraValue\":2},{\"id\":2,\"paraName\":\"震荡孵育时间(s)\",\"paraValue\":30},{\"id\":3,\"paraName\":\"X轴电机初始化\",\"paraValue\":1}]', '0', '', '');
INSERT INTO `tprocess_para_copy1` VALUES ('489', '5', '3', '第一次清洗', 'L1086', '第三次摇床电机初始化', 'L1104', '7', '1', '摇床电机初始化', 'L1060', '[{\"id\":1,\"paraName\":\"初始化延时时间(s)\",\"paraValue\":1000}]', '0', '', '');
INSERT INTO `tprocess_para_copy1` VALUES ('492', '5', '3', '第一次清洗', 'L1086', '第三次排废液及蠕动泵加液(洗涤缓冲液)', 'L1105', '8', '2', '排废液及蠕动泵加液', 'L1128', '[{\"id\":1,\"paraName\":\"RID\",\"paraValue\":9},{\"id\":2,\"paraName\":\"加液量(ul)\",\"paraValue\":1000},{\"id\":3,\"paraName\":\"排废液(s)\",\"paraValue\":3}]', '0', '', '');
INSERT INTO `tprocess_para_copy1` VALUES ('495', '5', '3', '第一次清洗', 'L1086', '第三次摇床震荡孵育', 'L1106', '9', '3', '摇床工作', 'L1129', '[{\"id\":1,\"paraName\":\"摇床速度\",\"paraValue\":2},{\"id\":2,\"paraName\":\"震荡孵育时间(s)\",\"paraValue\":30},{\"id\":3,\"paraName\":\"X轴电机初始化\",\"paraValue\":1}]', '0', '', '');
INSERT INTO `tprocess_para_copy1` VALUES ('498', '5', '3', '第一次清洗', 'L1086', '第四次摇床电机初始化', 'L1132', '10', '1', '摇床电机初始化', 'L1060', '[{\"id\":1,\"paraName\":\"初始化延时时间(s)\",\"paraValue\":1000}]', '0', '', '');
INSERT INTO `tprocess_para_copy1` VALUES ('501', '5', '3', '第一次清洗', 'L1086', '第四次排废液及蠕动泵加液(洗涤缓冲液)', 'L1133', '11', '2', '排废液及蠕动泵加液', 'L1128', '[{\"id\":1,\"paraName\":\"RID\",\"paraValue\":9},{\"id\":2,\"paraName\":\"加液量(ul)\",\"paraValue\":1000},{\"id\":3,\"paraName\":\"排废液(s)\",\"paraValue\":3}]', '0', '', '');
INSERT INTO `tprocess_para_copy1` VALUES ('504', '5', '3', '第一次清洗', 'L1086', '第四次摇床震荡孵育', 'L1134', '12', '3', '摇床工作', 'L1129', '[{\"id\":1,\"paraName\":\"摇床速度\",\"paraValue\":2},{\"id\":2,\"paraName\":\"震荡孵育时间(s)\",\"paraValue\":30},{\"id\":3,\"paraName\":\"X轴电机初始化\",\"paraValue\":1}]', '0', '', '');
INSERT INTO `tprocess_para_copy1` VALUES ('507', '5', '3', '第一次清洗', 'L1086', '第五次摇床电机初始化', 'L1135', '13', '1', '摇床电机初始化', 'L1060', '[{\"id\":1,\"paraName\":\"初始化延时时间(s)\",\"paraValue\":1000}]', '0', '', '');
INSERT INTO `tprocess_para_copy1` VALUES ('510', '5', '3', '第一次清洗', 'L1086', '第五次排废液及蠕动泵加液(洗涤缓冲液)', 'L1136', '14', '2', '排废液及蠕动泵加液', 'L1128', '[{\"id\":1,\"paraName\":\"RID\",\"paraValue\":9},{\"id\":2,\"paraName\":\"加液量(ul)\",\"paraValue\":1000},{\"id\":3,\"paraName\":\"排废液(s)\",\"paraValue\":3}]', '0', '', '');
INSERT INTO `tprocess_para_copy1` VALUES ('513', '5', '3', '第一次清洗', 'L1086', '第五次摇床震荡孵育', 'L1137', '15', '3', '摇床工作', 'L1129', '[{\"id\":1,\"paraName\":\"摇床速度\",\"paraValue\":2},{\"id\":2,\"paraName\":\"震荡孵育时间(s)\",\"paraValue\":30},{\"id\":3,\"paraName\":\"X轴电机初始化\",\"paraValue\":1}]', '0', '', '');
INSERT INTO `tprocess_para_copy1` VALUES ('516', '5', '4', '加酶', 'L1087', '摇床电机初始化', 'L1060', '1', '1', '摇床电机初始化', 'L1060', '[{\"id\":1,\"paraName\":\"初始化延时时间(s)\",\"paraValue\":1000}]', '0', '', '');
INSERT INTO `tprocess_para_copy1` VALUES ('519', '5', '4', '加酶', 'L1087', '排废液及蠕动泵加液(结合物)', 'L1107', '2', '2', '排废液及蠕动泵加液', 'L1128', '[{\"id\":1,\"paraName\":\"RID\",\"paraValue\":-1},{\"id\":2,\"paraName\":\"加酶量(ul)\",\"paraValue\":1000},{\"id\":3,\"paraName\":\"排废液(s)\",\"paraValue\":3}]', '0', '', '');
INSERT INTO `tprocess_para_copy1` VALUES ('522', '5', '4', '加酶', 'L1087', '回流(结合物)', 'L1108', '3', '4', '蠕动泵回流', 'L1130', '[{\"id\":1,\"paraName\":\"回流\",\"paraValue\":-1},{\"id\":2,\"paraName\":\"回流体积\",\"paraValue\":3000}]', '0', '', '');
INSERT INTO `tprocess_para_copy1` VALUES ('525', '5', '4', '加酶', 'L1087', '摇床震荡孵育', 'L1094', '4', '3', '摇床工作', 'L1129', '[{\"id\":1,\"paraName\":\"摇床速度\",\"paraValue\":2},{\"id\":2,\"paraName\":\"震荡孵育时间(s)\",\"paraValue\":1800},{\"id\":3,\"paraName\":\"X轴电机初始化\",\"paraValue\":1}]', '0', '', '');
INSERT INTO `tprocess_para_copy1` VALUES ('528', '5', '5', '第二次清洗', 'L1088', '第一次摇床电机初始化', 'L1098', '1', '1', '摇床电机初始化', 'L1060', '[{\"id\":1,\"paraName\":\"初始化延时时间(s)\",\"paraValue\":1000}]', '0', '', '');
INSERT INTO `tprocess_para_copy1` VALUES ('531', '5', '5', '第二次清洗', 'L1088', '第一次排废液及蠕动泵加液(洗涤缓冲液)', 'L1099', '2', '2', '排废液及蠕动泵加液', 'L1128', '[{\"id\":1,\"paraName\":\"RID\",\"paraValue\":9},{\"id\":2,\"paraName\":\"加液量(ul)\",\"paraValue\":1000},{\"id\":3,\"paraName\":\"排废液(s)\",\"paraValue\":3}]', '0', '', '');
INSERT INTO `tprocess_para_copy1` VALUES ('534', '5', '5', '第二次清洗', 'L1088', '第一次摇床震荡孵育', 'L1100', '3', '3', '摇床工作', 'L1129', '[{\"id\":1,\"paraName\":\"摇床速度\",\"paraValue\":2},{\"id\":2,\"paraName\":\"震荡孵育时间(s)\",\"paraValue\":30},{\"id\":3,\"paraName\":\"X轴电机初始化\",\"paraValue\":1}]', '0', '', '');
INSERT INTO `tprocess_para_copy1` VALUES ('537', '5', '5', '第二次清洗', 'L1088', '第二次摇床电机初始化', 'L1101', '4', '1', '摇床电机初始化', 'L1060', '[{\"id\":1,\"paraName\":\"初始化延时时间(s)\",\"paraValue\":1000}]', '0', '', '');
INSERT INTO `tprocess_para_copy1` VALUES ('540', '5', '5', '第二次清洗', 'L1088', '第二次排废液及蠕动泵加液(洗涤缓冲液)', 'L1102', '5', '2', '排废液及蠕动泵加液', 'L1128', '[{\"id\":1,\"paraName\":\"RID\",\"paraValue\":9},{\"id\":2,\"paraName\":\"加液量(ul)\",\"paraValue\":1000},{\"id\":3,\"paraName\":\"排废液(s)\",\"paraValue\":3}]', '0', '', '');
INSERT INTO `tprocess_para_copy1` VALUES ('543', '5', '5', '第二次清洗', 'L1088', '第二次摇床震荡孵育', 'L1103', '6', '3', '摇床工作', 'L1129', '[{\"id\":1,\"paraName\":\"摇床速度\",\"paraValue\":2},{\"id\":2,\"paraName\":\"震荡孵育时间(s)\",\"paraValue\":30},{\"id\":3,\"paraName\":\"X轴电机初始化\",\"paraValue\":1}]', '0', '', '');
INSERT INTO `tprocess_para_copy1` VALUES ('546', '5', '5', '第二次清洗', 'L1088', '第三次摇床电机初始化', 'L1104', '7', '1', '摇床电机初始化', 'L1060', '[{\"id\":1,\"paraName\":\"初始化延时时间(s)\",\"paraValue\":1000}]', '0', '', '');
INSERT INTO `tprocess_para_copy1` VALUES ('549', '5', '5', '第二次清洗', 'L1088', '第三次排废液及蠕动泵加液(洗涤缓冲液)', 'L1105', '8', '2', '排废液及蠕动泵加液', 'L1128', '[{\"id\":1,\"paraName\":\"RID\",\"paraValue\":9},{\"id\":2,\"paraName\":\"加液量(ul)\",\"paraValue\":1000},{\"id\":3,\"paraName\":\"排废液(s)\",\"paraValue\":3}]', '0', '', '');
INSERT INTO `tprocess_para_copy1` VALUES ('552', '5', '5', '第二次清洗', 'L1088', '第三次摇床震荡孵育', 'L1106', '9', '3', '摇床工作', 'L1129', '[{\"id\":1,\"paraName\":\"摇床速度\",\"paraValue\":2},{\"id\":2,\"paraName\":\"震荡孵育时间(s)\",\"paraValue\":30},{\"id\":3,\"paraName\":\"X轴电机初始化\",\"paraValue\":1}]', '0', '', '');
INSERT INTO `tprocess_para_copy1` VALUES ('555', '5', '5', '第二次清洗', 'L1088', '第四次摇床电机初始化', 'L1132', '10', '1', '摇床电机初始化', 'L1060', '[{\"id\":1,\"paraName\":\"初始化延时时间(s)\",\"paraValue\":1000}]', '0', '', '');
INSERT INTO `tprocess_para_copy1` VALUES ('558', '5', '5', '第二次清洗', 'L1088', '第四次排废液及蠕动泵加液(洗涤缓冲液)', 'L1133', '11', '2', '排废液及蠕动泵加液', 'L1128', '[{\"id\":1,\"paraName\":\"RID\",\"paraValue\":9},{\"id\":2,\"paraName\":\"加液量(ul)\",\"paraValue\":1000},{\"id\":3,\"paraName\":\"排废液(s)\",\"paraValue\":3}]', '0', '', '');
INSERT INTO `tprocess_para_copy1` VALUES ('561', '5', '5', '第二次清洗', 'L1088', '第四次摇床震荡孵育', 'L1134', '12', '3', '摇床工作', 'L1129', '[{\"id\":1,\"paraName\":\"摇床速度\",\"paraValue\":2},{\"id\":2,\"paraName\":\"震荡孵育时间(s)\",\"paraValue\":30},{\"id\":3,\"paraName\":\"X轴电机初始化\",\"paraValue\":1}]', '0', '', '');
INSERT INTO `tprocess_para_copy1` VALUES ('564', '5', '5', '第二次清洗', 'L1088', '第五次摇床电机初始化', 'L1135', '13', '1', '摇床电机初始化', 'L1060', '[{\"id\":1,\"paraName\":\"初始化延时时间(s)\",\"paraValue\":1000}]', '0', '', '');
INSERT INTO `tprocess_para_copy1` VALUES ('567', '5', '5', '第二次清洗', 'L1088', '第五次排废液及蠕动泵加液(洗涤缓冲液)', 'L1136', '14', '2', '排废液及蠕动泵加液', 'L1128', '[{\"id\":1,\"paraName\":\"RID\",\"paraValue\":9},{\"id\":2,\"paraName\":\"加液量(ul)\",\"paraValue\":1000},{\"id\":3,\"paraName\":\"排废液(s)\",\"paraValue\":3}]', '0', '', '');
INSERT INTO `tprocess_para_copy1` VALUES ('570', '5', '5', '第二次清洗', 'L1088', '回流(洗涤缓冲液)', 'L1138', '15', '4', '蠕动泵回流', 'L1130', '[{\"id\":1,\"paraName\":\"回流\",\"paraValue\":9},{\"id\":2,\"paraName\":\"回流体积\",\"paraValue\":3000}]', '0', '', '');
INSERT INTO `tprocess_para_copy1` VALUES ('573', '5', '5', '第二次清洗', 'L1088', '第五次摇床震荡孵育', 'L1137', '16', '3', '摇床工作', 'L1129', '[{\"id\":1,\"paraName\":\"摇床速度\",\"paraValue\":2},{\"id\":2,\"paraName\":\"震荡孵育时间(s)\",\"paraValue\":30},{\"id\":3,\"paraName\":\"X轴电机初始化\",\"paraValue\":1}]', '0', '', '');
INSERT INTO `tprocess_para_copy1` VALUES ('576', '5', '6', '加底物', 'L1089', '摇床电机初始化', 'L1060', '1', '1', '摇床电机初始化', 'L1060', '[{\"id\":1,\"paraName\":\"初始化延时时间(s)\",\"paraValue\":1000}]', '0', '', '');
INSERT INTO `tprocess_para_copy1` VALUES ('579', '5', '6', '加底物', 'L1089', '排废液及蠕动泵加液(底物液)', 'L1110', '2', '2', '排废液及蠕动泵加液', 'L1128', '[{\"id\":1,\"paraName\":\"RID\",\"paraValue\":6},{\"id\":2,\"paraName\":\"加液量(ul)\",\"paraValue\":1000},{\"id\":3,\"paraName\":\"排废液(s)\",\"paraValue\":3}]', '0', '', '');
INSERT INTO `tprocess_para_copy1` VALUES ('582', '5', '6', '加底物', 'L1089', '回流(底物液)', 'L1111', '3', '4', '蠕动泵回流', 'L1130', '[{\"id\":1,\"paraName\":\"回流\",\"paraValue\":6},{\"id\":2,\"paraName\":\"回流体积\",\"paraValue\":3000}]', '0', '', '');
INSERT INTO `tprocess_para_copy1` VALUES ('585', '5', '6', '加底物', 'L1089', '摇床震荡孵育', 'L1094', '4', '3', '摇床工作', 'L1129', '[{\"id\":1,\"paraName\":\"摇床速度\",\"paraValue\":2},{\"id\":2,\"paraName\":\"震荡孵育时间(s)\",\"paraValue\":1200},{\"id\":3,\"paraName\":\"X轴电机初始化\",\"paraValue\":1}]', '0', '', '');
INSERT INTO `tprocess_para_copy1` VALUES ('588', '5', '7', '加蒸馏水', 'L1090', '摇床电机初始化', 'L1060', '1', '1', '摇床电机初始化', 'L1060', '[{\"id\":1,\"paraName\":\"初始化延时时间(s)\",\"paraValue\":1000}]', '0', '', '');
INSERT INTO `tprocess_para_copy1` VALUES ('591', '5', '7', '加蒸馏水', 'L1090', '排废液及加入蒸馏水', 'L1112', '2', '2', '排废液及蠕动泵加液', 'L1128', '[{\"id\":1,\"paraName\":\"RID\",\"paraValue\":8},{\"id\":2,\"paraName\":\"加液量(ul)\",\"paraValue\":1000},{\"id\":3,\"paraName\":\"排废液(s)\",\"paraValue\":3}]', '0', '', '');
INSERT INTO `tprocess_para_copy1` VALUES ('594', '5', '7', '加蒸馏水', 'L1090', '摇床震荡孵育', 'L1094', '3', '3', '摇床工作', 'L1129', '[{\"id\":1,\"paraName\":\"摇床速度\",\"paraValue\":2},{\"id\":2,\"paraName\":\"震荡孵育时间(s)\",\"paraValue\":30},{\"id\":3,\"paraName\":\"X轴电机初始化\",\"paraValue\":1}]', '0', '', '');
INSERT INTO `tprocess_para_copy1` VALUES ('597', '5', '7', '加蒸馏水', 'L1090', '摇床电机初始化', 'L1060', '4', '1', '摇床电机初始化', 'L1060', '[{\"id\":1,\"paraName\":\"初始化延时时间(s)\",\"paraValue\":1000}]', '0', '', '');
INSERT INTO `tprocess_para_copy1` VALUES ('600', '5', '7', '加蒸馏水', 'L1090', '排废液及加入蒸馏水', 'L1112', '5', '2', '排废液及蠕动泵加液', 'L1128', '[{\"id\":1,\"paraName\":\"RID\",\"paraValue\":8},{\"id\":2,\"paraName\":\"加液量(ul)\",\"paraValue\":1000},{\"id\":3,\"paraName\":\"排废液(s)\",\"paraValue\":3}]', '0', '', '');
INSERT INTO `tprocess_para_copy1` VALUES ('603', '5', '7', '加蒸馏水', 'L1090', '摇床震荡孵育', 'L1094', '6', '3', '摇床工作', 'L1129', '[{\"id\":1,\"paraName\":\"摇床速度\",\"paraValue\":2},{\"id\":2,\"paraName\":\"震荡孵育时间(s)\",\"paraValue\":30},{\"id\":3,\"paraName\":\"X轴电机初始化\",\"paraValue\":1}]', '0', '', '');
INSERT INTO `tprocess_para_copy1` VALUES ('606', '5', '7', '加蒸馏水', 'L1090', '摇床电机初始化', 'L1060', '7', '1', '摇床电机初始化', 'L1060', '[{\"id\":1,\"paraName\":\"初始化延时时间(s)\",\"paraValue\":1000}]', '0', '', '');
INSERT INTO `tprocess_para_copy1` VALUES ('609', '5', '7', '加蒸馏水', 'L1090', '排废液及加入蒸馏水', 'L1112', '8', '2', '排废液及蠕动泵加液', 'L1128', '[{\"id\":1,\"paraName\":\"RID\",\"paraValue\":8},{\"id\":2,\"paraName\":\"加液量(ul)\",\"paraValue\":1000},{\"id\":3,\"paraName\":\"排废液(s)\",\"paraValue\":3}]', '0', '', '');
INSERT INTO `tprocess_para_copy1` VALUES ('612', '5', '7', '加蒸馏水', 'L1090', '摇床震荡孵育', 'L1094', '9', '3', '摇床工作', 'L1129', '[{\"id\":1,\"paraName\":\"摇床速度\",\"paraValue\":2},{\"id\":2,\"paraName\":\"震荡孵育时间(s)\",\"paraValue\":30},{\"id\":3,\"paraName\":\"X轴电机初始化\",\"paraValue\":1}]', '0', '', '');
INSERT INTO `tprocess_para_copy1` VALUES ('615', '5', '7', '加蒸馏水', 'L1090', '摇床电机初始化', 'L1060', '10', '1', '摇床电机初始化', 'L1060', '[{\"id\":1,\"paraName\":\"初始化延时时间(s)\",\"paraValue\":1000}]', '0', '', '');
INSERT INTO `tprocess_para_copy1` VALUES ('618', '5', '7', '加蒸馏水', 'L1090', '排废液及加入蒸馏水', 'L1112', '11', '2', '排废液及蠕动泵加液', 'L1128', '[{\"id\":1,\"paraName\":\"RID\",\"paraValue\":8},{\"id\":2,\"paraName\":\"加液量(ul)\",\"paraValue\":1000},{\"id\":3,\"paraName\":\"排废液(s)\",\"paraValue\":3}]', '0', '', '');
INSERT INTO `tprocess_para_copy1` VALUES ('621', '5', '7', '加蒸馏水', 'L1090', '摇床震荡孵育', 'L1094', '12', '3', '摇床工作', 'L1129', '[{\"id\":1,\"paraName\":\"摇床速度\",\"paraValue\":2},{\"id\":2,\"paraName\":\"震荡孵育时间(s)\",\"paraValue\":30},{\"id\":3,\"paraName\":\"X轴电机初始化\",\"paraValue\":1}]', '0', '', '');
INSERT INTO `tprocess_para_copy1` VALUES ('624', '5', '7', '加蒸馏水', 'L1090', '摇床电机初始化', 'L1060', '13', '1', '摇床电机初始化', 'L1060', '[{\"id\":1,\"paraName\":\"初始化延时时间(s)\",\"paraValue\":1000}]', '0', '', '');
INSERT INTO `tprocess_para_copy1` VALUES ('627', '5', '7', '加蒸馏水', 'L1090', '排废液及加入蒸馏水', 'L1112', '14', '2', '排废液及蠕动泵加液', 'L1128', '[{\"id\":1,\"paraName\":\"RID\",\"paraValue\":8},{\"id\":2,\"paraName\":\"加液量(ul)\",\"paraValue\":1000},{\"id\":3,\"paraName\":\"排废液(s)\",\"paraValue\":3}]', '0', '', '');
INSERT INTO `tprocess_para_copy1` VALUES ('630', '5', '7', '加蒸馏水', 'L1088', '回流(加蒸馏水)', 'L1109', '15', '4', '蠕动泵回流', 'L1130', '[{\"id\":1,\"paraName\":\"回流\",\"paraValue\":8},{\"id\":2,\"paraName\":\"回流体积\",\"paraValue\":3000}]', '0', '', '');
INSERT INTO `tprocess_para_copy1` VALUES ('633', '5', '7', '加蒸馏水', 'L1090', '摇床震荡孵育', 'L1094', '15', '3', '摇床工作', 'L1129', '[{\"id\":1,\"paraName\":\"摇床速度\",\"paraValue\":2},{\"id\":2,\"paraName\":\"震荡孵育时间(s)\",\"paraValue\":30},{\"id\":3,\"paraName\":\"X轴电机初始化\",\"paraValue\":1}]', '0', '', '');
INSERT INTO `tprocess_para_copy1` VALUES ('636', '5', '9', '干燥', 'L1092', '摇床电机初始化', 'L1060', '1', '1', '摇床电机初始化', 'L1060', '[{\"id\":1,\"paraName\":\"初始化延时时间(s)\",\"paraValue\":1000}]', '0', '', '');
INSERT INTO `tprocess_para_copy1` VALUES ('639', '5', '9', '干燥', 'L1092', '排废液', 'L1115', '2', '2', '排废液及蠕动泵加液', 'L1128', '[{\"id\":1,\"paraName\":\"RID\",\"paraValue\":8},{\"id\":2,\"paraName\":\"加液量(ul)\",\"paraValue\":0},{\"id\":3,\"paraName\":\"排废液(s)\",\"paraValue\":3}]', '0', '', '');
INSERT INTO `tprocess_para_copy1` VALUES ('642', '5', '9', '干燥', 'L1092', '摇床震荡孵育', 'L1094', '1', '3', '摇床工作', 'L1129', '[{\"id\":1,\"paraName\":\"摇床速度\",\"paraValue\":2},{\"id\":2,\"paraName\":\"震荡孵育时间(s)\",\"paraValue\":7200},{\"id\":3,\"paraName\":\"X轴电机初始化\",\"paraValue\":1}]', '0', '', '');

-- ----------------------------
-- Table structure for tprocess_reagent
-- ----------------------------
DROP TABLE IF EXISTS `tprocess_reagent`;
CREATE TABLE `tprocess_reagent` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `processParaId` int(11) DEFAULT '0' COMMENT 'tprocess_para',
  `paperId` int(11) DEFAULT '0',
  `reagentId` int(11) DEFAULT '0',
  PRIMARY KEY (`id`) USING BTREE
) ENGINE=InnoDB AUTO_INCREMENT=29 DEFAULT CHARSET=utf8 ROW_FORMAT=DYNAMIC;

-- ----------------------------
-- Records of tprocess_reagent
-- ----------------------------
INSERT INTO `tprocess_reagent` VALUES ('1', '13', '1', '1');
INSERT INTO `tprocess_reagent` VALUES ('2', '13', '2', '2');
INSERT INTO `tprocess_reagent` VALUES ('3', '13', '3', '3');
INSERT INTO `tprocess_reagent` VALUES ('4', '14', '1', '1');
INSERT INTO `tprocess_reagent` VALUES ('5', '14', '2', '2');
INSERT INTO `tprocess_reagent` VALUES ('6', '14', '3', '3');
INSERT INTO `tprocess_reagent` VALUES ('14', '1', '1', '9');
INSERT INTO `tprocess_reagent` VALUES ('15', '1', '2', '9');
INSERT INTO `tprocess_reagent` VALUES ('16', '1', '3', '9');
INSERT INTO `tprocess_reagent` VALUES ('17', '13', '17', '17');
INSERT INTO `tprocess_reagent` VALUES ('18', '13', '18', '18');
INSERT INTO `tprocess_reagent` VALUES ('19', '13', '19', '16');
INSERT INTO `tprocess_reagent` VALUES ('20', '13', '20', '19');
INSERT INTO `tprocess_reagent` VALUES ('21', '14', '17', '17');
INSERT INTO `tprocess_reagent` VALUES ('22', '14', '18', '18');
INSERT INTO `tprocess_reagent` VALUES ('23', '14', '19', '16');
INSERT INTO `tprocess_reagent` VALUES ('24', '14', '20', '19');
INSERT INTO `tprocess_reagent` VALUES ('25', '1', '17', '17');
INSERT INTO `tprocess_reagent` VALUES ('26', '1', '18', '18');
INSERT INTO `tprocess_reagent` VALUES ('27', '1', '19', '16');
INSERT INTO `tprocess_reagent` VALUES ('28', '1', '20', '19');

-- ----------------------------
-- Table structure for tprocess_step
-- ----------------------------
DROP TABLE IF EXISTS `tprocess_step`;
CREATE TABLE `tprocess_step` (
  `id` int(10) unsigned NOT NULL,
  `tName` varchar(64) NOT NULL,
  `templatePara` varchar(511) DEFAULT '',
  `actTime` int(11) DEFAULT '0' COMMENT 'ms',
  `remark` varchar(255) DEFAULT '',
  PRIMARY KEY (`id`) USING BTREE
) ENGINE=InnoDB DEFAULT CHARSET=utf8 ROW_FORMAT=DYNAMIC;

-- ----------------------------
-- Records of tprocess_step
-- ----------------------------
INSERT INTO `tprocess_step` VALUES ('1', '排废液及蠕动泵加液', '[{\"id\":1,\"paraName\":\"试剂ID\",\"paraValue\":-1},{\"id\":2,\"paraName\":\"加液量(ul)\",\"paraValue\":-1},{\"id\":3,\"paraName\":\"排废液(s)\",\"paraValue\":-1}]', '2000', '');
INSERT INTO `tprocess_step` VALUES ('2', '摇床震荡孵育', '[{\"id\":1,\"paraName\":\"摇床速度\",\"paraValue\":-1},{\"id\":2,\"paraName\":\"震荡孵育时间(s)\",\"paraValue\":-1}]', '0', '');
INSERT INTO `tprocess_step` VALUES ('3', '回流', '[{\"id\":1,\"paraName\":\"回流类型\",\"paraValue\":-1},{\"id\":2,\"paraName\":\"回流体积\",\"paraValue\":-1}]', '3769', '');
INSERT INTO `tprocess_step` VALUES ('4', '样本臂移液', '[{\"id\":1,\"paraName\":\"加样量\",\"paraValue\":-1}]', '25741', '');
INSERT INTO `tprocess_step` VALUES ('5', '干燥', '[{\"id\":1,\"paraName\":\"时间\",\"paraValue\":-1},{\"id\":2,\"paraName\":\"是否加热\",\"paraValue\":-1},{\"id\":3,\"paraName\":\"控制温度\",\"paraValue\":-1},{\"id\":4,\"paraName\":\"风扇速度\",\"paraValue\":-1},{\"id\":5,\"paraName\":\"摇床速度\",\"paraValue\":-1},{\"id\":6,\"paraName\":\"风扇时间(s)\",\"paraValue\":-1},{\"id\":7,\"paraName\":\"\",\"paraValue\":-1}]', '0', '');
INSERT INTO `tprocess_step` VALUES ('6', '摇床初始化', '[]', '0', '');

-- ----------------------------
-- Table structure for treagent
-- ----------------------------
DROP TABLE IF EXISTS `treagent`;
CREATE TABLE `treagent` (
  `ID` int(10) unsigned NOT NULL AUTO_INCREMENT,
  `reagentName` varchar(63) NOT NULL DEFAULT '0',
  `TestPaperID` int(10) DEFAULT NULL,
  `companyID` int(10) unsigned NOT NULL DEFAULT '0',
  `IsNoDrip` tinyint(1) unsigned NOT NULL DEFAULT '0',
  `IsSkimp` tinyint(1) unsigned NOT NULL DEFAULT '0',
  `IsNeedPrepare` tinyint(1) unsigned NOT NULL DEFAULT '0',
  `PumpNo` int(10) DEFAULT '-1',
  `fluidMeasureSmall` float(255,6) DEFAULT '0.300000' COMMENT '小冲灌',
  `fluidMeasure` float(20,6) DEFAULT NULL COMMENT '液量（大冲灌）',
  `spentTime` varchar(20) DEFAULT NULL COMMENT '耗时',
  `flushing_type` tinyint(4) DEFAULT '0' COMMENT '冲灌类型，0为大，1为小',
  PRIMARY KEY (`ID`) USING BTREE
) ENGINE=InnoDB AUTO_INCREMENT=40 DEFAULT CHARSET=utf8 ROW_FORMAT=DYNAMIC;

-- ----------------------------
-- Records of treagent
-- ----------------------------
INSERT INTO `treagent` VALUES ('1', 'ANA-LIA(12)-CON', '1', '1', '1', '1', '1', '0', '0.200000', '3.000000', '3', '0');
INSERT INTO `treagent` VALUES ('2', 'ANA-LIA-2(9N)-CON', '2', '1', '1', '1', '1', '3', '0.200000', '3.000000', '3', '0');
INSERT INTO `treagent` VALUES ('3', 'ANA-LIA-1(9D)-CON', '3', '1', '1', '1', '1', '2', '0.200000', '3.000000', '3', '0');
INSERT INTO `treagent` VALUES ('5', 'K1693', '111', '0', '0', '0', '0', '4', '0.200000', '3.000000', '3', '0');
INSERT INTO `treagent` VALUES ('6', 'K1691', '111', '0', '0', '0', '0', '5', '0.200000', '3.000000', '3', '0');
INSERT INTO `treagent` VALUES ('7', 'K1694', '111', '0', '0', '0', '0', '6', '0.200000', '3.000000', '3', '0');
INSERT INTO `treagent` VALUES ('8', 'K1692', '111', '0', '0', '0', '0', '7', '0.200000', '3.000000', '3', '0');
INSERT INTO `treagent` VALUES ('9', 'K1695', '111', '0', '0', '0', '0', '8', '0.200000', '3.000000', '3', '0');
INSERT INTO `treagent` VALUES ('10', 'K1696', '111', '0', '0', '0', '0', '-1', '0.200000', '3.000000', '3', '0');
INSERT INTO `treagent` VALUES ('12', 'ANCA_E', '21', '2', '1', '1', '1', '1', '0.200000', '3.000000', '3', '0');
INSERT INTO `treagent` VALUES ('16', 'ANA LIA Maxx-CON', '19', '1', '1', '1', '1', '1', '0.200000', '3.000000', '3', '0');
INSERT INTO `treagent` VALUES ('18', 'Liver-LIA-CON', '18', '1', '1', '1', '1', '0', '0.200000', '3.000000', '3', '0');
INSERT INTO `treagent` VALUES ('19', 'Vasculitis-LIA-CON', '20', '1', '1', '1', '1', '3', '0.200000', '3.000000', '3', '0');
INSERT INTO `treagent` VALUES ('20', 'ANA_E', '22', '2', '1', '1', '1', '0', '0.200000', '3.000000', '3', '0');
INSERT INTO `treagent` VALUES ('21', 'ALD_E', '24', '2', '1', '1', '0', '2', '0.200000', '3.000000', '3', '0');
INSERT INTO `treagent` VALUES ('22', 'MYO_E', '25', '2', '1', '1', '1', '3', '0.200000', '3.000000', '3', '0');
INSERT INTO `treagent` VALUES ('23', 'MYO-25_E', '27', '2', '1', '1', '0', '3', '0.200000', '3.000000', '3', '0');
INSERT INTO `treagent` VALUES ('24', 'ANA-18_E', '28', '2', '1', '1', '0', '0', '0.200000', '3.000000', '3', '0');
INSERT INTO `treagent` VALUES ('25', 'ANA-17_E', '29', '2', '1', '1', '0', '0', '0.200000', '3.000000', '3', '0');
INSERT INTO `treagent` VALUES ('26', 'ANA-15_E', '30', '2', '1', '1', '0', '0', '0.200000', '3.000000', '3', '0');
INSERT INTO `treagent` VALUES ('27', 'ANA-13_E', '31', '2', '1', '1', '0', '0', '0.200000', '3.000000', '3', '0');
INSERT INTO `treagent` VALUES ('28', 'ANA-12_E', '32', '2', '1', '1', '0', '0', '0.200000', '3.000000', '3', '0');
INSERT INTO `treagent` VALUES ('29', 'ANA-9N_E', '33', '2', '1', '1', '0', '0', '0.200000', '3.000000', '3', '0');
INSERT INTO `treagent` VALUES ('30', 'ANA-9D_E', '34', '2', '1', '1', '0', '0', '0.200000', '3.000000', '3', '0');
INSERT INTO `treagent` VALUES ('31', 'ANA-7_E', '35', '2', '1', '1', '0', '0', '0.200000', '3.000000', '3', '0');
INSERT INTO `treagent` VALUES ('32', 'Vasculitis-LIA', '926', '3', '1', '1', '1', '0', '1.000000', '1.000000', null, '0');
INSERT INTO `treagent` VALUES ('33', 'ANA LIA Maxx', '921', '3', '1', '1', '1', '1', '1.000000', '1.000000', null, '0');
INSERT INTO `treagent` VALUES ('34', '9D', '922', '3', '0', '0', '0', '0', '1.000000', '1.000000', null, '0');
INSERT INTO `treagent` VALUES ('35', '9N', '923', '3', '1', '1', '1', '3', '1.000000', '1.000000', null, '0');
INSERT INTO `treagent` VALUES ('36', 'ANA-LIA12', '924', '3', '1', '1', '1', '2', '1.000000', '1.000000', null, '0');
INSERT INTO `treagent` VALUES ('37', 'Liver-LIA', '925', '3', '0', '0', '0', '3', '1.000000', '1.000000', null, '0');
INSERT INTO `treagent` VALUES ('38', 'PNS14-serum', '927', '4', '0', '0', '0', '0', '0.200000', '3.000000', null, '0');
INSERT INTO `treagent` VALUES ('39', 'PNS14-cerebrofluid', '928', '5', '0', '0', '0', '0', '0.200000', '3.000000', null, '0');

-- ----------------------------
-- Table structure for tremark
-- ----------------------------
DROP TABLE IF EXISTS `tremark`;
CREATE TABLE `tremark` (
  `ID` int(10) unsigned NOT NULL AUTO_INCREMENT,
  `strRemark` text NOT NULL,
  `RemarkRK` varchar(255) DEFAULT '',
  `shortKey` varchar(32) DEFAULT '',
  PRIMARY KEY (`ID`) USING BTREE,
  UNIQUE KEY `ID_UNIQUE` (`ID`) USING BTREE,
  UNIQUE KEY `shortKey_UNIQUE` (`shortKey`) USING BTREE
) ENGINE=InnoDB AUTO_INCREMENT=2 DEFAULT CHARSET=utf8 ROW_FORMAT=DYNAMIC COMMENT='医院科室表。';

-- ----------------------------
-- Records of tremark
-- ----------------------------
INSERT INTO `tremark` VALUES ('1', '测试数据1111', '', 'cs');

-- ----------------------------
-- Table structure for tresult_left_right_pixp
-- ----------------------------
DROP TABLE IF EXISTS `tresult_left_right_pixp`;
CREATE TABLE `tresult_left_right_pixp` (
  `pkid` int(25) NOT NULL AUTO_INCREMENT,
  `test_id` varchar(100) NOT NULL,
  `left_pix_position` int(11) NOT NULL,
  `right_pix_position` int(11) NOT NULL,
  `position_index` int(11) NOT NULL DEFAULT '0',
  `create_time` datetime DEFAULT CURRENT_TIMESTAMP,
  `projectName` varchar(255) DEFAULT NULL,
  `height` int(11) NOT NULL,
  `top` int(11) NOT NULL,
  PRIMARY KEY (`pkid`) USING BTREE
) ENGINE=InnoDB DEFAULT CHARSET=utf8 ROW_FORMAT=DYNAMIC;

-- ----------------------------
-- Records of tresult_left_right_pixp
-- ----------------------------

-- ----------------------------
-- Table structure for tsample
-- ----------------------------
DROP TABLE IF EXISTS `tsample`;
CREATE TABLE `tsample` (
  `pkid` int(11) NOT NULL AUTO_INCREMENT,
  `Id` varchar(20) NOT NULL,
  `testId` varchar(64) DEFAULT NULL COMMENT '测试编号',
  `sampleNo` varchar(64) DEFAULT '' COMMENT '样本编号',
  `samplePos` tinyint(255) NOT NULL DEFAULT '0' COMMENT '样本位置（1-72）',
  `paperId` varchar(10) DEFAULT NULL COMMENT '模条编号',
  `paperPos` tinyint(255) NOT NULL COMMENT '模条位置（1-72）',
  `barcode` varchar(255) DEFAULT '' COMMENT '样本条码',
  `PatientName` varchar(64) DEFAULT '' COMMENT '病人姓名。',
  `SexID` int(10) unsigned DEFAULT '0' COMMENT '病人性别ID。',
  `Age` int(10) DEFAULT '-1' COMMENT '病人年龄。',
  `AgeUnitID` int(10) unsigned DEFAULT '0' COMMENT '病人年龄单位ID。',
  `birthday` bigint(255) DEFAULT '0' COMMENT '出生日期',
  `bloodType` varchar(255) DEFAULT '' COMMENT '血型',
  `AnamnesisNO` varchar(45) DEFAULT '' COMMENT '门诊号、病列号。',
  `wardName` varchar(32) DEFAULT '' COMMENT '病区',
  `BedNo` varchar(32) DEFAULT '' COMMENT '床号。',
  `departmentName` varchar(64) DEFAULT '' COMMENT '送检部门',
  `cupType` tinyint(255) NOT NULL DEFAULT '-1' COMMENT '杯类型(00标准杯,01 采血管,02 微量杯)\r\n',
  `diagnosis` varchar(512) DEFAULT '' COMMENT '诊断',
  `errorFlag` varchar(255) DEFAULT '' COMMENT '错误标识，以逗号分隔',
  `skipFlag` varchar(255) DEFAULT '' COMMENT '跳步标识，以逗号分隔',
  `stateFlag` tinyint(255) DEFAULT '0' COMMENT '状态 1=保存，2=测试中，88=成功，-1=失败',
  `isDelete` tinyint(255) DEFAULT '0' COMMENT '删除状态，1=删除',
  `testTime` varchar(30) DEFAULT '0' COMMENT '测试时间',
  `testUser` varchar(32) DEFAULT '' COMMENT '测试人',
  `intPreField` int(255) DEFAULT '-1',
  `strPreField` varchar(255) DEFAULT '',
  `articleNo` varchar(45) DEFAULT NULL COMMENT '货号',
  `createDay` datetime DEFAULT CURRENT_TIMESTAMP COMMENT '创建日期',
  `test_batch` int(11) DEFAULT '1',
  PRIMARY KEY (`pkid`) USING BTREE
) ENGINE=InnoDB AUTO_INCREMENT=7 DEFAULT CHARSET=utf8 ROW_FORMAT=DYNAMIC;

-- ----------------------------
-- Records of tsample
-- ----------------------------
INSERT INTO `tsample` VALUES ('1', '2024041215570000001', null, '3456', '0', '20', '0', '', '', '0', '10', '0', '0', '', '', '', '', '', '-1', '', '', '', '1', '0', '0', '', '-1', '', null, '2024-04-12 00:00:00', '1');
INSERT INTO `tsample` VALUES ('2', '2024041215570000002', null, '3456', '0', '2', '0', '', '', '0', '10', '0', '0', '', '', '', '', '', '-1', '', '', '', '1', '0', '0', '', '-1', '', null, '2024-04-12 00:00:00', '1');
INSERT INTO `tsample` VALUES ('3', '2024041215570000003', null, '3456', '0', '1', '0', '', '', '0', '10', '0', '0', '', '', '', '', '', '-1', '', '', '', '1', '0', '0', '', '-1', '', null, '2024-04-12 00:00:00', '1');
INSERT INTO `tsample` VALUES ('4', '2024041215570000004', null, '3456', '0', '3', '0', '', '', '0', '10', '0', '0', '', '', '', '', '', '-1', '', '', '', '1', '0', '0', '', '-1', '', null, '2024-04-12 00:00:00', '1');
INSERT INTO `tsample` VALUES ('5', '2024041215570000005', null, '3456', '0', '18', '0', '', '', '0', '10', '0', '0', '', '', '', '', '', '-1', '', '', '', '1', '0', '0', '', '-1', '', null, '2024-04-12 00:00:00', '1');
INSERT INTO `tsample` VALUES ('6', '2024041215570000006', null, '3456', '0', '19', '0', '', '', '0', '10', '0', '0', '', '', '', '', '', '-1', '', '', '', '1', '0', '0', '', '-1', '', null, '2024-04-12 00:00:00', '1');

-- ----------------------------
-- Table structure for tsample_sender
-- ----------------------------
DROP TABLE IF EXISTS `tsample_sender`;
CREATE TABLE `tsample_sender` (
  `ID` int(10) unsigned NOT NULL AUTO_INCREMENT COMMENT '送检医生ID。',
  `senderName` varchar(32) NOT NULL DEFAULT '' COMMENT '送检医生名称。',
  `shortKey` varchar(32) DEFAULT '',
  `remark` varchar(255) DEFAULT '',
  PRIMARY KEY (`ID`) USING BTREE,
  UNIQUE KEY `ID_UNIQUE` (`ID`) USING BTREE,
  UNIQUE KEY `Name_UNIQUE` (`shortKey`) USING BTREE
) ENGINE=InnoDB AUTO_INCREMENT=7 DEFAULT CHARSET=utf8 ROW_FORMAT=DYNAMIC COMMENT='送检医生表。';

-- ----------------------------
-- Records of tsample_sender
-- ----------------------------
INSERT INTO `tsample_sender` VALUES ('1', '张三', 'zs', '');
INSERT INTO `tsample_sender` VALUES ('4', '张龙', 'zr', '');
INSERT INTO `tsample_sender` VALUES ('6', '李四', 'ls', '');

-- ----------------------------
-- Table structure for tsample_test
-- ----------------------------
DROP TABLE IF EXISTS `tsample_test`;
CREATE TABLE `tsample_test` (
  `pkid` bigint(25) unsigned NOT NULL AUTO_INCREMENT,
  `Id` varchar(64) DEFAULT NULL COMMENT '测试编号',
  `solutionName` varchar(255) DEFAULT NULL COMMENT '方案名称',
  `manageName` varchar(255) DEFAULT NULL COMMENT '管理员名称',
  `sampleId` bigint(20) unsigned DEFAULT '0',
  `paperId` int(10) unsigned DEFAULT '0',
  `slotPos` int(255) DEFAULT '0',
  `projectName` varchar(255) DEFAULT NULL COMMENT '项目名字',
  `cutGrayValue` double(20,5) DEFAULT '0.00000' COMMENT 'cutoff值',
  `coefficient` double(10,4) DEFAULT '1.0000' COMMENT '系数',
  `testGrayValue` double(20,5) DEFAULT NULL COMMENT '测试得到的灰值',
  `testResult` varchar(255) DEFAULT NULL COMMENT '测试得到灰度与cutoff的比值*系数得到数值',
  `testTime` varchar(20) DEFAULT '0',
  `runStatus` int(10) DEFAULT NULL COMMENT '1测试中;2测试完成;3异常停止;4结果异常',
  `isDelete` tinyint(255) DEFAULT '0',
  `remark` varchar(255) DEFAULT '',
  `articleNo` varchar(45) DEFAULT NULL COMMENT '货号差不多相当于批次号',
  `sendLisFlag` int(11) DEFAULT '1' COMMENT '1等待上传，2上传中，3为上传完成',
  `error_code` int(11) DEFAULT '25',
  PRIMARY KEY (`pkid`) USING BTREE,
  KEY `pkid` (`pkid`) USING BTREE
) ENGINE=InnoDB DEFAULT CHARSET=utf8 ROW_FORMAT=DYNAMIC;

-- ----------------------------
-- Records of tsample_test
-- ----------------------------

-- ----------------------------
-- Table structure for tservice_type
-- ----------------------------
DROP TABLE IF EXISTS `tservice_type`;
CREATE TABLE `tservice_type` (
  `id` int(11) unsigned NOT NULL AUTO_INCREMENT,
  `TypeName` varchar(64) NOT NULL DEFAULT '',
  `shortKey` varchar(64) DEFAULT '',
  `orderNo` int(11) NOT NULL DEFAULT '0',
  `remark` varchar(0) DEFAULT '',
  PRIMARY KEY (`id`) USING BTREE
) ENGINE=InnoDB AUTO_INCREMENT=4 DEFAULT CHARSET=utf8 ROW_FORMAT=DYNAMIC;

-- ----------------------------
-- Records of tservice_type
-- ----------------------------
INSERT INTO `tservice_type` VALUES ('1', '门诊', 'mz', '1', '');
INSERT INTO `tservice_type` VALUES ('2', '住院', 'zy', '2', '');
INSERT INTO `tservice_type` VALUES ('3', '体检', 'tj', '3', '');

-- ----------------------------
-- Table structure for tsex
-- ----------------------------
DROP TABLE IF EXISTS `tsex`;
CREATE TABLE `tsex` (
  `ID` int(10) unsigned NOT NULL,
  `SexName` varchar(45) NOT NULL,
  `orderNo` tinyint(4) DEFAULT '0',
  PRIMARY KEY (`ID`) USING BTREE,
  UNIQUE KEY `ID_UNIQUE` (`ID`) USING BTREE,
  UNIQUE KEY `Name_UNIQUE` (`SexName`) USING BTREE
) ENGINE=InnoDB DEFAULT CHARSET=utf8 ROW_FORMAT=DYNAMIC COMMENT='性别表，描述系统中支持的全部性别。';

-- ----------------------------
-- Records of tsex
-- ----------------------------
INSERT INTO `tsex` VALUES ('1', '男', '1');
INSERT INTO `tsex` VALUES ('2', '女', '2');
INSERT INTO `tsex` VALUES ('3', '其它', '3');

-- ----------------------------
-- Table structure for tstep_incubation_time
-- ----------------------------
DROP TABLE IF EXISTS `tstep_incubation_time`;
CREATE TABLE `tstep_incubation_time` (
  `pkid` int(11) NOT NULL AUTO_INCREMENT,
  `step_name` varchar(255) DEFAULT NULL,
  `step_incubation_time` int(11) DEFAULT '10' COMMENT '单位为秒',
  `company_id` int(11) DEFAULT '1' COMMENT '膜条所在公司编号',
  PRIMARY KEY (`pkid`) USING BTREE
) ENGINE=InnoDB AUTO_INCREMENT=33 DEFAULT CHARSET=utf8 ROW_FORMAT=DYNAMIC;

-- ----------------------------
-- Records of tstep_incubation_time
-- ----------------------------
INSERT INTO `tstep_incubation_time` VALUES ('1', '润湿', '60', '1');
INSERT INTO `tstep_incubation_time` VALUES ('2', '加样本', '1800', '1');
INSERT INTO `tstep_incubation_time` VALUES ('3', '清洗', '900', '1');
INSERT INTO `tstep_incubation_time` VALUES ('4', '加酶', '1800', '1');
INSERT INTO `tstep_incubation_time` VALUES ('5', '加底物', '600', '1');
INSERT INTO `tstep_incubation_time` VALUES ('6', '加蒸馏水', '60', '1');
INSERT INTO `tstep_incubation_time` VALUES ('7', '加终止液', '300', '1');
INSERT INTO `tstep_incubation_time` VALUES ('8', '干燥', '1800', '1');
INSERT INTO `tstep_incubation_time` VALUES ('9', '润湿', '300', '2');
INSERT INTO `tstep_incubation_time` VALUES ('10', '加样本', '1800', '2');
INSERT INTO `tstep_incubation_time` VALUES ('11', '清洗', '1800', '2');
INSERT INTO `tstep_incubation_time` VALUES ('12', '加酶', '1800', '2');
INSERT INTO `tstep_incubation_time` VALUES ('13', '加底物', '600', '2');
INSERT INTO `tstep_incubation_time` VALUES ('14', '加蒸馏水', '60', '2');
INSERT INTO `tstep_incubation_time` VALUES ('15', '加终止液', '300', '2');
INSERT INTO `tstep_incubation_time` VALUES ('16', '干燥', '1800', '2');
INSERT INTO `tstep_incubation_time` VALUES ('17', '润湿', '300', '4');
INSERT INTO `tstep_incubation_time` VALUES ('18', '加样本', '1800', '4');
INSERT INTO `tstep_incubation_time` VALUES ('19', '清洗', '150', '4');
INSERT INTO `tstep_incubation_time` VALUES ('20', '加酶', '1800', '4');
INSERT INTO `tstep_incubation_time` VALUES ('21', '加底物', '1200', '4');
INSERT INTO `tstep_incubation_time` VALUES ('22', '加蒸馏水', '150', '4');
INSERT INTO `tstep_incubation_time` VALUES ('23', '加终止液', '300', '4');
INSERT INTO `tstep_incubation_time` VALUES ('24', '干燥', '7200', '4');
INSERT INTO `tstep_incubation_time` VALUES ('25', '润湿', '300', '5');
INSERT INTO `tstep_incubation_time` VALUES ('26', '加样本', '1800', '5');
INSERT INTO `tstep_incubation_time` VALUES ('27', '清洗', '150', '5');
INSERT INTO `tstep_incubation_time` VALUES ('28', '加酶', '1800', '5');
INSERT INTO `tstep_incubation_time` VALUES ('29', '加底物', '1200', '5');
INSERT INTO `tstep_incubation_time` VALUES ('30', '加蒸馏水', '120', '5');
INSERT INTO `tstep_incubation_time` VALUES ('31', '加终止液', '300', '5');
INSERT INTO `tstep_incubation_time` VALUES ('32', '干燥', '7200', '5');

-- ----------------------------
-- Table structure for tsystemset
-- ----------------------------
DROP TABLE IF EXISTS `tsystemset`;
CREATE TABLE `tsystemset` (
  `id` int(11) unsigned NOT NULL,
  `saveSet` int(11) DEFAULT '0',
  `saveDes` varchar(256) DEFAULT '',
  `remark` varchar(512) DEFAULT '',
  PRIMARY KEY (`id`) USING BTREE
) ENGINE=InnoDB DEFAULT CHARSET=utf8 ROW_FORMAT=DYNAMIC;

-- ----------------------------
-- Records of tsystemset
-- ----------------------------
INSERT INTO `tsystemset` VALUES ('1', '40', '40', '功能条灰度阈值');
INSERT INTO `tsystemset` VALUES ('2', '18', '18', 'Cut Off条灰度阈值');
INSERT INTO `tsystemset` VALUES ('3', '0', 'D:\\HumablotProFiles\\TestPictures', '测试图像保存根目录');
INSERT INTO `tsystemset` VALUES ('4', '0', 'D:\\HumablotProFiles\\Reports', '测试报告保存根目录');
INSERT INTO `tsystemset` VALUES ('5', '1', 'TEST', '当前使用的膜条所属公司');
INSERT INTO `tsystemset` VALUES ('6', '1', 'defaultProcess', '默认时序');
INSERT INTO `tsystemset` VALUES ('7', '1', '打开', '样本针吸样液位探测，1=打开，0=关闭');
INSERT INTO `tsystemset` VALUES ('8', '1', '打开', '样本针吐样液位探测，1=打开，0=关闭');
INSERT INTO `tsystemset` VALUES ('20', '3000', 'systemLiquidIrrigate', '系统液冲灌体积');
INSERT INTO `tsystemset` VALUES ('21', '5000', '', '系统液清洗体积');
INSERT INTO `tsystemset` VALUES ('22', '3000', '300,300,300', '月维护泵充灌');
INSERT INTO `tsystemset` VALUES ('23', '3000', '200,200,200', '周维护泵充灌');
INSERT INTO `tsystemset` VALUES ('24', '900000', '', '月维护管路浸泡15分钟');
INSERT INTO `tsystemset` VALUES ('25', '500', '', '月维护泵校准');
INSERT INTO `tsystemset` VALUES ('26', '5000', '7000', '泵校准两次下降最大差值');
INSERT INTO `tsystemset` VALUES ('9991', '1800', '1', '周维护完成时间');
INSERT INTO `tsystemset` VALUES ('9992', '1800', '2023-08-02 09:30:38', '月维护完成时间');
INSERT INTO `tsystemset` VALUES ('9993', '0', '1', '启动LIS 1为启动0为不启动');
INSERT INTO `tsystemset` VALUES ('9994', '0', '0', '是否启动实时模式1为启，0为不启动');
INSERT INTO `tsystemset` VALUES ('9995', '0', '192.168.20.33', 'IP');
INSERT INTO `tsystemset` VALUES ('9996', '0', '8889', '端口');
INSERT INTO `tsystemset` VALUES ('9997', '0', 'HL7', 'protocol类型');
INSERT INTO `tsystemset` VALUES ('10001', '180', '6', '润湿用时秒数');
INSERT INTO `tsystemset` VALUES ('10002', '180', '28', '加样本用时秒数');
INSERT INTO `tsystemset` VALUES ('10003', '180', '18', '清洗用时秒数');
INSERT INTO `tsystemset` VALUES ('10004', '180', '6', '加酶用时秒数');
INSERT INTO `tsystemset` VALUES ('10005', '180', '18', '二次清洗用时秒数');
INSERT INTO `tsystemset` VALUES ('10006', '180', '6', '加底物用时秒数');
INSERT INTO `tsystemset` VALUES ('10007', '180', '6', '加蒸馏水用时秒数');
INSERT INTO `tsystemset` VALUES ('10008', '180', '12', '加终止液用时秒数');
INSERT INTO `tsystemset` VALUES ('10009', '180', '1', '干燥用时秒数');
INSERT INTO `tsystemset` VALUES ('20001', '1', '是', '增加蜂鸣器声音“使能-1/关闭-0”按钮');
INSERT INTO `tsystemset` VALUES ('20002', '1', '是', '废液桶 使能 1、去使能为 0”');
INSERT INTO `tsystemset` VALUES ('20003', '3000', '1000', '');
INSERT INTO `tsystemset` VALUES ('20004', '3000', '1000', '');
INSERT INTO `tsystemset` VALUES ('20005', '1', '1', '');
INSERT INTO `tsystemset` VALUES ('20006', '18', '18.48', '毫米对应像素点');
INSERT INTO `tsystemset` VALUES ('20007', '0', '0', '0，未请求完成，1为请求完成');
INSERT INTO `tsystemset` VALUES ('20008', '1', '1', '0，无拍照功能，1有拍照功能');
INSERT INTO `tsystemset` VALUES ('20009', '24', '24', '测试结果，列表每页显示的数量');

-- ----------------------------
-- Table structure for ttube
-- ----------------------------
DROP TABLE IF EXISTS `ttube`;
CREATE TABLE `ttube` (
  `ID` int(10) unsigned NOT NULL AUTO_INCREMENT,
  `Name1` varchar(45) NOT NULL COMMENT '名称',
  `IsControl` tinyint(1) unsigned NOT NULL COMMENT '是否为质控管',
  `Inner1` int(10) unsigned DEFAULT NULL COMMENT '试管内径',
  `CupHeight` int(10) unsigned DEFAULT NULL COMMENT '试管高度',
  `LiquidStartPos` int(10) unsigned DEFAULT NULL COMMENT '液位启始位置',
  PRIMARY KEY (`ID`) USING BTREE
) ENGINE=InnoDB AUTO_INCREMENT=3 DEFAULT CHARSET=utf8 ROW_FORMAT=DYNAMIC;

-- ----------------------------
-- Records of ttube
-- ----------------------------
INSERT INTO `ttube` VALUES ('1', '1', '1', '1', '1', '1');
INSERT INTO `ttube` VALUES ('2', '88', '0', '10', '2', '2');

-- ----------------------------
-- Table structure for tuser
-- ----------------------------
DROP TABLE IF EXISTS `tuser`;
CREATE TABLE `tuser` (
  `ID` int(10) unsigned NOT NULL AUTO_INCREMENT,
  `GroupID` int(10) unsigned NOT NULL,
  `LoginName` varchar(32) NOT NULL,
  `uPassword` varchar(64) NOT NULL,
  `showName` varchar(32) DEFAULT '',
  `addUser` varchar(32) DEFAULT '',
  `addTime` bigint(20) unsigned DEFAULT '0',
  `isDelete` tinyint(255) unsigned DEFAULT '0',
  PRIMARY KEY (`ID`) USING BTREE,
  UNIQUE KEY `UserName_UNIQUE` (`LoginName`) USING BTREE
) ENGINE=InnoDB AUTO_INCREMENT=22 DEFAULT CHARSET=utf8 ROW_FORMAT=DYNAMIC;

-- ----------------------------
-- Records of tuser
-- ----------------------------
INSERT INTO `tuser` VALUES ('1', '1', 'admin', '0000', '', '', '0', '0');
INSERT INTO `tuser` VALUES ('2', '2', 'engineer1', '0000', '', '', '0', '0');
INSERT INTO `tuser` VALUES ('3', '3', 'user1', '0000', '', '', '0', '0');
INSERT INTO `tuser` VALUES ('4', '2', 'engineer', '0000', '', '', '0', '0');
INSERT INTO `tuser` VALUES ('5', '3', 'user', '0000', '', '', '0', '0');
INSERT INTO `tuser` VALUES ('6', '3', 'user2', '0000', '', '', '0', '0');
INSERT INTO `tuser` VALUES ('7', '3', 'user3', '0000', '', '', '0', '0');
INSERT INTO `tuser` VALUES ('10', '2', 'engineer2', '0000', '', '', '0', '0');
INSERT INTO `tuser` VALUES ('11', '2', 'engineer3', '0000', '', '', '0', '0');
INSERT INTO `tuser` VALUES ('17', '3', 'user344', '0000', '', '', '0', '0');
INSERT INTO `tuser` VALUES ('18', '3', 'sssss', '0000', '', '', '0', '0');
INSERT INTO `tuser` VALUES ('20', '3', 'ddfdfd', '0000', '', '', '0', '0');
INSERT INTO `tuser` VALUES ('21', '3', '66', '32233', '', '', '0', '0');

-- ----------------------------
-- Table structure for tusergroup
-- ----------------------------
DROP TABLE IF EXISTS `tusergroup`;
CREATE TABLE `tusergroup` (
  `ID` int(10) unsigned NOT NULL,
  `GroupName` varchar(32) NOT NULL,
  `EnableAddOrDelete` tinyint(3) unsigned NOT NULL DEFAULT '0',
  `EnableChangePassword` tinyint(3) unsigned NOT NULL DEFAULT '0',
  PRIMARY KEY (`ID`) USING BTREE
) ENGINE=InnoDB DEFAULT CHARSET=utf8 ROW_FORMAT=DYNAMIC;

-- ----------------------------
-- Records of tusergroup
-- ----------------------------
INSERT INTO `tusergroup` VALUES ('1', 'Admin', '0', '0');
INSERT INTO `tusergroup` VALUES ('2', 'Engineer', '0', '0');
INSERT INTO `tusergroup` VALUES ('3', 'User', '1', '1');
INSERT INTO `tusergroup` VALUES ('4', '普通用户', '1', '1');

-- ----------------------------
-- Table structure for tward
-- ----------------------------
DROP TABLE IF EXISTS `tward`;
CREATE TABLE `tward` (
  `ID` int(10) unsigned NOT NULL AUTO_INCREMENT,
  `wardName` varchar(64) NOT NULL,
  `shortKey` varchar(32) DEFAULT '',
  `remark` varchar(255) DEFAULT '',
  PRIMARY KEY (`ID`) USING BTREE,
  UNIQUE KEY `ID_UNIQUE` (`ID`) USING BTREE,
  UNIQUE KEY `Name_UNIQUE` (`shortKey`) USING BTREE
) ENGINE=InnoDB AUTO_INCREMENT=4 DEFAULT CHARSET=utf8 ROW_FORMAT=DYNAMIC COMMENT='医院科室表。';

-- ----------------------------
-- Records of tward
-- ----------------------------
INSERT INTO `tward` VALUES ('1', '301A', 'A', '');
INSERT INTO `tward` VALUES ('2', '301C', 'C', '');
INSERT INTO `tward` VALUES ('3', '302', 'B', '');

-- ----------------------------
-- Table structure for t_judge_rules
-- ----------------------------
DROP TABLE IF EXISTS `t_judge_rules`;
CREATE TABLE `t_judge_rules` (
  `pkid` int(11) unsigned NOT NULL AUTO_INCREMENT,
  `RulesId` int(255) DEFAULT NULL,
  `GrayValue` double(20,5) DEFAULT NULL,
  `GrayWord` varchar(255) DEFAULT NULL,
  PRIMARY KEY (`pkid`) USING BTREE
) ENGINE=InnoDB AUTO_INCREMENT=85 DEFAULT CHARSET=utf8 ROW_FORMAT=DYNAMIC;

-- ----------------------------
-- Records of t_judge_rules
-- ----------------------------
INSERT INTO `t_judge_rules` VALUES ('14', '1', '1.15000', 'o');
INSERT INTO `t_judge_rules` VALUES ('15', '1', '1.50000', '+');
INSERT INTO `t_judge_rules` VALUES ('16', '1', '2.40000', '++');
INSERT INTO `t_judge_rules` VALUES ('26', '3', '-1.40000', '--');
INSERT INTO `t_judge_rules` VALUES ('34', '4', '-1.40000', '--');
INSERT INTO `t_judge_rules` VALUES ('35', '4', '0.70000', '-');
INSERT INTO `t_judge_rules` VALUES ('36', '4', '0.60000', '-');
INSERT INTO `t_judge_rules` VALUES ('37', '4', '1.00000', 'O');
INSERT INTO `t_judge_rules` VALUES ('38', '4', '5.00000', '+');
INSERT INTO `t_judge_rules` VALUES ('39', '4', '6.00000', '+');
INSERT INTO `t_judge_rules` VALUES ('40', '4', '7.00000', '++');
INSERT INTO `t_judge_rules` VALUES ('41', '4', '8.00000', '+++');
INSERT INTO `t_judge_rules` VALUES ('42', '5', '-1.40000', '--');
INSERT INTO `t_judge_rules` VALUES ('43', '5', '0.70000', '-');
INSERT INTO `t_judge_rules` VALUES ('44', '5', '0.60000', '-');
INSERT INTO `t_judge_rules` VALUES ('45', '5', '1.00000', 'O');
INSERT INTO `t_judge_rules` VALUES ('46', '5', '5.00000', '+');
INSERT INTO `t_judge_rules` VALUES ('47', '5', '6.00000', '+');
INSERT INTO `t_judge_rules` VALUES ('48', '5', '7.00000', '++');
INSERT INTO `t_judge_rules` VALUES ('49', '5', '8.00000', '+++');
INSERT INTO `t_judge_rules` VALUES ('50', '6', '-1.40000', '--');
INSERT INTO `t_judge_rules` VALUES ('51', '6', '0.70000', '-');
INSERT INTO `t_judge_rules` VALUES ('52', '6', '0.60000', '-');
INSERT INTO `t_judge_rules` VALUES ('53', '6', '1.00000', 'O');
INSERT INTO `t_judge_rules` VALUES ('54', '6', '5.00000', '+');
INSERT INTO `t_judge_rules` VALUES ('55', '6', '6.00000', '+');
INSERT INTO `t_judge_rules` VALUES ('56', '6', '7.00000', '++');
INSERT INTO `t_judge_rules` VALUES ('57', '6', '8.00000', '+++');
INSERT INTO `t_judge_rules` VALUES ('58', '7', '-1.40000', '--');
INSERT INTO `t_judge_rules` VALUES ('59', '7', '0.70000', '-');
INSERT INTO `t_judge_rules` VALUES ('60', '7', '0.60000', '-');
INSERT INTO `t_judge_rules` VALUES ('61', '7', '1.00000', 'O');
INSERT INTO `t_judge_rules` VALUES ('62', '7', '5.00000', '+');
INSERT INTO `t_judge_rules` VALUES ('63', '7', '6.00000', '+');
INSERT INTO `t_judge_rules` VALUES ('64', '7', '7.00000', '++');
INSERT INTO `t_judge_rules` VALUES ('65', '7', '8.00000', '+++');
INSERT INTO `t_judge_rules` VALUES ('66', '8', '-1.40000', '--');
INSERT INTO `t_judge_rules` VALUES ('67', '8', '0.70000', '-');
INSERT INTO `t_judge_rules` VALUES ('68', '8', '0.60000', '-');
INSERT INTO `t_judge_rules` VALUES ('69', '8', '1.00000', 'O');
INSERT INTO `t_judge_rules` VALUES ('70', '8', '5.00000', '+');
INSERT INTO `t_judge_rules` VALUES ('71', '8', '6.00000', '+');
INSERT INTO `t_judge_rules` VALUES ('72', '8', '7.00000', '++');
INSERT INTO `t_judge_rules` VALUES ('74', '8', '14.66000', '+++');
INSERT INTO `t_judge_rules` VALUES ('76', '1', '0.85000', '-');
INSERT INTO `t_judge_rules` VALUES ('77', '1', '50.00000', '+++');
INSERT INTO `t_judge_rules` VALUES ('78', '2', '0.97000', '-');
INSERT INTO `t_judge_rules` VALUES ('79', '2', '1.02000', 'O');
INSERT INTO `t_judge_rules` VALUES ('80', '2', '1.07000', '+');
INSERT INTO `t_judge_rules` VALUES ('81', '2', '1.23000', '++');
INSERT INTO `t_judge_rules` VALUES ('84', '2', '50.00000', '+++');

-- ----------------------------
-- Table structure for t_judge_rules_name
-- ----------------------------
DROP TABLE IF EXISTS `t_judge_rules_name`;
CREATE TABLE `t_judge_rules_name` (
  `pkid` int(20) unsigned NOT NULL AUTO_INCREMENT,
  `RuleName` varchar(255) DEFAULT NULL,
  PRIMARY KEY (`pkid`) USING BTREE
) ENGINE=InnoDB AUTO_INCREMENT=9 DEFAULT CHARSET=utf8 ROW_FORMAT=DYNAMIC;

-- ----------------------------
-- Records of t_judge_rules_name
-- ----------------------------
INSERT INTO `t_judge_rules_name` VALUES ('1', 'K1650');
INSERT INTO `t_judge_rules_name` VALUES ('2', 'K1651');
INSERT INTO `t_judge_rules_name` VALUES ('3', 'K1652');
INSERT INTO `t_judge_rules_name` VALUES ('4', 'K1653');
INSERT INTO `t_judge_rules_name` VALUES ('5', 'K1654');
INSERT INTO `t_judge_rules_name` VALUES ('6', 'K1655');
INSERT INTO `t_judge_rules_name` VALUES ('7', 'K1656');
INSERT INTO `t_judge_rules_name` VALUES ('8', 'K1657');

-- ----------------------------
-- Table structure for t_login_name_info
-- ----------------------------
DROP TABLE IF EXISTS `t_login_name_info`;
CREATE TABLE `t_login_name_info` (
  `pkid` int(11) NOT NULL AUTO_INCREMENT,
  `login_name` varchar(255) DEFAULT NULL,
  `login_time` datetime DEFAULT NULL,
  `is_delete` tinyint(4) DEFAULT '0',
  PRIMARY KEY (`pkid`) USING BTREE
) ENGINE=InnoDB AUTO_INCREMENT=3 DEFAULT CHARSET=utf8 ROW_FORMAT=DYNAMIC;

-- ----------------------------
-- Records of t_login_name_info
-- ----------------------------
INSERT INTO `t_login_name_info` VALUES ('1', 'admin', '2024-04-15 09:19:51', '0');
INSERT INTO `t_login_name_info` VALUES ('2', 'user', '2023-09-25 15:20:49', '0');

-- ----------------------------
-- Table structure for t_operate_log
-- ----------------------------
DROP TABLE IF EXISTS `t_operate_log`;
CREATE TABLE `t_operate_log` (
  `pkid` int(11) NOT NULL AUTO_INCREMENT,
  `model_name` varchar(255) DEFAULT NULL,
  `machine_id` varchar(255) DEFAULT NULL,
  `operate_content` varchar(255) DEFAULT NULL COMMENT '操作的内容，比如说删除什么，修改什么。添加了什么',
  `user_name` varchar(255) DEFAULT NULL,
  `create_time` datetime DEFAULT CURRENT_TIMESTAMP,
  PRIMARY KEY (`pkid`) USING BTREE
) ENGINE=InnoDB AUTO_INCREMENT=656 DEFAULT CHARSET=utf8 ROW_FORMAT=DYNAMIC;

-- ----------------------------
-- Records of t_operate_log
-- ----------------------------
INSERT INTO `t_operate_log` VALUES ('654', '用户登录', '登录状态，未取得机器序号', '登录', 'admin', '2024-04-12 15:56:49');
INSERT INTO `t_operate_log` VALUES ('655', '用户登录', '登录状态，未取得机器序号', '登录', 'admin', '2024-04-15 09:19:51');

-- ----------------------------
-- Table structure for t_run_log
-- ----------------------------
DROP TABLE IF EXISTS `t_run_log`;
CREATE TABLE `t_run_log` (
  `pkid` int(11) NOT NULL AUTO_INCREMENT,
  `tip_info` varchar(255) DEFAULT NULL,
  `solution_name` varchar(255) DEFAULT NULL,
  `login_name` varchar(255) DEFAULT NULL,
  `machine_UID` varchar(20) DEFAULT NULL,
  `create_time` datetime DEFAULT CURRENT_TIMESTAMP,
  PRIMARY KEY (`pkid`) USING BTREE
) ENGINE=InnoDB AUTO_INCREMENT=22629 DEFAULT CHARSET=utf8 ROW_FORMAT=DYNAMIC;

-- ----------------------------
-- Records of t_run_log
-- ----------------------------

-- ----------------------------
-- Table structure for t_sql_version
-- ----------------------------
DROP TABLE IF EXISTS `t_sql_version`;
CREATE TABLE `t_sql_version` (
  `version_name` varchar(255) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8 ROW_FORMAT=DYNAMIC;

-- ----------------------------
-- Records of t_sql_version
-- ----------------------------
INSERT INTO `t_sql_version` VALUES ('6.0');

-- ----------------------------
-- Table structure for t_step_times
-- ----------------------------
DROP TABLE IF EXISTS `t_step_times`;
CREATE TABLE `t_step_times` (
  `id` int(11) DEFAULT NULL,
  `saveSet` varchar(255) DEFAULT NULL,
  `saveDes` varchar(255) DEFAULT NULL,
  `remark` varchar(255) DEFAULT NULL,
  `type` int(11) DEFAULT '0'
) ENGINE=InnoDB DEFAULT CHARSET=utf8 ROW_FORMAT=DYNAMIC;

-- ----------------------------
-- Records of t_step_times
-- ----------------------------
INSERT INTO `t_step_times` VALUES ('10001', '180', '6.5', '润湿用时秒数', '2');
INSERT INTO `t_step_times` VALUES ('10002', '180', '28', '加样本用时秒数', '2');
INSERT INTO `t_step_times` VALUES ('10003', '180', '18', '清洗用时秒数', '2');
INSERT INTO `t_step_times` VALUES ('10004', '180', '6', '加酶用时秒数', '2');
INSERT INTO `t_step_times` VALUES ('10005', '180', '18', '二次清洗用时秒数', '2');
INSERT INTO `t_step_times` VALUES ('10006', '180', '6', '加底物用时秒数', '2');
INSERT INTO `t_step_times` VALUES ('10007', '180', '6', '加蒸馏水用时秒数', '2');
INSERT INTO `t_step_times` VALUES ('10008', '180', '12', '加终止液用时秒数', '2');
INSERT INTO `t_step_times` VALUES ('10009', '180', '1', '干燥用时秒数', '2');
INSERT INTO `t_step_times` VALUES ('10001', '180', '4.5', '润湿用时秒数', '1');
INSERT INTO `t_step_times` VALUES ('10002', '180', '23', '加样本用时秒数', '1');
INSERT INTO `t_step_times` VALUES ('10003', '180', '20.5', '清洗用时秒数', '1');
INSERT INTO `t_step_times` VALUES ('10004', '180', '5.5', '加酶用时秒数', '1');
INSERT INTO `t_step_times` VALUES ('10005', '180', '20.5', '二次清洗用时秒数', '1');
INSERT INTO `t_step_times` VALUES ('10006', '180', '5.7', '加底物用时秒数', '1');
INSERT INTO `t_step_times` VALUES ('10007', '180', '5.5', '加蒸馏水用时秒数', '1');
INSERT INTO `t_step_times` VALUES ('10008', '180', '5.5', '加终止液用时秒数', '1');
INSERT INTO `t_step_times` VALUES ('10009', '180', '5.5', '干燥用时秒数', '1');
INSERT INTO `t_step_times` VALUES ('10001', '180', '6', '润湿用时秒数', '5');
INSERT INTO `t_step_times` VALUES ('10002', '180', '28', '加样本用时秒数', '5');
INSERT INTO `t_step_times` VALUES ('10003', '180', '18', '清洗用时秒数', '5');
INSERT INTO `t_step_times` VALUES ('10004', '180', '6', '加酶用时秒数', '5');
INSERT INTO `t_step_times` VALUES ('10005', '180', '18', '二次清洗用时秒数', '5');
INSERT INTO `t_step_times` VALUES ('10006', '180', '6', '加底物用时秒数', '5');
INSERT INTO `t_step_times` VALUES ('10007', '180', '6', '加蒸馏水用时秒数', '5');
INSERT INTO `t_step_times` VALUES ('10008', '180', '12', '加终止液用时秒数', '5');
INSERT INTO `t_step_times` VALUES ('10009', '180', '1', '干燥用时秒数', '4');
INSERT INTO `t_step_times` VALUES ('10001', '180', '6', '润湿用时秒数', '4');
INSERT INTO `t_step_times` VALUES ('10002', '180', '28', '加样本用时秒数', '4');
INSERT INTO `t_step_times` VALUES ('10003', '180', '18', '清洗用时秒数', '4');
INSERT INTO `t_step_times` VALUES ('10004', '180', '6', '加酶用时秒数', '4');
INSERT INTO `t_step_times` VALUES ('10005', '180', '18', '二次清洗用时秒数', '4');
INSERT INTO `t_step_times` VALUES ('10006', '180', '6', '加底物用时秒数', '4');
INSERT INTO `t_step_times` VALUES ('10007', '180', '6', '加蒸馏水用时秒数', '4');
INSERT INTO `t_step_times` VALUES ('10008', '180', '12', '加终止液用时秒数', '4');
INSERT INTO `t_step_times` VALUES ('10009', '180', '1', '干燥用时秒数', '5');

-- ----------------------------
-- Table structure for t_testpaper
-- ----------------------------
DROP TABLE IF EXISTS `t_testpaper`;
CREATE TABLE `t_testpaper` (
  `ID` int(10) unsigned NOT NULL AUTO_INCREMENT,
  `PaperName` varchar(255) DEFAULT NULL,
  `Company_ID` int(10) unsigned NOT NULL COMMENT '模条属于哪个公司',
  `TotalNumber` int(10) unsigned NOT NULL COMMENT '总个数：测试项目个数 + 空白项目区域个数',
  `Item_Number` int(10) unsigned NOT NULL COMMENT '测试项目个数',
  `TestPaparLenght` double NOT NULL COMMENT '模条总长度（精确到0.1毫米）',
  `FuncPosition` double NOT NULL COMMENT '功能条左侧位置（精确到0.1毫米），即左边缘',
  `cutoffPosition` double NOT NULL DEFAULT '0',
  `isFun` tinyint(2) DEFAULT '1' COMMENT '默认为有功能线1，0为没有',
  `funGrayValue` double(4,0) DEFAULT NULL COMMENT '功能条灰度值',
  `isCutOff` tinyint(2) DEFAULT '1' COMMENT '默认是有1，0为没有cutoff线',
  `cutoffValue` double(4,0) DEFAULT NULL COMMENT 'cutoff线灰度值',
  `TestAeaLenght` double NOT NULL DEFAULT '50' COMMENT '测试区域长度 从功能条右侧到最后一个测试项目右侧（精确到0.1毫米）',
  `usageV` int(255) DEFAULT '0' COMMENT 'ul',
  `articleNo` varchar(45) DEFAULT NULL COMMENT '货号',
  `defaultBGRGB` varchar(255) DEFAULT '' COMMENT '默认',
  `BGRGB` varchar(255) DEFAULT '',
  `isDelete` tinyint(255) DEFAULT '0',
  `rect_Analysis.x` double(4,0) DEFAULT '0' COMMENT '/* 方形的左上角的x-坐标 */',
  `rect_Analysis.y` double(4,2) DEFAULT '81.00' COMMENT '/* 方形的左上角的y-坐标*/',
  `rect_Analysis.width` decimal(10,2) DEFAULT NULL,
  `rect_Analysis.height` double(4,0) DEFAULT '55' COMMENT '截取高度',
  `analysis_height_percentage` double(4,0) DEFAULT '50' COMMENT '截取用于分析图片中间高度的百分比，取大值100',
  `head_length` double(4,0) DEFAULT '0' COMMENT '膜条头长度，单位像素，和计算无关，为了深色膜条显示全',
  `set_calculate_point` int(11) DEFAULT '3' COMMENT '设置计算点数量',
  `point_to_min_percent` double DEFAULT '0.2' COMMENT '最低值两边点值的差值范围',
  `find_min_times` int(11) DEFAULT '50' COMMENT '查找最低值的次数，防止有跳点',
  `left_judge_value` int(11) DEFAULT '50' COMMENT '左边灰度对比值',
  `sort_idx` int(11) DEFAULT '1111',
  `wave_pix_width` int(11) DEFAULT '17',
  `threshold_value` int(11) DEFAULT '20',
  `background_values` int(11) DEFAULT '100',
  `bg_difference` int(11) DEFAULT '25',
  `zero_value_coefficient` double DEFAULT '0.3',
  `wave_pix_width_max` int(11) DEFAULT '24',
  `wave_pix_width_min` int(11) DEFAULT '10',
  PRIMARY KEY (`ID`) USING BTREE
) ENGINE=InnoDB AUTO_INCREMENT=929 DEFAULT CHARSET=utf8 ROW_FORMAT=DYNAMIC;

-- ----------------------------
-- Records of t_testpaper
-- ----------------------------
INSERT INTO `t_testpaper` VALUES ('1', 'ANA-LIA(12)', '1', '12', '12', '75', '10', '14', '1', '200', '1', '200', '67.6', '10', 'HM00003', '#F2E026', '#F2E026', '0', '120', '1.60', '18.42', '95', '10', '0', '10', '0.2', '3', '20', '92', '20', '20', '140', '8', '0.45', '24', '6');
INSERT INTO `t_testpaper` VALUES ('2', 'ANA-LIA-2(9N) ', '1', '9', '9', '68', '3', '6.5', '1', '200', '1', '200', '74.57', '10', 'HM00004', '#F6C0C7', '#F6C0C7', '0', '120', '1.60', '18.48', '95', '10', '116', '10', '0.2', '3', '2', '84', '20', '20', '140', '8', '0.45', '24', '6');
INSERT INTO `t_testpaper` VALUES ('3', 'ANA-LIA-1(9D) ', '1', '9', '9', '68', '4', '7.5', '1', '200', '1', '200', '48', '10', 'HM00005', '#C4181F', '#C4181F', '0', '120', '1.60', '18.48', '95', '10', '116', '10', '0.2', '3', '2', '108', '20', '20', '140', '8', '0.45', '24', '6');
INSERT INTO `t_testpaper` VALUES ('18', 'Liver-LIA', '1', '6', '6', '68', '3.5', '7.5', '1', '200', '1', '200', '28', '10', 'HM00002', '#8B3E29', '#8B3E29', '0', '120', '1.60', '18.61', '95', '10', '116', '10', '0.2', '3', '2', '109', '20', '20', '140', '8', '0.45', '24', '6');
INSERT INTO `t_testpaper` VALUES ('19', 'ANA LIA Maxx', '1', '17', '17', '68', '3', '6', '1', '200', '1', '200', '91.61', '10', 'HM00006', '#8AC1E3', '#E37610', '0', '120', '1.60', '18.45', '95', '10', '116', '10', '0.2', '3', '2', '110', '20', '20', '140', '8', '0.45', '24', '6');
INSERT INTO `t_testpaper` VALUES ('20', 'Vasculitis-LIA', '1', '3', '3', '68', '11', '15', '1', '200', '1', '200', '16', '10', 'HM00007', '#891F80', '#891F80', '0', '120', '1.60', '18.72', '95', '10', '116', '10', '0.2', '3', '2', '52', '20', '20', '140', '8', '0.45', '24', '6');
INSERT INTO `t_testpaper` VALUES ('21', 'ANCA-3', '2', '3', '3', '125', '17.5', '18.34', '1', '150', '0', '140', '50', '0', 'L90031', '', '#338f22', '0', '110', '0.80', '18.54', '150', '10', '0', '3', '0.2', '50', '20', '123', '17', '20', '100', '25', '0.3', '24', '10');
INSERT INTO `t_testpaper` VALUES ('27', 'MYO-25', '2', '25', '25', '125', '16.5', '0', '1', '150', '0', '140', '50', '0', 'L90041', '', '#ff5500', '0', '110', '0.60', '18.54', '55', '10', '0', '3', '0.2', '50', '15', '120', '17', '20', '100', '25', '0.3', '24', '10');
INSERT INTO `t_testpaper` VALUES ('28', 'ANA-18', '2', '18', '18', '125', '16.5', '17', '1', '150', '0', '140', '50', '0', 'L90011', '', '#ffff00', '1', '110', '0.60', '18.54', '55', '10', '0', '3', '0.2', '50', '20', '122', '17', '20', '100', '25', '0.3', '24', '10');
INSERT INTO `t_testpaper` VALUES ('29', 'ANA-17', '2', '17', '17', '125', '16.5', '17', '1', '150', '0', '140', '50', '0', 'L90012', '', '#ffff00', '0', '110', '0.60', '18.54', '55', '10', '0', '3', '0.2', '50', '100', '124', '17', '20', '100', '25', '0.3', '24', '10');
INSERT INTO `t_testpaper` VALUES ('30', 'ANA-15', '2', '15', '15', '125', '16.5', '17', '1', '150', '0', '140', '50', '0', 'L90013', '', '#ffff00', '1', '110', '0.60', '18.54', '55', '10', '0', '3', '0.2', '50', '20', '125', '17', '20', '100', '25', '0.3', '24', '10');
INSERT INTO `t_testpaper` VALUES ('31', 'ANA-13', '2', '13', '13', '125', '16.5', '17', '1', '150', '0', '140', '50', '0', 'L90014', '', '#ffff00', '1', '110', '0.60', '18.54', '55', '10', '0', '3', '0.2', '50', '20', '126', '17', '20', '100', '25', '0.3', '24', '10');
INSERT INTO `t_testpaper` VALUES ('32', 'ANA-12', '2', '12', '12', '125', '16.5', '17', '1', '150', '0', '140', '50', '0', 'L90015', '', '#ffff00', '0', '110', '0.60', '18.54', '55', '10', '0', '3', '0.2', '50', '20', '127', '17', '20', '100', '25', '0.3', '24', '10');
INSERT INTO `t_testpaper` VALUES ('33', 'ANA-9N', '2', '9', '9', '125', '16.5', '17', '1', '150', '0', '140', '50', '0', 'L90017', '', '#ffff00', '1', '110', '0.60', '18.54', '55', '10', '0', '3', '0.2', '50', '20', '129', '17', '20', '100', '25', '0.3', '24', '10');
INSERT INTO `t_testpaper` VALUES ('34', 'ANA-9D', '2', '9', '9', '125', '16.5', '17', '1', '150', '0', '140', '50', '0', 'L90016', '', '#ffff00', '1', '110', '0.60', '18.54', '55', '10', '0', '3', '0.2', '50', '20', '128', '17', '20', '100', '25', '0.3', '24', '10');
INSERT INTO `t_testpaper` VALUES ('35', 'ANA-7', '2', '7', '7', '125', '16.5', '17', '1', '150', '0', '140', '50', '0', 'L90018', '', '#ffff00', '1', '110', '0.60', '18.54', '55', '10', '0', '3', '0.2', '50', '20', '131', '17', '20', '100', '25', '0.3', '24', '10');
INSERT INTO `t_testpaper` VALUES ('921', 'ANA LIA Maxx', '3', '17', '17', '68', '3', '6', '1', '240', '1', '23', '50', '0', 'HM00006', '', '', '0', '110', '1.00', '18.48', '180', '10', '128', '3', '0.2', '50', '20', '1', '17', '20', '100', '25', '0.3', '24', '10');
INSERT INTO `t_testpaper` VALUES ('922', 'ANA-LIA-1(9D) ', '3', '9', '9', '68', '3', '7', '1', '240', '1', '23', '50', '0', 'HM00005', '', '', '0', '140', '1.00', '18.48', '55', '10', '126', '3', '0.2', '50', '20', '2', '17', '20', '100', '25', '0.3', '24', '10');
INSERT INTO `t_testpaper` VALUES ('923', 'ANA-LIA-2(9N) ', '3', '9', '9', '68', '3', '6.5', '1', '240', '1', '23', '50', '0', 'HM00004', '', '', '0', '120', '1.00', '18.48', '55', '10', '126', '3', '0.2', '50', '20', '3', '17', '20', '100', '25', '0.3', '24', '10');
INSERT INTO `t_testpaper` VALUES ('924', 'ANA-LIA(12)', '3', '12', '12', '75', '10', '13.5', '1', '240', '1', '23', '50', '0', 'HM00003', '', '', '0', '100', '1.00', '18.48', '160', '10', '0', '3', '0.2', '50', '20', '4', '17', '20', '100', '25', '0.3', '24', '10');
INSERT INTO `t_testpaper` VALUES ('925', 'Liver-LIA', '3', '6', '6', '68', '2.5', '6.5', '1', '240', '1', '23', '50', '0', 'HM00002', '', '', '0', '120', '1.00', '18.48', '55', '10', '128', '3', '0.2', '50', '20', '5', '17', '20', '100', '25', '0.3', '24', '10');
INSERT INTO `t_testpaper` VALUES ('926', 'Vasculitis-LIA', '3', '3', '3', '68', '11', '15', '1', '240', '1', '23', '50', '0', 'HM00007', '', '', '0', '100', '1.00', '18.48', '200', '10', '125', '3', '0.2', '50', '20', '6', '17', '20', '100', '25', '0.3', '24', '10');
INSERT INTO `t_testpaper` VALUES ('927', 'PNS14-serum', '4', '6', '6', '68', '3.5', '7.5', '1', '240', '1', '210', '50', '0', 'HM00000', '', '#005500', '0', '120', '1.40', '18.61', '55', '10', '116', '3', '0.2', '50', '20', '4', '17', '20', '100', '25', '0.3', '24', '10');
INSERT INTO `t_testpaper` VALUES ('928', 'PNS14-cerebrofluid', '5', '6', '6', '68', '3.5', '7.5', '1', '240', '1', '210', '50', '0', 'HM00001', '', '#ffaa00', '0', '120', '1.40', '18.61', '55', '10', '116', '3', '0.2', '50', '20', '5', '17', '20', '100', '25', '0.3', '24', '10');

-- ----------------------------
-- Table structure for t_testpapercompany
-- ----------------------------
DROP TABLE IF EXISTS `t_testpapercompany`;
CREATE TABLE `t_testpapercompany` (
  `ID` int(10) unsigned NOT NULL AUTO_INCREMENT,
  `Name` varchar(45) NOT NULL,
  PRIMARY KEY (`ID`) USING BTREE,
  UNIQUE KEY `Name_UNIQUE` (`Name`) USING BTREE
) ENGINE=InnoDB AUTO_INCREMENT=6 DEFAULT CHARSET=utf8 ROW_FORMAT=DYNAMIC;

-- ----------------------------
-- Records of t_testpapercompany
-- ----------------------------
INSERT INTO `t_testpapercompany` VALUES ('1', 'human');
INSERT INTO `t_testpapercompany` VALUES ('2', 'human自研');
INSERT INTO `t_testpapercompany` VALUES ('5', 'RAVO-脑脊液');
INSERT INTO `t_testpapercompany` VALUES ('4', 'RAVO-血清');
INSERT INTO `t_testpapercompany` VALUES ('3', 'TEST');

-- ----------------------------
-- Table structure for wgm_reagent
-- ----------------------------
DROP TABLE IF EXISTS `wgm_reagent`;
CREATE TABLE `wgm_reagent` (
  `ID` int(10) unsigned NOT NULL AUTO_INCREMENT,
  `Name` varchar(45) NOT NULL,
  `Company_ID` int(10) unsigned NOT NULL,
  `TestPaper_ID` int(10) unsigned DEFAULT NULL,
  `IsNoDrip` tinyint(1) unsigned NOT NULL,
  `IsSkimp` tinyint(1) unsigned NOT NULL,
  `IsNeedPrepare` tinyint(1) unsigned NOT NULL,
  `PumpNo` int(10) unsigned DEFAULT NULL,
  PRIMARY KEY (`ID`) USING BTREE
) ENGINE=InnoDB AUTO_INCREMENT=2 DEFAULT CHARSET=utf8 ROW_FORMAT=DYNAMIC;

-- ----------------------------
-- Records of wgm_reagent
-- ----------------------------
INSERT INTO `wgm_reagent` VALUES ('1', 'qqq', '1', '1', '1', '1', '1', '1');

-- ----------------------------
-- Table structure for wgm_sample
-- ----------------------------
DROP TABLE IF EXISTS `wgm_sample`;
CREATE TABLE `wgm_sample` (
  `ID` int(10) unsigned NOT NULL AUTO_INCREMENT,
  `ProjectName` varchar(45) NOT NULL DEFAULT '',
  `SampleID` int(10) unsigned DEFAULT NULL,
  `TestPaper_ID` int(10) unsigned DEFAULT NULL,
  `AnalysisState` tinyint(1) unsigned NOT NULL DEFAULT '0',
  `TestDateTime` varchar(19) DEFAULT NULL,
  PRIMARY KEY (`ID`) USING BTREE
) ENGINE=InnoDB AUTO_INCREMENT=5 DEFAULT CHARSET=utf8 ROW_FORMAT=DYNAMIC;

-- ----------------------------
-- Records of wgm_sample
-- ----------------------------
INSERT INTO `wgm_sample` VALUES ('1', 'project001', '1', '1', '0', '2022-02-24 14:32:02');
INSERT INTO `wgm_sample` VALUES ('2', 'project001', '2', '1', '0', '2022-02-14 16:14:41');
INSERT INTO `wgm_sample` VALUES ('3', 'project001', '3', '1', '0', '2022-02-14 15:30:04');
INSERT INTO `wgm_sample` VALUES ('4', 'project001', '4', '1', '0', '2022-02-14 15:30:11');

-- ----------------------------
-- Table structure for wgm_systemset
-- ----------------------------
DROP TABLE IF EXISTS `wgm_systemset`;
CREATE TABLE `wgm_systemset` (
  `id` int(11) unsigned NOT NULL,
  `saveSet` int(11) DEFAULT '0',
  `saveDes` varchar(256) DEFAULT '',
  `remark` varchar(512) DEFAULT '',
  PRIMARY KEY (`id`) USING BTREE
) ENGINE=InnoDB DEFAULT CHARSET=utf8 ROW_FORMAT=DYNAMIC;

-- ----------------------------
-- Records of wgm_systemset
-- ----------------------------
INSERT INTO `wgm_systemset` VALUES ('1', '0', '40', '功能条灰度阈值');
INSERT INTO `wgm_systemset` VALUES ('2', '0', '18', 'Cut Off条灰度阈值');
INSERT INTO `wgm_systemset` VALUES ('3', '0', 'D:\\HumablotProFiles\\TestPictures', '测试图像保存根目录');
INSERT INTO `wgm_systemset` VALUES ('4', '0', 'D:\\HumablotProFiles\\Reports', '测试报告保存根目录');

-- ----------------------------
-- Table structure for wgm_testdata
-- ----------------------------
DROP TABLE IF EXISTS `wgm_testdata`;
CREATE TABLE `wgm_testdata` (
  `ID` int(10) unsigned NOT NULL AUTO_INCREMENT,
  `ProjectName` varchar(45) NOT NULL DEFAULT '',
  `SampleID` int(10) unsigned DEFAULT NULL,
  `TestPaper_ID` int(10) unsigned DEFAULT NULL,
  `ItemName` varchar(45) NOT NULL,
  `Position` int(10) unsigned NOT NULL,
  `GrayValue` double NOT NULL,
  `RatioToCut` double NOT NULL,
  `Diagnosis` varchar(16) DEFAULT NULL,
  `TestDateTime` varchar(19) NOT NULL,
  PRIMARY KEY (`ID`) USING BTREE
) ENGINE=InnoDB AUTO_INCREMENT=1135 DEFAULT CHARSET=utf8 ROW_FORMAT=DYNAMIC;

-- ----------------------------
-- Records of wgm_testdata
-- ----------------------------
INSERT INTO `wgm_testdata` VALUES ('883', 'project001', '1', '1', 'FC', '197', '117.392', '4.8213', '+++', '2021-09-15 10:16:25');
INSERT INTO `wgm_testdata` VALUES ('884', 'project001', '1', '1', 'Cut', '271', '24.3485', '1', 'O', '2021-09-15 10:16:25');
INSERT INTO `wgm_testdata` VALUES ('885', 'project001', '1', '1', 'Nucleosomes', '348', '83.2895', '3.42072', '++', '2021-09-15 10:16:25');
INSERT INTO `wgm_testdata` VALUES ('886', 'project001', '1', '1', 'dsDNA', '430', '52.1198', '2.14057', '+', '2021-09-15 10:16:25');
INSERT INTO `wgm_testdata` VALUES ('887', 'project001', '1', '1', 'Histones', '511', '89.95', '3.69427', '++', '2021-09-15 10:16:25');
INSERT INTO `wgm_testdata` VALUES ('888', 'project001', '1', '1', 'SmD1', '591', '100.468', '4.12625', '+++', '2021-09-15 10:16:25');
INSERT INTO `wgm_testdata` VALUES ('889', 'project001', '1', '1', 'U1-snRNP', '670', '158.716', '6.51851', '+++', '2021-09-15 10:16:25');
INSERT INTO `wgm_testdata` VALUES ('890', 'project001', '1', '1', 'SSA/Ro 60', '748', '39.1688', '1.60867', '+', '2021-09-15 10:16:25');
INSERT INTO `wgm_testdata` VALUES ('891', 'project001', '1', '1', 'SSA/Ro 52', '819', '3.14196', '0.129041', '-', '2021-09-15 10:16:25');
INSERT INTO `wgm_testdata` VALUES ('892', 'project001', '1', '1', 'SSB/La', '896', '65.988', '2.71014', '++', '2021-09-15 10:16:25');
INSERT INTO `wgm_testdata` VALUES ('893', 'project001', '1', '1', 'Scl 70', '979', '37.1522', '1.52585', '+', '2021-09-15 10:16:25');
INSERT INTO `wgm_testdata` VALUES ('894', 'project001', '1', '1', 'CENP-B', '1060', '28.9961', '1.19088', 'O', '2021-09-15 10:16:25');
INSERT INTO `wgm_testdata` VALUES ('895', 'project001', '1', '1', 'Jo-1', '1136', '6.80483', '0.279476', '-', '2021-09-15 10:16:25');
INSERT INTO `wgm_testdata` VALUES ('896', 'project001', '1', '1', 'RPP/P0', '1221', '192.857', '7.92067', '+++', '2021-09-15 10:16:25');
INSERT INTO `wgm_testdata` VALUES ('897', 'project001', '2', '1', 'FC', '198', '115.216', '4.37672', '+++', '2021-09-15 10:16:26');
INSERT INTO `wgm_testdata` VALUES ('898', 'project001', '2', '1', 'Cut', '272', '26.3248', '1', 'O', '2021-09-15 10:16:26');
INSERT INTO `wgm_testdata` VALUES ('899', 'project001', '2', '1', 'Nucleosomes', '349', '88.0084', '3.34318', '++', '2021-09-15 10:16:26');
INSERT INTO `wgm_testdata` VALUES ('900', 'project001', '2', '1', 'dsDNA', '431', '64.7651', '2.46023', '+', '2021-09-15 10:16:26');
INSERT INTO `wgm_testdata` VALUES ('901', 'project001', '2', '1', 'Histones', '512', '106.711', '4.05364', '+++', '2021-09-15 10:16:26');
INSERT INTO `wgm_testdata` VALUES ('902', 'project001', '2', '1', 'SmD1', '592', '101.098', '3.8404', '++', '2021-09-15 10:16:26');
INSERT INTO `wgm_testdata` VALUES ('903', 'project001', '2', '1', 'U1-snRNP', '671', '166.1', '6.30967', '+++', '2021-09-15 10:16:26');
INSERT INTO `wgm_testdata` VALUES ('904', 'project001', '2', '1', 'SSA/Ro 60', '749', '38.5243', '1.46343', '+', '2021-09-15 10:16:26');
INSERT INTO `wgm_testdata` VALUES ('905', 'project001', '2', '1', 'SSA/Ro 52', '821', '6.982', '0.265226', '-', '2021-09-15 10:16:26');
INSERT INTO `wgm_testdata` VALUES ('906', 'project001', '2', '1', 'SSB/La', '897', '67.8779', '2.57848', '++', '2021-09-15 10:16:26');
INSERT INTO `wgm_testdata` VALUES ('907', 'project001', '2', '1', 'Scl 70', '979', '38.8663', '1.47642', '+', '2021-09-15 10:16:26');
INSERT INTO `wgm_testdata` VALUES ('908', 'project001', '2', '1', 'CENP-B', '1061', '30.1714', '1.14612', 'O', '2021-09-15 10:16:26');
INSERT INTO `wgm_testdata` VALUES ('909', 'project001', '2', '1', 'Jo-1', '1136', '6.94873', '0.263962', '-', '2021-09-15 10:16:26');
INSERT INTO `wgm_testdata` VALUES ('910', 'project001', '2', '1', 'RPP/P0', '1222', '204.61', '7.77251', '+++', '2021-09-15 10:16:26');
INSERT INTO `wgm_testdata` VALUES ('911', 'project001', '3', '1', 'FC', '198', '115.581', '4.69726', '+++', '2021-09-15 10:16:26');
INSERT INTO `wgm_testdata` VALUES ('912', 'project001', '3', '1', 'Cut', '273', '24.6059', '1', 'O', '2021-09-15 10:16:26');
INSERT INTO `wgm_testdata` VALUES ('913', 'project001', '3', '1', 'Nucleosomes', '349', '88.1521', '3.58256', '++', '2021-09-15 10:16:26');
INSERT INTO `wgm_testdata` VALUES ('914', 'project001', '3', '1', 'dsDNA', '431', '66.4237', '2.6995', '++', '2021-09-15 10:16:26');
INSERT INTO `wgm_testdata` VALUES ('915', 'project001', '3', '1', 'Histones', '512', '107.386', '4.36423', '+++', '2021-09-15 10:16:26');
INSERT INTO `wgm_testdata` VALUES ('916', 'project001', '3', '1', 'SmD1', '592', '107.985', '4.38857', '+++', '2021-09-15 10:16:26');
INSERT INTO `wgm_testdata` VALUES ('917', 'project001', '3', '1', 'U1-snRNP', '671', '158.491', '6.44118', '+++', '2021-09-15 10:16:26');
INSERT INTO `wgm_testdata` VALUES ('918', 'project001', '3', '1', 'SSA/Ro 60', '749', '38.8021', '1.57694', '+', '2021-09-15 10:16:26');
INSERT INTO `wgm_testdata` VALUES ('919', 'project001', '3', '1', 'SSA/Ro 52', '821', '5.00775', '0.203518', '-', '2021-09-15 10:16:26');
INSERT INTO `wgm_testdata` VALUES ('920', 'project001', '3', '1', 'SSB/La', '897', '63.8066', '2.59314', '++', '2021-09-15 10:16:26');
INSERT INTO `wgm_testdata` VALUES ('921', 'project001', '3', '1', 'Scl 70', '980', '38.3426', '1.55827', '+', '2021-09-15 10:16:26');
INSERT INTO `wgm_testdata` VALUES ('922', 'project001', '3', '1', 'CENP-B', '1061', '29.6847', '1.2064', '+', '2021-09-15 10:16:26');
INSERT INTO `wgm_testdata` VALUES ('923', 'project001', '3', '1', 'Jo-1', '1137', '4.05602', '0.164839', '-', '2021-09-15 10:16:26');
INSERT INTO `wgm_testdata` VALUES ('924', 'project001', '3', '1', 'RPP/P0', '1223', '196.598', '7.98985', '+++', '2021-09-15 10:16:26');
INSERT INTO `wgm_testdata` VALUES ('925', 'project001', '4', '1', 'FC', '200', '118.529', '3.86713', '++', '2021-09-15 10:16:27');
INSERT INTO `wgm_testdata` VALUES ('926', 'project001', '4', '1', 'Cut', '274', '30.6502', '1', 'O', '2021-09-15 10:16:27');
INSERT INTO `wgm_testdata` VALUES ('927', 'project001', '4', '1', 'Nucleosomes', '351', '94.4527', '3.08163', '++', '2021-09-15 10:16:27');
INSERT INTO `wgm_testdata` VALUES ('928', 'project001', '4', '1', 'dsDNA', '433', '66.0231', '2.15408', '+', '2021-09-15 10:16:27');
INSERT INTO `wgm_testdata` VALUES ('929', 'project001', '4', '1', 'Histones', '514', '108.01', '3.52397', '++', '2021-09-15 10:16:27');
INSERT INTO `wgm_testdata` VALUES ('930', 'project001', '4', '1', 'SmD1', '594', '108.532', '3.54098', '++', '2021-09-15 10:16:27');
INSERT INTO `wgm_testdata` VALUES ('931', 'project001', '4', '1', 'U1-snRNP', '673', '165.824', '5.41022', '+++', '2021-09-15 10:16:27');
INSERT INTO `wgm_testdata` VALUES ('932', 'project001', '4', '1', 'SSA/Ro 60', '750', '40.7785', '1.33045', '+', '2021-09-15 10:16:27');
INSERT INTO `wgm_testdata` VALUES ('933', 'project001', '4', '1', 'SSA/Ro 52', '823', '6.78529', '0.221378', '-', '2021-09-15 10:16:27');
INSERT INTO `wgm_testdata` VALUES ('934', 'project001', '4', '1', 'SSB/La', '898', '68.4273', '2.23252', '+', '2021-09-15 10:16:27');
INSERT INTO `wgm_testdata` VALUES ('935', 'project001', '4', '1', 'Scl 70', '981', '37.944', '1.23797', '+', '2021-09-15 10:16:27');
INSERT INTO `wgm_testdata` VALUES ('936', 'project001', '4', '1', 'CENP-B', '1062', '29.6193', '0.966364', 'O', '2021-09-15 10:16:27');
INSERT INTO `wgm_testdata` VALUES ('937', 'project001', '4', '1', 'Jo-1', '1138', '3.55281', '0.115915', '-', '2021-09-15 10:16:27');
INSERT INTO `wgm_testdata` VALUES ('938', 'project001', '4', '1', 'RPP/P0', '1224', '200.043', '6.52663', '+++', '2021-09-15 10:16:27');
INSERT INTO `wgm_testdata` VALUES ('939', 'project001', '3', '1', 'FC', '172', '114.162', '5.10252', '+++', '2022-01-24 10:10:53');
INSERT INTO `wgm_testdata` VALUES ('940', 'project001', '3', '1', 'Cut', '247', '22.3736', '1', 'O', '2022-01-24 10:10:53');
INSERT INTO `wgm_testdata` VALUES ('941', 'project001', '3', '1', 'Nucleosomes', '317', '43.2279', '1.9321', '+', '2022-01-24 10:10:53');
INSERT INTO `wgm_testdata` VALUES ('942', 'project001', '3', '1', 'dsDNA', '391', '52.0278', '2.32541', '+', '2022-01-24 10:10:53');
INSERT INTO `wgm_testdata` VALUES ('943', 'project001', '3', '1', 'Histones', '466', '42.8838', '1.91672', '+', '2022-01-24 10:10:53');
INSERT INTO `wgm_testdata` VALUES ('944', 'project001', '3', '1', 'SmD1', '538', '65.1344', '2.91122', '++', '2022-01-24 10:10:53');
INSERT INTO `wgm_testdata` VALUES ('945', 'project001', '3', '1', 'U1-snRNP', '614', '30.6769', '1.37112', '+', '2022-01-24 10:10:53');
INSERT INTO `wgm_testdata` VALUES ('946', 'project001', '3', '1', 'SSA/Ro 60', '689', '150.735', '6.7372', '+++', '2022-01-24 10:10:53');
INSERT INTO `wgm_testdata` VALUES ('947', 'project001', '3', '1', 'SSA/Ro 52', '760', '96.801', '4.32658', '+++', '2022-01-24 10:10:53');
INSERT INTO `wgm_testdata` VALUES ('948', 'project001', '3', '1', 'SSB/La', '835', '152.594', '6.82025', '+++', '2022-01-24 10:10:53');
INSERT INTO `wgm_testdata` VALUES ('949', 'project001', '3', '1', 'Scl 70', '884', '-2.17914', '-0.0973978', '-', '2022-01-24 10:10:53');
INSERT INTO `wgm_testdata` VALUES ('950', 'project001', '3', '1', 'CENP-B', '987', '38.6338', '1.72676', '+', '2022-01-24 10:10:53');
INSERT INTO `wgm_testdata` VALUES ('951', 'project001', '3', '1', 'Jo-1', '1058', '31.2698', '1.39762', '+', '2022-01-24 10:10:53');
INSERT INTO `wgm_testdata` VALUES ('952', 'project001', '3', '1', 'RPP/P0', '1129', '30.4388', '1.36048', '+', '2022-01-24 10:10:53');
INSERT INTO `wgm_testdata` VALUES ('953', 'project001', '1', '1', 'FC', '197', '117.258', '4.81773', '+++', '2022-02-14 14:51:25');
INSERT INTO `wgm_testdata` VALUES ('954', 'project001', '1', '1', 'Cut', '271', '24.3388', '1', 'O', '2022-02-14 14:51:25');
INSERT INTO `wgm_testdata` VALUES ('955', 'project001', '1', '1', '', '348', '83.1774', '3.41748', '++', '2022-02-14 14:51:25');
INSERT INTO `wgm_testdata` VALUES ('956', 'project001', '1', '1', '', '430', '51.86', '2.13075', '+', '2022-02-14 14:51:25');
INSERT INTO `wgm_testdata` VALUES ('957', 'project001', '1', '1', '', '511', '89.7757', '3.68858', '++', '2022-02-14 14:51:25');
INSERT INTO `wgm_testdata` VALUES ('958', 'project001', '1', '1', '', '591', '100.446', '4.12698', '+++', '2022-02-14 14:51:25');
INSERT INTO `wgm_testdata` VALUES ('959', 'project001', '1', '1', '', '670', '158.861', '6.52709', '+++', '2022-02-14 14:51:25');
INSERT INTO `wgm_testdata` VALUES ('960', 'project001', '1', '1', '', '748', '39.2513', '1.61271', '+', '2022-02-14 14:51:25');
INSERT INTO `wgm_testdata` VALUES ('961', 'project001', '1', '1', '', '819', '3.2667', '0.134218', '-', '2022-02-14 14:51:25');
INSERT INTO `wgm_testdata` VALUES ('962', 'project001', '1', '1', '', '896', '65.9054', '2.70783', '++', '2022-02-14 14:51:25');
INSERT INTO `wgm_testdata` VALUES ('963', 'project001', '1', '1', '', '979', '37.3053', '1.53275', '+', '2022-02-14 14:51:25');
INSERT INTO `wgm_testdata` VALUES ('964', 'project001', '1', '1', '', '1060', '28.9926', '1.19121', 'O', '2022-02-14 14:51:25');
INSERT INTO `wgm_testdata` VALUES ('965', 'project001', '1', '1', '', '1136', '6.80512', '0.2796', '-', '2022-02-14 14:51:25');
INSERT INTO `wgm_testdata` VALUES ('966', 'project001', '1', '1', '', '1221', '193.018', '7.93046', '+++', '2022-02-14 14:51:25');
INSERT INTO `wgm_testdata` VALUES ('967', 'project001', '2', '1', 'FC', '198', '115.265', '4.39943', '+++', '2022-02-14 14:51:26');
INSERT INTO `wgm_testdata` VALUES ('968', 'project001', '2', '1', 'Cut', '272', '26.1999', '1', 'O', '2022-02-14 14:51:26');
INSERT INTO `wgm_testdata` VALUES ('969', 'project001', '2', '1', '', '349', '87.5953', '3.34334', '++', '2022-02-14 14:51:26');
INSERT INTO `wgm_testdata` VALUES ('970', 'project001', '2', '1', '', '431', '64.4461', '2.45978', '+', '2022-02-14 14:51:26');
INSERT INTO `wgm_testdata` VALUES ('971', 'project001', '2', '1', '', '512', '106.722', '4.07335', '+++', '2022-02-14 14:51:26');
INSERT INTO `wgm_testdata` VALUES ('972', 'project001', '2', '1', '', '592', '101.058', '3.85717', '++', '2022-02-14 14:51:26');
INSERT INTO `wgm_testdata` VALUES ('973', 'project001', '2', '1', '', '671', '166.239', '6.345', '+++', '2022-02-14 14:51:26');
INSERT INTO `wgm_testdata` VALUES ('974', 'project001', '2', '1', '', '749', '38.8127', '1.4814', '+', '2022-02-14 14:51:26');
INSERT INTO `wgm_testdata` VALUES ('975', 'project001', '2', '1', '', '821', '7.05875', '0.269419', '-', '2022-02-14 14:51:26');
INSERT INTO `wgm_testdata` VALUES ('976', 'project001', '2', '1', '', '897', '68.0136', '2.59594', '++', '2022-02-14 14:51:26');
INSERT INTO `wgm_testdata` VALUES ('977', 'project001', '2', '1', '', '979', '38.6695', '1.47594', '+', '2022-02-14 14:51:26');
INSERT INTO `wgm_testdata` VALUES ('978', 'project001', '2', '1', '', '1061', '30.2034', '1.15281', 'O', '2022-02-14 14:51:26');
INSERT INTO `wgm_testdata` VALUES ('979', 'project001', '2', '1', '', '1136', '6.76169', '0.25808', '-', '2022-02-14 14:51:26');
INSERT INTO `wgm_testdata` VALUES ('980', 'project001', '2', '1', '', '1222', '204.657', '7.81134', '+++', '2022-02-14 14:51:26');
INSERT INTO `wgm_testdata` VALUES ('981', 'project001', '3', '1', 'FC', '198', '115.443', '4.72724', '+++', '2022-02-14 14:51:28');
INSERT INTO `wgm_testdata` VALUES ('982', 'project001', '3', '1', 'Cut', '273', '24.4207', '1', 'O', '2022-02-14 14:51:28');
INSERT INTO `wgm_testdata` VALUES ('983', 'project001', '3', '1', '', '349', '87.8024', '3.5954', '++', '2022-02-14 14:51:28');
INSERT INTO `wgm_testdata` VALUES ('984', 'project001', '3', '1', '', '431', '66.2274', '2.71193', '++', '2022-02-14 14:51:28');
INSERT INTO `wgm_testdata` VALUES ('985', 'project001', '3', '1', '', '512', '107.55', '4.40404', '+++', '2022-02-14 14:51:28');
INSERT INTO `wgm_testdata` VALUES ('986', 'project001', '3', '1', '', '592', '108.251', '4.43276', '+++', '2022-02-14 14:51:28');
INSERT INTO `wgm_testdata` VALUES ('987', 'project001', '3', '1', '', '671', '158.546', '6.49227', '+++', '2022-02-14 14:51:28');
INSERT INTO `wgm_testdata` VALUES ('988', 'project001', '3', '1', '', '749', '39.1452', '1.60295', '+', '2022-02-14 14:51:28');
INSERT INTO `wgm_testdata` VALUES ('989', 'project001', '3', '1', '', '821', '5.16664', '0.211568', '-', '2022-02-14 14:51:28');
INSERT INTO `wgm_testdata` VALUES ('990', 'project001', '3', '1', '', '897', '63.7618', '2.61097', '++', '2022-02-14 14:51:28');
INSERT INTO `wgm_testdata` VALUES ('991', 'project001', '3', '1', '', '980', '38.3545', '1.57057', '+', '2022-02-14 14:51:28');
INSERT INTO `wgm_testdata` VALUES ('992', 'project001', '3', '1', '', '1061', '29.6901', '1.21577', '+', '2022-02-14 14:51:28');
INSERT INTO `wgm_testdata` VALUES ('993', 'project001', '3', '1', '', '1137', '4.02949', '0.165003', '-', '2022-02-14 14:51:28');
INSERT INTO `wgm_testdata` VALUES ('994', 'project001', '3', '1', '', '1223', '196.916', '8.06348', '+++', '2022-02-14 14:51:28');
INSERT INTO `wgm_testdata` VALUES ('995', 'project001', '4', '1', 'FC', '200', '118.486', '3.86005', '++', '2022-02-14 14:51:30');
INSERT INTO `wgm_testdata` VALUES ('996', 'project001', '4', '1', 'Cut', '274', '30.6955', '1', 'O', '2022-02-14 14:51:30');
INSERT INTO `wgm_testdata` VALUES ('997', 'project001', '4', '1', '', '351', '94.2972', '3.07202', '++', '2022-02-14 14:51:30');
INSERT INTO `wgm_testdata` VALUES ('998', 'project001', '4', '1', '', '433', '65.8845', '2.14639', '+', '2022-02-14 14:51:30');
INSERT INTO `wgm_testdata` VALUES ('999', 'project001', '4', '1', '', '514', '108.27', '3.52723', '++', '2022-02-14 14:51:30');
INSERT INTO `wgm_testdata` VALUES ('1000', 'project001', '4', '1', '', '594', '108.615', '3.53847', '++', '2022-02-14 14:51:30');
INSERT INTO `wgm_testdata` VALUES ('1001', 'project001', '4', '1', '', '673', '166.029', '5.40889', '+++', '2022-02-14 14:51:30');
INSERT INTO `wgm_testdata` VALUES ('1002', 'project001', '4', '1', '', '750', '40.8273', '1.33007', '+', '2022-02-14 14:51:30');
INSERT INTO `wgm_testdata` VALUES ('1003', 'project001', '4', '1', '', '823', '6.75064', '0.219923', '-', '2022-02-14 14:51:30');
INSERT INTO `wgm_testdata` VALUES ('1004', 'project001', '4', '1', '', '898', '68.4698', '2.23061', '+', '2022-02-14 14:51:30');
INSERT INTO `wgm_testdata` VALUES ('1005', 'project001', '4', '1', '', '981', '37.6791', '1.22751', '+', '2022-02-14 14:51:30');
INSERT INTO `wgm_testdata` VALUES ('1006', 'project001', '4', '1', '', '1062', '29.561', '0.963039', 'O', '2022-02-14 14:51:30');
INSERT INTO `wgm_testdata` VALUES ('1007', 'project001', '4', '1', '', '1138', '3.523', '0.114773', '-', '2022-02-14 14:51:30');
INSERT INTO `wgm_testdata` VALUES ('1008', 'project001', '4', '1', '', '1224', '200.15', '6.52048', '+++', '2022-02-14 14:51:30');
INSERT INTO `wgm_testdata` VALUES ('1009', 'project001', '1', '1', 'FC', '197', '117.258', '4.81773', '+++', '2022-02-14 15:07:39');
INSERT INTO `wgm_testdata` VALUES ('1010', 'project001', '1', '1', 'Cut', '271', '24.3388', '1', 'O', '2022-02-14 15:07:39');
INSERT INTO `wgm_testdata` VALUES ('1011', 'project001', '1', '1', '', '348', '83.1774', '3.41748', '++', '2022-02-14 15:07:39');
INSERT INTO `wgm_testdata` VALUES ('1012', 'project001', '1', '1', '', '430', '51.86', '2.13075', '+', '2022-02-14 15:07:39');
INSERT INTO `wgm_testdata` VALUES ('1013', 'project001', '1', '1', '', '511', '89.7757', '3.68858', '++', '2022-02-14 15:07:39');
INSERT INTO `wgm_testdata` VALUES ('1014', 'project001', '1', '1', '', '591', '100.446', '4.12698', '+++', '2022-02-14 15:07:39');
INSERT INTO `wgm_testdata` VALUES ('1015', 'project001', '1', '1', '', '670', '158.861', '6.52709', '+++', '2022-02-14 15:07:39');
INSERT INTO `wgm_testdata` VALUES ('1016', 'project001', '1', '1', '', '748', '39.2513', '1.61271', '+', '2022-02-14 15:07:39');
INSERT INTO `wgm_testdata` VALUES ('1017', 'project001', '1', '1', '', '819', '3.2667', '0.134218', '-', '2022-02-14 15:07:39');
INSERT INTO `wgm_testdata` VALUES ('1018', 'project001', '1', '1', '', '896', '65.9054', '2.70783', '++', '2022-02-14 15:07:39');
INSERT INTO `wgm_testdata` VALUES ('1019', 'project001', '1', '1', '', '979', '37.3053', '1.53275', '+', '2022-02-14 15:07:39');
INSERT INTO `wgm_testdata` VALUES ('1020', 'project001', '1', '1', '', '1060', '28.9926', '1.19121', 'O', '2022-02-14 15:07:39');
INSERT INTO `wgm_testdata` VALUES ('1021', 'project001', '1', '1', '', '1136', '6.80512', '0.2796', '-', '2022-02-14 15:07:39');
INSERT INTO `wgm_testdata` VALUES ('1022', 'project001', '1', '1', '', '1221', '193.018', '7.93046', '+++', '2022-02-14 15:07:39');
INSERT INTO `wgm_testdata` VALUES ('1023', 'project001', '2', '1', 'FC', '198', '115.265', '4.39943', '+++', '2022-02-14 15:15:51');
INSERT INTO `wgm_testdata` VALUES ('1024', 'project001', '2', '1', 'Cut', '272', '26.1999', '1', 'O', '2022-02-14 15:15:51');
INSERT INTO `wgm_testdata` VALUES ('1025', 'project001', '2', '1', '', '349', '87.5953', '3.34334', '++', '2022-02-14 15:15:51');
INSERT INTO `wgm_testdata` VALUES ('1026', 'project001', '2', '1', '', '431', '64.4461', '2.45978', '+', '2022-02-14 15:15:51');
INSERT INTO `wgm_testdata` VALUES ('1027', 'project001', '2', '1', '', '512', '106.722', '4.07335', '+++', '2022-02-14 15:15:51');
INSERT INTO `wgm_testdata` VALUES ('1028', 'project001', '2', '1', '', '592', '101.058', '3.85717', '++', '2022-02-14 15:15:51');
INSERT INTO `wgm_testdata` VALUES ('1029', 'project001', '2', '1', '', '671', '166.239', '6.345', '+++', '2022-02-14 15:15:51');
INSERT INTO `wgm_testdata` VALUES ('1030', 'project001', '2', '1', '', '749', '38.8127', '1.4814', '+', '2022-02-14 15:15:51');
INSERT INTO `wgm_testdata` VALUES ('1031', 'project001', '2', '1', '', '821', '7.05875', '0.269419', '-', '2022-02-14 15:15:51');
INSERT INTO `wgm_testdata` VALUES ('1032', 'project001', '2', '1', '', '897', '68.0136', '2.59594', '++', '2022-02-14 15:15:51');
INSERT INTO `wgm_testdata` VALUES ('1033', 'project001', '2', '1', '', '979', '38.6695', '1.47594', '+', '2022-02-14 15:15:51');
INSERT INTO `wgm_testdata` VALUES ('1034', 'project001', '2', '1', '', '1061', '30.2034', '1.15281', 'O', '2022-02-14 15:15:51');
INSERT INTO `wgm_testdata` VALUES ('1035', 'project001', '2', '1', '', '1136', '6.76169', '0.25808', '-', '2022-02-14 15:15:51');
INSERT INTO `wgm_testdata` VALUES ('1036', 'project001', '2', '1', '', '1222', '204.657', '7.81134', '+++', '2022-02-14 15:15:51');
INSERT INTO `wgm_testdata` VALUES ('1037', 'project001', '3', '1', 'FC', '198', '115.443', '4.72724', '+++', '2022-02-14 15:30:06');
INSERT INTO `wgm_testdata` VALUES ('1038', 'project001', '3', '1', 'Cut', '273', '24.4207', '1', 'O', '2022-02-14 15:30:06');
INSERT INTO `wgm_testdata` VALUES ('1039', 'project001', '3', '1', '', '349', '87.8024', '3.5954', '++', '2022-02-14 15:30:06');
INSERT INTO `wgm_testdata` VALUES ('1040', 'project001', '3', '1', '', '431', '66.2274', '2.71193', '++', '2022-02-14 15:30:06');
INSERT INTO `wgm_testdata` VALUES ('1041', 'project001', '3', '1', '', '512', '107.55', '4.40404', '+++', '2022-02-14 15:30:06');
INSERT INTO `wgm_testdata` VALUES ('1042', 'project001', '3', '1', '', '592', '108.251', '4.43276', '+++', '2022-02-14 15:30:06');
INSERT INTO `wgm_testdata` VALUES ('1043', 'project001', '3', '1', '', '671', '158.546', '6.49227', '+++', '2022-02-14 15:30:06');
INSERT INTO `wgm_testdata` VALUES ('1044', 'project001', '3', '1', '', '749', '39.1452', '1.60295', '+', '2022-02-14 15:30:06');
INSERT INTO `wgm_testdata` VALUES ('1045', 'project001', '3', '1', '', '821', '5.16664', '0.211568', '-', '2022-02-14 15:30:06');
INSERT INTO `wgm_testdata` VALUES ('1046', 'project001', '3', '1', '', '897', '63.7618', '2.61097', '++', '2022-02-14 15:30:06');
INSERT INTO `wgm_testdata` VALUES ('1047', 'project001', '3', '1', '', '980', '38.3545', '1.57057', '+', '2022-02-14 15:30:06');
INSERT INTO `wgm_testdata` VALUES ('1048', 'project001', '3', '1', '', '1061', '29.6901', '1.21577', '+', '2022-02-14 15:30:06');
INSERT INTO `wgm_testdata` VALUES ('1049', 'project001', '3', '1', '', '1137', '4.02949', '0.165003', '-', '2022-02-14 15:30:06');
INSERT INTO `wgm_testdata` VALUES ('1050', 'project001', '3', '1', '', '1223', '196.916', '8.06348', '+++', '2022-02-14 15:30:06');
INSERT INTO `wgm_testdata` VALUES ('1051', 'project001', '4', '1', 'FC', '200', '118.486', '3.86005', '++', '2022-02-14 15:30:12');
INSERT INTO `wgm_testdata` VALUES ('1052', 'project001', '4', '1', 'Cut', '274', '30.6955', '1', 'O', '2022-02-14 15:30:12');
INSERT INTO `wgm_testdata` VALUES ('1053', 'project001', '4', '1', '', '351', '94.2972', '3.07202', '++', '2022-02-14 15:30:12');
INSERT INTO `wgm_testdata` VALUES ('1054', 'project001', '4', '1', '', '433', '65.8845', '2.14639', '+', '2022-02-14 15:30:12');
INSERT INTO `wgm_testdata` VALUES ('1055', 'project001', '4', '1', '', '514', '108.27', '3.52723', '++', '2022-02-14 15:30:12');
INSERT INTO `wgm_testdata` VALUES ('1056', 'project001', '4', '1', '', '594', '108.615', '3.53847', '++', '2022-02-14 15:30:12');
INSERT INTO `wgm_testdata` VALUES ('1057', 'project001', '4', '1', '', '673', '166.029', '5.40889', '+++', '2022-02-14 15:30:12');
INSERT INTO `wgm_testdata` VALUES ('1058', 'project001', '4', '1', '', '750', '40.8273', '1.33007', '+', '2022-02-14 15:30:12');
INSERT INTO `wgm_testdata` VALUES ('1059', 'project001', '4', '1', '', '823', '6.75064', '0.219923', '-', '2022-02-14 15:30:12');
INSERT INTO `wgm_testdata` VALUES ('1060', 'project001', '4', '1', '', '898', '68.4698', '2.23061', '+', '2022-02-14 15:30:12');
INSERT INTO `wgm_testdata` VALUES ('1061', 'project001', '4', '1', '', '981', '37.6791', '1.22751', '+', '2022-02-14 15:30:12');
INSERT INTO `wgm_testdata` VALUES ('1062', 'project001', '4', '1', '', '1062', '29.561', '0.963039', 'O', '2022-02-14 15:30:12');
INSERT INTO `wgm_testdata` VALUES ('1063', 'project001', '4', '1', '', '1138', '3.523', '0.114773', '-', '2022-02-14 15:30:12');
INSERT INTO `wgm_testdata` VALUES ('1064', 'project001', '4', '1', '', '1224', '200.15', '6.52048', '+++', '2022-02-14 15:30:12');
INSERT INTO `wgm_testdata` VALUES ('1065', 'project001', '1', '1', 'FC', '197', '117.258', '4.81773', '+++', '2022-02-14 16:14:28');
INSERT INTO `wgm_testdata` VALUES ('1066', 'project001', '1', '1', 'Cut', '271', '24.3388', '1', 'O', '2022-02-14 16:14:28');
INSERT INTO `wgm_testdata` VALUES ('1067', 'project001', '1', '1', '', '348', '83.1774', '3.41748', '++', '2022-02-14 16:14:28');
INSERT INTO `wgm_testdata` VALUES ('1068', 'project001', '1', '1', '', '430', '51.86', '2.13075', '+', '2022-02-14 16:14:28');
INSERT INTO `wgm_testdata` VALUES ('1069', 'project001', '1', '1', '', '511', '89.7757', '3.68858', '++', '2022-02-14 16:14:28');
INSERT INTO `wgm_testdata` VALUES ('1070', 'project001', '1', '1', '', '591', '100.446', '4.12698', '+++', '2022-02-14 16:14:28');
INSERT INTO `wgm_testdata` VALUES ('1071', 'project001', '1', '1', '', '670', '158.861', '6.52709', '+++', '2022-02-14 16:14:28');
INSERT INTO `wgm_testdata` VALUES ('1072', 'project001', '1', '1', '', '748', '39.2513', '1.61271', '+', '2022-02-14 16:14:28');
INSERT INTO `wgm_testdata` VALUES ('1073', 'project001', '1', '1', '', '819', '3.2667', '0.134218', '-', '2022-02-14 16:14:28');
INSERT INTO `wgm_testdata` VALUES ('1074', 'project001', '1', '1', '', '896', '65.9054', '2.70783', '++', '2022-02-14 16:14:28');
INSERT INTO `wgm_testdata` VALUES ('1075', 'project001', '1', '1', '', '979', '37.3053', '1.53275', '+', '2022-02-14 16:14:28');
INSERT INTO `wgm_testdata` VALUES ('1076', 'project001', '1', '1', '', '1060', '28.9926', '1.19121', 'O', '2022-02-14 16:14:28');
INSERT INTO `wgm_testdata` VALUES ('1077', 'project001', '1', '1', '', '1136', '6.80512', '0.2796', '-', '2022-02-14 16:14:28');
INSERT INTO `wgm_testdata` VALUES ('1078', 'project001', '1', '1', '', '1221', '193.018', '7.93046', '+++', '2022-02-14 16:14:28');
INSERT INTO `wgm_testdata` VALUES ('1079', 'project001', '2', '1', 'FC', '198', '115.265', '4.39943', '+++', '2022-02-14 16:14:42');
INSERT INTO `wgm_testdata` VALUES ('1080', 'project001', '2', '1', 'Cut', '272', '26.1999', '1', 'O', '2022-02-14 16:14:42');
INSERT INTO `wgm_testdata` VALUES ('1081', 'project001', '2', '1', '', '349', '87.5953', '3.34334', '++', '2022-02-14 16:14:42');
INSERT INTO `wgm_testdata` VALUES ('1082', 'project001', '2', '1', '', '431', '64.4461', '2.45978', '+', '2022-02-14 16:14:42');
INSERT INTO `wgm_testdata` VALUES ('1083', 'project001', '2', '1', '', '512', '106.722', '4.07335', '+++', '2022-02-14 16:14:42');
INSERT INTO `wgm_testdata` VALUES ('1084', 'project001', '2', '1', '', '592', '101.058', '3.85717', '++', '2022-02-14 16:14:42');
INSERT INTO `wgm_testdata` VALUES ('1085', 'project001', '2', '1', '', '671', '166.239', '6.345', '+++', '2022-02-14 16:14:42');
INSERT INTO `wgm_testdata` VALUES ('1086', 'project001', '2', '1', '', '749', '38.8127', '1.4814', '+', '2022-02-14 16:14:42');
INSERT INTO `wgm_testdata` VALUES ('1087', 'project001', '2', '1', '', '821', '7.05875', '0.269419', '-', '2022-02-14 16:14:42');
INSERT INTO `wgm_testdata` VALUES ('1088', 'project001', '2', '1', '', '897', '68.0136', '2.59594', '++', '2022-02-14 16:14:42');
INSERT INTO `wgm_testdata` VALUES ('1089', 'project001', '2', '1', '', '979', '38.6695', '1.47594', '+', '2022-02-14 16:14:42');
INSERT INTO `wgm_testdata` VALUES ('1090', 'project001', '2', '1', '', '1061', '30.2034', '1.15281', 'O', '2022-02-14 16:14:42');
INSERT INTO `wgm_testdata` VALUES ('1091', 'project001', '2', '1', '', '1136', '6.76169', '0.25808', '-', '2022-02-14 16:14:42');
INSERT INTO `wgm_testdata` VALUES ('1092', 'project001', '2', '1', '', '1222', '204.657', '7.81134', '+++', '2022-02-14 16:14:42');
INSERT INTO `wgm_testdata` VALUES ('1093', 'project001', '1', '1', 'FC', '172', '140.891', '2.28882', '+', '2022-02-23 16:05:22');
INSERT INTO `wgm_testdata` VALUES ('1094', 'project001', '1', '1', 'Cut', '247', '61.5562', '1', 'O', '2022-02-23 16:05:22');
INSERT INTO `wgm_testdata` VALUES ('1095', 'project001', '1', '1', '', '321', '4.74116', '0.0770217', '-', '2022-02-23 16:05:22');
INSERT INTO `wgm_testdata` VALUES ('1096', 'project001', '1', '1', '', '373', '0.0921717', '0.00149736', '-', '2022-02-23 16:05:22');
INSERT INTO `wgm_testdata` VALUES ('1097', 'project001', '1', '1', '', '446', '-0.390783', '-0.00634839', '-', '2022-02-23 16:05:22');
INSERT INTO `wgm_testdata` VALUES ('1098', 'project001', '1', '1', '', '533', '0.825126', '0.0134044', '-', '2022-02-23 16:05:22');
INSERT INTO `wgm_testdata` VALUES ('1099', 'project001', '1', '1', '', '619', '116.269', '1.88883', '+', '2022-02-23 16:05:22');
INSERT INTO `wgm_testdata` VALUES ('1100', 'project001', '1', '1', '', '696', '170.489', '2.76964', '++', '2022-02-23 16:05:22');
INSERT INTO `wgm_testdata` VALUES ('1101', 'project001', '1', '1', '', '767', '137.632', '2.23588', '+', '2022-02-23 16:05:22');
INSERT INTO `wgm_testdata` VALUES ('1102', 'project001', '1', '1', '', '840', '98.4476', '1.59931', '+', '2022-02-23 16:05:22');
INSERT INTO `wgm_testdata` VALUES ('1103', 'project001', '1', '1', '', '917', '0.777146', '0.012625', '-', '2022-02-23 16:05:22');
INSERT INTO `wgm_testdata` VALUES ('1104', 'project001', '1', '1', '', '1007', '-0.903409', '-0.0146762', '-', '2022-02-23 16:05:22');
INSERT INTO `wgm_testdata` VALUES ('1105', 'project001', '1', '1', '', '1075', '2.81439', '0.0457207', '-', '2022-02-23 16:05:22');
INSERT INTO `wgm_testdata` VALUES ('1106', 'project001', '1', '1', '', '1152', '0.072601', '0.00117943', '-', '2022-02-23 16:05:22');
INSERT INTO `wgm_testdata` VALUES ('1107', '1', '1', '2', 'FC', '172', '52.6921', '3.22045', '++', '2022-02-24 17:10:24');
INSERT INTO `wgm_testdata` VALUES ('1108', '1', '1', '2', 'Cut', '247', '16.3617', '1', 'O', '2022-02-24 17:10:24');
INSERT INTO `wgm_testdata` VALUES ('1109', '1', '1', '2', 'Nucleosomes', '316', '26.5887', '1.62505', '+', '2022-02-24 17:10:24');
INSERT INTO `wgm_testdata` VALUES ('1110', '1', '1', '2', '', '390', '31.9066', '1.95008', '+', '2022-02-24 17:10:24');
INSERT INTO `wgm_testdata` VALUES ('1111', '1', '1', '2', '', '465', '28.3056', '1.72999', '+', '2022-02-24 17:10:24');
INSERT INTO `wgm_testdata` VALUES ('1112', '1', '1', '2', 'SmD1', '537', '37.1631', '2.27135', '+', '2022-02-24 17:10:24');
INSERT INTO `wgm_testdata` VALUES ('1113', '1', '1', '2', 'U1-snRNP', '614', '19.6365', '1.20015', '+', '2022-02-24 17:10:24');
INSERT INTO `wgm_testdata` VALUES ('1114', '1', '1', '2', 'SSA/Ro 60', '689', '69.419', '4.24278', '+++', '2022-02-24 17:10:24');
INSERT INTO `wgm_testdata` VALUES ('1115', '1', '1', '2', 'SSA/Ro 52', '760', '44.4669', '2.71774', '++', '2022-02-24 17:10:24');
INSERT INTO `wgm_testdata` VALUES ('1116', '1', '1', '2', 'SSB/La', '835', '67.2021', '4.10728', '+++', '2022-02-24 17:10:24');
INSERT INTO `wgm_testdata` VALUES ('1117', '1', '1', '2', 'Scl 70', '884', '-1.06501', '-0.0650917', '-', '2022-02-24 17:10:24');
INSERT INTO `wgm_testdata` VALUES ('1118', '1', '1', '2', '', '987', '23.9314', '1.46265', '+', '2022-02-24 17:10:24');
INSERT INTO `wgm_testdata` VALUES ('1119', '1', '1', '2', 'Jo-1', '1058', '18.7216', '1.14423', 'O', '2022-02-24 17:10:24');
INSERT INTO `wgm_testdata` VALUES ('1120', '1', '1', '2', 'RPP/P0', '1129', '15.7423', '0.962144', 'O', '2022-02-24 17:10:24');
INSERT INTO `wgm_testdata` VALUES ('1121', '1', '1', '2', 'FC', '172', '52.6921', '3.22045', '++', '2022-02-24 17:34:36');
INSERT INTO `wgm_testdata` VALUES ('1122', '1', '1', '2', 'Cut', '247', '16.3617', '1', 'O', '2022-02-24 17:34:36');
INSERT INTO `wgm_testdata` VALUES ('1123', '1', '1', '2', 'Nucleosomes', '316', '26.5887', '1.62505', '+', '2022-02-24 17:34:36');
INSERT INTO `wgm_testdata` VALUES ('1124', '1', '1', '2', '', '390', '31.9066', '1.95008', '+', '2022-02-24 17:34:36');
INSERT INTO `wgm_testdata` VALUES ('1125', '1', '1', '2', '', '465', '28.3056', '1.72999', '+', '2022-02-24 17:34:36');
INSERT INTO `wgm_testdata` VALUES ('1126', '1', '1', '2', 'SmD1', '537', '37.1631', '2.27135', '+', '2022-02-24 17:34:36');
INSERT INTO `wgm_testdata` VALUES ('1127', '1', '1', '2', 'U1-snRNP', '614', '19.6365', '1.20015', '+', '2022-02-24 17:34:36');
INSERT INTO `wgm_testdata` VALUES ('1128', '1', '1', '2', 'SSA/Ro 60', '689', '69.419', '4.24278', '+++', '2022-02-24 17:34:36');
INSERT INTO `wgm_testdata` VALUES ('1129', '1', '1', '2', 'SSA/Ro 52', '760', '44.4669', '2.71774', '++', '2022-02-24 17:34:36');
INSERT INTO `wgm_testdata` VALUES ('1130', '1', '1', '2', 'SSB/La', '835', '67.2021', '4.10728', '+++', '2022-02-24 17:34:36');
INSERT INTO `wgm_testdata` VALUES ('1131', '1', '1', '2', 'Scl 70', '884', '-1.06501', '-0.0650917', '-', '2022-02-24 17:34:36');
INSERT INTO `wgm_testdata` VALUES ('1132', '1', '1', '2', '', '987', '23.9314', '1.46265', '+', '2022-02-24 17:34:36');
INSERT INTO `wgm_testdata` VALUES ('1133', '1', '1', '2', 'Jo-1', '1058', '18.7216', '1.14423', 'O', '2022-02-24 17:34:36');
INSERT INTO `wgm_testdata` VALUES ('1134', '1', '1', '2', 'RPP/P0', '1129', '15.7423', '0.962144', 'O', '2022-02-24 17:34:36');

-- ----------------------------
-- Table structure for wgm_testpaper
-- ----------------------------
DROP TABLE IF EXISTS `wgm_testpaper`;
CREATE TABLE `wgm_testpaper` (
  `ID` int(10) unsigned NOT NULL AUTO_INCREMENT,
  `Name` varchar(45) NOT NULL COMMENT '模条名称',
  `Company_ID` int(10) unsigned NOT NULL COMMENT '模条属于哪个公司',
  `TotalNumber` int(10) unsigned NOT NULL COMMENT '总个数：测试项目个数 + 空白项目区域个数',
  `Null_Number` int(10) unsigned NOT NULL COMMENT '模条上面空白项目区域个数',
  `Item_Number` int(10) unsigned NOT NULL COMMENT '测试项目个数',
  `TestPaparLenght` double NOT NULL COMMENT '模条总长度（精确到0.1毫米）',
  `FuncPosition` double NOT NULL COMMENT '功能条左侧位置（精确到0.1毫米），即左边缘',
  `TestAeaLenght` double NOT NULL COMMENT '测试区域长度 从功能条右侧到最后一个测试项目右侧（精确到0.1毫米）',
  PRIMARY KEY (`ID`) USING BTREE,
  UNIQUE KEY `Name_UNIQUE` (`Name`) USING BTREE
) ENGINE=InnoDB AUTO_INCREMENT=4 DEFAULT CHARSET=utf8 ROW_FORMAT=DYNAMIC;

-- ----------------------------
-- Records of wgm_testpaper
-- ----------------------------
INSERT INTO `wgm_testpaper` VALUES ('1', 'ANA1211', '1', '12', '0', '12', '75', '10', '52');
INSERT INTO `wgm_testpaper` VALUES ('2', 'ANA 9N11', '1', '12', '3', '9', '75', '10', '52');
INSERT INTO `wgm_testpaper` VALUES ('3', 'ANA 9D332', '1', '11', '2', '9', '75', '10', '48');

-- ----------------------------
-- Table structure for wgm_testpapercompany
-- ----------------------------
DROP TABLE IF EXISTS `wgm_testpapercompany`;
CREATE TABLE `wgm_testpapercompany` (
  `ID` int(10) unsigned NOT NULL AUTO_INCREMENT,
  `Name` varchar(45) NOT NULL,
  PRIMARY KEY (`ID`) USING BTREE,
  UNIQUE KEY `Name_UNIQUE` (`Name`) USING BTREE
) ENGINE=InnoDB AUTO_INCREMENT=2 DEFAULT CHARSET=utf8 ROW_FORMAT=DYNAMIC;

-- ----------------------------
-- Records of wgm_testpapercompany
-- ----------------------------
INSERT INTO `wgm_testpapercompany` VALUES ('1', 'human');

-- ----------------------------
-- Table structure for wgm_testpaperitem
-- ----------------------------
DROP TABLE IF EXISTS `wgm_testpaperitem`;
CREATE TABLE `wgm_testpaperitem` (
  `ID` varchar(5) NOT NULL,
  `TestPaper_ID` int(10) unsigned NOT NULL,
  `Name` varchar(45) DEFAULT NULL,
  `PositionNo` int(10) unsigned NOT NULL,
  `IsNull` int(10) unsigned NOT NULL DEFAULT '0',
  PRIMARY KEY (`ID`) USING BTREE
) ENGINE=InnoDB DEFAULT CHARSET=utf8 ROW_FORMAT=DYNAMIC;

-- ----------------------------
-- Records of wgm_testpaperitem
-- ----------------------------
INSERT INTO `wgm_testpaperitem` VALUES ('00101', '1', 'Nucleosomes', '1', '0');
INSERT INTO `wgm_testpaperitem` VALUES ('00102', '1', 'dsDNA', '2', '0');
INSERT INTO `wgm_testpaperitem` VALUES ('00103', '1', 'Histones', '3', '0');
INSERT INTO `wgm_testpaperitem` VALUES ('00104', '1', 'SmD1', '4', '0');
INSERT INTO `wgm_testpaperitem` VALUES ('00105', '1', 'U1-snRNP', '5', '0');
INSERT INTO `wgm_testpaperitem` VALUES ('00106', '1', 'SSA/Ro 60', '6', '0');
INSERT INTO `wgm_testpaperitem` VALUES ('00107', '1', 'SSA/Ro 52', '7', '0');
INSERT INTO `wgm_testpaperitem` VALUES ('00108', '1', 'SSB/La', '8', '0');
INSERT INTO `wgm_testpaperitem` VALUES ('00109', '1', 'Scl 70', '9', '0');
INSERT INTO `wgm_testpaperitem` VALUES ('00110', '1', 'CENP-B', '10', '0');
INSERT INTO `wgm_testpaperitem` VALUES ('00111', '1', 'Jo-1', '11', '0');
INSERT INTO `wgm_testpaperitem` VALUES ('00112', '1', 'RPP/P0', '12', '0');
INSERT INTO `wgm_testpaperitem` VALUES ('00201', '2', 'Nucleosomes', '1', '0');
INSERT INTO `wgm_testpaperitem` VALUES ('00202', '2', '', '2', '1');
INSERT INTO `wgm_testpaperitem` VALUES ('00203', '2', '', '3', '1');
INSERT INTO `wgm_testpaperitem` VALUES ('00204', '2', 'SmD1', '4', '0');
INSERT INTO `wgm_testpaperitem` VALUES ('00205', '2', 'U1-snRNP', '5', '0');
INSERT INTO `wgm_testpaperitem` VALUES ('00206', '2', 'SSA/Ro 60', '6', '0');
INSERT INTO `wgm_testpaperitem` VALUES ('00207', '2', 'SSA/Ro 52', '7', '0');
INSERT INTO `wgm_testpaperitem` VALUES ('00208', '2', 'SSB/La', '8', '0');
INSERT INTO `wgm_testpaperitem` VALUES ('00209', '2', 'Scl 70', '9', '0');
INSERT INTO `wgm_testpaperitem` VALUES ('00210', '2', '', '10', '1');
INSERT INTO `wgm_testpaperitem` VALUES ('00211', '2', 'Jo-1', '11', '0');
INSERT INTO `wgm_testpaperitem` VALUES ('00212', '2', 'RPP/P0', '12', '0');
INSERT INTO `wgm_testpaperitem` VALUES ('00301', '3', '', '1', '1');
INSERT INTO `wgm_testpaperitem` VALUES ('00302', '3', 'dsDNA', '2', '0');
INSERT INTO `wgm_testpaperitem` VALUES ('00303', '3', '', '3', '1');
INSERT INTO `wgm_testpaperitem` VALUES ('00304', '3', 'SmD1', '4', '0');
INSERT INTO `wgm_testpaperitem` VALUES ('00305', '3', 'U1-snRNP', '5', '0');
INSERT INTO `wgm_testpaperitem` VALUES ('00306', '3', 'SSA/Ro 60', '6', '0');
INSERT INTO `wgm_testpaperitem` VALUES ('00307', '3', 'SSA/Ro 52', '7', '0');
INSERT INTO `wgm_testpaperitem` VALUES ('00308', '3', 'SSB/La', '8', '0');
INSERT INTO `wgm_testpaperitem` VALUES ('00309', '3', 'Scl 70', '9', '0');
INSERT INTO `wgm_testpaperitem` VALUES ('00310', '3', 'CENP-B', '10', '0');
INSERT INTO `wgm_testpaperitem` VALUES ('00311', '3', 'Jo-1', '11', '0');
INSERT INTO `wgm_testpaperitem` VALUES ('00501', '5', 'aa', '1', '0');
INSERT INTO `wgm_testpaperitem` VALUES ('00502', '5', 'bb', '2', '0');
INSERT INTO `wgm_testpaperitem` VALUES ('00503', '5', 'NULL', '3', '1');
INSERT INTO `wgm_testpaperitem` VALUES ('00504', '5', 'cc', '4', '0');

-- ----------------------------
-- Table structure for wgm_tube
-- ----------------------------
DROP TABLE IF EXISTS `wgm_tube`;
CREATE TABLE `wgm_tube` (
  `ID` int(10) unsigned NOT NULL AUTO_INCREMENT,
  `Name` varchar(45) NOT NULL,
  `IsControl` tinyint(1) unsigned NOT NULL,
  `Inner` int(10) unsigned DEFAULT NULL,
  `CupHeight` int(10) unsigned DEFAULT NULL,
  `LiquidStartPos` int(10) unsigned DEFAULT NULL,
  PRIMARY KEY (`ID`) USING BTREE
) ENGINE=InnoDB DEFAULT CHARSET=utf8 ROW_FORMAT=DYNAMIC;

-- ----------------------------
-- Records of wgm_tube
-- ----------------------------
