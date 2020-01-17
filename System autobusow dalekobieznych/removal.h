#ifndef _REMOV_H_
#define _REMOV_H_

#include "general.h"

void Delete(Body * bus_system); //funkcja obslugujaca usuwanie
void DeleteBus(Body * bus_system, Route * current_route, int bus_number); //usuwanie autobusow
void DeleteRoute(Body * bus_system, Route * current_route);	//usuwanie tras w przypadku, gdy nie ma juz autobusow

#endif