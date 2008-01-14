/*
MySQL Data Transfer
Source Host: 192.168.1.100
Source Database: osrose
Target Host: 192.168.1.100
Target Database: osrose
Date: 1/13/2008 8:28:14 PM
*/

SET FOREIGN_KEY_CHECKS=0;
-- ----------------------------
-- Table structure for list_customgates
-- ----------------------------
CREATE TABLE `list_customgates` (
  `id` int(11) NOT NULL auto_increment,
  `name` varchar(255) collate latin1_general_ci NOT NULL,
  `sourcemap` int(11) NOT NULL,
  `sourcex` float NOT NULL,
  `sourcey` float NOT NULL,
  `destmap` int(11) NOT NULL,
  `destx` float NOT NULL,
  `desty` float NOT NULL,
  `radius` int(11) NOT NULL default '2',
  `active` int(11) NOT NULL default '0',
  PRIMARY KEY  (`id`)
) ENGINE=MyISAM AUTO_INCREMENT=5 DEFAULT CHARSET=latin1 COLLATE=latin1_general_ci;

-- ----------------------------
-- Records 
-- ----------------------------
INSERT INTO `list_customgates` VALUES ('1', 'Goblin cave B1 TP zone to Sunshine Coast', '31', '5027', '5509', '37', '5117', '5303', '3', '0');
INSERT INTO `list_customgates` VALUES ('3', 'Zant to Fall Ball in Gorge of Silence', '1', '5196', '5091', '28', '5570', '4798', '2', '0');
INSERT INTO `list_customgates` VALUES ('2', 'AP Waterfall to Sunshine Coast', '22', '5022', '5182', '37', '5117', '5303', '2', '0');
INSERT INTO `list_customgates` VALUES ('4', 'Zant to Sants planetoid', '1', '5329', '5162', '38', '5072', '5345', '3', '1');
