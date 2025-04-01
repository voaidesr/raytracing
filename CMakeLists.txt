cmake_minimum_required(VERSION 3.10)
project(raytracing)

set(CMAKE_CXX_STANDARD 17)

include(FetchContent)

FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG v3.4.0
)
FetchContent_MakeAvailable(Catch2)

include_directories(include)

add_executable(raytracing
    main.cpp
)

add_executable(tests
    tests/test_vec3.cpp
    tests/test_color.cpp
    tests/test_ray.cpp
)
target_link_libraries(tests PRIVATE Catch2::Catch2WithMain)
target_include_directories(tests PRIVATE include)

enable_testing()

include(CTest)
include(Catch)

catch_discover_tests(tests)