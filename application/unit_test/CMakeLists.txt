cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

project(unit_tests)

find_package(Threads REQUIRED)

add_executable(unit_tests
      main.cpp
      business/abbreviated_and_full_tests.cpp
      business/value_component_tests.cpp
   )

include_directories(/usr/src/gmock/include /usr/src/gmock/gtest/include)
target_link_libraries(unit_tests nfirspp-business $ENV{HOME}/third-party/gmock/libgmock.a $ENV{HOME}/third-party/gmock/gtest/libgtest.a ${CMAKE_THREAD_LIBS_INIT})

SETUP_TARGET_FOR_COVERAGE(cover_unit_tests
                          ${PROJECT_BINARY_DIR}/unit_tests
                          ${PROJECT_BINARY_DIR}/cover_unit_tests
                         )
