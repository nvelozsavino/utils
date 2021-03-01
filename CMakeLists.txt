cmake_minimum_required(VERSION 3.17)
project(utils C)

set(CMAKE_C_STANDARD 11)

add_library(utils library.c library.h rb_bst.c rb_bst.h)