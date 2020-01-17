#include "removal.h"

void Delete(Body * bus_system)
{
	if (bus_system->head == NULL) //przypadek, gdy nie ma czego usunac
	{
		puts("Brak dostepnych autobusow, wcisnij dowolny klawisz aby wrocic do menu.");
		_getch();
	}
	else
	{
		Route * current_route;
		int choice, bus_number, route_number; //zmienne przechowujace wybor uzytkownika
		do
		{
			system("cls");
			route_number = ShowRoutes(bus_system);
			if (route_number == 0)	//przypadek, jezeli po usunieciu ostatniego autobusu uzytkownik nadal chce
				break;				//cos usunac

			current_route = PickRoute(bus_system, route_number); //wskaznik na trase wybrana przez uzytkownika
			bus_number = ShowBuses(current_route);
			puts("\nCzy na pewno chcesz usunac autobus? (Wcisnij t jesli tak, lub inny klawisz jesli nie)");
			if ((choice = _getch()) != 't' && choice != 'T')
				break;

			puts("Podaj numer autobusu, ktory chcesz usunac:");
			DeleteBus(bus_system, current_route, bus_number);
			puts("\nAutobus usunieto pomyslnie!\n\n"
				"Czy chcesz usunac kolejny autobus? (Wcisnij t jesli tak, lub inny klawisz jesli nie)");
		} while ((choice = _getch()) == 't' || choice == 'T');
	}
}
void DeleteBus(Body * bus_system, Route * current_route, int bus_number)
{
	Bus * current_bus = current_route->main_bus;
	Bus * previous_bus = NULL;
	int choice = GetChoice(bus_number);

	current_route->bus_counter--;
	if (choice == 1)			//przypadek usuwania main_busa
	{
		if (current_bus->next == NULL) //jezeli w trasie jest tylko jeden autobus, usuwany jest bus + cala trasa
		{
			delete current_bus;
			DeleteRoute(bus_system, current_route);
		}
		else							//w przeciwnym wypadku nastepny autobus zostaje main_busem
		{
			current_route->main_bus = current_bus->next;
			delete current_bus;
		}
	}
	else									//jezeli nie jest usuwaniy main_bus, to petla przechodzi choice razy,
	{										//laczy sasiadujace autobusy i usuwa wybrany
		for (int i = 1; i < choice; i++)
		{
			previous_bus = current_bus;
			current_bus = current_bus->next;
		}
		previous_bus->next = current_bus->next;
		delete current_bus;
	}
}
void DeleteRoute(Body * bus_system, Route * current_route)
{
	if (current_route == bus_system->head && bus_system->head == bus_system->tail)
	{  //przypadek, jezeli istnieje tylko jedna trasa
		current_route->main_bus = NULL;
		delete current_route;
		bus_system->head = bus_system->tail = NULL;
	}
	else if (current_route == bus_system->head) //przypadek, w ktorym usuwana trasa jest glowa listy tras
	{
		current_route->main_bus = NULL;
		bus_system->head = current_route->next;
		current_route->next->prev = NULL;
		delete current_route;
	}
	else if (current_route == bus_system->tail) //jezeli usuwana trasa jest ogonem listy tras
	{
		current_route->main_bus = NULL;
		bus_system->tail = current_route->prev;
		current_route->prev->next = NULL;
		delete current_route;
	}
	else										//jezeli trasa jest w srodku
	{
		current_route->main_bus = NULL;
		current_route->prev->next = current_route->next;
		current_route->next->prev = current_route->prev;
		delete current_route;
	}
}