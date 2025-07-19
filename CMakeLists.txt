cmake_minimum_required(VERSION 3.31)
project(idk C)

set(CMAKE_C_STANDARD 99)

add_executable(
        idk
        main.c
        str.c
        list_str.c
        str_util.c
        more_str_util.c
        parser.c
)
