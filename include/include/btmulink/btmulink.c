#include "simstruct.h"

#ifndef S_FUNCTION_NAME
#error S_FUNCTION_NAME must be defined
#endif

#define _QUOTE1(name) #name
#define _QUOTE(name) _QUOTE1(name)

#define _BXERR(cond, msg)                                                                                              \
    do                                                                                                                 \
    {                                                                                                                  \
        if (cond)                                                                                                      \
        {                                                                                                              \
            bxErrMsgTxt(msg);                                                                                          \
            return;                                                                                                    \
        }                                                                                                              \
    } while (0)

static void create_simstruct(bxArray *plhs[], int nrhs, const bxArray *prhs[])
{
    const char *fieldnames[] = {"t",
                                "sampleTime",
                                "numContStates",
                                "numDiscStates",
                                "numY",
                                "numU",
                                "sysDirFeedThrough",
                                "numSampleTimes",
                                "numSFcnParams",
                                "contStates",
                                "discStates",
                                "dlgNum",
                                "dlgParams",
                                "errorStatus"};
    plhs[2]                  = bxCreateStructMatrix(1, 1, 14, fieldnames);
    ssSetTime(plhs[2], *bxGetDoublesRW(prhs[0]));
    ssSetSampleTime(plhs[2], 0);
    ssSetNumContStates(plhs[2], 0);
    ssSetNumDiscStates(plhs[2], 0);
    ssSetNumOutputs(plhs[2], 0);
    ssSetNumInputs(plhs[2], 0);
    ssSetDirectFeedThrough(plhs[2], 0);
    ssSetNumSampleTimes(plhs[2], 0);
    ssSetNumSFcnParams(plhs[2], 0);
    bxSetField(plhs[2], 0, "contStates", bxCreateDoubleMatrix(0, 0, bxREAL));
    bxSetField(plhs[2], 0, "discStates", bxCreateDoubleMatrix(0, 0, bxREAL));
    _ssSetSFcnParamsCount(plhs[2], nrhs - 4);
    if (nrhs > 4)
    {
        bxSetField(plhs[2], 0, "dlgParams", bxCreateCellMatrix(1, nrhs - 4));
        for (int i = 0; i < nrhs - 4; i++)
            _ssSetSFcnParam(plhs[2], i, bxDuplicateArray(prhs[i + 4]));
    }
    else
        bxSetField(plhs[2], 0, "dlgParams", bxCreateCellMatrix(0, 0));
    bxSetField(plhs[2], 0, "errorStatus", bxCreateString(""));
}

/**
 * S-function 入口
 * flag = 0
 *      函数原型 [sys,x0,str,ts]=f(t,x,u,flag,p1,p2,...)
 * flag = 1,2
 *      函数原型 sys=f(t,x,u,flag,simstruct)
 */
void bexFunction(int_T nlhs, bxArray *plhs[], int nrhs, const bxArray *prhs[])
{
#ifndef NDEBUG
    _BXERR(nlhs < 1, "S-Function 模块 " _QUOTE(S_FUNCTION_NAME) " 函数返回值个数应当大于 1.");
    _BXERR(nrhs < 4, "S-Function 模块 " _QUOTE(S_FUNCTION_NAME) " 初始化函数参数个数应当不小于 4.");
#endif

    const real_T *flagDbl = bxGetDoublesRO(prhs[3]);
    int_T         flag    = (int_T)(*flagDbl);

    switch (flag)
    {
        case 0:
        {
#ifndef NDEBUG
            _BXERR(nlhs != 4, "S-Function 模块 " _QUOTE(S_FUNCTION_NAME) " 初始化函数返回值个数应当是 4.");
#endif
            create_simstruct(plhs, nrhs, prhs);
            /* 用户编写，初始化大小 */
            mdlInitializeSizes(plhs[2]);

#if defined(MDL_CHECK_PARAMETERS)
            /* 用户编写，检查参数 */
            mdlCheckParameters(plhs[2]);
#endif
            /* 如果有错误信息，直接返回，由北太真元处理 */
            if (ssGetErrorStatus(plhs[2]) != NULL)
            {
                plhs[0] = bxCreateDoubleMatrix(0, 0, bxREAL);
                plhs[1] = bxCreateDoubleMatrix(0, 0, bxREAL);
                plhs[3] = bxCreateDoubleMatrix(0, 0, bxREAL);
                return;
            }

            /* 用户编写，设置采样时间 */
            mdlInitializeSampleTimes(plhs[2]);

            /* 为连续状态分配内存 */
            int_T nc = ssGetNumContStates(plhs[2]);
            if (nc > 0)
                bxSetField(plhs[2], 0, "contStates", bxCreateDoubleMatrix(nc, 1, bxREAL));
            /* 为离散状态分配内存 */
            int_T nd = ssGetNumDiscStates(plhs[2]);
            if (nd > 0)
                bxSetField(plhs[2], 0, "discStates", bxCreateDoubleMatrix(nd, 1, bxREAL));

#if defined(MDL_INITIALIZE_CONDITIONS)
            /* 用户编写，初始化状态变量 */
            mdlInitializeConditions(plhs[2]);
#endif
            // 复制初始连续状态
            if (nc > 0)
            {
                plhs[1]          = bxCreateDoubleMatrix(nc, 1, bxREAL);
                real_T       *x0 = bxGetDoublesRW(plhs[1]);
                const real_T *x  = bxGetDoublesRO(bxGetFieldRO(plhs[2], 0, "contStates"));
                for (int i = 0; i < nc; i++)
                    x0[i] = x[i];
            }
            else
                plhs[1] = bxCreateDoubleMatrix(0, 0, bxREAL);

            plhs[0]     = bxCreateDoubleMatrix(1, 7, bxREAL);
            real_T *sys = bxGetDoublesRW(plhs[0]);
            sys[0]      = ssGetNumContStates(plhs[2]);
            sys[1]      = ssGetNumDiscStates(plhs[2]);
            sys[2]      = ssGetNumOutputs(plhs[2]);
            sys[3]      = ssGetNumInputs(plhs[2]);
            sys[4]      = 0;
            sys[5]      = ssIsDirectFeedThrough(plhs[2]);
            sys[6]      = ssGetNumSampleTimes(plhs[2]);

            plhs[3] = bxCreateDoubleScalar(ssGetSampleTime(plhs[2]));

            break;
        }
        case 1:
        {
#ifndef NDEBUG
            _BXERR(nlhs != 1, "S-Function 模块 " _QUOTE(S_FUNCTION_NAME) " 更新函数返回值个数应当是 1.");
            _BXERR(nrhs != 5, "S-Function 模块 " _QUOTE(S_FUNCTION_NAME) " 更新函数参数个数应当是 5.");
#endif

            int_T nc = ssGetNumContStates(prhs[4]);
            if (nc > 0)
                plhs[0] = bxCreateDoubleMatrix(nc, 1, bxREAL);
            else
                plhs[0] = bxCreateDoubleMatrix(0, 0, bxREAL);

#if defined(MDL_INCREMENT)
            real_T       *y = bxGetDoublesRW(plhs[0]);
            const real_T *x = bxGetDoublesRO(prhs[1]);
            const real_T *u = bxGetDoublesRO(prhs[2]);

            /* 用户编写, 计算连续状态导数 */
            mdlIncrement(y, x, u, prhs[4]);
#endif

            break;
        }
        case 2:
        {
#ifndef NDEBUG
            _BXERR(nlhs != 1, "S-Function 模块 " _QUOTE(S_FUNCTION_NAME) " 更新函数返回值个数应当是 1.");
            _BXERR(nrhs != 5, "S-Function 模块 " _QUOTE(S_FUNCTION_NAME) " 更新函数参数个数应当是 5.");
#endif

            int_T no = ssGetNumOutputs(prhs[4]);
            if (no > 0)
                plhs[0] = bxCreateDoubleMatrix(no, 1, bxREAL);
            else
                plhs[0] = bxCreateDoubleMatrix(0, 0, bxREAL);

            real_T       *y = bxGetDoublesRW(plhs[0]);
            const real_T *x = bxGetDoublesRO(prhs[1]);
            const real_T *u = bxGetDoublesRO(prhs[2]);

            /* 用户编写, 计算输出 */
            mdlUpdate(y, x, u, prhs[4]);

            break;
        }
        default:
        {
            bxErrMsgTxt("S-Function 模块 " _QUOTE(S_FUNCTION_NAME) " flag 设置错误.");
            break;
        }
    }
}
