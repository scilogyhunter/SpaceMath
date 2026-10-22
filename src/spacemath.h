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
 * @file spacemath.h
 * @brief 空间数学库头文件
 * @author scilogyhunter
 * @date 2026.10.22
 * @version V0.1.3
 *
 * 本文件定义了空间数学库的数据结构、常量和函数声明。
 * 提供了三维向量、旋转矩阵、四元数、欧拉角、旋转矢量和轴角等旋转表示的数据结构和操作函数。
 */

/*!
 * @defgroup spacemath_modify 修改记录
 * @{
 */

/*!
 * @brief 修改记录表
 * 
 * | 修改日期    | 修改人        | 版本号  | 修改内容                     |
 * |------------|---------------|---------|----------------------------|
 * | 2025.09.01 | scilogyhunter | V0.1.0  | 初始版本创建                |
 * | 2025.11.18 | scilogyhunter | V0.1.1  | 完善注释，使用doxygen格式   |
 * | 2025.12.28 | scilogyhunter | V0.1.2  | 补充API，调整参数顺序，去掉旋转向量，优化测试程序   |
 * | 2026.10.22 | scilogyhunter | V0.1.3  | 完善接口可靠性与数值稳定性   |
 */

/** @} */ /* end of group spacemath_modify */

#ifndef _SPACEMATH_H_
#define _SPACEMATH_H_

#include <stdbool.h>
#include <math.h>
#include <float.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*!
 * @defgroup spacemath_config 配置选项
 * spacemath 数学库配置项，仅可以修改此处两条宏来调整库的行为。不要修改其他内容。
 * CFG_FLOATWORD_BITSIZE用于配置浮点数的位数，支持32,64,128位三种类型。注意x86架构下128位浮点数实际只有80位精度，存储空间同样为16字节。
 * CFG_EULER_ORDER用于配置默认的欧拉角旋转顺序，通过字符串表示，有些必由小写xyz字母组成，长度固定为3字，从左向右来表示按哪个轴来旋转。
 * 共有6种有效旋转顺序：要求旋转的三个轴各不相同，包括"xyz","xzy","yxz","yzx","zxy","zyx"六种组合。
 * 航天上一般使用"zyx"转序；本库的默认转序由CFG_EULER_ORDER宏指定。如果需要其他默认转序，可以修改CFG_EULER_ORDER宏。
 * 如果是临时使用非默认转序，可以使用rotation_e2m_order和rotation_m2e_order两个函数来实现，直接指定所需转序。
 * @{
 */
#define CFG_FLOATWORD_BITSIZE      (64)             /*!< 浮点数字长配置，支持32,64,128位 */
#define CFG_EULER_ORDER            "yxz"            /*!< 默认欧拉角旋转顺序              */
/** @} */ /* end of group spacemath_config */

/*!
 * @defgroup spacemath_constants 常量定义
 * @{
 */

#if (CFG_FLOATWORD_BITSIZE == 32)
typedef float       ftype_t;                        /*!< 单精度浮点数类型定义 */

#define MPI             (3.1415926536f)             /*!< 圆周率π的近似值 */
#define MPI2            (6.2831853072f)             /*!< 2π的近似值 */
#define MPI_2           (1.5707963268f)             /*!< π/2的近似值 */
#define MPI_4           (0.7853981634f)             /*!< π/4的近似值 */
#define M1_PI           (0.3183098862f)             /*!< 1/π的近似值 */
#define M2_PI           (0.6366197724f)             /*!< 2/π的近似值 */
#define M2_SQRTPI       (1.1283791671f)             /*!< 2/√π的近似值 */
#define ME              (2.7182818285f)             /*!< 自然对数e的近似值 */
#define MLOG2E          (1.4426950409f)             /*!< log2(e)的近似值 */
#define MLOG10E         (0.4342944819f)             /*!< log10(e)的近似值 */
#define MLN2            (0.6931471806f)             /*!< ln(2)的近似值 */
#define MLN10           (2.3025850930f)             /*!< ln(10)的近似值 */
#define MSQRT2          (1.4142135624f)             /*!< √2的近似值 */
#define MSQRT1_2        (0.7071067812f)             /*!< 1/√2的近似值 */
#define MEPSILON        (FLT_EPSILON)               /*!< 浮点数精度容差 */
#define MRAD2DEG        (180.0f / MPI)              /*!< 弧度转角度系数 */
#define MDEG2RAD        (MPI / 180.0f)              /*!< 角度转弧度系数 */
#define MFLOAT_C(c)     (c ## f)                    /*!< 浮点数常量宏 */

#define MFABS           fabsf                       /*!< 绝对值函数 */
#define MFMIN           fminf                       /*!< 最小值函数 */
#define MFMAX           fmaxf                       /*!< 最大值函数 */
#define MSQRT           sqrtf                       /*!< 平方根函数 */
#define MSIN            sinf                        /*!< 正弦函数 */
#define MCOS            cosf                        /*!< 余弦函数 */
#define MACOS           acosf                       /*!< 反余弦函数 */  
#define MASIN           asinf                       /*!< 反正弦函数 */
#define MTAN            tanf                        /*!< 正切函数 */
#define MATAN           atanf                       /*!< 反正切函数 */
#define MATAN2          atan2f                      /*!< 反正切函数 */
#if defined(HAVE_SINCOS) && defined(__USE_GNU)
#define MSINCOS         sincosf                     /*!< 同时计算正弦和余弦（glibc扩展） */
#else
#define MSINCOS(a, ps, pc)  ((*(ps) = MSIN(a)), (*(pc) = MCOS(a)))    /*!< 同时计算正弦和余弦（便携回退） */
#endif
#define MPOW            powf                        /*!< 幂函数 */
#define MFLOOR          floorf                      /*!< 向下取整函数 */
#define MCEIL           ceilf                       /*!< 向上取整函数 */
#define MROUND          roundf                      /*!< 四舍五入函数 */
#define MTRUNC          truncf                      /*!< 截断函数 */
#define MFMOD           fmodf                       /*!< 取模函数 */
#define MCOPYSIGN       copysignf                   /*!< 符号函数 */
#define MREMAINDER      remainderf                  /*!< 余数函数 */
#define MCOPYSIGN       copysignf                   /*!< 符号函数 */
#endif

#if (CFG_FLOATWORD_BITSIZE == 64)
typedef double          ftype_t;                    /*!< 双精度浮点数类型定义 */

#define MPI             (3.14159265358979323846)    /*!< 圆周率π的近似值 */
#define MPI2            (6.28318530717958647692)    /*!< 2π的近似值 */
#define MPI_2           (1.57079632679489661923)    /*!< π/2的近似值 */
#define MPI_4           (0.78539816339744830962)    /*!< π/4的近似值 */
#define M1_PI           (0.31830988618379067154)    /*!< 1/π的近似值 */
#define M2_PI           (0.63661977236758134308)    /*!< 2/π的近似值 */
#define M2_SQRTPI       (1.12837916709551257390)    /*!< 2/√π的近似值 */
#define ME              (2.71828182845904523536)    /*!< 自然对数e的近似值 */
#define MLOG2E          (1.44269504088896340735)    /*!< log2(e)的近似值 */
#define MLOG10E         (0.43429448190325182765)    /*!< log10(e)的近似值 */
#define MLN2            (0.69314718055994530941)    /*!< ln(2)的近似值 */
#define MLN10           (2.30258509299404568402)    /*!< ln(10)的近似值 */
#define MSQRT2          (1.41421356237309504880)    /*!< √2的近似值 */
#define MSQRT1_2        (0.70710678118654752440)    /*!< 1/√2的近似值 */
#define MEPSILON        (DBL_EPSILON)               /*!< 浮点数精度容差 */
#define MRAD2DEG        (180.0 / MPI)               /*!< 弧度转角度系数 */
#define MDEG2RAD        (MPI / 180.0)               /*!< 角度转弧度系数 */
#define MFLOAT_C(c)     (c)                         /*!< 浮点数常量宏 */

#define MFABS           fabs                        /*!< 绝对值函数 */
#define MFMIN           fmin                        /*!< 最小值函数 */
#define MFMAX           fmax                        /*!< 最大值函数 */
#define MSQRT           sqrt                        /*!< 平方根函数 */
#define MSIN            sin                         /*!< 正弦函数 */
#define MCOS            cos                         /*!< 余弦函数 */
#define MACOS           acos                        /*!< 反余弦函数 */
#define MASIN           asin                        /*!< 反正弦函数 */
#define MTAN            tan                         /*!< 正切函数 */
#define MATAN           atan                        /*!< 反正切函数 */
#define MATAN2          atan2                       /*!< 反正切函数 */
#if defined(HAVE_SINCOS) && defined(__USE_GNU)
#define MSINCOS         sincos                      /*!< 同时计算正弦和余弦（glibc扩展） */
#else
#define MSINCOS(a, ps, pc)  ((*(ps) = MSIN(a)), (*(pc) = MCOS(a)))    /*!< 同时计算正弦和余弦（便携回退） */
#endif
#define MPOW            pow                         /*!< 幂函数 */
#define MFLOOR          floor                       /*!< 向下取整函数 */
#define MCEIL           ceil                        /*!< 向上取整函数 */
#define MROUND          round                       /*!< 四舍五入函数 */
#define MTRUNC          trunc                       /*!< 截断函数 */
#define MFMOD           fmod                        /*!< 取模函数 */
#define MCOPYSIGN       copysign                    /*!< 符号函数 */
#define MREMAINDER      remainder                   /*!< 余数函数 */
#define MCOPYSIGN       copysign                    /*!< 符号函数 */
#endif

#if (CFG_FLOATWORD_BITSIZE == 128)
typedef long double          ftype_t;               /*!< 双精度浮点数类型定义 */

#define MPI             (3.14159265358979323846264338327950288419716939937510582097494459230781640628620899L)    /*!< 圆周率π的128位近似值 */
#define MPI2            (6.28318530717958647692528676655900576839433879875021164194988918461563281257241799L)    /*!< 2π的128位近似值 */
#define MPI_2           (1.57079632679489661923132169163975144209858469968755291048747229615390820314310449L)    /*!< π/2的128位近似值 */
#define MPI_4           (0.78539816339744830961566084581987572104929234984377645524373614807695410157155224L)    /*!< π/4的128位近似值 */
#define M1_PI           (0.31830988618379067153776752674502872406891929148091289749533468811779359526845307L)    /*!< 1/π的近似值 */
#define M2_PI           (0.63661977236758134307553505349005744813783858296182579499066937623558719053690614L)    /*!< 2/π的近似值 */
#define M2_SQRTPI       (1.12837916709551257389615890312154517168810125865799771368817144342128493688298504L)    /*!< 2/√π的近似值 */
#define ME              (2.71828182845904523536028747135266249775724709369995957496696762772407663035354759L)    /*!< 自然对数e的近似值 */
#define MLOG2E          (1.44269504088896340735992468100189213742664595415298593413544940692110921993432412L)    /*!< log2(e)的近似值 */
#define MLOG10E         (0.43429448190325182765112891891660508229439700580366656611445378316586464920887077L)    /*!< log10(e)的近似值 */
#define MLN2            (0.69314718055994530941723212145817656807550013436025525412068000949339362196969471L)    /*!< ln(2)的近似值 */
#define MLN10           (2.30258509299404568401799145468436420760110148862877297603332790096757260967735248L)    /*!< ln(10)的近似值 */
#define MSQRT2          (1.41421356237309504880168872420969807856967187537694807317667973799073247846210703L)    /*!< √2的近似值 */
#define MSQRT1_2        (0.70710678118654752440084436210484903928483593768847403658833986899536623923105351L)    /*!< 1/√2的近似值 */
#define MEPSILON        (LDBL_EPSILON)               /*!< 128位浮点数精度容差 */
#define MRAD2DEG        (180.0L / MPI)               /*!< 弧度转角度系数 */
#define MDEG2RAD        (MPI / 180.0L)               /*!< 角度转弧度系数 */
#define MFLOAT_C(c)     (c ## L)                     /*!< 128位浮点数常量宏 */

#define MFABS           fabsl                        /*!< 128位绝对值函数 */
#define MFMIN           fminl                        /*!< 128位最小值函数 */
#define MFMAX           fmaxl                        /*!< 128位最大值函数 */
#define MSQRT           sqrtl                        /*!< 128位平方根函数 */
#define MSIN            sinl                         /*!< 128位正弦函数 */
#define MCOS            cosl                         /*!< 128位余弦函数 */
#define MACOS           acosl                        /*!< 128位反余弦函数 */
#define MASIN           asinl                        /*!< 128位反正弦函数 */
#define MTAN            tanl                         /*!< 128位正切函数 */
#define MATAN           atanl                        /*!< 128位反正切函数 */
#define MATAN2          atan2l                      /*!< 128位反正切函数 */
#if defined(HAVE_SINCOS) && defined(__USE_GNU)
#define MSINCOS         sincosl                     /*!< 同时计算正弦和余弦（glibc扩展） */
#else
#define MSINCOS(a, ps, pc)  ((*(ps) = MSIN(a)), (*(pc) = MCOS(a)))    /*!< 同时计算正弦和余弦（便携回退） */
#endif
#define MPOW            powl                         /*!< 128位幂函数 */
#define MFLOOR          floorl                       /*!< 128位向下取整函数 */
#define MCEIL           ceill                        /*!< 128位向上取整函数 */
#define MROUND          roundl                       /*!< 128位四舍五入函数 */
#define MTRUNC          truncl                       /*!< 128位截断函数 */
#define MFMOD           fmodl                        /*!< 128位取模函数 */
#define MCOPYSIGN       copysignl                    /*!< 128位符号函数 */
#define MREMAINDER      remainderl                   /*!< 128位余数函数 */
#define MCOPYSIGN       copysignl                    /*!< 符号函数 */

/* 128位专用数学函数 */
#define MEXPL           expl                         /*!< 128位指数函数 */
#define MLOGL           logl                         /*!< 128位自然对数 */
#define MLOG10L         log10l                       /*!< 128位常用对数 */
#define MSINHL          sinhl                        /*!< 128位双曲正弦 */
#define MCOSHL          coshl                        /*!< 128位双曲余弦 */
#define MTANHL          tanhl                        /*!< 128位双曲正切 */
#define MHYPOTL         hypotl                       /*!< 128位欧几里得距离 */
#define MFMODL          fmodl                        /*!< 128位浮点取模 */
#define MFREXPL         frexpl                       /*!< 128位分解浮点数 */
#define MLDEXPL         ldexpl                       /*!< 128位组合浮点数 */
#endif
/** @} */ /* end of group spacemath_constants */

/*!
 * @defgroup spacemath_types 类型定义
 * @{
 */

/*!
 * @brief 三维向量结构体
 * 
 * 表示三维空间中的向量，支持多种访问方式。
 */
typedef struct {
    union {
        struct {
            ftype_t x;    /*!< 三维向量X轴分量 */
            ftype_t y;    /*!< 三维向量Y轴分量 */
            ftype_t z;    /*!< 三维向量Z轴分量 */
        };
        ftype_t v[3];     /*!< 三维向量数组形式 */
    };
} vec3_st;

/*!
 * @brief 轴角结构体
 * 
 * 表示轴角旋转，包含旋转轴和旋转角度。
 */
typedef struct {
    union {
        struct {
            vec3_st v3;       /*!< 旋转轴单位向量 */
            ftype_t angle;    /*!< 旋转角度 */
        };
        ftype_t v[4];         /*!< 轴角数组形式 */
    };
} axis_st;

/*!
 * @brief 欧拉角结构体
 * 
 * 表示欧拉角旋转，支持多种命名约定。
 */
typedef struct {
    union {
        struct {
            ftype_t x;    /*!< 绕X轴旋转角度 */
            ftype_t y;    /*!< 绕Y轴旋转角度 */
            ftype_t z;    /*!< 绕Z轴旋转角度 */
        };
        struct {
            ftype_t roll;   /*!< 滚转角，绕X轴旋转角度 */
            ftype_t pitch;  /*!< 俯仰角，绕Y轴旋转角度 */
            ftype_t yaw;    /*!< 偏航角，绕Z轴旋转角度 */
        };
        ftype_t v[3];       /*!< 欧拉角数组形式 */
    };
} eula_st;


/*!
 * @brief 四元数结构体
 * 
 * 表示四元数旋转，包含向量部分和标量部分。
 */
typedef  struct {
    union {
        struct {
            ftype_t x;    /*!< 四元数i分量 */
            ftype_t y;    /*!< 四元数j分量 */
            ftype_t z;    /*!< 四元数k分量 */
            ftype_t w;    /*!< 四元数实部 */
        };
        struct {
            vec3_st v3;    /*!< 四元数向量部分 */
            ftype_t s;     /*!< 四元数标量部分 (scalar) */
        };
        ftype_t v[4];      /*!< 四元数数组形式 */
    };
} quat_st;

/*!
 * @brief 三阶方阵结构体
 * 
 * 表示三阶方阵，支持多种访问方式，采用列优先存储。
 * 
 * 注意：mat3_st是列优先定义，符合数学惯例，且计算时CPU的cache加速效果更好
 * 旋转矩阵数学中的布局：
 * [ m11 m12 m13 ] | [ v[0] v[3] v[6] ] | [ vv[0][0] vv[1][0] vv[2][0] ] | [ v3[0].x v3[1].x v3[2].x ]
 * [ m21 m22 m23 ] | [ v[1] v[4] v[7] ] | [ vv[0][1] vv[1][1] vv[2][1] ] | [ v3[0].y v3[1].y v3[2].y ]
 * [ m31 m32 m33 ] | [ v[2] v[5] v[8] ] | [ vv[0][2] vv[1][2] vv[2][2] ] | [ v3[0].z v3[1].z v3[2].z ]
 * 旋转矩阵内存中的布局：
 * [ m11      m21      m31      m12      m22      m32      m13      m23      m33 ]
 * [ v[0]     v[1]     v[2]     v[3]     v[4]     v[5]     v[6]     v[7]     v[8] ]
 * [ vv[0][0] vv[0][1] vv[0][2] vv[1][0] vv[1][1] vv[1][2] vv[2][0] vv[2][1] vv[2][2] ]
 * [ v3[0].x  v3[0].y  v3[0].z  v3[1].x  v3[1].y  v3[1].z  v3[2].x  v3[2].y  v3[2].z ]
 */
typedef  struct {
    union {
        struct {
            ftype_t m11;    /*!< 矩阵第1行第1列元素 */
            ftype_t m21;    /*!< 矩阵第2行第1列元素 */
            ftype_t m31;    /*!< 矩阵第3行第1列元素 */
            ftype_t m12;    /*!< 矩阵第1行第2列元素 */
            ftype_t m22;    /*!< 矩阵第2行第2列元素 */
            ftype_t m32;    /*!< 矩阵第3行第2列元素 */
            ftype_t m13;    /*!< 矩阵第1行第3列元素 */
            ftype_t m23;    /*!< 矩阵第2行第3列元素 */
            ftype_t m33;    /*!< 矩阵第3行第3列元素 */
        };
        ftype_t v[9];       /*!< 三阶方阵一维数组形式 */
        ftype_t vv[3][3];   /*!< 三阶方阵二维数组形式 */
        vec3_st v3[3];     /*!< 三阶方阵列向量数组形式 */
    };
} mat3_st;

/*!
 * 用于直接索引以上数据类型中数组元素
 */
enum {
    MINDEX_X = 0,
    MINDEX_Y = 1,
    MINDEX_Z = 2,
    MINDEX_W = 3,
    MINDEX_S = 3,
    MINDEX_ANGLE = 3,
    MINDEX_ROLL = 0,
    MINDEX_PITCH = 1,
    MINDEX_YAW = 2,
    MINDEX_M11 = 0,
    MINDEX_M21 = 1,
    MINDEX_M31 = 2,
    MINDEX_M12 = 3,
    MINDEX_M22 = 4,
    MINDEX_M32 = 5,
    MINDEX_M13 = 6,
    MINDEX_M23 = 7,
    MINDEX_M33 = 8
};

/** @} */ /* end of group spacemath_types */

/*!
 * 安全的反三角函数，用于辅助计算
 */
bool    safe_is_equal(ftype_t a, ftype_t b);
bool    safe_is_equal_eps(ftype_t a, ftype_t b, ftype_t epsilon);
bool    safe_is_zero(ftype_t a);
ftype_t safe_asin(ftype_t x);
ftype_t safe_acos(ftype_t x);
ftype_t safe_atan2(ftype_t y, ftype_t x);

/*!
 * 轴角相关函数
 */
bool    axis_is_zero(axis_st a);
bool    axis_is_zero_eps(axis_st axis, ftype_t epsilon);
bool    axis_is_equal(axis_st a, axis_st b);
bool    axis_is_equal_eps(axis_st a, axis_st b, ftype_t epsilon);
axis_st axis(ftype_t x, ftype_t y, ftype_t z, ftype_t angle);
axis_st axis_v(ftype_t v[4]);
axis_st axis_from_vector_angle(vec3_st v3, ftype_t a);
axis_st axis_from_vector_vector(vec3_st to, vec3_st from);
axis_st axis_zero(void);

/*!
 * 欧拉角相关函数
 */
bool    eula_validate(eula_st e, char  *order);
bool    eula_is_zero(eula_st e);
bool    eula_is_equal(eula_st a, eula_st b);
bool    eula_is_equal_eps(eula_st a, eula_st b, ftype_t epsilon);
eula_st eula(ftype_t x, ftype_t y, ftype_t z);
eula_st eula_v(ftype_t v[3]);
eula_st eula_zero(void);
eula_st eula_add(eula_st e0, eula_st e1);
eula_st eula_sub(eula_st e0, eula_st e1);
eula_st eula_deg2rad(eula_st deg);
eula_st eula_rad2deg(eula_st rad);
eula_st eula_remainder(eula_st e, ftype_t  range);

/*!
 * 三阶矩阵相关函数
 */
bool    mat3_is_zero(mat3_st m);
bool    mat3_is_one(mat3_st m);
bool    mat3_is_identity(mat3_st m); 
bool    mat3_is_symmetric(mat3_st m);
bool    mat3_is_orthogonal(mat3_st m);
bool    mat3_is_diagonal(mat3_st m);
bool    mat3_is_equal(mat3_st m0, mat3_st m1);
bool    mat3_is_equal_eps(mat3_st m0, mat3_st m1, ftype_t epsilon);
ftype_t mat3_det(mat3_st m);
ftype_t mat3_trace(mat3_st m);
ftype_t mat3_norm(mat3_st m, int norm_type);
ftype_t mat3_cond(mat3_st m);
vec3_st mat3_mul_vec(mat3_st m, vec3_st v);
mat3_st mat3(ftype_t m11, ftype_t m12, ftype_t m13, ftype_t m21, ftype_t m22, ftype_t m23, ftype_t m31, ftype_t m32, ftype_t m33);
mat3_st mat3_v(ftype_t v[9]);
mat3_st mat3_vv(ftype_t vv[3][3]);
mat3_st mat3_v3(vec3_st v3[3]);
mat3_st mat3_zero(void);
mat3_st mat3_one(void);
mat3_st mat3_identity(void);
mat3_st mat3_transpose(mat3_st m);
mat3_st mat3_inverse(mat3_st m);
mat3_st mat3_negate(mat3_st m);
mat3_st mat3_add(mat3_st m0, mat3_st m1);
mat3_st mat3_add_f(mat3_st m, ftype_t f);
mat3_st mat3_sub(mat3_st m0, mat3_st m1);
mat3_st mat3_sub_f(mat3_st m, ftype_t f);
mat3_st mat3_mul(mat3_st m0, mat3_st m1);
mat3_st mat3_mul_f(mat3_st m, ftype_t f);
mat3_st mat3_scale(mat3_st m, ftype_t scalar);
mat3_st mat3_scale_matrix(ftype_t sx, ftype_t sy, ftype_t sz);
mat3_st mat3_exp(mat3_st m);
mat3_st mat3_log(mat3_st m);
mat3_st mat3_pow(mat3_st m, ftype_t exponent);
mat3_st mat3_rotation_x(ftype_t f);
mat3_st mat3_rotation_y(ftype_t f);
mat3_st mat3_rotation_z(ftype_t f);
mat3_st mat3_lerp(mat3_st from, mat3_st to, ftype_t t);
mat3_st mat3_orthonormalization(mat3_st basis);

/*!
 * 三阶向量相关函数
 */
bool    vec3_is_zero(vec3_st v);
bool    vec3_is_zero_eps(vec3_st v, ftype_t epsilon);
bool    vec3_is_equal(vec3_st v0, vec3_st v1);
bool    vec3_is_equal_eps(vec3_st v0, vec3_st v1, ftype_t epsilon);
bool    vec3_is_linear_independent(vec3_st v0, vec3_st v1, vec3_st v2);
ftype_t vec3_dot(vec3_st v0, vec3_st v1);
ftype_t vec3_angle(vec3_st v0, vec3_st v1);
ftype_t vec3_len(vec3_st v);
ftype_t vec3_len_sq(vec3_st v);
ftype_t vec3_dist(vec3_st v0, vec3_st v1);
ftype_t vec3_dist_sq(vec3_st v0, vec3_st v1);
vec3_st vec3(ftype_t x, ftype_t y, ftype_t z);
vec3_st vec3_v(ftype_t v[3]);
vec3_st vec3_zero(void);
vec3_st vec3_one(void);
vec3_st vec3_sign(vec3_st v);
vec3_st vec3_add(vec3_st v0, vec3_st v1);
vec3_st vec3_add_f(vec3_st v, ftype_t f);
vec3_st vec3_sub(vec3_st v0, vec3_st v1);
vec3_st vec3_sub_f(vec3_st v, ftype_t f);
vec3_st vec3_mul(vec3_st v0, vec3_st v1);
vec3_st vec3_mul_f(vec3_st v, ftype_t f);
vec3_st vec3_div(vec3_st v0, vec3_st v1);
vec3_st vec3_div_f(vec3_st v, ftype_t f);
vec3_st vec3_snap(vec3_st v0, vec3_st v1);
vec3_st vec3_snap_f(vec3_st v, ftype_t f);
vec3_st vec3_wrapping_f(vec3_st v, ftype_t f);
vec3_st vec3_neg(vec3_st v);
vec3_st vec3_abs(vec3_st v);
vec3_st vec3_floor(vec3_st v);
vec3_st vec3_ceil(vec3_st v);
vec3_st vec3_round(vec3_st v);
vec3_st vec3_trunc(vec3_st v);
vec3_st vec3_max(vec3_st v0, vec3_st v1);
vec3_st vec3_min(vec3_st v0, vec3_st v1);
vec3_st vec3_clamp(vec3_st v, vec3_st min, vec3_st max);
vec3_st vec3_clamp_min_abs(vec3_st v, ftype_t min_abs);
vec3_st vec3_clamp_max_abs(vec3_st v, ftype_t max_abs);
vec3_st vec3_clamp_len(vec3_st v, ftype_t min, ftype_t max);
vec3_st vec3_cross(vec3_st v0, vec3_st v1);
vec3_st vec3_unit(vec3_st v);
vec3_st vec3_project(vec3_st v, vec3_st onto);
vec3_st vec3_slide(vec3_st v, vec3_st normal);
vec3_st vec3_reflect(vec3_st v, vec3_st normal);
vec3_st vec3_rotate(vec3_st v, vec3_st axis, ftype_t angle);
vec3_st vec3_lerp(vec3_st from, vec3_st to, ftype_t t);
vec3_st vec3_bezier3(vec3_st v0, vec3_st v1, vec3_st v2, ftype_t f);
vec3_st vec3_bezier4(vec3_st v0, vec3_st v1, vec3_st v2, vec3_st v3, ftype_t f);

/*!
 * 四元数相关函数
 */
bool    quat_is_zero(quat_st q);
bool    quat_is_equal(quat_st q0, quat_st q1);
bool    quat_is_equal_eps(quat_st q0, quat_st q1, ftype_t epsilon);
ftype_t quat_dot(quat_st q0, quat_st q1);
ftype_t quat_len(quat_st q);
ftype_t quat_len_sq(quat_st q);
ftype_t quat_angle(quat_st q);
vec3_st quat_axis(quat_st q);
vec3_st quat_rotate_vec3(quat_st q, vec3_st v);
vec3_st quat_rotate_vec3_fast(quat_st q, vec3_st v);
vec3_st quat_rotate_vec3_components(quat_st q, vec3_st v);
quat_st quat(ftype_t x, ftype_t y, ftype_t z, ftype_t w);
quat_st quat_v(ftype_t v[4]);
quat_st quat_zero(void);
quat_st quat_null(void);
quat_st quat_identity(void);
quat_st quat_add(quat_st q0, quat_st q1);
quat_st quat_sub(quat_st q0, quat_st q1);
quat_st quat_mul(quat_st q0, quat_st q1);
quat_st quat_mul_f(quat_st q, ftype_t f);
quat_st quat_div(quat_st q0, quat_st q1);
quat_st quat_div_f(quat_st q, ftype_t f);
quat_st quat_neg(quat_st q);
quat_st quat_conjugate(quat_st q);
quat_st quat_inverse(quat_st q);
quat_st quat_normalize(quat_st q);
quat_st quat_continuous(quat_st q0, quat_st q1);
quat_st quat_pow(quat_st q, ftype_t exponent);
quat_st quat_from_axis_angle(vec3_st axis, ftype_t angle);
quat_st quat_from_vv(vec3_st to, vec3_st from);
quat_st quat_lerp(quat_st from, quat_st to, ftype_t t);
quat_st quat_slerp(quat_st from, quat_st to, ftype_t t);
quat_st quat_rotation_x(ftype_t angle);
quat_st quat_rotation_y(ftype_t angle);
quat_st quat_rotation_z(ftype_t angle);
quat_st quat_derivative(quat_st q, vec3_st omega);
quat_st quat_integrate(quat_st q, quat_st q_dot, ftype_t dt);
quat_st quat_integrate_w(quat_st q, vec3_st w, ftype_t dt);
/*!
 * 旋转相关函数
 */
axis_st rotation_a_rvs(axis_st a);
axis_st rotation_a_rx(ftype_t angle);
axis_st rotation_a_ry(ftype_t angle);
axis_st rotation_a_rz(ftype_t angle);
eula_st rotation_e_rvs(eula_st e);
eula_st rotation_e_rx(ftype_t angle);
eula_st rotation_e_ry(ftype_t angle);
eula_st rotation_e_rz(ftype_t angle);
mat3_st rotation_m_rvs(mat3_st m);
mat3_st rotation_m_rx(ftype_t angle);
mat3_st rotation_m_ry(ftype_t angle);
mat3_st rotation_m_rz(ftype_t angle);
quat_st rotation_q_rvs(quat_st q);
quat_st rotation_q_rx(ftype_t angle);
quat_st rotation_q_ry(ftype_t angle);
quat_st rotation_q_rz(ftype_t angle);
mat3_st rotation_e2m_order(eula_st e, char *order);
eula_st rotation_m2e_order(mat3_st m, char *order);
quat_st rotation_e2q_order(eula_st e, char *order);
eula_st rotation_q2e_order(quat_st q, char *order);
eula_st rotation_a2e(axis_st a);
mat3_st rotation_a2m(axis_st a);
quat_st rotation_a2q(axis_st a);
axis_st rotation_e2a(eula_st e);
mat3_st rotation_e2m(eula_st e);
quat_st rotation_e2q(eula_st e);
axis_st rotation_m2a(mat3_st m);
eula_st rotation_m2e(mat3_st m);
quat_st rotation_m2q(mat3_st m);
axis_st rotation_q2a(quat_st q);
eula_st rotation_q2e(quat_st q);
mat3_st rotation_q2m(quat_st q);
axis_st rotation_vv2a(vec3_st to, vec3_st from);
eula_st rotation_vv2e(vec3_st to, vec3_st from);
mat3_st rotation_vv2m(vec3_st to, vec3_st from);
quat_st rotation_vv2q(vec3_st to, vec3_st from);
axis_st rotation_aa2a(axis_st to, axis_st from);
eula_st rotation_ee2e(eula_st to, eula_st from);
mat3_st rotation_mm2m(mat3_st to, mat3_st from);
quat_st rotation_qq2q(quat_st to, quat_st from);

/*!
 * 旋转操作函数
 */
axis_st rotation_aRa(axis_st ra, axis_st a);
axis_st rotation_eRa(eula_st re, axis_st a);
axis_st rotation_mRa(mat3_st rm, axis_st a);
axis_st rotation_qRa(quat_st rq, axis_st a);
eula_st rotation_aRe(axis_st ra, eula_st e);
eula_st rotation_eRe(eula_st re, eula_st e);
eula_st rotation_mRe(mat3_st rm, eula_st e);
eula_st rotation_qRe(quat_st rq, eula_st e);
mat3_st rotation_aRm(axis_st ra, mat3_st m);
mat3_st rotation_eRm(eula_st re, mat3_st m);
mat3_st rotation_mRm(mat3_st rm, mat3_st m);
mat3_st rotation_qRm(quat_st rq, mat3_st m);
quat_st rotation_aRq(axis_st ra, quat_st q);
quat_st rotation_eRq(eula_st re, quat_st q);
quat_st rotation_mRq(mat3_st rm, quat_st q);
quat_st rotation_qRq(quat_st rq, quat_st q);
vec3_st rotation_aRv(axis_st ra, vec3_st v);
vec3_st rotation_eRv(eula_st re, vec3_st v);
vec3_st rotation_mRv(mat3_st rm, vec3_st v);
vec3_st rotation_qRv(quat_st rq, vec3_st v);

#endif

/**********************************************************************************************************************
 * End of spacemath file
 *********************************************************************************************************************/
