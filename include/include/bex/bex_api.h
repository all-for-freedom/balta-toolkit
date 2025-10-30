/*
 * 北太天元（Baltamatica）开发者工具箱头文件。
 *
 * 该文件用于声明北太天元 SDK 导入/导出的符号。
 * 适用于 v4.1 版本的北太天元。
 *
 * 版权所有 © 2021-2025，北太振寰（重庆）科技有限公司
 */

#ifndef BALTAM_BEX_API_H
#define BALTAM_BEX_API_H

#include "api_helper_macro.h"

#ifdef bex_EXPORTS 
#define BEX_API BALTAM_HELPER_DLL_EXPORT
#else
#define BEX_API BALTAM_HELPER_DLL_IMPORT
#endif
#define BEX_EXPORT BALTAM_HELPER_DLL_EXPORT
#define BEX_LOCAL BALTAM_HELPER_DLL_LOCAL

#endif 

