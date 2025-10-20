cmake_minimum_required(VERSION 3.10)
project(SolarSystem)

include_directories(${CMAKE_SOURCE_DIR}/include)


set(CMAKE_CXX_STANDARD 17)

file(GLOB SOURCES "src/*.cpp")

add_executable(SolarSystem ${SOURCES})

find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(glfw3 REQUIRED)

target_link_libraries(SolarSystem
    OpenGL::GL
    GLEW::GLEW
    glfw
)
