/*
 * DBManager.cpp
 *
 *  Created on: Oct 25, 2017
 *      Author: maija
 */

#include "DBManager.h"

DBManager::DBManager() {
	try {
		std::cout << "Getting driver instance" << std::endl;
		driver = sql::mysql::get_driver_instance();
		std::cout << "Creating connection" << std::endl;
		connection = driver->connect("tcp://127.0.0.1:3306", "root", "K0rpp1_K4nt4");
		std::cout << "Connected!" << std::endl;
	} catch(const sql::SQLException& ex) {
		Util::exitWithMessage(ex.what());
	}
}

DBManager::~DBManager() {
	std::cout << "Deleting connection" << std::endl;
	delete connection;
}

std::vector<horse> DBManager::getHorses() {
	std::cout << "Getting horses" << std::endl;

	std::vector<horse> horses = {};

	sql::Statement* stmt = connection->createStatement();
	stmt->execute("USE horsedb");
	sql::ResultSet* res = stmt->executeQuery("SELECT * FROM horses");
	while(res->next()) {
		horse horse;
		strcpy(horse.name, res->getString("name").c_str());
		std::string dateOfBirth = res->getString("dateofbirth");
		horse.dateOfBirth = parseDate(dateOfBirth);
		horse.gender = res->getInt("gender");
		horse.breed = res->getInt("breed");
		std::cout << "Name: " << horse.name
				<< " Date of birth:" << formatDate(horse.dateOfBirth)
				<< " Gender: " << (int)horse.gender
				<< " Breed: " << (int)horse.breed
				<< std::endl;
		horses.push_back(horse);
	}

	return horses;
}

date DBManager::parseDate(std::string dateString) {
	std::cout << "dateString: " << dateString << std::endl;
	int year = getNextInt(dateString);
	std::cout << "dateString: " << dateString << std::endl;
	int month = getNextInt(dateString);
	std::cout << "dateString: " << dateString << std::endl;
	int day = getNextInt(dateString);
	std::cout << "dateString: " << dateString << std::endl;
	date dte;
	dte.y = (uint16_t)year;
	dte.m = (uint8_t)month;
	dte.d = (uint8_t)day;
	return dte;
}

int DBManager::getNextInt(std::string &str) {
	size_t hyphenPosition = str.find("-");
	if(hyphenPosition != std::string::npos) {
		std::string token = str.substr(0, hyphenPosition);
		str.erase(0, hyphenPosition + 1);
		return std::stoi(token);
	}
	else {
		return std::stoi(str);
	}
}

std::string DBManager::formatDate(date date) {
	std::stringstream strstr;
	strstr << (int)date.d << "."
			<< (int)date.m << "."
			<< (int)date.y;
	return strstr.str();
}
