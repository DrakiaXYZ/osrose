/*
MySQL Data Transfer
Source Host: osrose
Source Database: osrose
Target Host: osrose
Target Database: osrose
Date: 7/19/2008 8:06:52 AM
*/

SET FOREIGN_KEY_CHECKS=0;
-- ----------------------------
-- Table structure for list_telegates
-- ----------------------------
CREATE TABLE `list_telegates` (
  `id` int(10) NOT NULL,
  `srcmap` int(10) NOT NULL,
  `srcx` float NOT NULL,
  `srcy` float NOT NULL,
  `destmap` int(10) NOT NULL,
  `destx` float NOT NULL,
  `desty` float NOT NULL,
  PRIMARY KEY  (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records 
-- ----------------------------
INSERT INTO `list_telegates` VALUES ('11', '21', '5135.83', '5551.34', '1', '5247.99', '5024.26');
INSERT INTO `list_telegates` VALUES ('12', '21', '5080.88', '5018.84', '22', '5844.11', '5543.18');
INSERT INTO `list_telegates` VALUES ('13', '21', '5545.91', '5338.69', '23', '5045.95', '4962.88');
INSERT INTO `list_telegates` VALUES ('14', '21', '5306.85', '5025.11', '22', '5973.44', '5550.06');
INSERT INTO `list_telegates` VALUES ('17', '22', '5825.77', '5571.81', '21', '5093.14', '5044.78');
INSERT INTO `list_telegates` VALUES ('18', '22', '5383.32', '5078.91', '31', '5520.44', '5450.31');
INSERT INTO `list_telegates` VALUES ('19', '22', '5979.73', '5577.98', '21', '5301.46', '5047.28');
INSERT INTO `list_telegates` VALUES ('21', '1', '5236.86', '4982.02', '21', '5140.06', '5504.44');
INSERT INTO `list_telegates` VALUES ('22', '1', '5271.78', '5543.42', '24', '5151.02', '4878.51');
INSERT INTO `list_telegates` VALUES ('23', '1', '5546.1', '5170.63', '23', '5040.86', '5206.05');
INSERT INTO `list_telegates` VALUES ('26', '23', '5010.83', '4964.57', '21', '5520.37', '5335.52');
INSERT INTO `list_telegates` VALUES ('27', '23', '5048.43', '5569.67', '24', '5382.48', '4906.56');
INSERT INTO `list_telegates` VALUES ('28', '23', '5009.55', '5204.56', '1', '5512.29', '5177.15');
INSERT INTO `list_telegates` VALUES ('31', '24', '5161.2', '4830.98', '1', '5279.88', '5493.08');
INSERT INTO `list_telegates` VALUES ('32', '24', '5376.06', '4848.49', '23', '5065.35', '5532.05');
INSERT INTO `list_telegates` VALUES ('33', '24', '5751.95', '5493.36', '25', '5027.93', '5442.95');
INSERT INTO `list_telegates` VALUES ('36', '25', '4994.22', '5404.84', '24', '5691.21', '5492.95');
INSERT INTO `list_telegates` VALUES ('38', '25', '5417.02', '4893.31', '2', '5615.07', '5543.74');
INSERT INTO `list_telegates` VALUES ('39', '25', '5699.28', '5232.03', '26', '5050.41', '5501.55');
INSERT INTO `list_telegates` VALUES ('40', '25', '5529.2', '5564.26', '29', '5082.87', '5023.78');
INSERT INTO `list_telegates` VALUES ('41', '26', '4993.92', '5525.09', '25', '5642.96', '5241.79');
INSERT INTO `list_telegates` VALUES ('42', '26', '5273.73', '4853.05', '27', '5154.97', '5483.59');
INSERT INTO `list_telegates` VALUES ('43', '29', '5088.85', '4982.47', '25', '5503.03', '5530.31');
INSERT INTO `list_telegates` VALUES ('46', '27', '5152.74', '5519.31', '26', '5277.77', '4883.99');
INSERT INTO `list_telegates` VALUES ('47', '27', '5760.53', '5520.38', '28', '5471.66', '4768.62');
INSERT INTO `list_telegates` VALUES ('51', '28', '5461.25', '4733.01', '27', '5768.91', '5494.68');
INSERT INTO `list_telegates` VALUES ('56', '2', '5639.49', '5563.82', '25', '5407.84', '4949.69');
INSERT INTO `list_telegates` VALUES ('61', '31', '5520.7', '5481.9', '22', '5408.64', '5038.51');
INSERT INTO `list_telegates` VALUES ('62', '31', '5292.86', '5303.2', '32', '5434.77', '5257.05');
INSERT INTO `list_telegates` VALUES ('63', '31', '5387.19', '5273', '32', '5524.89', '5384.32');
INSERT INTO `list_telegates` VALUES ('64', '32', '5437.07', '5298.83', '31', '5294.74', '5327.64');
INSERT INTO `list_telegates` VALUES ('65', '32', '5522.32', '5358.58', '31', '5381.38', '5216.77');
INSERT INTO `list_telegates` VALUES ('66', '32', '5436.84', '5162.54', '33', '5605.13', '5485.46');
INSERT INTO `list_telegates` VALUES ('67', '32', '5121.17', '5031.31', '33', '5154.54', '5207.43');
INSERT INTO `list_telegates` VALUES ('68', '33', '5607.6', '5506.83', '32', '5433.88', '5202.87');
INSERT INTO `list_telegates` VALUES ('69', '33', '5155.8', '5245.27', '32', '5117.51', '5074');
INSERT INTO `list_telegates` VALUES ('71', '40', '5185.07', '5129.11', '2', '5547.6', '5193.07');
INSERT INTO `list_telegates` VALUES ('86', '54', '5066.67', '4240.93', '56', '5034.48', '4272.99');
INSERT INTO `list_telegates` VALUES ('87', '56', '5710.57', '4380.42', '56', '5664.48', '4924.34');
INSERT INTO `list_telegates` VALUES ('88', '56', '5673.99', '4943.41', '56', '5590.93', '4385.44');
INSERT INTO `list_telegates` VALUES ('89', '56', '5211.99', '4614.97', '56', '5125.16', '5311.09');
INSERT INTO `list_telegates` VALUES ('90', '56', '5120.08', '5277.04', '56', '5215.43', '4733.23');
INSERT INTO `list_telegates` VALUES ('91', '56', '5045.29', '4519.77', '56', '5528.24', '4564.86');
INSERT INTO `list_telegates` VALUES ('92', '56', '5478.15', '4569.29', '56', '5096.59', '4565.07');
INSERT INTO `list_telegates` VALUES ('93', '57', '5772.26', '5171.19', '57', '5432.11', '5354.7');
INSERT INTO `list_telegates` VALUES ('94', '57', '5456.32', '5350.38', '57', '5764.81', '5185.23');
INSERT INTO `list_telegates` VALUES ('95', '56', '5035.08', '5253.38', '57', '5540.01', '5157.9');
INSERT INTO `list_telegates` VALUES ('96', '57', '5541.42', '5101.11', '56', '5035.21', '5200.04');
INSERT INTO `list_telegates` VALUES ('101', '51', '5008.97', '4839.75', '52', '6156.07', '5210.39');
INSERT INTO `list_telegates` VALUES ('102', '51', '5445.15', '4686.24', '53', '6159.24', '5368.95');
INSERT INTO `list_telegates` VALUES ('103', '51', '5718.27', '5230.67', '54', '5058.63', '4439.96');
INSERT INTO `list_telegates` VALUES ('104', '51', '5079.73', '5378.6', '55', '5524.47', '4464.4');
INSERT INTO `list_telegates` VALUES ('105', '51', '5007.16', '5307.56', '58', '5676.35', '4269.24');
INSERT INTO `list_telegates` VALUES ('106', '52', '6201.18', '5201.6', '51', '5059.28', '4851.4');
INSERT INTO `list_telegates` VALUES ('107', '52', '5731.86', '4677.65', '53', '5037.27', '5202.48');
INSERT INTO `list_telegates` VALUES ('109', '53', '6127.19', '5414.47', '51', '5444.41', '4728.49');
INSERT INTO `list_telegates` VALUES ('110', '53', '4989.23', '5191', '52', '5690.67', '4690.99');
INSERT INTO `list_telegates` VALUES ('112', '54', '5025.87', '4408.42', '51', '5667.08', '5237.91');
INSERT INTO `list_telegates` VALUES ('113', '54', '5063.33', '4833.69', '55', '5814.3', '4684.07');
INSERT INTO `list_telegates` VALUES ('115', '55', '5519.94', '4416.11', '51', '5084.68', '5344.79');
INSERT INTO `list_telegates` VALUES ('116', '55', '5838.36', '4697.31', '54', '5093.42', '4824.61');
INSERT INTO `list_telegates` VALUES ('117', '58', '5680.8', '4174.61', '51', '4999.23', '5265.38');
INSERT INTO `list_telegates` VALUES ('120', '56', '5035.79', '4235.9', '54', '5114.37', '4250.87');
INSERT INTO `list_telegates` VALUES ('123', '59', '5007.55', '5126.43', '54', '5114.37', '4250.87');
INSERT INTO `list_telegates` VALUES ('126', '61', '5232.55', '5418.33', '62', '5681.12', '4554.2');
INSERT INTO `list_telegates` VALUES ('127', '61', '5827.32', '5411.13', '62', '6333.31', '4460.94');
INSERT INTO `list_telegates` VALUES ('128', '62', '5686.36', '4391.86', '61', '5218.67', '5385.83');
INSERT INTO `list_telegates` VALUES ('129', '62', '6326.54', '4342.24', '61', '5802.86', '5388.78');
INSERT INTO `list_telegates` VALUES ('130', '62', '5005.84', '5317.1', '63', '6080.95', '5189.86');
INSERT INTO `list_telegates` VALUES ('131', '63', '6106.96', '5239.22', '62', '5092.95', '5261.04');
INSERT INTO `list_telegates` VALUES ('132', '62', '6590.96', '5292.14', '64', '5042.98', '5318.52');
INSERT INTO `list_telegates` VALUES ('133', '64', '5020.87', '5357.01', '62', '6536.86', '5245.06');
INSERT INTO `list_telegates` VALUES ('134', '63', '5404.55', '4372.7', '65', '5511.9', '5395');
INSERT INTO `list_telegates` VALUES ('135', '65', '5451.93', '5380.5', '63', '5403.91', '4437.7');
