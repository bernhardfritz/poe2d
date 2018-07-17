cmake_minimum_required(VERSION 3.1)
project(poe2d)
set (CMAKE_CXX_STANDARD 11)

set(TINYXML2_INCLUDE_DIR ../tinyxml2)
set(TINYXML2_LIBRARIES tinyxml2)

set(BUILD_SHARED_LIBS ON CACHE BOOL "" FORCE)
set(BUILD_STATIC_LIBS OFF CACHE BOOL "" FORCE)
set(BUILD_DOCUMENTATION OFF CACHE BOOL "" FORCE)
set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory(lib/libxd)
add_subdirectory(lib/tinyxml2)
add_subdirectory(lib/tmxparser)

add_executable(${PROJECT_NAME} src/sketch.cpp)

target_sources(${PROJECT_NAME}
    PUBLIC src/sketch.cpp
    PUBLIC src/animation.cpp
    PUBLIC src/sprite.cpp
    PUBLIC src/spritesheet.cpp
    PUBLIC src/camera.cpp
    PUBLIC src/tmxmapwrapper.cpp
    PUBLIC src/character.cpp
    PUBLIC src/movement.cpp
)
target_include_directories(${PROJECT_NAME}
    PUBLIC include
    PUBLIC ${CMAKE_CURRENT_BINARY_DIR}/lib/tmxparser
    PUBLIC lib/tmxparser/src
)
target_link_libraries(${PROJECT_NAME}
    xd
    tmxparser
)
set_target_properties(${PROJECT_NAME}
    PROPERTIES OUTPUT_NAME sketch
)

file (COPY ${CMAKE_CURRENT_SOURCE_DIR}/resources DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
