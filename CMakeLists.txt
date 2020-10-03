cmake_minimum_required(VERSION 3.6)
project(RTv1 C)


set(SDL2_INCLUDE_DIR SDL2/include)
set(SDL2_LIB_DIR SDL2/lib)

find_package(OpenCL REQUIRED)

include_directories(${SDL2_INCLUDE_DIR})
link_directories(${SDL2_LIB_DIR})
include_directories(${SDL2_INCLUDE_DIRS}
        ${SDL2IMAGE_INCLUDE_DIRS}
        ${SDL2TTF_INCLUDE_DIRS} include
        ${OPENCL_SDK_INCLUDE_DIRS})
add_compile_options(-Wall -Wextra)

add_executable(RTv1 source/cleanup.c
        source/color.c
        source/control_utils.c
        source/errors.c
        source/init.c
        source/light.c
        source/main.c
        source/sphere.c
        source/texture.c
        source/utils.c
        source/vectors.c
        source/CL.c)
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES} ${SDL2IMAGE_LIBRARIES} ${SDL2TTF_LIBRARIES} m OpenCL)