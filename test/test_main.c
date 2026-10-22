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
 * @file test_main.c
 * @brief 测试主程序实现文件
 * @author scilogyhunter
 * @date 2026.10.22
 * @version V0.1.3
 *
 * 本文件实现了测试主程序，负责调用各个测试模块并汇总测试结果。
 */

/*!
 * @defgroup test_main_modify 修改记录
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

/** @} */ /* end of group test_main_modify */

#include "test_main.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include "../src/spacemath.h"
#if (CFG_FLOATWORD_BITSIZE == 128)
#include <quadmath.h>
#endif

// 声明各个模块的测试函数
int test_matrix_all(void);
int test_vector_all(void);
int test_quat_all(void);
int test_rotation_all(void);
int test_random_all(void);
int test_others_all(void);
int test_eula_all(void);
int test_axis_all(void);


// 全局变量定义
test_stats_t g_test_stats = {0, 0, 0};
bool g_verbose_mode = false; // 是否开启详细模式
bool g_print_eps = false; //是否开启误差值打印

//打印轴角
void print_axis(axis_st a) {
#if (CFG_FLOATWORD_BITSIZE == 128)
    printf("Axis: (%.6Lf, %.6Lf, %.6Lf), Angle: %.6Lf radians\n", a.v3.x, a.v3.y, a.v3.z, a.angle);
#else
    printf("Axis: (%.3f, %.3f, %.3f), Angle: %.3f radians\n", a.v3.x, a.v3.y, a.v3.z, a.angle);
#endif
}
//打印欧拉角
void print_eula(eula_st e) {
#if (CFG_FLOATWORD_BITSIZE == 128)
    printf("Eula: (%.6Lf, %.6Lf, %.6Lf) radians\n", e.x, e.y, e.z);
#else
    printf("Eula: (%.3f, %.3f, %.3f) radians\n", e.x, e.y, e.z);
#endif
}
// 打印向量
void print_vec3(vec3_st v) {
#if (CFG_FLOATWORD_BITSIZE == 128)
    printf("Vec3: (%.6Lf, %.6Lf, %.6Lf)\n", v.x, v.y, v.z);
#else
    printf("Vec3: (%.3f, %.3f, %.3f)\n", v.x, v.y, v.z);
#endif
}
// 打印矩阵
void print_mat3(mat3_st m) {
    printf("Mat3:\n");
    for (int i = 0; i < 3; i++) {
#if (CFG_FLOATWORD_BITSIZE == 128)
        printf("[%.6Lf %.6Lf %.6Lf]\n", m.vv[i][0], m.vv[i][1], m.vv[i][2]);
#else
        printf("[%.3f %.3f %.3f]\n", m.vv[i][0], m.vv[i][1], m.vv[i][2]);
#endif
    }
}
// 打印四元数
void print_quat(quat_st q) {
#if (CFG_FLOATWORD_BITSIZE == 128)
    printf("Quat: (%.6Lf, %.6Lf, %.6Lf, %.6Lf)\n", q.x, q.y, q.z, q.w);
#else
    printf("Quat: (%.3f, %.3f, %.3f, %.3f)\n", q.x, q.y, q.z, q.w);
#endif
}

// 打印测试结果
void test_print_result(const char* test_name, int result) {
    g_test_stats.total_tests++;
    
    if (result == 0) {
        g_test_stats.passed_tests++;
        if (g_verbose_mode) {
            printf("[\033[32mPASS\033[0m] %s\n", test_name);
        }
    } else {
        g_test_stats.failed_tests++;
        if (g_verbose_mode) {
            printf("[\033[31mFAIL\033[0m] %s\n", test_name);
        }
    }
}

// 打印最终统计
void test_print_summary(void) {
    printf("测试结果统计\n");
    printf("总测试项数: %d\n", g_test_stats.total_tests);
    printf("通过测试数: %d\n", g_test_stats.passed_tests);
    printf("失败测试数: %d\n", g_test_stats.failed_tests);
    printf("测试通过率: %.1f%%\n", 
           g_test_stats.total_tests > 0 ? 
           (float)g_test_stats.passed_tests / g_test_stats.total_tests * 100.0f : 0.0f);
    
    if (g_test_stats.failed_tests == 0) {
        printf("所有测试通过！\n");
    } else {
        printf("有测试失败，请检查！\n");
    }
}

// 浮点数比较（考虑精度）
bool float_equal(ftype_t a, ftype_t b, ftype_t epsilon) {
    if ((g_print_eps) && (MFABS(a - b) > epsilon)) {
#if (CFG_FLOATWORD_BITSIZE == 128)
    char buf[128];
    // 注意：格式字符串中只能有一个转换说明符
    quadmath_snprintf(buf, sizeof(buf), "epsilon: %+.6Qe\n", MFABS(a - b)); 
    printf("%s\n", buf);
#else
    printf("epsilon: %+.6e\n", MFABS(a - b));
#endif
    }
    return (MFABS(a - b) <= epsilon);
}

// 向量比较
bool vec3_equal(vec3_st a, vec3_st b, ftype_t epsilon) {
    return float_equal(a.x, b.x, epsilon) &&
           float_equal(a.y, b.y, epsilon) &&
           float_equal(a.z, b.z, epsilon);
}

// 矩阵比较
bool mat3_equal(mat3_st a, mat3_st b, ftype_t epsilon) {
    for (int i = 0; i < 9; i++) {
        if (!float_equal(a.v[i], b.v[i], epsilon)) {
            return false;
        }
    }
    return true;
}

// 四元数比较
bool quat_equal(quat_st a, quat_st b, ftype_t epsilon) {
    if ((a.w * b.w) < MFLOAT_C(0.0)) {
        b.x = -b.x;
        b.y = -b.y;
        b.z = -b.z;
        b.w = -b.w;
    }
    return float_equal(a.x, b.x, epsilon) &&
           float_equal(a.y, b.y, epsilon) &&
           float_equal(a.z, b.z, epsilon) &&
           float_equal(a.w, b.w, epsilon);
}

// 轴角比较
bool axis_equal(axis_st a, axis_st b, ftype_t epsilon) {
    if ((a.angle * b.angle) < MFLOAT_C(0.0)) {
        b.v3.x = -b.v3.x;
        b.v3.y = -b.v3.y;
        b.v3.z = -b.v3.z;
        b.angle = -b.angle;
    }
    return vec3_equal(a.v3, b.v3, epsilon) &&
           float_equal(a.angle, b.angle, epsilon);
}

// 欧拉角比较
bool eula_equal(eula_st a, eula_st b, ftype_t epsilon) {
    return float_equal(a.x, b.x, epsilon) &&
           float_equal(a.y, b.y, epsilon) &&
           float_equal(a.z, b.z, epsilon);
}


// 测试主程序
int main(int argc, char *argv[]) {
    //增加执行耗时统计功能
    clock_t start_time = clock();
    // 解析命令行参数
    g_verbose_mode = false;
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-v") == 0 || strcmp(argv[i], "--verbose") == 0) {
            g_verbose_mode = true;
        }
        // 打印误差值
        if (strcmp(argv[i], "-e") == 0 || strcmp(argv[i], "--epsilon") == 0) {
            g_print_eps = true;
        }
        if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0) {
            printf("SpaceMath 测试程序\n");
            printf("用法: %s [选项]\n", argv[0]);
            printf("选项:\n");
            printf("  -v, --verbose  显示详细测试结果\n");
            printf("  -e, --epsilon  打印误差值\n");
            printf("  -h, --help     显示此帮助信息\n");
            return 0;
        }
    }
    
    printf("spacemath(v0.1.3) test\n");
    printf("CFG_EULER_ORDER       = \"%s\"\n", CFG_EULER_ORDER);
    printf("CFG_FLOATWORD_BITSIZE = %d bit\n", CFG_FLOATWORD_BITSIZE);
    printf("sizeof(void *)        = %ld bit\n", sizeof(void *) * 8);
    printf("sizeof(ftype_t)       = %ld bit\n", sizeof(ftype_t) * 8);
    printf("开始 SpaceMath 库测试...\n");

    // 运行各个模块的测试
    test_others_all();
    test_matrix_all();
    test_vector_all();
    test_quat_all();
    test_rotation_all();
    test_random_all();
    test_eula_all();
    test_axis_all();

    // 打印最终统计结果
    test_print_summary();
    // 打印执行耗时
    printf("测试耗时: %.3f 秒\n", (double)(clock() - start_time) / CLOCKS_PER_SEC);
    
    return g_test_stats.failed_tests > 0 ? 1 : 0;
}
/**********************************************************************************************************************
 * End of spacemath file
 *********************************************************************************************************************/