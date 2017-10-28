#include "DBManager.h"
#include "SocketManager.h"

int main(int argc, char* argv[]) {

	std::cout << "Starting" << std::endl;

	if(argc != 2)
		Util::exitWithMessage("Parameters: <server port>");
	std::string portString(argv[1]);
	int serverPort = std::stoi(portString);
	std::cout << "Port: " << serverPort << std::endl;
	SocketManager* socketManager = new SocketManager(serverPort);
	DBManager* dbManager = new DBManager();

	socketManager->loop(dbManager);

	delete dbManager;
	delete socketManager;

	return 0;
}
