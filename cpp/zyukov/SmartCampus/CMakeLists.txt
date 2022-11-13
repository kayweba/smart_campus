cmake_minimum_required( VERSION 3.10 )
project( SmartCampus CXX)

IF (NOT WIN32)
    SET (CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BANIRY_DIR}/lib)
    SET (CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
    SET (CMAKE_RUNTUME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
ENDIF()

list(APPEND CMAKE_PREFIX_PATH $ENV{QTDIR}/lib/cmake/Qt5)
SET (CMAKE_INCLUDE_CURRENT_DIR ON)

function(PrintList Header Prop TRG)
    IF ("${TRG}" STREQUAL "")
		get_property(dirs DIRECTORY PROPERTY ${Prop})
	ELSE()
		get_target_property(dirs ${TRG} ${Prop})
	ENDIF()
	message("\n${Header}")
	foreach(dir ${dirs})
		message("    ${dir}")
	endforeach()
endfunction()

# Download automatically, you can also just copy the conan.cmake file
if(NOT EXISTS "${CMAKE_BINARY_DIR}/conan.cmake")
   message(STATUS "Downloading conan.cmake from https://github.com/conan-io/cmake-conan")
   file(DOWNLOAD "https://raw.githubusercontent.com/conan-io/cmake-conan/master/conan.cmake"
                  "${CMAKE_BINARY_DIR}/conan.cmake")
endif()
include(${CMAKE_BINARY_DIR}/conan.cmake)
conan_add_remote(NAME conancenter
		INDEX 0
		URL https://center.conan.io
		VERIFY_SLL True)

conan_cmake_run(REQUIRES boost/1.80.0
		OPTIONS boost:shared=False
                BASIC_SETUP)

message ("QTDIR is " $ENV{QTDIR})
IF ("$ENV{QTDIR}" STREQUAL "")
	message(FATAL_ERROR "Не задана переменная окружения QTDIR")
	exit()
ENDIF()

message("Prefix path: " ${CMAKE_PREFIX_PATH})

FIND_PACKAGE(Qt5 REQUIRED COMPONENTS Widgets Gui Core Sql)
SET (HW_HEADER_DIR include)
include_directories(${HW_HEADER_DIR})
link_directories(lib)
link_libraries(${CONAN_LIBS})

PrintList("Include directories:" INCLUDE_DIRECTORIES "")
message("")
PrintList("Link directories:" LINK_DIRECTORIES "")
message("")

#set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
add_subdirectory(sources)