/*
 * Util.h
 *
 *  Created on: Oct 26, 2017
 *      Author: maija
 */

#ifndef UTIL_H_
#define UTIL_H_

#include <iostream>

class Util {
public:
	Util();
	virtual ~Util();
	static void exitWithMessage(std::string msg);
};

#endif /* UTIL_H_ */
