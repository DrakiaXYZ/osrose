SET FOREIGN_KEY_CHECKS=0;
-- ----------------------------
-- Table structure for list_mobgroups_special
-- ----------------------------
CREATE TABLE `list_mobgroups_special` (
`id` int(11) NOT NULL auto_increment,
`map` int(11) NOT NULL,
`x` float NOT NULL,
`y` float NOT NULL,
`range` int(11) NOT NULL,
`respawntime` int(11) NOT NULL,
`limit` int(11) NOT NULL,
`tacticalpoints` int(11) NOT NULL,
`moblist` varchar(1024) default NULL,
`daynight` int(11) NOT NULL default 0,
`isactive` int(11) NOT NULL default 1,
`whatisit` varchar(50) default NULL,
PRIMARY KEY  (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=1 DEFAULT CHARSET=utf8;
INSERT INTO `list_mobgroups_special` VALUES (0, 2, 5514.00, 5363.00, 10, 20, 8, 200, '3012,1,0|3012,1,0|3012,1,0|3013,1,0|3013,1,0|3013,1,0',2,0,'Halloween_2008_JP');
INSERT INTO `list_mobgroups_special` VALUES (0, 2, 5567.00, 5365.00, 10, 20, 5, 200, '3009,1,0|3009,1,0|3009,1,0|3010,1,0|3010,1,0|3010,1,0',2,0,'Halloween_2008_JP');
INSERT INTO `list_mobgroups_special` VALUES (0, 2, 5706.00, 5362.00, 10, 20, 5, 200, '3012,1,0|3012,1,0|3012,1,0|3013,1,0|3013,1,0|3013,1,0',2,0,'Halloween_2008_JP');
INSERT INTO `list_mobgroups_special` VALUES (0, 2, 5704.00, 5285.00, 10, 20, 5, 200, '3012,1,0|3012,1,0|3012,1,0|3013,1,0|3013,1,0|3013,1,0',2,0,'Halloween_2008_JP');
INSERT INTO `list_mobgroups_special` VALUES (0, 2, 5706.00, 5203.00, 10, 20, 5, 200, '3009,1,0|3009,1,0|3009,1,0|3010,1,0|3010,1,0|3010,1,0',2,0,'Halloween_2008_JP');
INSERT INTO `list_mobgroups_special` VALUES (0, 2, 5695.00, 5098.00, 10, 20, 7, 200, '3012,1,0|3012,1,0|3012,1,0|3013,1,0|3013,1,0|3013,1,0',2,0,'Halloween_2008_JP');
INSERT INTO `list_mobgroups_special` VALUES (0, 2, 5565.00, 5075.00, 10, 20, 7, 200, '3009,1,0|3009,1,0|3009,1,0|3010,1,0|3010,1,0|3010,1,0',2,0,'Halloween_2008_JP');
INSERT INTO `list_mobgroups_special` VALUES (0, 2, 5459.00, 5075.00, 10, 20, 9, 200, '3012,1,0|3012,1,0|3012,1,0|3013,1,0|3013,1,0|3013,1,0',2,0,'Halloween_2008_JP');
INSERT INTO `list_mobgroups_special` VALUES (0, 2, 5381.00, 5675.00, 10, 20, 5, 200, '3012,1,0|3012,1,0|3012,1,0|3013,1,0|3013,1,0|3013,1,0',2,0,'Halloween_2008_JP');
INSERT INTO `list_mobgroups_special` VALUES (0, 2, 5385.00, 5146.00, 10, 20, 6, 200, '3009,1,0|3009,1,0|3009,1,0|3010,1,0|3010,1,0|3010,1,0',2,0,'Halloween_2008_JP');
INSERT INTO `list_mobgroups_special` VALUES (0, 2, 5384.00, 5276.00, 10, 20, 9, 200, '3012,1,0|3012,1,0|3012,1,0|3013,1,0|3013,1,0|3013,1,0',2,0,'Halloween_2008_JP');
INSERT INTO `list_mobgroups_special` VALUES (0, 2, 5395.00, 5364.00, 10, 20, 5, 200, '3009,1,0|3009,1,0|3009,1,0|3010,1,0|3010,1,0|3010,1,0',2,0,'Halloween_2008_JP');
INSERT INTO `list_mobgroups_special` VALUES (0, 2, 5481.00, 5364.00, 10, 20, 5, 200, '3012,1,0|3012,1,0|3012,1,0|3013,1,0|3013,1,0|3013,1,0',2,0,'Halloween_2008_JP');
INSERT INTO `list_mobgroups_special` VALUES (0, 2, 5283.00, 5495.00, 10, 20, 9, 200, '3009,1,0|3009,1,0|3009,1,0|3010,1,0|3010,1,0|3010,1,0',2,0,'Halloween_2008_JP');
INSERT INTO `list_mobgroups_special` VALUES (0, 2, 5390.00, 5518.00, 10, 20, 6, 200, '3012,1,0|3012,1,0|3012,1,0|3013,1,0|3013,1,0|3013,1,0',2,0,'Halloween_2008_JP');
INSERT INTO `list_mobgroups_special` VALUES (0, 2, 5504.00, 5521.00, 10, 20, 8, 200, '3012,1,0|3012,1,0|3012,1,0|3013,1,0|3013,1,0|3013,1,0',2,0,'Halloween_2008_JP');
INSERT INTO `list_mobgroups_special` VALUES (0, 2, 5532.00, 5472.00, 10, 20, 6, 200, '3009,1,0|3009,1,0|3009,1,0|3010,1,0|3010,1,0|3010,1,0',2,0,'Halloween_2008_JP');
INSERT INTO `list_mobgroups_special` VALUES (0, 2, 5624.00, 5485.00, 10, 20, 8, 200, '3012,1,0|3012,1,0|3012,1,0|3013,1,0|3013,1,0|3013,1,0',2,0,'Halloween_2008_JP');
INSERT INTO `list_mobgroups_special` VALUES (0, 2, 5714.00, 5498.00, 10, 20, 9, 200, '3012,1,0|3012,1,0|3012,1,0|3013,1,0|3013,1,0|3013,1,0',2,0,'Halloween_2008_JP');
INSERT INTO `list_mobgroups_special` VALUES (0, 2, 5788.00, 5498.00, 10, 20, 7, 200, '3009,1,0|3009,1,0|3009,1,0|3010,1,0|3010,1,0|3010,1,0',2,0,'Halloween_2008_JP');
INSERT INTO `list_mobgroups_special` VALUES (0, 29, 5067.43, 5358.85, 1, 1200, 1, 200, '3016,10,0|3016,10,0|3016,10,0|3016,10,0|3016,10,0|3016,10,1|3016,10,1',0,0,'Halloween_2008_DoD_Grand_Pumpkin');
INSERT INTO `list_mobgroups_special` VALUES (0, 55, 5278.87, 4504.42, 10, 90, 1, 100, '232,1,0|232,1,0|232,1,0|232,1,0|232,1,0|232,1,1|232,1,1',0,0,'Xmas_2008_Elite_Wolverine');
INSERT INTO `list_mobgroups_special` VALUES (0, 55, 5341.20, 4668.04, 10, 90, 1, 100, '232,1,0|232,1,0|232,1,0|232,1,0|232,1,0|232,1,1|232,1,1',0,0,'Xmas_2008_Elite_Wolverine');
INSERT INTO `list_mobgroups_special` VALUES (0, 55, 5421.41, 4402.91, 10, 90, 1, 100, '232,1,0|232,1,0|232,1,0|232,1,0|232,1,0|232,1,1|232,1,1',0,0,'Xmas_2008_Elite_Wolverine');
INSERT INTO `list_mobgroups_special` VALUES (0, 55, 5493.48, 4690.32, 10, 90, 1, 100, '232,1,0|232,1,0|232,1,0|232,1,0|232,1,0|232,1,1|232,1,1',0,0,'Xmas_2008_Elite_Wolverine');
INSERT INTO `list_mobgroups_special` VALUES (0, 55, 5670.05, 4451.56, 10, 90, 1, 100, '232,1,0|232,1,0|232,1,0|232,1,0|232,1,0|232,1,1|232,1,1',0,0,'Xmas_2008_Elite_Wolverine');
INSERT INTO `list_mobgroups_special` VALUES (0, 55, 5768.39, 4439.00, 10, 90, 1, 100, '232,1,0|232,1,0|232,1,0|232,1,0|232,1,0|232,1,1|232,1,1',0,0,'Xmas_2008_Elite_Wolverine');
INSERT INTO `list_mobgroups_special` VALUES (0, 54, 5167.20, 5339.15, 10, 90, 1, 100, '233,1,0|233,1,0|233,1,0|233,1,0|233,1,0|233,1,1|233,1,1',0,0,'Xmas_2008_Elite_Elder_Mammoth');
INSERT INTO `list_mobgroups_special` VALUES (0, 54, 5228.91, 4464.56, 10, 90, 1, 100, '233,1,0|233,1,0|233,1,0|233,1,0|233,1,0|233,1,1|233,1,1',0,0,'Xmas_2008_Elite_Elder_Mammoth');
INSERT INTO `list_mobgroups_special` VALUES (0, 54, 5291.81, 5240.74, 10, 90, 1, 100, '233,1,0|233,1,0|233,1,0|233,1,0|233,1,0|233,1,1|233,1,1',0,0,'Xmas_2008_Elite_Elder_Mammoth');
INSERT INTO `list_mobgroups_special` VALUES (0, 54, 5440.40, 5075.92, 10, 90, 1, 100, '233,1,0',0,0,'Xmas_2008_Elite_Elder_Mammoth');
INSERT INTO `list_mobgroups_special` VALUES (0, 54, 5440.69, 5208.50, 10, 90, 1, 100, '233,1,0|233,1,0|233,1,0|233,1,0|233,1,0|233,1,1|233,1,1',0,0,'Xmas_2008_Elite_Elder_Mammoth');
INSERT INTO `list_mobgroups_special` VALUES (0, 54, 5610.94, 4797.55, 10, 90, 1, 100, '233,1,0|233,1,0|233,1,0|233,1,0|233,1,0|233,1,1|233,1,1',0,0,'Xmas_2008_Elite_Elder_Mammoth');
INSERT INTO `list_mobgroups_special` VALUES (0, 53, 5333.39, 5034.83, 10, 90, 1, 100, '234,1,0|234,1,0|234,1,0|234,1,0|234,1,0|234,1,1|234,1,1',0,0,'Xmas_2008_Elite_Tyrant_Warship');
INSERT INTO `list_mobgroups_special` VALUES (0, 58, 5410.82, 4624.33, 20, 90, 1, 200, '235,1,0',0,0,'Xmas_2008_Elite_Behemoth_King');


