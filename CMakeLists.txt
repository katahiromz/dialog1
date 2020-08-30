# CMakeLists.txt --- CMake project settings
#    ex) cmake -G "Visual Studio 9 2008" .
#    ex) cmake -DCMAKE_BUILD_TYPE=Release -G "MSYS Makefiles" .
##############################################################################

# CMake minimum version
cmake_minimum_required(VERSION 2.4)

# project name and language
project(dialog C CXX RC)

##############################################################################

add_definitions(-DUNICODE -D_UNICODE)

# hello2.exe
add_executable(dialog WIN32 dialog.cpp dialog_res.rc)
target_link_libraries(dialog PRIVATE comctl32)

##############################################################################
