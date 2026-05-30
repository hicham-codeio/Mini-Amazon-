cmake_minimum_required(VERSION 3.5)
project(MiniAmazon LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 COMPONENTS Widgets REQUIRED)

include_directories(include)

# Shared files
file(GLOB_RECURSE SHARED_SRC src/database/*.cpp src/order/*.cpp src/product/*.cpp src/user/*.cpp)
file(GLOB_RECURSE SHARED_HDR include/database/*.h include/order/*.h include/product/*.h include/user/*.h)

# CLI files
file(GLOB_RECURSE CLI_SRC src/cli/*.cpp)
file(GLOB_RECURSE CLI_HDR include/cli/*.h)

# GUI files
file(GLOB_RECURSE GUI_SRC src/gui/*.cpp)
file(GLOB_RECURSE GUI_HDR include/gui/*.h)

# CLI Executable
add_executable(MiniAmazonCLI src/main_cli.cpp ${SHARED_SRC} ${CLI_SRC} ${SHARED_HDR} ${CLI_HDR})

# GUI Executable
add_executable(MiniAmazonGUI src/main_gui.cpp ${SHARED_SRC} ${GUI_SRC} ${SHARED_HDR} ${GUI_HDR})
target_link_libraries(MiniAmazonGUI PRIVATE Qt6::Widgets)
