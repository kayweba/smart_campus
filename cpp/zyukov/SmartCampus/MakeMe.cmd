@echo off

chcp 65001

set QTDIR=C:\Qt\Qt5.9.9\5.9.9\msvc2017_64
if exist build (
	echo Deleting build directory first.
	rmdir /S /Q build
) else (
	echo There is no build directory. Nothing to delete.
)
cmake -S ./ -B ./build
cmake --build ./build --config RelWithDebInfo

xcopy /DICYQ %QTDIR%\bin\Qt5Core.dll .\build\sources\RelWithDebInfo >nul
xcopy /DICYQ %QTDIR%\bin\Qt5Sql.dll .\build\sources\RelWithDebInfo >nul
xcopy /DICYQ %QTDIR%\bin\Qt5Widgets.dll .\build\sources\RelWithDebInfo >nul
xcopy /DICYQ %QTDIR%\bin\Qt5Gui.dll .\build\sources\RelWithDebInfo >nul
xcopy /DICYQ .\db\korpus_1.db .\build\sources\RelWithDebInfo >nul