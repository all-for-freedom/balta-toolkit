/*
 * 北太天元（Baltamatica）开发者工具箱头文件。
 *
 * 该文件包含日历持续时间数组元素的定义。
 * 适用于 v3.5+ 的北太天元。
 *
 * 版权所有 © 2021-2025，北太振寰（重庆）科技有限公司
 */

#ifndef BALTAM_CORE_CALENDAR_DURATION_ELEM_H
#define BALTAM_CORE_CALENDAR_DURATION_ELEM_H

#include "core_api.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @class ba_calendar_duration_elem
 * @brief 表示日历持续时间的结构体。
 *
 * 该结构体为日历持续时间数组的基本元素，字段包括年、季度、月、周、天数、小时、
 * 分钟、秒。除了秒为 @p double 类型外，其余字段均为 @p int 类型。
 */
#ifdef __cplusplus
struct CORE_API ba_calendar_duration_elem {
#else
struct ba_calendar_duration_elem {
#endif
    int year; ///< 年
    int quarter; ///< 季度，一个季度有 3 个月
    int month; ///< 月
    int week; ///< 周，一周有 7 天
    int day; ///< 天
    int hour; ///< 小时
    int minute; ///< 分钟
    double second; ///< 秒
#ifdef __cplusplus
    /**
     * @brief 默认构造函数。
     *
     * 构造一个默认日历持续时间元素，各个字段均为 0。
     */
    ba_calendar_duration_elem();

    /**
     * @brief 使用给定字段构造日历持续时间元素。
     * @param y 年
     * @param m 月
     * @param d 日
     * @param h 时
     * @param mi 分
     * @param s 秒
     *
     * 使用年月日时分秒构造日历持续时间元素。<b>不会</b>进行归一化（即不会将 60s 换算为 1min）。
     */
    ba_calendar_duration_elem(int y, int m, int d, int h, int mi, double s);
#endif
};

typedef struct ba_calendar_duration_elem baCalendarDurationElem;

#ifdef __cplusplus
}
#endif

#endif

