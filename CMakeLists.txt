cmake_minimum_required(VERSION 3.26)
project(Elixir)

set(CMAKE_CXX_STANDARD 23)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(INCLUDE_DIR include)
set(SRC_DIR src)

file(GLOB SOURCES "src/*.cpp" "Libraries/*.c")
file(GLOB HEADERS "include/*.h" "include/*.hpp" "Libraries/*.h")

find_package(OpenGL REQUIRED)
find_package(PkgConfig REQUIRED)
pkg_search_module(GLFW REQUIRED glfw3)
find_package(glm REQUIRED)

include_directories(${OPENGL_INCLUDE_DIRS} ${INCLUDE_DIR} ${CMAKE_CURRENT_BINARY_DIR})

add_executable(${PROJECT_NAME} ${SOURCES} )

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_BINARY_DIR} ${INCLUDE_DIR} Libraries)

target_sources(${PROJECT_NAME} PUBLIC ${HEADERS})

target_link_libraries(${PROJECT_NAME}
        ${OPENGL_LIBRARIES}
        ${GLFW_LIBRARIES}
        GLEW
        glm::glm
        dl
        X11
        pthread)