/*
 * 北太天元（Baltamatica）开发者工具箱头文件。
 *
 * 该文件包含使用 SDK 必要的宏定义，类型声明，函数原型声明。
 * 适用于 v4.1 版本的北太天元。
 *
 * 版权所有 © 2021-2025，北太振寰（重庆）科技有限公司
 */

#ifndef BALTAM_EXTERN_FCN_TYPE_H
#define BALTAM_EXTERN_FCN_TYPE_H

#ifdef __cplusplus
extern "C" {
#endif

struct __bxArray;


// bex 接口函数类型
typedef void (*bexfun_t)(int, struct __bxArray*[], int, const struct __bxArray*[]);
// bex 接口函数类型
typedef int (*bexofunchkr_t)(int, const struct __bxArray*[]);
// 复制函数原型
typedef void* (*cstruct_copy_t)(const void*);
// 析构函数原型
typedef void (*cstruct_delete_t)(void*);
// 字符串序列化函数原型
typedef char* (*cstruct_to_string_t)(const void*);
// 析构序列化的字符串
typedef void (*cstruct_to_string_delete_t)(char *);
// 函数列表元素的结构体
typedef struct {
    const char * name;
    bexfun_t ptr;
    const char * help;
} bexfun_info_t;
// 获取函数列表原型
typedef bexfun_info_t * (*bexfun_list_t)(void);
// 初始化函数原型
typedef int (*bexinit_t)(int, const struct __bxArray*[]);
// 释放函数原型
typedef int (*bexfini_t)(void);
// 初始化外部函数库原型
typedef int (*bexinit_lib_t)(void *);


#ifdef __cplusplus
}
#endif

#endif

