cmake_minimum_required(VERSION 3.23)

project(Ubject)

add_library(ubject_c_flags INTERFACE)
target_compile_features(ubject_c_flags INTERFACE c_std_17)
target_compile_options(
  ubject_c_flags
  INTERFACE
    "$<BUILD_INTERFACE:-Wall;-Wextra;-Wshadow;-Wformat=2;-Wunused>"
    "$<BUILD_INTERFACE:$<$<STREQUAL:${CMAKE_BUILD_TYPE},Debug>:-fPIC;-ggdb3;-O0;-fno-omit-frame-pointer;-fsanitize=address>>"
)
target_link_options(
  ubject_c_flags
  INTERFACE
  # "$<BUILD_INTERFACE:-Wall;-Wextra;-Wshadow;-Wformat=2;-Wunused-Wl,--exclude-libs
  # >" "$<BUILD_INTERFACE:-Wall;-Wl,--exclude-libs>"
  "$<BUILD_INTERFACE:$<$<STREQUAL:${CMAKE_BUILD_TYPE},Debug>:-fPIC;-ggdb3;-O0;-fno-omit-frame-pointer;-fsanitize=address>>"
)

target_compile_definitions(
  ubject_c_flags
  INTERFACE "$<$<STREQUAL:${CMAKE_BUILD_TYPE},Debug>:IU_MEM_LK=1>")

add_library(mem_lk SHARED IMPORTED)
set_property(TARGET mem_lk PROPERTY IMPORTED_LOCATION
                                    ${CMAKE_INSTALL_PREFIX}/bin/libmem_lk.so)

add_library(Ubject SHARED)
include(sources.cmake)
add_dependencies(Ubject mem_lk)

target_include_directories(Ubject
                           PRIVATE ${CMAKE_INSTALL_PREFIX}/include/mem_lk)

target_link_libraries(
  Ubject
  PUBLIC mem_lk
  PRIVATE ubject_c_flags)

# add_executable(ubject-test test.c)

install(TARGETS Ubject DESTINATION bin)
include(headers.cmake)
