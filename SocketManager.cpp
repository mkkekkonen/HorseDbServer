/*
 * SocketManager.cpp
 *
 *  Created on: Oct 25, 2017
 *      Author: maija
 */

#include "SocketManager.h"

SocketManager::SocketManager(in_port_t servPort) {

	if((servSock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
		Util::exitWithMessage("socket() failed");

	struct sockaddr_in servAddr;
	memset(&servAddr, 0, sizeof(servAddr));
	servAddr.sin_family = AF_INET;
	servAddr.sin_addr.s_addr = htonl(INADDR_ANY); // host to network - ulong
	servAddr.sin_port = htons(servPort); // host to network - ushort

	if(bind(servSock, (struct sockaddr*)&servAddr, sizeof(servAddr)) < 0)
		Util::exitWithMessage("bind() failed");

	if(listen(servSock, MAXPENDING) < 0)
		Util::exitWithMessage("listen() failed");
}

SocketManager::~SocketManager() {
	// TODO Auto-generated destructor stub
}

void SocketManager::loop(DBManager* dbm) {

	for(;;) {

		FILE* fileStream = acceptTCPConnection();
		uint32_t msg = getNextMsg(fileStream);
		std::cout << "msg: " << msg << std::endl;
		if(msg == 0b010101)
			putHorses(dbm->getHorses(), fileStream);
		else
			putZero(fileStream);
	}
}

FILE* SocketManager::acceptTCPConnection() {

	struct sockaddr_storage clntAddr;
	socklen_t clntAddrLen = sizeof(clntAddr);

	int clntSock = accept(servSock, (struct sockaddr*)&clntAddr, &clntAddrLen);
	if(clntSock < 0)
		Util::exitWithMessage("accept() failed");

	FILE* channel = fdopen(clntSock, "r+");
	if(channel == NULL)
		Util::exitWithMessage("fdopen() failed");
	return channel;
}

uint32_t SocketManager::getNextMsg(FILE* channel) {
	uint32_t msg,
		error = 0;
	if(fread(&msg, sizeof(uint32_t), 1, channel) != 1)
		return error;
	msg = ntohl(msg);
	return msg;
}

bool SocketManager::putHorses(std::vector<horse> v, FILE* channel) {
	uint16_t header = 0b010101;
	header = htons(header);
	uint16_t nHorses = v.size();
	nHorses = htons(nHorses);
	if(fwrite(&header, sizeof(uint16_t), 1, channel) != 1
			|| fwrite(&nHorses, sizeof(uint16_t), 1, channel) != 1)
		Util::exitWithMessage("writing header failed");
	for(int i = 0; i < v.size(); i++)
		if(!putHorse(v[i], channel))
			Util::exitWithMessage("putHorse() failed");
}

bool SocketManager::putHorse(horse h, FILE* channel) {
	std::cout << "Putting horse" << std::endl;
	h.dateOfBirth.y = htons(h.dateOfBirth.y);
	if(fwrite(&h, sizeof(horse), 1, channel) != 1)
		return false;
	fflush(channel);
	return true;
}

bool SocketManager::putZero(FILE* channel) {
	std::cout << "Putting zero" << std::endl;
	uint16_t zero = 0;
	if(fwrite(&zero, sizeof(uint16_t), 1, channel) != 1)
		return false;
	fflush(channel);
	return true;
}
