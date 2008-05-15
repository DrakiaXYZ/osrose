/*
MySQL Data Transfer
Source Host: localhost
Source Database: osrose
Target Host: localhost
Target Database: osrose
Date: 5/12/2008 10:07:10 AM
*/

SET FOREIGN_KEY_CHECKS=0;
-- ----------------------------
-- Table structure for list_npcs
-- ----------------------------
CREATE TABLE `list_npcs` (
  `id` int(11) NOT NULL auto_increment,
  `name` varchar(255) NOT NULL,
  `type` int(11) NOT NULL,
  `map` int(11) NOT NULL,
  `dir` float NOT NULL,
  `x` float NOT NULL,
  `y` float NOT NULL,
  PRIMARY KEY  (`id`)
) ENGINE=MyISAM AUTO_INCREMENT=179 DEFAULT CHARSET=latin1;

-- ----------------------------
-- Records 
-- ----------------------------
INSERT INTO `list_npcs` VALUES ('1', '[Village Chief] Cornell', '1001', '1', '183.008', '5217.51', '5113.18');
INSERT INTO `list_npcs` VALUES ('2', '[Akram Kingdom Minister] Warren', '1002', '1', '178.499', '5208.78', '5112.94');
INSERT INTO `list_npcs` VALUES ('3', '[Co-Founder of the Junon Order] Francis', '1003', '1', '157.957', '5080.3', '5066.28');
INSERT INTO `list_npcs` VALUES ('4', '[Ferrell Guild Staff] Crow', '1004', '1', '6.06652', '5094.38', '5259.9');
INSERT INTO `list_npcs` VALUES ('5', '[Righteous Crusader] Leonard', '1005', '1', '16.1021', '5261.08', '5166.96');
INSERT INTO `list_npcs` VALUES ('6', '[Arumic Merchant] Tryteh', '1006', '1', '258.129', '5313.26', '5153.73');
INSERT INTO `list_npcs` VALUES ('7', '[Gypsy Jewel Seller] Mina', '1007', '1', '197.989', '5292.56', '5127.66');
INSERT INTO `list_npcs` VALUES ('8', '[Weapon Seller] Raffle', '1008', '1', '322.406', '5302.32', '5232.34');
INSERT INTO `list_npcs` VALUES ('9', '[Armor Seller] Carrion', '1009', '1', '275.984', '5313.53', '5198.14');
INSERT INTO `list_npcs` VALUES ('10', '[Designer] Keenu', '1010', '1', '343.898', '5273.5', '5256.83');
INSERT INTO `list_npcs` VALUES ('11', '[Eccentric Inventor] Spero', '1011', '1', '14.2928', '5212.36', '5254.66');
INSERT INTO `list_npcs` VALUES ('12', '[Ferrell Guild Staff] Ulysses', '1012', '1', '84.0163', '5071.26', '5206.92');
INSERT INTO `list_npcs` VALUES ('13', '[Tavern Owner] Sharlin', '1013', '1', '333.435', '5131.56', '5218.14');
INSERT INTO `list_npcs` VALUES ('14', '[Guide] Lena', '1014', '1', '169.135', '5240.4', '5124.57');
INSERT INTO `list_npcs` VALUES ('15', '[Resident] Luth', '1015', '1', '270', '5130.61', '5154.58');
INSERT INTO `list_npcs` VALUES ('16', '[Livestock Farmer] Lampa', '1016', '1', '173.934', '5109.42', '5363.68');
INSERT INTO `list_npcs` VALUES ('17', '[Cornell\'s Grandson] Cheney', '1018', '1', '22.0426', '5436.3', '5492.26');
INSERT INTO `list_npcs` VALUES ('18', '[Lena\'s Sister] Shirley', '1019', '1', '322.406', '5504.69', '5274.08');
INSERT INTO `list_npcs` VALUES ('19', '[Keenu\'s Daughter] Arisa', '1020', '1', '275.984', '5428.17', '5082.68');
INSERT INTO `list_npcs` VALUES ('20', '[Event Info] Judy', '1201', '1', '162.011', '5261.88', '5212.97');
INSERT INTO `list_npcs` VALUES ('21', '[Mayor] Darren', '1081', '2', '178.499', '5514.48', '5238.2');
INSERT INTO `list_npcs` VALUES ('22', '[Guide] Eva', '1082', '2', '153.435', '5505.78', '5346.09');
INSERT INTO `list_npcs` VALUES ('23', '[Founder of Junon Order] Raw', '1088', '2', '181.501', '5319.27', '5095.36');
INSERT INTO `list_npcs` VALUES ('24', '[Manager of Ferrell] Arothel', '1089', '2', '270', '5713.43', '5360.16');
INSERT INTO `list_npcs` VALUES ('25', '[Righteous Crusader] Gawain', '1090', '2', '84.0163', '5334.58', '5353.91');
INSERT INTO `list_npcs` VALUES ('26', '[Arumic Merchant] Chester', '1091', '2', '211.693', '5723.96', '5087.24');
INSERT INTO `list_npcs` VALUES ('27', '[Gypsy Jewel Seller] Bellia', '1092', '2', '217.594', '5725.11', '5199.04');
INSERT INTO `list_npcs` VALUES ('28', '[Weapon Merchant] Crune', '1093', '2', '335.763', '5728.67', '5224.89');
INSERT INTO `list_npcs` VALUES ('29', '[Armor Merchant] Saki', '1094', '2', '258.129', '5721.8', '5290.79');
INSERT INTO `list_npcs` VALUES ('30', '[Designer] Lisa', '1095', '2', '220.893', '5729.06', '5136.33');
INSERT INTO `list_npcs` VALUES ('31', '[Ferrell Guild Merchant] Mildun', '1096', '2', '165.707', '5673.16', '5193.89');
INSERT INTO `list_npcs` VALUES ('32', '[Tavern Owner] Harin', '1097', '2', '89.9999', '5681.79', '5131.11');
INSERT INTO `list_npcs` VALUES ('33', '[Ferrell Guild Staff] Kiroth', '1098', '2', '275.984', '5603.58', '5058.1');
INSERT INTO `list_npcs` VALUES ('34', '[Ferrell Guild Staff] Hayen', '1099', '2', '258.129', '5603.77', '5046.12');
INSERT INTO `list_npcs` VALUES ('35', '[Ferrell Guild Staff] Itz', '1100', '2', '270', '5603.69', '5034.52');
INSERT INTO `list_npcs` VALUES ('36', '[Historian] Jones', '1104', '2', '162.011', '5578.19', '4890.44');
INSERT INTO `list_npcs` VALUES ('37', '[Livestock Farmer] Sicru', '1107', '2', '187.631', '5818.02', '5487.59');
INSERT INTO `list_npcs` VALUES ('38', '[Elder of Junon Order] Gorthein', '1109', '2', '181.501', '5325.54', '5095.31');
INSERT INTO `list_npcs` VALUES ('39', '[Ferrell Guild Staff] Charrs', '1110', '2', '270', '5713.38', '5368.71');
INSERT INTO `list_npcs` VALUES ('40', '[Righteous Crusader] Huffe', '1111', '2', '89.9999', '5334.84', '5345.81');
INSERT INTO `list_npcs` VALUES ('41', '[Arumic Researcher] Carasia', '1112', '2', '197.989', '5730.57', '5094.06');
INSERT INTO `list_npcs` VALUES ('42', '[Clan Owner] Burtland', '1115', '2', '89.9999', '5289.1', '5264.1');
INSERT INTO `list_npcs` VALUES ('43', '[Soldier] Odelo', '1116', '2', '0', '5507.31', '5397.4');
INSERT INTO `list_npcs` VALUES ('44', '[Soldier] Winters', '1117', '2', '0', '5522.99', '5397.75');
INSERT INTO `list_npcs` VALUES ('45', '[Guide] Alphonso', '1118', '2', '178.499', '5520.56', '5063.66');
INSERT INTO `list_npcs` VALUES ('46', '[Vicious Captain] Ruven', '1125', '2', '270', '5597.76', '4918.87');
INSERT INTO `list_npcs` VALUES ('47', '[Event Info] Felice Fete', '1202', '2', '206.565', '5562', '5164.83');
INSERT INTO `list_npcs` VALUES ('48', '[Clan War Manager] Regina', '1751', '2', '89.9999', '5290.17', '5244.25');
INSERT INTO `list_npcs` VALUES ('49', '[Clan Merchant] Aliche Patt', '1752', '2', '90.0001', '5288.35', '5260.53');
INSERT INTO `list_npcs` VALUES ('50', '[Ferrell Guild Staff] Rooen', '1513', '3', '0', '5104.48', '5019.71');
INSERT INTO `list_npcs` VALUES ('51', '[Akram Minister] Rodath', '1086', '5', '89.9999', '5155.07', '5279.92');
INSERT INTO `list_npcs` VALUES ('52', '[Akram Minister] Mel', '1087', '5', '270', '5247.07', '5279.96');
INSERT INTO `list_npcs` VALUES ('53', '[Akram Minister] Gamp', '1084', '6', '270', '5248.14', '5279.2');
INSERT INTO `list_npcs` VALUES ('54', '[Referee] Leum', '1113', '9', '0', '5199.99', '5390.04');
INSERT INTO `list_npcs` VALUES ('55', '[Referee] Pirre', '1114', '9', '180', '5201.59', '4765.69');
INSERT INTO `list_npcs` VALUES ('56', '[Akram Minister] Nell', '1085', '11', '84.0163', '4953.37', '4992.35');
INSERT INTO `list_npcs` VALUES ('57', '[Akram Minister] Nell', '1085', '11', '10.8648', '4978.48', '5478.6');
INSERT INTO `list_npcs` VALUES ('58', '[Akram Minister] Nell', '1085', '11', '337.957', '5455.57', '5478.99');
INSERT INTO `list_npcs` VALUES ('59', '[Akram Minister] Nell', '1085', '11', '335.763', '5521.94', '5020.66');
INSERT INTO `list_npcs` VALUES ('60', '[Akram Minister] Nell', '1085', '12', '84.0163', '4953.37', '4992.35');
INSERT INTO `list_npcs` VALUES ('61', '[Akram Minister] Nell', '1085', '12', '10.8648', '4978.48', '5478.6');
INSERT INTO `list_npcs` VALUES ('62', '[Akram Minister] Nell', '1085', '12', '337.957', '5455.57', '5478.99');
INSERT INTO `list_npcs` VALUES ('63', '[Akram Minister] Nell', '1085', '12', '335.763', '5521.94', '5020.66');
INSERT INTO `list_npcs` VALUES ('64', '[Akram Minister] Nell', '1085', '13', '84.0163', '4953.37', '4992.35');
INSERT INTO `list_npcs` VALUES ('65', '[Akram Minister] Nell', '1085', '13', '10.8648', '4978.48', '5478.6');
INSERT INTO `list_npcs` VALUES ('66', '[Akram Minister] Nell', '1085', '13', '337.957', '5455.57', '5478.99');
INSERT INTO `list_npcs` VALUES ('67', '[Akram Minister] Nell', '1085', '13', '335.763', '5521.94', '5020.66');
INSERT INTO `list_npcs` VALUES ('68', '[Clan House Manager] Kushard', '1161', '15', '0', '5200.16', '5209.81');
INSERT INTO `list_npcs` VALUES ('69', '[Clan House Manager] Kushard', '1161', '15', '0', '5200.13', '5051.79');
INSERT INTO `list_npcs` VALUES ('70', '[Clan House Manager] Kushard', '1161', '15', '0', '5200.16', '4890.67');
INSERT INTO `list_npcs` VALUES ('71', '[Clan House Manager] Kushard', '1161', '15', '0', '5360.21', '5210.15');
INSERT INTO `list_npcs` VALUES ('72', '[Clan House Manager] Kushard', '1161', '15', '0', '5360.2', '5051.41');
INSERT INTO `list_npcs` VALUES ('73', '[Clan House Manager] Kushard', '1161', '15', '0', '5360.25', '4890.3');
INSERT INTO `list_npcs` VALUES ('74', '[Clan House Manager] Kushard', '1161', '15', '0', '5520.19', '5211.31');
INSERT INTO `list_npcs` VALUES ('75', '[Clan House Manager] Kushard', '1161', '15', '0', '5520.18', '5051.41');
INSERT INTO `list_npcs` VALUES ('76', '[Clan House Manager] Kushard', '1161', '15', '0', '5520.16', '4891.07');
INSERT INTO `list_npcs` VALUES ('77', '[Clan House Soldier] Jason', '1162', '15', '183.008', '5205.79', '5129.92');
INSERT INTO `list_npcs` VALUES ('78', '[Clan House Soldier] Jason', '1162', '15', '181.501', '5204.57', '4970.37');
INSERT INTO `list_npcs` VALUES ('79', '[Clan House Soldier] Jason', '1162', '15', '181.501', '5203.89', '4809.55');
INSERT INTO `list_npcs` VALUES ('80', '[Clan House Soldier] Jason', '1162', '15', '180', '5363.94', '5130.38');
INSERT INTO `list_npcs` VALUES ('81', '[Clan House Soldier] Jason', '1162', '15', '180', '5364.04', '4970.33');
INSERT INTO `list_npcs` VALUES ('82', '[Clan House Soldier] Jason', '1162', '15', '183.008', '5363.85', '4810.42');
INSERT INTO `list_npcs` VALUES ('83', '[Clan House Soldier] Jason', '1162', '15', '183.008', '5524.3', '5129.46');
INSERT INTO `list_npcs` VALUES ('84', '[Clan House Soldier] Jason', '1162', '15', '183.008', '5523.83', '4970.15');
INSERT INTO `list_npcs` VALUES ('85', '[Clan House Soldier] Jason', '1162', '15', '181.501', '5523.67', '4810.61');
INSERT INTO `list_npcs` VALUES ('86', '[Arumic Resercher] Lutis', '1051', '21', '160.035', '5118.14', '5374.91');
INSERT INTO `list_npcs` VALUES ('87', '[Mountain Guide] Shannon', '1052', '21', '353.933', '5357.27', '5282.19');
INSERT INTO `list_npcs` VALUES ('88', '[Cleric] Karitte', '1053', '21', '95.9836', '5112.44', '5385.08');
INSERT INTO `list_npcs` VALUES ('89', '[Boy in the Hut]Huey', '1021', '22', '333.435', '5650.66', '5407.16');
INSERT INTO `list_npcs` VALUES ('90', '[Visitor Guide] Arua\'s Fairy', '1030', '22', '89.9999', '5060.19', '5522.94');
INSERT INTO `list_npcs` VALUES ('91', '[Visitor Guide] Ronway', '1031', '22', '246.969', '5147.55', '5356.75');
INSERT INTO `list_npcs` VALUES ('92', '[Akram Minister] Mairard', '1032', '22', '298.187', '5154.85', '5332.74');
INSERT INTO `list_npcs` VALUES ('93', '[Smith] Ronk', '1034', '22', '224.459', '5140.96', '5303.35');
INSERT INTO `list_npcs` VALUES ('94', '[Little Street Vendor] Pony', '1035', '22', '0', '5860.22', '5431.89');
INSERT INTO `list_npcs` VALUES ('95', '[Ferrell Guild Staff] Seyon', '1036', '22', '293.031', '5882.08', '5420.74');
INSERT INTO `list_npcs` VALUES ('96', '[Village Chief] Gray', '1038', '22', '157.957', '5083.86', '5284.24');
INSERT INTO `list_npcs` VALUES ('97', '[Fruit Store] Reene', '1039', '22', '26.5651', '5061.58', '5342.24');
INSERT INTO `list_npcs` VALUES ('98', '[Novice Designer] Cassirin', '1040', '22', '355.472', '5103.53', '5378.9');
INSERT INTO `list_npcs` VALUES ('99', '[Old Man] Myad', '1041', '22', '17.9888', '5078.07', '5372.4');
INSERT INTO `list_npcs` VALUES ('100', '[Ferrell Guild Storage Keeper] Fabrizio', '1042', '22', '192.55', '5113.43', '5260.64');
INSERT INTO `list_npcs` VALUES ('101', 'Melendino', '1473', '22', '142.406', '5107.44', '5013.71');
INSERT INTO `list_npcs` VALUES ('102', '[Ferrell Guild Staff] Peron', '1511', '22', '275.984', '5905.42', '5306.42');
INSERT INTO `list_npcs` VALUES ('103', '[Ferrell Guild Staff] Belz', '1061', '23', '270', '5358.63', '5058.99');
INSERT INTO `list_npcs` VALUES ('104', '[Smith] Punwell', '1062', '23', '24.2374', '5340.65', '5070.26');
INSERT INTO `list_npcs` VALUES ('105', '[Little Street Vendor] Mile', '1063', '23', '307.514', '5356.41', '5043.28');
INSERT INTO `list_npcs` VALUES ('106', '[Weapon Craftsman] Mairath', '1064', '23', '180', '5349.02', '5033.95');
INSERT INTO `list_npcs` VALUES ('107', '[Ferrell Guild Merchant] Lina', '1071', '24', '293.031', '5567.26', '4927.03');
INSERT INTO `list_npcs` VALUES ('108', '[Gypsy Merchant] Methio', '1072', '24', '192.55', '5563.13', '4895.45');
INSERT INTO `list_npcs` VALUES ('109', '[Ikaness Staff] Orias', '1073', '24', '95.9836', '5515.26', '4925.14');
INSERT INTO `list_npcs` VALUES ('110', '[Ikaness Staff] Shroon', '1121', '25', '9.22765', '5375.78', '5188.33');
INSERT INTO `list_npcs` VALUES ('111', '[Guide of Plain] Pein', '1122', '25', '307.514', '5503.22', '5350.93');
INSERT INTO `list_npcs` VALUES ('112', '[Gypsy Seller] Edone', '1123', '25', '187.631', '5448.14', '4976.38');
INSERT INTO `list_npcs` VALUES ('113', '[Mountain Guide] Kay', '1131', '26', '22.0426', '5669.16', '5105.24');
INSERT INTO `list_npcs` VALUES ('114', '[Righteous Crusader] Gallahad', '1141', '27', '178.499', '5345.2', '5047.71');
INSERT INTO `list_npcs` VALUES ('115', '[Akram Minister] Luce', '1142', '27', '101.871', '5320.52', '5081.27');
INSERT INTO `list_npcs` VALUES ('116', '[Ferrell Guild Merchant ] Bith', '1143', '27', '197.989', '5259.72', '5147.64');
INSERT INTO `list_npcs` VALUES ('117', '[Resident] Hotch', '1144', '27', '189.228', '5384.23', '5180.1');
INSERT INTO `list_npcs` VALUES ('118', '[Ferrell Guild Staff] Robin', '1512', '27', '264.016', '5239.23', '5040.74');
INSERT INTO `list_npcs` VALUES ('119', '[Ferrell Guild Merchant] Med', '1151', '28', '127.514', '5587.09', '4732.29');
INSERT INTO `list_npcs` VALUES ('120', '[Dead Priest] Lantore', '1154', '29', '241.813', '5114.61', '5131.16');
INSERT INTO `list_npcs` VALUES ('121', '[Ranger] Paul', '1155', '29', '330.956', '5157.1', '5176.39');
INSERT INTO `list_npcs` VALUES ('122', '[Town Girl] Lithia', '1156', '29', '24.2374', '5091.98', '5181.81');
INSERT INTO `list_npcs` VALUES ('123', '[Ghost] Harry', '1157', '29', '184.528', '5051.39', '5119.6');
INSERT INTO `list_npcs` VALUES ('124', '[Event Info] Judith', '1204', '37', '358.499', '5115.68', '5324.15');
INSERT INTO `list_npcs` VALUES ('125', '[Event Info] Santa Claus', '1205', '38', '3.01237', '5069.18', '5362.51');
INSERT INTO `list_npcs` VALUES ('126', '[Event Info] Loelsch', '1206', '38', '66.9407', '5057.19', '5351.61');
INSERT INTO `list_npcs` VALUES ('127', '[Event Info] Lucielle Fete', '1203', '40', '333.435', '5254.64', '5216.39');
INSERT INTO `list_npcs` VALUES ('128', '[Eucar Judge] Ishtal', '1171', '51', '206.565', '5430.09', '4937.96');
INSERT INTO `list_npcs` VALUES ('129', '[Akram Ambassador] Eliot', '1172', '51', '157.957', '5285.69', '4940.95');
INSERT INTO `list_npcs` VALUES ('130', '[Arumic Prophet] Olleck Basilasi', '1173', '51', '178.499', '5359.62', '5085.72');
INSERT INTO `list_npcs` VALUES ('131', '[Ferrell Guild Banker] Andre', '1180', '51', '0', '5414.86', '5114.41');
INSERT INTO `list_npcs` VALUES ('132', '[Smith] Pavrick', '1181', '51', '335.763', '5440.45', '5103.41');
INSERT INTO `list_npcs` VALUES ('133', '[Ferrell Trader] Sergei', '1184', '51', '258.129', '5450.88', '5077.06');
INSERT INTO `list_npcs` VALUES ('134', '[Magic Goods Seller] Pabel', '1185', '51', '3.00825', '5298.98', '5105.03');
INSERT INTO `list_npcs` VALUES ('135', '[Tavern Owner] Anzhelika', '1186', '51', '139.107', '5263.61', '5079.49');
INSERT INTO `list_npcs` VALUES ('137', '[Station Guide] Illiya', '1188', '51', '148.307', '5107.24', '4996.57');
INSERT INTO `list_npcs` VALUES ('138', '[Shamanist] Est', '1191', '54', '84.0163', '5088.26', '4257.84');
INSERT INTO `list_npcs` VALUES ('139', '[Righteous Crusader] Harold Evan', '1211', '61', '14.2928', '5369.75', '4575.29');
INSERT INTO `list_npcs` VALUES ('140', '[Arumic Researcher] Catherine Clara', '1212', '61', '330.956', '5473.37', '4618.79');
INSERT INTO `list_npcs` VALUES ('141', '[Ferrell Guild Staff] Gilbert', '1213', '61', '217.594', '5474.35', '4513.74');
INSERT INTO `list_npcs` VALUES ('142', '[Elder of Junon Order] Oscar Patrick', '1214', '61', '157.957', '5371.18', '4546.51');
INSERT INTO `list_npcs` VALUES ('143', '[Akram Ambassador] Jacklyn Cooper', '1215', '61', '180', '5430', '4483.79');
INSERT INTO `list_npcs` VALUES ('144', '[Station Guide] Chacha', '1219', '61', '12.5502', '5226.6', '4452.72');
INSERT INTO `list_npcs` VALUES ('145', '[Raknu Chief] Darka Khan', '1220', '61', '352.369', '5650.09', '4464.73');
INSERT INTO `list_npcs` VALUES ('146', '[Raknu Warrior] Jeffrey Lloyd', '1221', '61', '180', '5434.01', '4595.87');
INSERT INTO `list_npcs` VALUES ('147', '[Storage Keeper] Dustin Leta', '1222', '61', '197.989', '5489.63', '4553.05');
INSERT INTO `list_npcs` VALUES ('148', '[Smith] Nel Eldora', '1223', '61', '14.2928', '5395.55', '4614.05');
INSERT INTO `list_npcs` VALUES ('149', '[Chef] Peppie', '1224', '61', '190.865', '5626.88', '4435.97');
INSERT INTO `list_npcs` VALUES ('150', '[Raknu Warrior] Toanu', '1229', '61', '180', '5434.62', '4671.5');
INSERT INTO `list_npcs` VALUES ('151', '[Raknu Warrior] Guanu', '1230', '61', '181.501', '5424.42', '4671.62');
INSERT INTO `list_npcs` VALUES ('152', '[Raknu Resident] Jerrita', '1236', '61', '303.017', '5657.17', '4455.98');
INSERT INTO `list_npcs` VALUES ('153', '[Raknu Resident] Netty', '1237', '61', '328.307', '5494.83', '4593.46');
INSERT INTO `list_npcs` VALUES ('154', '[Patrol Dog] Max', '1243', '61', '199.965', '5487.27', '4550.96');
INSERT INTO `list_npcs` VALUES ('155', '[Patrol Dog] Stephen', '1244', '61', '180', '5427.52', '4482.43');
INSERT INTO `list_npcs` VALUES ('156', '[Cleric] Jude', '1251', '62', '330.956', '5851.77', '5209.4');
INSERT INTO `list_npcs` VALUES ('158', '[Sikuku Chief] Namiel Char', '1252', '62', '220.893', '5896.76', '5129.8');
INSERT INTO `list_npcs` VALUES ('159', '[Bird] Hawker', '1253', '62', '220.893', '5901.42', '5130.73');
INSERT INTO `list_npcs` VALUES ('160', '[Sikuku Warrior] Ruduck', '1254', '62', '22.0426', '5779.49', '5040.41');
INSERT INTO `list_npcs` VALUES ('161', '[Sikuku Warrior] Yak', '1255', '62', '24.2373', '5789.36', '5051.35');
INSERT INTO `list_npcs` VALUES ('162', '[Sikuku Warrior] Seka', '1256', '62', '181.501', '5817.34', '5174');
INSERT INTO `list_npcs` VALUES ('163', '[Sikuku Warrior] Kilie', '1257', '62', '333.435', '5647.96', '5126.88');
INSERT INTO `list_npcs` VALUES ('164', '[Sikuku Resident] Martie', '1258', '62', '16.1021', '5638.21', '5127.42');
INSERT INTO `list_npcs` VALUES ('165', '[Sikuku Resident] Carl', '1259', '62', '95.9836', '5714.45', '5121.83');
INSERT INTO `list_npcs` VALUES ('166', '[Sikuku Resident] Parah', '1260', '62', '192.55', '5721.78', '5118.28');
INSERT INTO `list_npcs` VALUES ('167', '[Sikuku Resident] Shilma', '1261', '62', '330.956', '5854.29', '5225.03');
INSERT INTO `list_npcs` VALUES ('168', '[Sikuku Warrior] Wounded Soldier', '1262', '62', '206.565', '5864.97', '5211.14');
INSERT INTO `list_npcs` VALUES ('169', '[Sikuku Warrior] Wounded Soldier', '1263', '62', '350.772', '5862.55', '5218.48');
INSERT INTO `list_npcs` VALUES ('170', '[Critically Wounded] Nukie', '1266', '62', '202.043', '5858.96', '5208.03');
INSERT INTO `list_npcs` VALUES ('171', 'Gate', '1022', '70', '90', '5244.98', '5043.13');
INSERT INTO `list_npcs` VALUES ('172', 'Gate', '1022', '70', '270', '5476.32', '5040.21');
INSERT INTO `list_npcs` VALUES ('173', 'Gate', '1023', '74', '0', '5072.13', '5289.34');
INSERT INTO `list_npcs` VALUES ('174', 'Gate', '1023', '74', '0', '5072.59', '5112.01');
INSERT INTO `list_npcs` VALUES ('175', 'Gate', '1023', '74', '0', '5157.48', '5288.8');
INSERT INTO `list_npcs` VALUES ('176', 'Gate', '1023', '74', '0', '5159.85', '5109.6');
INSERT INTO `list_npcs` VALUES ('177', '[Teleporter] Selladin', '1017', '1', '162.011', '5247.24', '5222.58');
INSERT INTO `list_npcs` VALUES ('178', '[Teleporter] Idiosel', '1119', '2', '270', '5343.67', '5177.36');
