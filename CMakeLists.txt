cmake_minimum_required(VERSION 3.12)
project(CSC_173_Submission C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(CSC_173_Submission
        cDFA.c
        cDFA.h
        dfa.c
        dfa.h
        IntHashSet.c
        IntHashSet.h
        main.c
        nfa.c
        nfa.h
        Set.h)
