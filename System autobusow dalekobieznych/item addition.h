#ifndef _ITEM_ADD_H_
#define _ITEM_ADD_H_

#include "general.h"

void ChooseRoute(Body * bus_system); //dodawanie tras/wejscie do trasy(jezeli taka istnieje)
void ChooseCities(Route * newRoute);	//wybor miasta poczatkowego i docelowego trasy
void AddBus(Route * bus_system);	//chronologiczne dodawanie autobusow do listy
void AddTime(tm newDate);		//i konkretnej godziny
void AddDate(Bus * newBus);		//przypisanie autobusowi konkretnej daty
void SetBusOptions(Bus * newBus);	//ustawienie, czy autobus jest pietrowy, ma klimatyzacje, wifi

#endif