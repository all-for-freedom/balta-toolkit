cmake_minimum_required(VERSION 3.10)
project(balta_toolkit)

# 搜索 src/ 目录里的所有 cpp
file(GLOB_RECURSE PLUGIN_SOURCE src/*.cpp)

# 生成插件 main.dll
add_library(${PROJECT_NAME} MODULE ${PLUGIN_SOURCE})
set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME "main")
set_target_properties(${PROJECT_NAME} PROPERTIES PREFIX "")

# 链接 SDK 的 bex 库
add_library(bex SHARED IMPORTED)

# 让编译器知道去哪里找 bex/bex.hpp
target_include_directories(${PROJECT_NAME} PRIVATE
    ${PROJECT_SOURCE_DIR}/include/include
)

# 头文件路径（指向 include/include）
set_target_properties(bex PROPERTIES
    INTERFACE_INCLUDE_DIRECTORIES ${PROJECT_SOURCE_DIR}/include/include
)

# 根据平台设置库文件路径
if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
    # Windows 平台：需要 DLL（运行时）和导入库（链接时）
    if(CMAKE_SIZEOF_VOID_P EQUAL 8)
        set(BEX_PLATFORM "windows_x86_64")
        set(BEX_DLL_PATH ${PROJECT_SOURCE_DIR}/include/lib/${BEX_PLATFORM}/libbex.dll)
        set(BEX_IMPLIB_PATH ${PROJECT_SOURCE_DIR}/include/lib/${BEX_PLATFORM}/libbex.dll.a)
        set_target_properties(bex PROPERTIES
            IMPORTED_LOCATION ${BEX_DLL_PATH}
            IMPORTED_IMPLIB ${BEX_IMPLIB_PATH}
        )
    else()
        message(FATAL_ERROR "Windows x86 (32-bit) is not supported")
    endif()
elseif(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    # Linux 平台：只需要 .so 文件（同时用于运行时和链接时）
    if(CMAKE_SYSTEM_PROCESSOR MATCHES "aarch64|arm64|ARM64")
        set(BEX_PLATFORM "linux_arm64")
    elseif(CMAKE_SYSTEM_PROCESSOR MATCHES "x86_64|AMD64")
        set(BEX_PLATFORM "linux_x86_64")
    else()
        message(FATAL_ERROR "Unsupported Linux architecture: ${CMAKE_SYSTEM_PROCESSOR}")
    endif()
    set(BEX_SO_PATH ${PROJECT_SOURCE_DIR}/include/lib/${BEX_PLATFORM}/libbex.so)
    set_target_properties(bex PROPERTIES
        IMPORTED_LOCATION ${BEX_SO_PATH}
    )
else()
    message(FATAL_ERROR "Unsupported platform: ${CMAKE_SYSTEM_NAME}")
endif()

# 这里链接第三方库
target_include_directories(${PROJECT_NAME} PRIVATE 
    ${PROJECT_SOURCE_DIR}/third_party
)

# 链接到你的插件
target_link_libraries(${PROJECT_NAME} bex)