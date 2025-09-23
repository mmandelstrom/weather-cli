#ifndef __CITY_H__
#define __CITY_H__
#include "../includes/linkedlist.h"

typedef struct City City;

typedef struct City {
	City* prev;
	City* next;
	char* name;
	float latitude;
	float longitude;
} City;

#endif

