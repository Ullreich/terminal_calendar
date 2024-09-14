#ifndef LIBICAL_UTILS   /* Include guard */
#define LIBICAL_UTILS
#include <TUI_aggregator.h>
#include <libical/ical.h>

char* readStream(char *s, size_t size, void *d);

icaltimetype componentToicaltimetype(icalcomponent *c, bool start);

const char* componentToSummaryText(icalcomponent *c);

int mondayFirstDay(int weekday);

void timetableWeekFill(struct Week *w, char *file);


void timetableWeekWrite(struct Week *w);

#endif
