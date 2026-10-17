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
 * @file rotation.c
 * @brief 旋转表示转换实现文件
 * @author scilogyhunter
 * @date 2025.09.01
 * @version V0.1.2
 *
 * 本文件实现了不同旋转表示之间的转换，包括欧拉角、旋转矩阵、四元数、旋转矢量和轴角表示。
 * 支持各种旋转表示之间的相互转换和旋转操作。
 */

/*!
 * @defgroup rotation_modify 修改记录
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

/** @} */ /* end of group rotation_modify */

#include "spacemath.h"

/*!
 * @brief 计算轴角表示的逆旋转
 * @param a 输入的轴角表示
 * @return 返回逆轴角表示（旋转轴取反，角度保持不变）
 * @note 轴角表示的逆旋转通过旋转轴取反实现
 */
axis_st rotation_a_rvs(axis_st a)
{
    return axis(-a.v3.x, -a.v3.y, -a.v3.z, a.angle);    /* 旋转轴取反，角度保持不变 */
}


/*!
 * @brief 创建绕X轴旋转的轴角表示
 * @param angle 旋转角度（弧度）
 * @return 返回绕X轴旋转的轴角表示
 * @note 旋转轴为X轴正方向，角度为输入参数
 */
axis_st rotation_a_rx(ftype_t angle)
{
    return axis(MFLOAT_C(1.0), MFLOAT_C(0.0), MFLOAT_C(0.0), angle);    /* X轴旋转，旋转轴为(1,0,0) */
}


/*!
 * @brief 创建绕Y轴旋转的轴角表示
 * @param angle 旋转角度（弧度）
 * @return 返回绕Y轴旋转的轴角表示
 * @note 旋转轴为Y轴正方向，角度为输入参数
 */
axis_st rotation_a_ry(ftype_t angle)
{
    return axis(MFLOAT_C(0.0), MFLOAT_C(1.0), MFLOAT_C(0.0), angle);    /* Y轴旋转，旋转轴为(0,1,0) */
}


/*!
 * @brief 创建绕Z轴旋转的轴角表示
 * @param angle 旋转角度（弧度）
 * @return 返回绕Z轴旋转的轴角表示
 * @note 旋转轴为Z轴正方向，角度为输入参数
 */
axis_st rotation_a_rz(ftype_t angle)
{
    return axis(MFLOAT_C(0.0), MFLOAT_C(0.0), MFLOAT_C(1.0), angle);    /* Z轴旋转，旋转轴为(0,0,1) */
}


/*!
 * @brief 计算欧拉角表示的逆旋转
 * @param e 输入的欧拉角表示
 * @return 返回逆欧拉角表示（所有角度分量取反）
 * @note 欧拉角表示的逆旋转通过所有角度分量取反实现
 */
eula_st rotation_e_rvs(eula_st e)
{
    return eula(-e.x, -e.y, -e.z);    /* 所有欧拉角分量取反 */
}


/*!
 * @brief 创建绕X轴旋转的欧拉角表示
 * @param angle 旋转角度（弧度）
 * @return 返回绕X轴旋转的欧拉角表示
 * @note 只有X分量有角度值，Y和Z分量为0
 */
eula_st rotation_e_rx(ftype_t angle)
{
    return eula(angle, MFLOAT_C(0.0), MFLOAT_C(0.0));    /* X轴旋转，只有X分量有角度 */
}


/*!
 * @brief 创建绕Y轴旋转的欧拉角表示
 * @param angle 旋转角度（弧度）
 * @return 返回绕Y轴旋转的欧拉角表示
 * @note 只有Y分量有角度值，X和Z分量为0
 */
eula_st rotation_e_ry(ftype_t angle)
{
    return eula(MFLOAT_C(0.0), angle, MFLOAT_C(0.0));    /* Y轴旋转，只有Y分量有角度 */
}


/*!
 * @brief 创建绕Z轴旋转的欧拉角表示
 * @param angle 旋转角度（弧度）
 * @return 返回绕Z轴旋转的欧拉角表示
 * @note 只有Z分量有角度值，X和Y分量为0
 */
eula_st rotation_e_rz(ftype_t angle)
{
    return eula(MFLOAT_C(0.0), MFLOAT_C(0.0), angle);    /* Z轴旋转，只有Z分量有角度 */
}


/*!
 * @brief 计算旋转矩阵的逆旋转
 * @param m 输入的旋转矩阵
 * @return 返回逆旋转矩阵（转置矩阵）
 * @note 旋转矩阵的逆旋转等于其转置矩阵
 */
mat3_st rotation_m_rvs(mat3_st m)
{
    return mat3_transpose(m);    /* 旋转矩阵的逆等于转置 */
}


/*!
 * @brief 创建绕X轴旋转的旋转矩阵
 * @param angle 旋转角度（弧度）
 * @return 返回绕X轴旋转的旋转矩阵
 * @note 调用mat3_rotation_x函数创建绕X轴旋转矩阵
 */
mat3_st rotation_m_rx(ftype_t angle)
{
    return mat3_rotation_x(angle);    /* 调用绕X轴旋转矩阵函数 */
}


/*!
 * @brief 创建绕Y轴旋转的旋转矩阵
 * @param angle 旋转角度（弧度）
 * @return 返回绕Y轴旋转的旋转矩阵
 * @note 调用mat3_rotation_y函数创建绕Y轴旋转矩阵
 */
mat3_st rotation_m_ry(ftype_t angle)
{
    return mat3_rotation_y(angle);    /* 调用绕Y轴旋转矩阵函数 */
}


/*!
 * @brief 创建绕Z轴旋转的旋转矩阵
 * @param angle 旋转角度（弧度）
 * @return 返回绕Z轴旋转的旋转矩阵
 * @note 调用mat3_rotation_z函数创建绕Z轴旋转矩阵
 */
mat3_st rotation_m_rz(ftype_t angle)
{
    return mat3_rotation_z(angle);    /* 调用绕Z轴旋转矩阵函数 */
}


/*!
 * @brief 计算四元数的逆旋转
 * @param q 输入的四元数
 * @return 返回逆四元数（共轭四元数）
 * @note 四元数的逆旋转等于其共轭四元数
 */
quat_st rotation_q_rvs(quat_st q)
{
    return quat_conjugate(q);    /* 四元数的逆等于共轭 */
}


/*!
 * @brief 创建绕X轴旋转的四元数
 * @param angle 旋转角度（弧度）
 * @return 返回绕X轴旋转的四元数
 * @note 调用quat_rotation_x函数创建绕X轴旋转四元数
 */
quat_st rotation_q_rx(ftype_t angle)
{
    return quat_rotation_x(angle);    /* 调用绕X轴旋转四元数函数 */
}


/*!
 * @brief 创建绕Y轴旋转的四元数
 * @param angle 旋转角度（弧度）
 * @return 返回绕Y轴旋转的四元数
 * @note 调用quat_rotation_y函数创建绕Y轴旋转四元数
 */
quat_st rotation_q_ry(ftype_t angle)
{
    return quat_rotation_y(angle);    /* 调用绕Y轴旋转四元数函数 */
}


/*!
 * @brief 创建绕Z轴旋转的四元数
 * @param angle 旋转角度（弧度）
 * @return 返回绕Z轴旋转的四元数
 * @note 调用quat_rotation_z函数创建绕Z轴旋转四元数
 */
quat_st rotation_q_rz(ftype_t angle)
{
    return quat_rotation_z(angle);    /* 调用绕Z轴旋转四元数函数 */
}


/*!
 * @brief 将欧拉旋转角转换为旋转矩阵（使用内旋约定和指定顺序）
 * @param e 欧拉旋转角向量（x、y、z分量分别表示绕对应轴的旋转角度）
 * @param order 旋转顺序字符串（如"xyz"、"zyx"等）
 * @return 返回对应的旋转矩阵
 * @note 使用内旋约定，根据指定的旋转顺序构建旋转矩阵
 */
mat3_st rotation_e2m_order(eula_st e, char  *order)
{
    mat3_st m;
    mat3_st r[3];

    /* 验证欧拉角是否有效 */
    if (eula_validate(e, order) == false) {
        return mat3_zero();    /* 欧拉角无效，返回零矩阵 */
    }

    for (int i = 0; i < 3; i++) {
        switch (order[i]) {
            case 'x': r[i] = mat3_rotation_x(e.x); break;    /* X轴旋转 */
            case 'y': r[i] = mat3_rotation_y(e.y); break;    /* Y轴旋转 */
            case 'z': r[i] = mat3_rotation_z(e.z); break;    /* Z轴旋转 */
            default: return mat3_zero();          /* 默认单位矩阵 */
        }
    }

    /* 内旋：矩阵乘法顺序 R = R3 * R2 * R1 表示：先执行R1旋转，然后R2，最后R3*/
    m = mat3_mul(r[2], mat3_mul(r[1], r[0])); /* 矩阵乘法组合旋转 */

    return m;
}

/*!
 * @brief 将旋转矩阵转换为欧拉旋转角（使用内旋约定和指定顺序）
 * @param m 输入的旋转矩阵
 * @param order 旋转顺序字符串（如"xyz"、"zyx"等）
 * @return 返回对应的欧拉旋转角
 * @note 使用内旋约定，根据指定的旋转顺序解析旋转矩阵
 */
eula_st rotation_m2e_order(mat3_st m, char *order)
{
    eula_st e = eula_zero();
#if (CFG_FLOATWORD_BITSIZE == 32)
    ftype_t epsilon = MFLOAT_C(1e-6);
    ftype_t small_eps = MFLOAT_C(1e-8);
#endif

#if (CFG_FLOATWORD_BITSIZE == 64)
    ftype_t epsilon = MFLOAT_C(1e-6);
    ftype_t small_eps = MFLOAT_C(1e-10);
#endif

#if (CFG_FLOATWORD_BITSIZE == 128)
    ftype_t epsilon = MFLOAT_C(1e-6);
    ftype_t small_eps = MFLOAT_C(1e-10);
#endif
    
    if (strncmp(order, "xyz", 3) == 0) {
        /* XYZ顺序：R = Rz(ψ) * Ry(θ) * Rx(φ) */
        // 从 m31 = -sin(θ_y) 提取 θ_y
        if (MFABS(m.m31 + MFLOAT_C(1.0)) < epsilon) {
            // 万向锁：θ_y = -π/2
            e.y = -MPI_2;
            e.x = MFLOAT_C(0.0);
            e.z = MATAN2(-m.m12, m.m22);
        } else if (MFABS(m.m31 - MFLOAT_C(1.0)) < epsilon) {
            // 万向锁：θ_y = π/2
            e.y = MPI_2;
            e.x = MFLOAT_C(0.0);
            e.z = MATAN2(m.m12, -m.m22);
        } else {
            // 正常情况
            e.y = safe_asin(-m.m31);
            ftype_t cy = MCOS(e.y);
            
            if (MFABS(cy) > small_eps) {
                e.z = MATAN2(m.m21 / cy, m.m11 / cy);
                e.x = MATAN2(m.m32 / cy, m.m33 / cy);
            } else {
                e.z = MATAN2(m.m21, m.m11);
                e.x = MATAN2(m.m32, m.m33);
            }
        }
    } else if (strncmp(order, "xzy", 3) == 0) {
        /* XZY顺序：R = Ry(ψ) * Rz(θ) * Rx(φ) */
        // 从 m21 = sin(θ_z) 提取 θ_z
        if (MFABS(m.m21 + MFLOAT_C(1.0)) < epsilon) {
            // 万向锁：θ_z = -π/2
            e.z = -MPI_2;
            e.x = MFLOAT_C(0.0);
            e.y = MATAN2(-m.m13, m.m33);
        } else if (MFABS(m.m21 - MFLOAT_C(1.0)) < epsilon) {
            // 万向锁：θ_z = π/2
            e.z = MPI_2;
            e.x = MFLOAT_C(0.0);
            e.y = MATAN2(m.m13, -m.m33);
        } else {
            // 正常情况
            e.z = safe_asin(m.m21);
            ftype_t cz = MCOS(e.z);
            
            if (MFABS(cz) > small_eps) {
                e.y = MATAN2(-m.m31 / cz, m.m11 / cz);
                e.x = MATAN2(-m.m23 / cz, m.m22 / cz);
            } else {
                e.y = MATAN2(-m.m31, m.m11);
                e.x = MATAN2(-m.m23, m.m22);
            }
        }
    } else if (strncmp(order, "yxz", 3) == 0) {
        /* YXZ顺序：R = Rz(ψ) * Rx(θ) * Ry(φ) */
        // 从 m32 = -sin(θ_x) 提取 θ_x
        if (MFABS(m.m32 + MFLOAT_C(1.0)) < epsilon) {
            // 万向锁：θ_x = -π/2
            e.x = -MPI_2;
            e.y = MFLOAT_C(0.0);
            e.z = MATAN2(-m.m21, m.m11);
        } else if (MFABS(m.m32 - MFLOAT_C(1.0)) < epsilon) {
            // 万向锁：θ_x = π/2
            e.x = MPI_2;
            e.y = MFLOAT_C(0.0);
            e.z = MATAN2(m.m21, -m.m11);
        } else {
            // 正常情况
            e.x = safe_asin(m.m32);
            ftype_t cx = MCOS(e.x);
            
            if (MFABS(cx) > small_eps) {
                e.z = MATAN2(-m.m12 / cx, m.m22 / cx);
                e.y = MATAN2(-m.m31 / cx, m.m33 / cx);
            } else {
                e.z = MATAN2(-m.m12, m.m22);
                e.y = MATAN2(-m.m31, m.m33);
            }
        }
    } else if (strncmp(order, "yzx", 3) == 0) {
        /* YZX顺序：R = Rx(ψ) * Rz(θ) * Ry(φ) */
        // 从 m12 = -sin(θ_z) 提取 θ_z
        if (MFABS(m.m12 + MFLOAT_C(1.0)) < epsilon) {
            // 万向锁：θ_z = -π/2
            e.z = -MPI_2;
            e.x = MFLOAT_C(0.0);
            e.y = MATAN2(-m.m31, m.m11);
        } else if (MFABS(m.m12 - MFLOAT_C(1.0)) < epsilon) {
            // 万向锁：θ_z = π/2
            e.z = MPI_2;
            e.x = MFLOAT_C(0.0);
            e.y = MATAN2(m.m31, -m.m11);
        } else {
            // 正常情况
            e.z = safe_asin(-m.m12);
            ftype_t cz = MCOS(e.z);
            
            if (MFABS(cz) > small_eps) {
                e.y = MATAN2(m.m13 / cz, m.m11 / cz);
                e.x = MATAN2(m.m32 / cz, m.m22 / cz);
            } else {
                e.y = MATAN2(m.m13, m.m11);
                e.x = MATAN2(m.m32, m.m22);
            }
        }
    } else if (strncmp(order, "zxy", 3) == 0) {
        /* ZXY顺序：R = Ry(e.y) * Rx(e.x) * Rz(e.z) (内旋顺序: z, x, y) */
        // 从 m23 = -sin(e.x) 提取 e.x
        if (MFABS(m.m23 + MFLOAT_C(1.0)) < epsilon) {
            // 万向锁：e.x = -π/2
            e.x = -MPI_2;
            e.z = MFLOAT_C(0.0);
            e.y = MATAN2(-m.m31, m.m33);
        } else if (MFABS(m.m23 - MFLOAT_C(1.0)) < epsilon) {
            // 万向锁：e.x = π/2
            e.x = MPI_2;
            e.z = MFLOAT_C(0.0);
            e.y = MATAN2(m.m31, -m.m33);
        } else {
            // 正常情况
            e.x = safe_asin(-m.m23);
            ftype_t cx = MCOS(e.x);
            
            if (MFABS(cx) > small_eps) {
                e.z = MATAN2(m.m21 / cx, m.m22 / cx);
                e.y = MATAN2(m.m13 / cx, m.m33 / cx);
            } else {
                e.z = MATAN2(m.m21, m.m22);
                e.y = MATAN2(m.m13, m.m33);
            }
        }
    } else if (strncmp(order, "zyx", 3) == 0) {
        /* ZYX顺序：R = Rx(e.x) * Ry(e.y) * Rz(e.z) (内旋顺序: z, y, x) */
        // 从 m31 = -sin(e.y) 提取 e.y
        if (MFABS(m.m13 + MFLOAT_C(1.0)) < epsilon) {
            // 万向锁：e.y = -π/2
            e.y = -MPI_2;
            e.x = MFLOAT_C(0.0);
            e.z = MATAN2(m.m21, m.m22);
        } else if (MFABS(m.m13 - MFLOAT_C(1.0)) < epsilon) {
            // 万向锁：e.y = π/2
            e.y = MPI_2;
            e.x = MFLOAT_C(0.0);
            e.z = MATAN2(-m.m21, -m.m22);
        } else {
            // 正常情况
            e.y = safe_asin(m.m13);
            ftype_t cy = MCOS(e.y);
            
            if (MFABS(cy) > small_eps) {
                e.z = MATAN2(-m.m12 / cy, m.m11 / cy);
                e.x = MATAN2(-m.m23 / cy, m.m33 / cy);
            } else {
                e.z = MATAN2(-m.m12, m.m11);
                e.x = MATAN2(-m.m23, m.m33);
            }
        }
    } else {
        fprintf(stderr, "错误: 未知的旋转顺序 '%s'\n", order);
        return eula_zero();
    }
    
    return e;
}

/*!
 * @brief 将欧拉旋转角转换为四元数（使用内旋约定和指定顺序）
 * @param e 欧拉旋转角（x、y、z分量分别表示绕对应轴的旋转角度）
 * @param order 旋转顺序字符串（如"xyz"、"zyx"等）
 * @return 返回对应的四元数
 * @note 使用内旋约定，根据指定的旋转顺序构建旋转矩阵
 */
quat_st rotation_e2q_order(eula_st e, char  *order)
{
    quat_st qout;
    quat_st q[3];

    /* 验证欧拉角是否有效 */
    if (eula_validate(e, order) == false) {
        return quat_zero();    /* 欧拉角无效，返回零矩阵 */
    }

    for (int i = 0; i < 3; i++) {
        switch (order[i]) {
            case 'x': q[i] = quat_rotation_x(e.x); break;    /* X轴旋转 */
            case 'y': q[i] = quat_rotation_y(e.y); break;    /* Y轴旋转 */
            case 'z': q[i] = quat_rotation_z(e.z); break;    /* Z轴旋转 */
            default: return quat_zero();          /* 默认四元数 */
        }
    }

    /* 内旋：四元数乘法顺序 q = q3 * q2 * q1 表示：先执行q1旋转，然后q2，最后q3*/
    qout = quat_mul(q[2], quat_mul(q[1], q[0])); /* 四元数乘法组合旋转 */

    return qout;
}

/*!
 * @brief 指定转序的四元数转欧拉角
 * @param q 输入的四元数
 * @param order 旋转顺序字符串（如"xyz"、"zyx"等）
 * @return 返回对应的欧拉旋转角向量（弧度）
 * @note 使用内旋约定，根据指定的旋转顺序构建旋转矩阵
 */
eula_st rotation_q2e_order(quat_st q, char *order)
{
    /* 首先将四元数转换为旋转矩阵 */
    mat3_st m = rotation_q2m(q);
    /* 然后从旋转矩阵中提取欧拉角 */
    return rotation_m2e_order(m, order);
}

/*!
 * @brief 将欧拉旋转角转换为旋转矩阵（使用内旋约定）
 * @param e 欧拉旋转角向量（x、y、z分量分别表示绕对应轴的旋转角度）
 * @return 返回对应的旋转矩阵
 * @note 使用默认旋转顺序将欧拉角转换为旋转矩阵
 */
mat3_st rotation_e2m(eula_st e)
{
    char *order = CFG_EULER_ORDER;               /* 使用默认旋转顺序 */
    return rotation_e2m_order(e, order);       /* 调用带顺序参数的函数 */
}


/*!
 * @brief 将欧拉旋转角转换为四元数
 * @param e 欧拉旋转角向量（x、y、z分量分别表示绕对应轴的旋转角度）
 * @return 返回对应的四元数
 * @note 将欧拉角转换为四元数表示（使用默认旋转顺序）
 */
quat_st rotation_e2q(eula_st e)
{
    char *order = CFG_EULER_ORDER;               /* 使用默认旋转顺序 */
    return (rotation_e2q_order(e, order));     /* 调用带顺序参数的函数 */
}


/*!
 * @brief 将欧拉旋转角转换为轴角形式
 * @param e 欧拉旋转角向量（x、y、z分量分别表示绕对应轴的旋转角度）
 * @return 返回对应的轴角表示
 * @note 将欧拉角转换为轴角表示（使用默认旋转顺序）
 */
axis_st rotation_e2a(eula_st e)
{
    return (rotation_m2a(rotation_e2m(e)));    /* 通过旋转矩阵转换为轴角 */
}


/*!
 * @brief 将旋转矩阵转换为欧拉旋转角（内旋约定）
 * @param m 旋转矩阵（行优先存储：m11,m12,m13; m21,m22,m23; m31,m32,m33）
 * @return 返回对应的欧拉旋转角向量（弧度）
 * @note 使用默认旋转顺序从旋转矩阵中提取欧拉角
 */
eula_st rotation_m2e(mat3_st m)
{
    char *order = CFG_EULER_ORDER;               /* 使用默认旋转顺序 */
    return (rotation_m2e_order(m, order));     /* 调用带顺序参数的函数 */
}


/*!
 * @brief 将旋转矩阵转换为四元数（修正版）
 * @param m 旋转矩阵
 * @return 返回对应的四元数
 * @note 使用标准算法将旋转矩阵转换为四元数，处理各种情况
 */
quat_st rotation_m2q(mat3_st m)
{
    quat_st q;
    ftype_t s;
    ftype_t trace = m.m11 + m.m22 + m.m33;       /* 计算矩阵的迹 */
    
    if (trace > MFLOAT_C(0.0)) {
        s = MSQRT(trace + MFLOAT_C(1.0)) * MFLOAT_C(2.0);  /* s = 4 * qw */
        if (MFABS(s) < MEPSILON) {
            return quat_identity();             /* 数值不稳定，返回单位四元数 */
        }
        q.w = MFLOAT_C(0.25) * s;                       /* 计算实部 */
        q.x = (m.m32 - m.m23) / s;             /* 计算x分量 */
        q.y = (m.m13 - m.m31) / s;             /* 计算y分量 */
        q.z = (m.m21 - m.m12) / s;             /* 计算z分量 */
    } else if ((m.m11 > m.m22) && (m.m11 > m.m33)) {
        s = MSQRT(MFLOAT_C(1.0) + m.m11 - m.m22 - m.m33) * MFLOAT_C(2.0);
        if (MFABS(s) < MEPSILON) {
            return quat_identity();             /* 数值不稳定，返回单位四元数 */
        }
        q.w = (m.m32 - m.m23) / s;             /* 计算实部 */
        q.x = MFLOAT_C(0.25) * s;                       /* 计算x分量 */
        q.y = (m.m12 + m.m21) / s;             /* 计算y分量 */
        q.z = (m.m13 + m.m31) / s;             /* 计算z分量 */
    } else if (m.m22 > m.m33) {
        s = MSQRT(MFLOAT_C(1.0) + m.m22 - m.m11 - m.m33) * MFLOAT_C(2.0);
        if (MFABS(s) < MEPSILON) {
            return quat_identity();             /* 数值不稳定，返回单位四元数 */
        }
        q.w = (m.m13 - m.m31) / s;             /* 计算实部 */
        q.x = (m.m12 + m.m21) / s;             /* 计算x分量 */
        q.y = MFLOAT_C(0.25) * s;                       /* 计算y分量 */
        q.z = (m.m23 + m.m32) / s;             /* 计算z分量 */
    } else {
        s = MSQRT(MFLOAT_C(1.0) + m.m33 - m.m11 - m.m22) * MFLOAT_C(2.0);
        if (MFABS(s) < MEPSILON) {
            return quat_identity();             /* 数值不稳定，返回单位四元数 */
        }
        q.w = (m.m21 - m.m12) / s;             /* 计算实部 */
        q.x = (m.m13 + m.m31) / s;             /* 计算x分量 */
        q.y = (m.m23 + m.m32) / s;             /* 计算y分量 */
        q.z = MFLOAT_C(0.25) * s;                       /* 计算z分量 */
    }
    
    return quat_normalize(q);                   /* 返回归一化后的四元数 */
}


/*!
 * @brief 将旋转矩阵转换为轴角表示
 * @param m 旋转矩阵
 * @return 返回对应的轴角表示
 * @note 从旋转矩阵中提取轴角表示
 */
axis_st rotation_m2a(mat3_st m)
{
    axis_st a;

    /* 旋转矩阵直接转为轴角的数学公式为： 
     * angle = acos((trace(R) - 1) / 2)
     * axis = (R32 - R23, R13 - R31, R21 - R12) / (2*sin(angle))
     * 但为了避免数值不稳定性，通常先将旋转矩阵转换为四元数，再从四元数提取轴角.
    */
    a.angle = safe_acos((m.m11 + m.m22 + m.m33 - MFLOAT_C(1.0)) * MFLOAT_C(0.5)); /* 计算旋转角度 */
    if (MFABS(a.angle) < MEPSILON) {
        return axis_zero();                                 /* 角度太小，返回零轴角 */
    }
    ftype_t k_2sin = MSIN(a.angle) * MFLOAT_C(2.0);          /* 计算2*sin(angle) */
    if (MFABS(k_2sin) < MEPSILON) {
        return axis_zero();                                 /* 避免除以零，返回零轴角 */
    }

    a.v3.x = (m.m32 - m.m23) / k_2sin;                      /* 计算轴向量的X分量 */
    a.v3.y = (m.m13 - m.m31) / k_2sin;                      /* 计算轴向量的Y分量 */
    a.v3.z = (m.m21 - m.m12) / k_2sin;                      /* 计算轴向量的Z分量 */
    a.v3 = vec3_unit(a.v3);                                 /* 归一化轴向量 */

    return (a);     /* 通过四元数转换为轴角 */
}


/*!
 * @brief 将四元数转换为欧拉旋转角
 * @param q 四元数
 * @return 返回对应的欧拉旋转角向量
 * @note 从四元数中提取欧拉角表示（使用默认旋转顺序）
 */
eula_st rotation_q2e(quat_st q)
{
    char *order = CFG_EULER_ORDER;              /* 使用默认旋转顺序 */
    return (rotation_q2e_order(q, order));      /* 调用带顺序参数的函数 */
}


/*!
 * @brief 将四元数转换为旋转矩阵
 * @param q 四元数
 * @return 返回对应的旋转矩阵
 * @note 将四元数转换为旋转矩阵表示
 */
mat3_st rotation_q2m(quat_st q)
{
    mat3_st m;

    q = quat_normalize(q);                      /* 归一化四元数确保数值稳定性 */
    
    /* 第一列 */
    m.m11 = MFLOAT_C(1.0) - MFLOAT_C(2.0) * (q.y * q.y + q.z * q.z);    /* 计算m11元素 */
    m.m21 = MFLOAT_C(2.0) * (q.x * q.y + q.z * q.w);          /* 计算m21元素 */
    m.m31 = MFLOAT_C(2.0) * (q.x * q.z - q.y * q.w);          /* 计算m31元素 */
    
    /* 第二列 */
    m.m12 = MFLOAT_C(2.0) * (q.x * q.y - q.z * q.w);          /* 计算m12元素 */
    m.m22 = MFLOAT_C(1.0) - MFLOAT_C(2.0) * (q.x * q.x + q.z * q.z);    /* 计算m22元素 */
    m.m32 = MFLOAT_C(2.0) * (q.y * q.z + q.x * q.w);          /* 计算m32元素 */
    
    /* 第三列 */
    m.m13 = MFLOAT_C(2.0) * (q.x * q.z + q.y * q.w);          /* 计算m13元素 */
    m.m23 = MFLOAT_C(2.0) * (q.y * q.z - q.x * q.w);          /* 计算m23元素 */
    m.m33 = MFLOAT_C(1.0) - MFLOAT_C(2.0) * (q.x * q.x + q.y * q.y);    /* 计算m33元素 */

    return (m);                                    /* 返回旋转矩阵 */
}


/*!
 * @brief 将四元数转换为轴角
 * @param q 四元数
 * @return 返回对应的轴角
 * @note 从四元数中提取轴角表示
 */
axis_st rotation_q2a(quat_st q)
{
    axis_st a;
    ftype_t angle;

    /* 完全归一化四元数 */
    q = quat_normalize(q);                         /* 确保四元数是单位四元数 */

    /* 计算旋转角度 */
    angle = MFLOAT_C(2.0) * MACOS(q.w);                       /* 从四元数实部计算角度 */
    /* 将角度限制在[-π, π]范围内 */
    angle = MREMAINDER(angle, MPI2);
    /* 处理小角度情况，避免除以零 */
    if (MFABS(angle) < MEPSILON) {
        return axis_zero();                        /* 角度太小，返回零轴角 */
    }
    a.angle = angle;                               /* 设置轴角的角度 */
    a.v3 = vec3_unit(q.v3);                        /* 归一化旋转轴向量 */

    return (a);                                    /* 返回轴角表示 */
}


/*!
 * @brief 将轴角转换为四元数
 * @param a 轴角表示
 * @return 返回对应的四元数
 * @note 将轴角转换为四元数表示
 */
quat_st rotation_a2q(axis_st a)
{
    quat_st q;

    /* 如果旋转矢量为零矢量，则返回单位四元数 */
    if (axis_is_zero(a)) {
        return quat_identity();                    /* 零旋转，返回单位四元数 */
    }

    /* 检查旋转角度是否为零，为零则返回单位四元数，同时避免除以零 */
    if (MFABS(a.angle) < MEPSILON) {
        return quat_identity();                    /* 零角度，返回单位四元数 */
    }

    q = quat_from_axis_angle(a.v3, a.angle);       /* 从轴角创建四元数 */

    return (q);                                    /* 返回四元数 */
}


/*!
 * @brief 将轴角转换为欧拉旋转角
 * @param a 轴角表示
 * @return 返回对应的欧拉旋转角向量
 * @note 将轴角转换为欧拉角表示（使用默认旋转顺序）
 */
eula_st rotation_a2e(axis_st a)
{
    return (rotation_q2e(rotation_a2q(a)));        /* 通过四元数转换为欧拉角 */
}


/*!
 * @brief 将轴角转换为旋转矩阵
 * @param a 轴角表示
 * @return 返回对应的旋转矩阵
 * @note 将轴角转换为旋转矩阵表示
 */
mat3_st rotation_a2m(axis_st a)
{
    /* a = (k, angle) k为旋转轴的单位向量，称之为欧拉轴，angle为旋转角度，称之为欧拉转角
     * 轴角直接转为旋转矩阵的数学公式为：罗德里格斯旋转公式
     * 形式1：R = I + sin(angle) * K + (1 - cos(angle)) * K^2
     * 形式2：R = cos(angle)*I  + (1 - cos(angle)) * (k ⊗ k^T) - sin(angle) * K
     * 其中 K 是旋转轴的反对称矩阵。 K^2 = k ⊗ k^T - I
     * K = [[  0, -kz,  ky],
     *      [ kz,   0, -kx],
     *      [-ky,  kx,   0]]
     * 但为了简化实现，通常先将轴角转换为四元数，再从四元数转换为旋转矩阵。m = (rotation_q2m(rotation_a2q(a)))
    */

    if (axis_is_zero(a)) {
        return  (mat3_identity());
    }

    mat3_st K = {
        .m11 = MFLOAT_C(0.0),    .m12 =       -a.v3.z,   .m13 =        a.v3.y,
        .m21 =        a.v3.z,    .m22 = MFLOAT_C(0.0),   .m23 =       -a.v3.x,
        .m31 =       -a.v3.y,    .m32 =        a.v3.x,   .m33 = MFLOAT_C(0.0)
    };
    ftype_t c = MCOS(a.angle);
    ftype_t s = MSIN(a.angle);

    mat3_st sinK = mat3_mul_f(K, s);
    mat3_st K2 = mat3_mul(K, K);
    mat3_st one_minus_cosK2 = mat3_mul_f(K2, MFLOAT_C(1.0) - c);

    mat3_st m = mat3_add(mat3_identity(), sinK);
    m = mat3_add(m, one_minus_cosK2);

    return (m);
}


/*!
 * @brief 从向量from旋转到向量to，返回旋转所需的欧拉角
 * @param to 目标向量
 * @param from 起始向量
 * @return 返回表示旋转的欧拉角向量
 * @note 计算将向量from旋转到向量to所需的欧拉角（使用默认旋转顺序）
 */
eula_st rotation_vv2e(vec3_st to, vec3_st from)
{
    return rotation_m2e(rotation_vv2m(to, from));  /* 通过旋转矩阵转换为欧拉角 */
}


/*!
 * @brief 从向量from旋转到向量to，返回旋转矩阵
 * @param to 目标向量
 * @param from 起始向量
 * @return 返回表示旋转的旋转矩阵
 * @note 计算将向量from旋转到向量to所需的旋转矩阵
 */
mat3_st rotation_vv2m(vec3_st to, vec3_st from)
{
    return rotation_q2m(rotation_vv2q(to, from));  /* 通过四元数转换为旋转矩阵 */
}


/*!
 * @brief 从向量from旋转到向量to，返回四元数
 * @param to 目标向量
 * @param from 起始向量
 * @return 返回表示旋转的四元数
 * @note 计算将向量from旋转到向量to所需的四元数
 */
quat_st rotation_vv2q(vec3_st to, vec3_st from)
{
    return quat_from_vv(from, to);                 /* 调用四元数从向量到向量函数 */
}


/*!
 * @brief 从向量from旋转到向量to，返回轴角表示
 * @param to 目标向量
 * @param from 起始向量
 * @return 返回表示旋转的轴角表示
 * @note 计算将向量from旋转到向量to所需的轴角
 */
axis_st rotation_vv2a(vec3_st to, vec3_st from)
{
    return axis_from_vv(from, to);                 /* 调用轴角从向量到向量函数 */
}


/*!
 * @brief 从四元数from状态旋转到四元数to状态，返回旋转量的四元数
 * @param to 目标四元数
 * @param from 起始四元数
 * @return 返回表示旋转的四元数
 * @note 计算从起始四元数到目标四元数的相对旋转四元数
 */
quat_st rotation_qq2q(quat_st to, quat_st from)
{
    quat_st q;
    quat_st from_inv = quat_inverse(from);         /* 计算起始四元数的逆 */
    q = quat_mul(to, from_inv);                    /* 计算相对旋转四元数 */
    return quat_normalize(q);                      /* 返回归一化后的相对旋转四元数 */
}


/*!
 * @brief 从旋转矩阵from状态旋转到旋转矩阵to状态，返回旋转量的旋转矩阵
 * @param to 目标旋转矩阵
 * @param from 起始旋转矩阵
 * @return 返回表示旋转的旋转矩阵
 * @note 计算从起始旋转矩阵到目标旋转矩阵的相对旋转矩阵
 */
mat3_st rotation_mm2m(mat3_st to, mat3_st from)
{
    /* to = R_relative × from */
    /* R_relative = to × from^(-1) = to × from^T */
    return (mat3_mul(to, mat3_transpose(from)));   /* 计算相对旋转矩阵 */
}


/*!
 * @brief 从欧拉角from状态旋转到欧拉角to状态，返回旋转量的欧拉角
 * @param to 目标欧拉角
 * @param from 起始欧拉角
 * @return 返回表示旋转的欧拉角
 * @note 计算从起始欧拉角到目标欧拉角的相对旋转欧拉角
 */
eula_st rotation_ee2e(eula_st to, eula_st from)
{
    mat3_st m = rotation_mm2m(rotation_e2m(to), rotation_e2m(from));    /* 计算相对旋转矩阵 */
    return (rotation_m2e(m));                      /* 转换为欧拉角 */
}


/*!
 * @brief 从轴角from状态旋转到轴角to状态，返回旋转量的轴角
 * @param to 目标轴角
 * @param from 起始轴角
 * @return 返回表示旋转的轴角
 * @note 计算从起始轴角到目标轴角的相对旋转轴角
 */
axis_st rotation_aa2a(axis_st to, axis_st from)
{
    quat_st q = rotation_qq2q(rotation_a2q(to), rotation_a2q(from));    /* 计算相对旋转四元数 */
    return (rotation_q2a(q));                      /* 转换为轴角 */
}


/*!
 * @brief 将欧拉旋转角通过欧拉旋转角旋转
 * @param e 原始欧拉旋转角
 * @param re 旋转操作的欧拉旋转角
 * @return 返回旋转后的新欧拉旋转角
 * @note 使用欧拉角对欧拉角进行旋转操作
 */
eula_st rotation_eRe(eula_st re, eula_st e)
{
    mat3_st m = mat3_mul(rotation_e2m(re), rotation_e2m(e));    /* 组合旋转矩阵 */

    return (rotation_m2e(m));                      /* 转换为欧拉角 */
}


/*!
 * @brief 将欧拉旋转角通过旋转矩阵旋转
 * @param e 原始欧拉旋转角
 * @param rm 旋转操作的旋转矩阵
 * @return 返回旋转后的新欧拉旋转角
 * @note 使用旋转矩阵对欧拉角进行旋转操作
 */
eula_st rotation_mRe(mat3_st rm, eula_st e)
{
    mat3_st m = mat3_mul(rm, rotation_e2m(e));     /* 组合旋转矩阵 */

    return (rotation_m2e(m));                      /* 转换为欧拉角 */
}


/*!
 * @brief 将欧拉旋转角通过四元数旋转
 * @param e 原始欧拉旋转角
 * @param rq 旋转操作的四元数
 * @return 返回旋转后的新欧拉旋转角
 * @note 使用四元数对欧拉角进行旋转操作
 */
eula_st rotation_qRe(quat_st rq, eula_st e)
{
    quat_st q = quat_mul(rq, rotation_e2q(e));     /* 组合四元数 */

    return (rotation_q2e(q));                      /* 转换为欧拉角 */
}


/*!
 * @brief 将欧拉旋转角通过轴角旋转
 * @param e 原始欧拉旋转角
 * @param a 旋转操作的轴角
 * @return 返回旋转后的新欧拉旋转角
 * @note 使用轴角对欧拉角进行旋转操作
 */
eula_st rotation_aRe(axis_st a, eula_st e)
{
    quat_st q = quat_mul(rotation_a2q(a), rotation_e2q(e));     /* 组合四元数 */

    return (rotation_q2e(q));                      /* 转换为欧拉角 */
}


/*!
 * @brief 将旋转矩阵通过欧拉旋转角旋转
 * @param m 原始旋转矩阵
 * @param e 旋转操作的欧拉旋转角
 * @return 返回旋转后的新旋转矩阵
 * @note 使用欧拉角对旋转矩阵进行旋转操作
 */
mat3_st rotation_eRm(eula_st e, mat3_st m)
{
    return (mat3_mul(rotation_e2m(e), m));         /* 组合旋转矩阵 */
}


/*!
 * @brief 将旋转矩阵通过旋转矩阵旋转
 * @param m 原始旋转矩阵
 * @param rm 旋转操作的旋转矩阵
 * @return 返回旋转后的新旋转矩阵
 * @note 使用旋转矩阵对旋转矩阵进行旋转操作
 */
mat3_st rotation_mRm(mat3_st rm, mat3_st m)
{
    return (mat3_mul(rm, m));                      /* 组合旋转矩阵 */
}


/*!
 * @brief 将旋转矩阵通过四元数旋转
 * @param m 原始旋转矩阵
 * @param rq 旋转操作的四元数
 * @return 返回旋转后的新旋转矩阵
 * @note 使用四元数对旋转矩阵进行旋转操作
 */
mat3_st rotation_qRm(quat_st rq, mat3_st m)
{
    return (mat3_mul(rotation_q2m(rq), m));        /* 组合旋转矩阵 */
}


/*!
 * @brief 将旋转矩阵通过轴角旋转
 * @param m 原始旋转矩阵
 * @param a 旋转操作的轴角
 * @return 返回旋转后的新旋转矩阵
 * @note 使用轴角对旋转矩阵进行旋转操作
 */
mat3_st rotation_aRm(axis_st a, mat3_st m)
{
    return (mat3_mul(rotation_a2m(a), m));         /* 组合旋转矩阵 */
}


/*!
 * @brief 将四元数通过欧拉旋转角旋转
 * @param q 原始四元数
 * @param e 旋转操作的欧拉旋转角
 * @return 返回旋转后的新四元数
 * @note 使用欧拉角对四元数进行旋转操作
 */
quat_st rotation_eRq(eula_st e, quat_st q)
{
    quat_st tq = quat_mul(rotation_e2q(e), q);     /* 组合四元数 */

    return (quat_normalize(tq));                   /* 返回归一化后的四元数 */
}


/*!
 * @brief 将四元数通过旋转矩阵旋转
 * @param q 原始四元数
 * @param rm 旋转操作的旋转矩阵
 * @return 返回旋转后的新四元数
 * @note 使用旋转矩阵对四元数进行旋转操作
 */
quat_st rotation_mRq(mat3_st rm, quat_st q)
{
    quat_st tq = quat_mul(rotation_m2q(rm), q);    /* 组合四元数 */

    return (quat_normalize(tq));                   /* 返回归一化后的四元数 */
}


/*!
 * @brief 将四元数通过四元数旋转
 * @param q 原始四元数
 * @param rq 旋转操作的四元数
 * @return 返回旋转后的新四元数
 * @note 使用四元数对四元数进行旋转操作
 */
quat_st rotation_qRq(quat_st rq, quat_st q)
{
    quat_st tq = quat_mul(rq, q);                  /* 组合四元数 */

    return (quat_normalize(tq));                   /* 返回归一化后的四元数 */
}


/*!
 * @brief 将四元数通过轴角旋转
 * @param q 原始四元数
 * @param a 旋转操作的轴角
 * @return 返回旋转后的新四元数
 * @note 使用轴角对四元数进行旋转操作
 */
quat_st rotation_aRq(axis_st a, quat_st q)
{
    quat_st tq = quat_mul(rotation_a2q(a), q);     /* 组合四元数 */

    return (quat_normalize(tq));                   /* 返回归一化后的四元数 */
}


/*!
 * @brief 将轴角通过轴角旋转
 * @param a 原始轴角
 * @param ra 旋转操作的轴角
 * @return 返回旋转后的新轴角
 * @note 使用轴角对轴角进行旋转操作
 */
axis_st rotation_aRa(axis_st ra, axis_st a)
{
    quat_st tq = quat_mul(rotation_a2q(ra), rotation_a2q(a));   /* 组合四元数 */

    return (rotation_q2a(quat_normalize(tq)));     /* 转换为轴角 */
}


/*!
 * @brief 将轴角通过四元数旋转
 * @param a 原始轴角
 * @param q 旋转操作的四元数
 * @return 返回旋转后的新轴角
 * @note 使用四元数对轴角进行旋转操作
 */
axis_st rotation_qRa(quat_st q, axis_st a)
{
    quat_st tq = quat_mul(q, rotation_a2q(a));     /* 组合四元数 */

    return (rotation_q2a(quat_normalize(tq)));     /* 转换为轴角 */
}


/*!
 * @brief 将轴角通过旋转矩阵旋转
 * @param a 原始轴角
 * @param m 旋转操作的旋转矩阵
 * @return 返回旋转后的新轴角
 * @note 使用旋转矩阵对轴角进行旋转操作
 */
axis_st rotation_mRa(mat3_st m, axis_st a)
{
    quat_st tq = quat_mul(rotation_m2q(m), rotation_a2q(a));    /* 组合四元数 */

    return (rotation_q2a(quat_normalize(tq)));     /* 转换为轴角 */
}


/*!
 * @brief 将轴角通过欧拉旋转角旋转
 * @param a 原始轴角
 * @param e 旋转操作的欧拉旋转角
 * @return 返回旋转后的新轴角
 * @note 使用欧拉角对轴角进行旋转操作
 */
axis_st rotation_eRa(eula_st e, axis_st a)
{
    quat_st tq = quat_mul(rotation_e2q(e), rotation_a2q(a));    /* 组合四元数 */

    return (rotation_q2a(quat_normalize(tq)));     /* 转换为轴角 */
}


/*!
 * @brief 将三维向量通过欧拉旋转角旋转
 * @param v 原始三维向量
 * @param e 旋转操作的欧拉旋转角
 * @return 返回旋转后的新三维向量
 * @note 使用欧拉角对三维向量进行旋转操作
 */
vec3_st rotation_eRv(eula_st e, vec3_st v)
{
    return (mat3_mul_vec(rotation_e2m(e), v));     /* 通过旋转矩阵旋转向量 */
}


/*!
 * @brief 将三维向量通过旋转矩阵旋转
 * @param v 原始三维向量
 * @param m 旋转操作的旋转矩阵
 * @return 返回旋转后的新三维向量
 * @note 使用旋转矩阵对三维向量进行旋转操作
 */
vec3_st rotation_mRv(mat3_st m, vec3_st v)
{
    return (mat3_mul_vec(m, v));                   /* 通过旋转矩阵旋转向量 */
}


/*!
 * @brief 将三维向量通过四元数旋转
 * @param v 原始三维向量
 * @param q 旋转操作的四元数
 * @return 返回旋转后的新三维向量
 * @note 使用四元数对三维向量进行旋转操作
 */
vec3_st rotation_qRv(quat_st q, vec3_st v)
{
    return (quat_rotate_vec3_components(q, v));    /* 通过四元数旋转向量 */
}


/*!
 * @brief 将三维向量通过轴角旋转
 * @param v 原始三维向量
 * @param a 旋转操作的轴角
 * @return 返回旋转后的新三维向量
 * @note 使用轴角对三维向量进行旋转操作
 */
vec3_st rotation_aRv(axis_st a, vec3_st v)
{
    return (quat_rotate_vec3_components(rotation_a2q(a), v));    /* 通过四元数旋转向量 */
}

/**********************************************************************************************************************
 * End of spacemath file
 *********************************************************************************************************************/
