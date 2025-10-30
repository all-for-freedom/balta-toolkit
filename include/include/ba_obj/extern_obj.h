/*
 * 北太天元（Baltamatica）开发者工具箱头文件。
 *
 * 该文件包含使用 SDK 中外部对象基类的定义。
 * 适用于 v4.1 版本的北太天元。
 *
 * 版权所有 © 2021-2025，北太振寰（重庆）科技有限公司
 */

#ifndef BALTAM_EXTERN_OBJ_H
#define BALTAM_EXTERN_OBJ_H

#include <string>

namespace baltam {
    /**
     * @class extern_obj_base
     * @brief 所有不属于北太天元的外部对象基类。
     *
     * 当合作开发者/社区开发者使用 C++ 开发并且需要将某些对象临时托管到北太天元中时，
     * 必须从这个类继承。
     *
     * 软件内核对该类对象仅定义抽象的方法，具体实现交给开发者。软件无需了解
     * @p extern_obj_base 子类的实现细节。
     */
    struct extern_obj_base {
        virtual extern_obj_base* dup() const { return nullptr; }
        virtual ~extern_obj_base() {};
        virtual std::string to_string() const { return ""; }
        virtual std::string classname() const { return "extern object"; };
        int sid; ///< 整数，用于存储内核自动分配的外部类 ID
    };
}

#endif

