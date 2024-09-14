#include <libical_utils.h>
#include <customutils.h>

char* readStream(char *s, size_t size, void *d) {
  return fgets(s, size, (FILE*)d);
}

icaltimetype componentToicaltimetype(icalcomponent *c, bool start) {
  icalproperty *prop = start ? icalcomponent_get_first_property(c, ICAL_DTSTART_PROPERTY) : icalcomponent_get_first_property(c, ICAL_DTEND_PROPERTY);
  icalvalue *iv = icalproperty_get_value(prop);
  const char *time = icalvalue_as_ical_string(iv);
  icaltimetype it = icaltime_from_string(time);

  return it;
}

const char* componentToSummaryText(icalcomponent *c) {
  icalproperty *prop = icalcomponent_get_first_property(c, ICAL_SUMMARY_PROPERTY);
  icalvalue *iv = icalproperty_get_value(prop);
  char* summary = icalvalue_as_ical_string(iv);
  //const char *summary = icalproperty_as_ical_string(icalcomponent_get_first_property(c, ICAL_SUMMARY_PROPERTY));
  return summary;
}

int mondayFirstDay(int weekday) {
  return (weekday-2)%7;
}

void timetableWeekFill(struct Week *w, char *file) {
  char *line;
  icalcomponent *component;
  icalparser *parser = icalparser_new();
  icalcomponent *c;
  icalproperty *prop;
  icalproperty *title;

  // open file
  FILE* stream = fopen(file, "r");
  
  // associate the FILE with the parser so that read_stream
  // will have access to it
  icalparser_set_gen_data(parser, stream);
  component = icalparser_parse(parser, readStream);

  // iterate through ical file and fill week correspondingly
  for (c = icalcomponent_get_first_component(component, ICAL_VEVENT_COMPONENT);
  c != 0;
  c = icalcomponent_get_next_component(component, ICAL_VEVENT_COMPONENT)) {
    icaltimetype start = componentToicaltimetype(c, true);
    icaltimetype end = componentToicaltimetype(c, false);
    int weekday = mondayFirstDay(icaltime_day_of_week(start));// TODO: what if event is over multiple days or even weeks
    int startHour = start.hour;
    int endHour = end.hour;
  
    // fill the appropriate cell with component
    for (int i=startHour; i<endHour; ++i) {
      w->cellsContent[weekday][i-8] = c;
    }
  }
}

void timetableWeekWrite(struct Week *w) {
  for (int d=0; d<(w->days); ++d) {
    for (int h=0; h<(w->hours); ++h) {
      // write summary of event to cell
      if (w->cellsContent[d][h]) { // make sure cell isnt empty 
        char *text = componentToSummaryText(w->cellsContent[d][h]);
        updateCell(w, d, h, text, false);
      }
    }
  }
  refreshCells(w);
}
