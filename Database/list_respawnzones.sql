/*
MySQL Data Transfer
Source Host: localhost
Source Database: osrose
Target Host: localhost
Target Database: osrose
Date: 7/18/2008 11:53:56 AM
*/

SET FOREIGN_KEY_CHECKS=0;
-- ----------------------------
-- Table structure for list_respawnzones
-- ----------------------------
CREATE TABLE `list_respawnzones` (
  `id` int(11) NOT NULL auto_increment,
  `map` int(11) NOT NULL,
  `x` float NOT NULL,
  `y` float NOT NULL,
  `radius` float NOT NULL default '10',
  `type` int(11) NOT NULL default '2',
  PRIMARY KEY  (`id`)
) ENGINE=MyISAM AUTO_INCREMENT=286 DEFAULT CHARSET=latin1;

-- ----------------------------
-- Records 
-- ----------------------------
INSERT INTO `list_respawnzones` VALUES ('1', '1', '5241', '5190', '10', '0');
INSERT INTO `list_respawnzones` VALUES ('2', '1', '5210', '5137', '10', '1');
INSERT INTO `list_respawnzones` VALUES ('3', '2', '5655', '5238', '10', '1');
INSERT INTO `list_respawnzones` VALUES ('4', '2', '5655', '5216', '10', '0');
INSERT INTO `list_respawnzones` VALUES ('5', '2', '5334', '5178', '10', '0');
INSERT INTO `list_respawnzones` VALUES ('6', '2', '5518', '5449', '10', '0');
INSERT INTO `list_respawnzones` VALUES ('7', '3', '5178', '5009', '10', '1');
INSERT INTO `list_respawnzones` VALUES ('8', '3', '5184', '5000', '10', '0');
INSERT INTO `list_respawnzones` VALUES ('9', '4', '5085', '5022', '10', '1');
INSERT INTO `list_respawnzones` VALUES ('10', '4', '5096', '5021', '10', '0');
INSERT INTO `list_respawnzones` VALUES ('11', '5', '5155', '5105', '10', '1');
INSERT INTO `list_respawnzones` VALUES ('12', '5', '5202', '5498', '10', '0');
INSERT INTO `list_respawnzones` VALUES ('13', '5', '5201', '5060', '10', '0');
INSERT INTO `list_respawnzones` VALUES ('14', '6', '5155', '5105', '10', '1');
INSERT INTO `list_respawnzones` VALUES ('15', '6', '5202', '5498', '10', '0');
INSERT INTO `list_respawnzones` VALUES ('16', '6', '5201', '5060', '10', '0');
INSERT INTO `list_respawnzones` VALUES ('17', '8', '5526', '4547', '10', '1');
INSERT INTO `list_respawnzones` VALUES ('18', '8', '5520', '4558', '10', '0');
INSERT INTO `list_respawnzones` VALUES ('19', '9', '5211', '4868', '10', '1');
INSERT INTO `list_respawnzones` VALUES ('20', '9', '5200', '4785', '10', '0');
INSERT INTO `list_respawnzones` VALUES ('21', '11', '5512', '5027', '10', '1');
INSERT INTO `list_respawnzones` VALUES ('22', '11', '5016', '5360', '10', '0');
INSERT INTO `list_respawnzones` VALUES ('23', '11', '5380', '5427', '10', '0');
INSERT INTO `list_respawnzones` VALUES ('24', '11', '5429', '4982', '10', '0');
INSERT INTO `list_respawnzones` VALUES ('25', '11', '5001', '5045', '10', '0');
INSERT INTO `list_respawnzones` VALUES ('26', '12', '5512', '5027', '10', '1');
INSERT INTO `list_respawnzones` VALUES ('27', '12', '5016', '5360', '10', '0');
INSERT INTO `list_respawnzones` VALUES ('28', '12', '5380', '5427', '10', '0');
INSERT INTO `list_respawnzones` VALUES ('29', '12', '5429', '4982', '10', '0');
INSERT INTO `list_respawnzones` VALUES ('30', '12', '5001', '5045', '10', '0');
INSERT INTO `list_respawnzones` VALUES ('31', '13', '5512', '5027', '10', '1');
INSERT INTO `list_respawnzones` VALUES ('32', '13', '5016', '5360', '10', '0');
INSERT INTO `list_respawnzones` VALUES ('33', '13', '5380', '5427', '10', '0');
INSERT INTO `list_respawnzones` VALUES ('34', '13', '5429', '4982', '10', '0');
INSERT INTO `list_respawnzones` VALUES ('35', '13', '5001', '5045', '10', '0');
INSERT INTO `list_respawnzones` VALUES ('36', '15', '5190', '5140', '10', '1');
INSERT INTO `list_respawnzones` VALUES ('37', '15', '5210', '5140', '10', '0');
INSERT INTO `list_respawnzones` VALUES ('38', '15', '5367', '5140', '10', '0');
INSERT INTO `list_respawnzones` VALUES ('39', '15', '5530', '5139', '10', '0');
INSERT INTO `list_respawnzones` VALUES ('40', '15', '5208', '4982', '10', '0');
INSERT INTO `list_respawnzones` VALUES ('41', '15', '5368', '4982', '10', '0');
INSERT INTO `list_respawnzones` VALUES ('42', '15', '5529', '4984', '10', '0');
INSERT INTO `list_respawnzones` VALUES ('43', '15', '5208', '4822', '10', '0');
INSERT INTO `list_respawnzones` VALUES ('44', '15', '5368', '4822', '10', '0');
INSERT INTO `list_respawnzones` VALUES ('45', '15', '5527', '4820', '10', '0');
INSERT INTO `list_respawnzones` VALUES ('46', '19', '5196', '5183', '10', '1');
INSERT INTO `list_respawnzones` VALUES ('47', '19', '5212', '5184', '10', '0');
INSERT INTO `list_respawnzones` VALUES ('48', '21', '5340', '5284', '10', '0');
INSERT INTO `list_respawnzones` VALUES ('49', '21', '5102', '5064', '10', '1');
INSERT INTO `list_respawnzones` VALUES ('50', '21', '5104', '5073', '10', '0');
INSERT INTO `list_respawnzones` VALUES ('51', '21', '5296', '5059', '10', '0');
INSERT INTO `list_respawnzones` VALUES ('52', '21', '5398', '5511', '10', '0');
INSERT INTO `list_respawnzones` VALUES ('53', '21', '5140', '5492', '10', '0');
INSERT INTO `list_respawnzones` VALUES ('54', '22', '5025', '5523', '10', '1');
INSERT INTO `list_respawnzones` VALUES ('55', '22', '5098', '5322', '10', '0');
INSERT INTO `list_respawnzones` VALUES ('56', '23', '5036', '5086', '10', '0');
INSERT INTO `list_respawnzones` VALUES ('57', '23', '5096', '4906', '10', '1');
INSERT INTO `list_respawnzones` VALUES ('58', '23', '5348', '5062', '10', '0');
INSERT INTO `list_respawnzones` VALUES ('59', '23', '5327', '5400', '10', '0');
INSERT INTO `list_respawnzones` VALUES ('60', '23', '5139', '5524', '10', '0');
INSERT INTO `list_respawnzones` VALUES ('61', '24', '5528', '5247', '10', '1');
INSERT INTO `list_respawnzones` VALUES ('62', '24', '5525', '5376', '10', '0');
INSERT INTO `list_respawnzones` VALUES ('63', '24', '5028', '5100', '10', '0');
INSERT INTO `list_respawnzones` VALUES ('64', '24', '5526', '4945', '10', '0');
INSERT INTO `list_respawnzones` VALUES ('65', '25', '5379', '5185', '10', '1');
INSERT INTO `list_respawnzones` VALUES ('66', '25', '5515', '4899', '10', '0');
INSERT INTO `list_respawnzones` VALUES ('67', '25', '5490', '5360', '10', '0');
INSERT INTO `list_respawnzones` VALUES ('68', '25', '5266', '5556', '10', '0');
INSERT INTO `list_respawnzones` VALUES ('69', '25', '5179', '5087', '10', '0');
INSERT INTO `list_respawnzones` VALUES ('70', '26', '5284', '5162', '10', '0');
INSERT INTO `list_respawnzones` VALUES ('71', '26', '5063', '5494', '10', '1');
INSERT INTO `list_respawnzones` VALUES ('72', '26', '5252', '5555', '10', '0');
INSERT INTO `list_respawnzones` VALUES ('73', '26', '5444', '5293', '10', '0');
INSERT INTO `list_respawnzones` VALUES ('74', '26', '5685', '5104', '10', '0');
INSERT INTO `list_respawnzones` VALUES ('75', '26', '5291', '4893', '10', '0');
INSERT INTO `list_respawnzones` VALUES ('76', '26', '5053', '5034', '10', '0');
INSERT INTO `list_respawnzones` VALUES ('77', '27', '5179', '5411', '10', '1');
INSERT INTO `list_respawnzones` VALUES ('78', '27', '5221', '5329', '10', '0');
INSERT INTO `list_respawnzones` VALUES ('79', '27', '5624', '5187', '10', '0');
INSERT INTO `list_respawnzones` VALUES ('80', '27', '5582', '5460', '10', '0');
INSERT INTO `list_respawnzones` VALUES ('81', '28', '5197', '4906', '10', '0');
INSERT INTO `list_respawnzones` VALUES ('82', '28', '5528', '4812', '10', '0');
INSERT INTO `list_respawnzones` VALUES ('83', '28', '5148', '5225', '10', '0');
INSERT INTO `list_respawnzones` VALUES ('84', '28', '5541', '4816', '10', '1');
INSERT INTO `list_respawnzones` VALUES ('85', '28', '5570', '5175', '10', '0');
INSERT INTO `list_respawnzones` VALUES ('86', '29', '5092', '5150', '10', '1');
INSERT INTO `list_respawnzones` VALUES ('87', '29', '5091', '5142', '10', '0');
INSERT INTO `list_respawnzones` VALUES ('88', '31', '5520', '5455', '10', '1');
INSERT INTO `list_respawnzones` VALUES ('89', '31', '5430', '5510', '10', '0');
INSERT INTO `list_respawnzones` VALUES ('90', '32', '5517', '5410', '10', '1');
INSERT INTO `list_respawnzones` VALUES ('91', '32', '5254', '5417', '10', '0');
INSERT INTO `list_respawnzones` VALUES ('92', '33', '5607', '5465', '10', '1');
INSERT INTO `list_respawnzones` VALUES ('93', '33', '5695', '5270', '10', '0');
INSERT INTO `list_respawnzones` VALUES ('94', '37', '5099', '5233', '10', '1');
INSERT INTO `list_respawnzones` VALUES ('95', '37', '5110', '5233', '10', '0');
INSERT INTO `list_respawnzones` VALUES ('96', '38', '5073', '5346', '10', '1');
INSERT INTO `list_respawnzones` VALUES ('97', '38', '5061', '5338', '10', '0');
INSERT INTO `list_respawnzones` VALUES ('98', '40', '5181', '5210', '10', '1');
INSERT INTO `list_respawnzones` VALUES ('99', '40', '5190', '5211', '10', '0');
INSERT INTO `list_respawnzones` VALUES ('100', '41', '5068', '5179', '10', '1');
INSERT INTO `list_respawnzones` VALUES ('101', '41', '5062', '5178', '10', '0');
INSERT INTO `list_respawnzones` VALUES ('102', '42', '5196', '5207', '10', '1');
INSERT INTO `list_respawnzones` VALUES ('103', '42', '5204', '5208', '10', '0');
INSERT INTO `list_respawnzones` VALUES ('104', '51', '5357', '5013', '10', '0');
INSERT INTO `list_respawnzones` VALUES ('105', '51', '5358', '5011', '10', '1');
INSERT INTO `list_respawnzones` VALUES ('106', '52', '6146', '5209', '10', '1');
INSERT INTO `list_respawnzones` VALUES ('107', '52', '6151', '5203', '10', '0');
INSERT INTO `list_respawnzones` VALUES ('108', '53', '5062', '5190', '10', '1');
INSERT INTO `list_respawnzones` VALUES ('109', '53', '5048', '5202', '10', '0');
INSERT INTO `list_respawnzones` VALUES ('110', '54', '5061', '4432', '10', '1');
INSERT INTO `list_respawnzones` VALUES ('111', '54', '5053', '4423', '10', '0');
INSERT INTO `list_respawnzones` VALUES ('112', '55', '5529', '4468', '10', '1');
INSERT INTO `list_respawnzones` VALUES ('113', '55', '5523', '4458', '10', '0');
INSERT INTO `list_respawnzones` VALUES ('114', '56', '5035', '4269', '10', '0');
INSERT INTO `list_respawnzones` VALUES ('115', '56', '5035', '4265', '10', '1');
INSERT INTO `list_respawnzones` VALUES ('116', '57', '5539', '5175', '10', '0');
INSERT INTO `list_respawnzones` VALUES ('117', '57', '5533', '5175', '10', '1');
INSERT INTO `list_respawnzones` VALUES ('118', '58', '5682', '4269', '10', '1');
INSERT INTO `list_respawnzones` VALUES ('119', '58', '5682', '4259', '10', '0');
INSERT INTO `list_respawnzones` VALUES ('120', '59', '5092', '5140', '10', '1');
INSERT INTO `list_respawnzones` VALUES ('121', '59', '5092', '5126', '10', '0');
INSERT INTO `list_respawnzones` VALUES ('122', '61', '5435', '4570', '10', '1');
INSERT INTO `list_respawnzones` VALUES ('123', '61', '5430', '4573', '10', '0');
INSERT INTO `list_respawnzones` VALUES ('124', '62', '5838', '5173', '10', '1');
INSERT INTO `list_respawnzones` VALUES ('125', '62', '5851', '5167', '10', '0');
INSERT INTO `list_respawnzones` VALUES ('126', '63', '6079', '5197', '10', '1');
INSERT INTO `list_respawnzones` VALUES ('127', '63', '6090', '5193', '10', '0');
INSERT INTO `list_respawnzones` VALUES ('128', '64', '5039', '5312', '10', '1');
INSERT INTO `list_respawnzones` VALUES ('129', '64', '5049', '5317', '10', '0');
INSERT INTO `list_respawnzones` VALUES ('130', '65', '5510', '5390', '10', '1');
INSERT INTO `list_respawnzones` VALUES ('131', '70', '5171', '5212', '10', '0');
INSERT INTO `list_respawnzones` VALUES ('132', '70', '5157', '4892', '10', '0');
INSERT INTO `list_respawnzones` VALUES ('133', '70', '5560', '4917', '10', '0');
INSERT INTO `list_respawnzones` VALUES ('134', '70', '5544', '5202', '10', '0');
INSERT INTO `list_respawnzones` VALUES ('135', '70', '5362', '5258', '10', '1');
INSERT INTO `list_respawnzones` VALUES ('136', '74', '5092', '5086', '10', '1');
INSERT INTO `list_respawnzones` VALUES ('137', '74', '5101', '5085', '10', '0');
INSERT INTO `list_respawnzones` VALUES ('138', '101', '5092', '5086', '10', '1');
INSERT INTO `list_respawnzones` VALUES ('139', '101', '5101', '5085', '10', '0');
INSERT INTO `list_respawnzones` VALUES ('140', '102', '5092', '5086', '10', '1');
INSERT INTO `list_respawnzones` VALUES ('141', '102', '5101', '5085', '10', '0');
INSERT INTO `list_respawnzones` VALUES ('142', '103', '5092', '5086', '10', '1');
INSERT INTO `list_respawnzones` VALUES ('143', '103', '5101', '5085', '10', '0');
INSERT INTO `list_respawnzones` VALUES ('144', '104', '5092', '5086', '10', '1');
INSERT INTO `list_respawnzones` VALUES ('145', '104', '5101', '5085', '10', '0');
INSERT INTO `list_respawnzones` VALUES ('146', '105', '5092', '5086', '10', '1');
INSERT INTO `list_respawnzones` VALUES ('147', '105', '5101', '5085', '10', '0');
INSERT INTO `list_respawnzones` VALUES ('148', '106', '5092', '5086', '10', '1');
INSERT INTO `list_respawnzones` VALUES ('149', '106', '5101', '5085', '10', '0');
INSERT INTO `list_respawnzones` VALUES ('150', '107', '5092', '5086', '10', '1');
INSERT INTO `list_respawnzones` VALUES ('151', '107', '5101', '5085', '10', '0');
INSERT INTO `list_respawnzones` VALUES ('152', '108', '5092', '5086', '10', '1');
INSERT INTO `list_respawnzones` VALUES ('153', '108', '5101', '5085', '10', '0');
INSERT INTO `list_respawnzones` VALUES ('154', '109', '5092', '5086', '10', '1');
INSERT INTO `list_respawnzones` VALUES ('155', '109', '5101', '5085', '10', '0');
INSERT INTO `list_respawnzones` VALUES ('156', '110', '5092', '5086', '10', '1');
INSERT INTO `list_respawnzones` VALUES ('157', '110', '5101', '5085', '10', '0');
INSERT INTO `list_respawnzones` VALUES ('158', '111', '5092', '5086', '10', '1');
INSERT INTO `list_respawnzones` VALUES ('159', '111', '5101', '5085', '10', '0');
INSERT INTO `list_respawnzones` VALUES ('160', '112', '5092', '5086', '10', '1');
INSERT INTO `list_respawnzones` VALUES ('161', '112', '5101', '5085', '10', '0');
INSERT INTO `list_respawnzones` VALUES ('162', '113', '5092', '5086', '10', '1');
INSERT INTO `list_respawnzones` VALUES ('163', '113', '5101', '5085', '10', '0');
INSERT INTO `list_respawnzones` VALUES ('164', '114', '5092', '5086', '10', '1');
INSERT INTO `list_respawnzones` VALUES ('165', '114', '5101', '5085', '10', '0');
INSERT INTO `list_respawnzones` VALUES ('166', '115', '5092', '5086', '10', '1');
INSERT INTO `list_respawnzones` VALUES ('167', '115', '5101', '5085', '10', '0');
INSERT INTO `list_respawnzones` VALUES ('168', '116', '5092', '5086', '10', '1');
INSERT INTO `list_respawnzones` VALUES ('169', '116', '5101', '5085', '10', '0');
INSERT INTO `list_respawnzones` VALUES ('170', '117', '5092', '5086', '10', '1');
INSERT INTO `list_respawnzones` VALUES ('171', '117', '5101', '5085', '10', '0');
INSERT INTO `list_respawnzones` VALUES ('172', '118', '5092', '5086', '10', '1');
INSERT INTO `list_respawnzones` VALUES ('173', '118', '5101', '5085', '10', '0');
INSERT INTO `list_respawnzones` VALUES ('174', '119', '5092', '5086', '10', '1');
INSERT INTO `list_respawnzones` VALUES ('175', '119', '5101', '5085', '10', '0');
INSERT INTO `list_respawnzones` VALUES ('176', '120', '5092', '5086', '10', '1');
INSERT INTO `list_respawnzones` VALUES ('177', '120', '5101', '5085', '10', '0');
INSERT INTO `list_respawnzones` VALUES ('285', '50', '5198', '5236', '10', '1');
