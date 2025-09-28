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

int city_get_info(Cities* _CityList);
int city_parse_list(Cities* _Cities, const char* list);
int city_Init(char* _Name, double _Latitude, double _Longitude, City** _CityPtr);

#endif

