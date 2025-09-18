#ifndef __CITIES_H__
#define __CITIES_H__

extern const char* cities_list;
typedef struct city city;

typedef struct city {
	city* prev;
	city* next;
	char* name;
	float latitude;
	float longitude;
} city;

typedef struct {
	city* head;
	city* tail;
} cities;

int cities_init(cities* c);
void cities_print(cities* _Cities);
int cities_add(cities* _Cities, char* _Name, float _Latitude, float _Longitude, city** _City);
void cities_remove(cities* _Cities, city* _City);
city* cities_search_by_name(cities* _Cities);
void cities_dispose(cities* c);

#endif
