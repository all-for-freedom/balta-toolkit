cmake_minimum_required(VERSION 3.10)
project(self_use)

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
# DLL 路径（运行时加载）
set_target_properties(bex PROPERTIES
    IMPORTED_LOCATION ${PROJECT_SOURCE_DIR}/include/bin/libbex.dll
)
# 导入库路径（链接时用）
set_target_properties(bex PROPERTIES
    IMPORTED_IMPLIB ${PROJECT_SOURCE_DIR}/include/lib/libbex.dll.a
)

## 这里链接第三方库
# target_include_directories(${PROJECT_NAME} PRIVATE 
# 
# )

# 链接到你的插件
target_link_libraries(${PROJECT_NAME} bex)