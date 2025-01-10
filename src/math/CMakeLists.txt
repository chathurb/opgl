add_library(math STATIC rotation.cpp)

set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/..)

target_include_directories(math
    PRIVATE ${SRC_DIR}/renderer
)

target_link_libraries(math renderer)