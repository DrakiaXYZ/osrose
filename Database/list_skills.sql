/*
MySQL Data Transfer
Source Host: localhost
Source Database: osrose
Target Host: localhost
Target Database: osrose
Date: 6/23/2009 3:45:35 PM
*/

SET FOREIGN_KEY_CHECKS=0;
-- ----------------------------
-- Table structure for list_skills
-- ----------------------------
CREATE TABLE `list_skills` (
  `id` int(11) NOT NULL auto_increment,
  `classid` int(11) NOT NULL,
  `skillid` int(11) NOT NULL,
  `skill_level` varchar(4) NOT NULL,
  `description` varchar(50) default NULL,
  `isactive` int(11) NOT NULL default '1',
  PRIMARY KEY  (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=406 DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records 
-- ----------------------------
INSERT INTO `list_skills` VALUES ('1', '121', '201', '9', 'Physical Training', '1');
INSERT INTO `list_skills` VALUES ('2', '121', '211', '9', 'Repose', '1');
INSERT INTO `list_skills` VALUES ('3', '121', '221', '9', 'Defense Training', '1');
INSERT INTO `list_skills` VALUES ('4', '121', '231', '5', 'Power Owerflow', '1');
INSERT INTO `list_skills` VALUES ('5', '121', '236', '5', 'howl', '1');
INSERT INTO `list_skills` VALUES ('6', '121', '241', '9', 'staminal assist', '1');
INSERT INTO `list_skills` VALUES ('7', '121', '251', '9', 'Melee Weapon Mastery', '1');
INSERT INTO `list_skills` VALUES ('8', '121', '261', '9', 'Melee Double Attack', '1');
INSERT INTO `list_skills` VALUES ('9', '121', '271', '9', 'One Handed Weapon Mastery', '1');
INSERT INTO `list_skills` VALUES ('10', '121', '281', '9', 'Shield Mastery', '1');
INSERT INTO `list_skills` VALUES ('11', '121', '291', '9', 'Fatal Thrust', '1');
INSERT INTO `list_skills` VALUES ('12', '121', '301', '5', 'durability assist', '1');
INSERT INTO `list_skills` VALUES ('13', '121', '306', '5', 'Shield Stun', '1');
INSERT INTO `list_skills` VALUES ('14', '121', '311', '4', 'soul wreck', '1');
INSERT INTO `list_skills` VALUES ('15', '121', '416', '5', 'taunt', '1');
INSERT INTO `list_skills` VALUES ('16', '121', '421', '4', 'soundles vacuum', '1');
INSERT INTO `list_skills` VALUES ('17', '121', '431', '9', 'Advanced Defense Training', '1');
INSERT INTO `list_skills` VALUES ('18', '121', '441', '9', 'One-Handed Combat Mastery', '1');
INSERT INTO `list_skills` VALUES ('19', '121', '451', '9', 'Actual Battle Training', '1');
INSERT INTO `list_skills` VALUES ('20', '121', '461', '18', 'Advanced Shield Mastery', '1');
INSERT INTO `list_skills` VALUES ('21', '121', '481', '9', 'Triple Strike', '1');
INSERT INTO `list_skills` VALUES ('22', '121', '491', '5', 'safe guard', '1');
INSERT INTO `list_skills` VALUES ('23', '121', '496', '5', 'Shield Reflect', '1');
INSERT INTO `list_skills` VALUES ('24', '121', '501', '4', 'battle alertniss', '1');
INSERT INTO `list_skills` VALUES ('25', '121', '506', '9', 'Staminal Training', '1');
INSERT INTO `list_skills` VALUES ('26', '121', '516', '9', 'Refreshment', '1');
INSERT INTO `list_skills` VALUES ('27', '121', '721', '5', 'Quick Step', '1');
INSERT INTO `list_skills` VALUES ('28', '121', '726', '5', 'Battle March', '1');
INSERT INTO `list_skills` VALUES ('29', '121', '731', '9', 'Sword Force', '1');
INSERT INTO `list_skills` VALUES ('30', '121', '5601', '1', 'Mileage-One-Handed Weapon Iron Blessing', '1');
INSERT INTO `list_skills` VALUES ('31', '121', '5602', '1', 'Mileage-One-Handed Weapon Wind Blessing', '1');
INSERT INTO `list_skills` VALUES ('32', '121', '4211', '4', 'Unique-Sacrifice', '1');
INSERT INTO `list_skills` VALUES ('33', '121', '426', '1', 'Immortal Form', '0');
INSERT INTO `list_skills` VALUES ('34', '122', '201', '9', 'Physical Training', '1');
INSERT INTO `list_skills` VALUES ('35', '122', '211', '9', 'Repose', '1');
INSERT INTO `list_skills` VALUES ('36', '122', '221', '9', 'Defense Training', '1');
INSERT INTO `list_skills` VALUES ('37', '122', '231', '5', 'Power Owerflow', '1');
INSERT INTO `list_skills` VALUES ('38', '122', '236', '5', 'howl', '1');
INSERT INTO `list_skills` VALUES ('39', '122', '241', '9', 'staminal assist', '1');
INSERT INTO `list_skills` VALUES ('40', '122', '251', '9', 'Melee Weapon Mastery', '1');
INSERT INTO `list_skills` VALUES ('41', '122', '261', '9', 'Melee Double Attack', '1');
INSERT INTO `list_skills` VALUES ('42', '122', '311', '4', 'soul wreck', '1');
INSERT INTO `list_skills` VALUES ('43', '122', '316', '9', 'Two-Handed Weapon Mastery', '1');
INSERT INTO `list_skills` VALUES ('44', '122', '326', '9', 'Two-Handed Sword Mastery', '1');
INSERT INTO `list_skills` VALUES ('45', '122', '336', '9', 'Piercing Lunge', '1');
INSERT INTO `list_skills` VALUES ('46', '122', '346', '4', 'Battle howl', '1');
INSERT INTO `list_skills` VALUES ('47', '122', '351', '4', 'Voltage Crash', '1');
INSERT INTO `list_skills` VALUES ('48', '122', '356', '9', 'Spear Mastery', '1');
INSERT INTO `list_skills` VALUES ('49', '122', '366', '9', 'Raging Spear Strike', '1');
INSERT INTO `list_skills` VALUES ('50', '122', '376', '4', 'battle scream', '1');
INSERT INTO `list_skills` VALUES ('51', '122', '381', '4', 'spear screw', '1');
INSERT INTO `list_skills` VALUES ('52', '122', '386', '9', 'Axe Mastery', '1');
INSERT INTO `list_skills` VALUES ('53', '122', '396', '9', 'Leaping Axe Strike', '1');
INSERT INTO `list_skills` VALUES ('54', '122', '406', '4', 'Battle cry', '1');
INSERT INTO `list_skills` VALUES ('55', '122', '411', '4', 'Axe Launcher', '1');
INSERT INTO `list_skills` VALUES ('56', '122', '416', '5', 'taunt', '1');
INSERT INTO `list_skills` VALUES ('57', '122', '421', '4', 'soundles vacuum', '1');
INSERT INTO `list_skills` VALUES ('58', '122', '501', '4', 'battle alertniss', '1');
INSERT INTO `list_skills` VALUES ('59', '122', '506', '9', 'Staminal Training', '1');
INSERT INTO `list_skills` VALUES ('60', '122', '516', '9', 'Refreshment', '1');
INSERT INTO `list_skills` VALUES ('61', '122', '531', '9', 'Melee Combat Mastery', '1');
INSERT INTO `list_skills` VALUES ('62', '122', '541', '9', 'Two-Handed Battle Mastery', '1');
INSERT INTO `list_skills` VALUES ('63', '122', '551', '9', 'Battle Sense Mastery', '1');
INSERT INTO `list_skills` VALUES ('64', '122', '561', '18', 'Advanced Two-Handed Sword Mastery', '1');
INSERT INTO `list_skills` VALUES ('65', '122', '581', '9', 'Geon Archangel Crumpler', '1');
INSERT INTO `list_skills` VALUES ('66', '122', '591', '4', 'combat howl', '1');
INSERT INTO `list_skills` VALUES ('67', '122', '596', '4', 'War howl', '1');
INSERT INTO `list_skills` VALUES ('68', '122', '601', '9', 'Seismic Impact', '1');
INSERT INTO `list_skills` VALUES ('69', '122', '611', '18', 'Advanced Spear Mastery', '1');
INSERT INTO `list_skills` VALUES ('70', '122', '631', '9', 'Longinus\'s Spear', '1');
INSERT INTO `list_skills` VALUES ('71', '122', '641', '4', 'combat scream', '1');
INSERT INTO `list_skills` VALUES ('72', '122', '646', '4', 'war scream', '1');
INSERT INTO `list_skills` VALUES ('73', '122', '651', '9', 'Achilles\'s Heel Strike', '1');
INSERT INTO `list_skills` VALUES ('74', '122', '661', '18', 'Advanced Axe Mastery', '1');
INSERT INTO `list_skills` VALUES ('75', '122', '681', '9', 'Vaulting Axe Smash', '1');
INSERT INTO `list_skills` VALUES ('76', '122', '691', '4', 'combat cry', '1');
INSERT INTO `list_skills` VALUES ('77', '122', '696', '4', 'war cry', '1');
INSERT INTO `list_skills` VALUES ('78', '122', '701', '9', 'Axe Slugger', '1');
INSERT INTO `list_skills` VALUES ('79', '122', '711', '5', 'motion sensing', '1');
INSERT INTO `list_skills` VALUES ('80', '122', '716', '5', 'beserk', '1');
INSERT INTO `list_skills` VALUES ('81', '122', '5603', '1', 'Mileage-Two-Handed Sword Iron Blessing', '1');
INSERT INTO `list_skills` VALUES ('82', '122', '5604', '1', 'Mileage-Two-Handed Sword Wind Blessing', '1');
INSERT INTO `list_skills` VALUES ('83', '122', '5605', '1', 'Mileage-Two-Handed Spear Iron Blessing', '1');
INSERT INTO `list_skills` VALUES ('84', '122', '5606', '1', 'Mileage-Two-Handed Spear Wind Blessing', '1');
INSERT INTO `list_skills` VALUES ('85', '122', '5607', '1', 'Mileage-Two-Handed Axe Iron Blessing', '1');
INSERT INTO `list_skills` VALUES ('86', '122', '5608', '1', 'Mileage-Two-Handed Axe Wind Blessing', '1');
INSERT INTO `list_skills` VALUES ('87', '122', '4211', '4', 'Unique-Sacrifice', '1');
INSERT INTO `list_skills` VALUES ('88', '122', '526', '1', 'Sword Master Form', '0');
INSERT INTO `list_skills` VALUES ('89', '221', '851', '9', 'Mana Bolt', '1');
INSERT INTO `list_skills` VALUES ('90', '221', '831', '18', 'Frostbiter', '1');
INSERT INTO `list_skills` VALUES ('91', '221', '891', '9', 'Spell Mastery', '1');
INSERT INTO `list_skills` VALUES ('92', '221', '861', '9', 'Mana Spear', '1');
INSERT INTO `list_skills` VALUES ('93', '221', '881', '4', 'Fire Ring', '1');
INSERT INTO `list_skills` VALUES ('94', '221', '871', '4', 'Voltage Jolt', '1');
INSERT INTO `list_skills` VALUES ('95', '221', '831', '9', 'Frostbiter', '1');
INSERT INTO `list_skills` VALUES ('96', '221', '821', '9', 'Ice Bolt', '1');
INSERT INTO `list_skills` VALUES ('97', '221', '841', '4', 'Wind Storm', '1');
INSERT INTO `list_skills` VALUES ('98', '221', '846', '4', 'Tornado', '1');
INSERT INTO `list_skills` VALUES ('99', '221', '876', '4', 'Icy Hailstorm', '1');
INSERT INTO `list_skills` VALUES ('100', '221', '886', '4', 'Meteorite Strike', '1');
INSERT INTO `list_skills` VALUES ('101', '221', '901', '9', 'Spirit Boost', '1');
INSERT INTO `list_skills` VALUES ('102', '221', '1046', '1', 'Sorceror Form', '1');
INSERT INTO `list_skills` VALUES ('103', '221', '1051', '18', 'Staff Combat Mastery', '1');
INSERT INTO `list_skills` VALUES ('104', '221', '1316', '9', 'Lucid Soul', '1');
INSERT INTO `list_skills` VALUES ('105', '221', '1136', '4', 'Mystic Eye', '1');
INSERT INTO `list_skills` VALUES ('106', '221', '1071', '9', 'Freezing Chill', '1');
INSERT INTO `list_skills` VALUES ('107', '221', '1101', '5', 'Soul Shock', '1');
INSERT INTO `list_skills` VALUES ('108', '221', '1121', '5', 'Hellfire', '1');
INSERT INTO `list_skills` VALUES ('109', '221', '1141', '9', 'Elemental Bolt', '1');
INSERT INTO `list_skills` VALUES ('110', '221', '1106', '5', 'Fierce Cudgeling', '1');
INSERT INTO `list_skills` VALUES ('111', '221', '1126', '5', 'Staff Stun', '1');
INSERT INTO `list_skills` VALUES ('112', '221', '1081', '4', 'Tempest', '1');
INSERT INTO `list_skills` VALUES ('113', '221', '1096', '5', 'Hurricane', '1');
INSERT INTO `list_skills` VALUES ('114', '221', '1151', '9', 'Aural Pierce', '1');
INSERT INTO `list_skills` VALUES ('115', '221', '1086', '9', 'Glaciating Chill', '1');
INSERT INTO `list_skills` VALUES ('116', '221', '1111', '5', 'Soul Electric', '1');
INSERT INTO `list_skills` VALUES ('117', '221', '1131', '5', 'Mana Burn', '1');
INSERT INTO `list_skills` VALUES ('118', '221', '1116', '5', 'Permafrost Chill', '1');
INSERT INTO `list_skills` VALUES ('119', '221', '1171', '5', 'Meteorite Flow', '1');
INSERT INTO `list_skills` VALUES ('120', '221', '1176', '5', 'Soul Doubt', '1');
INSERT INTO `list_skills` VALUES ('121', '221', '1161', '9', 'Elemental Spike', '1');
INSERT INTO `list_skills` VALUES ('122', '221', '801', '18', 'Staff Mastery', '1');
INSERT INTO `list_skills` VALUES ('123', '221', '911', '9', 'Meditation', '1');
INSERT INTO `list_skills` VALUES ('124', '221', '921', '5', 'Cure', '1');
INSERT INTO `list_skills` VALUES ('125', '221', '5702', '1', 'Mileage-Staff Iron Blessing', '1');
INSERT INTO `list_skills` VALUES ('126', '221', '5703', '1', 'Mileage-Staff Wind Blessing', '1');
INSERT INTO `list_skills` VALUES ('127', '221', '5701', '1', 'Mileage-Soul Restore', '1');
INSERT INTO `list_skills` VALUES ('128', '221', '4401', '3', 'Unique-Soul Recall', '1');
INSERT INTO `list_skills` VALUES ('129', '222', '931', '18', 'Wand Mastery', '1');
INSERT INTO `list_skills` VALUES ('130', '222', '911', '9', 'Meditation', '1');
INSERT INTO `list_skills` VALUES ('131', '222', '921', '5', 'Cure', '1');
INSERT INTO `list_skills` VALUES ('132', '222', '926', '5', 'Hustle Charm', '1');
INSERT INTO `list_skills` VALUES ('133', '222', '951', '9', 'Mana Drop', '1');
INSERT INTO `list_skills` VALUES ('134', '222', '986', '9', 'Wallop Charm', '1');
INSERT INTO `list_skills` VALUES ('135', '222', '1021', '9', 'Bonfire', '1');
INSERT INTO `list_skills` VALUES ('136', '222', '1031', '5', 'Party Heal', '1');
INSERT INTO `list_skills` VALUES ('137', '222', '976', '5', 'Soul Revive', '1');
INSERT INTO `list_skills` VALUES ('138', '222', '996', '9', 'Resilience Charm', '1');
INSERT INTO `list_skills` VALUES ('139', '222', '1006', '4', 'Purify', '1');
INSERT INTO `list_skills` VALUES ('140', '222', '1036', '4', 'Blessed Mind', '1');
INSERT INTO `list_skills` VALUES ('141', '222', '1041', '5', 'Integrity', '1');
INSERT INTO `list_skills` VALUES ('142', '222', '961', '9', 'Voltage Shock', '1');
INSERT INTO `list_skills` VALUES ('143', '222', '971', '5', 'Summon Phantom Sword', '1');
INSERT INTO `list_skills` VALUES ('144', '222', '981', '5', 'Recovery', '1');
INSERT INTO `list_skills` VALUES ('145', '222', '1011', '9', 'Precision Charm', '1');
INSERT INTO `list_skills` VALUES ('146', '222', '1181', '1', 'Untouchable Aura', '1');
INSERT INTO `list_skills` VALUES ('147', '222', '1186', '18', 'Magic Battle Mastery', '1');
INSERT INTO `list_skills` VALUES ('148', '222', '1296', '9', 'Dragon Skin', '1');
INSERT INTO `list_skills` VALUES ('149', '222', '1306', '9', 'Chant Focusing', '1');
INSERT INTO `list_skills` VALUES ('150', '222', '1241', '5', 'Heavenly Grace', '1');
INSERT INTO `list_skills` VALUES ('151', '222', '1211', '9', 'Mana Wave', '1');
INSERT INTO `list_skills` VALUES ('152', '222', '1206', '4', 'Summon Mastery', '1');
INSERT INTO `list_skills` VALUES ('153', '222', '1246', '9', 'Battle Charm', '1');
INSERT INTO `list_skills` VALUES ('154', '222', '1256', '3', 'Salamander Flame', '1');
INSERT INTO `list_skills` VALUES ('155', '222', '1266', '5', 'Clobber Charm', '1');
INSERT INTO `list_skills` VALUES ('156', '222', '1276', '9', 'Critical Charm', '1');
INSERT INTO `list_skills` VALUES ('157', '222', '1271', '5', 'Evasive Charm', '1');
INSERT INTO `list_skills` VALUES ('158', '222', '1226', '9', 'Voltage Storm', '1');
INSERT INTO `list_skills` VALUES ('159', '222', '1236', '5', 'Summon Firegon', '1');
INSERT INTO `list_skills` VALUES ('160', '222', '1261', '3', 'Mana Flame', '1');
INSERT INTO `list_skills` VALUES ('161', '222', '1176', '5', 'Soul Doubt', '1');
INSERT INTO `list_skills` VALUES ('162', '222', '1286', '9', 'Valkyrie Charm', '1');
INSERT INTO `list_skills` VALUES ('163', '222', '1221', '5', 'Summon Elemental', '1');
INSERT INTO `list_skills` VALUES ('164', '222', '6001', '18', 'Wand Contol - 198', '1');
INSERT INTO `list_skills` VALUES ('165', '222', '6021', '9', 'Mystic Shielding - 198', '1');
INSERT INTO `list_skills` VALUES ('166', '222', '6031', '18', 'Improved Wand Mastery - 198', '1');
INSERT INTO `list_skills` VALUES ('167', '222', '6051', '18', 'Wand Focusing - 198', '1');
INSERT INTO `list_skills` VALUES ('168', '222', '6071', '9', 'Mystic Armor - 198', '1');
INSERT INTO `list_skills` VALUES ('169', '222', '6081', '18', 'Wand Combat Mastery - 198', '1');
INSERT INTO `list_skills` VALUES ('170', '222', '5704', '1', 'Mileage-Wand Iron Blessing', '1');
INSERT INTO `list_skills` VALUES ('171', '222', '5705', '1', 'Mileage-Wand Wind Blessing', '1');
INSERT INTO `list_skills` VALUES ('172', '222', '5701', '1', 'Mileage-Soul Restore', '1');
INSERT INTO `list_skills` VALUES ('173', '222', '4401', '3', 'Unique-Soul Recall', '1');
INSERT INTO `list_skills` VALUES ('174', '321', '1401', '9', 'Combat Mastery', '1');
INSERT INTO `list_skills` VALUES ('175', '321', '1521', '18', 'Knuckle Mastery', '1');
INSERT INTO `list_skills` VALUES ('176', '321', '1541', '9', 'Double Slash', '1');
INSERT INTO `list_skills` VALUES ('177', '321', '1551', '9', 'Focused Impact', '1');
INSERT INTO `list_skills` VALUES ('178', '321', '1561', '9', 'pison knife', '1');
INSERT INTO `list_skills` VALUES ('179', '321', '1571', '9', 'triple slash', '1');
INSERT INTO `list_skills` VALUES ('180', '321', '1581', '9', 'katar upper', '1');
INSERT INTO `list_skills` VALUES ('181', '321', '1591', '9', 'dividing cleave', '1');
INSERT INTO `list_skills` VALUES ('182', '321', '1601', '5', 'venom knife', '1');
INSERT INTO `list_skills` VALUES ('183', '321', '1606', '9', 'Katar Mastery', '1');
INSERT INTO `list_skills` VALUES ('184', '321', '1616', '9', 'Dual Weapon Mastery', '1');
INSERT INTO `list_skills` VALUES ('185', '321', '1626', '4', 'stealth', '1');
INSERT INTO `list_skills` VALUES ('186', '321', '1631', '4', 'ferocity accordance', '1');
INSERT INTO `list_skills` VALUES ('187', '321', '1636', '4', 'weaken', '1');
INSERT INTO `list_skills` VALUES ('188', '321', '1641', '4', 'morror phantasim', '1');
INSERT INTO `list_skills` VALUES ('189', '321', '1646', '4', 'flame hawk', '1');
INSERT INTO `list_skills` VALUES ('190', '321', '1651', '4', 'spiral kick', '1');
INSERT INTO `list_skills` VALUES ('191', '321', '1776', '1', 'Assassin Form', '1');
INSERT INTO `list_skills` VALUES ('192', '321', '1781', '18', 'Combat Weapon Mastery', '1');
INSERT INTO `list_skills` VALUES ('193', '321', '1801', '9', 'Combo Slash', '1');
INSERT INTO `list_skills` VALUES ('194', '321', '1811', '4', 'mystic knife', '1');
INSERT INTO `list_skills` VALUES ('195', '321', '1946', '4', 'plasma falcon', '1');
INSERT INTO `list_skills` VALUES ('196', '321', '1816', '9', 'Crazy-Style Slash', '1');
INSERT INTO `list_skills` VALUES ('197', '321', '1826', '9', 'Quick-Style Assualt', '1');
INSERT INTO `list_skills` VALUES ('198', '321', '1951', '4', 'circle break', '1');
INSERT INTO `list_skills` VALUES ('199', '321', '1836', '4', 'screw slash', '1');
INSERT INTO `list_skills` VALUES ('200', '321', '1841', '9', 'Advanced Katar Mastery', '1');
INSERT INTO `list_skills` VALUES ('201', '321', '1851', '4', 'cloaking', '1');
INSERT INTO `list_skills` VALUES ('202', '321', '1856', '4', 'evasion guard', '1');
INSERT INTO `list_skills` VALUES ('203', '321', '1861', '9', 'Advanced Katar Mastery', '1');
INSERT INTO `list_skills` VALUES ('204', '321', '1871', '4', 'bloody assault', '1');
INSERT INTO `list_skills` VALUES ('205', '321', '1881', '4', 'critical accordance', '1');
INSERT INTO `list_skills` VALUES ('206', '321', '1886', '4', 'mental storm', '1');
INSERT INTO `list_skills` VALUES ('207', '321', '1891', '4', 'enfeeblement', '1');
INSERT INTO `list_skills` VALUES ('208', '321', '1896', '9', 'Phoenix Slash', '1');
INSERT INTO `list_skills` VALUES ('209', '321', '1906', '9', 'Flame Slash', '1');
INSERT INTO `list_skills` VALUES ('210', '321', '1916', '9', 'Freezing Assualt', '1');
INSERT INTO `list_skills` VALUES ('211', '321', '1926', '9', 'Precision Slash', '1');
INSERT INTO `list_skills` VALUES ('212', '321', '1936', '9', 'Precision Assualt', '1');
INSERT INTO `list_skills` VALUES ('213', '321', '1876', '4', 'vicious accordance', '1');
INSERT INTO `list_skills` VALUES ('214', '321', '1811', '4', 'Mystic Knife', '1');
INSERT INTO `list_skills` VALUES ('215', '321', '1506', '5', 'sprint', '1');
INSERT INTO `list_skills` VALUES ('216', '321', '1511', '5', 'velocity accordance', '1');
INSERT INTO `list_skills` VALUES ('217', '321', '1766', '5', 'rapid twitch', '1');
INSERT INTO `list_skills` VALUES ('218', '321', '1761', '5', 'hawker accordance', '1');
INSERT INTO `list_skills` VALUES ('219', '321', '1516', '4', 'secound sight', '1');
INSERT INTO `list_skills` VALUES ('220', '321', '1771', '4', 'requiem', '1');
INSERT INTO `list_skills` VALUES ('221', '321', '5803', '1', 'Mileage-Katar Iron Blessing', '1');
INSERT INTO `list_skills` VALUES ('222', '321', '5804', '1', 'Mileage-Katar Wind Blessing', '1');
INSERT INTO `list_skills` VALUES ('223', '321', '5805', '1', 'Mileage-Duel Wield Iron Blessing', '1');
INSERT INTO `list_skills` VALUES ('224', '321', '5806', '1', 'Mileage-Duel Wield Wind Blessing', '1');
INSERT INTO `list_skills` VALUES ('225', '322', '1401', '9', 'Combat Mastery', '1');
INSERT INTO `list_skills` VALUES ('226', '322', '1411', '18', 'Bow Mastery', '1');
INSERT INTO `list_skills` VALUES ('227', '322', '1431', '9', 'Clamp Arrow', '1');
INSERT INTO `list_skills` VALUES ('228', '322', '1441', '9', 'Double Arrow', '1');
INSERT INTO `list_skills` VALUES ('229', '322', '1451', '9', 'Backpack Proficiency', '1');
INSERT INTO `list_skills` VALUES ('230', '322', '1461', '9', 'Mana Profut', '1');
INSERT INTO `list_skills` VALUES ('231', '322', '1471', '5', 'offensive focus', '1');
INSERT INTO `list_skills` VALUES ('232', '322', '1496', '5', 'soul disciplin', '1');
INSERT INTO `list_skills` VALUES ('233', '322', '1476', '9', 'Shackle Arrow', '1');
INSERT INTO `list_skills` VALUES ('234', '322', '1486', '9', 'Triple Arrow', '1');
INSERT INTO `list_skills` VALUES ('235', '322', '1501', '4', 'stun arrow', '1');
INSERT INTO `list_skills` VALUES ('236', '322', '1656', '1', 'Flame Hawk', '1');
INSERT INTO `list_skills` VALUES ('237', '322', '1661', '18', 'Advanced Bow Mastery', '1');
INSERT INTO `list_skills` VALUES ('238', '322', '1681', '9', 'Call Hawk', '1');
INSERT INTO `list_skills` VALUES ('239', '322', '1691', '9', 'Trap Arrow', '1');
INSERT INTO `list_skills` VALUES ('240', '322', '1701', '9', 'Aimed Triple Arrow', '1');
INSERT INTO `list_skills` VALUES ('241', '322', '1711', '5', 'camoflage', '1');
INSERT INTO `list_skills` VALUES ('242', '322', '1716', '5', 'longinus`s Incoration', '1');
INSERT INTO `list_skills` VALUES ('243', '322', '1721', '9', 'mana flow', '1');
INSERT INTO `list_skills` VALUES ('244', '322', '1731', '5', 'point black arrow', '1');
INSERT INTO `list_skills` VALUES ('245', '322', '1736', '9', 'Entangling Arrow', '1');
INSERT INTO `list_skills` VALUES ('246', '322', '1746', '9', 'Phoenix Arrow', '1');
INSERT INTO `list_skills` VALUES ('247', '322', '1756', '5', 'soul gurrent', '1');
INSERT INTO `list_skills` VALUES ('248', '322', '1506', '5', 'sprint', '1');
INSERT INTO `list_skills` VALUES ('249', '322', '1766', '5', 'rapid twitch', '1');
INSERT INTO `list_skills` VALUES ('250', '322', '1511', '5', 'Velocity accourdance', '1');
INSERT INTO `list_skills` VALUES ('251', '322', '1761', '5', 'Hawker accordance', '1');
INSERT INTO `list_skills` VALUES ('252', '322', '1516', '4', 'secound sight', '1');
INSERT INTO `list_skills` VALUES ('253', '322', '1771', '4', 'requiem', '1');
INSERT INTO `list_skills` VALUES ('254', '322', '1956', '6', 'impact arrow', '1');
INSERT INTO `list_skills` VALUES ('255', '322', '5801', '1', 'Mileage-Bow Iron Blessing', '1');
INSERT INTO `list_skills` VALUES ('256', '322', '5802', '1', 'Mileage-Bow Wind Blessing', '1');
INSERT INTO `list_skills` VALUES ('257', '322', '4601', '9', 'Unique-Call Beast', '1');
INSERT INTO `list_skills` VALUES ('258', '421', '2001', '9', 'Trigger Finger', '1');
INSERT INTO `list_skills` VALUES ('259', '421', '2011', '18', 'Tough Gunner', '1');
INSERT INTO `list_skills` VALUES ('260', '421', '2036', '9', 'Twin Shot', '1');
INSERT INTO `list_skills` VALUES ('261', '421', '2031', '5', 'Intesify', '1');
INSERT INTO `list_skills` VALUES ('262', '421', '2056', '5', 'selsam gaint', '1');
INSERT INTO `list_skills` VALUES ('263', '421', '2046', '5', 'craftsman talent', '1');
INSERT INTO `list_skills` VALUES ('264', '421', '2051', '5', 'Discount', '1');
INSERT INTO `list_skills` VALUES ('265', '421', '2061', '9', 'Sniping', '1');
INSERT INTO `list_skills` VALUES ('266', '421', '2071', '5', 'master twin shot', '1');
INSERT INTO `list_skills` VALUES ('267', '421', '2076', '9', 'Demolition Expertise', '1');
INSERT INTO `list_skills` VALUES ('268', '421', '2086', '5', 'backpack mastery', '1');
INSERT INTO `list_skills` VALUES ('269', '421', '2091', '5', 'illusion', '1');
INSERT INTO `list_skills` VALUES ('270', '421', '2096', '4', 'mercenery employment', '1');
INSERT INTO `list_skills` VALUES ('271', '421', '2111', '5', 'weapon expertise', '1');
INSERT INTO `list_skills` VALUES ('272', '421', '2101', '5', 'employ warrior', '1');
INSERT INTO `list_skills` VALUES ('273', '421', '2106', '5', 'employ hunter', '1');
INSERT INTO `list_skills` VALUES ('274', '421', '2256', '9', 'Veteran Sniper', '1');
INSERT INTO `list_skills` VALUES ('275', '421', '2266', '18', 'Ace Gunner', '1');
INSERT INTO `list_skills` VALUES ('276', '421', '2286', '9', 'Merchandising', '1');
INSERT INTO `list_skills` VALUES ('277', '421', '2296', '1', 'Third Eye', '1');
INSERT INTO `list_skills` VALUES ('278', '421', '2301', '5', 'triple shot', '1');
INSERT INTO `list_skills` VALUES ('279', '421', '2316', '9', 'Zulie Bolt', '1');
INSERT INTO `list_skills` VALUES ('280', '421', '2306', '9', 'Venemous Shot', '1');
INSERT INTO `list_skills` VALUES ('281', '421', '2401', '5', 'master triple shot', '1');
INSERT INTO `list_skills` VALUES ('282', '421', '2326', '9', 'Shrapnel Burst', '1');
INSERT INTO `list_skills` VALUES ('283', '421', '2336', '9', 'Chaotic Burst', '1');
INSERT INTO `list_skills` VALUES ('284', '421', '2346', '5', 'windstep', '1');
INSERT INTO `list_skills` VALUES ('285', '421', '2356', '9', 'stockpile', '1');
INSERT INTO `list_skills` VALUES ('286', '421', '2366', '5', 'weapon agument', '1');
INSERT INTO `list_skills` VALUES ('287', '421', '2351', '5', 'light step', '1');
INSERT INTO `list_skills` VALUES ('288', '421', '2376', '5', 'summon dreag knight', '1');
INSERT INTO `list_skills` VALUES ('289', '421', '2371', '5', 'jury rigging', '1');
INSERT INTO `list_skills` VALUES ('290', '421', '2381', '9', 'Toxic Shot', '1');
INSERT INTO `list_skills` VALUES ('291', '421', '2391', '9', 'Zulie Stun', '1');
INSERT INTO `list_skills` VALUES ('292', '421', '2406', '9', 'Cannon Splash Burst', '1');
INSERT INTO `list_skills` VALUES ('293', '421', '2416', '9', 'Flame Stun Burst', '1');
INSERT INTO `list_skills` VALUES ('294', '421', '2426', '5', 'reflect aura', '1');
INSERT INTO `list_skills` VALUES ('295', '421', '2431', '5', 'dual layer', '1');
INSERT INTO `list_skills` VALUES ('296', '421', '5904', '1', 'Mileage-Launcher Iron Blessing', '1');
INSERT INTO `list_skills` VALUES ('297', '421', '5905', '1', 'Mileage-Launcher Wind Blessing', '1');
INSERT INTO `list_skills` VALUES ('298', '421', '2461', '5', 'Aimed Triple Shot', '1');
INSERT INTO `list_skills` VALUES ('299', '422', '2031', '5', 'Intensify Weapon', '1');
INSERT INTO `list_skills` VALUES ('300', '422', '2036', '9', 'Twin Shot', '1');
INSERT INTO `list_skills` VALUES ('301', '422', '2046', '5', 'Craftsman\'s Talent', '1');
INSERT INTO `list_skills` VALUES ('302', '422', '2051', '5', 'Discount', '1');
INSERT INTO `list_skills` VALUES ('303', '422', '2056', '5', 'Salesman Gait', '1');
INSERT INTO `list_skills` VALUES ('304', '422', '2086', '5', 'Backpack Mastery', '1');
INSERT INTO `list_skills` VALUES ('305', '422', '2301', '5', 'Triple Shot', '1');
INSERT INTO `list_skills` VALUES ('306', '422', '2461', '5', 'Aimed Triple Shot', '1');
INSERT INTO `list_skills` VALUES ('307', '422', '2116', '9', 'Weapon Research', '1');
INSERT INTO `list_skills` VALUES ('308', '422', '2126', '9', 'Armor Research', '1');
INSERT INTO `list_skills` VALUES ('309', '422', '2136', '9', 'SubItem Research', '1');
INSERT INTO `list_skills` VALUES ('310', '422', '2146', '9', 'Alchemy Research', '1');
INSERT INTO `list_skills` VALUES ('311', '422', '2156', '9', 'Weapon Craft', '1');
INSERT INTO `list_skills` VALUES ('312', '422', '2166', '1', 'Dark Blade Research', '1');
INSERT INTO `list_skills` VALUES ('313', '422', '2176', '1', 'Beam Blade Research', '1');
INSERT INTO `list_skills` VALUES ('314', '422', '2186', '1', 'Metal Blade Research', '1');
INSERT INTO `list_skills` VALUES ('315', '422', '2196', '1', 'Timber Blade Research', '1');
INSERT INTO `list_skills` VALUES ('316', '422', '2206', '9', 'Armor Craft', '1');
INSERT INTO `list_skills` VALUES ('317', '422', '2216', '1', 'Earth Blade Research', '1');
INSERT INTO `list_skills` VALUES ('318', '422', '2226', '1', 'Ocean Blade Research', '1');
INSERT INTO `list_skills` VALUES ('319', '422', '2236', '9', 'SubItem Craft', '1');
INSERT INTO `list_skills` VALUES ('320', '422', '2246', '9', 'Alchemy Craft', '1');
INSERT INTO `list_skills` VALUES ('321', '422', '2666', '9', 'Weapon Darkening', '1');
INSERT INTO `list_skills` VALUES ('322', '422', '2676', '9', 'Weapon Hardening', '1');
INSERT INTO `list_skills` VALUES ('323', '422', '2686', '9', 'Weapon Balancing', '1');
INSERT INTO `list_skills` VALUES ('324', '422', '2696', '9', 'Weapon Enchanting', '1');
INSERT INTO `list_skills` VALUES ('325', '422', '2706', '9', 'Armor Reinforcement', '1');
INSERT INTO `list_skills` VALUES ('326', '422', '2716', '9', 'Armor Endowment', '1');
INSERT INTO `list_skills` VALUES ('327', '422', '2441', '18', 'Top Gunner', '1');
INSERT INTO `list_skills` VALUES ('328', '422', '2466', '9', 'Poison Shot', '1');
INSERT INTO `list_skills` VALUES ('329', '422', '2476', '5', 'Hypno Shot', '1');
INSERT INTO `list_skills` VALUES ('330', '422', '2481', '5', 'Summon Terror Knight', '1');
INSERT INTO `list_skills` VALUES ('331', '422', '2486', '9', 'Advanced Weapon Research', '1');
INSERT INTO `list_skills` VALUES ('332', '422', '2496', '9', 'Advanced Armor Research', '1');
INSERT INTO `list_skills` VALUES ('333', '422', '2506', '9', 'Advanced Subitem Research', '1');
INSERT INTO `list_skills` VALUES ('334', '422', '2516', '9', 'Advanced Alchemy Research', '1');
INSERT INTO `list_skills` VALUES ('335', '422', '2526', '9', 'Advanced Weapon Craft', '1');
INSERT INTO `list_skills` VALUES ('336', '422', '2536', '1', 'Advanced Dark Blade Research', '1');
INSERT INTO `list_skills` VALUES ('337', '422', '2546', '1', 'Advanced Beam Blade Research', '1');
INSERT INTO `list_skills` VALUES ('338', '422', '2556', '1', 'Advanced Metal Blade Research', '1');
INSERT INTO `list_skills` VALUES ('339', '422', '2566', '1', 'Advanced Timber Blade Research', '1');
INSERT INTO `list_skills` VALUES ('340', '422', '2576', '9', 'Advanced Armor Craft', '1');
INSERT INTO `list_skills` VALUES ('341', '422', '2586', '1', 'Advanced Earth Blade Research', '1');
INSERT INTO `list_skills` VALUES ('342', '422', '2596', '1', 'Advanced Ocean Blade Research', '1');
INSERT INTO `list_skills` VALUES ('343', '422', '2606', '9', 'Advanced SubItem Craft', '1');
INSERT INTO `list_skills` VALUES ('344', '422', '2616', '9', 'Advanced Alchemy Craft', '1');
INSERT INTO `list_skills` VALUES ('345', '422', '2626', '9', 'PAT Research', '1');
INSERT INTO `list_skills` VALUES ('346', '422', '2636', '9', 'PAT Craft', '1');
INSERT INTO `list_skills` VALUES ('347', '422', '2646', '9', 'Gem Cutting Research', '1');
INSERT INTO `list_skills` VALUES ('348', '422', '2656', '9', 'Gem Cutting', '1');
INSERT INTO `list_skills` VALUES ('349', '422', '2726', '9', 'Advanced Weapon Darkening', '1');
INSERT INTO `list_skills` VALUES ('350', '422', '2736', '9', 'Advanced Weapon Hardening', '1');
INSERT INTO `list_skills` VALUES ('351', '422', '2746', '9', 'Advanced Weapon Balancing', '1');
INSERT INTO `list_skills` VALUES ('352', '422', '2756', '9', 'Advanced Weapon Enchanting', '1');
INSERT INTO `list_skills` VALUES ('353', '422', '2766', '9', 'Advanced Armor Reinforcement', '1');
INSERT INTO `list_skills` VALUES ('354', '422', '2776', '9', 'Advanced Armor Endowment', '1');
INSERT INTO `list_skills` VALUES ('355', '422', '5902', '1', 'Mileage-Gun Iron Blessing', '1');
INSERT INTO `list_skills` VALUES ('356', '422', '5903', '1', 'Mileage-Gun Wind Blessing', '1');
INSERT INTO `list_skills` VALUES ('357', '422', '4801', '9', 'Unique-Face Item Craft', '1');
INSERT INTO `list_skills` VALUES ('358', '422', '4811', '9', 'Accessory Craft', '1');
INSERT INTO `list_skills` VALUES ('359', '2', '3201', '1', 'GM-Healing All', '1');
INSERT INTO `list_skills` VALUES ('360', '2', '3202', '1', 'GM-ATK & Accuracy Up', '1');
INSERT INTO `list_skills` VALUES ('361', '2', '3203', '1', 'GM-DEF & M-DEF Up', '1');
INSERT INTO `list_skills` VALUES ('362', '2', '3204', '1', 'GM-A-SPD & CRI Up', '1');
INSERT INTO `list_skills` VALUES ('363', '2', '3205', '1', 'GM-M-SPD & Dodge Up', '1');
INSERT INTO `list_skills` VALUES ('364', '2', '3210', '1', 'GM-Purify All', '1');
INSERT INTO `list_skills` VALUES ('365', '2', '3211', '1', 'GM-Invincibility (Self)', '1');
INSERT INTO `list_skills` VALUES ('366', '2', '3212', '1', 'GM-Power Up (Self)', '1');
INSERT INTO `list_skills` VALUES ('367', '2', '3213', '1', 'GM-Speed Up (Self)', '1');
INSERT INTO `list_skills` VALUES ('368', '2', '3214', '1', 'GM-Invisibility (Self)', '1');
INSERT INTO `list_skills` VALUES ('369', '2', '3215', '1', 'GM-Healing (Self)', '1');
INSERT INTO `list_skills` VALUES ('370', '2', '3216', '1', 'GM-Kill (Anti-Crime)', '1');
INSERT INTO `list_skills` VALUES ('371', '2', '3217', '1', 'GM-Stun (600\")', '1');
INSERT INTO `list_skills` VALUES ('372', '2', '3218', '1', 'GM-Mute (600\")', '1');
INSERT INTO `list_skills` VALUES ('373', '2', '3219', '1', 'GM-Purify', '1');
INSERT INTO `list_skills` VALUES ('374', '1', '3220', '1', 'GM Passiv Skill', '0');
INSERT INTO `list_skills` VALUES ('375', '1', '3221', '1', 'DEV Passiv Sill', '0');
INSERT INTO `list_skills` VALUES ('376', '1', '3225', '1', '', '0');
INSERT INTO `list_skills` VALUES ('377', '1', '3226', '1', '', '0');
INSERT INTO `list_skills` VALUES ('378', '1', '3227', '1', '', '0');
INSERT INTO `list_skills` VALUES ('379', '0', '5505', '1', 'Mileage-ALL-Swift Blessing', '1');
INSERT INTO `list_skills` VALUES ('380', '0', '5506', '1', 'Mileage-ALL-Nimble Blessing', '1');
INSERT INTO `list_skills` VALUES ('381', '0', '2850', '1', 'Mileage-Weight Training Light', '1');
INSERT INTO `list_skills` VALUES ('382', '0', '2851', '1', 'Mileage-Weight Training Medium', '1');
INSERT INTO `list_skills` VALUES ('383', '0', '2852', '1', 'Mileage-Weight Training Heavy', '1');
INSERT INTO `list_skills` VALUES ('384', '0', '2853', '1', 'Mileage-Weight Training Advanced', '1');
INSERT INTO `list_skills` VALUES ('385', '0', '5000', '1', 'Drive Cart', '1');
INSERT INTO `list_skills` VALUES ('386', '0', '5001', '1', 'Drive Castle Gear', '1');
INSERT INTO `list_skills` VALUES ('387', '0', '5500', '1', 'Mileage-Union Reward Bonus', '1');
INSERT INTO `list_skills` VALUES ('388', '0', '2839', '1', 'Metal Moldie - Pre-F2P Unique Skill', '1');
INSERT INTO `list_skills` VALUES ('389', '1', '5501', '1', 'Mana Corrosion - all', '0');
INSERT INTO `list_skills` VALUES ('390', '1', '5502', '1', 'Dispel - all', '0');
INSERT INTO `list_skills` VALUES ('391', '1', '5901', '1', 'Virtuoso Crafting - (can learn, but not showing)', '0');
INSERT INTO `list_skills` VALUES ('392', '1', '4001', '1', 'ManaBrake - all', '0');
INSERT INTO `list_skills` VALUES ('393', '1', '4002', '1', 'Anti Magic Shell - all', '0');
INSERT INTO `list_skills` VALUES ('394', '1', '0', '', '  563 - all', '0');
INSERT INTO `list_skills` VALUES ('395', '1', '4406', '', 'Mana Shield - all - 4407, 4408', '0');
INSERT INTO `list_skills` VALUES ('396', '1', '4821', '', 'Expert Crafting - dealer - 4822, 4823', '0');
INSERT INTO `list_skills` VALUES ('397', '1', '4201', '', 'Adamantine Fist-', '0');
INSERT INTO `list_skills` VALUES ('398', '0', '2844', '1', 'Mileage-Summon Leprechaun', '1');
INSERT INTO `list_skills` VALUES ('399', '0', '2839', '1', 'Metal Moldie (Pre-F2P Unique Skill)', '1');
INSERT INTO `list_skills` VALUES ('400', '0', '2854', '1', 'Mileage-Weight Training Mastery', '1');
INSERT INTO `list_skills` VALUES ('401', '0', '50', '1', 'Pat Painting', '1');
INSERT INTO `list_skills` VALUES ('402', '221', '6100', '5', 'Restoration', '1');
INSERT INTO `list_skills` VALUES ('403', '222', '6100', '5', 'Restoration', '1');
INSERT INTO `list_skills` VALUES ('404', '0', '2880', '1', 'Unique-Arua\'s Fate', '1');
INSERT INTO `list_skills` VALUES ('405', '0', '2881', '1', 'Unique-Hebarn\'s Fate', '1');
