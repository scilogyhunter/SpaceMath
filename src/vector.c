/*********************************************************************************************************************/
/*                                                                                                                   */
/*                ███████╗██████╗  █████╗  ██████╗███████╗    ███╗   ███╗ █████╗ ████████╗██╗  ██╗   (R)             */
/*                ██╔════╝██╔══██╗██╔══██╗██╔════╝██╔════╝    ████  ████║██╔══██╗╚══██╔══╝██║  ██║                   */
/*                ███████╗██████╔╝███████║██║     █████╗      ██╔████╔██║███████║   ██║   ███████║                   */
/*                ╚════██║██╔═══╝ ██╔══██║██║     ██╔══╝      ██║╚██╔╝██║██╔══██║   ██║   ██╔══██║                   */
/*                ███████║██║     ██║  ██║╚██████╗███████╗    ██║ ╚═╝ ██║██║  ██║   ██║   ██║  ██║                   */
/*                ╚══════╝╚═╝     ╚═╝  ╚═╝ ╚═════╝╚══════╝    ╚═╝     ╚═╝╚═╝  ╚═╝   ╚═╝   ╚═╝  ╚═╝   (V0.1.2)        */
/*                                                                                                                   */
/*                          For linear calculations of spatial translation and rotation.                             */
/*                              Create by scilogyhunter <scilogyhunter@gmail.com>                                    */
/*                                                                                                                   */
/*********************************************************************************************************************/
/*!
 * @file vector.c
 * @brief 向量运算实现文件
 * @author scilogyhunter
 * @date 2025.09.01
 * @version V0.1.2
 *
 * 本文件实现了三维向量的基本运算，包括创建、归一化、点积、叉积、插值等操作。
 * 向量运算在计算机图形学、物理模拟和几何计算中具有广泛应用。
 */

/*!
 * @defgroup vector_modify 修改记录
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

/** @} */ /* end of group vector_modify */

#include "spacemath.h"


/*!
 * @brief 创建一个三维向量
 * @param x 向量的x分量
 * @param y 向量的y分量
 * @param z 向量的z分量
 * @return 返回创建的三维向量
 * @note 直接使用三个分量创建三维向量
 */
vec3_st vec3(ftype_t x, ftype_t y, ftype_t z)
{
    vec3_st result;
    result.x = x;   /* 设置x分量 */
    result.y = y;   /* 设置y分量 */
    result.z = z;   /* 设置z分量 */
    return result;
}


/*!
 * @brief 通过v[3]数组对三维向量赋值
 * @param v 输入数组
 * @return 返回创建的三维向量
 * @note 使用一维数组初始化三维向量，数组索引0-2分别对应x,y,z分量
 */
vec3_st vec3_v(ftype_t v[3])
{
    vec3_st result;
    result.x = v[0];    /* 数组索引0对应x分量 */
    result.y = v[1];    /* 数组索引1对应y分量 */
    result.z = v[2];    /* 数组索引2对应z分量 */
    return result;
}


/*!
 * @brief 创建一个零向量
 * @return 返回所有分量为0.0的三维向量
 * @note 创建一个x、y、z分量都为0的向量
 */
vec3_st vec3_zero(void)
{
    vec3_st result;
    result.x = MFLOAT_C(0.0);    /* x分量设为0 */
    result.y = MFLOAT_C(0.0);    /* y分量设为0 */
    result.z = MFLOAT_C(0.0);    /* z分量设为0 */
    return result;
}


/*!
 * @brief 创建一个单位向量（所有分量为1.0）
 * @return 返回所有分量为1.0的三维向量
 * @note 创建一个x、y、z分量都为1的向量
 */
vec3_st vec3_one(void)
{
    vec3_st result;
    result.x = MFLOAT_C(1.0);    /* x分量设为1 */
    result.y = MFLOAT_C(1.0);    /* y分量设为1 */
    result.z = MFLOAT_C(1.0);    /* z分量设为1 */
    return result;
}


/*!
 * @brief 检查三维向量是否为零向量
 * @param v 要检查的三维向量
 * @return 如果向量的所有分量都接近零则返回true，否则返回false
 * @note 使用MEPSILON作为浮点数比较的容差
 */
bool vec3_is_zero(vec3_st v)
{
    /* 检查所有分量是否都在容差范围内接近零 */
    return ((MFABS(v.x) < MEPSILON) && 
            (MFABS(v.y) < MEPSILON) && 
            (MFABS(v.z) < MEPSILON));
}


/*!
 * @brief 检查三维向量是否为零向量（指定容差）
 * @param v 要检查的三维向量
 * @param epsilon 容差
 * @return 如果向量的所有分量都接近零则返回true，否则返回false
 * @note 使用指定的容差进行浮点数比较
 */
bool vec3_is_zero_eps(vec3_st v, ftype_t epsilon)
{
    /* 检查所有分量是否都在指定容差范围内接近零 */
    return ((MFABS(v.x) < epsilon) && 
            (MFABS(v.y) < epsilon) && 
            (MFABS(v.z) < epsilon));
}


/*!
 * @brief 检查两个三维向量是否相等
 * @param v0 第一个三维向量
 * @param v1 第二个三维向量
 * @return 如果两个向量的所有分量都接近相等则返回true，否则返回false
 * @note 使用MEPSILON作为浮点数比较的容差
 */
bool vec3_is_equal(vec3_st v0, vec3_st v1)
{
    /* 检查对应分量的差值是否都在容差范围内 */
    return ((MFABS(v0.x - v1.x) < MEPSILON) && 
            (MFABS(v0.y - v1.y) < MEPSILON) && 
            (MFABS(v0.z - v1.z) < MEPSILON));
}


/*!
 * @brief 检查两个三维向量是否相等（指定容差）
 * @param v0 第一个三维向量
 * @param v1 第二个三维向量
 * @param epsilon 容差
 * @return 如果两个向量的所有分量都接近相等则返回true，否则返回false
 * @note 使用指定的容差进行浮点数比较
 */
bool vec3_is_equal_eps(vec3_st v0, vec3_st v1, ftype_t epsilon)
{
    /* 检查对应分量的差值是否都在指定容差范围内 */
    return ((MFABS(v0.x - v1.x) < epsilon) && 
            (MFABS(v0.y - v1.y) < epsilon) && 
            (MFABS(v0.z - v1.z) < epsilon));
}


/*!
 * @brief 计算向量的符号向量
 * @param v 输入的三维向量
 * @return 返回符号向量（每个分量为原分量的符号）
 * @note 对于每个分量：正数返回1.0，负数返回-1.0，零返回0.0
 */
vec3_st vec3_sign(vec3_st v)
{
    vec3_st result;
    /* 处理x分量的符号 */
    if (v.x > MFLOAT_C(0.0)) {
        result.x = MFLOAT_C(1.0);    /* 正数返回1.0 */
    } else if (v.x < MFLOAT_C(0.0)) {
        result.x = -MFLOAT_C(1.0);   /* 负数返回-1.0 */
    } else {
        result.x = MFLOAT_C(0.0);    /* 零返回0.0 */
    }
    /* 处理y分量的符号 */
    if (v.y > MFLOAT_C(0.0)) {
        result.y = MFLOAT_C(1.0);    /* 正数返回1.0 */
    } else if (v.y < MFLOAT_C(0.0)) {
        result.y = -MFLOAT_C(1.0);   /* 负数返回-1.0 */
    } else {
        result.y = MFLOAT_C(0.0);    /* 零返回0.0 */
    }
    /* 处理z分量的符号 */
    if (v.z > MFLOAT_C(0.0)) {
        result.z = MFLOAT_C(1.0);    /* 正数返回1.0 */
    } else if (v.z < MFLOAT_C(0.0)) {
        result.z = -MFLOAT_C(1.0);   /* 负数返回-1.0 */
    } else {
        result.z = MFLOAT_C(0.0);    /* 零返回0.0 */
    }
    return result;
}


/*!
 * @brief 计算向量的负向量
 * @param v 输入的三维向量
 * @return 返回负向量（所有分量取反）
 * @note 对向量的每个分量取负值
 */
vec3_st vec3_neg(vec3_st v)
{
    vec3_st result;
    result.x = -v.x;    /* x分量取反 */
    result.y = -v.y;    /* y分量取反 */
    result.z = -v.z;    /* z分量取反 */
    return result;
}


/*!
 * @brief 计算向量的绝对值向量
 * @param v 输入的三维向量
 * @return 返回绝对值向量（所有分量为原分量的绝对值）
 * @note 对向量的每个分量取绝对值
 */
vec3_st vec3_abs(vec3_st v)
{
    vec3_st result;
    result.x = MFABS(v.x);    /* x分量取绝对值 */
    result.y = MFABS(v.y);    /* y分量取绝对值 */
    result.z = MFABS(v.z);    /* z分量取绝对值 */
    return result;
}


/*!
 * @brief 计算向量的向下取整向量
 * @param v 输入的三维向量
 * @return 返回向下取整向量
 * @note 对向量的每个分量进行向下取整运算
 */
vec3_st vec3_floor(vec3_st v)
{
    vec3_st result;
    result.x = MFLOOR(v.x);    /* x分量向下取整 */
    result.y = MFLOOR(v.y);    /* y分量向下取整 */
    result.z = MFLOOR(v.z);    /* z分量向下取整 */
    return result;
}


/*!
 * @brief 计算向量的向上取整向量
 * @param v 输入的三维向量
 * @return 返回向上取整向量
 * @note 对向量的每个分量进行向上取整运算
 */
vec3_st vec3_ceil(vec3_st v)
{
    vec3_st result;
    result.x = MCEIL(v.x);    /* x分量向上取整 */
    result.y = MCEIL(v.y);    /* y分量向上取整 */
    result.z = MCEIL(v.z);    /* z分量向上取整 */
    return result;
}


/*!
 * @brief 计算向量的四舍五入向量
 * @param v 输入的三维向量
 * @return 返回四舍五入向量
 * @note 对向量的每个分量进行四舍五入运算
 */
vec3_st vec3_round(vec3_st v)
{
    vec3_st result;
    result.x = MROUND(v.x);    /* x分量四舍五入 */
    result.y = MROUND(v.y);    /* y分量四舍五入 */
    result.z = MROUND(v.z);    /* z分量四舍五入 */
    return result;
}


/*!
 * @brief 计算向量的取整向量
 * @param v 输入的三维向量
 * @return 返回取整向量
 * @note 对向量的每个分量进行取整运算
 */
vec3_st vec3_trunc(vec3_st v)
{
    vec3_st result;
    result.x = MTRUNC(v.x);    /* x分量取整 */
    result.y = MTRUNC(v.y);    /* y分量取整 */
    result.z = MTRUNC(v.z);    /* z分量取整 */
    return result;
}


/*!
 * @brief 计算向量的模长
 * @param v 输入的三维向量
 * @return 返回向量的欧几里得长度
 * @note 计算向量的模长（欧几里得距离）
 */
ftype_t vec3_len(vec3_st v)
{
    /* 计算各分量平方和的平方根 */
    return MSQRT(v.x * v.x + v.y * v.y + v.z * v.z);
}


/*!
 * @brief 计算向量模长的平方
 * @param v 输入的三维向量
 * @return 返回向量模长的平方
 * @note 避免开方运算，用于性能敏感的比较操作
 */
ftype_t vec3_len_sq(vec3_st v)
{
    /* 计算各分量的平方和 */
    return (v.x * v.x + v.y * v.y + v.z * v.z);
}


/*!
 * @brief 获取单位向量
 * @param v 输入的三维向量
 * @return 返回单位向量
 * @note 将向量除以其模长，使其成为单位向量，有除零保护
 */
vec3_st vec3_unit(vec3_st v)
{
    ftype_t l = MSQRT(v.x * v.x + v.y * v.y + v.z * v.z);    /* 计算模长 */
    vec3_st result;
    /* 检查模长是否接近零 */
    if (l < MEPSILON) {
        result = vec3_zero();    /* 模长为零，返回零向量 */
    } else {
        result.x = v.x / l;    /* x分量除以模长 */
        result.y = v.y / l;    /* y分量除以模长 */
        result.z = v.z / l;    /* z分量除以模长 */
    }
    return result;
}


/*!
 * @brief 向量加法
 * @param v0 第一个三维向量
 * @param v1 第二个三维向量
 * @return 返回两个向量的和
 * @note 执行逐分量的向量加法运算
 */
vec3_st vec3_add(vec3_st v0, vec3_st v1)
{
    vec3_st result;
    result.x = v0.x + v1.x;    /* x分量相加 */
    result.y = v0.y + v1.y;    /* y分量相加 */
    result.z = v0.z + v1.z;    /* z分量相加 */
    return result;
}


/*!
 * @brief 向量标量加法
 * @param v 输入的三维向量
 * @param f 标量加数
 * @return 返回向量与标量的和
 * @note 将向量的每个分量加上标量值
 */
vec3_st vec3_add_f(vec3_st v, ftype_t f)
{
    vec3_st result;
    result.x = v.x + f;    /* x分量加标量 */
    result.y = v.y + f;    /* y分量加标量 */
    result.z = v.z + f;    /* z分量加标量 */
    return result;
}


/*!
 * @brief 向量减法
 * @param v0 被减向量
 * @param v1 减数向量
 * @return 返回两个向量的差
 * @note 执行逐分量的向量减法运算
 */
vec3_st vec3_sub(vec3_st v0, vec3_st v1)
{
    vec3_st result;
    result.x = v0.x - v1.x;    /* x分量相减 */
    result.y = v0.y - v1.y;    /* y分量相减 */
    result.z = v0.z - v1.z;    /* z分量相减 */
    return result;
}


/*!
 * @brief 向量标量减法
 * @param v 输入的三维向量
 * @param f 标量减数
 * @return 返回向量与标量的差
 * @note 将向量的每个分量减去标量值
 */
vec3_st vec3_sub_f(vec3_st v, ftype_t f)
{
    vec3_st result;
    result.x = v.x - f;    /* x分量减标量 */
    result.y = v.y - f;    /* y分量减标量 */
    result.z = v.z - f;    /* z分量减标量 */
    return result;
}


/*!
 * @brief 向量乘法（逐分量）
 * @param v0 第一个三维向量
 * @param v1 第二个三维向量
 * @return 返回两个向量的逐分量乘积
 * @note 执行逐分量的向量乘法运算
 */
vec3_st vec3_mul(vec3_st v0, vec3_st v1)
{
    vec3_st result;
    result.x = v0.x * v1.x;    /* x分量相乘 */
    result.y = v0.y * v1.y;    /* y分量相乘 */
    result.z = v0.z * v1.z;    /* z分量相乘 */
    return result;
}


/*!
 * @brief 向量标量乘法
 * @param v 输入的三维向量
 * @param f 标量乘数
 * @return 返回向量与标量的乘积
 * @note 将向量的每个分量乘以标量值
 */
vec3_st vec3_mul_f(vec3_st v, ftype_t f)
{
    vec3_st result;
    result.x = v.x * f;    /* x分量乘以标量 */
    result.y = v.y * f;    /* y分量乘以标量 */
    result.z = v.z * f;    /* z分量乘以标量 */
    return result;
}


/*!
 * @brief 向量除法（逐分量）
 * @param v0 被除向量
 * @param v1 除数向量
 * @return 返回两个向量的逐分量商
 * @note 执行逐分量的向量除法运算，有除零保护
 */
vec3_st vec3_div(vec3_st v0, vec3_st v1)
{
    vec3_st result;
    /* 检查除数分量是否接近零，避免除零错误 */
    result.x = (MFABS(v1.x) < MEPSILON) ? MFLOAT_C(0.0) : v0.x / v1.x;    /* x分量除法 */
    result.y = (MFABS(v1.y) < MEPSILON) ? MFLOAT_C(0.0) : v0.y / v1.y;    /* y分量除法 */
    result.z = (MFABS(v1.z) < MEPSILON) ? MFLOAT_C(0.0) : v0.z / v1.z;    /* z分量除法 */
    return result;
}


/*!
 * @brief 向量标量除法
 * @param v 输入的三维向量
 * @param f 标量除数
 * @return 返回向量与标量的商
 * @note 将向量的每个分量除以标量值，有除零保护
 */
vec3_st vec3_div_f(vec3_st v, ftype_t f)
{
    vec3_st result;
    /* 检查除数是否接近零，避免除零错误 */
    if (MFABS(f) < MEPSILON) {
        result = vec3_zero();    /* 除数为零，返回零向量 */
    } else {
        result.x = v.x / f;    /* x分量除以标量 */
        result.y = v.y / f;    /* y分量除以标量 */
        result.z = v.z / f;    /* z分量除以标量 */
    }
    return result;
}


/*!
 * @brief 计算两个向量的最大值向量
 * @param v0 第一个三维向量
 * @param v1 第二个三维向量
 * @return 返回最大值向量（每个分量为两个向量对应分量的最大值）
 * @note 对两个向量的每个分量取最大值
 */
vec3_st vec3_max(vec3_st v0, vec3_st v1)
{
    vec3_st result;
    result.x = MFMAX(v0.x, v1.x);    /* x分量取最大值 */
    result.y = MFMAX(v0.y, v1.y);    /* y分量取最大值 */
    result.z = MFMAX(v0.z, v1.z);    /* z分量取最大值 */
    return result;
}


/*!
 * @brief 计算两个向量的最小值向量
 * @param v0 第一个三维向量
 * @param v1 第二个三维向量
 * @return 返回最小值向量（每个分量为两个向量对应分量的最小值）
 * @note 对两个向量的每个分量取最小值
 */
vec3_st vec3_min(vec3_st v0, vec3_st v1)
{
    vec3_st result;
    result.x = MFMIN(v0.x, v1.x);    /* x分量取最小值 */
    result.y = MFMIN(v0.y, v1.y);    /* y分量取最小值 */
    result.z = MFMIN(v0.z, v1.z);    /* z分量取最小值 */
    return result;
}


/*!
 * @brief 向量钳制运算
 * @param v 输入的三维向量
 * @param min 最小值向量
 * @param max 最大值向量
 * @return 返回钳制后的向量
 * @note 将向量的每个分量限制在最小值和最大值之间
 */
vec3_st vec3_clamp(vec3_st v, vec3_st min, vec3_st max)
{
    vec3_st result = vec3_max(v, min);    /* 确保不小于最小值 */
    result = vec3_min(result, max);       /* 确保不大于最大值 */
    return result;
}


/*!
 * @brief 向量钳制最小绝对值运算
 * @param v 输入的三维向量
 * @param min_abs 最小绝对值，必须为正
 * @return 返回钳制后的向量
 * @note 将向量的每个分量绝对值限制在最小值且不改变正负号
 */
vec3_st vec3_clamp_min_abs(vec3_st v, ftype_t min_abs)
{
    vec3_st result;
    /* 检查每个分量的绝对值，如果小于最小值则使用最小值并保持符号 */
    result.x = (MFABS(v.x) < min_abs) ? MCOPYSIGN(min_abs, v.x) : v.x;    /* x分量钳制 */
    result.y = (MFABS(v.y) < min_abs) ? MCOPYSIGN(min_abs, v.y) : v.y;    /* y分量钳制 */
    result.z = (MFABS(v.z) < min_abs) ? MCOPYSIGN(min_abs, v.z) : v.z;    /* z分量钳制 */
    return result;
}


/*!
 * @brief 向量钳制最大绝对值运算
 * @param v 输入的三维向量
 * @param max_abs 最大绝对值，必须为正
 * @return 返回钳制后的向量
 * @note 将向量的每个分量绝对值限制在最大值且不改变正负号
 */
vec3_st vec3_clamp_max_abs(vec3_st v, ftype_t max_abs)
{
    vec3_st result;
    /* 检查每个分量的绝对值，如果大于最大值则使用最大值并保持符号 */
    result.x = MFABS(v.x) > max_abs ? MCOPYSIGN(max_abs, v.x) : v.x;    /* x分量钳制 */
    result.y = MFABS(v.y) > max_abs ? MCOPYSIGN(max_abs, v.y) : v.y;    /* y分量钳制 */
    result.z = MFABS(v.z) > max_abs ? MCOPYSIGN(max_abs, v.z) : v.z;    /* z分量钳制 */
    return result;
}

/*!
 * @brief 向量钳制长度运算
 * @param v 输入的三维向量
 * @param min 最小长度
 * @param max 最大长度
 * @return 返回钳制后的向量
 * @note 将向量的长度限制在最小值和最大值之间，保持方向不变
 */
vec3_st vec3_clamp_len(vec3_st v, ftype_t min, ftype_t max)
{
    vec3_st result;
    ftype_t len = vec3_len(v);

    if ((len < MEPSILON) || (max < min)) {
        return v;    /* 长度接近零或最大值小于最小值，返回原向量 */
    }
    if (len < min) {
        len = min;
    } else if (len > max) {
        len = max;
    }
    result = vec3_mul_f(v, len / vec3_len(v));
    return result;
}


/*!
 * @brief 向量对齐到网格
 * @param v0 输入的三维向量
 * @param v1 网格大小向量
 * @return 返回对齐到网格的向量
 * @note 将向量的每个分量对齐到指定网格大小，有除零保护，按向下取整方式对齐到网格
 */
vec3_st vec3_snap(vec3_st v0, vec3_st v1)
{
    vec3_st result;
    /* 检查网格大小分量是否接近零，避免除零错误 */
    result.x = (MFABS(v1.x) < MEPSILON) ? v0.x : MFLOOR(v0.x / v1.x) * v1.x;    /* x分量对齐 */
    result.y = (MFABS(v1.y) < MEPSILON) ? v0.y : MFLOOR(v0.y / v1.y) * v1.y;    /* y分量对齐 */
    result.z = (MFABS(v1.z) < MEPSILON) ? v0.z : MFLOOR(v0.z / v1.z) * v1.z;    /* z分量对齐 */
    return result;
}


/*!
 * @brief 向量按向下取整方式对齐到网格（使用标量网格大小）
 * @param v 输入的三维向量
 * @param f 网格大小标量
 * @return 返回对齐到网格的向量
 * @note 将向量的每个分量对齐到指定网格大小，有除零保护
 */
vec3_st vec3_snap_f(vec3_st v, ftype_t f)
{
    vec3_st result;
    /* 检查网格大小是否接近零，避免除零错误 */
    if (MFABS(f) < MEPSILON) {
        result = v;    /* 网格大小为零，返回原向量 */
    } else {
        result.x = MFLOOR(v.x / f) * f;    /* x分量对齐 */
        result.y = MFLOOR(v.y / f) * f;    /* y分量对齐 */
        result.z = MFLOOR(v.z / f) * f;    /* z分量对齐 */
    }
    return result;
}


/*!
 * @brief 向量按取整方式规约到范围内
 * @param v 输入的三维向量
 * @param f 网格大小标量
 * @return 返回对齐到网格的向量
 * @note 将向量的每个分量按取整方式规约到范围内，有除零保护。一般用于将角度/弧度规约到主值
 */
vec3_st vec3_wrapping_f(vec3_st v, ftype_t f)
{
    vec3_st result;
    /* 检查网格大小是否接近零，避免除零错误 */
    if (MFABS(f) < MEPSILON) {
        result = v;    /* 网格大小为零，返回原向量 */
    } else {
        result.x = v.x - MTRUNC(v.x / f) * f;    /* x分量规约 */
        result.y = v.y - MTRUNC(v.y / f) * f;    /* y分量规约 */
        result.z = v.z - MTRUNC(v.z / f) * f;    /* z分量规约 */
    }
    return result;
}


/*!
 * @brief 计算两个向量的叉积
 * @param v0 第一个三维向量
 * @param v1 第二个三维向量
 * @return 返回两个向量的叉积向量
 * @note 叉积结果是一个垂直于两个输入向量的新向量。叉积不支持交换律 v0xv1 = -v1xv0
 */
vec3_st vec3_cross(vec3_st v0, vec3_st v1)
{
    vec3_st result;
    result.x = v0.y * v1.z - v0.z * v1.y;    /* 计算x分量 */
    result.y = v0.z * v1.x - v0.x * v1.z;    /* 计算y分量 */
    result.z = v0.x * v1.y - v0.y * v1.x;    /* 计算z分量 */
    return result;
}


/*!
 * @brief 计算两个向量的点积
 * @param v0 第一个三维向量
 * @param v1 第二个三维向量
 * @return 返回两个向量的点积（标量值）
 * @note 点积结果表示两个向量的相似程度和夹角信息
 */
ftype_t vec3_dot(vec3_st v0, vec3_st v1)
{
    /* 计算对应分量的乘积之和 */
    return (v0.x * v1.x + v0.y * v1.y + v0.z * v1.z);
}


/*!
 * @brief 计算两个向量的夹角（弧度）
 * @param v0 第一个三维向量
 * @param v1 第二个三维向量
 * @return 返回两个向量的夹角（弧度）
 * @note 使用反余弦函数计算夹角
 */
ftype_t vec3_angle(vec3_st v0, vec3_st v1)
{
    ftype_t dot = vec3_dot(v0, v1);        /* 计算点积 */
    ftype_t len0 = vec3_len(v0);           /* 计算第一个向量的模长 */
    ftype_t len1 = vec3_len(v1);           /* 计算第二个向量的模长 */
    /* 检查模长是否接近零，避免除零错误 */
    if (len0 < MEPSILON || len1 < MEPSILON) {
        return MFLOAT_C(0.0);    /* 模长为零，返回0角度 */
    }
    ftype_t cos_angle = dot / (len0 * len1);    /* 计算余弦值 */
    return MACOS(cos_angle);                     /* 计算反余弦得到夹角 */
}


/*!
 * @brief 计算向量在另一个向量上的投影
 * @param v 要投影的向量
 * @param onto 目标向量
 * @return 返回v在onto上的投影向量
 * @note 投影结果表示v在onto方向上的分量，有除零保护
 */
vec3_st vec3_project(vec3_st v, vec3_st onto)
{
    ftype_t d = vec3_dot(onto, onto);    /* 计算目标向量的模长平方 */
    vec3_st result;
    /* 检查模长平方是否接近零，避免除零错误 */
    if (MFABS(d) < MEPSILON) {
        result = vec3_zero();    /* 目标向量为零，返回零向量 */
    } else {
        ftype_t s = vec3_dot(v, onto) / d;    /* 计算投影比例 */
        result.x = onto.x * s;                /* 计算x分量投影 */
        result.y = onto.y * s;                /* 计算y分量投影 */
        result.z = onto.z * s;                /* 计算z分量投影 */
    }
    return result;
}


/*!
 * @brief 计算向量在平面上的滑动分量
 * @param v 输入向量
 * @param normal 平面法向量
 * @return 返回向量在平面上的滑动分量
 * @note 移除向量在法线方向上的分量，保留平面上的分量
 */
vec3_st vec3_slide(vec3_st v, vec3_st normal)
{
    ftype_t d = vec3_dot(v, normal);    /* 计算向量在法线方向上的投影长度 */
    vec3_st result;
    result.x = v.x - normal.x * d;    /* 移除x分量在法线方向上的分量 */
    result.y = v.y - normal.y * d;    /* 移除y分量在法线方向上的分量 */
    result.z = v.z - normal.z * d;    /* 移除z分量在法线方向上的分量 */
    return result;
}


/*!
 * @brief 计算向量的反射向量
 * @param v 入射向量
 * @param normal 反射面法向量
 * @return 返回反射向量
 * @note 根据入射角和法线计算反射方向
 */
vec3_st vec3_reflect(vec3_st v, vec3_st normal)
{
    ftype_t d = MFLOAT_C(2.0) * vec3_dot(v, normal);    /* 计算两倍的点积 */
    vec3_st result;
    result.x = v.x - normal.x * d;    /* 计算x分量反射 */
    result.y = v.y - normal.y * d;    /* 计算y分量反射 */
    result.z = v.z - normal.z * d;    /* 计算z分量反射 */
    return result;
}


/*!
 * @brief 绕任意轴旋转向量
 * @param v 要旋转的向量
 * @param axis 旋转轴向量
 * @param angle 旋转角度（弧度）
 * @return 返回旋转后的向量
 * @note 使用罗德里格斯旋转公式进行向量旋转
 */
vec3_st vec3_rotate(vec3_st v, vec3_st axis, ftype_t angle)
{
    ftype_t cos_angle = MCOS(angle);                /* 计算旋转角度的余弦值 */
    ftype_t sin_angle = MSIN(angle);                /* 计算旋转角度的正弦值 */
    vec3_st normalized_axis = vec3_unit(axis);      /* 归一化旋转轴向量 */
    
    /* 使用罗德里格斯旋转公式：v_rot = v * cosθ + (k × v) * sinθ + k * (k·v) * (1 - cosθ) */
    vec3_st cross = vec3_cross(normalized_axis, v); /* 计算叉积 k × v */
    ftype_t dot = vec3_dot(normalized_axis, v);     /* 计算点积 k·v */
    
    vec3_st result;
    result.x = v.x * cos_angle + cross.x * sin_angle + normalized_axis.x * dot * (1 - cos_angle);
    result.y = v.y * cos_angle + cross.y * sin_angle + normalized_axis.y * dot * (1 - cos_angle);
    result.z = v.z * cos_angle + cross.z * sin_angle + normalized_axis.z * dot * (1 - cos_angle);
    return result;
}


/*!
 * @brief 向量线性插值
 * @param from 起始向量
 * @param to 结束向量
 * @param t 插值因子（0.0到1.0之间）
 * @return 返回插值后的向量
 * @note 对两个向量的每个分量进行线性插值
 */
vec3_st vec3_lerp(vec3_st from, vec3_st to, ftype_t t)
{
    vec3_st result;
    result.x = from.x + (to.x - from.x) * t;    /* x分量线性插值 */
    result.y = from.y + (to.y - from.y) * t;    /* y分量线性插值 */
    result.z = from.z + (to.z - from.z) * t;    /* z分量线性插值 */
    return result;
}


/*!
 * @brief 三次贝塞尔曲线插值
 * @param v0 起始点向量
 * @param v1 第一个控制点向量
 * @param v2 结束点向量
 * @param f 插值因子（0.0到1.0之间）
 * @return 返回贝塞尔曲线上的插值点向量
 * @note 计算三次贝塞尔曲线上的点
 */
vec3_st vec3_bezier3(vec3_st v0, vec3_st v1, vec3_st v2, ftype_t f)
{
    vec3_st tmp0 = vec3_lerp(v0, v1, f);    /* 第一次线性插值 */
    vec3_st tmp1 = vec3_lerp(v1, v2, f);    /* 第二次线性插值 */
    return vec3_lerp(tmp0, tmp1, f);        /* 第三次线性插值得到贝塞尔点 */
}


/*!
 * @brief 四次贝塞尔曲线插值
 * @param v0 起始点向量
 * @param v1 第一个控制点向量
 * @param v2 第二个控制点向量
 * @param v3 结束点向量
 * @param f 插值因子（0.0到1.0之间）
 * @return 返回贝塞尔曲线上的插值点向量
 * @note 计算四次贝塞尔曲线上的点
 */
vec3_st vec3_bezier4(vec3_st v0, vec3_st v1, vec3_st v2, vec3_st v3, ftype_t f)
{
    vec3_st tmp0 = vec3_lerp(v0, v1, f);    /* 第一次线性插值 */
    vec3_st tmp1 = vec3_lerp(v1, v2, f);    /* 第二次线性插值 */
    vec3_st tmp2 = vec3_lerp(v2, v3, f);    /* 第三次线性插值 */
    vec3_st tmp3 = vec3_lerp(tmp0, tmp1, f);    /* 第四次线性插值 */
    vec3_st tmp4 = vec3_lerp(tmp1, tmp2, f);    /* 第五次线性插值 */
    return vec3_lerp(tmp3, tmp4, f);            /* 第六次线性插值得到贝塞尔点 */
}


/*!
 * @brief 计算两个向量之间的距离
 * @param v0 第一个三维向量
 * @param v1 第二个三维向量
 * @return 返回两个向量之间的欧几里得距离
 * @note 计算两点之间的直线距离
 */
ftype_t vec3_dist(vec3_st v0, vec3_st v1)
{
    /* 计算各分量差值的平方和的平方根 */
    return MSQRT((v0.x - v1.x) * (v0.x - v1.x) + 
                 (v0.y - v1.y) * (v0.y - v1.y) + 
                 (v0.z - v1.z) * (v0.z - v1.z));
}


/*!
 * @brief 计算两个向量之间距离的平方
 * @param v0 第一个三维向量
 * @param v1 第二个三维向量
 * @return 返回两个向量之间距离的平方
 * @note 避免开方运算，用于性能敏感的距离比较
 */
ftype_t vec3_dist_sq(vec3_st v0, vec3_st v1)
{
    /* 计算各分量差值的平方和 */
    return (v0.x - v1.x) * (v0.x - v1.x) + 
           (v0.y - v1.y) * (v0.y - v1.y) + 
           (v0.z - v1.z) * (v0.z - v1.z);
}


/*!
 * @brief 检查三个向量是否线性无关
 * @param v0 第一个三维向量
 * @param v1 第二个三维向量
 * @param v2 第三个三维向量
 * @return 如果三个向量线性无关则返回true，否则返回false
 * @note 通过计算混合积（标量三重积）来判断线性无关性
 */
bool vec3_is_linear_independent(vec3_st v0, vec3_st v1, vec3_st v2)
{
    /* 计算混合积（标量三重积） */
    return (v0.x * v1.y * v2.z + v0.y * v1.z * v2.x + v0.z * v1.x * v2.y
        - v0.z * v1.y * v2.x - v0.y * v1.x * v2.z - v0.x * v1.z * v2.y);
}

/**********************************************************************************************************************
 * End of spacemath file
 *********************************************************************************************************************/
