/*
MySQL Data Transfer
Source Host: osrose
Source Database: osrose
Target Host: osrose
Target Database: osrose
Date: 5/10/2008 4:15:54 PM
*/

SET FOREIGN_KEY_CHECKS=0;
-- ----------------------------
-- Table structure for chest_data
-- ----------------------------
CREATE TABLE `chest_data` (
  `id` int(11) NOT NULL auto_increment,
  `chestid` int(11) NOT NULL,
  `reward` varchar(255) NOT NULL,
  `rewardtype` varchar(255) NOT NULL,
  `prob` varchar(255) NOT NULL,
  `maxamount` varchar(255) NOT NULL,
  `maxpossible` int(11) NOT NULL,
  `numberofrewards` int(11) NOT NULL,
  `Description` varchar(255) NOT NULL,
  PRIMARY KEY  (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=2403 DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records 
-- ----------------------------
INSERT INTO `chest_data` VALUES ('1', '70', '153|153|153|142|147|146|149|150', '2|3|5|10|10|10|10|10', '800|800|800|900|900|900|900|900', '1|1|1|1|1|1|1|1', '1', '8', 'Small Gift Box - 2006');
INSERT INTO `chest_data` VALUES ('2', '71', '153|153|153|142|147|146|149|150', '2|3|5|10|10|10|10|10', '800|800|800|900|900|900|900|900', '1|1|1|1|1|1|1|1', '1', '8', 'Surprise Gift Box - 2006');
INSERT INTO `chest_data` VALUES ('3', '72', '153|153|153|142|147|146|149|150', '2|3|5|10|10|10|10|10', '800|800|800|900|900|900|900|900', '1|1|1|1|1|1|1|1', '1', '8', 'Impressive Gift Box - 2006');
INSERT INTO `chest_data` VALUES ('11', '905', '13', '10', '500', '1', '1', '1', 'Small Gift Box ?');
INSERT INTO `chest_data` VALUES ('12', '906', '13', '10', '500', '1', '1', '1', 'Surprise Gift Box ?');
INSERT INTO `chest_data` VALUES ('13', '907', '13', '10', '500', '1', '1', '1', 'Impressive Gift Box ?');
INSERT INTO `chest_data` VALUES ('1801', '75', '146|147|153|153|153|987|988|898', '10|10|2|3|5|10|10|10', '65000|20000|4000|3000|3000|2000|2000|1000', '5|5|1|1|1|3|3|1', '1', '8', 'Event: Gift Box (S)');
INSERT INTO `chest_data` VALUES ('1802', '76', '146|147|153|153|153|987|988|898', '10|10|2|3|5|10|10|10', '65000|20000|4000|3000|3000|2000|2000|1000', '5|5|1|1|1|3|3|1', '2', '8', 'Event: Gift Box (M)');
INSERT INTO `chest_data` VALUES ('1803', '77', '011|030|280|005|102|202|006|103|203', '10|10|10|14|14|14|14|14|14', '60000|25000|3000|2000|2000|2000|2000|2000|2000', '20|20|1|1|1|1|1|1|1', '1', '9', 'Event: GM Event Gift Box ');
INSERT INTO `chest_data` VALUES ('1804', '78', '149|150|994', '10|10|10', '70000|20000|10000', '5|5|5', '1', '3', 'Event: Gift Box ');
INSERT INTO `chest_data` VALUES ('1805', '946', '416|143', '12|10', '80000|20000', '5|1', '1', '2', 'Event: Christmas Event Gift Box ');
INSERT INTO `chest_data` VALUES ('1901', '997', '763|153|333|313|303|284|037|170|035|360|361|405|944|155|963', '6|3|11|11|11|10|9|3|9|10|10|14|10|3|10', '1000|1000|3000|3000|3000|7000|8000|8000|8000|7000|7000|10000|10000|12000|12000', '1|1|1|1|1|1|1|1|1|1|1|1|1|1|1', '1', '15', 'Title Line: ROSE Treasure Chest (S)');
INSERT INTO `chest_data` VALUES ('1902', '998', '283|202|363|353|373|191|467|153|983|984|942|169|157|171|961', '10|10|11|11|11|3|8|5|10|10|10|3|3|3|10', '1000|1000|3000|3000|3000|3000|4000|9000|9000|10000|10000|10000|11000|11000|12000', '1|1|1|1|1|1|1|1|1|1|1|1|1|1|1', '1', '15', 'NA: ROSE Treasure Chest (M)');
INSERT INTO `chest_data` VALUES ('1903', '999', '771|838|161|406|202|334|425|192|464|283|962|363|985|173|594', '6|2|3|14|10|11|14|3|8|10|10|10|10|3|10', '1000|2000|2000|3000|3000|3000|5000|6000|7000|7000|11000|12000|12000|13000|13000', '1|1|1|1|1|1|1|1|1|1|1|1|1|1|1', '1', '15', 'NA: ROSE Treasure Chest (L)');
INSERT INTO `chest_data` VALUES ('1904', '1000', '407|202|323|353|373|191|467|153|153|984|942|169|157|171|961', '14|10|11|11|11|3|8|5|2|10|10|3|3|3|10', '1000|1000|3000|3000|3000|3000|4000|9000|9000|10000|10000|10000|11000|11000|12000', '1|1|1|1|1|1|1|1|1|1|1|1|1|1|1', '1', '15', 'NA: ROSE Treasure Chest (XL)');
INSERT INTO `chest_data` VALUES ('1905', '996', '763|167|333|313|363|284|944|035|157|156|187|405|364|940|963', '6|1|11|11|11|10|10|9|2|3|4|14|10|10|10', '1000|1000|2000|3000|4000|7000|8000|8000|8000|7000|7000|10000|10000|12000|12000', '1|1|1|1|1|1|1|1|1|1|1|1|1|1|1', '1', '15', 'NA: ROSE Treasure Chest (S: 1.5)');
INSERT INTO `chest_data` VALUES ('1958', '1160', '001', '10', '100000', '10', '1', '1', 'Health Vial (S) Dispenser: Health Vial (S) Dispenser');
INSERT INTO `chest_data` VALUES ('1959', '1161', '002', '10', '100000', '10', '1', '1', 'Health Vial (M) Dispenser: Health Vial (M) Dispenser');
INSERT INTO `chest_data` VALUES ('1960', '1162', '003', '10', '100000', '10', '1', '1', 'Health Vial (L) Dispenser: Health Vial (L) Dispenser');
INSERT INTO `chest_data` VALUES ('1961', '1163', '004', '10', '100000', '10', '1', '1', 'Health Bottle (S) Dispenser: Health Bottle (S) Dispenser');
INSERT INTO `chest_data` VALUES ('1962', '1164', '005', '10', '100000', '10', '1', '1', 'Health Bottle (M) Dispenser: Health Bottle (M) Dispenser');
INSERT INTO `chest_data` VALUES ('1963', '1165', '006', '10', '100000', '10', '1', '1', 'Health Bottle (L) Dispenser: Health Bottle (L) Dispenser');
INSERT INTO `chest_data` VALUES ('1964', '1166', '010', '10', '100000', '10', '1', '1', 'Vital Water (S) Dispenser: Vital Water (S) Dispenser');
INSERT INTO `chest_data` VALUES ('1965', '1167', '011', '10', '100000', '10', '1', '1', 'Vital Water (M) Dispenser: Vital Water (M) Dispenser');
INSERT INTO `chest_data` VALUES ('1966', '1168', '012', '10', '100000', '10', '1', '1', 'Vital Water (L) Dispenser: Vital Water (L) Dispenser');
INSERT INTO `chest_data` VALUES ('1968', '1170', '021', '10', '100000', '10', '1', '1', 'Mana Vial (S) Dispenser: Mana Vial (S) Dispenser');
INSERT INTO `chest_data` VALUES ('1969', '1171', '022', '10', '100000', '10', '1', '1', 'Mana Vial (M) Dispenser: Mana Vial (M) Dispenser');
INSERT INTO `chest_data` VALUES ('1970', '1172', '023', '10', '100000', '10', '1', '1', 'Mana Vial (L) Dispenser: Mana Vial (L) Dispenser');
INSERT INTO `chest_data` VALUES ('1971', '1173', '024', '10', '100000', '10', '1', '1', 'Mana Bottle (S) Dispenser: Mana Bottle (S) Dispenser');
INSERT INTO `chest_data` VALUES ('1972', '1174', '025', '10', '100000', '10', '1', '1', 'Mana Bottle (M) Dispenser: Mana Bottle (M) Dispenser');
INSERT INTO `chest_data` VALUES ('1973', '1175', '026', '10', '100000', '10', '1', '1', 'Mana Bottle (L) Dispenser: Mana Bottle (L) Dispenser');
INSERT INTO `chest_data` VALUES ('1974', '1176', '029', '10', '100000', '10', '1', '1', 'Spiritual Water (S) Dispenser: Spiritual Water (S) Dispenser');
INSERT INTO `chest_data` VALUES ('1975', '1177', '030', '10', '100000', '10', '1', '1', 'Spiritual Water (M) Dispenser: Spiritual Water (M) Dispenser');
INSERT INTO `chest_data` VALUES ('1976', '1178', '031', '10', '100000', '10', '1', '1', 'Spiritual Water (L) Dispenser: Spiritual Water (L) Dispenser');
INSERT INTO `chest_data` VALUES ('2001', '1001', '132|133|087|077|103|133|051|183|680|073|553', '12|12|12|12|2|2|8|8|5|3|8', '78895|20000|204|51|234|234|137|137|35|35|38', '5|3|1|1|1|1|1|1|1|1|1', '1', '11', 'Sikuku Prison Treasure Chests: Wooden Treasure Chest A');
INSERT INTO `chest_data` VALUES ('2002', '1002', '132|133|087|077|043|073|686|321|581|781|865', '12|12|12|12|3|3|8|8|4|2|8', '78795|20000|204|51|256|256|154|154|47|47|36', '5|3|1|1|1|1|1|1|1|1|1', '1', '11', 'Sikuku Prison Treasure Chests: Wooden Treasure Chest B');
INSERT INTO `chest_data` VALUES ('2003', '1003', '132|133|087|077|103|133|349|250|581|381|718', '12|12|12|12|3|3|8|8|5|4|8', '78795|20000|204|51|256|256|154|154|44|44|42', '5|3|1|1|1|1|1|1|1|1|1', '1', '11', 'Sikuku Prison Treasure Chests: Wooden Treasure Chest C');
INSERT INTO `chest_data` VALUES ('2004', '1004', '132|133|087|077|043|073|022|420|581|043|221', '12|12|12|12|4|4|8|8|3|3|8', '78695|20000|204|51|281|281|174|174|49|49|42', '5|3|1|1|1|1|1|1|1|1|1', '1', '11', 'Sikuku Prison Treasure Chests: Wooden Treasure Chest D');
INSERT INTO `chest_data` VALUES ('2005', '1005', '132|133|087|077|103|133|278|120|681|043|595', '12|12|12|12|4|4|8|8|2|5|8', '78695|20000|204|51|280|280|173|173|51|51|42', '5|3|1|1|1|1|1|1|1|1|1', '1', '11', 'Sikuku Prison Treasure Chests: Wooden Treasure Chest E');
INSERT INTO `chest_data` VALUES ('2006', '1006', '132|133|087|077|043|073|183|448|681|073|844', '12|12|12|12|5|5|8|8|5|3|8', '78595|20000|204|51|305|305|193|193|53|53|48', '5|3|1|1|1|1|1|1|1|1|1', '1', '11', 'Sikuku Prison Treasure Chests: Wooden Treasure Chest F');
INSERT INTO `chest_data` VALUES ('2007', '1007', '132|133|087|077|103|133|662|686|073|580|524', '12|12|12|12|5|5|8|8|5|2|8', '78595|20000|204|51|305|305|193|193|53|53|48', '5|3|1|1|1|1|1|1|1|1|1', '1', '11', 'Sikuku Prison Treasure Chests: Wooden Treasure Chest G');
INSERT INTO `chest_data` VALUES ('2008', '1008', '132|133|087|077|043|073|321|349|581|781|718', '12|12|12|12|2|2|8|8|4|2|8', '78495|20000|204|51|329|329|212|212|57|57|54', '5|3|1|1|1|1|1|1|1|1|1', '1', '11', 'Sikuku Prison Treasure Chests: Wooden Treasure Chest H');
INSERT INTO `chest_data` VALUES ('2009', '1009', '132|133|087|077|103|133|250|022|581|380|628', '12|12|12|12|2|2|8|8|5|4|8', '78495|20000|204|51|334|334|217|217|47|47|54', '5|3|1|1|1|1|1|1|1|1|1', '1', '11', 'Sikuku Prison Treasure Chests: Wooden Treasure Chest I');
INSERT INTO `chest_data` VALUES ('2010', '1010', '132|133|087|077|043|073|420|278|581|380|596', '12|12|12|12|3|3|8|8|3|3|8', '78395|20000|204|51|354|354|232|232|62|62|54', '5|3|1|1|1|1|1|1|1|1|1', '1', '11', 'Sikuku Prison Treasure Chests: Wooden Treasure Chest J');
INSERT INTO `chest_data` VALUES ('2011', '1011', '132|133|087|077|103|133|120|221|681|480|151', '12|12|12|12|3|3|8|8|4|2|8', '78395|20000|204|51|353|353|231|231|64|64|54', '5|3|1|1|1|1|1|1|1|1|1', '1', '11', 'Sikuku Prison Treasure Chests: Wooden Treasure Chest K');
INSERT INTO `chest_data` VALUES ('2012', '1012', '132|133|087|077|043|073|448|662|680|073|844', '12|12|12|12|4|4|8|8|5|3|8', '78295|20000|204|51|378|378|251|251|66|66|60', '5|3|1|1|1|1|1|1|1|1|1', '1', '11', 'Sikuku Prison Treasure Chests: Wooden Treasure Chest L');
INSERT INTO `chest_data` VALUES ('2013', '1013', '132|133|087|077|043|073|448|662|480|580|783', '12|12|12|12|4|4|8|8|5|2|8', '78295|20000|204|51|378|378|251|251|66|66|60', '5|3|1|1|1|1|1|1|1|1|1', '1', '11', 'Sikuku Prison Treasure Chests: Wooden Treasure Chest M');
INSERT INTO `chest_data` VALUES ('2014', '1014', '087|077|103|043|103|043|022|051|596|120|480|524', '12|12|2|3|3|4|8|8|8|8|2|8', '15000|5000|10000|10000|10000|10000|8000|8000|8000|8000|6000|2000', '1|1|1|1|1|1|1|1|1|1|1|1', '2', '12', 'Sikuku Prison Treasure Chests: Silver Treasure Chest A');
INSERT INTO `chest_data` VALUES ('2015', '1015', '087|077|103|043|103|043|448|183|662|686|580|553', '12|12|4|5|5|2|8|8|8|8|2|8', '15000|5000|10000|10000|10000|10000|8000|8000|8000|8000|6000|2000', '1|1|1|1|1|1|1|1|1|1|1|1', '2', '12', 'Sikuku Prison Treasure Chests: Silver Treasure Chest B');
INSERT INTO `chest_data` VALUES ('2016', '1016', '087|077|133|073|133|073|250|278|321|349|781|718', '12|12|2|3|3|4|8|8|8|8|2|8', '15000|5000|10000|10000|10000|10000|8000|8000|8000|8000|6000|2000', '1|1|1|1|1|1|1|1|1|1|1|1', '2', '12', 'Sikuku Prison Treasure Chests: Silver Treasure Chest C');
INSERT INTO `chest_data` VALUES ('2017', '1017', '087|077|133|073|133|073|420|120|250|321|380|595', '12|12|4|5|5|2|8|8|8|8|3|8', '15000|5000|10000|10000|10000|10000|8000|8000|8000|8000|6000|2000', '1|1|1|1|1|1|1|1|1|1|1|1', '2', '12', 'Sikuku Prison Treasure Chests: Silver Treasure Chest D');
INSERT INTO `chest_data` VALUES ('2018', '1018', '087|077|103|043|103|043|022|051|865|120|480|596', '12|12|2|3|3|4|8|8|8|8|3|8', '15000|5000|10000|10000|10000|10000|8000|8000|8000|8000|6000|2000', '1|1|1|1|1|1|1|1|1|1|1|1', '2', '12', 'Sikuku Prison Treasure Chests: Silver Treasure Chest E');
INSERT INTO `chest_data` VALUES ('2019', '1019', '087|077|580|043|580|043|448|183|662|686|380|865', '12|12|4|5|5|2|8|8|8|8|4|8', '15000|5000|10000|10000|10000|10000|8000|8000|8000|8000|6000|2000', '1|1|1|1|1|1|1|1|1|1|1|1', '2', '12', 'Sikuku Prison Treasure Chests: Silver Treasure Chest F');
INSERT INTO `chest_data` VALUES ('2020', '1020', '087|077|780|073|681|480|250|278|321|349|380|151', '12|12|2|3|3|4|8|8|8|8|5|8', '15000|5000|10000|10000|10000|10000|8000|8000|8000|8000|6000|2000', '1|1|1|1|1|1|1|1|1|1|1|1', '2', '12', 'Sikuku Prison Treasure Chests: Silver Treasure Chest G');
INSERT INTO `chest_data` VALUES ('2021', '1021', '087|077|133|380|133|073|420|120|250|321|481|628', '12|12|4|5|5|2|8|8|8|8|2|8', '15000|5000|10000|10000|10000|10000|8000|8000|8000|8000|6000|2000', '1|1|1|1|1|1|1|1|1|1|1|1', '2', '12', 'Sikuku Prison Treasure Chests: Silver Treasure Chest H');
INSERT INTO `chest_data` VALUES ('2022', '1022', '087|077|680|043|580|043|022|051|524|120|581|221', '12|12|2|3|3|4|8|8|8|8|2|8', '15000|5000|10000|10000|10000|10000|8000|8000|8000|8000|6000|2000', '1|1|1|1|1|1|1|1|1|1|1|1', '2', '12', 'Sikuku Prison Treasure Chests: Silver Treasure Chest I');
INSERT INTO `chest_data` VALUES ('2023', '1023', '087|077|580|381|103|043|448|183|662|686|780|745', '12|12|4|5|5|2|8|8|8|8|2|8', '15000|5000|10000|10000|10000|10000|8000|8000|8000|8000|6000|2000', '1|1|1|1|1|1|1|1|1|1|1|1', '2', '12', 'Sikuku Prison Treasure Chests: Silver Treasure Chest J');
INSERT INTO `chest_data` VALUES ('2024', '1024', '087|077|133|073|680|481|250|278|321|349|043|783', '12|12|2|3|3|4|8|8|8|8|3|8', '15000|5000|10000|10000|10000|10000|8000|8000|8000|8000|6000|2000', '1|1|1|1|1|1|1|1|1|1|1|1', '2', '12', 'Sikuku Prison Treasure Chests: Silver Treasure Chest K');
INSERT INTO `chest_data` VALUES ('2025', '1025', '087|077|680|380|133|073|420|120|250|321|480|806', '12|12|4|5|5|2|8|8|8|8|3|8', '15000|5000|10000|10000|10000|10000|8000|8000|8000|8000|6000|2000', '1|1|1|1|1|1|1|1|1|1|1|1', '2', '12', 'Sikuku Prison Treasure Chests: Silver Treasure Chest L');
INSERT INTO `chest_data` VALUES ('2026', '1026', '087|077|681|043|580|043|022|051|844|120|043|844', '12|12|2|3|3|4|8|8|8|8|3|8', '15000|5000|10000|10000|10000|10000|8000|8000|8000|8000|6000|2000', '1|1|1|1|1|1|1|1|1|1|1|1', '2', '12', 'Sikuku Prison Treasure Chests: Silver Treasure Chest M');
INSERT INTO `chest_data` VALUES ('2027', '1027', '481|581|781|381|524|553|783|595|596|865', '2|2|2|3|8|8|8|8|8|8', '10000|10000|10000|10000|10000|10000|10000|10000|10000|10000', '1|1|1|1|1|1|1|1|1|1', '2', '10', 'Sikuku Prison Treasure Chests: Gold Treasure Chest A');
INSERT INTO `chest_data` VALUES ('2028', '1028', '481|381|381|151|628|221|718|783|844|806', '3|4|5|8|8|8|8|8|8|8', '10000|10000|10000|10000|10000|10000|10000|10000|10000|10000', '1|1|1|1|1|1|1|1|1|1', '2', '10', 'Sikuku Prison Treasure Chests: Gold Treasure Chest B');
INSERT INTO `chest_data` VALUES ('2050', '270', '361|362|363|364|365|366|367|368|369|370', '12|12|12|12|12|12|12|12|12|12', '10000|10000|10000|10000|10000|10000|10000|10000|10000|10000', '1|1|1|1|1|1|1|1|1|1', '1', '10', 'Dirty Zodiac Stone: Dirty Zodiac Stone');
INSERT INTO `chest_data` VALUES ('2051', '271', '381|382|383|384|385|386|387|388|389|390', '12|12|12|12|12|12|12|12|12|12', '10000|10000|10000|10000|10000|10000|10000|10000|10000|10000', '1|1|1|1|1|1|1|1|1|1', '1', '10', 'Dirty Rune Stone: Dirty Rune Stone');
INSERT INTO `chest_data` VALUES ('2052', '272', '291|292|293|294', '12|12|12|12', '25000|25000|25000|25000', '1|1|1|1', '1', '4', 'Dirty Ore: Dirty Ore');
INSERT INTO `chest_data` VALUES ('2053', '273', '121|122|123|124|125', '12|12|12|12|12', '20000|20000|20000|20000|20000', '1|1|1|1|1', '1', '5', 'Dirty Stone: Dirty Stone');
INSERT INTO `chest_data` VALUES ('2054', '274', '161|162|163|164', '12|12|12|12', '25000|25000|25000|25000', '2|2|2|2', '1', '4', 'Dirty Crystal: Dirty Crystal');
INSERT INTO `chest_data` VALUES ('2055', '275', '295|296|297|298|299', '12|12|12|12|12', '24875|24875|24875|24875|500', '1|1|1|1|1', '1', '5', 'Dirty Spiritual Stone: Dirty Spiritual Stone');
INSERT INTO `chest_data` VALUES ('2056', '276', '151|152|153|154|155|156|157', '12|12|12|12|12|12|12', '14286|14286|14286|14286|14286|14285|14285', '1|1|1|1|1|1|1', '1', '7', 'Dirty Heart Stone: Dirty Heart Stone');
INSERT INTO `chest_data` VALUES ('2380', '1080', '918|918|918|919|919|168|281', '10|10|10|10|10|1|6', '35000|10000|5000|30000|10000|5000|5000', '1|2|5|2|5|1|1', '1', '7', '2008 Valentines Box: Valentines Box');
INSERT INTO `chest_data` VALUES ('2381', '1081', '178|175|175|178|169', '3|4|2|5|1', '20000|20000|20000|20000|20000', '1|1|1|1|1', '1', '5', '2008 St. Patricks Day Box: Leprechauns Box');
INSERT INTO `chest_data` VALUES ('2382', '1082', '203|816|817|818|819|039|145|250|251|107|940|941', '2|2|2|2|2|9|10|10|10|10|10|10', '2500|2500|2500|2500|2500|2500|5500|25000|25000|9000|9000|9000', '1|1|1|1|1|1|3|5|5|5|2|2', '1', '12', '2008 Easter Egg: 2008 Easter Egg');
INSERT INTO `chest_data` VALUES ('2400', '247', '326|913|240|241|243|245|242|244|246|496', '10|10|10|10|10|10|10|10|10|10', '13000|12000|12000|10000|10000|10000|10000|10000|8000|5000', '5|5|3|3|3|3|3|3|3|1', '2', '10', '2007 Christmas Event: Small Christmas Present');
INSERT INTO `chest_data` VALUES ('2401', '248', '326|240|241|243|245|242|244|246|496|174|177|174|177|038', '10|10|10|10|10|10|10|10|10|2|3|4|5|9', '20000|16000|15000|15000|10000|7000|7000|3000|2000|1000|1000|1000|1000|1000', '10|5|5|5|5|5|5|5|2|1|1|1|1|1', '2', '14', '2007 Christmas Event: Medium Christmas Present');
INSERT INTO `chest_data` VALUES ('2402', '249', '326|240|241|243|245|242|244|246|496|174|177|174|177|038', '10|10|10|10|10|10|10|10|10|2|3|4|5|9', '18500|15000|14000|15000|10000|7000|7000|3500|2500|1500|1500|1500|1500|1500', '15|8|8|8|8|8|8|8|3|1|1|1|1|1', '2', '14', '2007 Christmas Event: Large Christmas Present');

