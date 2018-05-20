#include "common/helper.h"

#define MAXYEARS	2
#define MAXDAYS		13

static char daytab[MAXYEARS][MAXDAYS] = {
	{0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
	{0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
};

/* day_of_year:  set day of year from month & day */
int day_of_year(int year, int month, int day)
{
	char *p;
	int i, leap;

	if (year < 1 || month < 1 || month > 12 || day < 1)
		return -1;
	leap = year%4 == 0 && year%100 != 0 || year%400 == 0;
	p = &daytab[leap][1];
	for (i = 0; i < month; i++)
		day += *p++;
	return day;
}

/* month_day:  set month, day from day of year */
int month_day(int year, int yearday, int *pmonth, int *pday)
{
	char *p;
	int i, leap;

	if (year < 1752 || yearday < 1)
		return -1;
	leap = year%4 == 0 && year%100 != 0 || year%400 == 0;
	p = &daytab[leap][1];
	for (i = 0; yearday > *p; i++)
		yearday -= *p++;
	*pmonth = i;
	*pday = yearday;
	return 0;
}

/* month_name:  return name of n-th month */
char *month_name(int n)
{
	static char *name[] = {
		"Illegal month",
		"January", "February", "March",
		"April", "May", "June", "July",
		"August", "September", "October",
		"November", "December"
	};
	return (n < 1 || n > 12) ? name[0] : name[n];
}

int main(void)
{
	int mon, day;

	day = day_of_year(1988, 3, 22);
	month_day(1988, day, &mon, &day);
	printf("Month: %s\nDay: %d\n", month_name(mon), day);
	return 0;
}
