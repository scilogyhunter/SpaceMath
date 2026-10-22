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
 * @file eula.c
 * @brief 空间数学库欧拉角实现文件
 * @author scilogyhunter
 * @date 2026.10.22
 * @version V0.1.3
 *
 * 本文件实现了空间数学库欧拉角相关函数，包括欧拉角的验证、转换、加减、规范化等。
 */

/*!
 * @defgroup eula_modify 修改记录
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

/** @} */ /* end of group eula_modify */

#include "spacemath.h"

/*!
 * @brief 验证旋转顺序字符串是否有效
 * @param e 欧拉角结构体
 * @param order 旋转顺序字符串（如"xyz"、"zyx"等）
 * @return 如果旋转顺序有效则返回true，否则返回false
 * @note 检查旋转顺序字符串的格式和欧拉角的角度范围
 */
bool eula_validate(eula_st e, char  *order) 
{
    if (order == NULL) {
        return false;                    /* 空指针无效 */
    }

    /* 长度必选为3个字符，且只能是小写的xyz字母 */
    if ((3 != strlen(order)) ||
        (order[0] != 'x' && order[0] != 'y' && order[0] != 'z') ||
        (order[1] != 'x' && order[1] != 'y' && order[1] != 'z') ||
        (order[2] != 'x' && order[2] != 'y' && order[2] != 'z')) {
        return false;                /* 旋转顺序无效 */
    }

    /* 必须是经典欧拉角（三个不同轴） */
    if ((order[0] == order[1]) || (order[1] == order[2]) || (order[2] == order[0])) {
        return false;
    }

    /* 检查三个角度范围，第1,3旋转角范围[-PI, PI]，第2旋转角范围[-PI/2, PI/2] */
    ftype_t  eula[3];                /* 存储按顺序排列的欧拉角 */

    /* 根据旋转顺序提取对应的角度值 */
    eula[0] = e.v[order[0] - 'x'];   /* 第一个旋转轴的角度 */
    eula[1] = e.v[order[1] - 'x'];   /* 第二个旋转轴的角度 */
    eula[2] = e.v[order[2] - 'x'];   /* 第三个旋转轴的角度 */

    /* 检查角度范围是否在有效范围内 */
    if (MFABS(eula[0]) > MPI || MFABS(eula[2]) > MPI || MFABS(eula[1]) > MPI_2) {
        return false;                /* 角度超出有效范围 */
    }

    return true;                     /* 旋转顺序和角度范围都有效 */
}


/*!
 * @brief 创建欧拉角结构体
 * @param x 绕X轴的旋转角度（弧度）
 * @param y 绕Y轴的旋转角度（弧度）
 * @param z 绕Z轴的旋转角度（弧度）
 * @return 返回创建的欧拉角结构体
 * @note 使用三个角度分量创建欧拉角表示
 */
eula_st  eula(ftype_t x, ftype_t y, ftype_t z) 
{
    eula_st e = {.x = x, .y = y, .z = z};    /* 初始化欧拉角结构体 */

    return e;                         /* 返回创建的欧拉角 */
}


/*!
 * @brief 通过数组创建欧拉角结构体
 * @param v[3] 包含三个角度分量的数组
 * @return 返回创建的欧拉角结构体
 * @note 使用数组中的三个元素分别作为x、y、z分量
 */
eula_st eula_v(ftype_t v[3]) 
{
    if (v == NULL) {
        return eula_zero();
    }
    eula_st e = {.x = v[0], .y = v[1], .z = v[2]};    /* 使用数组初始化欧拉角 */

    return e;                         /* 返回创建的欧拉角 */
}


/*!
 * @brief 创建零欧拉角
 * @return 返回所有分量为0.0的欧拉角
 * @note 创建一个表示无旋转的欧拉角
 */
eula_st eula_zero(void)
{
    eula_st e = {.x = 0.0, .y = 0.0, .z = 0.0};    /* 初始化所有分量为0 */

    return e;                         /* 返回零欧拉角 */
}


/*!
 * @brief 检查欧拉角是否为零欧拉角
 * @param e 要检查的欧拉角
 * @return 如果所有角度分量都接近零则返回true，否则返回false
 * @note 使用MEPSILON作为浮点数比较的容差
 */
bool eula_is_zero(eula_st e)
{
    return ((MFABS(e.x) < MEPSILON) && (MFABS(e.y) < MEPSILON) && (MFABS(e.z) < MEPSILON));
}
/*!
 * @brief 检查欧拉角是否相等
 * @param a 第一个欧拉角
 * @param b 第二个欧拉角
 * @return 如果所有角度分量都接近零则返回true，否则返回false
 * @note 使用MEPSILON作为浮点数比较的容差
 */
bool eula_is_equal(eula_st a, eula_st b)
{
    return (MFABS(a.x - b.x) < MEPSILON) &&
           (MFABS(a.y - b.y) < MEPSILON) &&
           (MFABS(a.z - b.z) < MEPSILON);
}
/*!
 * @brief 检查欧拉角是否相等（带容差）
 * @param a 第一个欧拉角
 * @param b 第二个欧拉角
 * @param epsilon 容差值
 * @return 如果所有角度分量都接近零则返回true，否则返回false
 * @note 使用指定的容差值进行比较
 */
bool eula_is_equal_eps(eula_st a, eula_st b, ftype_t epsilon)
{
    return (MFABS(a.x - b.x) < epsilon) &&
           (MFABS(a.y - b.y) < epsilon) &&
           (MFABS(a.z - b.z) < epsilon);
}


/*!
 * @brief 欧拉角相加
 * @param e0 第一个欧拉角
 * @param e1 第二个欧拉角
 * @return 返回相加后的欧拉角
 * @note 分别对x、y、z分量进行相加操作
 */
eula_st  eula_add(eula_st e0, eula_st e1) 
{
    eula_st result;
    result.x = e0.x + e1.x;
    result.y = e0.y + e1.y;
    result.z = e0.z + e1.z;
    return result;
}
/*!
 * @brief 欧拉角相减
 * @param e0 被减欧拉角
 * @param e1 减欧拉角
 * @return 返回相减后的欧拉角
 * @note 分别对x、y、z分量进行相减操作
 */
eula_st  eula_sub(eula_st e0, eula_st e1) 
{
    eula_st result;
    result.x = e0.x - e1.x;
    result.y = e0.y - e1.y;
    result.z = e0.z - e1.z;
    return result;
} 

/*!
 * @brief 将欧拉角从角度转换为弧度
 * @param deg 角度表示的欧拉角
 * @return 返回弧度表示的欧拉角
 * @note 将三个角度分量从度转换为弧度
 */
eula_st  eula_deg2rad(eula_st deg) 
{
    deg.x = MDEG2RAD * (deg.x);         /* 转换X分量 */
    deg.y = MDEG2RAD * (deg.y);         /* 转换Y分量 */
    deg.z = MDEG2RAD * (deg.z);         /* 转换Z分量 */
    return deg;                      /* 返回转换后的欧拉角 */
}


/*!
 * @brief 将欧拉角从弧度转换为角度
 * @param rad 弧度表示的欧拉角
 * @return 返回角度表示的欧拉角
 * @note 将三个角度分量从弧度转换为度
 */
eula_st  eula_rad2deg(eula_st rad) 
{
    rad.x = MRAD2DEG * (rad.x);         /* 转换X分量 */
    rad.y = MRAD2DEG * (rad.y);         /* 转换Y分量 */
    rad.z = MRAD2DEG * (rad.z);         /* 转换Z分量 */
    return rad;                      /* 返回转换后的欧拉角 */
}


/*!
 * @brief 欧拉角范围规范化到[-range, range]
 * @param e 输入的欧拉角
 * @param range 规范化范围
 * @return 返回规范化后的欧拉角
 * @note 使用remainder函数将角度规范到指定范围内
 */
eula_st  eula_remainder(eula_st e, ftype_t  range) 
{
    eula_st  n;                      /* 存储规范化后的欧拉角 */
    n.x = MREMAINDER(e.x, 2 * range);    /* 规范化X分量 */
    n.y = MREMAINDER(e.y, 2 * range);    /* 规范化Y分量 */
    n.z = MREMAINDER(e.z, 2 * range);    /* 规范化Z分量 */

    return n;                        /* 返回规范化后的欧拉角 */
}


/**********************************************************************************************************************
 * End of spacemath file
 *********************************************************************************************************************/
