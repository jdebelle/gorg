cmake_minimum_required(VERSION 3.17)

project(gorg)

ADD_DEFINITIONS("-DBOOST_ALL_NO_LIB")
set(Boost_DEBUG ON)
set(Boost_USE_STATIC_LIBS       OFF)
set(Boost_USE_MULTITHREADED      ON)
set(Boost_USE_STATIC_RUNTIME    OFF)
set(Boost_ROOT "${CMAKE_SOURCE_DIR}/extern/boost_1_75_0")
set(Boost_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/extern/boost_1_75_0")
set(Boost_LIBRARY_DIR "${CMAKE_SOURCE_DIR}/extern/boost_1_75_0/stage/lib")
set(Boost_USE_MULTITHREADED ON)


FIND_PACKAGE( Boost 1.75 REQUIRED COMPONENTS program_options)
INCLUDE_DIRECTORIES( ${Boost_INCLUDE_DIR} "inc")
LINK_DIRECTORIES( ${Boost_LIBRARY_DIR} )

# specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURC_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

if (MSVC)
    # warning level 4 and all warnings as errors
    add_compile_options(/W4 /WX)
else()
    # lots of warnings and all warnings as errors
    add_compile_options(-Wall -Wextra -pedantic -Werror)
endif()


file(GLOB GORG_SRC "src/*.cpp")

add_executable(gorg ${GORG_SRC})


message("Program Options Path:${Boost_PROGRAM_OPTIONS_LIBRARY}")
TARGET_LINK_LIBRARIES( gorg ${Boost_PROGRAM_OPTIONS_LIBRARY} )
#TARGET_LINK_LIBRARIES( gorg libboost_program_options-vc142-mt-gd-x64-1_75)