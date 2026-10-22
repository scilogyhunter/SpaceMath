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
 * @file test_axis.c
 * @brief 测试轴角函数实现文件
 * @author scilogyhunter
 * @date 2026.10.22
 * @version V0.1.3
 *
 * 本文件定义了测试轴角函数和全局变量，用于各个测试模块的实现。
 */

/*!
 * @defgroup test_axis_modify 修改记录
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

/** @} */ /* end of group test_axis_modify */

#include "test_main.h"
#include <math.h>

// 辅助函数测试

int test_axis_is_zero(void) {
    axis_st zero = axis_zero();
    axis_st non_zero = axis(0.0, 0.0, 1.0, MPI_2);
    
    if (!axis_is_zero(zero)) return -1;
    if (axis_is_zero(non_zero)) return -1;
    
    return 0;
}

int test_axis(void) {
    axis_st a = axis(1.0, 2.0, 3.0, MPI_2);
    axis_st expected = {.v3 = {.x = 1.0, .y = 2.0, .z = 3.0}, .angle = MPI_2};

    expected.v3 = vec3_unit(expected.v3);
    if (!axis_equal(a, expected, MEPSILON)) return -1;

    return 0;
}

int test_axis_v(void) {
    ftype_t v[4] = {1.0, 2.0, 3.0, MPI_2};
    axis_st a = axis_v(v);
    axis_st expected = {.v3 = {.x = 1.0, .y = 2.0, .z = 3.0}, .angle = MPI_2};

    expected.v3 = vec3_unit(expected.v3);
    if (!axis_equal(a, expected, MEPSILON)) return -1;
    return 0;
}

int test_axis_zero(void) {
    axis_st zero = axis_zero();
    axis_st expected = {.v3 = {.x = 0.0, .y = 0.0, .z = 0.0}, .angle = 0.0};
    
    if (!axis_equal(zero, expected, MEPSILON)) return -1;
    
    return 0;
}

int test_axis_from_vector_angle(void) {
    vec3_st axis_vector = vec3(0.0, 0.0, 1.0);
    ftype_t angle = MPI_2;
    axis_st a = axis_from_vector_angle(axis_vector, angle);
    axis_st expected = {.v3 = {.x = 0.0, .y = 0.0, .z = 1.0}, .angle = MPI_2};
    
    if (!axis_equal(a, expected, MEPSILON)) return -1;
    
    return 0;
}

int test_axis_from_vector_vector(void) {
    vec3_st from = vec3(1.0, 0.0, 0.0);
    vec3_st to = vec3(0.0, 1.0, 0.0);
    axis_st a = axis_from_vector_vector(to, from);

    // 验证旋转效果
    vec3_st rotated = rotation_aRv(a, from);
    if (!vec3_equal(rotated, to, MEPSILON)) return -1;
    
    return 0;
}

// 辅助函数模块所有测试
int test_axis_all(void) {
    test_print_result("axis_is_zero", test_axis_is_zero());
    test_print_result("axis", test_axis());
    test_print_result("axis_v", test_axis_v());
    test_print_result("axis_zero", test_axis_zero());
    test_print_result("axis_from_vector_angle", test_axis_from_vector_angle());
    test_print_result("axis_from_vector_vector", test_axis_from_vector_vector());
    
    return 0;
}

/**********************************************************************************************************************
 * End of spacemath file
 *********************************************************************************************************************/