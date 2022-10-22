@echo off

chcp 65001

set BUILD_TYPE=Release
set ARCH=x64

:next_parm
	set PARM_X=%1
Rem	echo Параметр : %PARM_X%

    if "%PARM_X%" == "" (
		GOTO end_parms
	)

    if "%PARM_X%" == "debug" (
    	set BUILD_TYPE=Debug
    ) ELSE ( if "%PARM_X%" == "release" (
    	set BUILD_TYPE=Release
    ) ELSE ( if "%PARM_X%" == "x64" (
    	set ARCH=x64
    ) ELSE ( if "%PARM_X%" == "x32" (
    	set ARCH=x86
    ) ELSE ( if "%PARM_X%" == "x86" (
    	set ARCH=x86
    ) ELSE (
    	echo Неверный параметр %PARM_X%
    	set ERR2=ERR
    )))))

	SHIFT
GOTO next_parm

:end_parms

Rem set QTDIR=C:\Qt\Qt5.9.9\5.9.9\msvc2017_64
if exist build (
	echo Deleting build directory first.
	rmdir /S /Q build
) else (
	echo There is no build directory. Nothing to delete.
)
echo +++ cmake -S ./ -B ./build  -D CMAKE_BUILD_TYPE="%BUILD_TYPE%" -D CMAKE_BINARY_DIR=./build
cmake -S ./ -B ./build  -D CMAKE_BUILD_TYPE="%BUILD_TYPE%" -D CMAKE_BINARY_DIR=./build
IF NOT %ERRORLEVEL% == 0 (
	echo.
	echo ***** Ошибки при выполнении cmake -S . -B ./build ... *****
	goto endend
)
	echo +++ cmake./build --config %BUILD_TYPE% 
	cmake --build ./build --config %BUILD_TYPE%
IF NOT %ERRORLEVEL% == 0 (
	echo.
	echo ***** Ошибки при выполнении cmake --build ... *****
	goto endend
)
set DEBUG=
IF "%BUILD_TYPE%" == "Debug" (
	set DEBUG="d"
)
	xcopy /DICYQ .\build\bin\Qt5Core%DEBUG%.dll .\build\bin\%BUILD_TYPE% >nul
	xcopy /DICYQ .\build\bin\Qt5Sql%DEBUG%.dll .\build\bin\%BUILD_TYPE% >nul
	xcopy /DICYQ .\build\bin\Qt5Widgets%DEBUG%.dll .\build\bin\%BUILD_TYPE% >nul
	xcopy /DICYQ .\build\bin\Qt5Gui%DEBUG%.dll .\build\bin\%BUILD_TYPE% >nul
	xcopy /DICYQ .\build\bin\archdatadir\plugins\platforms\ .\build\bin\%BUILD_TYPE%\platforms >nul
	xcopy /DICYQ .\build\bin\archdatadir\plugins\sqldrivers\ .\build\bin\%BUILD_TYPE%\sqldrivers >nul
	xcopy /DICYQ .\db\korpus_1.db .\build\bin\%BUILD_TYPE% >nul
	xcopy /DICYQ .\db\settings.json .\build\bin\%BUILD_TYPE% >nul
:endend