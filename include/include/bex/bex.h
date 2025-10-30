/*
 * 北太天元（Baltamatica）开发者工具箱头文件。
 *
 * 该文件包含使用 bex 库必要的宏定义，类型声明，函数原型声明。
 * 适用于 v4.1 版本的北太天元。
 *
 * 版权所有 © 2021-2025，北太振寰（重庆）科技有限公司
 */

#ifndef BALTAM_BEX_H
#define BALTAM_BEX_H

// 默认整数类型
#ifndef BALTAM_DEFAULT_INT
#include <stddef.h>
#define BALTAM_DEFAULT_INT ptrdiff_t
#endif

#include <stdint.h>
#include <stdbool.h>
#include "bex_api.h"
#include "bex/bx_op.h"
#include "bex/extern_fcn_type.h"
#include "ba_obj/calendar_duration_elem.h"

#if !defined(baltam_core_EXPORTS) && !defined(bex_EXPORTS) && !defined(NO_BEX_CONFIG)
#include "bex_config.h"
#endif

// 宏展开：统一工具箱接口
#define BALTAM_PLUGIN_FCN(word) \
    void word(int nlhs, bxArray *plhs[], int nrhs, const bxArray *prhs[])


#ifdef __cplusplus
extern "C" {
#endif

// 定义数据类型
typedef BALTAM_DEFAULT_INT baInt;
typedef baInt baIndex;
typedef baInt baSize;
typedef baIndex baSparseIndex;

// 定义用于传递内核变量的 C 结构体（不透明对象）
struct __bxArray;
typedef struct __bxArray bxArray;

typedef enum {
    bxREAL = 0,
    bxCOMPLEX
} bxComplexity;

typedef enum {
    bxDENSE = 0,
    bxSPARSE
} bxSparsity;

typedef enum {
    bxUNKNOWN_CLASS = 0,
    bxINT8_CLASS = 1, // 需要从 1 开始
    bxINT16_CLASS,
    bxINT_CLASS,
    bxINT32_CLASS = bxINT_CLASS,
    bxINT64_CLASS,
    bxUINT8_CLASS,
    bxUINT16_CLASS,
    bxUINT32_CLASS,
    bxUINT64_CLASS,
    bxDOUBLE_CLASS,
    bxSINGLE_CLASS,
    bxCHAR_CLASS = 13,
    bxLOGICAL_CLASS,
    bxSTRUCT_CLASS = 16,
    bxSTRING_CLASS,
    bxOBJECT_CLASS = 20,
    bxEXTERN_CLASS = 21,
    bxVOID_CLASS = 22,
    bxCELL_CLASS = 25,
    bxTABLE_CLASS = 32,
    bxDATETIME_CLASS,
    bxDURATION_CLASS,
    bxCALENDAR_DURATION_CLASS,
    bxTIMETABLE_CLASS,
    bxCATEGORICAL_CLASS = 38,
} bxClassID;

// 函数句柄类型枚举类
typedef enum {
    bxFH_UNKNOWN = -1,
    bxFH_ANONYMOUS = 0, // 匿名函数
    bxFH_VARIABLE,      // 变量
    bxFH_BUILTIN,       // 内置函数
    bxFH_MFUNCTION,     // M 函数
    bxFH_SCRIPT         // 脚本
} bxFHandleType;

// 表格类型插入模式
typedef enum {
    bxINSERT_BEFORE = 0,
    bxINSERT_AFTER
} bxInsertMode;

// 表格维度
typedef enum {
    bxTABLE_ROW = 0,
    bxTABLE_COLUMN
} bxTableDimension;

// 添加变量模式
typedef enum {
    bxNON_OVERWRITE = 0,
    bxOVERWRITE
} bxVarOpMode;

// 获取公有属性模式
typedef enum {
    bxEXCLUDE_HIDDEN = 0,
    bxINCLUDE_HIDDEN
} bxPubPropMode;

// 获取属性访问权限模式
typedef enum {
    bxGET_ACCESS = 0,
    bxSET_ACCESS
} bxPropertyAccessType;

// 访问权限
typedef enum {
    bxACCESS_UNKNOWN,
    bxACCESS_PUBLIC = 0,
    bxACCESS_PROTECTED,
    bxACCESS_PRIVATE
} bxAccessLevel;

// 分类数组的类型
typedef enum {
    bxCATEGORICAL_FREE = 0,
    bxCATEGORICAL_PROTECTED = 2,
    bxCATEGORICAL_ORDINAL = 3,
    bxCATEGORICAL_UNKNOWN = -1
} bxCategoricalType;

// VOID
typedef enum {
    bxVOID_DEFAULT = 0x00,
    bxVOID_ANS     = 0x01,
} bxVoidFlag;

// bex 接口函数原型
// 数组基本属性
BEX_API bxClassID bxGetClassID(const bxArray*);
BEX_API const char * bxTypeCStr(const bxArray*);
BEX_API baSize bxGetNumberOfDimensions(const bxArray*);
BEX_API const baSize * bxGetDimensions(const bxArray*);
BEX_API baSize bxGetNumberOfElements(const bxArray*);
BEX_API baSize bxGetM(const bxArray*);
BEX_API baSize bxGetN(const bxArray*);
BEX_API void bxSetM(bxArray*, baSize);
BEX_API void bxSetN(bxArray*, baSize);
BEX_API void bxResize(bxArray*, baSize, baSize);
BEX_API void bxSetDimensions(bxArray*, const baSize *, int);
BEX_API bool bxIsDouble(const bxArray*);
BEX_API bool bxIsSingle(const bxArray*);
BEX_API bool bxIsComplex(const bxArray*);
BEX_API bool bxIsNumeric(const bxArray *ba);
BEX_API bool bxIsEmpty(const bxArray *ba);
BEX_API bool bxIsScalar(const bxArray *ba);
BEX_API double bxGetScalar(const bxArray *ba);

// 浮点数组
BEX_API bxArray* bxCreateDoubleMatrix(baSize, baSize, bxComplexity);
BEX_API bxArray* bxCreateNumericMatrix(baSize, baSize, bxClassID, bxComplexity);
BEX_API bxArray* bxCreateNumericArray(baSize, const baSize *, bxClassID, bxComplexity);
BEX_API bxArray* bxCreateDoubleScalar(double);
BEX_API bxArray* bxCreateSingleScalar(float);
BEX_API bxArray* bxCreateComplexDoubleScalar(double, double);
BEX_API bxArray* bxCreateComplexSingleScalar(float, float);
// 旧版 getter
BEX_API double* bxGetPr(const bxArray*);
BEX_API double* bxGetDoubles(const bxArray*);
BEX_API float* bxGetSingles(const bxArray*);
BEX_API void* bxGetComplexDoubles(const bxArray*);
BEX_API void* bxGetComplexSingles(const bxArray*);
// v3 新增新版 getter，区分了读写和只读的情况
BEX_API const double* bxGetPrRO(const bxArray*);
BEX_API const double* bxGetDoublesRO(const bxArray*);
BEX_API const float* bxGetSinglesRO(const bxArray*);
BEX_API const void* bxGetComplexDoublesRO(const bxArray*);
BEX_API const void* bxGetComplexSinglesRO(const bxArray*);
// RW
BEX_API double* bxGetPrRW(const bxArray*);
BEX_API double* bxGetDoublesRW(const bxArray*);
BEX_API float* bxGetSinglesRW(const bxArray*);
BEX_API void* bxGetComplexDoublesRW(const bxArray*);
BEX_API void* bxGetComplexSinglesRW(const bxArray*);
// end of getters
BEX_API bool bxIsRealDouble(const bxArray*);
BEX_API bool bxIsRealSingle(const bxArray*);
BEX_API bool bxIsComplexDouble(const bxArray*);
BEX_API bool bxIsComplexSingle(const bxArray*);

// 整数数组
BEX_API bxArray* bxCreateInt8Scalar(int8_t);
BEX_API bxArray* bxCreateInt16Scalar(int16_t);
BEX_API bxArray* bxCreateInt32Scalar(int32_t);
BEX_API bxArray* bxCreateInt64Scalar(int64_t);
BEX_API bxArray* bxCreateUInt8Scalar(uint8_t);
BEX_API bxArray* bxCreateUInt16Scalar(uint16_t);
BEX_API bxArray* bxCreateUInt32Scalar(uint32_t);
BEX_API bxArray* bxCreateUInt64Scalar(uint64_t);
BEX_API int8_t* bxGetInt8s(const bxArray*);
BEX_API int16_t* bxGetInt16s(const bxArray*);
BEX_API int32_t* bxGetInt32s(const bxArray*);
BEX_API int64_t* bxGetInt64s(const bxArray*);
BEX_API uint8_t* bxGetUInt8s(const bxArray*);
BEX_API uint16_t* bxGetUInt16s(const bxArray*);
BEX_API uint32_t* bxGetUInt32s(const bxArray*);
BEX_API uint64_t* bxGetUInt64s(const bxArray*);
// v3 新增新版 getter，区分了读写和只读的情况
BEX_API const int8_t* bxGetInt8sRO(const bxArray*);
BEX_API const int16_t* bxGetInt16sRO(const bxArray*);
BEX_API const int32_t* bxGetInt32sRO(const bxArray*);
BEX_API const int64_t* bxGetInt64sRO(const bxArray*);
BEX_API const uint8_t* bxGetUInt8sRO(const bxArray*);
BEX_API const uint16_t* bxGetUInt16sRO(const bxArray*);
BEX_API const uint32_t* bxGetUInt32sRO(const bxArray*);
BEX_API const uint64_t* bxGetUInt64sRO(const bxArray*);
// RW
BEX_API int8_t* bxGetInt8sRW(const bxArray*);
BEX_API int16_t* bxGetInt16sRW(const bxArray*);
BEX_API int32_t* bxGetInt32sRW(const bxArray*);
BEX_API int64_t* bxGetInt64sRW(const bxArray*);
BEX_API uint8_t* bxGetUInt8sRW(const bxArray*);
BEX_API uint16_t* bxGetUInt16sRW(const bxArray*);
BEX_API uint32_t* bxGetUInt32sRW(const bxArray*);
BEX_API uint64_t* bxGetUInt64sRW(const bxArray*);
// end of getters
BEX_API bool bxIsInt8(const bxArray*);
BEX_API bool bxIsInt16(const bxArray*);
BEX_API bool bxIsInt32(const bxArray*);
BEX_API bool bxIsInt64(const bxArray*);
BEX_API bool bxIsUInt8(const bxArray*);
BEX_API bool bxIsUInt16(const bxArray*);
BEX_API bool bxIsUInt32(const bxArray*);
BEX_API bool bxIsUInt64(const bxArray*);

// 字符数组（char）
BEX_API bxArray* bxCreateCharMatrixFromStrings(baSize, const char **);
BEX_API bxArray* bxCreateCharArray(baSize, const baSize *);
BEX_API bxArray* bxCreateString(const char *);
BEX_API char* bxGetChars(const bxArray*);
BEX_API const char* bxGetCharsRO(const bxArray*);
BEX_API char* bxGetCharsRW(const bxArray*);
BEX_API bool bxIsChar(const bxArray*);

// 逻辑数组（logical）
BEX_API bxArray* bxCreateLogicalMatrix(baSize, baSize);
BEX_API bxArray* bxCreateLogicalArray(baSize, const baSize *);
BEX_API bxArray* bxCreateLogicalScalar(bool);
BEX_API bool* bxGetLogicals(const bxArray*);
BEX_API const bool* bxGetLogicalsRO(const bxArray*);
BEX_API bool* bxGetLogicalsRW(const bxArray*);
BEX_API bool bxIsLogical(const bxArray*);

// 字符串（string）
BEX_API bxArray* bxCreateStringMatrix(baSize m, baSize n);
BEX_API bxArray* bxCreateStringScalar(const char *str);
BEX_API bxArray* bxCreateStringArray(baSize ndim, const baSize *dims);
BEX_API bxArray* bxCreateStringMatrixFromStrings(baSize m, baSize n, const char **str);
BEX_API const char* bxGetString(const bxArray*, baIndex);
BEX_API baSize bxGetStringLength(const bxArray*ba, baIndex ind);
BEX_API void bxSetString(bxArray*, baIndex, const char *);
BEX_API bool bxIsString(const bxArray*);
// 已过时函数，不建议使用
BEX_API bxArray* bxCreateStringObj(const char *);
BEX_API baSize bxGetStringLen(const bxArray*);
BEX_API const char* bxGetStringDataPr(const bxArray*);
BEX_API void bxSetStringFromCStr(bxArray*, const char *);

// 结构体
BEX_API bxArray* bxCreateStructMatrix(baSize, baSize, int, const char **);
BEX_API bxArray* bxCreateStructArray(baSize, const baSize *, int, const char **);
BEX_API bxArray* bxExtractStructRows(const bxArray *ba, const baIndex *row_ind, int nrow);
BEX_API bxArray* bxExtractStructSubBlock(const bxArray *ba, const baIndex *row_ind, int nrow, const baIndex *col_ind, int ncol);
BEX_API bxArray* bxGetField(const bxArray*, baIndex, const char *);
BEX_API const bxArray* bxGetFieldRO(const bxArray*, baIndex, const char *);
BEX_API bxArray* bxGetFieldRW(const bxArray*, baIndex, const char *);
BEX_API bxArray* bxGetFieldByNumber(const bxArray*, baIndex, int);
BEX_API const bxArray* bxGetFieldByNumberRO(const bxArray*, baIndex, int);
BEX_API bxArray* bxGetFieldByNumberRW(const bxArray*, baIndex, int);
BEX_API baSize bxGetNumberOfFields(const bxArray*);
BEX_API int bxGetFieldNumber(const bxArray*, const char *);
BEX_API const char* bxGetFieldNameByNumber(const bxArray*, int);
BEX_API bool bxIsField(const bxArray *ba, const char *fieldname);
BEX_API void bxSetField(bxArray*, baIndex, const char *, bxArray*);
BEX_API void bxSetFieldByNumber(bxArray*, baIndex, int, bxArray*);
BEX_API void bxAddField(bxArray*, const char *);
BEX_API void bxAddFieldAt(bxArray*, baIndex, const char *);
BEX_API void bxRenameField(bxArray*, baIndex, const char *);
BEX_API void bxRemoveField(bxArray*, const char *);
BEX_API bool bxIsStruct(const bxArray*);

// 元胞数组（cell）
BEX_API bxArray* bxCreateCellMatrix(baSize, baSize);
BEX_API bxArray* bxCreateCellArray(baSize, const baSize *);
BEX_API bxArray* bxGetCell(const bxArray*, baIndex);
BEX_API const bxArray* bxGetCellRO(const bxArray*, baIndex);
BEX_API bxArray* bxGetCellRW(const bxArray*, baIndex);
BEX_API void bxSetCell(bxArray*, baIndex, bxArray*);
BEX_API bool bxIsCell(const bxArray*);

// 稀疏矩阵
BEX_API bxArray* bxCreateSparse(baSize, baSize, baSize, bxComplexity);
BEX_API bxArray* bxCreateSparseNumericMatrix(baSize, baSize, baSize, bxClassID, bxComplexity);
BEX_API bxArray* bxCreateSparseLogicalMatrix(baSize, baSize, baSize);
BEX_API bool bxIsSparse(const bxArray*);
BEX_API bool bxIsSparseRealDouble(const bxArray*);
BEX_API bool bxIsSparseRealSingle(const bxArray*);
BEX_API bool bxIsSparseComplexDouble(const bxArray*);
BEX_API bool bxIsSparseComplexSingle(const bxArray*);
BEX_API bool bxIsSparseLogical(const bxArray*);
// 旧版 getters
BEX_API double* bxGetSparseDoubles(const bxArray*);
BEX_API float* bxGetSparseSingles(const bxArray*);
BEX_API void* bxGetSparseComplexDoubles(const bxArray*);
BEX_API void* bxGetSparseComplexSingles(const bxArray*);
BEX_API bool* bxGetSparseLogicals(const bxArray*);
BEX_API baSparseIndex* bxGetIr(const bxArray*);
BEX_API baSparseIndex* bxGetJc(const bxArray*);
// v3 getters
BEX_API const double* bxGetSparseDoublesRO(const bxArray*);
BEX_API const float* bxGetSparseSinglesRO(const bxArray*);
BEX_API const void* bxGetSparseComplexDoublesRO(const bxArray*);
BEX_API const void* bxGetSparseComplexSinglesRO(const bxArray*);
BEX_API const bool* bxGetSparseLogicalsRO(const bxArray*);
BEX_API const baSparseIndex* bxGetIrRO(const bxArray*);
BEX_API const baSparseIndex* bxGetJcRO(const bxArray*);
BEX_API double* bxGetSparseDoublesRW(const bxArray*);
BEX_API float* bxGetSparseSinglesRW(const bxArray*);
BEX_API void* bxGetSparseComplexDoublesRW(const bxArray*);
BEX_API void* bxGetSparseComplexSinglesRW(const bxArray*);
BEX_API bool* bxGetSparseLogicalsRW(const bxArray*);
BEX_API baSparseIndex* bxGetIrRW(const bxArray*);
BEX_API baSparseIndex* bxGetJcRW(const bxArray*);
// end of getters
BEX_API baSize bxGetNnz(const bxArray*);
BEX_API baSize bxGetNzmax(const bxArray*);
BEX_API void bxSetNzmax(bxArray*, baSize);
BEX_API void bxSparseFinalize(bxArray*);

// 函数句柄
BEX_API bool bxIsFunctionHandle(const bxArray*);
BEX_API bxFHandleType bxGetFunctionHandleType(const bxArray*);
BEX_API const char * bxGetFunctionHandleData(const bxArray*);

// 表格
BEX_API bxArray* bxCreateTable(baSize m, baSize n);
BEX_API bxArray* bxCreateNullTable(baSize m, baSize n);
BEX_API bxArray* bxCreateTableFromColumns(baSize n, const bxArray **columns);
BEX_API void bxResizeTableRows(bxArray *ba, baSize nrows);
BEX_API const bxArray* bxGetTableColumnRO(const bxArray *ba, baIndex i);
BEX_API bxArray* bxGetTableColumnRW(const bxArray *ba, baIndex i);
BEX_API const bxArray* bxGetTableColumnByNameRO(const bxArray *ba, const char *name);
BEX_API bxArray* bxGetTableColumnByNameRW(const bxArray *ba, const char *name);
BEX_API void bxSetTableColumn(bxArray *ba, baIndex i, const bxArray *column);
BEX_API void bxSetTableColumnByName(bxArray *ba, const char *name, const bxArray *column);
BEX_API void bxInsertTableColumn(bxArray *ba, baIndex i, bxInsertMode mode, const char *name, const bxArray *column);
BEX_API void bxInsertTableColumnByName(bxArray *ba, const char *ref, bxInsertMode mode, const char *name, const bxArray *column);
BEX_API void bxAppendTableColumn(bxArray *ba, const char *name, const bxArray *column);
BEX_API void bxRemoveTableColumn(bxArray *ba, baIndex i);
BEX_API void bxRemoveTableColumnByName(bxArray *ba, const char *name);
BEX_API void bxRenameTableColumn(bxArray *ba, baIndex i, const char *name);
BEX_API void bxRenameTableColumnByName(bxArray *ba, const char *old_name, const char *name);
BEX_API const char *bxGetTableColumnName(const bxArray *ba, baIndex i);
BEX_API const char *bxGetTableRowName(const bxArray *ba, baIndex i);
BEX_API const char *bxGetTableDimensionName(const bxArray *ba, bxTableDimension dim);
BEX_API void bxSetTableColumnNames(bxArray *ba, const char **names);
BEX_API void bxSetTableRowNames(bxArray *ba, const char **names);
BEX_API void bxSetTableDimensionName(bxArray *ba, bxTableDimension dim, const char *name);
BEX_API bool bxIsTableColumn(const bxArray *ba, const char *name);
BEX_API void bxRenameTableRow(bxArray *ba, baIndex i, const char * name);

// 日期时间（datetime）
BEX_API bxArray* bxCreateDatetimeMatrix(baSize m, baSize n);
BEX_API bxArray* bxCreateDatetimeArray(baSize ndim, const baSize * dim_vec);
BEX_API bxArray* bxCreateDatetimeScalar(double date);
BEX_API bxArray* bxCreateDatetimeScalarFromString(const char *date_str);
BEX_API const double* bxGetDatetimesRO(const bxArray *ba);
BEX_API double* bxGetDatetimesRW(const bxArray *ba);
BEX_API int bxSetDatetimeByString(bxArray *ba, baIndex ind, const char * date_str);
BEX_API int bxSetDatetimeFormat(bxArray *ba, const char *fmt);
BEX_API int bxSetTimeZone(bxArray *ba, const char *tz);
BEX_API void bxGetDatetimeFormat(const bxArray *ba, char *result, baSize len);
BEX_API void bxGetTimeZone(const bxArray *ba, char *result, baSize len);
BEX_API void bxGetDatetimeDisplayString(const bxArray *ba, baIndex ind, char *result, baSize len);

// 持续时间（duration）
BEX_API bxArray* bxCreateDurationMatrix(baSize m, baSize n);
BEX_API bxArray* bxCreateDurationArray(baSize ndim, const baSize * dim_vec);
BEX_API bxArray* bxCreateDurationScalar(double ms);
BEX_API const double* bxGetDurationsRO(const bxArray *ba);
BEX_API double* bxGetDurationsRW(const bxArray *ba);
BEX_API const char *bxGetDurationFormat(const bxArray *ba);
BEX_API bool bxSetDurationFormat(bxArray *ba, const char *fmt);
BEX_API baSize bxGetDurationDisplayString(const bxArray *ba, baIndex ind, char *result, baSize len);

// 日历持续时间（calendarDuration）
BEX_API bxArray* bxCreateCalendarDurationMatrix(baSize m, baSize n);
BEX_API bxArray* bxCreateCalendarDurationArray(baSize ndim, const baSize * dim_vec);
BEX_API bxArray* bxCreateCalendarDurationScalar(int year, int month, int day, int hour, int minute, double second);
BEX_API bxArray* bxCreateCalendarDurationScalarByMS(double ms);
BEX_API const baCalendarDurationElem* bxGetCalendarDurationsRO(const bxArray *ba);
BEX_API baCalendarDurationElem* bxGetCalendarDurationsRW(const bxArray *ba);
BEX_API const char *bxGetCalendarDurationFormat(const bxArray *ba);
BEX_API bool bxSetCalendarDurationFormat(bxArray *ba, const char *fmt);
BEX_API void bxNormalizeCalendarDuration(bxArray *ba);

// 对象（object）
BEX_API bool bxIsClass(const bxArray *ba, const char * classname);
BEX_API bool bxIsClassdef(const bxArray *ba);
BEX_API const char * bxGetClassName(const bxArray *ba);
BEX_API int bxGetInternalClassID(const bxArray *ba);
BEX_API const bxArray * bxGetPropertyRO(const bxArray *ba, baIndex index, const char *propname);
BEX_API bxArray * bxGetPropertyRW(const bxArray *ba, baIndex index, const char *propname);

BEX_API void bxSetProperty(bxArray *ba, baIndex index, const char *propname, const bxArray * value);
BEX_API baSize bxGetNumberOfPublicProperties(const bxArray *ba, bxPubPropMode mode);
BEX_API baSize bxGetPublicPropertyNames(const bxArray *ba, bxPubPropMode mode, const char ** names, baSize n);
BEX_API bxAccessLevel bxGetPropertyAccess(const bxArray *ba, const char *propname, bxPropertyAccessType type);
BEX_API baSize bxGetNumberOfProperties(const bxArray *ba, bxPubPropMode mode);
BEX_API baSize bxGetPropertyNames(const bxArray *ba, bxPubPropMode mode, const char ** names, baSize n);
BEX_API bool bxIsDependentProperty(const bxArray *ba, const char *propname);
BEX_API bool bxIsConstantProperty(const bxArray *ba, const char *propname);

// 时间表
BEX_API bxArray* bxCreateTimeTable(baSize m, baSize n);
BEX_API bxArray* bxCreateNullTimeTable(baSize m, baSize n);
BEX_API bxArray* bxCreateTimeTableFromColumns(baSize n, const bxArray **columns);
BEX_API bool bxIsTimeTableRowTimeDatetime(const bxArray *ba);
BEX_API bool bxIsTimeTableRowTimeDuration(const bxArray *ba);
BEX_API void bxResizeTimeTableRows(bxArray *ba, baSize nrows);
BEX_API const bxArray* bxGetTimeTableColumnRO(const bxArray *ba, baIndex ind);
BEX_API bxArray* bxGetTimeTableColumnRW(const bxArray *ba, baIndex ind);
BEX_API const bxArray* bxGetTimeTableColumnByNameRO(const bxArray *ba, const char *name);
BEX_API bxArray* bxGetTimeTableColumnByNameRW(const bxArray *ba, const char *name);
BEX_API void bxSetTimeTableColumn(bxArray *ba, baIndex ind, const bxArray *column);
BEX_API void bxSetTimeTableColumnByName(bxArray *ba, const char *name, const bxArray *column);
BEX_API void bxInsertTimeTableColumn(bxArray *ba, baIndex ind, bxInsertMode mode, const char *name, const bxArray *column);
BEX_API void bxInsertTimeTableColumnByName(bxArray *ba, const char *ref, bxInsertMode mode, const char *name, const bxArray *column);
BEX_API void bxAppendTimeTableColumn(bxArray *ba, const char *name, const bxArray *column);
BEX_API void bxRemoveTimeTableColumn(bxArray *ba, baIndex ind);
BEX_API void bxRemoveTimeTableColumnByName(bxArray *ba, const char *name);
BEX_API void bxRenameTimeTableColumn(bxArray *ba, baIndex ind, const char *name);
BEX_API void bxRenameTimeTableColumnByName(bxArray *ba, const char *old_name, const char *name);
BEX_API const char *bxGetTimeTableColumnName(const bxArray *ba, baIndex ind);
BEX_API baSize bxGetTimeTableRowTimeString(const bxArray *ba, baIndex ind, char *name, baSize len);
BEX_API const char *bxGetTimeTableDimensionName(const bxArray *ba, bxTableDimension dim);
BEX_API void bxSetTimeTableColumnNames(bxArray *ba, const char **names);
BEX_API void bxSetTimeTableRowTimesByDatetime(bxArray *ba, const double *rowtimes);
BEX_API void bxSetTimeTableRowTimesByDuration(bxArray *ba, const double *rowtimes);
BEX_API void bxRenameTimeTableRow(bxArray *ba, baIndex ind, double rowtime);
BEX_API void bxSetTimeTableDimensionName(bxArray *ba, bxTableDimension dim, const char *name);
BEX_API bool bxIsTimeTableColumn(const bxArray *ba, const char *name);
BEX_API int bxSetTimeTableFormat(bxArray *ba, const char *fmt);
BEX_API int bxSetTimeTableTimeZone(bxArray *ba, const char *tz);
BEX_API baSize bxGetTimeTableFormat(const bxArray *ba, char *result, baSize len);
BEX_API baSize bxGetTimeTableTimeZone(const bxArray *ba, char *result, baSize len);

// 分类数组
BEX_API bxArray *bxCreateCategoricalMatrix(baSize m, baSize n, bxCategoricalType type);
BEX_API bxArray *bxCreateCategoricalArray(baSize ndim, const baSize *dim_vec, bxCategoricalType type);
BEX_API const int64_t *bxGetCategoricalRO(const bxArray *ba);
BEX_API int64_t *bxGetCategoricalRW(bxArray *ba);
BEX_API baSize bxGetCategoricalDisplayString(const bxArray *ba, baIndex ind, char *result, baSize len);
BEX_API baSize bxGetCategoricalCategoryNum(const bxArray *ba);
BEX_API baSize bxGetCategoricalCategoryName(const bxArray *ba, int64_t code, char *result, baSize len);
BEX_API int64_t bxGetCategoricalCategoryCode(const bxArray *ba, const char *name);
BEX_API bool bxIsCategoricalProtected(const bxArray *ba);
BEX_API bool bxIsCategoricalOrdinal(const bxArray *ba);
BEX_API bxCategoricalType bxGetCategoricalType(const bxArray *ba);
BEX_API void bxSetCategoricalCategoryNames(bxArray *ba, baSize num, const char **names);
BEX_API int64_t bxAddCategoryName(bxArray *ba, const char *name);
BEX_API void bxRenameCategoryByName(bxArray *ba, const char *old_name, const char *new_name);
BEX_API void bxRenameCategoryByCode(bxArray *ba, int64_t code, const char *new_name);
BEX_API void bxRemoveCategoryNameByName(bxArray *ba, const char *name);
BEX_API void bxRemoveCategoryNameByCode(bxArray *ba, int64_t code);
BEX_API void bxReorderCategoryNames(bxArray *ba);

// 创建和删除
BEX_API bxArray* bxDuplicateArray(const bxArray*);
BEX_API bxArray* bxDuplicateArrayS(const bxArray*);
BEX_API void bxCopyArray(const bxArray *src, bxArray *dst);
BEX_API void bxCopyArrayS(const bxArray *src, bxArray *dst);
BEX_API void bxDestroyArray(bxArray*);

// 类型转化
BEX_API baInt bxAsInt(const bxArray* ba, int *perr);
BEX_API int bxAsCStr(const bxArray *ba, char *buffer, baSize size);
BEX_API int bxMakeArrayComplex(bxArray *ba);
BEX_API int bxMakeArrayReal(bxArray *ba);
BEX_API void bxResetArray(bxArray *ba, bxClassID id, bxComplexity c, bxSparsity s);

// 输出与调试
BEX_API int bxPrintf(const char *, ...);
BEX_API void bxErrMsgTxt(const char *);
BEX_API void bxArrayToStdout(const bxArray *ba, int line_width);
BEX_API baSize bxArrayToCStr(const bxArray *ba, int line_width, int phase, char * buffer, baSize len);

// 辅助函数
BEX_API baIndex bxCalcSingleSubscript(const bxArray*, int, baIndex*);
BEX_API const char * bxGetBaltamaticaRoot(void);
BEX_API const char * bxClassIDCStr(bxClassID id);
BEX_API bxArray * bxCreateVoid(int flag);

// 变量列表
BEX_API baSize bxGetVariableListLength(const bxArray *ba);
BEX_API baSize bxReadVariableList(const bxArray *ba, bxArray **p, baSize len);
BEX_API baSize bxReadVariableListConst(const bxArray *ba, const bxArray **p, baSize len);
BEX_API bxArray *bxGetVariableListElement(const bxArray *ba, baIndex ind);
BEX_API bool bxIsVariableList(const bxArray *ba);

// bex 外部数据
BEX_API int bxRegisterCStruct(const char *, cstruct_copy_t, cstruct_delete_t);
BEX_API int bxSetCStructName(int id, const char *name);
BEX_API int bxSetCStructToString(int id, cstruct_to_string_t to_s, cstruct_to_string_delete_t to_s_deleter);
BEX_API void * bxGetCStruct(int, const bxArray*);
BEX_API bxArray *bxCreateCStruct(int, void *);
BEX_API bool bxIsExtern(const bxArray * ba);
BEX_API bool bxIsExternID(const bxArray * ba, int id);
BEX_API int bxRegisterUnaryOperator(const char *, const char *, int, bexfun_t);
BEX_API int bxRegisterBinaryOperator(const char *, const char *, int, int, bexfun_t);
BEX_API int bxRegisterTernaryOperator(const char *, const char *, int, int, int, bexfun_t);
BEX_API int bxRegisterUnaryOperatorID(const char *, bxOperatorID, int, bexfun_t);
BEX_API int bxRegisterBinaryOperatorID(const char *, bxOperatorID, int, int, bexfun_t);
BEX_API int bxRegisterTernaryOperatorID(const char *, bxOperatorID, int, int, int, bexfun_t);
BEX_API int bxRegisterOperator(const char *, const char *, int, bexfun_t);
BEX_API int bxRegisterOperatorID(const char *, bxOperatorID, int, bexfun_t);

// 函数重载
BEX_API int bxOverloadFunction(const char *, const char *, bexfun_t);
BEX_API void bxReturnOverloadFailure(void);
BEX_API void bxReturnOverloadFailureMsg(const char *);

// Baltamatica 插件函数原型
BEX_EXPORT int bxPluginInitLib(void*);
BEX_EXPORT int bxPluginInit(int, const bxArray *[]);
BEX_EXPORT int bxPluginFini(void);
BEX_EXPORT bexfun_info_t *bxPluginFunctions(void);

// BEX 文件原型
BEX_EXPORT void bexFunction(int, bxArray *[], int, const bxArray*[]);

// 向内核和前端的轮询函数
BEX_API void * bxK2FQuery(const char *, void *);
BEX_API void * bxF2KQuery(const char *, void *);

// 执行函数和语句
BEX_API int bxEvalString(const char *);
BEX_API int bxEvalIn(const char *ws, const char *expr, bxArray **plhs);
BEX_API int bxCallBaltamatica(int, bxArray *[], int, const bxArray *[], const char *);
BEX_API int bxCallBaltamaticaF(int, bxArray *[], int, const bxArray *[], const bxArray *);

// 工作区操作
BEX_API int bxAddVariable(const char *name, bxArray *value, bxVarOpMode mode);
BEX_API int bxRenameVariable(const char *old_name, const char *new_name, bxVarOpMode mode);
BEX_API void bxRemoveVariable(const char *name);
BEX_API void bxGetVariableNames(const char ***result, int * num);
BEX_API void bxFreeVariableNames(const char **result);

// bxGetXxxxs 等函数是否关联到 RW
// 从而在调用的时候会自动触发写入时复制
#ifdef BALTAM_BEX_LEGACY_GETTER_RW
#define bxGetPr bxGetPrRW
#define bxGetInt8s bxGetInt8sRW
#define bxGetInt16s bxGetInt16sRW
#define bxGetInt32s bxGetInt32sRW
#define bxGetInt64s bxGetInt64sRW
#define bxGetUInt8s bxGetUInt8sRW
#define bxGetUInt16s bxGetUInt16sRW
#define bxGetUInt32s bxGetUInt32sRW
#define bxGetUIn64s bxGetUInt64sRW
#define bxGetDoubles bxGetDoublesRW
#define bxGetSingles bxGetSinglesRW
#define bxGetComplexDoubles bxGetComplexDoublesRW
#define bxGetComplexSingles bxGetComplexSinglesRW
#define bxGetChars bxGetCharsRW
#define bxGetLogicals bxGetLogicalsRW
#define bxGetField bxGetFieldRW
#define bxGetFieldByNumber bxGetFieldByNumberRW
#define bxGetCell bxGetCellRW
#define bxGetSparseDoubles bxGetSparseDoublesRW
#define bxGetSparseSingles bxGetSparseSinglesRW
#define bxGetSparseComplexDoubles bxGetSparseComplexDoublesRW
#define bxGetSparseComplexSingles bxGetSparseComplexSinglesRW
#define bxGetSparseLogicals bxGetSparseLogicalsRW
#define bxGetIr bxGetIrRW
#define bxGetJc bxGetJcRW
#endif

// ---

#ifdef __cplusplus
}
#endif // of __cplusplus

#endif

