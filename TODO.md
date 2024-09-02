# TODO
* refactor stuff:
    * [ ] rename variables and structs and all to something sane
    * [ ] sane file hierarchy
    * [ ] refactor so that you select cellsize not table dims
    * [ ] have all the X and Y vars scrolls be the same?
* [ ] screen scrolling automatical when you move to cells past end of screen 
* [ ] memory safety and stuff
* [ ] unit tests
* [ ] add commandline flags for: fps, size (dont forget string sanitization)
* [ ] vim keybinds
* [ ] cmake file to compile (dont forget dependencies)
* [ ] readme
* [ ] make way of interacting with cells
* [ ] implement icalendar parsing with libical
* [ ] multiple calendars
* [ ] multiple entries in one cell (perhaps indicate multiple entries through arrows? and only render biggest entry?)
* [ ] mouse support: select cell by clicking

## libical stuff
* [ ] doubly linked lists (containing arrays of fixed size?) to store calendar entries? that way easy to append/prepend.

# ideas
* [ ] find good name for project
* [ ] refactor so that not made up of fixed-sized cells but rather of cells based on time events in icalendar? Or perhaps multiple modes? 
* [ ] add month/day view
