@echo off

set PROGRAM="%~1"

if %PROGRAM%=="" (
	echo Please specify path to program
	exit /b 1
)

rem Too few arguments count
%PROGRAM% > nul
if NOT ERRORLEVEL 1 goto err
echo Test 1 passed

rem Too many arguments
%PROGRAM% tests_data\12312312345.txt "%TEMP%\output.txt" 1 2 3 > nul
if NOT ERRORLEVEL 1 goto err
echo Test 2 passed

rem Trying to open a nonexistent file
%PROGRAM% tests_data\nonexistent.txt "%TEMP%\output.txt" 1 2 > nul
if NOT ERRORLEVEL 1 goto err
echo Test 3 passed

%PROGRAM% tests_data\12312312345.txt "%TEMP%\output.txt" 1231234 6
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\output.txt" tests_data\12312312345_to_12365.txt > nul
if ERRORLEVEL 1 goto err
echo Test 4 passed

%PROGRAM% tests_data\ma.txt "%TEMP%\output.txt" ma mama
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\output.txt" tests_data\ma_to_mama.txt > nul
if ERRORLEVEL 1 goto err
echo Test 5 passed

rem Copying the file without replacing if the sought string is empty
%PROGRAM% tests_data\replace_empty_string.txt "%TEMP%\output.txt" "" replacing
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\output.txt" tests_data\replace_empty_string.txt > nul
if ERRORLEVEL 1 goto err
echo Test 6 passed

echo All tests passed
exit /b 0

:err
echo Testing failed
exit /b 1