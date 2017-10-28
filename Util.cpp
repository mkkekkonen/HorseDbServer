/*
 * Util.cpp
 *
 *  Created on: Oct 26, 2017
 *      Author: maija
 */

#include "Util.h"

Util::Util() {
	// TODO Auto-generated constructor stub

}

Util::~Util() {
	// TODO Auto-generated destructor stub
}

void Util::exitWithMessage(std::string msg) {
	std::cout << msg << std::endl;
	exit(1);
}
