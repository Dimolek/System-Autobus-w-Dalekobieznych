#include "general.h"
#include "file operations.h"
#include "item addition.h"
#include "removal.h"
#include "reservation.h"

int main()
{
	Body bus_system;
	bus_system.head = bus_system.tail = NULL;
	char choice;

	ReadFile(&bus_system);
	do
	{
		puts("================================================================================"
			"=======================S Y S T E M   R E Z E R W A C J I========================"
			"================A U T O B U S O W   D A L E K O B I E Z N Y C H================="
			"================================================================================"
			"\n"
			"1 - D O D A J   A U T O B U S\n\n"
			"2 - U S U N   A U T O B U S\n\n"
			"3 - R E Z E R W U J\n\n"
			"k - Z A K O N C Z   P R O G R A M");

		choice = _getch();
		switch (choice)
		{
		case '1':
			system("cls");
			ChooseRoute(&bus_system);
			break;
		case '2':
			system("cls");
			Delete(&bus_system);
			break;
		case '3':
			system("cls");
			Reserve(&bus_system);
			break;
		default:
			break;
		}
		system("cls");
	} while (choice != 'k');

	SaveToFile(bus_system);
	FreeMemory(&bus_system);
	return 0;
}