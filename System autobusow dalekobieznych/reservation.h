#ifndef _RESERV_H_
#define _RESERV_H_

#include "general.h"

void Reserve(Body * bus_system);	//funkcja obslugujaca rezerwacje
void PickBus(Route * current_route, int bus_number); //wybranie autobusu do rezerwacji
void AddReservation(Bus * current_bus); //dodawanie rezerwacji
void ShowReservations(Bus * current_bus); //wyswietlenie miejsc w autobusie

#endif