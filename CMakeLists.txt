cmake_minimum_required(VERSION 3.17)
project(test-app C)

# Add 'test' build target.
enable_testing()

#include(CTest)

#FIXME: CTEST: add_test(testall, test-vmath)

#FIXME: CTEST: set(CMAKE_C_STANDARD 99)

find_package(SDL2 REQUIRED)
#find_package(CTEST REQUIRED)

include_directories(${SDL2_INCLUDE_DIRS})
#include_directories(${SDL2_INCLUDE_DIRS})


# Download CTest.
file(DOWNLOAD https://raw.githubusercontent.com/bvdberg/ctest/master/ctest.h ${CMAKE_SOURCE_DIR}/ctest.h)


#FIXME: CTEST: add_executable(test-vmath test-vmath.c vmath.c vmath.h)
#FIXME: CTEST: target_link_libraries(test-vmath ${SDL2_LIBRARIES} m)

#FIXME: CTEST: add_executable(test-vmath test-vmath.c vmath.c vmath.h)
#FIXME: CTEST: target_link_libraries(test-vmath ${SDL2_LIBRARIES} m)


set(SOURCE_FILES main.c main.h sdl2boot.c sdl2boot.h vmath.c vmath.h vdraw.c vdraw.h vedge.c vedge.h vfont.c vfont.h vfont-segs.h)

add_executable(test-app ${SOURCE_FILES})
target_link_libraries(test-app ${SDL2_LIBRARIES} m)


add_executable(vmath-tests vmath-tests.c vmath.c vmath.h)
target_link_libraries(vmath-tests m)

add_test(vmath-tests vmath-tests)


add_executable(vdraw-tests vdraw-tests.c sdl2boot.c sdl2boot.h vmath.c vmath.h vdraw.c vdraw.h)
target_link_libraries(vdraw-tests ${SDL2_LIBRARIES} m)

add_test(vdraw-tests vdraw-tests)


add_executable(vedge-tests vedge-tests.c vmath.c vmath.h vdraw.c vdraw.h vedge.c vedge.h vfont.c vfont.h vfont-segs.h)
target_link_libraries(vedge-tests ${SDL2_LIBRARIES} m)

add_test(vedge-tests vedge-tests)
