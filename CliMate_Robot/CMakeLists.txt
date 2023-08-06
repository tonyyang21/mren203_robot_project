cmake_minimum_required(VERSION 3.20)
project(CliMate_Robot)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)
include_directories(CliMate_Robot)

add_executable(CliMate_Robot
        CliMate_Robot/CliMate.ino
        CliMate_Robot/pinAssignments.h
        CliMate_Robot/lights.h
        CliMate_Robot/scanning.h
        CliMate_Robot/speaker.h)
