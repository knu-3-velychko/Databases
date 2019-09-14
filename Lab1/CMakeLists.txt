cmake_minimum_required(VERSION 3.14)
project(untitled)

set(CMAKE_CXX_STANDARD 14)

add_executable(untitled main.c
        structures.h structures.c
        run.h run.c
        io.h io.c
        insert.h insert.c
        delete.h delete.c
        get.h get.c
        update.h update.c
        count.h count.c)