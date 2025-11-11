cmake_minimum_required(VERSION 3.10)

set(CC_PLUGIN_NAME "COCOS_CC_PLUGIN_TP___glue")
set(CC_THREELIB_NAME "THREE_LIB_TP__")

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_C_FLAGS_DEBUG "$ENV{CMAKE_C_FLAGS_DEBUG} -std=c++17 -O0 -Wall -g")
set(CMAKE_CXX_FLAGS_DEBUG "$ENV{CMAKE_CXX_FLAGS_DEBUG} -std=c++17 -O0 -Wall -g")

set(CC_PLUGIN_LIB_PATH ${CMAKE_CURRENT_LIST_DIR})

file(GLOB SRC_FILES ${CMAKE_CURRENT_LIST_DIR}/../glue/*.cpp ${CMAKE_CURRENT_LIST_DIR}/../src/*.cpp)

add_library(${CC_PLUGIN_NAME} ${SRC_FILES})

target_compile_definitions(${CC_PLUGIN_NAME} PRIVATE CC_PLUGIN_NATIVE=1)

target_link_libraries(${CC_PLUGIN_NAME}

    ${CC_THREELIB_NAME}
    simplelog
    z
    "-lsqlite3"
    pthread
    "-framework VideoToolbox"
    "-framework AudioToolbox"
    ${ENGINE_NAME} # cocos_engine
)

target_include_directories(${CC_PLUGIN_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/../include
    ${CC_PLUGIN_LIB_PATH}/include
    ${CC_EXTERNAL_INCLUDES}
    ${CWD}
    ${CWD}/cocos
    ${CWD}/cocos/renderer
    ${CWD}/cocos/platform
    ${CWD}/cocos/renderer/core
    ${CWD}/cocos/editor-support
    ${SWIG_OUTPUT_ROOT}
    ${SWIG_OUTPUT_ROOT}/cocos
)
