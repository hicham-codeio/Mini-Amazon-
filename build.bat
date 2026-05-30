@echo off
REM Mini Amazon C++ E-Commerce System - Build Script for Windows
REM This script compiles the project using g++ compiler

setlocal enabledelayedexpansion

REM Configuration
set CXX=g++
set CXXFLAGS=-std=c++14 -Wall -Wextra -Wpedantic -Wshadow -Wnon-virtual-dtor -O2 -Iinclude
set OUTPUT=app.exe

REM Source files
set SRC=^
    src/main.cpp ^
    src/product/Product.cpp ^
    src/product/Electronics.cpp ^
    src/product/Food.cpp ^
    src/product/Clothing.cpp ^
    src/product/RecommendationService.cpp ^
    src/order/CartItem.cpp ^
    src/order/Cart.cpp ^
    src/order/Order.cpp ^
    src/user/Customer.cpp ^
    src/user/UI.cpp ^
    src/database/ProductDAO.cpp ^
    src/database/OrderDAO.cpp ^
    src/database/CustomerDAO.cpp ^
    src/database/Database.cpp ^
    src/database/Store.cpp

REM Parse command line arguments
if "%1"=="clean" goto clean
if "%1"=="rebuild" goto clean

:build
echo.
echo Building Mini Amazon C++ Project...
echo.
%CXX% %CXXFLAGS% %SRC% -o %OUTPUT%

if %ERRORLEVEL% EQU 0 (
    echo.
    echo BUILD SUCCESSFUL!
    echo.
    echo Run the application with: %OUTPUT%
    echo Or use: .\%OUTPUT%
    goto end
) else (
    echo.
    echo BUILD FAILED! Please check the errors above.
    echo.
    goto end
)

:clean
echo Cleaning build artifacts...
if exist %OUTPUT% (
    del %OUTPUT%
    echo Deleted %OUTPUT%
)
if "%1"=="rebuild" goto build
echo Clean complete.
goto end

:end
endlocal
