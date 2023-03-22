cmake_minimum_required (VERSION 3.20)

project ("knu-db-lab-1")

file(GLOB_RECURSE sources src/*.cpp src/*.h)

add_executable (knu-db-lab-1 ${sources})