cmake_minimum_required(VERSION 2.8)

project(A1)
project(A2)
project(A3)
project(A4)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

include_directories(${OPENGL_INCLUDE_DIR}  ${GLUT_INCLUDE_DIR})

add_definitions(-std=gnu++0x -Wall)


add_executable(A1 src/a1.cpp)
add_executable(A2 src/a2.cpp src/controller/glut_engine.cpp)
add_executable(A3 src/a2.cpp src/controller/glut_engine3.cpp src/view/window.cpp)
add_executable(A4 src/a2.cpp src/controller/glut_engine4.cpp src/view/window.cpp src/view/demo_window.cpp)

target_link_libraries(A1 ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES})
target_link_libraries(A2 ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES})
target_link_libraries(A3 ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES})
target_link_libraries(A4 ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES})
