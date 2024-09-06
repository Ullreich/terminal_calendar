# Set the project name
project (customutils)

add_library(${PROJECT_NAME} src/customutils.c)
add_library(sub::customutils ALIAS ${PROJECT_NAME})

target_include_directories(${PROJECT_NAME}
    INTERFACE
        ${PROJECT_SOURCE_DIR}/include
)
