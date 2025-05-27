cmake_minimum_required(VERSION 3.10)
project(RayTracer)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS_RELEASE "-O3 -march=native -ffast-math -DNDEBUG -funroll-loops -flto")

include(FetchContent)
find_package(OpenMP REQUIRED)
set(SFML3_COMPONENTS
    SFML::Graphics
    SFML::Window
    SFML::System
)

find_package(SFML COMPONENTS ${SFML3_COMPONENTS} QUIET)

if(SFML_FOUND)
    message(STATUS "Found SFML 3.x")
    set(_SFML_LINK_TARGETS ${SFML3_COMPONENTS})
else()
    find_package(SFML 2.5 REQUIRED COMPONENTS graphics window system)
    message(STATUS "Found SFML 2.5")
    set(_SFML_LINK_TARGETS
        SFML::Graphics
        SFML::Window
        SFML::System
    )
endif()

FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG v3.4.0
)
FetchContent_MakeAvailable(Catch2)

include_directories(include)

add_executable(raytracer
    main.cpp
    src/vec3.cpp
    src/color.cpp
    src/sphere.cpp
    src/hittable_list.cpp
    src/utils.cpp
    src/interval.cpp
    src/camera.cpp
    src/material.cpp
    src/display.cpp
    src/scene.cpp
)

add_executable(tests
    tests/test_vec3.cpp
    tests/test_ray.cpp
    tests/test_sphere.cpp
    tests/test_hittable_list.cpp
    tests/test_interval.cpp
    tests/test_utils.cpp
    tests/test_materials.cpp
    src/vec3.cpp
    src/color.cpp
    src/sphere.cpp
    src/hittable_list.cpp
    src/interval.cpp
    src/camera.cpp
    src/utils.cpp
    src/material.cpp
    src/display.cpp
)
target_link_libraries(raytracer PRIVATE
    OpenMP::OpenMP_CXX
    sfml-graphics
    sfml-window
    sfml-system
)


target_link_libraries(tests PRIVATE
    Catch2::Catch2WithMain
    OpenMP::OpenMP_CXX
    sfml-graphics
    sfml-window
    sfml-system
)

target_include_directories(tests PRIVATE include)

enable_testing()

include(CTest)
include(Catch)

catch_discover_tests(tests)
