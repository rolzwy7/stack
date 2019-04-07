DROP DATABASE IF EXISTS company;
CREATE DATABASE IF NOT EXISTS company CHARACTER SET utf8 COLLATE utf8_polish_ci;

USE company;

CREATE TABLE `employees` (
  `id` mediumint(8) unsigned NOT NULL auto_increment,
  `first_name` varchar(255) default NULL,
  `added` varchar(255),
  `surname` varchar(255) default NULL,
  PRIMARY KEY (`id`)
) AUTO_INCREMENT=1;

INSERT INTO `employees` (`first_name`,`added`,`surname`) VALUES ("Gil","2018-07-06 20:30:12","Combs"),("Karyn","2018-04-26 21:39:05","Reese"),("Molly","2018-09-06 10:28:04","Torres"),("Amir","2019-01-24 23:57:19","Mccarty"),("Illiana","2019-11-24 21:29:02","Drake"),("Basil","2018-06-24 10:52:01","Anthony"),("Xanthus","2019-05-19 06:36:27","Solomon"),("Piper","2019-06-11 21:27:45","Moore"),("Desiree","2020-03-19 23:01:52","Carlson"),("Donovan","2020-03-14 23:06:13","Hampton");
INSERT INTO `employees` (`first_name`,`added`,`surname`) VALUES ("Chastity","2019-03-07 10:03:13","Wallace"),("Carl","2019-04-03 16:41:21","Moses"),("Ella","2018-11-05 09:33:04","Spears"),("Britanney","2019-02-03 16:15:34","Waters"),("Xandra","2018-07-23 21:56:36","Salinas"),("Hannah","2019-08-19 03:39:36","Strong"),("Abel","2019-09-12 00:41:43","Rios"),("Craig","2020-03-17 02:05:37","Mckee"),("Cassidy","2018-10-13 23:13:57","Bridges"),("Wang","2019-07-16 11:32:09","Conner");
INSERT INTO `employees` (`first_name`,`added`,`surname`) VALUES ("Maryam","2018-04-14 13:27:10","Newton"),("Gavin","2019-04-14 19:36:26","Gordon"),("Dawn","2018-05-31 09:45:19","Craft"),("Brian","2018-04-17 21:43:13","Potter"),("Odessa","2019-08-11 19:38:38","Levy"),("Walker","2019-11-01 00:08:29","Monroe"),("Kennan","2019-07-01 15:07:51","Reid"),("Callie","2019-02-27 06:49:18","Morgan"),("Gray","2018-12-12 07:49:21","Stout"),("Leila","2019-12-18 17:09:41","Moore");
INSERT INTO `employees` (`first_name`,`added`,`surname`) VALUES ("Sara","2018-08-31 07:28:13","Benjamin"),("Owen","2018-10-15 13:07:35","Wilder"),("Fredericka","2019-11-10 08:35:13","Tanner"),("Aquila","2018-11-14 07:25:45","Potter"),("Stewart","2019-04-28 00:34:59","Foster"),("Basia","2018-09-24 07:03:38","Dickerson"),("Yuri","2019-02-21 08:33:41","Ortiz"),("Orla","2019-04-17 23:52:17","Shelton"),("Aubrey","2019-07-29 15:47:48","Dennis"),("Clinton","2018-11-05 16:18:40","Durham");
INSERT INTO `employees` (`first_name`,`added`,`surname`) VALUES ("Brody","2020-03-06 00:17:29","Ingram"),("Dean","2019-06-28 03:04:29","Walters"),("Fuller","2019-08-18 19:46:17","Jefferson"),("Odette","2019-04-07 03:44:48","Dyer"),("Ivan","2019-04-24 16:27:47","Vaughan"),("Wynne","2020-04-01 02:12:16","Fernandez"),("Vivien","2018-12-17 02:21:14","Mcfarland"),("Portia","2018-11-03 16:03:47","Holcomb"),("Melanie","2020-02-15 10:41:42","Cline"),("Dennis","2018-10-08 03:26:13","Huffman");
INSERT INTO `employees` (`first_name`,`added`,`surname`) VALUES ("Lewis","2018-06-16 21:04:34","Rhodes"),("Hannah","2019-08-22 12:34:33","Wyatt"),("Evelyn","2019-03-24 01:49:37","Buckner"),("Jennifer","2019-06-18 14:05:57","Valenzuela"),("Maxine","2019-08-08 00:31:13","Hood"),("Quynn","2018-08-26 22:58:27","Smith"),("Hashim","2018-09-26 01:35:24","Callahan"),("Demetrius","2018-09-18 11:45:50","Lara"),("Boris","2019-10-28 06:00:13","Miles"),("Zachery","2019-02-16 11:02:07","Simpson");
INSERT INTO `employees` (`first_name`,`added`,`surname`) VALUES ("Selma","2018-06-18 01:34:06","Oneill"),("Jameson","2019-11-07 21:37:48","Phelps"),("Mohammad","2018-10-04 00:12:30","Estrada"),("Hiroko","2018-06-08 00:16:35","Joyce"),("Matthew","2019-05-19 17:30:41","Black"),("Daquan","2019-05-05 15:11:47","Jones"),("Blossom","2019-06-04 20:23:57","Reed"),("Elliott","2019-05-12 19:13:00","Bentley"),("Zachery","2018-06-14 22:35:14","Weeks"),("Stacey","2020-01-22 18:26:05","Weaver");
INSERT INTO `employees` (`first_name`,`added`,`surname`) VALUES ("Ignacia","2018-05-31 08:09:17","Mercado"),("Chantale","2020-03-06 17:12:22","Mccormick"),("Seth","2019-06-08 15:53:22","Todd"),("Buffy","2019-06-23 02:50:22","Wiley"),("Forrest","2018-10-26 04:25:38","Hogan"),("Julie","2018-12-07 20:46:00","Stanton"),("Laith","2019-11-09 00:25:30","Harris"),("Talon","2019-07-29 01:44:56","Meyers"),("Lydia","2019-01-09 11:07:06","Charles"),("Ishmael","2018-12-28 10:54:08","Hoffman");
INSERT INTO `employees` (`first_name`,`added`,`surname`) VALUES ("Nichole","2019-05-17 06:41:52","Pope"),("Connor","2020-03-29 05:38:55","Gutierrez"),("Ingrid","2019-08-16 02:22:05","Dickson"),("Lucian","2019-03-28 18:53:53","Morrow"),("Hyacinth","2019-10-16 21:40:12","Petty"),("Quynn","2018-06-23 16:57:29","Jimenez"),("Julian","2019-08-27 07:47:37","Velasquez"),("Zena","2019-06-03 21:06:05","Riggs"),("Griffin","2020-02-08 18:56:33","Orr"),("Shelby","2018-11-10 14:33:10","Norris");
INSERT INTO `employees` (`first_name`,`added`,`surname`) VALUES ("Diana","2018-05-06 10:54:38","Chaney"),("Kylynn","2019-04-14 16:00:50","Vasquez"),("Kirestin","2019-09-02 05:38:02","Padilla"),("Angela","2020-03-14 00:28:52","Garner"),("Bernard","2019-01-24 17:36:05","Benson"),("Uta","2018-04-15 06:07:26","Mathews"),("Ingrid","2019-12-05 04:12:08","Bartlett"),("Tanya","2018-11-04 03:29:36","Fitzgerald"),("Raven","2019-10-17 05:39:10","Barry"),("Caldwell","2019-03-12 11:20:36","Simmons");
