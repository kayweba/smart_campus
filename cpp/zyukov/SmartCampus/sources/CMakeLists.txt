set (TARGET SmartCampusMain)

message("CXX compiler: " ${CMAKE_CXX_COMPILER_ID} " (" ${CMAKE_CXX_COMPILER_VERSION} ")")
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(SOURCES 
	${CMAKE_CURRENT_SOURCE_DIR}/stdafx.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/Application.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/DbManager.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/DbData.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/ElectricalSensor.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/DbValueGenerator.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/BuildingTreeItem.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/BuildingTreeModel.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/../resources/resources.qrc
)
qt5_wrap_ui(SOURCES mainwindow.ui electricalsensor.ui)
add_executable(${TARGET}
	${SOURCES}
)

target_include_directories(${TARGET} PRIVATE
	${CMAKE_SOURCE_DIR}/include
	${CMAKE_SOURCE_DIR}/resources
)

target_link_libraries(${TARGET} PUBLIC
	Qt5::Widgets
	Qt5::Core
	Qt5::Gui
	Qt5::Sql
)

IF (NOT WIN32)
    target_compile_options(${TARGET} PUBLIC
	-std=c++11
    )
    target_link_libraries(${TARGET} PUBLIC
	dl
    )
ENDIF()

