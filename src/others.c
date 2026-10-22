/*********************************************************************************************************************/
/*                                                                                                                   */
/*                ███████╗██████╗  █████╗  ██████╗███████╗    ███╗   ███╗ █████╗ ████████╗██╗  ██╗   (R)             */
/*                ██╔════╝██╔══██╗██╔══██╗██╔════╝██╔════╝    ████  ████║██╔══██╗╚══██╔══╝██║  ██║                   */
/*                ███████╗██████╔╝███████║██║     █████╗      ██╔████╔██║███████║   ██║   ███████║                   */
/*                ╚════██║██╔═══╝ ██╔══██║██║     ██╔══╝      ██║╚██╔╝██║██╔══██║   ██║   ██╔══██║                   */
/*                ███████║██║     ██║  ██║╚██████╗███████╗    ██║ ╚═╝ ██║██║  ██║   ██║   ██║  ██║                   */
/*                ╚══════╝╚═╝     ╚═╝  ╚═╝ ╚═════╝╚══════╝    ╚═╝     ╚═╝╚═╝  ╚═╝   ╚═╝   ╚═╝  ╚═╝   (V0.1.3)        */
/*                                                                                                                   */
/*                          For linear calculations of spatial translation and rotation.                             */
/*                              Create by scilogyhunter <scilogyhunter@gmail.com>                                    */
/*                                                                                                                   */
/*********************************************************************************************************************/
/*!
 * @file others.c
 * @brief 空间数学库其它实现文件
 * @author scilogyhunter
 * @date 2026.10.22
 * @version V0.1.3
 *
 * 本文件实现了空间数学库其它函数，包括安全三角函数、欧拉角操作、旋转矢量操作、轴角操作等。
 * 提供了各种旋转表示的基本操作和转换功能。
 */

/*!
 * @defgroup others_modify 修改记录
 * @{
 */

/*!
 * @brief 修改记录表
 * 
 * | 修改日期    | 修改人        | 版本号  | 修改内容                     |
 * |------------|---------------|---------|----------------------------|
 * | 2025.09.01 | scilogyhunter | V0.1.0  | 初始版本创建                |
 * | 2025.11.18 | scilogyhunter | V0.1.1  | 完善注释，使用doxygen格式   |
 */

/** @} */ /* end of group others_modify */

#include "spacemath.h"
/*!
 * @brief 安全浮点数比较函数
 * @param a 第一个浮点数
 * @param b 第二个浮点数
 * @return 如果两个浮点数在容差范围内相等则返回true，否则返回false
 * @note 使用预定义的精度容差MEPSILON进行比较，避免浮点数精度问题
 */
bool safe_is_equal(ftype_t a, ftype_t b)
{
    return (MFABS(a - b) <= MEPSILON);
}

/*!
 * @brief 安全浮点数比较函数（指定容差）
 * @param a 第一个浮点数
 * @param b 第二个浮点数
 * @param epsilon 容差
 * @return 如果两个浮点数在指定容差范围内相等则返回true，否则返回false
 * @note 使用指定的容差进行比较，避免浮点数精度问题
 */
bool safe_is_equal_eps(ftype_t a, ftype_t b, ftype_t epsilon)
{
    return (MFABS(a - b) <= epsilon);
}
/*!
 * @brief 安全浮点数零比较函数
 * @param a 浮点数值
 * @return 如果浮点数在容差范围内接近零则返回true，否则返回false
 * @note 使用预定义的精度容差MEPSILON进行比较，避免浮点数精度问题
 */
bool safe_is_zero(ftype_t a)
{
    return (MFABS(a) <= MEPSILON);
}   
/*!
 * @brief 安全arcsin函数，限制输入在[-1,1]范围内
 * @param x 输入值，应在[-1,1]范围内
 * @return 返回对应的反正弦值（弧度）
 * @note 防止输入超出有效范围导致的数值错误
 */
ftype_t safe_asin(ftype_t x) 
{
    if (x >= MFLOAT_C(1.0)) return MPI_2;    /* 输入大于等于1，返回π/2 */
    if (x <= -MFLOAT_C(1.0)) return -MPI_2;  /* 输入小于等于-1，返回-π/2 */
    return MASIN(x);                  /* 正常计算反正弦值 */
}


/*!
 * @brief 安全arccos函数，限制输入在[-1,1]范围内
 * @param x 输入值，应在[-1,1]范围内
 * @return 返回对应的反余弦值（弧度）
 * @note 防止输入超出有效范围导致的数值错误
 */
ftype_t safe_acos(ftype_t x) 
{
    if (x >= MFLOAT_C(1.0)) return 0;          /* 输入大于等于1，返回0 */
    if (x <= MFLOAT_C(-1.0)) return MPI;       /* 输入小于等于-1，返回π */
    return MACOS(x);                  /* 正常计算反余弦值 */
}


/*!
 * @brief 有除零保护的反正切函数
 * @param y 分子值
 * @param x 分母值
 * @return 返回对应的反正切值（弧度）
 * @note 处理分母接近零的特殊情况，避免除零错误
 */
ftype_t safe_atan2(ftype_t y, ftype_t x)
{
    ftype_t a;                       /* 存储计算结果 */
    #if (CFG_FLOATWORD_BITSIZE == 128)
        ftype_t epsilon = MFLOAT_C(1e-12);  /* 定义一个小的容差值 */
    #else
        ftype_t epsilon = MFLOAT_C(1e-3);  /* 定义一个小的容差值 */
    #endif


    /* 检查分母是否接近零 */
    if (MFABS(x)  <= epsilon) {
        if (MFABS(y) <= epsilon) {
            a = MFLOAT_C(0.0);                  /* 分子分母都接近零，返回0 */
        } else if (y > epsilon) {
            a = MPI_2;                          /* 分母接近零，分子为正，返回π/2 */
        } else {
            a = -MPI_2;                        /* 分母接近零，分子为负，返回-π/2 */
        }
    } else if (x > epsilon) {
        a = MATAN (y / x);                        /* 分母为正，正常计算 */
    } else {
        if (y >= epsilon) {
            a = MATAN (y / x) + MPI;              /* 分母为负，分子为正，返回π + atan(y/x) */
        } else {
            a = MATAN (y / x) - MPI;              /* 分母为负，分子为负，返回-π + atan(y/x) */
        }
    }

    return  a;                                  /* 返回计算结果 */
}

/**********************************************************************************************************************
 * End of spacemath file
 *********************************************************************************************************************/
