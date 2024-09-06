# Set the project name
project (TUI_components)

# Add a library with the above sources
add_library(${PROJECT_NAME} src/days.c src/hours.c src/week.c)
add_library(sub::TUI_components ALIAS ${PROJECT_NAME})

target_include_directories( ${PROJECT_NAME}
    PUBLIC ${PROJECT_SOURCE_DIR}/include
)
