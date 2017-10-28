/*
 * date.h
 *
 *  Created on: Oct 27, 2017
 *      Author: maija
 */

#ifndef DATE_H_
#define DATE_H_

#include <cstdint>

struct date {
	uint8_t d;
	uint8_t m;
	uint16_t y;
};

typedef struct date date;


#endif /* DATE_H_ */
