#ifndef _GENERAL_H_
#define _GENERAL_H_

#include <time.h>
#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <stdlib.h>
#define MAX_CITY_LENGTH 13
#define AMOUNT_OF_CITIES 22
#define AMOUNT_OF_SEATS 40

struct Bus
{
	tm date;								//zmienna typu tm(struktura z time.h) do przechowywania daty
	bool deck, air_cond, wifi;			//zmienne opisujace 'opcje' autobusu, tj pietrowy, klima, wifi
	int floor1[AMOUNT_OF_SEATS], floor2[AMOUNT_OF_SEATS];	//tablice przechowujace miejsca autobusu

	Bus * next;
};
struct Route
{
	int bus_counter = 0;		//ilosc autobusow w trasie
	char from[MAX_CITY_LENGTH], to[MAX_CITY_LENGTH];	//tablice przechowujace nazwy tras
	Route * next, *prev;
	Bus * main_bus;		//wskaznik na pierwszy autobus tej trasy	
};
struct Body
{
	Route * head, *tail;	//struktura pomocnicza, glowa i ogon listy tras
};

int GetChoice(int number);	//wybor uzytkownika
int ShowBuses(Route * current_route);	//wyswietlanie autobusow
int ShowRoutes(Body * bus_system);	//wyswietlanie tras
Route * PickRoute(Body * bus_system, int route_number);	//zwraca wskaznik na trase wybrana przez uzytkownika
void FreeMemory(Body * bus_system);	//zwalnianie pamieci

#endif