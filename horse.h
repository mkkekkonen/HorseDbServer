/*
 * horse.h
 *
 *  Created on: Oct 25, 2017
 *      Author: maija
 */

#ifndef HORSE_H_
#define HORSE_H_

#include "date.h"

struct horse {
	char name[256];
	date dateOfBirth;
	uint8_t gender;
	uint8_t breed;
};

typedef struct horse horse;

#endif /* HORSE_H_ */
