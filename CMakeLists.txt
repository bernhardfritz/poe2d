cmake_minimum_required(VERSION 3.1)
project(poe2d)
set (CMAKE_CXX_STANDARD 11)

add_subdirectory(lib/libxd)

add_executable(${PROJECT_NAME} src/sketch.cpp)

target_sources(${PROJECT_NAME}
    PUBLIC src/sketch.cpp
)
target_include_directories(${PROJECT_NAME}
    PUBLIC include
)
target_link_libraries(${PROJECT_NAME}
    xd
)
set_target_properties(${PROJECT_NAME}
    PROPERTIES OUTPUT_NAME sketch
)
