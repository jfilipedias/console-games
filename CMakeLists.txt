cmake_minimum_required(VERSION 3.24)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project("BeginningCPPThroughGameProgramming")

add_executable(${PROJECT_NAME} 
    main.cpp
    guess_my_number.cpp
)
