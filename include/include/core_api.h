/*
 * ===========================================================================
 *
 *       Filename:  core_api.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  03/31/2025 04:13:03 PM
 *       Revision:  none
 *       Compiler:  gcc/g++
 *
 *         Author:  Haoyang Liu (@liuhy), liuhaoyang@pku.edu.cn
 *   Organization:  BDA, PKU
 *
 * ===========================================================================
 */

#ifndef BALTAM_CORE_CORE_API_H
#define BALTAM_CORE_CORE_API_H

#include "api_helper_macro.h"

#ifdef baltam_core_EXPORTS 
#define CORE_API BALTAM_HELPER_DLL_EXPORT
#else
#define CORE_API BALTAM_HELPER_DLL_IMPORT
#endif
#define CORE_LOCAL BALTAM_HELPER_DLL_LOCAL

#endif

