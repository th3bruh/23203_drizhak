cmake_minimum_required(VERSION 3.5)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_COMPILER clang++)

project(blackjack CXX)

find_package(Boost CONFIG COMPONENTS program_options REQUIRED)
include_directories( ${Boost_INCLUDE_DIR} )

add_executable(${PROJECT_NAME} main.cpp competition.cpp tournament.cpp simple_deck.cpp console_interface.cpp strategy_1.cpp)

target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Wpedantic -std=c++20)

if(ENABLE_UBASAN)
  target_compile_options(${PROJECT_NAME} PUBLIC -g -O0 -fsanitize=address,undefined,leak -fno-omit-frame-pointer)
  target_link_options(${PROJECT_NAME} PUBLIC -fsanitize=address,undefined,leak)
endif()

if(CHECK_COVERAGE)
  target_compile_options(${PROJECT_NAME} PUBLIC -g -O0 --coverage)
  target_link_options(${PROJECT_NAME} PUBLIC --coverage)
endif()

enable_testing()
target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES})
