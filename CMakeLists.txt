cmake_minimum_required(VERSION 3.20)
project(simple_shell)

option(ENABLE_TESTING "Build all simple_shell tests" ON)
mark_as_advanced(ENABLE_TESTING)

FILE(GLOB SS_SOURCES ./*.c)

add_executable(shell)

target_sources(shell PUBLIC ${SS_SOURCES})

set_target_properties(shell PROPERTIES
  LINK_FLAGS "-fsanitize=address -Wall -Werror -Wextra -pedantic -std=gnu89"
  RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

if(ENABLE_TESTING)
  enable_testing()
  add_subdirectory(tests)
endif()
