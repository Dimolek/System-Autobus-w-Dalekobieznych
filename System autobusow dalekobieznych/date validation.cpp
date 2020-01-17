#include "date validation.h"

bool IsYearLeap(int year)
{
	return ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0);		//rok przestepny
}
bool IsDateValid(tm newDate) //wyklucza nieistniejace daty
{
	if ((0 < newDate.tm_mday) && (newDate.tm_mday < 32) && (newDate.tm_mon > 0) && (newDate.tm_mon < 13))
	{
		if ((newDate.tm_mon == 4 || newDate.tm_mon == 6 || newDate.tm_mon == 9 || newDate.tm_mon == 11) && newDate.tm_mday > 30)
			return false;

		else if (IsYearLeap(newDate.tm_year) && newDate.tm_mon == 2 && newDate.tm_mday > 29)
			return false;

		else if (!IsYearLeap(newDate.tm_year) && newDate.tm_mon == 2 && newDate.tm_mday > 28)
			return false;

		else
			return true;
	}
	else
		return false;
}
bool IsDateLater(tm newDate, tm nextDate)	//polecenie mktime konwertuje strukture tm, ktora przechowuje date, tzn
{											//rok, dzien, miesiac + czas na zmienna typu time_t, ktora jest
	time_t new_time = mktime(&newDate);		//odpowiednikiem daty w jednej liczbie (liczba sekund od 1 stycznia 1970
	time_t next_time = mktime(&nextDate);	//00:00 UTC do wprowadzonej daty)

	return (new_time > next_time);			//zwraca true/false
}
bool IsDateLater(tm newDate)				//j/w, ale sprawdza czy podana date jest pozniejsza niz obecny czas
{
	time_t new_time = mktime(&newDate);
	time_t current_time = time(NULL);

	return (new_time > current_time);
}