cmake_minimum_required(VERSION 3.2)


# Project Configuration

# Project name
set(PNAME "Browars")

# Minimum SFML version
set(SFML_VERSION 2.3)

set(SFML_COMPONENTS audio graphics window system)

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

project(${PNAME})
find_package(SFML ${SFML_VERSION} COMPONENTS ${SFML_COMPONENTS} REQUIRED)

add_library(sfeMovie SHARED IMPORTED)
set_target_properties( sfeMovie PROPERTIES IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/lib/sfeMovie/build/bin/libsfeMovie.so )

set (SOURCES
    "${CMAKE_SOURCE_DIR}/src/game_loop.cpp"
    "${CMAKE_SOURCE_DIR}/src/gui/gui.cpp"
    "${CMAKE_SOURCE_DIR}/src/init.cpp"
    "${CMAKE_SOURCE_DIR}/src/button.cpp"
)

set (GUI_SOURCES
    "${CMAKE_SOURCE_DIR}/src/gui/intro.cpp"
    "${CMAKE_SOURCE_DIR}/src/gui/main_menu.cpp"
    "${CMAKE_SOURCE_DIR}/src/gui/not_supported.cpp"
    "${CMAKE_SOURCE_DIR}/src/gui/singleplayer.cpp"
    "${CMAKE_SOURCE_DIR}/src/gui/select_region.cpp"
    "${CMAKE_SOURCE_DIR}/src/gui/select_character.cpp"
)

file(GLOB GUI_SOURCES "src/gui/*.cpp")
add_executable(${PNAME} "${CMAKE_SOURCE_DIR}/main.cpp" ${SOURCES} ${GUI_SOURCES})

target_include_directories(
    ${PNAME} PUBLIC
    ${SFML_INCLUDE_DIR}
    "${CMAKE_SOURCE_DIR}/include"
    "${CMAKE_SOURCE_DIR}/lib/sfeMovie/include"
)

target_link_libraries(${PNAME} ${SFML_LIBRARIES} ${SFML_DEPENDENCIES} sfeMovie)

set_property(TARGET ${PNAME} PROPERTY CXX_STANDARD 11) # Use C++11

if(NOT WIN32 OR MINGW)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall") # Show all warnings for GCC
endif()



#cmake_minimum_required( VERSION 3.0 )
#
#project( "Browars" )
#
#add_library( sfeMovie SHARED IMPORTED )
#
#set_target_properties( sfeMovie PROPERTIES IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/lib/sfeMovie/build/bin/libsfeMovie.so )
#
#set (SRCS
#    "${CMAKE_SOURCE_DIR}/src/game_loop.cpp"
#    "${CMAKE_SOURCE_DIR}/src/gui/gui.cpp"
#    "${CMAKE_SOURCE_DIR}/src/init.cpp"
#    "${CMAKE_SOURCE_DIR}/src/button.cpp"
#    "${CMAKE_SOURCE_DIR}/src/gui/intro.cpp"
#    "${CMAKE_SOURCE_DIR}/src/gui/main_menu.cpp"
#    "${CMAKE_SOURCE_DIR}/src/gui/not_supported.cpp"
#    "${CMAKE_SOURCE_DIR}/src/gui/singleplayer.cpp"
#    "${CMAKE_SOURCE_DIR}/src/gui/select_region.cpp"
#)
#
#add_executable( Browars main.cpp ${SRCS} )
#
#target_include_directories(Browars PUBLIC
#    "${CMAKE_SOURCE_DIR}/include"
#    "${CMAKE_SOURCE_DIR}/lib/sfeMovie/include"
#)
#
#target_link_libraries( Browars sfml-system sfml-window sfml-graphics sfml-audio sfeMovie )