/*
 * DBManager.h
 *
 *  Created on: Oct 25, 2017
 *      Author: maija
 */

#ifndef DBMANAGER_H_
#define DBMANAGER_H_

#include <cstring>
#include <exception>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <mysql_connection.h>
#include <mysql_driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include "horse.h"
#include "Util.h"

class DBManager {
public:
	DBManager();
	virtual ~DBManager();
	void init();
	std::vector<horse> getHorses();
private:
	date parseDate(std::string dateString);
	int getNextInt(std::string& str);
	std::string formatDate(date date);
	sql::Driver* driver;
	sql::Connection* connection;
};

#endif /* DBMANAGER_H_ */
