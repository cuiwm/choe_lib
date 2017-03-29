#! /bin/sh
# 创建指定年月的Record表

yearmonth=`date +%Y%m`
daynumber=31

for i in {0..7}
do
	mysql -h 127.0.0.1  -uroot -e"create database IF NOT EXISTS record0$i default charset utf8;"
	for date in $(seq 1 $daynumber)
	do
		for j in {0..31}
		do
			K=`expr $i \* 32 + $j`
			X=$K
			M=`echo $X $yearmonth $date |awk '{printf "%03d%6d%02d",$1,$2,$3}'`
			echo CREATE TABLE RECORD0$M
			mysql -h 127.0.0.1 -uroot -e"use record0$i;create table RECORD0$M(\`SEQ_ID\` bigint(20) unsigned NOT NULL auto_increment,\`APP_ID\` int(11) unsigned  NOT NULL  default '0',\`RECORD_TYPE\` int(11) unsigned  NOT NULL  default '0',\`RELATION_ACCOUNT\` CHAR(128) NOT NULL default '',\`CHAT_TIME\` int(11) unsigned  NOT NULL  default '0',\`CHAT_ID\` CHAR(32) NOT NULL default '',\`MSG_TYPE\` int(11) unsigned  NOT NULL  default '0',\`CHAT_TEXT\` blob,\`INSERT_TIME\` timestamp NOT NULL default CURRENT_TIMESTAMP on update CURRENT_TIMESTAMP,PRIMARY KEY  (\`SEQ_ID\`), KEY \`SELECT_ANY_RECORD\` (\`RELATION_ACCOUNT\`, \`RECORD_TYPE\`, \`APP_ID\`), KEY \`SELECT_ACCOUNT\` (\`RELATION_ACCOUNT\`,\`APP_ID\`), KEY \`SELECT_CHAT_ID\` (\`CHAT_ID\`) ) ENGINE=MYISAM DEFAULT CHARSET=utf8;"
		done
	done
done



