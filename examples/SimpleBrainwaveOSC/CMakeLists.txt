cmake_minimum_required(VERSION 3.22)
project(simpleBrainwaveOSC VERSION 1.0.0 LANGUAGES CXX C)
list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")

find_package(Boost REQUIRED)
find_package(LIBLO REQUIRED)
find_package(thinkgearcpp REQUIRED)

set (SOURCES
     main.cpp
     TG_OSCSender.cpp
    )
add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} PRIVATE lo)
if (BUILD_STATIC)
    target_link_libraries(${PROJECT_NAME} PUBLIC thinkgearcpp)
else()
    target_link_libraries(${PROJECT_NAME} PUBLIC thinkgearcpp_SHARED)
endif()

target_link_libraries(${PROJECT_NAME} PUBLIC Boost::boost)

install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION bin)
