cmake_minimum_required(VERSION 3.22)
project(libThinkGearCpp VERSION 1.0.0 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)

option(BUILD_SHARED "Whether to build the shared library" ON)
option(BUILD_STATIC "Whether to build the static library" ON)
option(COMPILE_PROJECTS "Build test" OFF)

include_directories(src/parser)
include_directories(src/signaler)
include_directories(src/thinkgear)


FILE(GLOB THINKGEAR_SOURCES 
          src/thinkgear/*.cpp
          src/signaler/*.cpp
          src/parser/*.cpp
    )

set (THINKGEAR_HEADERS
     src/thinkgear/ThinkGear.h
     src/thinkgear/thinkgear_c.h
     src/parser/ThinkGearStreamParser.h
     src/parser/ThinkGearValueHandler.h
     src/parser/TGData.h
     src/parser/TGEnums.h
     src/signaler/ThinkGearEvent.h
     src/signaler/ThinkGearEvents.h
     src/signaler/ThinkGearSignaler.h
     src/signaler/TGEegData.h
     )

if(BUILD_STATIC)
    message("Build static library")
    add_library (thinkgearcpp STATIC ${THINKGEAR_SOURCES})    
    target_include_directories(thinkgearcpp PRIVATE include PUBLIC $<INSTALL_INTERFACE:include>)
    set_target_properties(thinkgearcpp PROPERTIES PUBLIC_HEADER "${THINKGEAR_HEADERS}")
    list(APPEND THINKGEAR_TARGETS thinkgearcpp)
endif()
if(BUILD_SHARED)
    message("Build shared library")
    add_compile_definitions(EXPORT)
    add_library (thinkgearcpp_SHARED SHARED ${THINKGEAR_SOURCES})
    set_target_properties(thinkgearcpp_SHARED PROPERTIES OUTPUT_NAME thinkgearcpp)
    target_include_directories(thinkgearcpp_SHARED PRIVATE include PUBLIC $<INSTALL_INTERFACE:include>)
    set_target_properties(thinkgearcpp_SHARED PROPERTIES PUBLIC_HEADER "${THINKGEAR_HEADERS}")
    list(APPEND THINKGEAR_TARGETS thinkgearcpp_SHARED)
endif()

install(FILES ${THINKGEAR_HEADERS} DESTINATION include/thinkgearcpp)
install(TARGETS ${THINKGEAR_TARGETS} EXPORT thinkgearcpp-config
	LIBRARY DESTINATION lib
	ARCHIVE DESTINATION lib
	RUNTIME DESTINATION bin
	PUBLIC_HEADER DESTINATION include/thinkgearcpp)

install(EXPORT thinkgearcpp-config DESTINATION lib/cmake/thinkgearcpp)

#if (COMPILE_PROJECTS)
#    message("COMPILE PROJECTS!")
#    add_subdirectory(projects/parse_test)
#    add_subdirectory(projects/device_test)
#endif()
