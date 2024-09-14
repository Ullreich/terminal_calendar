cmake_minimum_required(VERSION 3.25) # TODO: maybe be a little more relaxed, test if it builds with older versions
project(terminal_calendar)

# build the libraries
add_subdirectory(src/customutils)
add_subdirectory(src/libical_components)
add_subdirectory(src/TUI_components)

add_executable(${PROJECT_NAME} main.c)

# add needed local libs that we just built
target_link_libraries(${PROJECT_NAME}
    # sub::customutils # already linked in TUI_components
    sub::TUI_components
    sub::libical_components
)

# This loads the external libs. 
# TODO: check if they are installed
target_link_libraries(${PROJECT_NAME} libical.so.3)
target_link_libraries(${PROJECT_NAME} ncurses)
