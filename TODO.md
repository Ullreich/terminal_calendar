# TODO
* refactor stuff:
    * [ ] rename variables and structs and all to something sane
    * [ ] refactor so that you select cellsize not table dims
    * [ ] have all the X and Y vars scrolls be the same?
* [ ] fix/do error handling of: no colors in terminal, no ical file added and more
* [ ] fix char/const char issue
* [ ] look at guards in headerfiles
* [ ] screen scrolling automatical when you move to cells past end of screen 
* [ ] memory safety and stuff
* [ ] unit tests (see cmake)
* [ ] add commandline flags for: fps, size (dont forget string sanitization)
* [ ] vim keybinds
* [ ] readme
* [ ] make way of interacting with cells
* [ ] implement icalendar parsing with libical
* [ ] multiple calendars
* [ ] multiple entries in one cell (perhaps indicate multiple entries through arrows? and only render biggest entry?)
* [ ] mouse support: select cell by clicking

## cmake
* [ ] what do INTERFACE PUBLIC and PRIVATE do? look into when to use which keywords
* [ ] test if ncurses and libical are installed
* [ ] unittests?
* [ ] compiler flags and optimization?
* [ ] multi-plattform building?

## libical stuff
* [ ] doubly linked lists (containing arrays of fixed size?) to store calendar entries? that way easy to append/prepend.

# ideas
* [ ] find good name for project
* [ ] refactor so that not made up of fixed-sized cells but rather of cells based on time events in icalendar? Or perhaps multiple modes? 
* [ ] add month/day view
