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
 * @file test_main.h
 * @brief 测试辅助函数头文件
 * @author scilogyhunter
 * @date 2026.10.22
 * @version V0.1.3
 *
 * 本文件定义了测试辅助函数和全局变量，用于各个测试模块的实现。
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

#ifndef TEST_UTILS_H
#define TEST_UTILS_H

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "../src/spacemath.h"

#if (CFG_FLOATWORD_BITSIZE == 32)
#define TEST_EPSILON        (MFLOAT_C(1e-3))
#endif

#if (CFG_FLOATWORD_BITSIZE == 64)
#define TEST_EPSILON        (MFLOAT_C(1e-8))
#endif

#if (CFG_FLOATWORD_BITSIZE == 128)
#define TEST_EPSILON        (MFLOAT_C(1e-12))
#endif
// 测试结果统计
typedef struct {
    int total_tests;
    int passed_tests;
    int failed_tests;
} test_stats_t;

// 全局测试统计
extern test_stats_t g_test_stats;

// 测试打印控制
extern bool g_verbose_mode;

void print_axis(axis_st a);
void print_eula(eula_st e);
void print_vec3(vec3_st v);
void print_mat3(mat3_st m);
void print_quat(quat_st q);

// 打印测试结果
void test_print_result(const char* test_name, int result);

// 打印最终统计
void test_print_summary(void);

// 浮点数比较（考虑精度）
bool float_equal(ftype_t a, ftype_t b, ftype_t epsilon);

// 向量比较
bool vec3_equal(vec3_st a, vec3_st b, ftype_t epsilon);

// 矩阵比较
bool mat3_equal(mat3_st a, mat3_st b, ftype_t epsilon);

// 四元数比较
bool quat_equal(quat_st a, quat_st b, ftype_t epsilon);

// 轴角比较
bool axis_equal(axis_st a, axis_st b, ftype_t epsilon);

// 欧拉角比较
bool eula_equal(eula_st a, eula_st b, ftype_t epsilon);

#endif // TEST_UTILS_H

/**********************************************************************************************************************
 * End of spacemath file
 *********************************************************************************************************************/