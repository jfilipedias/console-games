cmake_minimum_required(VERSION 3.24)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(ConsoleGames VERSION 1.0 LANGUAGES CXX)

add_executable(${PROJECT_NAME})

target_sources(${PROJECT_NAME} PRIVATE
    src/critter_caretaker.cpp
    src/guess_my_number.cpp
    src/word_jumble.cpp
    src/hangman.cpp
    src/tic_tac_toe.cpp
    src/main.cpp)
