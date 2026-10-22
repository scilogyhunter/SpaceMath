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
 * @file test_random.c
 * @brief 随机旋转运算测试文件
 * @author scilogyhunter
 * @date 2026.10.22
 * @version V0.1.3
 *
 * 本文件实现了三维旋转运算的随机单元测试，验证了旋转矩阵、四元数和轴角表示之间的转换及旋转效果。
 */

/*!
 * @defgroup test_random_modify 修改记录
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

/** @} */ /* end of group test_random_modify */

#include "test_main.h"
#include <math.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

//生成指定范围随机数
static  ftype_t random_ftype_range(ftype_t min, ftype_t max) {
    ftype_t scale = rand() / (ftype_t) RAND_MAX; // 生成0到1之间的随机数
    return min + scale * (max - min);           // 缩放到[min, max]范围内
}

//生成随机欧拉角,指定转序
static  eula_st random_eula_generate_order(char *order) {
    while (1) {
        //生成角度随机的旋转欧拉角对象
        ftype_t random_x = random_ftype_range(-MPI, MPI);
        ftype_t random_y = random_ftype_range(-MPI, MPI);
        ftype_t random_z = random_ftype_range(-MPI, MPI);
        eula_st random_eula = eula(random_x, random_y, random_z);

        /* 验证欧拉角是否有效 */
        if (eula_validate(random_eula, order) == false) {
            continue;
        }
        /* 避开欧拉角万向锁，即避免第二个旋转角接近±π/2 */
        ftype_t theta = random_eula.v[order[1]-'x'];
        if ((MPI_2 - MFABS(theta)) < 1e-2) {
            continue;
        }

        return  random_eula;
    }
    
    return  eula_zero();
}
//生成随机欧拉角
static  eula_st random_eula_generate(void) {
    return  random_eula_generate_order(CFG_EULER_ORDER);
}

//生成随机轴角
static  axis_st random_axis_generate(void) {
        while (1) {
        //生成角度随机的旋转欧拉角对象
        ftype_t random_x = random_ftype_range(-MPI, MPI);
        ftype_t random_y = random_ftype_range(-MPI, MPI);
        ftype_t random_z = random_ftype_range(-MPI, MPI);
        vec3_st random_v = vec3(random_x, random_y, random_z);

        ftype_t len = vec3_len(random_v);
        if (len < MEPSILON) {
            continue;
        }

        axis_st random_axis = axis_from_vector_angle(vec3_unit(random_v), random_ftype_range(-MPI, MPI));

        return  random_axis;
    }
    
    return  axis_zero();
}

static  quat_st random_quat_generate(void) {
    return  rotation_a2q(random_axis_generate());
}

static  mat3_st random_mat3_generate(void) {
    return  rotation_a2m(random_axis_generate());
}

static void print_aa(int i, axis_st a0, axis_st a1) {
    #if (CFG_FLOATWORD_BITSIZE == 128)
        printf("[%d] a0: (%.6Lf, %.6Lf, %.6Lf, %.6Lf) a1: (%.6Lf, %.6Lf, %.6Lf, %.6Lf)\n", i,
               a0.v3.x, a0.v3.y, a0.v3.z, a0.angle,  a1.v3.x, a1.v3.y, a1.v3.z, a1.angle);
    #else
        printf("[%d] a0: (%.6f, %.6f, %.6f, %.6f) a1: (%.6f, %.6f, %.6f, %.6f)\n", i,
               a0.v3.x, a0.v3.y, a0.v3.z, a0.angle,  a1.v3.x, a1.v3.y, a1.v3.z, a1.angle);
    #endif
}

static void print_ee(int i, eula_st e0, eula_st e1) {
    #if (CFG_FLOATWORD_BITSIZE == 128)
        printf("[%d] e0: (%.6Lf, %.6Lf, %.6Lf) e1: (%.6Lf, %.6Lf, %.6Lf)\n", i,
               e0.x, e0.y, e0.z,  e1.x, e1.y, e1.z);
    #else
        printf("[%d] e0: (%.6f, %.6f, %.6f) e1: (%.6f, %.6f, %.6f)\n", i,
               e0.x, e0.y, e0.z,  e1.x, e1.y, e1.z);
    #endif
}

static void print_qq(int i, quat_st q0, quat_st q1) {
    #if (CFG_FLOATWORD_BITSIZE == 128)
        printf("[%d] q0: (%.6Lf, %.6Lf, %.6Lf, %.6Lf) q1: (%.6Lf, %.6Lf, %.6Lf, %.6Lf)\n", i,
               q0.x, q0.y, q0.z, q0.w,  q1.x, q1.y, q1.z, q1.w);
    #else
        printf("[%d] q0: (%.6f, %.6f, %.6f, %.6f) q1: (%.6f, %.6f, %.6f, %.6f)\n", i,
               q0.x, q0.y, q0.z, q0.w,  q1.x, q1.y, q1.z, q1.w);
    #endif
}

static void print_mm(int i, mat3_st m0, mat3_st m1) {
    #if (CFG_FLOATWORD_BITSIZE == 128)
        printf("[%d] m0: (%.6Lf, %.6Lf, %.6Lf, %.6Lf, %.6Lf, %.6Lf, %.6Lf, %.6Lf, %.6Lf) m1: (%.6Lf, %.6Lf, %.6Lf, %.6Lf, %.6Lf, %.6Lf, %.6Lf, %.6Lf, %.6Lf)\n", i,
               m0.m11, m0.m12, m0.m13, m0.m21, m0.m22, m0.m23, m0.m31, m0.m32, m0.m33,
               m1.m11, m1.m12, m1.m13, m1.m21, m1.m22, m1.m23, m1.m31, m1.m32, m1.m33);
    #else
        printf("[%d] m0: (%.6f, %.6f, %.6f, %.6f, %.6f, %.6f, %.6f, %.6f, %.6f) m1: (%.6f, %.6f, %.6f, %.6f, %.6f, %.6f, %.6f, %.6f, %.6f)\n", i,
               m0.m11, m0.m12, m0.m13, m0.m21, m0.m22, m0.m23, m0.m31, m0.m32, m0.m33,
               m1.m11, m1.m12, m1.m13, m1.m21, m1.m22, m1.m23, m1.m31, m1.m32, m1.m33);
    #endif
}

//测试轴角-四元数转换
static  int test_random_aq(void) {

    int  fail_count = 0;

    for (int i = 0; i < 1024; i++) {
        axis_st a = random_axis_generate();
        quat_st q = rotation_a2q(a);
        axis_st converted_a = rotation_q2a(q);
        if (!axis_equal(a, converted_a, TEST_EPSILON)) {
            if (g_verbose_mode) {
                print_aa(i, a, converted_a);
            }
            fail_count++;
        }
    }

    return  ((fail_count > 0) ? -1 : 0);
}
//测试旋转矩阵-四元数转换
static  int test_random_mq(void) {

    int  fail_count = 0;

    for (int i = 0; i < 1024; i++) {
        mat3_st m = random_mat3_generate();
        quat_st q = rotation_m2q(m);
        mat3_st converted_m = rotation_a2m(rotation_q2a(q));
        quat_st converted_q = rotation_m2q(converted_m);
        if (!quat_equal(q, converted_q, TEST_EPSILON)) {
            if (g_verbose_mode) {
                print_qq(i, q, converted_q);
            }
            fail_count++;
        }
    }

    return  ((fail_count > 0) ? -1 : 0);
}

//测试轴角-旋转矩阵转换
static  int test_random_am(void) {

    int  fail_count = 0;

    for (int i = 0; i < 1024; i++) {
        axis_st a = random_axis_generate();
        mat3_st m = rotation_a2m(a);
        axis_st converted_a = rotation_m2a(m);
        if (!axis_equal(a, converted_a, TEST_EPSILON)) {
            if (g_verbose_mode) {
                print_aa(i, a, converted_a);
            }
            fail_count++;
        }
    }

    return  ((fail_count > 0) ? -1 : 0);
}

//测试欧拉角-旋转矩阵转换
static  int test_random_em(void) {

    int  fail_count = 0;

    for (int i = 0; i < 1024; i++) {
        eula_st e = random_eula_generate();
        mat3_st m = rotation_e2m(e);
        eula_st converted_e = rotation_m2e(m);
        mat3_st converted_m = rotation_e2m(converted_e);
        if (!mat3_equal(m, converted_m, TEST_EPSILON)) {
            if (g_verbose_mode) {
                print_ee(i, e, converted_e);
                print_mm(i, m, converted_m);
            }
            fail_count++;
        }
    }

    return  ((fail_count > 0) ? -1 : 0);
}

//测试欧拉角-四元数转换
static  int test_random_eq(void) {

    int  fail_count = 0;

    for (int i = 0; i < 1024; i++) {
        quat_st q = random_quat_generate();
        eula_st e = rotation_q2e(q);
        quat_st converted_q = rotation_e2q(e);
        if (!quat_equal(q, converted_q, TEST_EPSILON)) {
            if (g_verbose_mode) {
                print_qq(i, q, converted_q);
            }
            fail_count++;
        }
    }

    return  ((fail_count > 0) ? -1 : 0);
}

//测试欧拉角-轴角转换
static  int test_random_ea(void) {

    int  fail_count = 0;

    for (int i = 0; i < 1024; i++) {
        axis_st a = random_axis_generate();
        eula_st e = rotation_a2e(a);
        axis_st converted_a = rotation_e2a(e);
        if (!axis_equal(a, converted_a, TEST_EPSILON)) {
            if (g_verbose_mode) {
                print_ee(i, e, e);
                print_aa(i, a, converted_a);
            }
            fail_count++;
        }
    }

    return  ((fail_count > 0) ? -1 : 0);
}

//随机选择一个旋转轴，每次转0.1度，连续旋转7200次后应回到初始位置
static  int test_random_rotation1(void) {
    int  iFd = -1;
    int  u32IputLen = 0;
    char buf[1024];
    iFd = open("./out/rotation_data1.csv", O_CREAT | O_RDWR | O_TRUNC, 0666);
    if (iFd < 0) {
        return -1;
    }

    char  *title = "index,ex,ey,ez,ax,ay,az,aa,qx,qy,qz,qw,m11,m12,m13,m21,m22,m23,m31,m32,m33\n";
    write(iFd, title, strlen(title));

    // 随机选择一个旋转轴，每次转0.1度
    axis_st a = random_axis_generate();
    a.angle = 0;
    for (int i = 0; i < 7200; i++) {
        quat_st q = rotation_a2q(a);
        mat3_st m = rotation_a2m(a);
        eula_st e = rotation_a2e(a);

        u32IputLen = 0;
        u32IputLen += sprintf(buf + u32IputLen, "%04d, ", i);
        #if (CFG_FLOATWORD_BITSIZE == 128)
        u32IputLen += sprintf(buf + u32IputLen, "%.6Lf, %.6Lf, %.6Lf, ", e.x, e.y, e.z);
        u32IputLen += sprintf(buf + u32IputLen, "%.6Lf, %.6Lf, %.6Lf, %.6Lf, ", a.v3.x, a.v3.y, a.v3.z, a.angle);
        u32IputLen += sprintf(buf + u32IputLen, "%.6Lf, %.6Lf, %.6Lf, %.6Lf, ", q.x, q.y, q.z, q.w);
        u32IputLen += sprintf(buf + u32IputLen, "%.6Lf, %.6Lf, %.6Lf, %.6Lf, %.6Lf, %.6Lf, %.6Lf, %.6Lf, %.6Lf\n", 
                                                 m.m11, m.m12, m.m13, m.m21, m.m22, m.m23, m.m31, m.m32, m.m33);
        #else
        u32IputLen += sprintf(buf + u32IputLen, "%.6f, %.6f, %.6f, ", e.x, e.y, e.z);
        u32IputLen += sprintf(buf + u32IputLen, "%.6f, %.6f, %.6f, %.6f, ", a.v3.x, a.v3.y, a.v3.z, a.angle);
        u32IputLen += sprintf(buf + u32IputLen, "%.6f, %.6f, %.6f, %.6f, ", q.x, q.y, q.z, q.w);
        u32IputLen += sprintf(buf + u32IputLen, "%.6f, %.6f, %.6f, %.6f, %.6f, %.6f, %.6f, %.6f, %.6f\n", 
                                                 m.m11, m.m12, m.m13, m.m21, m.m22, m.m23, m.m31, m.m32, m.m33);
        #endif
        write(iFd, buf, u32IputLen);

        a.angle = MDEG2RAD *(0.1 * i);
    }

    close(iFd);

    return  (0);
}
//随机选择一个旋转轴，每次转0.1度，连续旋转7200次后应回到初始位置
static  int test_random_rotation2(void) {
    int  iFd = -1;
    int  u32IputLen = 0;
    char buf[1024];
    iFd = open("./out/rotation_data2.csv", O_CREAT | O_RDWR | O_TRUNC, 0666);
    if (iFd < 0) {
        return -1;
    }

    char  *title = "index,ex,ey,ez,ax,ay,az,aa,qx,qy,qz,qw,m11,m12,m13,m21,m22,m23,m31,m32,m33\n";
    write(iFd, title, strlen(title));

    // 随机选择一个旋转轴，每次转0.1度
    axis_st a_step = random_axis_generate();
    a_step.angle = MDEG2RAD *(0.1); // 每次旋转0.1度
    //转为四元数形式
    quat_st q_step = rotation_a2q(a_step);

    quat_st q = quat_identity();
    for (int i = 0; i < 7200; i++) {
        mat3_st m = rotation_q2m(q);
        eula_st e = rotation_q2e(q);
        axis_st a = rotation_q2a(q);

        u32IputLen = 0;
        u32IputLen += sprintf(buf + u32IputLen, "%04d, ", i);
        #if (CFG_FLOATWORD_BITSIZE == 128)
        u32IputLen += sprintf(buf + u32IputLen, "%.6Lf, %.6Lf, %.6Lf, ", e.x, e.y, e.z);
        u32IputLen += sprintf(buf + u32IputLen, "%.6Lf, %.6Lf, %.6Lf, %.6Lf, ", a.v3.x, a.v3.y, a.v3.z, a.angle);
        u32IputLen += sprintf(buf + u32IputLen, "%.6Lf, %.6Lf, %.6Lf, %.6Lf, ", q.x, q.y, q.z, q.w);
        u32IputLen += sprintf(buf + u32IputLen, "%.6Lf, %.6Lf, %.6Lf, %.6Lf, %.6Lf, %.6Lf, %.6Lf, %.6Lf, %.6Lf\n", 
                                                 m.m11, m.m12, m.m13, m.m21, m.m22, m.m23, m.m31, m.m32, m.m33);
        #else
        u32IputLen += sprintf(buf + u32IputLen, "%.6f, %.6f, %.6f, ", e.x, e.y, e.z);
        u32IputLen += sprintf(buf + u32IputLen, "%.6f, %.6f, %.6f, %.6f, ", a.v3.x, a.v3.y, a.v3.z, a.angle);
        u32IputLen += sprintf(buf + u32IputLen, "%.6f, %.6f, %.6f, %.6f, ", q.x, q.y, q.z, q.w);
        u32IputLen += sprintf(buf + u32IputLen, "%.6f, %.6f, %.6f, %.6f, %.6f, %.6f, %.6f, %.6f, %.6f\n", 
                                                 m.m11, m.m12, m.m13, m.m21, m.m22, m.m23, m.m31, m.m32, m.m33);
        #endif
        write(iFd, buf, u32IputLen);

        q = rotation_qRq(q_step, q);
    }

    close(iFd);

    return  (0);
}

//测试6种欧拉角-旋转矩阵数转换
static  int test_random_em6(void) {

    int  fail_count = 0;
    char *orders[6] = {"xyz", "xzy", "yzx", "yxz", "zxy", "zyx"};

    for (int j = 0; j < 1024; j++) {
        for (int i = 0; i < 6; i++) {
            eula_st e = random_eula_generate_order(orders[i]);
            mat3_st m = rotation_e2m_order(e, orders[i]);
            eula_st converted_e = rotation_m2e_order(m, orders[i]);
            mat3_st converted_m = rotation_e2m_order(converted_e, orders[i]);
            if (!mat3_equal(m, converted_m, TEST_EPSILON)) {
                if (g_verbose_mode) {
                    print_ee(i, e, converted_e);
                    print_mm(i, m, converted_m);
                }
                fail_count++;
            }
        }
    }

    return  ((fail_count > 0) ? -1 : 0);
}

//测试6种欧拉角-四元数转换
static  int test_random_eq6(void) {

    int  fail_count = 0;
    char *orders[6] = {"xyz", "xzy", "yzx", "yxz", "zxy", "zyx"};

    for (int j = 0; j < 1024; j++) {
        for (int i = 0; i < 6; i++) {
            eula_st e = random_eula_generate_order(orders[i]);
            quat_st q = rotation_e2q_order(e, orders[i]);
            eula_st converted_e = rotation_q2e_order(q, orders[i]);
            quat_st converted_q = rotation_e2q_order(converted_e, orders[i]);
            if (!quat_equal(q, converted_q, TEST_EPSILON)) {
                if (g_verbose_mode) {
                    print_ee(i, e, converted_e);
                    print_qq(i, q, converted_q);
                }
                fail_count++;
            }
        }
    }

    return  ((fail_count > 0) ? -1 : 0);
}

//测试6种欧拉角-旋转矩阵和四元数转换
static  int test_random_e2mq(void) {

    int  fail_count = 0;
    char *orders[6] = {"xyz", "xzy", "yzx", "yxz", "zxy", "zyx"};

    for (int j = 0; j < 1024; j++) {
        for (int i = 0; i < 6; i++) {
            eula_st e = random_eula_generate_order(orders[i]);
            mat3_st m = rotation_e2m_order(e, orders[i]);
            quat_st q = rotation_e2q_order(e, orders[i]);
            quat_st converted_q = rotation_m2q(m);

            if (!quat_equal(q, converted_q, TEST_EPSILON)) {
                if (g_verbose_mode) {
                    print_qq(i, q, converted_q);
                }
                fail_count++;
            }
        }
    }

    return  ((fail_count > 0) ? -1 : 0);
}

//测试6种旋转矩阵四元数-欧拉角转换
static  int test_random_mq2e(void) {

    int  fail_count = 0;
    char *orders[6] = {"xyz", "xzy", "yzx", "yxz", "zxy", "zyx"};

    for (int j = 0; j < 1024; j++) {
        for (int i = 0; i < 6; i++) {
            eula_st e = random_eula_generate_order(orders[i]);
            mat3_st m = rotation_e2m_order(e, orders[i]);
            quat_st q = rotation_e2q_order(e, orders[i]);
            eula_st e0 = rotation_m2e_order(m, orders[i]);
            eula_st e1 = rotation_q2e_order(q, orders[i]);

            if (!eula_equal(e0, e1, TEST_EPSILON)) {
                if (g_verbose_mode) {
                    print_ee(i, e, e0);
                    print_ee(i, e0, e1);
                }
                fail_count++;
            }
        }
    }

    return  ((fail_count > 0) ? -1 : 0);
}

// 随机旋转测试模块所有测试
int test_random_all(void) {
    
    // 初始化随机种子
    srand((unsigned int)time(NULL));

    test_print_result("test_random_aq", test_random_aq());
    test_print_result("test_random_mq", test_random_mq());
    test_print_result("test_random_am", test_random_am());
    test_print_result("test_random_em", test_random_em());
    test_print_result("test_random_eq", test_random_eq());
    test_print_result("test_random_ea", test_random_ea());
    test_print_result("test_random_rotation1", test_random_rotation1());
    test_print_result("test_random_rotation2", test_random_rotation2());

    test_print_result("test_random_em6", test_random_em6());
    test_print_result("test_random_eq6", test_random_eq6());
    test_print_result("test_random_e2mq", test_random_e2mq());
    test_print_result("test_random_mq2e", test_random_mq2e());

    return 0;
}

/**********************************************************************************************************************
 * End of spacemath file
 *********************************************************************************************************************/