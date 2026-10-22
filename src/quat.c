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
 * @file quat.c
 * @brief 四元数运算实现文件
 * @author scilogyhunter
 * @date 2026.10.22
 * @version V0.1.3
 *
 * 本文件实现了四元数的基本运算，包括创建、归一化、乘法、插值等操作。
 * 四元数用于表示三维空间中的旋转，具有避免万向节锁的优点。
 */

/*!
 * @defgroup quat_modify 修改记录
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

/** @} */ /* end of group quat_modify */

#include "spacemath.h"


/*!
 * @brief 创建一个四元数
 * @param x 四元数的x分量
 * @param y 四元数的y分量
 * @param z 四元数的z分量
 * @param w 四元数的w分量（实部）
 * @return 返回创建的四元数
 * @note 直接使用四个分量创建四元数
 */
quat_st quat(ftype_t x, ftype_t y, ftype_t z, ftype_t w)
{
    quat_st result;
    result.x = x;   /* 设置x分量 */
    result.y = y;   /* 设置y分量 */
    result.z = z;   /* 设置z分量 */
    result.w = w;   /* 设置w分量（实部） */
    return result;
}


/*!
 * @brief 通过v[4]数组对四元数赋值
 * @param v 输入数组，注意顺序为 x,y,z,w
 * @return 返回创建的四元数
 * @note 使用数组初始化四元数，数组索引0-3分别对应x,y,z,w分量
 */
quat_st quat_v(ftype_t v[4])
{
    if (v == NULL) {
        quat_st q = quat(MFLOAT_C(0.0), MFLOAT_C(0.0), MFLOAT_C(0.0), MFLOAT_C(0.0));
        return  (q);
    }
    quat_st result;
    result.x = v[0];    /* 数组索引0对应x分量 */
    result.y = v[1];    /* 数组索引1对应y分量 */
    result.z = v[2];    /* 数组索引2对应z分量 */
    result.w = v[3];    /* 数组索引3对应w分量 */
    return result;
}


/*!
 * @brief 创建一个零四元数
 * @return 返回所有分量为0.0的四元数
 * @note 创建一个实部和虚部都为0的四元数
 */
quat_st quat_zero(void)
{
    quat_st result;
    result.x = MFLOAT_C(0.0);    /* x分量设为0 */
    result.y = MFLOAT_C(0.0);    /* y分量设为0 */
    result.z = MFLOAT_C(0.0);    /* z分量设为0 */
    result.w = MFLOAT_C(0.0);    /* w分量设为0 */
    return result;
}


/*!
 * @brief 创建一个单位四元数（无旋转）
 * @return 返回单位四元数 [0, 0, 0, 1]
 * @note 创建一个表示无旋转的单位四元数
 */
quat_st quat_null(void)
{
    quat_st result;
    result.x = MFLOAT_C(0.0);    /* x分量设为0 */
    result.y = MFLOAT_C(0.0);    /* y分量设为0 */
    result.z = MFLOAT_C(0.0);    /* z分量设为0 */
    result.w = MFLOAT_C(1.0);    /* w分量设为1，表示无旋转 */
    return result;
}


/*!
 * @brief 创建一个单位四元数（无旋转）
 * @return 返回单位四元数 [0, 0, 0, 1]
 * @note 创建一个表示无旋转的单位四元数，与quat_null功能相同
 */
quat_st quat_identity(void)
{
    quat_st result;
    result.x = MFLOAT_C(0.0);    /* x分量设为0 */
    result.y = MFLOAT_C(0.0);    /* y分量设为0 */
    result.z = MFLOAT_C(0.0);    /* z分量设为0 */
    result.w = MFLOAT_C(1.0);    /* w分量设为1，表示无旋转 */
    return result;
}


/*!
 * @brief 检查四元数是否为零四元数
 * @param q 要检查的四元数
 * @return 如果四元数的所有分量都接近零则返回true，否则返回false
 * @note 使用MEPSILON作为浮点数比较的容差
 */
bool quat_is_zero(quat_st q)
{
    /* 检查所有分量是否都在容差范围内接近零 */
    return MFABS(q.x) < MEPSILON && 
           MFABS(q.y) < MEPSILON && 
           MFABS(q.z) < MEPSILON && 
           MFABS(q.w) < MEPSILON;
}


/*!
 * @brief 检查两个四元数是否相等
 * @param q0 第一个四元数
 * @param q1 第二个四元数
 * @return 如果两个四元数的所有分量都接近相等则返回true，否则返回false
 * @note 使用MEPSILON作为浮点数比较的容差
 */
bool quat_is_equal(quat_st q0, quat_st q1)
{
    /* 检查对应分量的差值是否都在容差范围内 */
    return MFABS(q0.x - q1.x) < MEPSILON && 
           MFABS(q0.y - q1.y) < MEPSILON && 
           MFABS(q0.z - q1.z) < MEPSILON && 
           MFABS(q0.w - q1.w) < MEPSILON;
}

/*!
 * @brief 检查两个四元数是否相等（使用指定容差）
 * @param q0 第一个四元数
 * @param q1 第二个四元数
 * @param epsilon 浮点数比较的容差
 * @return 如果两个四元数的所有分量都接近相等则返回true，否则返回false
 * @note 使用指定的容差值进行比较
 */
bool quat_is_equal_eps(quat_st q0, quat_st q1, ftype_t epsilon)
{
    /* 检查对应分量的差值是否都在容差范围内 */
    return MFABS(q0.x - q1.x) < epsilon && 
           MFABS(q0.y - q1.y) < epsilon && 
           MFABS(q0.z - q1.z) < epsilon && 
           MFABS(q0.w - q1.w) < epsilon;
}

/*!
 * @brief 计算四元数的模长
 * @param q 输入的四元数
 * @return 返回四元数的模长
 * @note 计算四元数的欧几里得长度
 */
ftype_t quat_len(quat_st q)
{
    /* 计算四元数各分量平方和的平方根 */
    return MSQRT(q.x * q.x + q.y * q.y + q.z * q.z + q.w * q.w);
}


/*!
 * @brief 计算四元数模长的平方
 * @param q 输入的四元数
 * @return 返回四元数模长的平方
 * @note 避免开方运算，用于性能敏感的比较操作
 */
ftype_t quat_len_sq(quat_st q)
{
    /* 计算四元数各分量的平方和 */
    return  (q.x * q.x + q.y * q.y + q.z * q.z + q.w * q.w);
}


/*!
 * @brief 计算四元数的负四元数
 * @param q 输入的四元数
 * @return 返回负四元数（所有分量取反）
 * @note 对四元数的每个分量取负值
 */
quat_st quat_neg(quat_st q)
{
    quat_st result;
    result.x = -q.x;    /* x分量取反 */
    result.y = -q.y;    /* y分量取反 */
    result.z = -q.z;    /* z分量取反 */
    result.w = -q.w;    /* w分量取反 */
    return result;
}


/*!
 * @brief 计算四元数的共轭
 * @param q 输入的四元数
 * @return 返回共轭四元数
 * @note 将四元数的虚部取反，实部保持不变
 */
quat_st quat_conjugate(quat_st q)
{
    quat_st result;
    result.x = -q.x;    /* 虚部x分量取反 */
    result.y = -q.y;    /* 虚部y分量取反 */
    result.z = -q.z;    /* 虚部z分量取反 */
    result.w = q.w;     /* 实部保持不变 */
    return result;
}


/*!
 * @brief 计算四元数的逆
 * @param q 输入的四元数
 * @return 返回四元数的逆
 * @note 四元数的逆等于其共轭除以模长的平方
 */
quat_st quat_inverse(quat_st q)
{
    ftype_t length_sq = (q.x * q.x + q.y * q.y + q.z * q.z + q.w * q.w);
    
    /* 检查长度平方是否接近零 */
    if (length_sq < MEPSILON) {
        /* 返回单位四元数作为安全值 */
        return quat_identity();
    }
    
    ftype_t l = MFLOAT_C(1.0) / length_sq;
    quat_st result;
    result.x = -q.x * l;    /* 虚部取反并除以模长平方 */
    result.y = -q.y * l;    /* 虚部取反并除以模长平方 */
    result.z = -q.z * l;    /* 虚部取反并除以模长平方 */
    result.w = q.w * l;     /* 实部除以模长平方 */
    return result;
}


/*!
 * @brief 归一化四元数
 * @param q 输入的四元数
 * @return 返回归一化后的四元数
 * @note 将四元数除以其模长，使其成为单位四元数
 */
quat_st quat_normalize(quat_st q)
{
    ftype_t length = MSQRT(q.x * q.x + q.y * q.y + q.z * q.z + q.w * q.w);
    
    /* 检查长度是否接近零 */
    if (length < MEPSILON) {
        /* 返回单位四元数作为安全值 */
        return quat_identity();
    }
    
    ftype_t l = MFLOAT_C(1.0) / length;
    quat_st result;
    result.x = q.x * l;    /* x分量除以模长 */
    result.y = q.y * l;    /* y分量除以模长 */
    result.z = q.z * l;    /* z分量除以模长 */
    result.w = q.w * l;    /* w分量除以模长 */
    return result;
}

/*!
 * @brief 四元数加法
 * @param q0 第一个四元数
 * @param q1 第二个四元数
 * @return 返回两个四元数的和
 * @note 对应分量相加
 */
quat_st quat_add(quat_st q0, quat_st q1)
{
    quat_st result;
    result.x = q0.x + q1.x;    /* x分量相加 */
    result.y = q0.y + q1.y;    /* y分量相加 */
    result.z = q0.z + q1.z;    /* z分量相加 */
    result.w = q0.w + q1.w;    /* w分量相加 */
    return result;
}

/*!
 * @brief 四元数减法
 * @param q0 被减四元数
 * @param q1 减数四元数
 * @return 返回两个四元数的差
 * @note 对应分量相减
 */
quat_st quat_sub(quat_st q0, quat_st q1)
{
    quat_st result;
    result.x = q0.x - q1.x;    /* x分量相减 */
    result.y = q0.y - q1.y;    /* y分量相减 */
    result.z = q0.z - q1.z;    /* z分量相减 */
    result.w = q0.w - q1.w;    /* w分量相减 */
    return result;
}


/*!
 * @brief 四元数乘法
 * @param q0 第一个四元数
 * @param q1 第二个四元数
 * @return 返回两个四元数的乘积 q0 x q1
 * @note 执行标准的四元数乘法运算，用于旋转的组合
 */
quat_st quat_mul(quat_st q0, quat_st q1)
{
    quat_st result;
    /* 四元数乘法公式：result = q0 × q1 */
    result.x = q0.w * q1.x + q0.x * q1.w + q0.y * q1.z - q0.z * q1.y;
    result.y = q0.w * q1.y + q0.y * q1.w + q0.z * q1.x - q0.x * q1.z;
    result.z = q0.w * q1.z + q0.z * q1.w + q0.x * q1.y - q0.y * q1.x;
    result.w = q0.w * q1.w - q0.x * q1.x - q0.y * q1.y - q0.z * q1.z;
    return result;
}


/*!
 * @brief 四元数标量乘法
 * @param q 输入的四元数
 * @param f 标量乘数
 * @return 返回四元数与标量的乘积
 * @note 将四元数的每个分量乘以标量值
 */
quat_st quat_mul_f(quat_st q, ftype_t f)
{
    quat_st result;
    result.x = q.x * f;    /* x分量乘以标量 */
    result.y = q.y * f;    /* y分量乘以标量 */
    result.z = q.z * f;    /* z分量乘以标量 */
    result.w = q.w * f;    /* w分量乘以标量 */
    return result;
}


/*!
 * @brief 四元数除法
 * @param q0 被除四元数
 * @param q1 除数四元数
 * @return 返回四元数除法结果
 * @note 执行四元数除法运算，相当于乘以除数的逆
 */
quat_st quat_div(quat_st q0, quat_st q1)
{
    ftype_t x = q0.x;
    ftype_t y = q0.y;
    ftype_t z = q0.z;
    ftype_t w = q0.w;
    ftype_t ls = (q1.x * q1.x + q1.y * q1.y + q1.z * q1.z + q1.w * q1.w);
    
    /* 检查除数是否接近零 */
    if (ls < MEPSILON) {
        /* 返回零四元数作为安全值 */
        return quat_zero();
    }
    
    ftype_t normalized_x = -q1.x / ls;
    ftype_t normalized_y = -q1.y / ls;
    ftype_t normalized_z = -q1.z / ls;
    ftype_t normalized_w =  q1.w / ls;
    
    quat_st result;
    /* 四元数除法公式：q0 / q1 = q0 × q1⁻¹ */
    result.x = x * normalized_w + normalized_x * w + (y * normalized_z - z * normalized_y);
    result.y = y * normalized_w + normalized_y * w + (z * normalized_x - x * normalized_z);
    result.z = z * normalized_w + normalized_z * w + (x * normalized_y - y * normalized_x);
    result.w = w * normalized_w - (x * normalized_x + y * normalized_y + z * normalized_z);
    return result;
}


/*!
 * @brief 四元数标量除法
 * @param q 输入的四元数
 * @param f 标量除数
 * @return 返回四元数与标量的除法结果
 * @note 将四元数的每个分量除以标量值
 */
quat_st quat_div_f(quat_st q, ftype_t f)
{
    /* 检查除数是否接近零 */
    if (MFABS(f) < MEPSILON) {
        /* 返回零四元数作为安全值 */
        return quat_zero();
    }
    
    quat_st result;
    result.x = q.x / f;    /* x分量除以标量 */
    result.y = q.y / f;    /* y分量除以标量 */
    result.z = q.z / f;    /* z分量除以标量 */
    result.w = q.w / f;    /* w分量除以标量 */
    return result;
}


/*!
 * @brief 计算两个四元数的点积
 * @param q0 第一个四元数
 * @param q1 第二个四元数
 * @return 返回两个四元数的点积
 * @note 四元数点积类似于向量点积，但包含实部
 */
ftype_t quat_dot(quat_st q0, quat_st q1)
{
    /* 计算对应分量的乘积之和 */
    return (q0.x * q1.x + q0.y * q1.y + q0.z * q1.z + q0.w * q1.w);
}


/*!
 * @brief 保持新的四元数与旧四元数连续
 * @param q0 旧四元数
 * @param q1 新四元数
 * @return 保持连续性的新四元数
 * @note 四元数 q 和 -q 表示相同的旋转，但数值上完全不同。当旋转角度超过180度时，
 *       算法可能选择符号相反的四元数，造成曲线不连续。
 */
quat_st quat_continuous(quat_st q0, quat_st q1)
{
    /* 如果点积为负，说明两者相差180度，取反以保证连续性 */
    if (quat_dot(q0, q1) < MFLOAT_C(0.0)) {
        q1 = quat_neg(q1);
    }

    return q1;
}


/*!
 * @brief 计算四元数的幂
 * @param q 输入的四元数
 * @param exponent 指数
 * @return 返回四元数的幂
 * @note 用于四元数的指数运算，常用于插值计算
 */
quat_st quat_pow(quat_st q, ftype_t exponent)
{
    quat_st result;
    ftype_t v_len = vec3_len(q.v3);    /* 计算虚部模长 */

    /* 虚部模长为零（纯实数四元数，无旋转轴），幂运算无定义，原样返回 */
    if (v_len < MEPSILON) {
        result.x = q.x;
        result.y = q.y;
        result.z = q.z;
        result.w = q.w;
        return result;
    }

    /* 半角 alpha = θ/2 用 atan2(|v|, w) 而非 acos(w) 提取：
     * 对单位四元数两者数学上等价，但 acos 在 w→±1（θ→0 或 θ→2π）处斜率无穷大，
     * 浮点舍入会使角度坍缩、指数不再生效；atan2 双参数形式则在两端都稳定。 */
    ftype_t alpha = MATAN2(v_len, q.w);              /* 半角 */
    ftype_t new_alpha = alpha * exponent;            /* 缩放后的半角 */
    ftype_t s = MSIN(new_alpha) / MSIN(alpha);       /* 虚部缩放因子 */

    result.x = q.x * s;                  /* 缩放x分量 */
    result.y = q.y * s;                  /* 缩放y分量 */
    result.z = q.z * s;                  /* 缩放z分量 */
    result.w = MCOS(new_alpha);          /* 计算新的实部 */
    return result;
}


/*!
 * @brief 从轴角创建四元数
 * @param axis 旋转轴向量（需要是单位向量）
 * @param angle 旋转角度（弧度）
 * @return 返回表示旋转的四元数
 * @note 使用标准的轴角到四元数转换公式
 */
quat_st quat_from_axis_angle(vec3_st axis, ftype_t angle)
{
     /* 检查角度是否为0或2π的倍数 */
    ftype_t normalized_angle = MFMOD(angle, MPI2);
    if (MFABS(normalized_angle) < MEPSILON) {
        return (quat_identity());    /* 角度为0，返回单位四元数 */
    }
    
    const ftype_t length_sq = (axis.x * axis.x + axis.y * axis.y + axis.z * axis.z);
    
    /* 检查轴向量是否有效 */
    if (length_sq < MEPSILON) {
        return (quat_identity());    /* 轴向量无效，返回单位四元数 */
    }
    
    const ftype_t half_angle = normalized_angle * MFLOAT_C(0.5); /* 计算半角 */
    ftype_t s, c;
    
    /* 使用sincos函数如果可用，否则分别计算 */
    #if defined(HAVE_SINCOS)
        MSINCOS(half_angle, &s, &c);
    #else
        s = MSIN(half_angle);    /* 计算半角的正弦值 */
        c = MCOS(half_angle);    /* 计算半角的余弦值 */
    #endif
    
    /* 归一化轴向量 */
    const ftype_t inv_length = MFLOAT_C(1.0) / MSQRT(length_sq);
    
    quat_st result = {
        .x = axis.x * s * inv_length,    /* x分量：轴向量x * sin(θ/2) */
        .y = axis.y * s * inv_length,    /* y分量：轴向量y * sin(θ/2) */
        .z = axis.z * s * inv_length,    /* z分量：轴向量z * sin(θ/2) */
        .w = c                           /* w分量：cos(θ/2) */
    };
    
    /* 对结果四元数进行归一化，确保数值稳定性 */
    return  (quat_normalize(result));
}


/*!
 * @brief 从两个向量创建四元数
 * @param to 目标向量
 * @param from 起始向量
 * @return 返回将from旋转到to的四元数
 * @note 计算将向量from旋转到向量to所需的四元数，参数顺序统一为(to, from)
 */
quat_st quat_from_vv(vec3_st to, vec3_st from)
{
    vec3_st  cross;
    
    ftype_t d = vec3_dot(from, to);           /* 计算两个向量的点积 */
    ftype_t a_ls = vec3_len_sq(from);         /* 计算起始向量的长度平方 */
    ftype_t b_ls = vec3_len_sq(to);           /* 计算目标向量的长度平方 */
    cross = vec3_cross(from, to);             /* 计算两个向量的叉积 */
    
    /* 创建四元数：虚部为叉积，实部为点积加长度乘积 */
    quat_st result = quat(cross.x, cross.y, cross.z, d + MSQRT(a_ls * b_ls));

    /* 反向向量对（夹角180°）时叉积为零、实部为零，上述公式退化为零四元数，
     * 无法表示旋转。此时取与 from 垂直的任意轴，构造180°纯虚单位四元数。 */
    if ((a_ls > MEPSILON) && (b_ls > MEPSILON) && quat_is_zero(result)) {
        vec3_st f = vec3_unit(from);          /* 单位化起始向量 */
        vec3_st axis;
        ftype_t ax = MFABS(f.x);
        ftype_t ay = MFABS(f.y);
        ftype_t az = MFABS(f.z);

        /* 选择与 f 分量最小的坐标轴做叉积，保证结果轴向量非零 */
        if ((ax <= ay) && (ax <= az)) {
            axis = vec3_cross(f, vec3(MFLOAT_C(1.0), MFLOAT_C(0.0), MFLOAT_C(0.0)));
        } else if (ay <= az) {
            axis = vec3_cross(f, vec3(MFLOAT_C(0.0), MFLOAT_C(1.0), MFLOAT_C(0.0)));
        } else {
            axis = vec3_cross(f, vec3(MFLOAT_C(0.0), MFLOAT_C(0.0), MFLOAT_C(1.0)));
        }
        axis = vec3_unit(axis);
        return quat(axis.x, axis.y, axis.z, MFLOAT_C(0.0));
    }

    return quat_normalize(result);             /* 返回归一化后的四元数 */
}


/*!
 * @brief 四元数线性插值
 * @param from 起始四元数
 * @param to 结束四元数
 * @param t 插值因子（0.0到1.0之间）
 * @return 返回插值后的四元数
 * @note 对两个四元数的每个分量进行线性插值
 * @warning 线性插值可能导致旋转速度不均匀
 */
quat_st quat_lerp(quat_st from, quat_st to, ftype_t t)
{
    quat_st result;
    result.x = from.x + (to.x - from.x) * t;    /* x分量线性插值 */
    result.y = from.y + (to.y - from.y) * t;    /* y分量线性插值 */
    result.z = from.z + (to.z - from.z) * t;    /* z分量线性插值 */
    result.w = from.w + (to.w - from.w) * t;    /* w分量线性插值 */
    return result;
}


/*!
 * @brief 四元数球面线性插值
 * @param from 起始四元数
 * @param to 结束四元数
 * @param t 插值因子（0.0到1.0之间）
 * @return 返回球面插值后的四元数
 * @note 在四元数球面上进行插值，保持恒定的角速度
 * @remark 这是最常用的四元数插值方法，用于平滑的旋转动画
 */
quat_st quat_slerp(quat_st from, quat_st to, ftype_t t)
{
    quat_st tmp1 = to;
    quat_st result;
    ftype_t d = quat_dot(from, to);    /* 计算两个四元数的点积 */
    ftype_t f0;
    ftype_t f1;

    /* 如果点积为负，取反以保证最短路径插值 */
    if (d < MFLOAT_C(0.0)) {
        tmp1 = quat_neg(tmp1);
        d = -d;
    }
    
    /* 如果两个四元数非常接近，使用线性插值避免数值问题 */
    if (d > MFLOAT_C(0.9995)) {
        f0 = MFLOAT_C(1.0) - t;    /* 起始四元数权重 */
        f1 = t;                    /* 结束四元数权重 */
    } else {
        ftype_t theta = MACOS(d);                          /* 计算夹角 */
        ftype_t sin_theta = MSIN(theta);                   /* 计算夹角的正弦值 */
        f0 = MSIN((MFLOAT_C(1.0) - t) * theta) / sin_theta; /* 计算起始权重 */
        f1 = MSIN(t * theta) / sin_theta;                  /* 计算结束权重 */
    }
    
    /* 计算插值结果 */
    result.x = from.x * f0 + tmp1.x * f1;    /* x分量插值 */
    result.y = from.y * f0 + tmp1.y * f1;    /* y分量插值 */
    result.z = from.z * f0 + tmp1.z * f1;    /* z分量插值 */
    result.w = from.w * f0 + tmp1.w * f1;    /* w分量插值 */

    /* 归一化保证输出为单位四元数：d>0.9995 的线性近似分支结果模长通常不为1 */
    return quat_normalize(result);
}


/*!
 * @brief 计算四元数的旋转角（弧度）
 * @param q 四元数
 * @return 四元数的旋转角（弧度）
 * @note 计算四元数相对于其实姿态的最小旋转角
 */
ftype_t quat_angle(quat_st q)
{
    ftype_t angle;
    ftype_t v_len;

    /* 用 2*atan2(|v|, w) 而非 2*acos(w) 计算角度：acos 在自变量趋近 ±1 处斜率无穷大，
     * 浮点数上 w 会因舍入坍缩为 ±1，使小角度信息彻底丢失（返回 0）；
     * atan2 双参数形式在角度→0 和角度→2π 两端都数值稳定。 */
    v_len = vec3_len(q.v3);                      /* 计算虚部模长 */
    angle = MFLOAT_C(2.0) * MATAN2(v_len, q.w);  /* 由虚部模长与实部求旋转角 */
    /* 将角度限制在[-π, π]范围内 */
    angle = MREMAINDER(angle, MPI2);

    return (angle);
}


/*!
 * @brief 计算四元数的旋转轴向量
 * @param q 四元数
 * @return 四元数的旋转轴向量
 * @note 计算四元数的旋转轴向量（单位向量）
 */
vec3_st quat_axis(quat_st q)
{
    return (vec3_unit(q.v3));                                    /* 返回轴角表示 */
}
/*!
 * @brief 创建绕X轴旋转的四元数
 * @param angle 旋转角度（弧度）
 * @return 绕X轴旋转的四元数
 */
quat_st quat_rotation_x(ftype_t angle)
{
    quat_st q;
    ftype_t half_angle = angle * MFLOAT_C(0.5);    /* 计算半角 */
    q.w = MCOS(half_angle);               /* 实部：cos(θ/2) */
    q.x = MSIN(half_angle);               /* x分量：sin(θ/2) */
    q.y = MFLOAT_C(0.0);                  /* y分量为0 */
    q.z = MFLOAT_C(0.0);                  /* z分量为0 */
    return quat_normalize(q);
}


/*!
 * @brief 创建绕Y轴旋转的四元数
 * @param angle 旋转角度（弧度）
 * @return 绕Y轴旋转的四元数
 */
quat_st quat_rotation_y(ftype_t angle)
{
    quat_st q;
    ftype_t half_angle = angle * MFLOAT_C(0.5);    /* 计算半角 */
    q.w = MCOS(half_angle);               /* 实部：cos(θ/2) */
    q.x = MFLOAT_C(0.0);                  /* x分量为0 */
    q.y = MSIN(half_angle);               /* y分量：sin(θ/2) */
    q.z = MFLOAT_C(0.0);                  /* z分量为0 */
    return quat_normalize(q);
}


/*!
 * @brief 创建绕Z轴旋转的四元数
 * @param angle 旋转角度（弧度）
 * @return 绕Z轴旋转的四元数
 */
quat_st quat_rotation_z(ftype_t angle)
{
    quat_st q;
    ftype_t half_angle = angle * MFLOAT_C(0.5);    /* 计算半角 */
    q.w = MCOS(half_angle);               /* 实部：cos(θ/2) */
    q.x = MFLOAT_C(0.0);                  /* x分量为0 */
    q.y = MFLOAT_C(0.0);                  /* y分量为0 */
    q.z = MSIN(half_angle);               /* z分量：sin(θ/2) */
    return quat_normalize(q);
}


/*!
 * @brief 使用四元数旋转向量（标准方法）
 * @param q 旋转四元数（需要是单位四元数）
 * @param v 要旋转的三维向量
 * @return 旋转后的向量
 * @note 使用标准的四元数旋转公式，最直观但计算量最大（32次乘法和24次加法）
 */
vec3_st quat_rotate_vec3(quat_st q, vec3_st v) 
{
    /* 确保四元数是单位四元数 */
    q = quat_normalize(q);
    
    /* 将向量转换为纯四元数 */
    quat_st v_quat = {.x = v.x, .y = v.y, .z = v.z, .w = MFLOAT_C(0.0)};
    
    /* 计算四元数的共轭（对于单位四元数，共轭等于逆） */
    quat_st q_conj = {.x = -q.x, .y = -q.y, .z = -q.z, .w = q.w};
    
    /* 计算旋转：q × v × q⁻¹ */
    quat_st temp, result_quat;
    
    /* 第一步：q × v */
    temp = quat_mul(q, v_quat);

    /* 第二步：(q × v) × q⁻¹ */
    result_quat = quat_mul(temp, q_conj);

    /* 提取向量部分（实部应该为0或接近0） */
    vec3_st result = {.x = result_quat.x, .y = result_quat.y, .z = result_quat.z};

    return result;
}


/*!
 * @brief 使用四元数旋转向量（优化方法）
 * @param q 旋转四元数（需要是单位四元数）
 * @param v 要旋转的三维向量
 * @return 旋转后的向量
 * @note 使用优化公式，性能较好（21次乘法和18次加法）
 */
vec3_st quat_rotate_vec3_fast(quat_st q, vec3_st v)
{
    /* 确保四元数是单位四元数 */
    q = quat_normalize(q);
    
    /* 提取四元数的实部和虚部 */
    ftype_t s = q.w;
    vec3_st u = {.x = q.x, .y = q.y, .z = q.z};
    
    /* 使用优化公式：v' = v + 2u × (s v + u × v) */
    vec3_st u_cross_v = vec3_cross(u, v);                    /* u × v */
    vec3_st temp = vec3_add(vec3_mul_f(v, s), u_cross_v);    /* s v + u × v */
    vec3_st u_cross_temp = vec3_cross(u, temp);              /* u × (s v + u × v) */
    vec3_st result = vec3_add(v, vec3_mul_f(u_cross_temp, MFLOAT_C(2.0))); /* v + 2u × (s v + u × v) */
    
    return result;
}


/*!
 * @brief 使用四元数旋转向量（分量方法）
 * @param q 旋转四元数（需要是单位四元数）
 * @param v 要旋转的三维向量
 * @return 旋转后的向量
 * @note 使用分量公式，性能最好（18次乘法和12次加法）
 */
vec3_st quat_rotate_vec3_components(quat_st q, vec3_st v)
{
    /* 确保四元数是单位四元数 */
    q = quat_normalize(q);
    
    /* 提取四元数的实部和虚部 */
    ftype_t s = q.w;
    vec3_st u = {.x= q.x, .y = q.y, .z = q.z};
    
    /* 使用分量公式：v' = (s² - u·u)v + 2(u·v)u + 2s(u × v) */
    ftype_t s2 = s * s;                              /* s² */
    ftype_t u_dot_u = vec3_dot(u, u);                /* u·u */
    ftype_t u_dot_v = vec3_dot(u, v);                /* u·v */
    vec3_st u_cross_v = vec3_cross(u, v);            /* u × v */
    
    vec3_st term1 = vec3_mul_f(v, s2 - u_dot_u);     /* (s² - u·u)v */
    vec3_st term2 = vec3_mul_f(u, MFLOAT_C(2.0) * u_dot_v);   /* 2(u·v)u */
    vec3_st term3 = vec3_mul_f(u_cross_v, MFLOAT_C(2.0) * s); /* 2s(u × v) */
    
    vec3_st result = vec3_add(term1, vec3_add(term2, term3)); /* 合并三项 */
    return result;
}

/*!
 * @brief 计算四元数的微分(时间导数)
 * @param q 当前四元数
 * @param omega 角速度向量（单位：弧度/秒）
 * @return 返回四元数的时间导数
 * @note 四元数的时间导数用于描述旋转的变化率。omega使用本体下表示的角速度
 */
quat_st quat_derivative(quat_st q, vec3_st omega)
{
    quat_st omega_quat = {.v3 = omega, .s  = MFLOAT_C(0.0)};
    
    /* 计算四元数的时间导数：0.5 * q x omega_quat */
    quat_st q_dot = quat_mul(q, omega_quat);
    q_dot = quat_mul_f(q_dot, MFLOAT_C(0.5));
    
    return q_dot;
}

/*!
 * @brief 使用四元数的时间导数进行积分
 * @param q 当前四元数
 * @param q_dot 四元数的时间导数
 * @param dt 时间步长（秒）
 * @return 返回积分后的四元数
 * @note 通过积分四元数的时间导数，可以更新四元数以反映旋转随时间的变化
 */
quat_st quat_integrate(quat_st q, quat_st q_dot, ftype_t dt)
{
    /* 使用欧拉积分方法更新四元数 */
    quat_st q_new = quat_add(q, quat_mul_f(q_dot, dt));
    
    /* 归一化结果四元数以保持单位长度 */
    return quat_normalize(q_new);
}

/*!
 * @brief 根据角速度和时间步长积分四元数
 * @param q 当前四元数
 * @param w 角速度向量（单位：弧度/秒）
 * @param dt 时间步长（秒）
 * @return 返回积分后的四元数
 * @note 结合四元数的时间导数和积分步骤，更新四元数以反映旋转随时间的变化
 */
quat_st quat_integrate_w(quat_st q, vec3_st w, ftype_t dt)
{
    quat_st q_dot = quat_derivative(q, w);
    return quat_integrate(q, q_dot, dt);
}

/**********************************************************************************************************************
 * End of spacemath file
 *********************************************************************************************************************/
