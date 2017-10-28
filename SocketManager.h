/*
 * SocketManager.h
 *
 *  Created on: Oct 25, 2017
 *      Author: maija
 */

#ifndef SOCKETMANAGER_H_
#define SOCKETMANAGER_H_

#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <vector>
#include "horse.h"
#include "DBManager.h"
#include "Util.h"

class SocketManager {
public:
	SocketManager(in_port_t servPort);
	virtual ~SocketManager();
	void loop(DBManager* dbm);
private:
	void exitWithMessage(std::string msg);
	FILE* acceptTCPConnection();
	uint32_t getNextMsg(FILE* channel);
	bool putHorses(std::vector<horse> horses, FILE* channel);
	bool putHorse(horse horse, FILE* channel);
	bool putZero(FILE* channel);
	static const int MAXPENDING = 5;
	int servSock;
};

#endif /* SOCKETMANAGER_H_ */
