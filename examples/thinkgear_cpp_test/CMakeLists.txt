cmake_minimum_required(VERSION 3.22)
project(thinkgear_cpp_test VERSION 1.0.0 LANGUAGES CXX C)
set(CMAKE_CXX_STANDARD 20)
find_package(thinkgearcpp)
set(SOURCES
        main.cpp
        ThinkGearMessages.cpp
        ThinkGearMonitor.cpp
    )
add_executable(${PROJECT_NAME} ${SOURCES})
if (BUILD_STATIC)
    target_link_libraries(${PROJECT_NAME} PUBLIC thinkgearcpp)
else()
    target_link_libraries(${PROJECT_NAME} PUBLIC thinkgearcpp_SHARED)
endif()
install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION bin)
