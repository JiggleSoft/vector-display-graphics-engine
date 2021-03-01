cmake_minimum_required(VERSION 3.17)
project(test-app C)

#FIXME: CTEST: enable_testing()
#FIXME: CTEST: add_test(testall, test-vmath)

#FIXME: CTEST: set(CMAKE_C_STANDARD 99)

find_package(SDL2 REQUIRED)
#FIXME: CTEST: find_package(CTEST REQUIRED)

include_directories(${SDL2_INCLUDE_DIRS})


#FIXME: CTEST: add_executable(test-vmath test-vmath.c vmath.c vmath.h)
#FIXME: CTEST: target_link_libraries(test-vmath ${SDL2_LIBRARIES} m)

#FIXME: CTEST: add_executable(test-vmath test-vmath.c vmath.c vmath.h)
#FIXME: CTEST: target_link_libraries(test-vmath ${SDL2_LIBRARIES} m)


set(SOURCE_FILES main.c vmath.c vmath.h vdraw.c vdraw.h vedge.c vedge.h vfont.c vfont.h )

add_executable(test-app ${SOURCE_FILES})
target_link_libraries(test-app ${SDL2_LIBRARIES} m)
