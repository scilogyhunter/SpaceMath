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
 * @file matrix.c
 * @brief 矩阵运算实现文件
 * @author scilogyhunter
 * @date 2026.10.22
 * @version V0.1.3
 *
 * 本文件实现了3x3矩阵的基本运算，包括创建、转置、求逆、乘法、插值等操作。
 * 矩阵运算在计算机图形学、物理模拟和数值计算中具有广泛应用。
 */

/*!
 * @defgroup matrix_modify 修改记录
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

/** @} */ /* end of group matrix_modify */

#include "spacemath.h"


/*!
 * @brief 创建一个3x3矩阵
 * @param m11 矩阵第一行第一列元素
 * @param m12 矩阵第一行第二列元素
 * @param m13 矩阵第一行第三列元素
 * @param m21 矩阵第二行第一列元素
 * @param m22 矩阵第二行第二列元素
 * @param m23 矩阵第二行第三列元素
 * @param m31 矩阵第三行第一列元素
 * @param m32 矩阵第三行第二列元素
 * @param m33 矩阵第三行第三列元素
 * @return 返回创建的3x3矩阵
 * @note 直接使用九个分量创建3x3矩阵
 */
mat3_st mat3(ftype_t m11, ftype_t m12, ftype_t m13, ftype_t m21, ftype_t m22, ftype_t m23, ftype_t m31, ftype_t m32, ftype_t m33)
{
    mat3_st result;
    result.m11 = m11;   /* 设置第一行第一列元素 */
    result.m12 = m12;   /* 设置第一行第二列元素 */
    result.m13 = m13;   /* 设置第一行第三列元素 */
    result.m21 = m21;   /* 设置第二行第一列元素 */
    result.m22 = m22;   /* 设置第二行第二列元素 */
    result.m23 = m23;   /* 设置第二行第三列元素 */
    result.m31 = m31;   /* 设置第三行第一列元素 */
    result.m32 = m32;   /* 设置第三行第二列元素 */
    result.m33 = m33;   /* 设置第三行第三列元素 */
    return result;
}


/*!
 * @brief 通过v[9]数组对3x3矩阵赋值
 * @param v 输入数组，列优先存储，与 mat3_st 的 v[9] 视图一致
 * @return 返回创建的3x3矩阵
 * @note 使用一维数组初始化3x3矩阵，数组按列优先存储：
 *       v[0..2] 为第1列，v[3..5] 为第2列，v[6..8] 为第3列。
 *       因此 mat3_v(m.v) == m 恒成立，与 mat3_vv / mat3_v3 自洽。
 */
mat3_st mat3_v(ftype_t v[9])
{
    if (v == NULL) {
        return mat3_zero();
    }
    mat3_st result;
    result.m11 = v[0];    /* v[0]→m11（第1列第1行） */
    result.m21 = v[1];    /* v[1]→m21（第1列第2行） */
    result.m31 = v[2];    /* v[2]→m31（第1列第3行） */
    result.m12 = v[3];    /* v[3]→m12（第2列第1行） */
    result.m22 = v[4];    /* v[4]→m22（第2列第2行） */
    result.m32 = v[5];    /* v[5]→m32（第2列第3行） */
    result.m13 = v[6];    /* v[6]→m13（第3列第1行） */
    result.m23 = v[7];    /* v[7]→m23（第3列第2行） */
    result.m33 = v[8];    /* v[8]→m33（第3列第3行） */
    return result;
}


/*!
 * @brief 通过vv[3][3]二维数组对3x3矩阵赋值
 * @param vv 输入数组，注意需要是列优先存储，如果是行优先存储需要再进行一次转置
 * @return 返回创建的3x3矩阵
 * @note 使用二维数组初始化3x3矩阵，注意存储顺序
 */
mat3_st mat3_vv(ftype_t vv[3][3])
{
    if (vv == NULL) {
        return mat3_zero();
    }
    mat3_st result;
    result.m11 = vv[0][0];    /* 第一行第一列元素 */
    result.m12 = vv[1][0];    /* 第一行第二列元素 */
    result.m13 = vv[2][0];    /* 第一行第三列元素 */
    result.m21 = vv[0][1];    /* 第二行第一列元素 */
    result.m22 = vv[1][1];    /* 第二行第二列元素 */
    result.m23 = vv[2][1];    /* 第二行第三列元素 */
    result.m31 = vv[0][2];    /* 第三行第一列元素 */
    result.m32 = vv[1][2];    /* 第三行第二列元素 */
    result.m33 = vv[2][2];    /* 第三行第三列元素 */

    return result;
}

/*!
 * @brief 通过3个向量初始化3x3矩阵
 * @param v3 输入向量数组
 * @return 返回创建的3x3矩阵
 * @note 使用3个向量初始化3x3矩阵，向量顺序为列优先
 * */
mat3_st mat3_v3(vec3_st v3[3])
{
    if (v3 == NULL) {
        return mat3_zero();
    }
    mat3_st result;
    result.v3[0] = v3[0];
    result.v3[1] = v3[1];
    result.v3[2] = v3[2];

    return result;
}


/*!
 * @brief 创建一个全零的3x3矩阵
 * @return 返回全零的3x3矩阵
 * @note 所有矩阵元素都被设置为0.0
 */
mat3_st mat3_zero(void)
{
    mat3_st result;
    result.m11 = MFLOAT_C(0.0);    /* 第一行第一列设为0 */
    result.m12 = MFLOAT_C(0.0);    /* 第一行第二列设为0 */
    result.m13 = MFLOAT_C(0.0);    /* 第一行第三列设为0 */
    result.m21 = MFLOAT_C(0.0);    /* 第二行第一列设为0 */
    result.m22 = MFLOAT_C(0.0);    /* 第二行第二列设为0 */
    result.m23 = MFLOAT_C(0.0);    /* 第二行第三列设为0 */
    result.m31 = MFLOAT_C(0.0);    /* 第三行第一列设为0 */
    result.m32 = MFLOAT_C(0.0);    /* 第三行第二列设为0 */
    result.m33 = MFLOAT_C(0.0);    /* 第三行第三列设为0 */
    return result;
}


/*!
 * @brief 创建一个所有元素为1.0的3x3矩阵
 * @return 返回所有元素为1.0的3x3矩阵
 * @note 所有矩阵元素都被设置为1.0
 */
mat3_st mat3_one(void)
{
    mat3_st result;
    result.m11 = MFLOAT_C(1.0);    /* 第一行第一列设为1 */
    result.m12 = MFLOAT_C(1.0);    /* 第一行第二列设为1 */
    result.m13 = MFLOAT_C(1.0);    /* 第一行第三列设为1 */
    result.m21 = MFLOAT_C(1.0);    /* 第二行第一列设为1 */
    result.m22 = MFLOAT_C(1.0);    /* 第二行第二列设为1 */
    result.m23 = MFLOAT_C(1.0);    /* 第二行第三列设为1 */
    result.m31 = MFLOAT_C(1.0);    /* 第三行第一列设为1 */
    result.m32 = MFLOAT_C(1.0);    /* 第三行第二列设为1 */
    result.m33 = MFLOAT_C(1.0);    /* 第三行第三列设为1 */
    return result;
}


/*!
 * @brief 创建一个单位矩阵（3x3）
 * @return 返回3x3单位矩阵
 * @note 主对角线元素为1.0，其他元素为0.0
 */
mat3_st mat3_identity(void)
{
    mat3_st result;
    result.m11 = MFLOAT_C(1.0);    /* 主对角线第一元素设为1 */
    result.m12 = MFLOAT_C(0.0);    /* 第一行第二列设为0 */
    result.m13 = MFLOAT_C(0.0);    /* 第一行第三列设为0 */
    result.m21 = MFLOAT_C(0.0);    /* 第二行第一列设为0 */
    result.m22 = MFLOAT_C(1.0);    /* 主对角线第二元素设为1 */
    result.m23 = MFLOAT_C(0.0);    /* 第二行第三列设为0 */
    result.m31 = MFLOAT_C(0.0);    /* 第三行第一列设为0 */
    result.m32 = MFLOAT_C(0.0);    /* 第三行第二列设为0 */
    result.m33 = MFLOAT_C(1.0);    /* 主对角线第三元素设为1 */
    return result;
}


/*!
 * @brief 检查矩阵是否为零矩阵
 * @param m 输入的3x3矩阵
 * @return 如果所有元素都为零返回true，否则返回false
 * @note 使用MEPSILON作为浮点数比较的容差
 */
bool mat3_is_zero(mat3_st m)
{
    /* 检查所有元素是否都在容差范围内接近零 */
    return (MFABS(m.m11) < MEPSILON) &&
           (MFABS(m.m12) < MEPSILON) &&
           (MFABS(m.m13) < MEPSILON) &&
           (MFABS(m.m21) < MEPSILON) &&
           (MFABS(m.m22) < MEPSILON) &&
           (MFABS(m.m23) < MEPSILON) &&
           (MFABS(m.m31) < MEPSILON) &&
           (MFABS(m.m32) < MEPSILON) &&
           (MFABS(m.m33) < MEPSILON);
}


/*!
 * @brief 检查矩阵是否为全1矩阵（所有元素为1.0）
 * @param m 输入的3x3矩阵
 * @return 如果所有元素都为1.0返回true，否则返回false
 * @note 使用MEPSILON作为浮点数比较的容差
 */
bool mat3_is_one(mat3_st m)
{
    /* 检查所有元素是否都在容差范围内接近1.0 */
    return (MFABS(m.m11 - MFLOAT_C(1.0)) < MEPSILON) &&
           (MFABS(m.m12 - MFLOAT_C(1.0)) < MEPSILON) &&
           (MFABS(m.m13 - MFLOAT_C(1.0)) < MEPSILON) &&
           (MFABS(m.m21 - MFLOAT_C(1.0)) < MEPSILON) &&
           (MFABS(m.m22 - MFLOAT_C(1.0)) < MEPSILON) &&
           (MFABS(m.m23 - MFLOAT_C(1.0)) < MEPSILON) &&
           (MFABS(m.m31 - MFLOAT_C(1.0)) < MEPSILON) &&
           (MFABS(m.m32 - MFLOAT_C(1.0)) < MEPSILON) &&
           (MFABS(m.m33 - MFLOAT_C(1.0)) < MEPSILON);
}


/*!
 * @brief 检查矩阵是否为单位矩阵
 * @param m 输入的3x3矩阵
 * @return 如果矩阵是单位矩阵返回true，否则返回false
 * @note 检查主对角线元素是否为1.0，非对角线元素是否为0.0
 */
bool mat3_is_identity(mat3_st m)
{
    /* 检查主对角线元素是否为1.0，非对角线元素是否为0.0 */
    return (MFABS(m.m11 - MFLOAT_C(1.0)) < MEPSILON) &&
           (MFABS(m.m12 - MFLOAT_C(0.0)) < MEPSILON) &&
           (MFABS(m.m13 - MFLOAT_C(0.0)) < MEPSILON) &&
           (MFABS(m.m21 - MFLOAT_C(0.0)) < MEPSILON) &&
           (MFABS(m.m22 - MFLOAT_C(1.0)) < MEPSILON) &&
           (MFABS(m.m23 - MFLOAT_C(0.0)) < MEPSILON) &&
           (MFABS(m.m31 - MFLOAT_C(0.0)) < MEPSILON) &&
           (MFABS(m.m32 - MFLOAT_C(0.0)) < MEPSILON) &&
           (MFABS(m.m33 - MFLOAT_C(1.0)) < MEPSILON);
}


/*!
 * @brief 检查两个矩阵是否相等
 * @param m0 第一个3x3矩阵
 * @param m1 第二个3x3矩阵
 * @return 如果所有对应元素都相等返回true，否则返回false
 * @note 使用MEPSILON作为浮点数比较的容差
 */
bool mat3_is_equal(mat3_st m0, mat3_st m1)
{
    /* 检查所有对应元素的差值是否都在容差范围内 */
    return (MFABS(m0.m11 - m1.m11) < MEPSILON) &&
           (MFABS(m0.m12 - m1.m12) < MEPSILON) &&
           (MFABS(m0.m13 - m1.m13) < MEPSILON) &&
           (MFABS(m0.m21 - m1.m21) < MEPSILON) &&
           (MFABS(m0.m22 - m1.m22) < MEPSILON) &&
           (MFABS(m0.m23 - m1.m23) < MEPSILON) &&
           (MFABS(m0.m31 - m1.m31) < MEPSILON) &&
           (MFABS(m0.m32 - m1.m32) < MEPSILON) &&
           (MFABS(m0.m33 - m1.m33) < MEPSILON);
}

/*!
 * @brief 检查两个矩阵是否相等（带容差）
 * @param m0 第一个3x3矩阵
 * @param m1 第二个3x3矩阵
 * @param epsilon 容差值
 * @return 如果所有对应元素都接近相等返回true，否则返回false
 * @note 使用指定的容差值进行比较
 */
bool mat3_is_equal_eps(mat3_st m0, mat3_st m1, ftype_t epsilon)
{
    /* 检查所有对应元素的差值是否都在容差范围内 */
    return (MFABS(m0.m11 - m1.m11) < epsilon) &&
           (MFABS(m0.m12 - m1.m12) < epsilon) &&
           (MFABS(m0.m13 - m1.m13) < epsilon) &&
           (MFABS(m0.m21 - m1.m21) < epsilon) &&
           (MFABS(m0.m22 - m1.m22) < epsilon) &&
           (MFABS(m0.m23 - m1.m23) < epsilon) &&
           (MFABS(m0.m31 - m1.m31) < epsilon) &&
           (MFABS(m0.m32 - m1.m32) < epsilon) &&
           (MFABS(m0.m33 - m1.m33) < epsilon);
}

/*!
 * @brief 检查矩阵是否对称
 * @param m 输入的3x3矩阵
 * @return 如果矩阵对称返回true，否则返回false
 * @note 对称矩阵满足 m[i][j] = m[j][i]
 */
bool mat3_is_symmetric(mat3_st m)
{
    /* 检查非对角线元素是否对称 */
    return (MFABS(m.m12 - m.m21) <= MEPSILON) &&
           (MFABS(m.m13 - m.m31) <= MEPSILON) &&
           (MFABS(m.m23 - m.m32) <= MEPSILON);
}


/*!
 * @brief 检查矩阵是否正交
 * @param m 输入的3x3矩阵
 * @return 如果矩阵正交返回true，否则返回false
 * @note 正交矩阵满足 M * M^T = I
 */
bool mat3_is_orthogonal(mat3_st m)
{
    mat3_st mt = mat3_transpose(m);        /* 计算转置矩阵 */
    mat3_st product = mat3_mul(m, mt);     /* 计算矩阵与转置的乘积 */
    mat3_st identity = mat3_identity();    /* 获取单位矩阵 */

    /* 检查乘积是否等于单位矩阵 */
    return mat3_is_equal(product, identity);
}


/*!
 * @brief 检查矩阵是否是对角矩阵
 * @param m 输入的3x3矩阵
 * @return 如果矩阵是对角矩阵返回true，否则返回false
 * @note 对角矩阵的非对角线元素都为零
 */
bool mat3_is_diagonal(mat3_st m)
{
    /* 检查所有非对角线元素是否接近零 */
    return (MFABS(m.m12) < MEPSILON) &&
           (MFABS(m.m13) < MEPSILON) &&
           (MFABS(m.m21) < MEPSILON) &&
           (MFABS(m.m23) < MEPSILON) &&
           (MFABS(m.m31) < MEPSILON) &&
           (MFABS(m.m32) < MEPSILON);
}


/*!
 * @brief 计算矩阵的负矩阵
 * @param m 输入的3x3矩阵
 * @return 返回负矩阵（所有元素取反）
 * @note 对矩阵的每个元素取负值
 */
mat3_st mat3_negate(mat3_st m)
{
    mat3_st result;
    result.m11 = -m.m11;    /* m11元素取反 */
    result.m12 = -m.m12;    /* m12元素取反 */
    result.m13 = -m.m13;    /* m13元素取反 */
    result.m21 = -m.m21;    /* m21元素取反 */
    result.m22 = -m.m22;    /* m22元素取反 */
    result.m23 = -m.m23;    /* m23元素取反 */
    result.m31 = -m.m31;    /* m31元素取反 */
    result.m32 = -m.m32;    /* m32元素取反 */
    result.m33 = -m.m33;    /* m33元素取反 */
    return result;
}


/*!
 * @brief 计算矩阵的转置矩阵
 * @param m 输入的3x3矩阵
 * @return 返回转置后的矩阵
 * @note 将矩阵的行和列互换
 */
mat3_st mat3_transpose(mat3_st m)
{
    mat3_st result;
    result.m11 = m.m11;    /* 主对角线元素保持不变 */
    result.m12 = m.m21;    /* 原第二行第一列变为第一行第二列 */
    result.m13 = m.m31;    /* 原第三行第一列变为第一行第三列 */
    result.m21 = m.m12;    /* 原第一行第二列变为第二行第一列 */
    result.m22 = m.m22;    /* 主对角线元素保持不变 */
    result.m23 = m.m32;    /* 原第三行第二列变为第二行第三列 */
    result.m31 = m.m13;    /* 原第一行第三列变为第三行第一列 */
    result.m32 = m.m23;    /* 原第二行第三列变为第三行第二列 */
    result.m33 = m.m33;    /* 主对角线元素保持不变 */
    return result;
}


/*!
 * @brief 计算3x3矩阵的行列式
 * @param m 输入的3x3矩阵
 * @return 返回矩阵的行列式值
 * @note 使用Sarrus法则计算3x3矩阵的行列式
 */
ftype_t mat3_det(mat3_st m)
{
    /* 使用Sarrus法则计算行列式 */
    ftype_t determinant = 
          m.m11 * m.m22 * m.m33    /* 主对角线乘积 */
        + m.m12 * m.m23 * m.m31    /* 第一循环对角线乘积 */
        + m.m13 * m.m21 * m.m32    /* 第二循环对角线乘积 */
        - m.m11 * m.m23 * m.m32    /* 副对角线乘积 */
        - m.m12 * m.m21 * m.m33    /* 第一循环副对角线乘积 */
        - m.m13 * m.m22 * m.m31;   /* 第二循环副对角线乘积 */
    return determinant;
}


/*!
 * @brief 计算矩阵的迹（主对角线元素之和）
 * @param m 输入的3x3矩阵
 * @return 返回矩阵的迹
 * @note 迹是矩阵主对角线元素的和
 */
ftype_t mat3_trace(mat3_st m)
{
    /* 计算主对角线元素之和 */
    return m.m11 + m.m22 + m.m33;
}


/*!
 * @brief 矩阵加法
 * @param m0 第一个3x3矩阵
 * @param m1 第二个3x3矩阵
 * @return 返回矩阵和
 * @note 对应元素相加
 */
mat3_st mat3_add(mat3_st m0, mat3_st m1)
{
    mat3_st result;
    result.m11 = m0.m11 + m1.m11;    /* 第一行第一列相加 */
    result.m12 = m0.m12 + m1.m12;    /* 第一行第二列相加 */
    result.m13 = m0.m13 + m1.m13;    /* 第一行第三列相加 */
    result.m21 = m0.m21 + m1.m21;    /* 第二行第一列相加 */
    result.m22 = m0.m22 + m1.m22;    /* 第二行第二列相加 */
    result.m23 = m0.m23 + m1.m23;    /* 第二行第三列相加 */
    result.m31 = m0.m31 + m1.m31;    /* 第三行第一列相加 */
    result.m32 = m0.m32 + m1.m32;    /* 第三行第二列相加 */
    result.m33 = m0.m33 + m1.m33;    /* 第三行第三列相加 */
    return result;
}


/*!
 * @brief 矩阵标量加法
 * @param m 输入的3x3矩阵
 * @param f 标量值
 * @return 返回矩阵与标量的和
 * @note 矩阵的每个元素加上标量值
 */
mat3_st mat3_add_f(mat3_st m, ftype_t f)
{
    mat3_st result;
    result.m11 = m.m11 + f;    /* m11元素加标量 */
    result.m12 = m.m12 + f;    /* m12元素加标量 */
    result.m13 = m.m13 + f;    /* m13元素加标量 */
    result.m21 = m.m21 + f;    /* m21元素加标量 */
    result.m22 = m.m22 + f;    /* m22元素加标量 */
    result.m23 = m.m23 + f;    /* m23元素加标量 */
    result.m31 = m.m31 + f;    /* m31元素加标量 */
    result.m32 = m.m32 + f;    /* m32元素加标量 */
    result.m33 = m.m33 + f;    /* m33元素加标量 */
    return result;
}


/*!
 * @brief 矩阵减法
 * @param m0 第一个3x3矩阵
 * @param m1 第二个3x3矩阵
 * @return 返回矩阵差
 * @note 对应元素相减
 */
mat3_st mat3_sub(mat3_st m0, mat3_st m1)
{
    mat3_st result;
    result.m11 = m0.m11 - m1.m11;    /* 第一行第一列相减 */
    result.m12 = m0.m12 - m1.m12;    /* 第一行第二列相减 */
    result.m13 = m0.m13 - m1.m13;    /* 第一行第三列相减 */
    result.m21 = m0.m21 - m1.m21;    /* 第二行第一列相减 */
    result.m22 = m0.m22 - m1.m22;    /* 第二行第二列相减 */
    result.m23 = m0.m23 - m1.m23;    /* 第二行第三列相减 */
    result.m31 = m0.m31 - m1.m31;    /* 第三行第一列相减 */
    result.m32 = m0.m32 - m1.m32;    /* 第三行第二列相减 */
    result.m33 = m0.m33 - m1.m33;    /* 第三行第三列相减 */
    return result;
}


/*!
 * @brief 矩阵标量减法
 * @param m 输入的3x3矩阵
 * @param f 标量值
 * @return 返回矩阵与标量的差
 * @note 矩阵的每个元素减去标量值
 */
mat3_st mat3_sub_f(mat3_st m, ftype_t f)
{
    mat3_st result;
    result.m11 = m.m11 - f;    /* m11元素减标量 */
    result.m12 = m.m12 - f;    /* m12元素减标量 */
    result.m13 = m.m13 - f;    /* m13元素减标量 */
    result.m21 = m.m21 - f;    /* m21元素减标量 */
    result.m22 = m.m22 - f;    /* m22元素减标量 */
    result.m23 = m.m23 - f;    /* m23元素减标量 */
    result.m31 = m.m31 - f;    /* m31元素减标量 */
    result.m32 = m.m32 - f;    /* m32元素减标量 */
    result.m33 = m.m33 - f;    /* m33元素减标量 */
    return result;
}


/*!
 * @brief 矩阵与向量乘法
 * @param m 输入的3x3矩阵
 * @param v 输入的3维向量
 * @return 返回矩阵与向量的乘积（3维向量）
 * @note 执行矩阵与向量的乘法运算
 */
vec3_st mat3_mul_vec(mat3_st m, vec3_st v)
{
    vec3_st result;
    result.x = m.m11 * v.x + m.m12 * v.y + m.m13 * v.z;    /* 第一行与向量点积 */
    result.y = m.m21 * v.x + m.m22 * v.y + m.m23 * v.z;    /* 第二行与向量点积 */
    result.z = m.m31 * v.x + m.m32 * v.y + m.m33 * v.z;    /* 第三行与向量点积 */
    return result;
}


/*!
 * @brief 矩阵乘法运算
 * @param m0 第一个3x3矩阵
 * @param m1 第二个3x3矩阵
 * @return 返回矩阵乘积结果
 * @note 执行标准的3x3矩阵乘法运算
 */
mat3_st mat3_mul(mat3_st m0, mat3_st m1)
{
    mat3_st result;
    /* 第一行与各列的点积 */
    result.m11 = m0.m11 * m1.m11 + m0.m12 * m1.m21 + m0.m13 * m1.m31;
    result.m12 = m0.m11 * m1.m12 + m0.m12 * m1.m22 + m0.m13 * m1.m32;
    result.m13 = m0.m11 * m1.m13 + m0.m12 * m1.m23 + m0.m13 * m1.m33;
    
    /* 第二行与各列的点积 */
    result.m21 = m0.m21 * m1.m11 + m0.m22 * m1.m21 + m0.m23 * m1.m31;
    result.m22 = m0.m21 * m1.m12 + m0.m22 * m1.m22 + m0.m23 * m1.m32;
    result.m23 = m0.m21 * m1.m13 + m0.m22 * m1.m23 + m0.m23 * m1.m33;
    
    /* 第三行与各列的点积 */
    result.m31 = m0.m31 * m1.m11 + m0.m32 * m1.m21 + m0.m33 * m1.m31;
    result.m32 = m0.m31 * m1.m12 + m0.m32 * m1.m22 + m0.m33 * m1.m32;
    result.m33 = m0.m31 * m1.m13 + m0.m32 * m1.m23 + m0.m33 * m1.m33;
    return result;
}


/*!
 * @brief 矩阵标量乘法
 * @param m 输入的3x3矩阵
 * @param f 标量乘数
 * @return 返回矩阵与标量的乘积
 * @note 将矩阵的每个元素乘以标量值
 */
mat3_st mat3_mul_f(mat3_st m, ftype_t f)
{
    mat3_st result;
    result.m11 = m.m11 * f;    /* m11元素乘以标量 */
    result.m12 = m.m12 * f;    /* m12元素乘以标量 */
    result.m13 = m.m13 * f;    /* m13元素乘以标量 */
    result.m21 = m.m21 * f;    /* m21元素乘以标量 */
    result.m22 = m.m22 * f;    /* m22元素乘以标量 */
    result.m23 = m.m23 * f;    /* m23元素乘以标量 */
    result.m31 = m.m31 * f;    /* m31元素乘以标量 */
    result.m32 = m.m32 * f;    /* m32元素乘以标量 */
    result.m33 = m.m33 * f;    /* m33元素乘以标量 */
    return result;
}


/*!
 * @brief 计算矩阵的逆矩阵
 * @param m 输入的3x3矩阵
 * @return 返回逆矩阵
 * @note 使用伴随矩阵法计算3x3矩阵的逆
 * @warning 当矩阵奇异（行列式为0）时返回单位矩阵
 */
mat3_st mat3_inverse(mat3_st m)
{
    mat3_st inv;
    ftype_t det;
    
    /* 计算行列式 */
    det = mat3_det(m);
    
    /* 检查行列式是否接近零（奇异矩阵） */
    if (MFABS(det) < MEPSILON) {
        /* 返回单位矩阵作为安全值 */
        return mat3_identity();
    }
    
    ftype_t inv_det = MFLOAT_C(1.0) / det;    /* 计算行列式的倒数 */
    
    /* 计算伴随矩阵（转置的余子式矩阵） */
    inv.m11 = (m.m22 * m.m33 - m.m23 * m.m32) * inv_det;    /* m11的余子式 */
    inv.m12 = (m.m13 * m.m32 - m.m12 * m.m33) * inv_det;    /* m12的余子式 */
    inv.m13 = (m.m12 * m.m23 - m.m13 * m.m22) * inv_det;    /* m13的余子式 */
    
    inv.m21 = (m.m23 * m.m31 - m.m21 * m.m33) * inv_det;    /* m21的余子式 */
    inv.m22 = (m.m11 * m.m33 - m.m13 * m.m31) * inv_det;    /* m22的余子式 */
    inv.m23 = (m.m13 * m.m21 - m.m11 * m.m23) * inv_det;    /* m23的余子式 */
    
    inv.m31 = (m.m21 * m.m32 - m.m22 * m.m31) * inv_det;    /* m31的余子式 */
    inv.m32 = (m.m12 * m.m31 - m.m11 * m.m32) * inv_det;    /* m32的余子式 */
    inv.m33 = (m.m11 * m.m22 - m.m12 * m.m21) * inv_det;    /* m33的余子式 */
    
    return inv;
}


/*!
 * @brief 计算矩阵的范数
 * @param m 输入的3x3矩阵
 * @param norm_type 范数类型（0:Frobenius范数, 1:1-范数, 2:∞-范数）
 * @return 返回矩阵的范数值
 * @note 支持三种常见的矩阵范数计算
 */
ftype_t mat3_norm(mat3_st m, int norm_type)
{
    switch (norm_type) {
        case 0: /* Frobenius范数（所有元素平方和的平方根） */
            return MSQRT(m.m11*m.m11 + m.m12*m.m12 + m.m13*m.m13 +
                         m.m21*m.m21 + m.m22*m.m22 + m.m23*m.m23 +
                         m.m31*m.m31 + m.m32*m.m32 + m.m33*m.m33);
        
        case 1: /* 1-范数（列和的最大值） */
            return MFMAX(MFMAX(MFABS(m.m11) + MFABS(m.m21) + MFABS(m.m31),
                        MFABS(m.m12) + MFABS(m.m22) + MFABS(m.m32)),
                        MFABS(m.m13) + MFABS(m.m23) + MFABS(m.m33));
        
        case 2: /* ∞-范数（行和的最大值） */
            return MFMAX(MFMAX(MFABS(m.m11) + MFABS(m.m12) + MFABS(m.m13),
                        MFABS(m.m21) + MFABS(m.m22) + MFABS(m.m23)),
                        MFABS(m.m31) + MFABS(m.m32) + MFABS(m.m33));
        
        default:
            return MFLOAT_C(0.0);    /* 无效范数类型返回0 */
    }
}


/*!
 * @brief 计算矩阵的条件数
 * @param m 输入的3x3矩阵
 * @return 返回矩阵的条件数（范数乘积）
 * @note 条件数 = ||M|| * ||M⁻¹||，反映矩阵的数值稳定性
 */
ftype_t mat3_cond(mat3_st m)
{
    mat3_st inv = mat3_inverse(m);                /* 计算逆矩阵 */
    return mat3_norm(m, 0) * mat3_norm(inv, 0);  /* 计算范数乘积 */
}


/*!
 * @brief 应用缩放变换到矩阵
 * @param m 输入的3x3矩阵
 * @param scalar 缩放因子
 * @return 返回缩放后的矩阵
 * @note 将矩阵的每个元素乘以缩放因子
 */
mat3_st mat3_scale(mat3_st m, ftype_t scalar)
{
    return mat3_mul_f(m, scalar);    /* 调用标量乘法函数 */
}


/*!
 * @brief 创建缩放矩阵
 * @param sx X轴缩放因子
 * @param sy Y轴缩放因子
 * @param sz Z轴缩放因子
 * @return 返回3x3缩放矩阵
 * @note 创建对角缩放矩阵，主对角线为缩放因子
 */
mat3_st mat3_scale_matrix(ftype_t sx, ftype_t sy, ftype_t sz)
{
    mat3_st result = mat3_identity();    /* 从单位矩阵开始 */
    result.m11 = sx;                     /* 设置X轴缩放因子 */
    result.m22 = sy;                     /* 设置Y轴缩放因子 */
    result.m33 = sz;                     /* 设置Z轴缩放因子 */
    return result;
}


/*!
 * @brief 计算矩阵指数（简化实现）
 * @param m 输入的3x3矩阵
 * @return 返回矩阵指数
 * @note 使用泰勒级数展开的前几项进行近似计算
 */
mat3_st mat3_exp(mat3_st m)
{
    /* 使用泰勒级数展开：exp(M) ≈ I + M + M²/2! + M³/3! + M⁴/4! */
    mat3_st result = mat3_identity();    /* 初始化为单位矩阵 */
    mat3_st term = m;                    /* 第一项：M */
    
    /* I + M */
    result = mat3_add(result, term);
    
    /* + M²/2! */
    term = mat3_mul(term, m);            /* 计算M² */
    term = mat3_mul_f(term, MFLOAT_C(0.5));        /* 除以2! */
    result = mat3_add(result, term);
    
    /* + M³/6 */
    term = mat3_mul(term, m);            /* 计算M³ */
    term = mat3_mul_f(term, MFLOAT_C(1.0/6.0));    /* 除以3!（3!=6） */
    result = mat3_add(result, term);
    
    /* + M⁴/24 */
    term = mat3_mul(term, m);            /* 计算M⁴ */
    term = mat3_mul_f(term, MFLOAT_C(1.0/24.0));   /* 除以4!（4!=24） */
    result = mat3_add(result, term);
    
    return result;
}


/*!
 * @brief 计算矩阵对数（简化实现）
 * @param m 输入的3x3矩阵
 * @return 返回矩阵对数
 * @note 使用近似方法计算矩阵对数
 */
mat3_st mat3_log(mat3_st m)
{
    /* 简化实现：对于接近单位矩阵的情况 */
    mat3_st a = mat3_sub(m, mat3_identity());    /* 计算 M - I */
    mat3_st result = a;                          /* 第一项：A */
    
    /* log(I + A) ≈ A - A²/2 + A³/3 - A⁴/4 */
    mat3_st a2 = mat3_mul(a, a);                 /* 计算A² */
    mat3_st a3 = mat3_mul(a2, a);                /* 计算A³ */
    mat3_st a4 = mat3_mul(a3, a);                /* 计算A⁴ */
    
    result = mat3_sub(result, mat3_mul_f(a2, MFLOAT_C(0.5)));        /* 减去A²/2 */
    result = mat3_add(result, mat3_mul_f(a3, MFLOAT_C(1.0/3.0)));    /* 加上A³/3 */
    result = mat3_sub(result, mat3_mul_f(a4, MFLOAT_C(0.25)));       /* 减去A⁴/4 */
    
    return result;
}


/*!
 * @brief 计算矩阵的幂
 * @param m 输入的3x3矩阵
 * @param exponent 幂指数
 * @return 返回矩阵的幂
 * @note 使用矩阵对数和指数计算矩阵幂：M^p = exp(p * log(M))
 */
mat3_st mat3_pow(mat3_st m, ftype_t exponent)
{
    mat3_st log_m = mat3_log(m);                 /* 计算矩阵对数 */
    mat3_st p_log_m = mat3_mul_f(log_m, exponent); /* 乘以指数 */
    return mat3_exp(p_log_m);                    /* 计算矩阵指数 */
}


/*!
 * @brief 矩阵的正交归一化（施密特正交化）
 * @param basis 输入的基础矩阵（包含三个向量）
 * @return 返回正交归一化后的矩阵
 * @note 使用施密特正交化方法将一组向量转换为正交归一化基
 */
mat3_st mat3_orthonormalization(mat3_st basis)
{
    vec3_st v0 = vec3(basis.v[0], basis.v[1], basis.v[2]);    /* 提取第一个向量 */
    vec3_st v1 = vec3(basis.v[3], basis.v[4], basis.v[5]);    /* 提取第二个向量 */
    vec3_st v2 = vec3(basis.v[6], basis.v[7], basis.v[8]);    /* 提取第三个向量 */

    /* 检查向量是否线性无关 */
    if (!vec3_is_linear_independent(v0, v1, v2)) {
        return basis;    /* 如果线性相关，返回原矩阵 */
    }

    /* 施密特正交化过程 */
    vec3_st u0 = v0;    /* 第一个正交向量 */
    vec3_st u1 = vec3_sub(v1, vec3_project(v1, u0));    /* 第二个正交向量 */
    vec3_st u2 = vec3_sub(vec3_sub(v2, vec3_project(v2, u0)), vec3_project(v2, u1)); /* 第三个正交向量 */

    /* 归一化向量 */
    vec3_st r0 = vec3_unit(u0);    /* 归一化第一个向量 */
    vec3_st r1 = vec3_unit(u1);    /* 归一化第二个向量 */
    vec3_st r2 = vec3_unit(u2);    /* 归一化第三个向量 */

    /* 构建正交归一化矩阵 */
    mat3_st result;
    result.v[0] = r0.x; result.v[1] = r0.y; result.v[2] = r0.z;    /* 第一列向量 */
    result.v[3] = r1.x; result.v[4] = r1.y; result.v[5] = r1.z;    /* 第二列向量 */
    result.v[6] = r2.x; result.v[7] = r2.y; result.v[8] = r2.z;    /* 第三列向量 */
    return result;
}


/*!
 * @brief 创建绕X轴旋转的矩阵
 * @param f 旋转角度（弧度）
 * @return 返回绕X轴旋转的3x3矩阵
 * @note 使用标准的绕X轴旋转矩阵公式
 */
mat3_st mat3_rotation_x(ftype_t f)
{
    ftype_t c = MCOS(f);    /* 计算余弦值 */
    ftype_t s = MSIN(f);    /* 计算正弦值 */
    mat3_st result = mat3_identity();    /* 从单位矩阵开始 */
    result.m22 = c;         /* 设置(2,2)元素为cos(θ) */
    result.m23 = -s;        /* 设置(2,3)元素为-sin(θ) */
    result.m32 = s;         /* 设置(3,2)元素为sin(θ) */
    result.m33 = c;         /* 设置(3,3)元素为cos(θ) */
    return result;
}


/*!
 * @brief 创建绕Y轴旋转的矩阵
 * @param f 旋转角度（弧度）
 * @return 返回绕Y轴旋转的3x3矩阵
 * @note 使用标准的绕Y轴旋转矩阵公式
 */
mat3_st mat3_rotation_y(ftype_t f)
{
    ftype_t c = MCOS(f);    /* 计算余弦值 */
    ftype_t s = MSIN(f);    /* 计算正弦值 */
    mat3_st result = mat3_identity();    /* 从单位矩阵开始 */
    result.m11 = c;         /* 设置(1,1)元素为cos(θ) */
    result.m13 = s;         /* 设置(1,3)元素为sin(θ) */
    result.m31 = -s;        /* 设置(3,1)元素为-sin(θ) */
    result.m33 = c;         /* 设置(3,3)元素为cos(θ) */
    return result;
}


/*!
 * @brief 创建绕Z轴旋转的矩阵
 * @param f 旋转角度（弧度）
 * @return 返回绕Z轴旋转的3x3矩阵
 * @note 使用标准的绕Z轴旋转矩阵公式
 */
mat3_st mat3_rotation_z(ftype_t f)
{
    ftype_t c = MCOS(f);    /* 计算余弦值 */
    ftype_t s = MSIN(f);    /* 计算正弦值 */
    mat3_st result = mat3_identity();    /* 从单位矩阵开始 */
    result.m11 = c;         /* 设置(1,1)元素为cos(θ) */
    result.m12 = -s;        /* 设置(1,2)元素为-sin(θ) */
    result.m21 = s;         /* 设置(2,1)元素为sin(θ) */
    result.m22 = c;         /* 设置(2,2)元素为cos(θ) */
    return result;
}


/*!
 * @brief 矩阵线性插值
 * @param from 起始矩阵
 * @param to 结束矩阵
 * @param t 插值因子（0.0到1.0之间）
 * @return 返回插值后的矩阵
 * @note 对两个矩阵的每个元素进行线性插值
 */
mat3_st mat3_lerp(mat3_st from, mat3_st to, ftype_t t)
{
    mat3_st result;
    result.m11 = from.m11 + (to.m11 - from.m11) * t;    /* m11元素插值 */
    result.m12 = from.m12 + (to.m12 - from.m12) * t;    /* m12元素插值 */
    result.m13 = from.m13 + (to.m13 - from.m13) * t;    /* m13元素插值 */
    result.m21 = from.m21 + (to.m21 - from.m21) * t;    /* m21元素插值 */
    result.m22 = from.m22 + (to.m22 - from.m22) * t;    /* m22元素插值 */
    result.m23 = from.m23 + (to.m23 - from.m23) * t;    /* m23元素插值 */
    result.m31 = from.m31 + (to.m31 - from.m31) * t;    /* m31元素插值 */
    result.m32 = from.m32 + (to.m32 - from.m32) * t;    /* m32元素插值 */
    result.m33 = from.m33 + (to.m33 - from.m33) * t;    /* m33元素插值 */
    return result;
}

/**********************************************************************************************************************
 * End of spacemath file
 *********************************************************************************************************************/
