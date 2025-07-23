cmake_minimum_required(VERSION 3.24)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(ConsoleGames VERSION 1.0 LANGUAGES CXX)

add_executable(${PROJECT_NAME})

target_sources(${PROJECT_NAME} PRIVATE
    guess_my_number.cpp
    word_jumble.cpp
    hangman.cpp
    tic_tac_toe.cpp
    main.cpp)
