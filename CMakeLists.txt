include_directories(${CMAKE_SOURCE_DIR}/Core/include)
include_directories(${CMAKE_SOURCE_DIR}/vendors)
include_directories(${CMAKE_SOURCE_DIR}/vendors/glm)
include_directories(${CMAKE_SOURCE_DIR}/vendors/glad)
include_directories(${CMAKE_SOURCE_DIR}/vendors/stbi)


add_executable(app main.cpp)

target_link_libraries(app tridme glfw OpenGL::GL)
find_package(OpenGL REQUIRED)