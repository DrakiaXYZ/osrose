/*
MySQL Data Transfer
Source Host: osrose
Source Database: osrose
Target Host: osrose
Target Database: osrose
Date: 7/10/2008 3:53:08 PM
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
  `dialogid` int(11) NOT NULL default '0',
  `eventid` int(11) NOT NULL default '0',
  `tempdialogid` int(11) NOT NULL default '0',
  PRIMARY KEY  (`id`)
) ENGINE=MyISAM AUTO_INCREMENT=435 DEFAULT CHARSET=latin1;

-- ----------------------------
-- Records 
-- ----------------------------
INSERT INTO `list_npcs` VALUES ('179', '[Livestock Farmer] Lampa', '1016', '1', '173.934', '5109.42', '5363.68', '116','0','0');
INSERT INTO `list_npcs` VALUES ('180', '[Ferrell Guild Staff] Crow', '1004', '1', '6.067', '5094.38', '5259.9', '104','0','0');
INSERT INTO `list_npcs` VALUES ('181', '[Ferrell Guild Staff] Ulysses', '1012', '1', '84.016', '5071.26', '5206.92', '112','0','0');
INSERT INTO `list_npcs` VALUES ('182', '[Co-Founder of the Junon Order] Francis', '1003', '1', '157.957', '5080.3', '5066.28', '103','0','0');
INSERT INTO `list_npcs` VALUES ('183', '[Righteous Crusader] Leonard', '1005', '1', '16.102', '5261.08', '5166.96', '105','0','0');
INSERT INTO `list_npcs` VALUES ('184', '[Designer] Keenu', '1010', '1', '343.898', '5273.5', '5256.83', '110','0','0');
INSERT INTO `list_npcs` VALUES ('185', '[Eccentric Inventor] Spero', '1011', '1', '14.293', '5212.36', '5254.66', '111','0','0');
INSERT INTO `list_npcs` VALUES ('186', '[Tavern Owner] Sharlin', '1013', '1', '333.435', '5131.56', '5218.14', '113','0','0');
INSERT INTO `list_npcs` VALUES ('187', '[Resident] Luth', '1015', '1', '270', '5130.61', '5154.58', '115','0','0');
INSERT INTO `list_npcs` VALUES ('188', '[Guide] Lena', '1014', '1', '169.135', '5240.4', '5124.57', '114','0','0');
INSERT INTO `list_npcs` VALUES ('189', '[Event Info] Judy', '1201', '1', '162.011', '5261.88', '5212.97', '305','0','0');
INSERT INTO `list_npcs` VALUES ('190', '[Akram Kingdom Minister] Warren', '1002', '1', '178.499', '5208.78', '5112.94', '102','0','0');
INSERT INTO `list_npcs` VALUES ('191', '[Village Chief] Cornell', '1001', '1', '183.008', '5217.51', '5113.18', '101','0','0');
INSERT INTO `list_npcs` VALUES ('192', '[Cornell\'s Grandson] Cheney', '1018', '1', '22.043', '5436.3', '5492.26', '118','0','0');
INSERT INTO `list_npcs` VALUES ('193', '[Arumic Merchant] Tryteh', '1006', '1', '258.129', '5313.26', '5153.74', '106','0','0');
INSERT INTO `list_npcs` VALUES ('194', '[Gypsy Jewel Seller] Mina', '1007', '1', '197.989', '5292.56', '5127.66', '107','0','0');
INSERT INTO `list_npcs` VALUES ('195', '[Weapon Seller] Raffle', '1008', '1', '322.406', '5302.32', '5232.34', '108','0','0');
INSERT INTO `list_npcs` VALUES ('196', '[Armor Seller] Carrion', '1009', '1', '275.984', '5313.53', '5198.14', '109','0','0');
INSERT INTO `list_npcs` VALUES ('197', '[Keenu\'s Daughter] Arisa', '1020', '1', '275.984', '5428.17', '5082.68', '120','0','0');
INSERT INTO `list_npcs` VALUES ('198', '[Lena\'s Sister] Shirley', '1019', '1', '322.406', '5504.69', '5274.08', '119','0','0');
INSERT INTO `list_npcs` VALUES ('199', '[Righteous Crusader] Gawain', '1090', '2', '84.016', '5334.58', '5353.91', '190','0','0');
INSERT INTO `list_npcs` VALUES ('200', '[Righteous Crusader] Huffe', '1111', '2', '90', '5334.84', '5345.81', '211','0','0');
INSERT INTO `list_npcs` VALUES ('201', '[Clan Owner] Burtland', '1115', '2', '90', '5289.1', '5264.1', '215','0','0');
INSERT INTO `list_npcs` VALUES ('202', '[Clan War Manager] Regina', '1751', '2', '90', '5290.17', '5244.25', '751','0','0');
INSERT INTO `list_npcs` VALUES ('203', '[Clan Merchant] Aliche Patt', '1752', '2', '90', '5288.35', '5260.53', '224','0','0');
INSERT INTO `list_npcs` VALUES ('204', '[Founder of Junon Order] Raw', '1088', '2', '181.501', '5319.27', '5095.36', '188','0','0');
INSERT INTO `list_npcs` VALUES ('205', '[Elder of Junon Order] Gorthein', '1109', '2', '181.501', '5325.54', '5095.31', '209','0','0');
INSERT INTO `list_npcs` VALUES ('206', '[Guide] Eva', '1082', '2', '153.435', '5505.78', '5346.09', '182','0','0');
INSERT INTO `list_npcs` VALUES ('207', '[Soldier] Odelo', '1116', '2', '0', '5507.31', '5397.4', '216','0','0');
INSERT INTO `list_npcs` VALUES ('208', '[Soldier] Winters', '1117', '2', '0', '5522.99', '5397.75', '217','0','0');
INSERT INTO `list_npcs` VALUES ('209', '[Mayor] Darren', '1081', '2', '178.499', '5514.48', '5238.2', '181','0','0');
INSERT INTO `list_npcs` VALUES ('210', '[Event Info] Felice Fete', '1202', '2', '206.565', '5562', '5164.83', '306','0','0');
INSERT INTO `list_npcs` VALUES ('211', '[Guide] Alphonso', '1118', '2', '178.499', '5520.56', '5063.66', '218','0','0');
INSERT INTO `list_npcs` VALUES ('212', '[Historian] Jones', '1104', '2', '162.011', '5578.19', '4890.44', '204','0','0');
INSERT INTO `list_npcs` VALUES ('213', '[Vicious Captain] Ruven', '1125', '2', '270', '5597.76', '4918.87', '220','0','0');
INSERT INTO `list_npcs` VALUES ('214', '[Manager of Ferrell] Arothel', '1089', '2', '270', '5713.43', '5360.16', '189','0','0');
INSERT INTO `list_npcs` VALUES ('215', '[Armor Merchant] Saki', '1094', '2', '258.129', '5721.8', '5290.79', '194','0','0');
INSERT INTO `list_npcs` VALUES ('216', '[Ferrell Guild Staff] Charrs', '1110', '2', '270', '5713.38', '5368.71', '210','0','0');
INSERT INTO `list_npcs` VALUES ('217', '[Gypsy Jewel Seller] Bellia', '1092', '2', '217.594', '5725.11', '5199.04', '192','0','0');
INSERT INTO `list_npcs` VALUES ('218', '[Weapon Merchant] Crune', '1093', '2', '335.763', '5728.67', '5224.89', '193','0','0');
INSERT INTO `list_npcs` VALUES ('219', '[Designer] Lisa', '1095', '2', '220.893', '5729.06', '5136.33', '195','0','0');
INSERT INTO `list_npcs` VALUES ('220', '[Ferrell Guild Merchant] Mildun', '1096', '2', '165.707', '5673.16', '5193.89', '196','0','0');
INSERT INTO `list_npcs` VALUES ('221', '[Tavern Owner] Harin', '1097', '2', '90', '5681.79', '5131.11', '197','0','0');
INSERT INTO `list_npcs` VALUES ('222', '[Arumic Merchant] Chelsie', '1091', '2', '211.693', '5723.96', '5087.24', '191','0','0');
INSERT INTO `list_npcs` VALUES ('223', '[Ferrell Guild Staff] Kiroth', '1098', '2', '275.984', '5603.58', '5058.1', '198','0','0');
INSERT INTO `list_npcs` VALUES ('224', '[Ferrell Guild Staff] Hayen', '1099', '2', '258.129', '5603.77', '5046.12', '199','0','0');
INSERT INTO `list_npcs` VALUES ('225', '[Ferrell Guild Staff] Itz', '1100', '2', '270', '5603.69', '5034.52', '200','0','0');
INSERT INTO `list_npcs` VALUES ('226', '[Arumic Researcher] Carasia', '1112', '2', '197.989', '5730.57', '5094.06', '212','0','0');
INSERT INTO `list_npcs` VALUES ('227', '[Livestock Farmer] Sicru', '1107', '2', '187.631', '5818.02', '5487.59', '207','0','0');
INSERT INTO `list_npcs` VALUES ('228', '[Ferrell Guild Staff] Rooen', '1513', '3', '0', '5104.48', '5019.71', '303','0','0');
INSERT INTO `list_npcs` VALUES ('229', '[Akram Minister] Rodath', '1086', '5', '90', '5155.07', '5279.92', '186','0','0');
INSERT INTO `list_npcs` VALUES ('230', '[Akram Minister] Mel', '1087', '5', '270', '5247.07', '5279.96', '187','0','0');
INSERT INTO `list_npcs` VALUES ('231', '[Akram Minister] Gamp', '1084', '6', '270', '5248.14', '5279.2', '187','0','0');
INSERT INTO `list_npcs` VALUES ('232', '[Referee] Leum', '1113', '9', '0', '5199.99', '5390.04', '213','0','0');
INSERT INTO `list_npcs` VALUES ('233', '[Referee] Pirre', '1114', '9', '180', '5201.59', '4765.69', '214','0','0');
INSERT INTO `list_npcs` VALUES ('234', '[Akram Minister] Nell', '1085', '11', '84.016', '4953.37', '4992.35', '184','0','0');
INSERT INTO `list_npcs` VALUES ('235', '[Akram Minister] Nell', '1085', '11', '10.865', '4978.48', '5478.6', '184','0','0');
INSERT INTO `list_npcs` VALUES ('236', '[Akram Minister] Nell', '1085', '11', '337.957', '5455.57', '5478.99', '184','0','0');
INSERT INTO `list_npcs` VALUES ('237', '[Akram Minister] Nell', '1085', '11', '335.763', '5521.94', '5020.66', '184','0','0');
INSERT INTO `list_npcs` VALUES ('238', '[Akram Minister] Nell', '1085', '12', '84.016', '4953.37', '4992.35', '184','0','0');
INSERT INTO `list_npcs` VALUES ('239', '[Akram Minister] Nell', '1085', '12', '10.865', '4978.48', '5478.6', '184','0','0');
INSERT INTO `list_npcs` VALUES ('240', '[Akram Minister] Nell', '1085', '12', '337.957', '5455.57', '5478.99', '184','0','0');
INSERT INTO `list_npcs` VALUES ('241', '[Akram Minister] Nell', '1085', '12', '335.763', '5521.94', '5020.66', '184','0','0');
INSERT INTO `list_npcs` VALUES ('242', '[Akram Minister] Nell', '1085', '13', '84.016', '4953.37', '4992.35', '184','0','0');
INSERT INTO `list_npcs` VALUES ('243', '[Akram Minister] Nell', '1085', '13', '10.865', '4978.48', '5478.6', '184','0','0');
INSERT INTO `list_npcs` VALUES ('244', '[Akram Minister] Nell', '1085', '13', '337.957', '5455.57', '5478.99', '184','0','0');
INSERT INTO `list_npcs` VALUES ('245', '[Akram Minister] Nell', '1085', '13', '335.763', '5521.94', '5020.66', '184','0','0');
INSERT INTO `list_npcs` VALUES ('246', '[Clan House Soldier] Jason', '1162', '15', '183.008', '5205.79', '5129.92', '262','0','0');
INSERT INTO `list_npcs` VALUES ('247', '[Clan House Manager] Kushard', '1161', '15', '0', '5200.16', '5209.81', '261','0','0');
INSERT INTO `list_npcs` VALUES ('248', '[Clan House Soldier] Jason', '1162', '15', '181.501', '5204.57', '4970.37', '262','0','0');
INSERT INTO `list_npcs` VALUES ('249', '[Clan House Manager] Kushard', '1161', '15', '0', '5200.13', '5051.79', '261','0','0');
INSERT INTO `list_npcs` VALUES ('250', '[Clan House Soldier] Jason', '1162', '15', '181.501', '5203.89', '4809.55', '262','0','0');
INSERT INTO `list_npcs` VALUES ('251', '[Clan House Manager] Kushard', '1161', '15', '0', '5200.16', '4890.67', '261','0','0');
INSERT INTO `list_npcs` VALUES ('252', '[Clan House Manager] Kushard', '1161', '15', '0', '5360.21', '5210.15', '261','0','0');
INSERT INTO `list_npcs` VALUES ('253', '[Clan House Soldier] Jason', '1162', '15', '180', '5363.94', '5130.38', '262','0','0');
INSERT INTO `list_npcs` VALUES ('254', '[Clan House Soldier] Jason', '1162', '15', '180', '5364.04', '4970.33', '262','0','0');
INSERT INTO `list_npcs` VALUES ('255', '[Clan House Manager] Kushard', '1161', '15', '0', '5360.2', '5051.41', '261','0','0');
INSERT INTO `list_npcs` VALUES ('256', '[Clan House Soldier] Jason', '1162', '15', '183.008', '5363.85', '4810.42', '262','0','0');
INSERT INTO `list_npcs` VALUES ('257', '[Clan House Manager] Kushard', '1161', '15', '0', '5360.25', '4890.3', '261','0','0');
INSERT INTO `list_npcs` VALUES ('258', '[Clan House Soldier] Jason', '1162', '15', '183.008', '5524.3', '5129.46', '262','0','0');
INSERT INTO `list_npcs` VALUES ('259', '[Clan House Manager] Kushard', '1161', '15', '0', '5520.19', '5211.31', '261','0','0');
INSERT INTO `list_npcs` VALUES ('260', '[Clan House Soldier] Jason', '1162', '15', '183.008', '5523.83', '4970.15', '262','0','0');
INSERT INTO `list_npcs` VALUES ('261', '[Clan House Manager] Kushard', '1161', '15', '0', '5520.18', '5051.41', '261','0','0');
INSERT INTO `list_npcs` VALUES ('262', '[Clan House Soldier] Jason', '1162', '15', '181.501', '5523.67', '4810.61', '262','0','0');
INSERT INTO `list_npcs` VALUES ('263', '[Clan House Manager] Kushard', '1161', '15', '0', '5520.16', '4891.07', '261','0','0');
INSERT INTO `list_npcs` VALUES ('264', '[Arumic Researcher] Lutis', '1051', '21', '160.035', '5118.14', '5374.91', '151','0','0');
INSERT INTO `list_npcs` VALUES ('265', '[Cleric] Karitte', '1053', '21', '95.984', '5112.44', '5385.08', '153','0','0');
INSERT INTO `list_npcs` VALUES ('266', '[Mountain Guide] Shannon', '1052', '21', '353.933', '5357.27', '5282.19', '152','0','0');
INSERT INTO `list_npcs` VALUES ('267', '[Visitor Guide] Arua\'s Fairy', '1030', '22', '90', '5060.19', '5522.94', '130','0','0');
INSERT INTO `list_npcs` VALUES ('268', '[Village Chief] Gray', '1038', '22', '157.957', '5083.86', '5284.24', '138','0','0');
INSERT INTO `list_npcs` VALUES ('269', '[Old Man] Myad', '1041', '22', '17.989', '5078.07', '5372.4', '141','0','0');
INSERT INTO `list_npcs` VALUES ('270', '[Novice Designer] Cassirin', '1040', '22', '355.472', '5103.53', '5378.9', '140','0','0');
INSERT INTO `list_npcs` VALUES ('271', '[Fruit Store] Reene', '1039', '22', '26.565', '5061.58', '5342.24', '139','0','0');
INSERT INTO `list_npcs` VALUES ('272', '[Ferrell Guild Storage Keeper] Fabrizio', '1042', '22', '192.55', '5113.43', '5260.64', '143','0','0');
INSERT INTO `list_npcs` VALUES ('273', 'Melendino', '1473', '22', '142.406', '5107.44', '5013.71', '0','0','0');
INSERT INTO `list_npcs` VALUES ('274', '[Visitor Guide] Ronway', '1031', '22', '246.969', '5147.55', '5356.75', '131','0','0');
INSERT INTO `list_npcs` VALUES ('275', '[Smith] Ronk', '1034', '22', '224.459', '5140.96', '5303.35', '134','0','0');
INSERT INTO `list_npcs` VALUES ('276', '[Akram Minister] Mairard', '1032', '22', '298.187', '5154.85', '5332.74', '132','0','0');
INSERT INTO `list_npcs` VALUES ('277', '[Boy in the Hut]Huey', '1021', '22', '333.435', '5650.66', '5407.16', '0','0','0');
INSERT INTO `list_npcs` VALUES ('278', '[Ferrell Guild Staff] Peron', '1511', '22', '275.984', '5905.42', '5306.42', '301','0','0');
INSERT INTO `list_npcs` VALUES ('279', '[Ferrell Guild Staff] Seyon', '1036', '22', '293.031', '5882.08', '5420.74', '136','0','0');
INSERT INTO `list_npcs` VALUES ('280', '[Little Street Vendor] Pony', '1035', '22', '0', '5860.22', '5431.89', '135','0','0');
INSERT INTO `list_npcs` VALUES ('281', '[Ferrell Guild Staff] Belz', '1061', '23', '270', '5358.63', '5058.99', '161','0','0');
INSERT INTO `list_npcs` VALUES ('282', '[Smith] Punwell', '1062', '23', '24.237', '5340.65', '5070.26', '162','0','0');
INSERT INTO `list_npcs` VALUES ('283', '[Little Street Vendor] Mile', '1063', '23', '307.514', '5356.41', '5043.28', '163','0','0');
INSERT INTO `list_npcs` VALUES ('284', '[Weapon Craftsman] Mairath', '1064', '23', '180', '5349.02', '5033.95', '164','0','0');
INSERT INTO `list_npcs` VALUES ('285', '[Ferrell Guild Merchant] Lina', '1071', '24', '293.031', '5567.26', '4927.03', '171','0','0');
INSERT INTO `list_npcs` VALUES ('286', '[Gypsy Merchant] Methio', '1072', '24', '192.55', '5563.13', '4895.45', '172','0','0');
INSERT INTO `list_npcs` VALUES ('287', '[Ikaness Staff] Orias', '1073', '24', '95.984', '5515.26', '4925.14', '173','0','0');
INSERT INTO `list_npcs` VALUES ('288', '[Ikaness Staff] Shroon', '1121', '25', '9.228', '5375.78', '5188.33', '221','0','0');
INSERT INTO `list_npcs` VALUES ('289', '[Guide of Plain] Pein', '1122', '25', '307.514', '5503.22', '5350.93', '222','0','0');
INSERT INTO `list_npcs` VALUES ('290', '[Gypsy Seller] Edone', '1123', '25', '187.631', '5448.14', '4976.37', '223','0','0');
INSERT INTO `list_npcs` VALUES ('291', '[Mountain Guide] Kay', '1131', '26', '22.043', '5669.16', '5105.24', '231','0','0');
INSERT INTO `list_npcs` VALUES ('292', '[Ferrell Guild Merchant ] Bith', '1143', '27', '197.989', '5259.72', '5147.64', '243','0','0');
INSERT INTO `list_npcs` VALUES ('293', '[Ferrell Guild Staff] Robin', '1512', '27', '264.016', '5239.23', '5040.74', '302','0','0');
INSERT INTO `list_npcs` VALUES ('294', '[Resident] Hotch', '1144', '27', '189.228', '5384.23', '5180.1', '244','0','0');
INSERT INTO `list_npcs` VALUES ('295', '[Righteous Crusader] Gallahad', '1141', '27', '178.499', '5345.2', '5047.71', '241','0','0');
INSERT INTO `list_npcs` VALUES ('296', '[Akram Minister] Luce', '1142', '27', '101.871', '5320.52', '5081.27', '242','0','0');
INSERT INTO `list_npcs` VALUES ('297', '[Ferrell Guild Merchant] Med', '1151', '28', '127.514', '5587.09', '4732.29', '251','0','0');
INSERT INTO `list_npcs` VALUES ('298', '[Dead Priest] Lantore', '1154', '29', '241.813', '5114.61', '5131.16', '254','0','0');
INSERT INTO `list_npcs` VALUES ('299', '[Town Girl] Lithia', '1156', '29', '24.237', '5091.98', '5181.81', '256','0','0');
INSERT INTO `list_npcs` VALUES ('300', '[Ghost] Harry', '1157', '29', '184.528', '5051.39', '5119.6', '257','0','0');
INSERT INTO `list_npcs` VALUES ('301', '[Ranger] Paul', '1155', '29', '330.956', '5157.1', '5176.39', '255','0','0');
INSERT INTO `list_npcs` VALUES ('302', '[Event Info] Judith', '1204', '37', '358.499', '5115.68', '5324.15', '308','0','0');
INSERT INTO `list_npcs` VALUES ('303', '[Event Info] Santa Claus', '1205', '38', '3.012', '5069.18', '5362.51', '309','0','0');
INSERT INTO `list_npcs` VALUES ('304', '[Event Info] Loelsch', '1206', '38', '66.941', '5057.19', '5351.61', '310','0','0');
INSERT INTO `list_npcs` VALUES ('305', '[Event Info] Lucielle Fete', '1203', '40', '333.435', '5254.64', '5216.39', '307','0','0');
INSERT INTO `list_npcs` VALUES ('306', '[Station Guide] Illiya', '1188', '51', '148.307', '5107.24', '4996.57', '288','0','0');
INSERT INTO `list_npcs` VALUES ('307', '[Tavern Owner] Anzhelika', '1186', '51', '139.107', '5263.61', '5079.49', '286','0','0');
INSERT INTO `list_npcs` VALUES ('308', '[Ferrell Guild Banker] Andre', '1180', '51', '0', '5414.86', '5114.41', '280','0','0');
INSERT INTO `list_npcs` VALUES ('309', '[Magic Goods Seller] Pabel', '1185', '51', '3.008', '5298.98', '5105.03', '285','0','0');
INSERT INTO `list_npcs` VALUES ('310', '[Arumic Prophet] Olleck Basilasi', '1173', '51', '178.499', '5359.62', '5085.72', '273','0','0');
INSERT INTO `list_npcs` VALUES ('311', '[Akram Ambassador] Eliot', '1172', '51', '157.957', '5285.69', '4940.95', '272','0','0');
INSERT INTO `list_npcs` VALUES ('312', '[Eucar Judge] Ishtal', '1171', '51', '206.565', '5430.09', '4937.96', '271','0','0');
INSERT INTO `list_npcs` VALUES ('313', '[Smith] Pavrick', '1181', '51', '335.763', '5440.45', '5103.41', '281','0','0');
INSERT INTO `list_npcs` VALUES ('314', '[Ferrell Trader] Sergei', '1184', '51', '258.129', '5450.88', '5077.06', '284','0','0');
INSERT INTO `list_npcs` VALUES ('315', '[Shamanist] Est', '1191', '54', '84.016', '5088.26', '4257.84', '291','0','0');
INSERT INTO `list_npcs` VALUES ('316', '[Station Guide] Chacha', '1219', '61', '12.55', '5226.6', '4452.72', '319','0','0');
INSERT INTO `list_npcs` VALUES ('317', '[Raknu Warrior] Toanu', '1229', '61', '180', '5434.62', '4671.5', '329','0','0');
INSERT INTO `list_npcs` VALUES ('318', '[Raknu Warrior] Guanu', '1230', '61', '181.501', '5424.42', '4671.62', '330','0','0');
INSERT INTO `list_npcs` VALUES ('319', '[Elder of Junon Order] Oscar Patrick', '1214', '61', '157.957', '5371.18', '4546.51', '314','0','0');
INSERT INTO `list_npcs` VALUES ('320', '[Righteous Crusader] Harold Evan', '1211', '61', '14.293', '5369.75', '4575.29', '311','0','0');
INSERT INTO `list_npcs` VALUES ('321', '[Smith] Nel Eldora', '1223', '61', '14.293', '5395.55', '4614.05', '323','0','0');
INSERT INTO `list_npcs` VALUES ('322', '[Akram Ambassador] Jacklyn Cooper', '1215', '61', '180', '5430', '4483.79', '315','0','0');
INSERT INTO `list_npcs` VALUES ('323', '[Patrol Dog] Stephen', '1244', '61', '180', '5427.52', '4482.43', '317','0','0');
INSERT INTO `list_npcs` VALUES ('324', '[Raknu Warrior] Jeffrey Lloyd', '1221', '61', '180', '5434.01', '4595.87', '321','0','0');
INSERT INTO `list_npcs` VALUES ('325', '[Arumic Researcher] Catherine Clara', '1212', '61', '330.956', '5473.37', '4618.79', '312','0','0');
INSERT INTO `list_npcs` VALUES ('326', '[Ferrell Guild Staff] Gilbert', '1213', '61', '217.594', '5474.35', '4513.74', '313','0','0');
INSERT INTO `list_npcs` VALUES ('327', '[Storage Keeper] Dustin Leta', '1222', '61', '197.989', '5489.63', '4553.05', '322','0','0');
INSERT INTO `list_npcs` VALUES ('328', '[Patrol Dog] Max', '1243', '61', '199.965', '5487.27', '4550.96', '316','0','0');
INSERT INTO `list_npcs` VALUES ('329', '[Raknu Resident] Netty', '1237', '61', '328.307', '5494.83', '4593.46', '337','0','0');
INSERT INTO `list_npcs` VALUES ('330', '[Chef] Peppie', '1224', '61', '190.865', '5626.88', '4435.97', '324','0','0');
INSERT INTO `list_npcs` VALUES ('331', '[Raknu Chief] Darka Khan', '1220', '61', '352.369', '5650.09', '4464.73', '320','0','0');
INSERT INTO `list_npcs` VALUES ('332', '[Raknu Resident] Jerrita', '1236', '61', '303.017', '5657.17', '4455.98', '336','0','0');
INSERT INTO `list_npcs` VALUES ('333', '[Sikuku Warrior] Kilie', '1257', '62', '333.435', '5647.96', '5126.88', '356','0','0');
INSERT INTO `list_npcs` VALUES ('334', '[Sikuku Resident] Martie', '1258', '62', '16.102', '5638.21', '5127.42', '357','0','0');
INSERT INTO `list_npcs` VALUES ('335', '[Sikuku Resident] Carl', '1259', '62', '95.984', '5714.45', '5121.83', '358','0','0');
INSERT INTO `list_npcs` VALUES ('336', '[Sikuku Resident] Parah', '1260', '62', '192.55', '5721.78', '5118.28', '359','0','0');
INSERT INTO `list_npcs` VALUES ('337', '[Sikuku Chief] Namiel Char', '1252', '62', '220.893', '5896.76', '5129.8', '352','0','0');
INSERT INTO `list_npcs` VALUES ('338', '[Cleric] Jude', '1251', '62', '330.956', '5851.77', '5209.4', '351','0','0');
INSERT INTO `list_npcs` VALUES ('339', '[Bird] Hawker', '1253', '62', '220.893', '5901.42', '5130.73', '364','0','0');
INSERT INTO `list_npcs` VALUES ('340', '[Sikuku Warrior] Seka', '1256', '62', '181.501', '5817.34', '5174', '355','0','0');
INSERT INTO `list_npcs` VALUES ('341', '[Sikuku Resident] Shilma', '1261', '62', '330.956', '5854.29', '5225.03', '360','0','0');
INSERT INTO `list_npcs` VALUES ('342', '[Sikuku Warrior] Wounded Soldier', '1262', '62', '206.565', '5864.97', '5211.14', '361','0','0');
INSERT INTO `list_npcs` VALUES ('343', '[Sikuku Warrior] Wounded Soldier', '1263', '62', '350.772', '5862.55', '5218.48', '361','0','0');
INSERT INTO `list_npcs` VALUES ('344', '[Critically Wounded] Nukie', '1266', '62', '202.043', '5858.96', '5208.03', '363','0','0');
INSERT INTO `list_npcs` VALUES ('345', '[Sikuku Warrior] Yak', '1255', '62', '24.237', '5789.36', '5051.35', '354','0','0');
INSERT INTO `list_npcs` VALUES ('346', '[Sikuku Warrior] Ruduck', '1254', '62', '22.043', '5779.49', '5040.41', '353','0','0');
INSERT INTO `list_npcs` VALUES ('347', 'Gate', '1022', '70', '90', '5244.98', '5043.13', '0','0','0');
INSERT INTO `list_npcs` VALUES ('348', 'Gate', '1022', '70', '270', '5476.32', '5040.21', '0','0','0');
INSERT INTO `list_npcs` VALUES ('349', 'Gate', '1023', '74', '0', '5072.13', '5289.34', '0','0','0');
INSERT INTO `list_npcs` VALUES ('350', 'Gate', '1023', '74', '0', '5072.59', '5112.01', '0','0','0');
INSERT INTO `list_npcs` VALUES ('351', 'Gate', '1023', '74', '0', '5157.48', '5288.8', '0','0','0');
INSERT INTO `list_npcs` VALUES ('352', 'Gate', '1023', '74', '0', '5159.85', '5109.6', '0','0','0');
INSERT INTO `list_npcs` VALUES ('353', 'Gate', '1023', '101', '0', '5072.13', '5289.34', '0','0','0');
INSERT INTO `list_npcs` VALUES ('354', 'Gate', '1023', '101', '0', '5072.59', '5112.01', '0','0','0');
INSERT INTO `list_npcs` VALUES ('355', 'Gate', '1023', '101', '0', '5157.48', '5288.8', '0','0','0');
INSERT INTO `list_npcs` VALUES ('356', 'Gate', '1023', '101', '0', '5159.85', '5109.6', '0','0','0');
INSERT INTO `list_npcs` VALUES ('357', 'Gate', '1023', '102', '0', '5072.13', '5289.34', '0','0','0');
INSERT INTO `list_npcs` VALUES ('358', 'Gate', '1023', '102', '0', '5072.59', '5112.01', '0','0','0');
INSERT INTO `list_npcs` VALUES ('359', 'Gate', '1023', '102', '0', '5157.48', '5288.8', '0','0','0');
INSERT INTO `list_npcs` VALUES ('360', 'Gate', '1023', '102', '0', '5159.85', '5109.6', '0','0','0');
INSERT INTO `list_npcs` VALUES ('361', 'Gate', '1023', '103', '0', '5072.13', '5289.34', '0','0','0');
INSERT INTO `list_npcs` VALUES ('362', 'Gate', '1023', '103', '0', '5072.59', '5112.01', '0','0','0');
INSERT INTO `list_npcs` VALUES ('363', 'Gate', '1023', '103', '0', '5157.48', '5288.8', '0','0','0');
INSERT INTO `list_npcs` VALUES ('364', 'Gate', '1023', '103', '0', '5159.85', '5109.6', '0','0','0');
INSERT INTO `list_npcs` VALUES ('365', 'Gate', '1023', '104', '0', '5072.13', '5289.34', '0','0','0');
INSERT INTO `list_npcs` VALUES ('366', 'Gate', '1023', '104', '0', '5072.59', '5112.01', '0','0','0');
INSERT INTO `list_npcs` VALUES ('367', 'Gate', '1023', '104', '0', '5157.48', '5288.8', '0','0','0');
INSERT INTO `list_npcs` VALUES ('368', 'Gate', '1023', '104', '0', '5159.85', '5109.6', '0','0','0');
INSERT INTO `list_npcs` VALUES ('369', 'Gate', '1023', '105', '0', '5072.13', '5289.34', '0','0','0');
INSERT INTO `list_npcs` VALUES ('370', 'Gate', '1023', '105', '0', '5072.59', '5112.01', '0','0','0');
INSERT INTO `list_npcs` VALUES ('371', 'Gate', '1023', '105', '0', '5157.48', '5288.8', '0','0','0');
INSERT INTO `list_npcs` VALUES ('372', 'Gate', '1023', '105', '0', '5159.85', '5109.6', '0','0','0');
INSERT INTO `list_npcs` VALUES ('373', 'Gate', '1023', '106', '0', '5072.13', '5289.34', '0','0','0');
INSERT INTO `list_npcs` VALUES ('374', 'Gate', '1023', '106', '0', '5072.59', '5112.01', '0','0','0');
INSERT INTO `list_npcs` VALUES ('375', 'Gate', '1023', '106', '0', '5157.48', '5288.8', '0','0','0');
INSERT INTO `list_npcs` VALUES ('376', 'Gate', '1023', '106', '0', '5159.85', '5109.6', '0','0','0');
INSERT INTO `list_npcs` VALUES ('377', 'Gate', '1023', '107', '0', '5072.13', '5289.34', '0','0','0');
INSERT INTO `list_npcs` VALUES ('378', 'Gate', '1023', '107', '0', '5072.59', '5112.01', '0','0','0');
INSERT INTO `list_npcs` VALUES ('379', 'Gate', '1023', '107', '0', '5157.48', '5288.8', '0','0','0');
INSERT INTO `list_npcs` VALUES ('380', 'Gate', '1023', '107', '0', '5159.85', '5109.6', '0','0','0');
INSERT INTO `list_npcs` VALUES ('381', 'Gate', '1023', '108', '0', '5072.13', '5289.34', '0','0','0');
INSERT INTO `list_npcs` VALUES ('382', 'Gate', '1023', '108', '0', '5072.59', '5112.01', '0','0','0');
INSERT INTO `list_npcs` VALUES ('383', 'Gate', '1023', '108', '0', '5157.48', '5288.8', '0','0','0');
INSERT INTO `list_npcs` VALUES ('384', 'Gate', '1023', '108', '0', '5159.85', '5109.6', '0','0','0');
INSERT INTO `list_npcs` VALUES ('385', 'Gate', '1023', '109', '0', '5072.13', '5289.34', '0','0','0');
INSERT INTO `list_npcs` VALUES ('386', 'Gate', '1023', '109', '0', '5072.59', '5112.01', '0','0','0');
INSERT INTO `list_npcs` VALUES ('387', 'Gate', '1023', '109', '0', '5157.48', '5288.8', '0','0','0');
INSERT INTO `list_npcs` VALUES ('388', 'Gate', '1023', '109', '0', '5159.85', '5109.6', '0','0','0');
INSERT INTO `list_npcs` VALUES ('389', 'Gate', '1023', '110', '0', '5072.13', '5289.34', '0','0','0');
INSERT INTO `list_npcs` VALUES ('390', 'Gate', '1023', '110', '0', '5072.59', '5112.01', '0','0','0');
INSERT INTO `list_npcs` VALUES ('391', 'Gate', '1023', '110', '0', '5157.48', '5288.8', '0','0','0');
INSERT INTO `list_npcs` VALUES ('392', 'Gate', '1023', '110', '0', '5159.85', '5109.6', '0','0','0');
INSERT INTO `list_npcs` VALUES ('393', 'Gate', '1023', '111', '0', '5072.13', '5289.34', '0','0','0');
INSERT INTO `list_npcs` VALUES ('394', 'Gate', '1023', '111', '0', '5072.59', '5112.01', '0','0','0');
INSERT INTO `list_npcs` VALUES ('395', 'Gate', '1023', '111', '0', '5157.48', '5288.8', '0','0','0');
INSERT INTO `list_npcs` VALUES ('396', 'Gate', '1023', '111', '0', '5159.85', '5109.6', '0','0','0');
INSERT INTO `list_npcs` VALUES ('397', 'Gate', '1023', '112', '0', '5072.13', '5289.34', '0','0','0');
INSERT INTO `list_npcs` VALUES ('398', 'Gate', '1023', '112', '0', '5072.59', '5112.01', '0','0','0');
INSERT INTO `list_npcs` VALUES ('399', 'Gate', '1023', '112', '0', '5157.48', '5288.8', '0','0','0');
INSERT INTO `list_npcs` VALUES ('400', 'Gate', '1023', '112', '0', '5159.85', '5109.6', '0','0','0');
INSERT INTO `list_npcs` VALUES ('401', 'Gate', '1023', '113', '0', '5072.13', '5289.34', '0','0','0');
INSERT INTO `list_npcs` VALUES ('402', 'Gate', '1023', '113', '0', '5072.59', '5112.01', '0','0','0');
INSERT INTO `list_npcs` VALUES ('403', 'Gate', '1023', '113', '0', '5157.48', '5288.8', '0','0','0');
INSERT INTO `list_npcs` VALUES ('404', 'Gate', '1023', '113', '0', '5159.85', '5109.6', '0','0','0');
INSERT INTO `list_npcs` VALUES ('405', 'Gate', '1023', '114', '0', '5072.13', '5289.34', '0','0','0');
INSERT INTO `list_npcs` VALUES ('406', 'Gate', '1023', '114', '0', '5072.59', '5112.01', '0','0','0');
INSERT INTO `list_npcs` VALUES ('407', 'Gate', '1023', '114', '0', '5157.48', '5288.8', '0','0','0');
INSERT INTO `list_npcs` VALUES ('408', 'Gate', '1023', '114', '0', '5159.85', '5109.6', '0','0','0');
INSERT INTO `list_npcs` VALUES ('409', 'Gate', '1023', '115', '0', '5072.13', '5289.34', '0','0','0');
INSERT INTO `list_npcs` VALUES ('410', 'Gate', '1023', '115', '0', '5072.59', '5112.01', '0','0','0');
INSERT INTO `list_npcs` VALUES ('411', 'Gate', '1023', '115', '0', '5157.48', '5288.8', '0','0','0');
INSERT INTO `list_npcs` VALUES ('412', 'Gate', '1023', '115', '0', '5159.85', '5109.6', '0','0','0');
INSERT INTO `list_npcs` VALUES ('413', 'Gate', '1023', '116', '0', '5072.13', '5289.34', '0','0','0');
INSERT INTO `list_npcs` VALUES ('414', 'Gate', '1023', '116', '0', '5072.59', '5112.01', '0','0','0');
INSERT INTO `list_npcs` VALUES ('415', 'Gate', '1023', '116', '0', '5157.48', '5288.8', '0','0','0');
INSERT INTO `list_npcs` VALUES ('416', 'Gate', '1023', '116', '0', '5159.85', '5109.6', '0','0','0');
INSERT INTO `list_npcs` VALUES ('417', 'Gate', '1023', '117', '0', '5072.13', '5289.34', '0','0','0');
INSERT INTO `list_npcs` VALUES ('418', 'Gate', '1023', '117', '0', '5072.59', '5112.01', '0','0','0');
INSERT INTO `list_npcs` VALUES ('419', 'Gate', '1023', '117', '0', '5157.48', '5288.8', '0','0','0');
INSERT INTO `list_npcs` VALUES ('420', 'Gate', '1023', '117', '0', '5159.85', '5109.6', '0','0','0');
INSERT INTO `list_npcs` VALUES ('421', 'Gate', '1023', '118', '0', '5072.13', '5289.34', '0','0','0');
INSERT INTO `list_npcs` VALUES ('422', 'Gate', '1023', '118', '0', '5072.59', '5112.01', '0','0','0');
INSERT INTO `list_npcs` VALUES ('423', 'Gate', '1023', '118', '0', '5157.48', '5288.8', '0','0','0');
INSERT INTO `list_npcs` VALUES ('424', 'Gate', '1023', '118', '0', '5159.85', '5109.6', '0','0','0');
INSERT INTO `list_npcs` VALUES ('425', 'Gate', '1023', '119', '0', '5072.13', '5289.34', '0','0','0');
INSERT INTO `list_npcs` VALUES ('426', 'Gate', '1023', '119', '0', '5072.59', '5112.01', '0','0','0');
INSERT INTO `list_npcs` VALUES ('427', 'Gate', '1023', '119', '0', '5157.48', '5288.8', '0','0','0');
INSERT INTO `list_npcs` VALUES ('428', 'Gate', '1023', '119', '0', '5159.85', '5109.6', '0','0','0');
INSERT INTO `list_npcs` VALUES ('429', 'Gate', '1023', '120', '0', '5072.13', '5289.34', '0','0','0');
INSERT INTO `list_npcs` VALUES ('430', 'Gate', '1023', '120', '0', '5072.59', '5112.01', '0','0','0');
INSERT INTO `list_npcs` VALUES ('431', 'Gate', '1023', '120', '0', '5157.48', '5288.8', '0','0','0');
INSERT INTO `list_npcs` VALUES ('432', 'Gate', '1023', '120', '0', '5159.85', '5109.6', '0','0','0');
INSERT INTO `list_npcs` VALUES ('433', '[Teleporter] Selladin', '1017', '1', '162.011', '5247.24', '5222.58', '117','0','0');
INSERT INTO `list_npcs` VALUES ('434', '[Teleporter] Idiosel', '1119', '2', '270', '5343.67', '5177.36', '219','0','0');
