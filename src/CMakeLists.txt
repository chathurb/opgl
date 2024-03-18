add_executable(${PROJECT_NAME} main.cpp)

add_subdirectory(renderer)

set(EXTERNAL_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/external)

target_include_directories(${PROJECT_NAME}
    PRIVATE ${EXTERNAL_DIRECTORY}/GLFW/include
    PRIVATE ${EXTERNAL_DIRECTORY}/GLEW/include
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/renderer
)

target_link_directories(${PROJECT_NAME}
    PRIVATE ${EXTERNAL_DIRECTORY}/GLFW/lib-vc2022
    PRIVATE ${EXTERNAL_DIRECTORY}/GLEW/lib/Release/x64
)

target_link_libraries(${PROJECT_NAME} glfw3 opengl32 glew32s renderer)