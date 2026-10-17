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
 * @file test_vector.c
 * @brief 三维向量运算测试文件
 * @author scilogyhunter
 * @date 2025.09.01
 * @version V0.1.2
 *
 * 本文件实现了三维向量运算的单元测试，验证了向量的创建、比较、点积、角度计算、长度和距离等基本功能。
 */

/*!
 * @defgroup test_vector_modify 修改记录
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

/** @} */ /* end of group test_vector_modify */

#include "test_main.h"
#include <math.h>

// 向量测试函数

int test_vec3_is_zero(void) {
    vec3_st zero = vec3_zero();
    vec3_st non_zero = vec3(1.0, 2.0, 3.0);
    
    if (!vec3_is_zero(zero)) return -1;
    if (vec3_is_zero(non_zero)) return -1;
    
    return 0;
}

int test_vec3_is_equal(void) {
    vec3_st v1 = vec3(1.0, 2.0, 3.0);
    vec3_st v2 = vec3(1.0, 2.0, 3.0);
    vec3_st v3 = vec3(4.0, 5.0, 6.0);
    
    if (!vec3_is_equal(v1, v2)) return -1;
    if (vec3_is_equal(v1, v3)) return -1;
    
    return 0;
}

int test_vec3_dot(void) {
    vec3_st v1 = vec3(1.0, 2.0, 3.0);
    vec3_st v2 = vec3(4.0, 5.0, 6.0);
    ftype_t dot = vec3_dot(v1, v2);
    
    if (!float_equal(dot, 32.0, MEPSILON)) return -1; // 1*4 + 2*5 + 3*6 = 4 + 10 + 18 = 32
    
    return 0;
}

int test_vec3_angle(void) {
    vec3_st v1 = vec3(1.0, 0.0, 0.0);
    vec3_st v2 = vec3(0.0, 1.0, 0.0);
    ftype_t angle = vec3_angle(v1, v2);
    
    if (!float_equal(angle, MPI_2, MEPSILON)) return -1; // 90度
    
    return 0;
}

int test_vec3_len(void) {
    vec3_st v = vec3(3.0, 4.0, 0.0);
    ftype_t len = vec3_len(v);
    
    if (!float_equal(len, 5.0, MEPSILON)) return -1; // sqrt(3^2 + 4^2) = 5
    
    return 0;
}

int test_vec3_dist(void) {
    vec3_st v1 = vec3(0.0, 0.0, 0.0);
    vec3_st v2 = vec3(3.0, 4.0, 0.0);
    ftype_t dist = vec3_dist(v1, v2);
    
    if (!float_equal(dist, 5.0, MEPSILON)) return -1;
    
    return 0;
}

int test_vec3_create(void) {
    vec3_st v = vec3(1.0, 2.0, 3.0);
    vec3_st expected = {.x = 1.0, .y = 2.0, .z = 3.0};
    
    if (!vec3_equal(v, expected, MEPSILON)) return -1;
    
    return 0;
}

int test_vec3_v(void) {
    ftype_t v[3] = {1.0, 2.0, 3.0};
    vec3_st vec = vec3_v(v);
    vec3_st expected = {.x = 1.0, .y = 2.0, .z = 3.0};
    
    if (!vec3_equal(vec, expected, MEPSILON)) return -1;
    
    return 0;
}

int test_vec3_zero(void) {
    vec3_st zero = vec3_zero();
    vec3_st expected = {.x = 0.0, .y = 0.0, .z = 0.0};
    
    if (!vec3_equal(zero, expected, MEPSILON)) return -1;
    
    return 0;
}

int test_vec3_one(void) {
    vec3_st one = vec3_one();
    vec3_st expected = {.x = 1.0, .y = 1.0, .z = 1.0};
    
    if (!vec3_equal(one, expected, MEPSILON)) return -1;
    
    return 0;
}

int test_vec3_add(void) {
    vec3_st v1 = vec3(1.0, 2.0, 3.0);
    vec3_st v2 = vec3(4.0, 5.0, 6.0);
    vec3_st result = vec3_add(v1, v2);
    vec3_st expected = {.x = 5.0, .y = 7.0, .z = 9.0};
    
    if (!vec3_equal(result, expected, MEPSILON)) return -1;
    
    return 0;
}

int test_vec3_sub(void) {
    vec3_st v1 = vec3(5.0, 7.0, 9.0);
    vec3_st v2 = vec3(1.0, 2.0, 3.0);
    vec3_st result = vec3_sub(v1, v2);
    vec3_st expected = {.x = 4.0, .y = 5.0, .z = 6.0};
    
    if (!vec3_equal(result, expected, MEPSILON)) return -1;
    
    return 0;
}

int test_vec3_mul(void) {
    vec3_st v1 = vec3(1.0, 2.0, 3.0);
    vec3_st v2 = vec3(4.0, 5.0, 6.0);
    vec3_st result = vec3_mul(v1, v2);
    vec3_st expected = {.x = 4.0, .y = 10.0, .z = 18.0};
    
    if (!vec3_equal(result, expected, MEPSILON)) return -1;
    
    return 0;
}

int test_vec3_div(void) {
    vec3_st v1 = vec3(4.0, 10.0, 18.0);
    vec3_st v2 = vec3(1.0, 2.0, 3.0);
    vec3_st result = vec3_div(v1, v2);
    vec3_st expected = {.x = 4.0, .y = 5.0, .z = 6.0};
    
    if (!vec3_equal(result, expected, MEPSILON)) return -1;
    
    return 0;
}

int test_vec3_neg(void) {
    vec3_st v = vec3(1.0, 2.0, 3.0);
    vec3_st neg = vec3_neg(v);
    vec3_st expected = {.x = -1.0, .y = -2.0, .z = -3.0};
    
    if (!vec3_equal(neg, expected, MEPSILON)) return -1;
    
    return 0;
}

int test_vec3_abs(void) {
    vec3_st v = vec3(-1.0, -2.0, -3.0);
    vec3_st abs_v = vec3_abs(v);
    vec3_st expected = {.x = 1.0, .y = 2.0, .z = 3.0};
    
    if (!vec3_equal(abs_v, expected, MEPSILON)) return -1;
    
    return 0;
}

int test_vec3_cross(void) {
    vec3_st v1 = vec3(1.0, 0.0, 0.0);
    vec3_st v2 = vec3(0.0, 1.0, 0.0);
    vec3_st cross = vec3_cross(v1, v2);
    vec3_st expected = {.x = 0.0, .y = 0.0, .z = 1.0};
    
    if (!vec3_equal(cross, expected, MEPSILON)) return -1;
    
    return 0;
}

int test_vec3_unit(void) {
    vec3_st v = vec3(3.0, 4.0, 0.0);
    vec3_st unit = vec3_unit(v);
    
    ftype_t len = vec3_len(unit);
    if (!float_equal(len, 1.0, MEPSILON)) return -1;
    
    return 0;
}

int test_vec3_project(void) {
    vec3_st v = vec3(3.0, 4.0, 0.0);
    vec3_st onto = vec3(1.0, 0.0, 0.0);
    vec3_st projection = vec3_project(v, onto);
    vec3_st expected = {.x = 3.0, .y = 0.0, .z = 0.0};
    
    if (!vec3_equal(projection, expected, MEPSILON)) return -1;
    
    return 0;
}

int test_vec3_reflect(void) {
    vec3_st v = vec3(1.0, -1.0, 0.0);
    vec3_st normal = vec3(0.0, 1.0, 0.0);
    vec3_st reflection = vec3_reflect(v, normal);
    vec3_st expected = {.x = 1.0, .y = 1.0, .z = 0.0};
    
    if (!vec3_equal(reflection, expected, MEPSILON)) return -1;
    
    return 0;
}

int test_vec3_rotate(void) {
    vec3_st v = vec3(1.0, 0.0, 0.0);
    vec3_st axis = vec3(0.0, 0.0, 1.0);
    ftype_t angle = MPI_2; // 90度
    vec3_st rotated = vec3_rotate(v, axis, angle);
    
    // 使用更宽松的容差，因为罗德里格斯旋转公式可能有小的浮点数误差
    if (!float_equal(rotated.x, 0.0, 1e-5)) return -1;
    if (!float_equal(rotated.y, 1.0, 1e-5)) return -1;
    if (!float_equal(rotated.z, 0.0, 1e-5)) return -1;
    
    return 0;
}

int test_vec3_lerp(void) {
    vec3_st from = vec3(0.0, 0.0, 0.0);
    vec3_st to = vec3(10.0, 10.0, 10.0);
    vec3_st result = vec3_lerp(from, to, 0.5);
    vec3_st expected = {.x = 5.0, .y = 5.0, .z = 5.0};
    
    if (!vec3_equal(result, expected, MEPSILON)) return -1;
    
    return 0;
}

int test_vec3_bezier3(void) {
    vec3_st v0 = vec3(0.0, 0.0, 0.0);
    vec3_st v1 = vec3(1.0, 1.0, 0.0);
    vec3_st v2 = vec3(2.0, 0.0, 0.0);
    vec3_st result = vec3_bezier3(v0, v1, v2, 0.5);
    vec3_st expected = {.x = 1.0, .y = 0.5, .z = 0.0};
    
    if (!vec3_equal(result, expected, MEPSILON)) return -1;
    
    return 0;
}

int test_vec3_bezier4(void) {
    vec3_st v0 = vec3(0.0, 0.0, 0.0);
    vec3_st v1 = vec3(1.0, 1.0, 0.0);
    vec3_st v2 = vec3(2.0, 1.0, 0.0);
    vec3_st v3 = vec3(3.0, 0.0, 0.0);
    vec3_st result = vec3_bezier4(v0, v1, v2, v3, 0.5);
    vec3_st expected = {.x = 1.5, .y = 0.75, .z = 0.0};
    
    if (!vec3_equal(result, expected, MEPSILON)) return -1;
    
    return 0;
}

int test_vec3_len_sq(void) {
    vec3_st v = vec3(3.0, 4.0, 0.0);
    ftype_t len_sq = vec3_len_sq(v);
    
    if (!float_equal(len_sq, 25.0, MEPSILON)) return -1; // 3^2 + 4^2 = 25
    
    return 0;
}

int test_vec3_dist_sq(void) {
    vec3_st v1 = vec3(0.0, 0.0, 0.0);
    vec3_st v2 = vec3(3.0, 4.0, 0.0);
    ftype_t dist_sq = vec3_dist_sq(v1, v2);
    
    if (!float_equal(dist_sq, 25.0, MEPSILON)) return -1; // 3^2 + 4^2 = 25
    
    return 0;
}

int test_vec3_is_equal_eps(void) {
    vec3_st v1 = vec3(1.0, 2.0, 3.0);
    vec3_st v2 = vec3(1.0001, 2.0001, 3.0001);
    vec3_st v3 = vec3(1.1, 2.1, 3.1);
    
    if (!vec3_is_equal_eps(v1, v2, 0.001)) return -1;
    if (vec3_is_equal_eps(v1, v3, 0.001)) return -1;
    
    return 0;
}

int test_vec3_is_zero_eps(void) {
    vec3_st zero = vec3(0.0001, 0.0001, 0.0001);
    vec3_st non_zero = vec3(0.1, 0.1, 0.1);
    
    if (!vec3_is_zero_eps(zero, 0.001)) return -1;
    if (vec3_is_zero_eps(non_zero, 0.001)) return -1;
    
    return 0;
}

int test_vec3_is_linear_independent(void) {
    vec3_st v1 = vec3(1.0, 0.0, 0.0);
    vec3_st v2 = vec3(0.0, 1.0, 0.0);
    vec3_st v3 = vec3(0.0, 0.0, 1.0);
    vec3_st v4 = vec3(1.0, 1.0, 0.0); // 与v1,v2线性相关
    
    if (!vec3_is_linear_independent(v1, v2, v3)) return -1;
    if (vec3_is_linear_independent(v1, v2, v4)) return -1;
    
    return 0;
}

int test_vec3_add_f(void) {
    vec3_st v = vec3(1.0, 2.0, 3.0);
    vec3_st result = vec3_add_f(v, 2.0);
    vec3_st expected = {.x = 3.0, .y = 4.0, .z = 5.0};
    
    if (!vec3_equal(result, expected, MEPSILON)) return -1;
    
    return 0;
}

int test_vec3_sub_f(void) {
    vec3_st v = vec3(5.0, 7.0, 9.0);
    vec3_st result = vec3_sub_f(v, 2.0);
    vec3_st expected = {.x = 3.0, .y = 5.0, .z = 7.0};
    
    if (!vec3_equal(result, expected, MEPSILON)) return -1;
    
    return 0;
}

int test_vec3_mul_f(void) {
    vec3_st v = vec3(1.0, 2.0, 3.0);
    vec3_st result = vec3_mul_f(v, 2.0);
    vec3_st expected = {.x = 2.0, .y = 4.0, .z = 6.0};
    
    if (!vec3_equal(result, expected, MEPSILON)) return -1;
    
    return 0;
}

int test_vec3_div_f(void) {
    vec3_st v = vec3(2.0, 4.0, 6.0);
    vec3_st result = vec3_div_f(v, 2.0);
    vec3_st expected = {.x = 1.0, .y = 2.0, .z = 3.0};
    
    if (!vec3_equal(result, expected, MEPSILON)) return -1;
    
    return 0;
}

int test_vec3_sign(void) {
    vec3_st v = vec3(-1.0, 0.0, 2.0);
    vec3_st sign = vec3_sign(v);
    vec3_st expected = {.x = -1.0, .y = 0.0, .z = 1.0};
    
    if (!vec3_equal(sign, expected, MEPSILON)) return -1;
    
    return 0;
}

int test_vec3_floor(void) {
    vec3_st v = vec3(1.7, 2.3, -1.8);
    vec3_st floor_v = vec3_floor(v);
    vec3_st expected = {.x = 1.0, .y = 2.0, .z = -2.0};
    
    if (!vec3_equal(floor_v, expected, MEPSILON)) return -1;
    
    return 0;
}

int test_vec3_ceil(void) {
    vec3_st v = vec3(1.7, 2.3, -1.8);
    vec3_st ceil_v = vec3_ceil(v);
    vec3_st expected = {.x = 2.0, .y = 3.0, .z = -1.0};
    
    if (!vec3_equal(ceil_v, expected, MEPSILON)) return -1;
    
    return 0;
}

int test_vec3_round(void) {
    vec3_st v = vec3(1.7, 2.3, -1.8);
    vec3_st round_v = vec3_round(v);
    vec3_st expected = {.x = 2.0, .y = 2.0, .z = -2.0};
    
    if (!vec3_equal(round_v, expected, MEPSILON)) return -1;
    
    return 0;
}

int test_vec3_trunc(void) {
    vec3_st v = vec3(1.7, 2.3, -1.8);
    vec3_st trunc_v = vec3_trunc(v);
    vec3_st expected = {.x = 1.0, .y = 2.0, .z = -1.0};
    
    if (!vec3_equal(trunc_v, expected, MEPSILON)) return -1;
    
    return 0;
}

int test_vec3_max(void) {
    vec3_st v1 = vec3(1.0, 5.0, 3.0);
    vec3_st v2 = vec3(4.0, 2.0, 6.0);
    vec3_st max_v = vec3_max(v1, v2);
    vec3_st expected = {.x = 4.0, .y = 5.0, .z = 6.0};
    
    if (!vec3_equal(max_v, expected, MEPSILON)) return -1;
    
    return 0;
}

int test_vec3_min(void) {
    vec3_st v1 = vec3(1.0, 5.0, 3.0);
    vec3_st v2 = vec3(4.0, 2.0, 6.0);
    vec3_st min_v = vec3_min(v1, v2);
    vec3_st expected = {.x = 1.0, .y = 2.0, .z = 3.0};
    
    if (!vec3_equal(min_v, expected, MEPSILON)) return -1;
    
    return 0;
}

int test_vec3_clamp(void) {
    vec3_st v = vec3(-1.0, 5.0, 2.0);
    vec3_st min = vec3(0.0, 0.0, 0.0);
    vec3_st max = vec3(3.0, 3.0, 3.0);
    vec3_st clamped = vec3_clamp(v, min, max);
    vec3_st expected = {.x = 0.0, .y = 3.0, .z = 2.0};
    
    if (!vec3_equal(clamped, expected, MEPSILON)) return -1;
    
    return 0;
}

int test_vec3_clamp_min_abs(void) {
    vec3_st v = vec3(0.5, -0.2, 1.5);
    vec3_st clamped = vec3_clamp_min_abs(v, 1.0);
    vec3_st expected = {.x = 1.0, .y = -1.0, .z = 1.5};
    
    if (!vec3_equal(clamped, expected, MEPSILON)) return -1;
    
    return 0;
}

int test_vec3_clamp_max_abs(void) {
    vec3_st v = vec3(2.0, -3.0, 1.0);
    vec3_st clamped = vec3_clamp_max_abs(v, 2.0);
    vec3_st expected = {.x = 2.0, .y = -2.0, .z = 1.0};
    
    if (!vec3_equal(clamped, expected, MEPSILON)) return -1;
    
    return 0;
}

int test_vec3_slide(void) {
    vec3_st v = vec3(3.0, 4.0, 0.0);
    vec3_st normal = vec3(0.0, 1.0, 0.0);
    vec3_st slide_v = vec3_slide(v, normal);
    vec3_st expected = {.x = 3.0, .y = 0.0, .z = 0.0};
    
    if (!vec3_equal(slide_v, expected, MEPSILON)) return -1;
    
    return 0;
}

int test_vec3_snap(void) {
    vec3_st v1 = vec3(1.7, 2.3, 3.8);
    vec3_st v2 = vec3(0.5, 0.5, 0.5);
    vec3_st snap_v = vec3_snap(v1, v2);
    vec3_st expected = {.x = 1.5, .y = 2.0, .z = 3.5};
    
    if (!vec3_equal(snap_v, expected, MEPSILON)) return -1;
    
    return 0;
}

int test_vec3_snap_f(void) {
    vec3_st v = vec3(1.7, 2.3, 3.8);
    vec3_st snap_v = vec3_snap_f(v, 0.5);
    vec3_st expected = {.x = 1.5, .y = 2.0, .z = 3.5};

    if (!vec3_equal(snap_v, expected, MEPSILON)) return -1;
    
    return 0;
}

int test_vec3_wrapping_f(void) {
    vec3_st v = vec3(3.5, 4.5, 5.5);
    vec3_st wrapped = vec3_wrapping_f(v, 4.0);
    vec3_st expected = {.x = 3.5, .y = 0.5, .z = 1.5};
    
    if (!vec3_equal(wrapped, expected, MEPSILON)) return -1;
    
    return 0;
}

// 向量模块所有测试
int test_vector_all(void) {
    test_print_result("vec3_is_zero", test_vec3_is_zero());
    test_print_result("vec3_is_equal", test_vec3_is_equal());
    test_print_result("vec3_is_equal_eps", test_vec3_is_equal_eps());
    test_print_result("vec3_is_zero_eps", test_vec3_is_zero_eps());
    test_print_result("vec3_is_linear_independent", test_vec3_is_linear_independent());
    test_print_result("vec3_dot", test_vec3_dot());
    test_print_result("vec3_angle", test_vec3_angle());
    test_print_result("vec3_len", test_vec3_len());
    test_print_result("vec3_len_sq", test_vec3_len_sq());
    test_print_result("vec3_dist", test_vec3_dist());
    test_print_result("vec3_dist_sq", test_vec3_dist_sq());
    test_print_result("vec3_create", test_vec3_create());
    test_print_result("vec3_v", test_vec3_v());
    test_print_result("vec3_zero", test_vec3_zero());
    test_print_result("vec3_one", test_vec3_one());
    test_print_result("vec3_add", test_vec3_add());
    test_print_result("vec3_add_f", test_vec3_add_f());
    test_print_result("vec3_sub", test_vec3_sub());
    test_print_result("vec3_sub_f", test_vec3_sub_f());
    test_print_result("vec3_mul", test_vec3_mul());
    test_print_result("vec3_mul_f", test_vec3_mul_f());
    test_print_result("vec3_div", test_vec3_div());
    test_print_result("vec3_div_f", test_vec3_div_f());
    test_print_result("vec3_neg", test_vec3_neg());
    test_print_result("vec3_abs", test_vec3_abs());
    test_print_result("vec3_sign", test_vec3_sign());
    test_print_result("vec3_floor", test_vec3_floor());
    test_print_result("vec3_ceil", test_vec3_ceil());
    test_print_result("vec3_round", test_vec3_round());
    test_print_result("vec3_trunc", test_vec3_trunc());
    test_print_result("vec3_max", test_vec3_max());
    test_print_result("vec3_min", test_vec3_min());
    test_print_result("vec3_clamp", test_vec3_clamp());
    test_print_result("vec3_clamp_min_abs", test_vec3_clamp_min_abs());
    test_print_result("vec3_clamp_max_abs", test_vec3_clamp_max_abs());
    test_print_result("vec3_cross", test_vec3_cross());
    test_print_result("vec3_unit", test_vec3_unit());
    test_print_result("vec3_project", test_vec3_project());
    test_print_result("vec3_slide", test_vec3_slide());
    test_print_result("vec3_reflect", test_vec3_reflect());
    test_print_result("vec3_rotate", test_vec3_rotate());
    test_print_result("vec3_lerp", test_vec3_lerp());
    test_print_result("vec3_bezier3", test_vec3_bezier3());
    test_print_result("vec3_bezier4", test_vec3_bezier4());
    test_print_result("vec3_snap", test_vec3_snap());
    test_print_result("vec3_snap_f", test_vec3_snap_f());
    test_print_result("vec3_wrapping_f", test_vec3_wrapping_f());
    
    return 0;
}

/**********************************************************************************************************************
 * End of spacemath file
 *********************************************************************************************************************/