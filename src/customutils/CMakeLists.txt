# Set the project name
project (customutils)

include_directories(include)

add_library(${PROJECT_NAME} SHARED src/customutils.c)
add_library(sub::customutils ALIAS ${PROJECT_NAME})

target_include_directories(${PROJECT_NAME}
    INTERFACE ${PROJECT_SOURCE_DIR}/include
)
