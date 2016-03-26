@ECHO OFF
if "%VCINSTALLDIR%"=="" call "%VS100COMNTOOLS%vsvars32.bat"
if "%VCINSTALLDIR%"=="" call "%VS110COMNTOOLS%vsvars32.bat"
if "%VCINSTALLDIR%"=="" call "%VS120COMNTOOLS%vsvars32.bat"
echo.
echo Build command line tools
echo ========================
cd Binaries\
call nmake /nologo %1
IF ERRORLEVEL 1 goto error
cd ..\
echo done
goto end

:error
echo error
exit /b 1
:end