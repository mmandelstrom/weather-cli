#include <stdio.h>
#include <strings.h>
#include <unistd.h>
#include "../includes/utils.h"
#include "../includes/linkedlist.h"
#include "../includes/city.h"
#include <stdbool.h>




bool cities_init(LinkedList* _LinkedList) {

  memset(_LinkedList, 0, sizeof(*_LinkedList)); 

  if (city_parse_list(_LinkedList, cities_list) != 0) {
    return -1;
  }
  
  ll_print(_LinkedList);

  city_get_info();
  
  return 0;
}

void ll_print(LinkedList* _LinkedList) {
  if (_LinkedList->head == NULL) {
    printf("List is empty, no cities to print\n");
  } else {
    City* current = _LinkedList->head;

    do {
      printf("- %s\n", current->name);
      current = current->next;
    } while (current != NULL);
  }
}

int cities_add(LinkedList* _Cities, char* _Name, float _Latitude, float _Longitude, City** _City) {
  City* new_city = (City*)malloc(sizeof(City));
  if (new_city == NULL) {
    printf("Unable to allocate memory for City: %s\n", _Name);
    return -1;
  }

  new_city->name = _Name;
  new_city->latitude = _Latitude;
  new_city->longitude = _Longitude;
  new_city->next = NULL;
  new_city->prev = NULL;
  
  
  if (_Cities->tail == NULL) {
    _Cities->head = new_city;
    _Cities->tail = new_city;
  } else {
    new_city->prev = _Cities->tail;
    _Cities->tail->next = new_city;
    _Cities->tail = new_city;
  }

  if (_City != NULL) {
    *(_City) = new_city;
  }

  return 0;
}




void cities_remove(LinkedList* _LinkedList, City* _City) {
  
	if (_City->next == NULL && _City->prev == NULL) {
		_LinkedList->tail = NULL;
        _LinkedList->head = NULL;
    } else if (_City == _LinkedList->tail) {
		_LinkedList->tail = _City->prev;
        _City->prev->next = NULL;
    } else if (_City == _LinkedList->head){
		_LinkedList->head = _City->next;
        _City->next->prev = NULL;
    } else {
        _City->next->prev = _City->prev;
        _City->prev->next = _City->next;
    }
    
	free(_City);

  return;
}

int cities_get(LinkedList* _LinkedList, char* _Name, City** _CityPtr) {
  City* current = _LinkedList->head;

  while(current != NULL) {
    if (current->name && strcmp(current->name, _Name) == 0) {
      printf("City %s found\n", current->name);
      if (_CityPtr != NULL) {
        *_CityPtr = current;
        return 0;
      }
    }
    current = current->next;
  }
   return -1;
}

