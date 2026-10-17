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
 * @file axis.c
 * @brief 空间数学库轴角实现文件
 * @author scilogyhunter
 * @date 2025.09.01
 * @version V0.1.2
 *
 * 本文件实现了空间数学库轴角相关函数，包括轴角操作等。
 */

/*!
 * @defgroup axis_modify 修改记录
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

/** @} */ /* end of group axis_modify */

#include "spacemath.h"


/*!
 * @brief 创建轴角结构体
 * @param x 旋转轴的X分量
 * @param y 旋转轴的Y分量
 * @param z 旋转轴的Z分量
 * @param angle 旋转角度（弧度）
 * @return 返回创建的轴角结构体
 * @note 使用旋转轴分量和角度创建轴角表示
 */
axis_st  axis(ftype_t x, ftype_t y, ftype_t z, ftype_t angle) 
{
    axis_st axis = {
        .v3.x = x,                   /* 设置旋转轴X分量 */
        .v3.y = y,                   /* 设置旋转轴Y分量 */
        .v3.z = z,                   /* 设置旋转轴Z分量 */
        .angle = angle};             /* 设置旋转角度 */
    axis.v3 = vec3_unit(axis.v3);               /* 归一化旋转轴 */
    return axis;                     /* 返回创建的轴角 */
}

/*!
 * @brief 通过数组创建轴角结构体
 * @param v[4] 包含四个分量的数组
 * @return 返回创建的轴角结构体
 * @note 使用数组中的四个元素分别作为x、y、z分量和角度
 */
axis_st  axis_v(ftype_t v[4])
{
    axis_st axis = {
        .v3.x = v[0],                /* 设置旋转轴X分量 */
        .v3.y = v[1],                /* 设置旋转轴Y分量 */
        .v3.z = v[2],                /* 设置旋转轴Z分量 */
        .angle = v[3]};              /* 设置旋转角度 */
    axis.v3 = vec3_unit(axis.v3);    /* 归一化旋转轴 */
    return axis;                     /* 返回创建的轴角 */
}


/*!
 * @brief 由旋转轴向量和角度创建轴角结构体
 * @param v3 旋转轴向量
 * @param a 旋转角度（弧度）
 * @return 返回创建的轴角结构体
 * @note 使用旋转轴向量和角度创建轴角表示
 */
axis_st  axis_from_vector_angle(vec3_st v3, ftype_t a) 
{
    axis_st axis = {.v3 = v3, .angle = a};    /* 使用向量和角度初始化轴角 */
    axis.v3 = vec3_unit(axis.v3);               /* 归一化旋转轴 */
    return axis;                     /* 返回创建的轴角 */
}


/*!
 * @brief 创建零轴角
 * @return 返回零旋转的轴角
 * @note 创建一个表示无旋转的轴角
 */
axis_st  axis_zero(void)
{
    axis_st axis = {.v3 = vec3_zero(), .angle = MFLOAT_C(0.0)};    /* 零旋转轴和零角度 */
    return axis;                     /* 返回零轴角 */
}   


/*!
 * @brief 判断轴角是否为零轴角
 * @param axis 要检查的轴角
 * @return 如果角度接近零或旋转轴为零向量则返回true，否则返回false
 * @note 使用MEPSILON作为浮点数比较的容差
 */
bool axis_is_zero(axis_st axis)
{
    if (MFABS(axis.angle) < MEPSILON) {
        return true;                 /* 角度接近零 */
    }

    if (vec3_is_zero(axis.v3)) {
        return true;                 /* 旋转轴为零向量 */
    }

    return false;                    /* 非零轴角 */
}
/*!
 * @brief 判断两个轴角是否相等
 * @param a 第一个轴角
 * @param b 第二个轴角
 * @return 如果两个轴角相等则返回true，否则返回false
 * @note 使用MEPSILON作为浮点数比较的容差
 */
bool axis_is_equal(axis_st a, axis_st b)
{
    if ((a.angle * b.angle) < MFLOAT_C(0.0)) {
        b.v3.x = -b.v3.x;
        b.v3.y = -b.v3.y;
        b.v3.z = -b.v3.z;
        b.angle = -b.angle;
    }
    return (MFABS(a.v3.x - b.v3.x) < MEPSILON) &&
           (MFABS(a.v3.y - b.v3.y) < MEPSILON) &&
           (MFABS(a.v3.z - b.v3.z) < MEPSILON) &&
           (MFABS(a.angle - b.angle) < MEPSILON);
}

/*!
 * @brief 判断两个轴角是否相等
 * @param a 第一个轴角
 * @param b 第二个轴角
 * @param epsilon 浮点数比较的容差
 * @return 如果两个轴角相等则返回true，否则返回false
 * @note 使用指定的容差epsilon进行浮点数比较
 */
bool axis_is_equal_eps(axis_st a, axis_st b, ftype_t epsilon)
{
    if ((a.angle * b.angle) < MFLOAT_C(0.0)) {
        b.v3.x = -b.v3.x;
        b.v3.y = -b.v3.y;
        b.v3.z = -b.v3.z;
        b.angle = -b.angle;
    }
    return (MFABS(a.v3.x - b.v3.x) < epsilon) &&
           (MFABS(a.v3.y - b.v3.y) < epsilon) &&
           (MFABS(a.v3.z - b.v3.z) < epsilon) &&
           (MFABS(a.angle - b.angle) < epsilon);
}
/*!
 * @brief 由两个向量计算旋转轴角
 * @param from 起始向量
 * @param to 目标向量
 * @return 返回将from旋转到to所需的轴角
 * @note 计算将向量from旋转到向量to所需的旋转轴和角度
 */
axis_st axis_from_vv(vec3_st from, vec3_st to)
{
    axis_st a;                       /* 存储轴角结果 */
    vec3_st cross;                   /* 存储叉积结果 */

    /* 检查输入向量是否为零向量 */
    if (vec3_is_zero(from) || vec3_is_zero(to)) {
        return  axis_zero();         /* 输入向量为零，返回零轴角 */
    }
    
    /* 归一化输入向量 */
    vec3_st from_unit = vec3_unit(from);    /* 归一化起始向量 */
    vec3_st to_unit = vec3_unit(to);        /* 归一化目标向量 */
    
    /* 计算点积和叉积 */
    ftype_t d = vec3_dot(from_unit, to_unit);    /* 计算点积 */
    cross = vec3_cross(from_unit, to_unit);      /* 计算叉积 */
    
    ftype_t epsilon = MFLOAT_C(1.0e-6);  /* 定义一个小的容差值 */
    /* 处理特殊情况：向量相同或相反 */
    if (d > (MFLOAT_C(1.0) - epsilon)) {
        /* 向量几乎相同，返回零旋转 */
        return  axis_zero();         /* 无旋转 */
    }
    
    if (d < (-MFLOAT_C(1.0) + epsilon)) {
        /* 向量几乎相反，需要选择任意垂直轴旋转180度 */
        /* 找一个与from不共线的向量作为参考向量 */
        vec3_st reference;           /* 参考向量 */
        if (MFABS(from_unit.x) < MFLOAT_C(0.9)) {
            reference = vec3(MFLOAT_C(1.0), MFLOAT_C(0.0), MFLOAT_C(0.0));    /* 选择X轴作为参考 */
        }
        else if (MFABS(from_unit.y) < MFLOAT_C(0.9)) {
            reference = vec3(MFLOAT_C(0.0), MFLOAT_C(1.0), MFLOAT_C(0.0));    /* 选择Y轴作为参考 */
        }
        else {
            reference = vec3(MFLOAT_C(0.0), MFLOAT_C(0.0), MFLOAT_C(1.0));    /* 选择Z轴作为参考 */
        }
        
        /* 计算旋转轴（垂直于from） */
        a.v3 = vec3_unit(vec3_cross(from_unit, reference));    /* 计算旋转轴 */
        a.angle = MPI;              /* 180度旋转 */
        return a;                    /* 返回轴角 */
    }
    
    /* 计算旋转角度 */
    a.angle = safe_acos(d);              /* 从点积计算旋转角度 */
    a.v3 = vec3_unit(cross);        /* 归一化旋转轴 */

    return a;                       /* 返回轴角 */
}

/**********************************************************************************************************************
 * End of spacemath file
 *********************************************************************************************************************/


