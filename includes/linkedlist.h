#ifndef __LINKEDLIST_H__
#define __LINKEDLIST_H__
#include <stdbool.h>
#include "../includes/city.h"

extern const char* cities_list;

typedef struct LinkedList LinkedList;

typedef struct LinkedList{
	City* head;
	City* tail;
} LinkedList;


int ll_get(LinkedList* _Cities, char* _Name, City** _CityPtr);
bool cities_init(LinkedList* _Cities);
void ll_print(LinkedList* _LinkedList);
int cities_add(LinkedList* _Cities, char* _Name, float _Latitude, float _Longitude, City** _City);
void cities_dispose(LinkedList* _Cities);

#endif
