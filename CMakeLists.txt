cmake_minimum_required(VERSION 3.25.1) # TODO: maybe be a little more relaxed, test if it builds with older versions
project(terminal_calendar)

# This loads the external libs. 
# TODO: check if they are installed
# target_link_libraries(${PROJECT_NAME} libical.so.3)
# target_link_libraries(${PROJECT_NAME} ncurses)

include_directories(src/customutils)
include_directories(src/TUI_components)

add_executable(${PROJECT_NAME} main.c)

