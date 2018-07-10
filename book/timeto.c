#include <stdio.h>
#include <time.h>

int main()
{
	int gettime(time_t*, time_t*);

	printf("Days to go from current date to\nRed Dead Redemption"
		" release is %d days.\n",
		gettime(NULL, NULL));
	return 0;
}

time_t setdate(struct tm *tmp, int day, int month, int year)
{
	tmp->tm_year = year-1900;
	tmp->tm_mon = month-1;
	tmp->tm_mday = day;
	return mktime(tmp);
}

int gettime(time_t *beg, time_t *end)
{
	struct tm *tmp;
	time_t now, then;

	/* get local time */
	now = time(NULL);
	tmp = localtime(&now);
	if (!tmp) {
		beg = NULL;
		end = NULL;
		return 0;
	}

	/* make time from above */
	then = setdate(tmp, 26, 10, 2018);
	if (beg != NULL)
		*beg = now;
	if (end != NULL)
		*end = then;

	return (int)(difftime(then, now) / (60*60*24));
}

