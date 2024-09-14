project (libical_components)

include_directories(include)

add_library(${PROJECT_NAME} SHARED
  src/libical_utils.c)
add_library(sub::libical_components ALIAS ${PROJECT_NAME})

target_include_directories( ${PROJECT_NAME}
    INTERFACE ${PROJECT_SOURCE_DIR}/include
)

# include customutils
target_link_libraries(${PROJECT_NAME}
    PUBLIC sub::customutils
    PUBLIC sub::TUI_components
)
