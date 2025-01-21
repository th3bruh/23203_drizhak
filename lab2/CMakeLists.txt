cmake_minimum_required(VERSION 3.10)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_COMPILER clang++)

project(blackjack CXX)

find_package(Boost CONFIG COMPONENTS program_options REQUIRED)
include_directories( ${Boost_INCLUDE_DIR} )

add_executable(${PROJECT_NAME} main.cpp competition.cpp tournament.cpp
  simple_deck.cpp multiple_deck.cpp console_interface.cpp strategy_1.cpp strategy_2.cpp strategy_3.cpp strategy_4.cpp strategy_5.cpp)

target_compile_options(${PROJECT_NAME} PUBLIC -std=c++20)
target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Wpedantic)

if(ENABLE_UBASAN)
  target_compile_options(${PROJECT_NAME} PRIVATE -g -O0 -fsanitize=address,undefined,leak -fno-omit-frame-pointer)
  target_link_options(${PROJECT_NAME} PRIVATE -fsanitize=address,undefined,leak)
endif()

if(CHECK_COVERAGE)
  target_compile_options(${PROJECT_NAME} PRIVATE -g -O0 --coverage)
  target_link_options(${PROJECT_NAME} PRIVATE --coverage)
endif()

enable_testing()
target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES})
