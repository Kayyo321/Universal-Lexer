cmake_minimum_required(VERSION 3.22)
project(Universal_Lexer C)

set(CMAKE_C_STANDARD 23)

add_executable(Universal_Lexer main.c Lexer.h Lexer.c)
