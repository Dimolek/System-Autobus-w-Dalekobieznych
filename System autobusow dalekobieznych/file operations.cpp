#include "file operations.h"
#include "general.h"

void ReadFile(Body * bus_system)
{
	FILE * fp;												//wskaznik na typ FILE
	if ((fp = fopen("data.dat", "rb")) != NULL)					//otwarcie pliku, przy nieudanej probie program
	{															//pomija wczytywanie pliku
		if (!feof(fp))										//sprawdzenie, czy wskaznik nie znajduje sie na koncu pliku
		{
			Route * newRoute = new Route;						//dynamiczna alokacja pamieci
			if (fread(newRoute, sizeof(Route), 1, fp) == 1) //wczytanie calej struktury(trasy), jezeli w pliku znajduja
			{															//sie smieci, to program zaprzestanie wczytywania
				bus_system->head = bus_system->tail = newRoute;		//przypisanie nowej glowy listy tras
				bus_system->head->prev = NULL;
			}
			else delete newRoute;
		}
		Route * current_route = bus_system->head;			//wskaznik pomocniczy na trase
		while (!feof(fp))										//petla dzialajaca dopoki nie zostanie wykryty
		{														//koniec pliku
			Bus * current_bus = NULL;						//wskaznik pomocniczy na autobus
			for (int i = 0; i < current_route->bus_counter; i++)	//petla dodajaca bus_counter autobusow
			{
				Bus * newBus = new Bus;							//dynamiczna alokacja pamieci
				fread(newBus, sizeof(Bus), 1, fp);			//wczytanie calej struktury(autobusu)
				newBus->next = NULL;
				if (i == 0)									//pierwszy bus musi byc glownym autobusem listy
				{											//tzn. main_bus
					current_route->main_bus = newBus;
					current_bus = newBus;					//ustawienie wskaznika pomocniczego na nowo zaalokowany
				}											//bus
				else
				{
					current_bus->next = newBus;				// "przewijanie" autobusow
					current_bus = current_bus->next;
				}
			}
			Route * newRoute = new Route;
			if (fread(newRoute, sizeof(Route), 1, fp) == 1)	//wczytanie kolejnej trasy, jesli nie
			{																//znajduje jej w pliku, to fread nie
				current_route->next = newRoute;								//zwroci 1 i zakonczy wczytywanie
				current_route->next->prev = current_route;
				bus_system->tail = newRoute;
				current_route = current_route->next;
				current_route->next = NULL;
			}
			else delete newRoute;							//usuniecie zaalokowanej pamieci, jesli trasa zostala blednie
		}													//wczytana
		fclose(fp);												//zamkniecie pliku
	}
}
void SaveToFile(Body bus_system)
{
	Route * current_route = bus_system.head;				//wskaznik na glowe listy tras(listy list)

		FILE * fp;											//wskaznik na typ FILE
		if ((fp = fopen("data.dat", "wb")) == NULL)			//otwarcie pliku, nieudane otwarcie zamyka program
		{
			puts("Nie moge utworzyc pliku data.dat. Nacisnij dowolny klawisz.");
			_getch();
			exit(EXIT_FAILURE);
		}
		while (current_route != NULL)							//sprawdzenie, czy istnieje cokolwiek do zapisu
		{														//i ewentualnie przejscie do zapisu kolejnej trasy
			Bus * current_bus = current_route->main_bus;	//wskaznik na pierwszy autobus w liscie

			fwrite(current_route, sizeof(Route), 1, fp);	//zapisanie calej struktury(trasy) do pliku
			while (current_bus != NULL)							//warunek kiedy skonczyc zapisywanie autobusow
			{													//i przejsc do kolejnej trasy
				fwrite(current_bus, sizeof(Bus), 1, fp);	//zapisanie calej struktury(autobusu) do pliku
				current_bus = current_bus->next;				//przejscie do kolejnego autobusu
			}
			current_route = current_route->next;			//przejscie do kolejnej trasy
		}
		fclose(fp);											//zamkniecie pliku
}
