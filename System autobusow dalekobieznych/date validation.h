#ifndef _DATE_VAL_H_
#define _DATE_VAL_H_

#include "general.h"

bool IsYearLeap(int year);						//sprawdzenie, czy rok jest przestepny
bool IsDateValid(tm newDate);					//-    ||   -, czy data jest poprawna
bool IsDateLater(tm newDate, tm nextDate);		//-    ||   -, czy podana data jest od poprzedniej
bool IsDateLater(tm newDate);					//-    ||   -, czy podana data jest pozniej od obecnej

#endif