set(EXTERNAL_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/../external)

add_library(renderer STATIC renderer.cpp vertexBuffer.cpp indexBuffer.cpp vertexArray.cpp shader.cpp texture.cpp utils.cpp)

target_include_directories(renderer
    PRIVATE ${EXTERNAL_DIRECTORY}/GLEW/include
    PRIVATE ${EXTERNAL_DIRECTORY}/stb_image
)

target_link_libraries(renderer stb_image)