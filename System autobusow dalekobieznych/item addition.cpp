#include "item addition.h"
#include "date validation.h"

void ChooseRoute(Body * bus_system)
{
	Route * newRoute = new Route;			//dynamiczna alokacja pamieci dla nowej trasy
	ChooseCities(newRoute);

	if (bus_system->head == NULL && bus_system->tail == NULL) //warunek, jezeli nie ma tras
	{
		bus_system->head = newRoute;				//pierwsza trasa jest jednoczesnie glowa i ogonem
		bus_system->tail = newRoute;
		newRoute->prev = newRoute->next = NULL;
		newRoute->main_bus = NULL;
		AddBus(newRoute);
	}
	else
	{
		Route * current = bus_system->head;			//wskaznik pomocniczy na glowe listy tras
		while (current != NULL)
		{
			if ((strcmp(current->from, newRoute->from) != 0) || (strcmp(current->to, newRoute->to) != 0))
				current = current->next;	//if sprawdza, czy taka sama trasa juz nie istnieje
			else
			{
				AddBus(current);
				delete newRoute;			//usuniecie niepotrzebnie zaalokowanej pamieci w przypadku, gdy
				break;						//nie musimy tworzyc nowej trasy
			}
		}
		if (current == NULL)					//wybrana trasa nie istnieje, tworzymy nowa i dodajemy ja
		{										//na poczatek, tzn ustawiamy na nia glowe i laczymy z pozostalymi
			newRoute->next = bus_system->head;
			newRoute->main_bus = NULL;
			bus_system->head->prev = newRoute;
			bus_system->head = newRoute;
			bus_system->head->prev = NULL;
			AddBus(newRoute);
		}
	}
}
void ChooseCities(Route * newRoute)
{
	int city_from, city_to;
	char * cities[AMOUNT_OF_CITIES] = { "Bialystok", "Bydgoszcz", "Czestochowa", "Gdansk", "Gorzow Wlkp",
		"Katowice", "Kielce", "Krakow", "Lublin", "Olsztyn", "Opole", "Ostrowiec Sw",
		"Ostroda", "Poznan", "Radom", "Rzeszow", "Szczecin", "Torun", "Warszawa",
		"Wroclaw", "Zakopane", "Lodz" };

	for (int i = 0; i < AMOUNT_OF_CITIES; ++i)		//wyswietlenie dostepnych miast
	{
		if (i % 2 == 0)
			printf("\n");
		printf("%d - %s		", i + 1, cities[i]);
	}

	while (true)
	{
		puts("\n\nPodaj numer miasta z ktorego chcesz wyruszyc:");
		while (scanf("%d", &city_from) != 1 || city_from <= 0 || city_from > AMOUNT_OF_CITIES)
		{		//zabezpieczenie przed dodaniem litery/nieprawidlowego numeru
			puts("Bledny znak, sprobuj ponownie.");
			while (getchar() != '\n')
				continue;
			continue;
		}
		puts("Podaj numer miasta docelowego:");
		while (scanf("%d", &city_to) != 1 || city_to <= 0 || city_to > AMOUNT_OF_CITIES)
		{		//zabezpieczenie przed dodaniem litery/nieprawidlowego numeru
			puts("Bledny znak, sprobuj ponownie.");
			while (getchar() != '\n')
				continue;
			continue;
		}
		if (city_from == city_to) //miasto "z" i "do" nie moze byc takie samo
			puts("Podales 2 razy to samo miasto, wybierz trase ponownie.");
		else break;
	}
	strcpy(newRoute->from, cities[city_from - 1]);		//wpisanie wybranych miast do zmiennych w strukturze trasa
	strcpy(newRoute->to, cities[city_to - 1]);
	system("cls");
}
void AddBus(Route * current_route)
{
	Bus * newBus = new Bus;					//dynamiczna alokacja pamieci dla nowego autobusu
	AddDate(newBus);
	SetBusOptions(newBus);

	if (current_route->main_bus == NULL)		//warunek, gdy nie ma zadnego autobusu w liscie
	{
		current_route->main_bus = newBus;
		newBus->next = NULL;
		current_route->bus_counter++;
	}
	else									//przypadek, gdy jakis autobus jus istnieje
	{
		if (!IsDateLater(newBus->date, current_route->main_bus->date))
		{	//jezeli nowy autobus jest wczesniej od pierwszego autobusu, to staje sie main_busem
			newBus->next = current_route->main_bus;
			current_route->main_bus = newBus;
			current_route->bus_counter++;
		}
		else	//jezeli nie, to musimy przeszukac liste i go umiejscowic
		{
			Bus * current = current_route->main_bus;	//pomocniczy wskaznik na pierwszy autobus
			Bus * temp = NULL;
			current_route->bus_counter++;
			while (current != NULL)			//petla sprawdza, gdzie umiejscowic autobus
			{
				if (IsDateLater(newBus->date, current->date))	//jezeli nowa data jest pozniej niz data main_busa
				{												//to wskaznik przechodzi na kolejny autobus
					temp = current;								//i znowu dokonywane jest porownanie, nowy autobus
					current = current->next;					//dodawany jest przed pierwszym autobusem, ktory
				}												//jest od niego pozniej
				else
				{
					newBus->next = temp->next;
					temp->next = newBus;
					break;
				}
			}
			if (current == NULL)				//jezeli nie ma pozniejszych autobusow, to nowy dodawany jest
			{									//na koncu
				newBus->next = temp->next;
				temp->next = newBus;
			}
		}
	}
	system("cls");
	puts("Pomyslnie dodano autobus!\n"
		"Wcisnij dowolny klawisz aby wrocic do menu.");
	_getch();
}
void AddTime(tm * newDate)
{
	puts("Podaj czas w formacie gg mm");

	while (true)
	{
		if (scanf("%d%d", &newDate->tm_hour, &newDate->tm_min) == 2) //wczytanie godziny i minuty odjazdu,
		{													//zabezpieczenie przed wprowadzeniem liter
			if ((newDate->tm_hour < 0) || (newDate->tm_hour > 23) || (newDate->tm_min < 0) || (newDate->tm_min > 59))
			{														//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
				puts("\nBledne dane lub znaki, sproboj ponownie.");	//warunek poprawnosci czasu
				continue;
			}
			else								//warunek konca petli; jezeli wprowadzone dane sa poprawne, to
				break;							//funkcja konczy sie
		}
		puts("\nBledne znaki, sproboj ponownie.");
		while (getchar() != '\n')				//powrot do wyboru po wcisnieciu litery zamiast liczby
			continue;
	}
}
void AddDate(Bus * newBus)
{
	while (true)
	{
		puts("Podaj date w formacie dd mm rrrr");
		if (scanf("%d%d%d", &newBus->date.tm_mday, &newBus->date.tm_mon, &newBus->date.tm_year) == 3)
		{																//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
			if (!IsDateValid(newBus->date) || newBus->date.tm_year >= 3000)//wczytywanie daty + zabezpieczenie
			{															//przed wprowadzaniem liter + rok
				puts("Bledne dane lub znaki, sproboj ponownie.");
				continue;
			}
		}
		else
		{
			puts("Bledne znaki, sproboj ponownie.");
			while (getchar() != '\n')			//powrot do wyboru po wcisnieciu litery zamiast liczby
				continue;
			continue;
		}

		newBus->date.tm_year -= 1900;		//tm_year to ilosc lat od 1900, dlatego musimy to odjac
		newBus->date.tm_mon -= 1;			//tm_month zawiera miesiace 0-11
		newBus->date.tm_isdst = -1;			//czas letni
		newBus->date.tm_sec = 0;

		AddTime(&newBus->date);

		if (IsDateLater(newBus->date))		//nie mozna podac daty wczesniejszej niz obecna
			break;
		puts("Podaj pozniejsza date i czas niz obecna.");
	}
}
void SetBusOptions(Bus * newBus)
{
	system("cls");
	int choice;

	puts("Czy autobus ma byc pietrowy? (Wcisnij t jesli tak, lub inny klawisz jesli nie)");
	if ((choice = _getch()) == 't' || choice == 'T')
		newBus->deck = true;
	else
		newBus->deck = false;

	system("cls");
	puts("Czy autobus ma posiadac klimatyzacje? (Wcisnij t jesli tak, lub inny klawisz jesli nie)");
	if ((choice = _getch()) == 't' || choice == 'T')
		newBus->air_cond = true;
	else
		newBus->air_cond = false;
	system("cls");
	puts("Czy autobus ma posiadac Wi-Fi? (Wcisnij t jesli tak, lub inny klawisz jesli nie)");
	if ((choice = _getch()) == 't' || choice == 'T')
		newBus->wifi = true;
	else
		newBus->wifi = false;

	for (int i = 0; i < AMOUNT_OF_SEATS; i++)
		newBus->floor1[i] = i + 1;

	if (newBus->deck)
	{
		for (int i = 0; i < AMOUNT_OF_SEATS; i++)
			newBus->floor2[i] = i + AMOUNT_OF_SEATS + 1;
	}
}