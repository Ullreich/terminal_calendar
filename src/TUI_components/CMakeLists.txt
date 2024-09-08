# Set the project name
project (TUI_components)

# this isnt needed but i dont know why
include_directories(include)

add_library(${PROJECT_NAME} SHARED
  src/days.c
  src/hours.c
  src/week.c)
add_library(sub::TUI_components ALIAS ${PROJECT_NAME})

target_include_directories( ${PROJECT_NAME}
    INTERFACE ${PROJECT_SOURCE_DIR}/include
)

# include customutils
target_link_libraries(${PROJECT_NAME}
    PUBLIC sub::customutils
)
