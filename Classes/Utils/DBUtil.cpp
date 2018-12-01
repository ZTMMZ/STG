#include "DBUtil.h"


DBUtil::DBUtil(){
	pDB = NULL;//���ݿ�ָ��         
	errMsg = NULL;//������Ϣ
	results = -1;//Execute����ֵ   
}
DBUtil::~DBUtil(){}

DBUtil* DBUtil::sharedDB(){
	static DBUtil sharedDB;
	return &sharedDB;
}

//��һ�����ݿ⣬����������򴴽�һ���µ����ݿ��ļ�  
bool DBUtil::openDB(std::string dbName){
	std::string folder = CCFileUtils::sharedFileUtils()->getWritablePath();
	std::string dbPath = folder + dbName;
	bool success = false;
	int result = sqlite3_open(dbPath.c_str(), &pDB);
	if (result != SQLITE_OK){
		CCLOG("Open database failed ,Error code:%d ,Cause:%s", result, errMsg);
		success = false;
	}else{
		CCLOG("Open database success");
		success = true;
	}
	return success;
}

//������
bool  DBUtil::createTable(std::string SQLStr){
	bool success = false;
	int result = sqlite3_exec(pDB, SQLStr.c_str(), NULL, NULL, &errMsg);
	if (result != SQLITE_OK){
		CCLOG("Create table failed ,Error code:%d ,Cause:%s", result, errMsg);
		success = false;
	}else{
		CCLOG("Create table success");
		success = true;
	}
	return success;
}

//�жϱ��Ƿ���� 
bool  DBUtil::isTableExisted(std::string tableName){
	bool success = false;
	std::string SQLStrs = "";
	SQLStrs.append("select count(type) from sqlite_master where type='table' and name='");
	SQLStrs.append(tableName);
	SQLStrs.append("'");
	int result = sqlite3_exec(pDB, SQLStrs.c_str(), NULL, NULL, &errMsg);
	if (result != SQLITE_OK){
		CCLOG("Table is not exist");
		success = false;
	}else{
		CCLOG("Table is exist");
		success = true;
	}
	return success;
}

//��������   
bool DBUtil::insertTable(std::string SQLStr){
	bool success = false;
	int result = sqlite3_exec(pDB, SQLStr.c_str(), NULL, NULL, &errMsg);
	if (result != SQLITE_OK){
		CCLOG("Insert data in table failed ,Error code:%d ,Cause:%s", result, errMsg);
		success = false;
	}else{
		CCLOG("Insert data success");
		success = true;
	}
	return success;
}


//ɾ����
bool DBUtil::deleteTable(std::string tableName){
	bool success = false;
	std::string SQLStrs = "";
	SQLStrs.append("drop table  ");
	SQLStrs.append(tableName);
	SQLStrs.append(" ");
	int result = sqlite3_exec(pDB, SQLStrs.c_str(), NULL, NULL, &errMsg);
	if (result != SQLITE_OK){
		CCLOG("Delete table failed ,Error code:%d ,Cause:%s", result, errMsg);
		success = false;
	}else{
		CCLOG("Delete table success");
		success = true;
	}
	return success;
}


//��������
bool DBUtil::updateTable(std::string SQLStr){
	bool success = false;
	int result = sqlite3_exec(pDB, SQLStr.c_str(), NULL, NULL, &errMsg);
	if (result != SQLITE_OK){
		CCLOG("Update table failed ,Error code:%d ,Cause:%s", result, errMsg);
		success = false;
	}else{
		CCLOG("Update table success");
		success = true;
	}
	return success;
}
//�������
bool DBUtil::clearTable(std::string tableName){
	bool success = false;
	std::string SQLStrs = "";
	SQLStrs.append("delete from  ");
	SQLStrs.append(tableName);
	SQLStrs.append(" ");
	int result = sqlite3_exec(pDB, SQLStrs.c_str(), NULL, NULL, &errMsg);
	if (result != SQLITE_OK){
		CCLOG("Clear data failed ,Error code:%d ,Cause:%s", result, errMsg);
		success = false;
	}else{
		CCLOG("Clear data success");
		success = true;
	}
	return success;
}

//�ر����ݿ�  
void DBUtil::closeDB(){
	sqlite3_close(pDB);
}

//��ȡ�����Ϣ
std::vector<std::vector<std::string>> DBUtil::getPlayerInfo(){
	std::vector<std::vector<std::string>> playerInfos;
	char **re;//��ѯ���
	int r, c;//�С���
	sqlite3_get_table(pDB, "select * from playerinfo order by playerscores desc", &re, &r, &c, NULL);//1
	
	std::vector<std::string> playerInfo;
	playerInfo.push_back(String::createWithFormat("%d", r)->_string);
	playerInfo.push_back(String::createWithFormat("%d", c)->_string);
	playerInfos.push_back(playerInfo);

	for (int i = 1; i <= r; i++)//2
	{
		std::vector<std::string> playerInfo;
		for (int j = 0; j < c; j++)
		{
			playerInfo.push_back(String::createWithFormat("%s", re[i*c + j])->_string);
		}
		playerInfos.push_back(playerInfo);
	}
	sqlite3_free_table(re);

	return playerInfos;
}
