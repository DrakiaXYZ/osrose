/*
MySQL Data Transfer
Source Host: dhrr
Source Database: osrose
Target Host: dhrr
Target Database: osrose
Date: 10/7/2008 8:06:54 PM
*/

SET FOREIGN_KEY_CHECKS=0;
-- ----------------------------
-- Table structure for list_config
-- ----------------------------
CREATE TABLE `list_config` (
  `id` int(10) NOT NULL auto_increment,
  `exp_rate` int(11) NOT NULL,
  `kill_on_fail` tinyint(1) NOT NULL default '0',
  `drop_rate` int(11) NOT NULL,
  `zuly_rate` int(11) NOT NULL,
  `blue_chance` int(11) NOT NULL,
  `slot_chance` int(11) NOT NULL,
  `stat_chance` int(11) NOT NULL,
  `refine_chance` int(11) NOT NULL,
  `rare_refine` int(11) NOT NULL default '0',
  `conf` varchar(50) NOT NULL,
  `player_damage` int(11) NOT NULL,
  `monster_damage` int(11) NOT NULL,
  `player_acc` int(11) NOT NULL,
  `monster_acc` int(11) NOT NULL,
  `pvp_acc` int(11) NOT NULL,
  `skill_damage` int(11) NOT NULL,
  `maxlevel` int(11) NOT NULL,
  `drop_type` int(11) NOT NULL,
  `savetime` int(11) NOT NULL,
  `partygap` int(11) NOT NULL,
  `maxstat` int(11) NOT NULL,
  `cfmode` int(11) NOT NULL,
  PRIMARY KEY  (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=2 DEFAULT CHARSET=latin1;

-- ----------------------------
-- Records 
-- ----------------------------
INSERT INTO `list_config` VALUES ('1', '8', '0', '80', '3', '5', '5', '5', '5', '0', 'default', '100', '100', '100', '100', '100', '100', '250', '2', '500', '10', '300', '0');
