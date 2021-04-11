# CMake version, project, and C standard version.
cmake_minimum_required(VERSION 3.17)
project(test-app C)
set(CMAKE_C_STANDARD 99)


# Add 'test' build target and include CTest.
enable_testing()
include(CTest)

# Download CTest dependency.
file(DOWNLOAD https://raw.githubusercontent.com/bvdberg/ctest/master/ctest.h ${CMAKE_SOURCE_DIR}/ctest.h)


# Require SDL version 2.
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})


# Library and demo application source lists.
set(LIB_SOURCE_FILES sdl2boot.c sdl2boot.h vmath.c vmath.h vdraw.c vdraw.h vedge.c vedge.h vfont.c vfont.h vfont-segs.h)
set(APP_SOURCE_FILES main.c main.h ${LIB_SOURCE_FILES})


## Demo application.
add_executable(demo-app ${APP_SOURCE_FILES})
target_link_libraries(demo-app ${SDL2_LIBRARIES} m)


# Test SDL 2 Boot.
add_executable(sdl2boot-tests sdl2boot-ctest.h sdl2boot-tests.c sdl2boot.c sdl2boot.h)
target_link_libraries(sdl2boot-tests ${SDL2_LIBRARIES})

add_test(sdl2boot-tests sdl2boot-tests)


# Test vMath.
add_executable(vmath-tests vmath-ctest.h vmath-tests.c vmath.c vmath.h)
target_link_libraries(vmath-tests ${SDL2_LIBRARIES} m)

add_test(vmath-tests vmath-tests)


# Test vDraw.
add_executable(vdraw-tests vdraw-ctest.h vdraw-tests.c sdl2boot.c sdl2boot.h vmath.c vmath.h vdraw.c vdraw.h)
target_link_libraries(vdraw-tests ${SDL2_LIBRARIES} m)

add_test(vdraw-tests vdraw-tests)


# Test vEdge.
add_executable(vedge-tests vedge-ctest.h vedge-tests.c vmath.c vmath.h vdraw.c vdraw.h vedge.c vedge.h vfont.c vfont.h vfont-segs.h)
target_link_libraries(vedge-tests ${SDL2_LIBRARIES} m)

add_test(vedge-tests vedge-tests)
