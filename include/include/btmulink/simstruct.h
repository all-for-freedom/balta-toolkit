#ifndef __SIMSTRUCT_H__
#define __SIMSTRUCT_H__

#include "btmulink_types.h"
#include <bex/bex.h>

#ifdef __cplusplus
#define SS_STATIC_CAST(T, E) static_cast<T>(E)
#else
#define SS_STATIC_CAST(T, E) (T)(E)
#endif

typedef bxArray SimStruct;

/* Time - s-function 当前仿真时间 */
#define ssGetTime(S) (*bxGetDoublesRO(bxGetFieldRO(S, 0, "t")))
#define ssSetTime(S, st)                                                                                               \
    do                                                                                                                 \
    {                                                                                                                  \
        bxSetField(S, 0, "t", bxCreateDoubleScalar(st));                                                               \
    } while (0)

/** SampleTime - s-function 采样时间
 * >0, 采样时间;
 * 0, 连续状态;
 * -1, 继承;
 * -2, 求解器步长;
 * -3, 不变;
 */
#define ssGetSampleTime(S) (*bxGetDoublesRO(bxGetFieldRO(S, 0, "sampleTime")))
#define ssSetSampleTime(S, sampleTime)                                                                                 \
    do                                                                                                                 \
    {                                                                                                                  \
        bxSetField(S, 0, "sampleTime", bxCreateDoubleScalar(sampleTime));                                              \
    } while (0)

/* NumContStates - s-function 连续状态数 */
#define ssGetNumContStates(S) (int_T)(*bxGetDoublesRO(bxGetFieldRO(S, 0, "numContStates")))
#define ssSetNumContStates(S, nContStates)                                                                             \
    do                                                                                                                 \
    {                                                                                                                  \
        bxSetField(S, 0, "numContStates", bxCreateDoubleScalar(nContStates));                                          \
    } while (0)

/* NumDiscStates - s-function 离散状态数 */
#define ssGetNumDiscStates(S) (int_T)(*bxGetDoublesRO(bxGetFieldRO(S, 0, "numDiscStates")))
#define ssSetNumDiscStates(S, nDiscStates)                                                                             \
    do                                                                                                                 \
    {                                                                                                                  \
        bxSetField(S, 0, "numDiscStates", bxCreateDoubleScalar(nDiscStates));                                          \
    } while (0)

/* NumOutputs - s-function 输出端口大小 */
#define ssGetNumOutputs(S) (int_T)(*bxGetDoublesRO(bxGetFieldRO(S, 0, "numY")))
#define ssSetNumOutputs(S, nOutputs)                                                                                   \
    do                                                                                                                 \
    {                                                                                                                  \
        bxSetField(S, 0, "numY", bxCreateDoubleScalar(nOutputs));                                                      \
    } while (0)

/* NumInputs - s-function 输入端口大小 */
#define ssGetNumInputs(S) (int_T)(*bxGetDoublesRO(bxGetFieldRO(S, 0, "numU")))
#define ssSetNumInputs(S, nInputs)                                                                                     \
    do                                                                                                                 \
    {                                                                                                                  \
        bxSetField(S, 0, "numU", bxCreateDoubleScalar(nInputs));                                                       \
    } while (0)

/* DirectFeedThrough - s-function 是否是直接馈通的 */
#define ssIsDirectFeedThrough(S) (int_T)(*bxGetDoublesRO(bxGetFieldRO(S, 0, "sysDirFeedThrough")))
#define ssSetDirectFeedThrough(S, dirFeed)                                                                             \
    do                                                                                                                 \
    {                                                                                                                  \
        bxSetField(S, 0, "sysDirFeedThrough", bxCreateDoubleScalar(dirFeed));                                          \
    } while (0)

/* NumSampleTimes - s-function 采样时间数 */
#define ssGetNumSampleTimes(S) (int_T)(*bxGetDoublesRO(bxGetFieldRO(S, 0, "numSampleTimes")))
#define ssSetNumSampleTimes(S, nSampleTimes)                                                                           \
    do                                                                                                                 \
    {                                                                                                                  \
        bxSetField(S, 0, "numSampleTimes", bxCreateDoubleScalar(nSampleTimes));                                        \
    } while (0)

/* NumSFcnParams - s-function 参数个数(用户设置) */
#define ssGetNumSFcnParams(S) (int_T)(*bxGetDoublesRO(bxGetFieldRO(S, 0, "numSFcnParams")))
#define ssSetNumSFcnParams(S, numInputArgs)                                                                            \
    do                                                                                                                 \
    {                                                                                                                  \
        bxSetField(S, 0, "numSFcnParams", bxCreateDoubleScalar(numInputArgs));                                         \
    } while (0)

/* ContStates - s-function 连续状态 */
#define ssGetContStatesPtr(S) bxGetFieldRW(S, 0, "contStates")
#define ssSetContStatesPtr(S, ptr)                                                                                     \
    do                                                                                                                 \
    {                                                                                                                  \
        bxSetField(S, 0, "contStates", ptr);                                                                           \
    } while (0)

#define ssGetContStates(S) bxGetDoublesRW(ssGetContStatesPtr(S))

/* dlgNum - s-function 对话框中参数个数 */
#define ssGetSFcnParamsCount(S) (int_T)(*bxGetDoublesRO(bxGetFieldRO(S, 0, "dlgNum")))
#define _ssSetSFcnParamsCount(S, numInputArgs)                                                                         \
    do                                                                                                                 \
    {                                                                                                                  \
        bxSetField(S, 0, "dlgNum", bxCreateDoubleScalar(numInputArgs));                                                \
    } while (0)

/* dlgParams - s-function 参数 */
#define ssGetSFcnParam(S, index) bxGetCellRO(bxGetFieldRO(S, 0, "dlgParams"), index)
#define _ssSetSFcnParam(S, index, mat)                                                                                 \
    do                                                                                                                 \
    {                                                                                                                  \
        bxSetCell(bxGetFieldRW(S, 0, "dlgParams"), index, mat);                                                        \
    } while (0)

#define ssGetErrorStatus(S) bxGetCharsRO(bxGetFieldRO(S, 0, "errorStatus"))
#define ssSetErrorStatus(S, msg)                                                                                       \
    do                                                                                                                 \
    {                                                                                                                  \
        bxSetField(S, 0, "errorStatus", bxCreateString(msg));                                                          \
    } while (0)

#endif