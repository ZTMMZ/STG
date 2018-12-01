#ifndef __DBUTIL_H__
#define __DBUTIL_H__

#include "cocos2d.h" 
#include "Utils/sqlite3.h"
#pragma comment(lib, "sqlite3.lib")
USING_NS_CC;

class DBUtil{
public:
	DBUtil();
	~DBUtil();
	static DBUtil* sharedDB();

	sqlite3 *pDB;//数据库指针            
	char * errMsg;//错误信息
	int results;//sqlite3_exec返回值   
	//Vector<Map<std::string, std::string>> playerInfo;

	bool openDB(std::string dbName);
	bool createTable(std::string SQLStr);
	bool isTableExisted(std::string tableName);
	bool insertTable(std::string dbExec);
	bool deleteTable(std::string tableName);
	bool updateTable(std::string dbExec);
	bool clearTable(std::string tableName);
	void closeDB();

	std::vector<std::vector<std::string>> getPlayerInfo();
};
 



































#endif /* __DBUTIL_H__ */
