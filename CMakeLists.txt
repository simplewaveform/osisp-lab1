cmake_minimum_required(VERSION 3.26)
project(lab1 C)

set(CMAKE_C_STANDARD 23)

add_executable(lab1 src/main.c
        src/args.c
        inc/args.h
        src/walk.c
        inc/walk.h
        inc/options.h
        src/options.c
        src/paths.c
        inc/paths.h
)
