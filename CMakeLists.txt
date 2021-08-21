cmake_minimum_required(VERSION 3.17)
project(ClinicManagementSystem)

set(CMAKE_C_STANDARD 99)

add_executable(ClinicManagementSystem source/main.c headers/STD_Types.h source/Login.c headers/Login.h source/AdminHelper.c headers/AdminHelper.h source/UserHelper.c headers/UserHelper.h)