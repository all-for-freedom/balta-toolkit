/*
 * 北太天元（Baltamatica）开发者工具箱头文件。
 *
 * 该文件包含使用 bex 库必要的宏定义，类型声明，函数原型声明。
 * 适用于 v4.1 版本的北太天元。
 *
 * 版权所有 © 2021-2025，北太振寰（重庆）科技有限公司
 */

#ifndef BALTAM_BX_OP_H
#define BALTAM_BX_OP_H

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    bxUNKNOWN_OP = 0,
    // 双目运算符
    bxADD_OP = 1,
    bxSUB_OP,
    bxTIMES_OP,
    bxRDIV_OP,
    bxLDIV_OP,
    bxMTIMES_OP,
    bxMRDIV_OP,
    bxMLDIV_OP,
    bxPOW_OP,
    bxMPOW_OP,
    bxLT_OP,
    bxGT_OP,
    bxLE_OP,
    bxGE_OP,
    bxNE_OP,
    bxEQ_OP,
    bxAND_OP,
    bxOR_OP,
    // 可变长算符
    bxHCAT_OP,
    bxVCAT_OP,
    // 单目运算符
    bxUMINUS_OP,
    bxUPLUS_OP,
    bxNOT_OP,
    bxTRANSP_OP,
    bxCTRANSP_OP,
    bxSUBSIND_OP,
    // 圆括号索引
    bxSUBSREF_OP,   // 双目
    bxSUBSASGN_OP,  // 三目
    // 花括号索引，可变长算符
    bxBRACEREF_OP,
    bxBRACEASGN_OP,
    // 点索引，可变长算符
    bxDOTREF_OP,
    bxDOTASGN_OP
} bxOperatorID;

#ifdef __cplusplus
}
#endif // of __cplusplus

#endif

