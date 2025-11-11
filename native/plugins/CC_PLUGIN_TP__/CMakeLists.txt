cmake_minimum_required(VERSION 3.10)

# import cocos engine
set(COCOS_X_PATH /Users/a1021500561/work/cocos-engine/native)
set(COCOS_X_EXTERNAL_PATH ${COCOS_X_PATH}/external)

SET(COCOS_PLUGIN_NAME "CC_PLUGIN_TP__")
project(${COCOS_PLUGIN_NAME} CXX)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_C_FLAGS_DEBUG "$ENV{CMAKE_C_FLAGS_DEBUG} -std=c++17 -O0 -Wall -g")
set(CMAKE_CXX_FLAGS_DEBUG "$ENV{CMAKE_CXX_FLAGS_DEBUG} -std=c++17 -O0 -Wall -g")

file(GLOB SRC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)

# default target dist
set(PLUGIN_LIB_PATH ${CMAKE_CURRENT_SOURCE_DIR}/dist)

if(ANDROID)
    # include(${COCOS_X_PATH}/CMakeLists.txt)
    include(${COCOS_X_PATH}/cmake/predefine.cmake)
    message(STATUS "plugin platfrom: ANDROID")

    # list(APPEND SRC_FILES XXX.cpp)
    set(PLUGIN_LIB_PATH ${CMAKE_CURRENT_SOURCE_DIR}/android/${ANDROID_ABI})
    set(COCOS_X_EXTERNAL_PATH ${COCOS_X_PATH}/external/android/${ANDROID_ABI})

elseif(IOS)
    include(${COCOS_X_PATH}/cmake/predefine.cmake)

    message(STATUS "plugin platfrom: IOS")

    # list(APPEND SRC_FILES XXX.cpp)
    set(PLUGIN_LIB_PATH ${CMAKE_CURRENT_SOURCE_DIR}/ios)
    set(COCOS_X_EXTERNAL_PATH ${COCOS_X_PATH}/external/ios)

elseif(WEB)
    set(PLUGIN_LIB_PATH ${CMAKE_CURRENT_SOURCE_DIR}/web)
elseif(WX)
    set(PLUGIN_LIB_PATH ${CMAKE_CURRENT_SOURCE_DIR}/wx)
endif()

message(STATUS "SRC_FILES: ${SRC_FILES}")
add_library(${COCOS_PLUGIN_NAME} ${SRC_FILES})

# THREE_LIB_TP__
set(COCOS_LIB_NAME "THREE_LIB_TP__")
add_library(${COCOS_LIB_NAME} STATIC IMPORTED GLOBAL)
set_target_properties(${COCOS_LIB_NAME} PROPERTIES
    INTERFACE_INCLUDE_DIRECTORIES "${PLUGIN_LIB_PATH}/include"
    IMPORTED_LOCATION "${PLUGIN_LIB_PATH}/lib/lib${COCOS_LIB_NAME}.a"
)

target_link_libraries(${COCOS_PLUGIN_NAME} INTERFACE
    ${COCOS_LIB_NAME}
)

target_include_directories(${COCOS_PLUGIN_NAME} INTERFACE
    ${CMAKE_CURRENT_LIST_DIR}/include
    ${PLUGIN_LIB_PATH}/include
)
message(COCOS_X_EXTERNAL_PATH: ${COCOS_X_EXTERNAL_PATH})

# # include cocos-engine
target_include_directories(${COCOS_PLUGIN_NAME} PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/include
    ${PLUGIN_LIB_PATH}/include
    ${CC_EXTERNAL_INCLUDES}
    ${COCOS_X_PATH}
    ${COCOS_X_PATH}/cocos
    ${COCOS_X_PATH}/cocos/renderer
    ${COCOS_X_PATH}/cocos/platform
    ${COCOS_X_PATH}/cocos/renderer/core
    ${COCOS_X_PATH}/cocos/bindings/jswrapper
    ${COCOS_X_PATH}/cocos/editor-support
    ${COCOS_X_PATH}/generated
    ${COCOS_X_PATH}/generated/cocos
    ${COCOS_X_PATH}/cocos/bindings/auto
    ${COCOS_X_PATH}/external/sources
    ${COCOS_X_EXTERNAL_INCLUDES}/include
    ${COCOS_X_EXTERNAL_INCLUDES}/include/v8
)

# # install
set(CMAKE_INSTALL_PREFIX ${PLUGIN_LIB_PATH})
install(TARGETS ${COCOS_PLUGIN_NAME} LIBRARY DESTINATION lib)
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include/ DESTINATION include)
