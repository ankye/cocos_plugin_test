if(ANDROID)
    set(simplelog_ROOT ${CMAKE_CURRENT_LIST_DIR}/${ANDROID_ABI})
else()
    set(simplelog_ROOT ${CMAKE_CURRENT_LIST_DIR})
endif()

set(COCOS_LIB_NAME "simplelog")
add_library(${COCOS_LIB_NAME} STATIC IMPORTED GLOBAL)
set_target_properties(${COCOS_LIB_NAME} PROPERTIES
    INTERFACE_INCLUDE_DIRECTORIES "${simplelog_ROOT}/include"
    IMPORTED_LOCATION "${simplelog_ROOT}/lib/lib${COCOS_LIB_NAME}.a"
)
