#ifndef __CITY_H__
#define __CITY_H__
typedef struct LinkedList LinkedList;


typedef struct City {
	City* prev;
	City* next;
	char* name;
	float latitude;
	float longitude;
} City;

int city_get_info(LinkedList* _CityList);
int city_parse_list(LinkedList* _LinkedList, const char* list);

#endif

