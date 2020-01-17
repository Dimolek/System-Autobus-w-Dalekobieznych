#include "general.h"

int GetChoice(int number)
{
	int choice;
	while ((scanf("%d", &choice) != 1) || choice <= 0 || choice > number) //wybor uzytkownika nie moze byc wiekszy
	{																	//niz ilosc dostepnych autobusow/tras
		puts("\nBledne znaki lub numer, sproboj ponownie.");
		while (getchar() != '\n')										//powrot do wyboru po wcisnieciu litery
			continue;													//zamiast liczby
	}
	return choice;
}
int ShowBuses(Route * current_route)
{
	system("cls");
	Bus * current_bus = current_route->main_bus;
	int bus_number = 0;								//zmienna numerujaca autobusy
	puts("Dostepne autobusy:");
	while (current_bus != NULL)									//petla wyswietlajaca zawartosc autobusow
	{
		bus_number++;
		printf("\n%d. %02d.%02d.%dr.  %02d:%02d	", bus_number,
			current_bus->date.tm_mday, current_bus->date.tm_mon + 1, current_bus->date.tm_year + 1900,
			current_bus->date.tm_hour, current_bus->date.tm_min);

		current_bus->deck ? printf("(Pietrowy: tak, ") : printf("(Pietrowy: nie, ");
		current_bus->air_cond ? printf("Klimatyzacja: tak, ") : printf("Klimatyzacja: nie, ");
		current_bus->wifi ? printf("Wi-Fi: tak)\n") : printf("Wi-Fi: nie)\n");

		current_bus = current_bus->next;				//przejscie do kolejnego autobusu
	}
	return bus_number;
}
int ShowRoutes(Body * bus_system)
{
	Route * current = bus_system->head;
	if (bus_system->head == NULL)				//sprawdza, czy istnieja jakiekolwiek trasy
	{
		puts("Brak dostepnych autobusow, wcisnij dowolny klawisz aby wrocic do menu.");
		_getch();
		return 0;
	}

	int route_number = 0;						//zmienna numerujaca trasy
	puts("Dostepne trasy:");
	while (current != NULL)					//petla wyswietlajaca trasy
	{
		route_number++;
		printf("\n%d. Z: %s Do: %s\n", route_number, current->from, current->to);
		current = current->next;
	}
	return route_number;
}
Route * PickRoute(Body * bus_system, int route_number)
{
	Route * current_route = bus_system->head;
	int choice = GetChoice(route_number);

	if (choice == 1)						//jezeli uzytkownik wybral trase nr 1, to funkcja zwraca wskaznik
		return current_route;

	else									//w przeciwnym razie trzeba wykonac petle choice razy
	{
		for (int i = 1; i < choice; i++)
			current_route = current_route->next;
		return current_route;
	}
}
void FreeMemory(Body * bus_system)
{
	Route * current_route = bus_system->head;
	Route * temp_route = NULL;
	while (current_route != NULL)			//petla zwalnia pamiec az do usuniecia ostatniego elementu
	{
		Bus * current_bus = current_route->main_bus;
		Bus * temp_bus = NULL;
		while (current_bus != NULL)			//usuwanie autobusow po kolei, do NULLa
		{
			temp_bus = current_bus;
			current_bus = current_bus->next;
			temp_bus->next = NULL;
			delete temp_bus;
		}
		current_route->main_bus = NULL;
		temp_route = current_route;
		current_route = current_route->next;
		temp_route->next = temp_route->prev = NULL;
		delete temp_route;
	}
	bus_system->head = bus_system->tail = NULL;
}