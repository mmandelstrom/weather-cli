#ifndef __CITIES_H__
#define __CITIES_H__

extern const char* cities_list;
typedef struct City City;

typedef struct City {
	City* prev;
	City* next;
	char* name;
	float latitude;
	float longitude;
} City;

typedef struct {
	City* head;
	City* tail;
} Cities;

int cities_init(Cities* _Cities);
void cities_print(Cities* _Cities);
int cities_add(Cities* _Cities, char* _Name, float _Latitude, float _Longitude, City** _City);
void cities_remove(Cities* _Cities, City* _City);
int cities_get(Cities* _Cities, char* _Name, City** _CityPtr);
void cities_dispose(Cities* _Cities);

#endif
