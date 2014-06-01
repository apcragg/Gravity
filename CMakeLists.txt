cmake_minimum_required(VERSION 2.8)

project("OpenGL_Gravity")

file(GLOB SRCS  ${OpenGL_Gravity_SOURCE_DIR}/src/*.cpp ${OpenGL_Gravity_SOURCE_DIR}/src/*.c)
file(GLOB HDRS  ${OpenGL_Gravity_SOURCE_DIR}/include/*.h)

include_directories(${OpenGL_Gravity_SOURCE_DIR}/include)
include_directories(${OpenGL_Gravity_SOURCE_DIR}/src)
add_definitions(-c -Wall -std=c++11)

add_executable(Debug ${HDRS} ${SRCS})

if(WIN32)
	target_link_libraries(Debug ${OpenGL_Gravity_SOURCE_DIR}/lib/libglew32.a)
	target_link_libraries(Debug ${OpenGL_Gravity_SOURCE_DIR}/lib/libglew32mx.a)
	target_link_libraries(Debug ${OpenGL_Gravity_SOURCE_DIR}/lib/libglfw3.a)
	target_link_libraries(Debug ${OpenGL_Gravity_SOURCE_DIR}/lib/libopengl32.a)
endif()

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU" OR
    "${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    set(warnings "-Wall -Wextra -Werror")
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
    set(warnings "/W4 /WX /EHsc")
endif()

install(TARGETS Debug DESTINATION bin)