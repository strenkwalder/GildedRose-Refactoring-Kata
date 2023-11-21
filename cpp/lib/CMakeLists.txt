set(LIB_NAME lib)
add_library(${LIB_NAME} INTERFACE
        ../src/item.cpp)
target_include_directories(${LIB_NAME} INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
