#include "reservation.h"

void Reserve(Body * bus_system)
{
	if (bus_system->head == NULL) //przypadek, jezeli nie ma co zarezerwowac
	{
		puts("Brak dostepnych autobusow, wcisnij dowolny klawisz aby wrocic do menu.");
		_getch();
	}
	else
	{
		int route_number = ShowRoutes(bus_system);						//uzytkownik wybiera trase, w ktorej chce
		puts("\nPodaj numer trasy w ktorej chcesz zarezerwowac autobus:");//zarezerowac autobus, potem konkretny
		Route * current_route = PickRoute(bus_system, route_number);	//autobus
		PickBus(current_route, ShowBuses(current_route));
	}
}
void PickBus(Route * current_route, int bus_number)
{
	puts("\nPodaj numer autobusu w ktorym chcesz zarezerwowac miejsce:");
	Bus * current_bus = current_route->main_bus;
	int choice = GetChoice(bus_number);

	if (choice == 1)						//jezeli wybor == 1, to interesuje nas aktualny wskaznik
	{
		ShowReservations(current_bus);
		AddReservation(current_bus);
	}
	else									//w przeciwnym wypadku petla musi wykonac sie choice razy
	{
		for (int i = 1; i < choice; i++)
			current_bus = current_bus->next;
		ShowReservations(current_bus);
		AddReservation(current_bus);
	}
}
void ShowReservations(Bus * current_bus)
{
	system("cls");
	puts("Poziom 1:\n");
	for (int i = 1; i <= AMOUNT_OF_SEATS; i++)
	{
		if (current_bus->floor1[i - 1] == (int)'x')			//zarezerwowane miejsca maja kod znaku 'x'
			printf("|XX| ");
		else
			printf("|%02d| ", current_bus->floor1[i - 1]);
		if (i % 2 == 0)
		{
			if (i % 4 == 0)
				printf("\n");
			else
				printf(" \t");
		}
	}
	if (current_bus->deck)									//jezeli autobus jest pietrowy, to wyswietlane jest
	{														//tez pietro autobusu
		printf("\n\n");
		puts("Poziom 2:\n");
		for (int i = 1; i <= AMOUNT_OF_SEATS; i++)
		{
			if (current_bus->floor2[i - 1] == (int)'x')
				printf("|XX| ");
			else
				printf("|%02d| ", current_bus->floor2[i - 1]);
			if (i % 2 == 0)
			{
				if (i % 4 == 0)
					printf("\n");
				else
					printf(" \t");
			}
		}
	}
	puts("\n|XX| - miejsce zarezerwowane\n");
}
void AddReservation(Bus * current_bus)
{
	int seats, choice;

	if (current_bus->deck)
		seats = AMOUNT_OF_SEATS * 2;
	else
		seats = AMOUNT_OF_SEATS;

	puts("Czy chcesz dokonac rezerwacji? (Wcisnij t jesli tak, lub inny klawisz jesli nie)");
	while ((choice = _getch()) == 't' || choice == 'T')
	{
		puts("Podaj numer miejsce, ktore chcesz zarezerwowac:");
		while ((scanf("%d", &choice) != 1) || choice <= 0 || choice > seats)
		{
			puts("\nBledne znaki lub numer, sproboj ponownie.");
			while (getchar() != '\n')
				continue;
		}
		if (choice > AMOUNT_OF_SEATS)//jezeli wybor jest wiekszy od 40, to rezerwujemy miejsca na pietrze
			current_bus->floor2[choice - AMOUNT_OF_SEATS - 1] = (int)'x';
		else
			current_bus->floor1[choice - 1] = (int)'x';
		system("cls");
		ShowReservations(current_bus);

		puts("Czy chcesz zarezerwowac kolejne miejsce? (Wcisnij t jesli tak, lub inny klawisz jesli nie)");
	}
}