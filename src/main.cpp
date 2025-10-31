/*
 * 北太天元(Baltamatica)t-SNE 插件主文件。
 * 适用于 v4.2 版本的北太天元。
 *
 */

#include "bex/bex.hpp"

using namespace baltam;
#define PLUGIN_NAME "balta_toolkit"

void isposdef(int, bxArray*[], int, const bxArray*[]);

static const char * isposdef_help = R"(
    判断一个矩阵是否正定。
)";

/**
 * @brief bxPluginInit 的定义
 *
 * bxPluginInit(args...) 会在调用 load_plugin(name, args...) 时调用,目的是
 * 进行一些初始化工作。
 *  
 * 目前还不知道需要做什么初始化工作
 */

int bxPluginInit(int, const bxArray*[]){ return 0;}


/**
 * @brief bxPluginFini 的定义
 *
 * bxPluginFini() 会在调用 unload_plugin() 时调用。目的是进行一些析构的工作。
 *
 * 这里因为无需特别的析构,所以定义为空函数。
 */

int bxPluginFini(){ return 0; }


/**
 * @brief bxPluginFunctions 的定义
 *
 * bxPluginFunctions 返回一个 bexfun_info_t * 的指针,指向函数列表的第一个元素。
 * 列表中最后一个元素的 name 标签必须为空字符串常量。
 * 函数列表可以以静态变量的方式定义在 .cpp 或 .c 中。
 *
 */
static bexfun_info_t flist[] = {
    {"isposdef", isposdef, isposdef_help},
    {"", nullptr, nullptr},
};

bexfun_info_t * bxPluginFunctions(){
    return flist;
}

/**
 * @brief 以下是插件函数的实际定义。
 * 
 */

void isposdef(int nlhs, bxArray *plhs[], int nrhs, const bxArray *prhs[]){
    
}