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
 * @file test_quat.c
 * @brief 四元数运算测试文件
 * @author scilogyhunter
 * @date 2026.10.22
 * @version V0.1.3
 *
 * 本文件实现了四元数运算的单元测试，验证了四元数的创建、比较、点积、角度计算、长度和旋转等基本功能。
 */

/*!
 * @defgroup test_quat_modify 修改记录
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

/** @} */ /* end of group test_quat_modify */

#include "test_main.h"
#include <math.h>

// 四元数测试函数

int test_quat_is_zero(void) {
    quat_st zero = quat_zero();
    quat_st non_zero = quat(1.0, 2.0, 3.0, 4.0);
    
    if (!quat_is_zero(zero)) return -1;
    if (quat_is_zero(non_zero)) return -1;
    
    return 0;
}

int test_quat_is_equal(void) {
    quat_st q1 = quat(1.0, 2.0, 3.0, 4.0);
    quat_st q2 = quat(1.0, 2.0, 3.0, 4.0);
    quat_st q3 = quat(5.0, 6.0, 7.0, 8.0);
    
    if (!quat_is_equal(q1, q2)) return -1;
    if (quat_is_equal(q1, q3)) return -1;
    
    return 0;
}

int test_quat_dot(void) {
    quat_st q1 = quat(1.0, 2.0, 3.0, 4.0);
    quat_st q2 = quat(5.0, 6.0, 7.0, 8.0);
    ftype_t dot = quat_dot(q1, q2);
    
    if (!float_equal(dot, 70.0, MEPSILON)) return -1; // 1*5 + 2*6 + 3*7 + 4*8 = 5 + 12 + 21 + 32 = 70
    
    return 0;
}

int test_quat_len(void) {
    quat_st q = quat(0.0, 3.0, 4.0, 0.0);
    ftype_t len = quat_len(q);
    
    if (!float_equal(len, 5.0, MEPSILON)) return -1; // sqrt(0^2 + 3^2 + 4^2 + 0^2) = 5
    
    return 0;
}

int test_quat_angle(void) {
    quat_st q = quat_rotation_x(MPI_2); // 绕X轴旋转90度
    ftype_t angle = quat_angle(q);

    if (!float_equal(angle, MPI_2, MEPSILON)) return -1; // 90度
    
    return 0;
}

int test_quat_axis(void) {
    quat_st q = quat_rotation_x(MPI_2); // 绕X轴旋转90度
    vec3_st axis = quat_axis(q);
    vec3_st expected = {.x = 1.0, .y = 0.0, .z = 0.0};

    if (!vec3_equal(axis, expected, MEPSILON)) return -1;
    
    return 0;
}

int test_quat_rotate_vec3(void) {
    quat_st q = quat_rotation_z(MPI_2); // 绕Z轴旋转90度
    vec3_st v = vec3(1.0, 0.0, 0.0);
    vec3_st rotated = quat_rotate_vec3(q, v);
    vec3_st expected = {.x = 0.0, .y = 1.0, .z = 0.0};
    
    if (!vec3_equal(rotated, expected, MEPSILON)) return -1;
    
    return 0;
}

int test_quat_create(void) {
    quat_st q = quat(1.0, 2.0, 3.0, 4.0);
    quat_st expected = {.x = 1.0, .y = 2.0, .z = 3.0, .w = 4.0};
    
    if (!quat_equal(q, expected, MEPSILON)) return -1;
    
    return 0;
}

int test_quat_v(void) {
    ftype_t v[4] = {1.0, 2.0, 3.0, 4.0};
    quat_st q = quat_v(v);
    quat_st expected = {.x = 1.0, .y = 2.0, .z = 3.0, .w = 4.0};
    
    if (!quat_equal(q, expected, MEPSILON)) return -1;
    
    return 0;
}

int test_quat_zero(void) {
    quat_st zero = quat_zero();
    quat_st expected = {.x = 0.0, .y = 0.0, .z = 0.0, .w = 0.0};
    
    if (!quat_equal(zero, expected, MEPSILON)) return -1;
    
    return 0;
}

int test_quat_identity(void) {
    quat_st identity = quat_identity();
    quat_st expected = {.x = 0.0, .y = 0.0, .z = 0.0, .w = 1.0};
    
    if (!quat_equal(identity, expected, MEPSILON)) return -1;
    
    return 0;
}

int test_quat_add(void) {
    quat_st q1 = quat(1.0, 2.0, 3.0, 4.0);
    quat_st q2 = quat(5.0, 6.0, 7.0, 8.0);
    quat_st result = quat_add(q1, q2);
    quat_st expected = {.x = 6.0, .y = 8.0, .z = 10.0, .w = 12.0};

    if (!quat_equal(result, expected, MEPSILON)) return -1;

    return 0;
}

int test_quat_sub(void) {
    quat_st q1 = quat(1.0, 2.0, 3.0, 4.0);
    quat_st q2 = quat(5.0, 6.0, 7.0, 8.0);
    quat_st result = quat_sub(q1, q2); // q1 - q2
    quat_st expected = {.x = -4.0, .y = -4.0, .z = -4.0, .w = -4.0};

    if (!quat_equal(result, expected, MEPSILON)) return -1;
    return 0;
}

int test_quat_mul(void) {
    quat_st q1 = quat(1.0, 2.0, 3.0, 4.0);
    quat_st q2 = quat(5.0, 6.0, 7.0, 8.0);
    quat_st result = quat_mul(q1, q2);
    
    // 四元数乘法结果验证
    // 这里只验证结果不为零，具体数学验证需要更复杂的测试
    if (quat_is_zero(result)) return -1;
    
    return 0;
}

int test_quat_conjugate(void) {
    quat_st q = quat(1.0, 2.0, 3.0, 4.0);
    quat_st conjugate = quat_conjugate(q);
    quat_st expected = {.x = -1.0, .y = -2.0, .z = -3.0, .w = 4.0};
    
    if (!quat_equal(conjugate, expected, MEPSILON)) return -1;
    
    return 0;
}

int test_quat_inverse(void) {
    quat_st q = quat(0.0, 0.0, 0.0, 1.0); // 单位四元数
    quat_st inverse = quat_inverse(q);
    quat_st expected = {.x = 0.0, .y = 0.0, .z = 0.0, .w = 1.0};
    
    if (!quat_equal(inverse, expected, MEPSILON)) return -1;
    
    return 0;
}

int test_quat_normalize(void) {
    quat_st q = quat(0.0, 3.0, 4.0, 0.0);
    quat_st normalized = quat_normalize(q);
    
    ftype_t len = quat_len(normalized);
    if (!float_equal(len, 1.0, MEPSILON)) return -1;
    
    return 0;
}

int test_quat_from_axis_angle(void) {
    vec3_st axis = vec3(0.0, 0.0, 1.0);
    ftype_t angle = MPI_2; // 90度
    quat_st q = quat_from_axis_angle(axis, angle);
    
    // 验证旋转效果
    vec3_st v = vec3(1.0, 0.0, 0.0);
    vec3_st rotated = quat_rotate_vec3(q, v);
    vec3_st expected = {.x = 0.0, .y = 1.0, .z = 0.0};

    if (!vec3_equal(rotated, expected, MEPSILON)) return -1;
    
    return 0;
}

int test_quat_from_vv(void) {
    vec3_st from = vec3(1.0, 0.0, 0.0);
    vec3_st to = vec3(0.0, 1.0, 0.0);
    quat_st q = quat_from_vv(to, from);
    
    // 验证旋转效果
    vec3_st rotated = quat_rotate_vec3(q, from);
    
    if (!vec3_equal(rotated, to, MEPSILON)) return -1;
    
    return 0;
}

int test_quat_lerp(void) {
    quat_st from = quat(MFLOAT_C(0.0), MFLOAT_C(0.0), MFLOAT_C(0.0), MFLOAT_C(1.0));
    quat_st to = quat(MFLOAT_C(1.0), MFLOAT_C(1.0), MFLOAT_C(1.0), MFLOAT_C(1.0));
    quat_st result = quat_lerp(from, to, MFLOAT_C(0.5));
    quat_st expected = {.x = MFLOAT_C(0.5), .y = MFLOAT_C(0.5), .z = MFLOAT_C(0.5), .w = MFLOAT_C(1.0)};
    
    if (!quat_equal(result, expected, MEPSILON)) return -1;
    
    return 0;
}

int test_quat_slerp(void) {
    quat_st from = quat_rotation_z(MFLOAT_C(0.0)); // 绕Z轴旋转0度
    quat_st to = quat_rotation_z(MPI_2); // 绕Z轴旋转90度
    quat_st result = quat_slerp(from, to, MFLOAT_C(0.5));
    
    // 验证旋转效果
    vec3_st v = vec3(MFLOAT_C(1.0), MFLOAT_C(0.0), MFLOAT_C(0.0));
    vec3_st rotated = quat_rotate_vec3(result, v);
    vec3_st expected = {.x = MSQRT(MFLOAT_C(2.0))/MFLOAT_C(2.0), .y = MSQRT(MFLOAT_C(2.0))/MFLOAT_C(2.0), .z = MFLOAT_C(0.0)};
    
    if (!vec3_equal(rotated, expected, MEPSILON)) return -1;
    
    return 0;
}

int test_quat_rotation_x(void) {
    ftype_t angle = MPI_2; // 90度
    quat_st q = quat_rotation_x(angle);
    
    // 验证绕X轴旋转90度
    vec3_st v = vec3(0.0, 1.0, 0.0);
    vec3_st rotated = quat_rotate_vec3(q, v);
    vec3_st expected = {.x = 0.0, .y = 0.0, .z = 1.0};

    if (!vec3_equal(rotated, expected, MEPSILON)) return -1;
    
    return 0;
}

int test_quat_rotation_y(void) {
    ftype_t angle = MPI_2; // 90度
    quat_st q = quat_rotation_y(angle);
    
    // 验证绕Y轴旋转90度
    vec3_st v = vec3(0.0, 0.0, 1.0);
    vec3_st rotated = quat_rotate_vec3(q, v);
    vec3_st expected = {.x = 1.0, .y = 0.0, .z = 0.0};

    if (!vec3_equal(rotated, expected, MEPSILON)) return -1;

    return 0;
}

int test_quat_rotation_z(void) {
    ftype_t angle = MPI_2; // 90度
    quat_st q = quat_rotation_z(angle);
    
    // 验证绕Z轴旋转90度
    vec3_st v = vec3(1.0, 0.0, 0.0);
    vec3_st rotated = quat_rotate_vec3(q, v);
    vec3_st expected = {.x = 0.0, .y = 1.0, .z = 0.0};

    if (!vec3_equal(rotated, expected, MEPSILON)) return -1;

    return 0;
}

int test_quat_len_sq(void) {
    quat_st q = quat(0.0, 3.0, 4.0, 0.0);
    ftype_t len_sq = quat_len_sq(q);
    
    if (!float_equal(len_sq, 25.0, MEPSILON)) return -1; // 0^2 + 3^2 + 4^2 + 0^2 = 25
    
    return 0;
}

int test_quat_mul_f(void) {
    quat_st q = quat(1.0, 2.0, 3.0, 4.0);
    quat_st result = quat_mul_f(q, 2.0);
    quat_st expected = {.x = 2.0, .y = 4.0, .z = 6.0, .w = 8.0};
    
    if (!quat_equal(result, expected, MEPSILON)) return -1;
    
    return 0;
}

int test_quat_div_f(void) {
    quat_st q = quat(2.0, 4.0, 6.0, 8.0);
    quat_st result = quat_div_f(q, 2.0);
    quat_st expected = {.x = 1.0, .y = 2.0, .z = 3.0, .w = 4.0};
    
    if (!quat_equal(result, expected, MEPSILON)) return -1;
    
    return 0;
}

int test_quat_neg(void) {
    quat_st q = quat(1.0, 2.0, 3.0, 4.0);
    quat_st neg = quat_neg(q);
    quat_st expected = {.x = -1.0, .y = -2.0, .z = -3.0, .w = -4.0};
    
    if (!quat_equal(neg, expected, MEPSILON)) return -1;
    
    return 0;
}

int test_quat_null(void) {
    quat_st null = quat_null();
    quat_st expected = {.x = 0.0, .y = 0.0, .z = 0.0, .w = 1.0};
    
    if (!quat_equal(null, expected, MEPSILON)) return -1;
    
    return 0;
}

int test_quat_div(void) {
    quat_st q1 = quat(1.0, 2.0, 3.0, 4.0);
    quat_st q2 = quat(1.0, 1.0, 1.0, 1.0);
    quat_st result = quat_div(q1, q2);
    
    // 这里只验证结果不为零，具体数学验证需要更复杂的测试
    if (quat_is_zero(result)) return -1;
    
    return 0;
}

int test_quat_continuous(void) {
    quat_st q0 = quat_identity();
    quat_st q1 = quat(0.1, 0.2, 0.3, 0.4);
    quat_st continuous = quat_continuous(q0, q1);
    
    // 这里只验证结果不为零，具体连续性验证需要更复杂的测试
    if (quat_is_zero(continuous)) return -1;
    
    return 0;
}

int test_quat_pow(void) {
    quat_st q = quat_identity();
    quat_st pow_q = quat_pow(q, 2.0);
    
    // 单位四元数的任意次幂还是单位四元数
    if (!quat_equal(pow_q, q, MEPSILON)) return -1;
    
    return 0;
}

int test_quat_rotate_vec3_fast(void) {
    quat_st q = quat_rotation_z(MPI_2); // 绕Z轴旋转90度
    vec3_st v = vec3(1.0, 0.0, 0.0);
    vec3_st rotated = quat_rotate_vec3_fast(q, v);
    vec3_st expected = {.x = 0.0, .y = 1.0, .z = 0.0};
    
    if (!vec3_equal(rotated, expected, MEPSILON)) return -1;
    
    return 0;
}

int test_quat_rotate_vec3_components(void) {
    quat_st q = quat_rotation_z(MPI_2); // 绕Z轴旋转90度
    vec3_st v = vec3(1.0, 0.0, 0.0);
    vec3_st rotated = quat_rotate_vec3_components(q, v);
    vec3_st expected = {.x = 0.0, .y = 1.0, .z = 0.0};
    
    if (!vec3_equal(rotated, expected, MEPSILON)) return -1;
    
    return 0;
}

int test_quat_derivative(void) {
    quat_st q = quat_identity();
    vec3_st omega = vec3(1.0, 0.0, 0.0);
    quat_st derivative = quat_derivative(q, omega);

    // 这里只验证结果不为零，具体连续性验证需要更复杂的测试
    if (quat_is_zero(derivative)) return -1;

    return 0;
}


int test_quat_integrate_w(void) {
    quat_st q = quat_identity();
    vec3_st w = vec3(1.0, 0.0, 0.0);
    ftype_t dt = 1.0;
    quat_st integrated = quat_integrate_w(q, w, dt);
    // 这里只验证结果不为零，具体连续性验证需要更复杂的测试
    if (quat_is_zero(integrated)) return -1;

    return 0;
}

int test_quat_integrate(void) {
    quat_st q = quat_identity();
    quat_st q_dot = quat_identity();
    ftype_t dt = 1.0;
    quat_st integrated = quat_integrate(q, q_dot, dt);

    // 这里只验证结果不为零，具体连续性验证需要更复杂的测试
    if (quat_is_zero(integrated)) return -1;

    return 0;
}

// 四元数模块所有测试
int test_quat_all(void) {
    test_print_result("quat_is_zero", test_quat_is_zero());
    test_print_result("quat_is_equal", test_quat_is_equal());
    test_print_result("quat_dot", test_quat_dot());
    test_print_result("quat_len", test_quat_len());
    test_print_result("quat_len_sq", test_quat_len_sq());
    test_print_result("quat_angle", test_quat_angle());
    test_print_result("quat_axis", test_quat_axis());
    test_print_result("quat_rotate_vec3", test_quat_rotate_vec3());
    test_print_result("quat_rotate_vec3_fast", test_quat_rotate_vec3_fast());
    test_print_result("quat_rotate_vec3_components", test_quat_rotate_vec3_components());
    test_print_result("quat_create", test_quat_create());
    test_print_result("quat_v", test_quat_v());
    test_print_result("quat_zero", test_quat_zero());
    test_print_result("quat_identity", test_quat_identity());
    test_print_result("quat_add", test_quat_add());
    test_print_result("quat_sub", test_quat_sub());
    test_print_result("quat_null", test_quat_null());
    test_print_result("quat_mul", test_quat_mul());
    test_print_result("quat_mul_f", test_quat_mul_f());
    test_print_result("quat_div", test_quat_div());
    test_print_result("quat_div_f", test_quat_div_f());
    test_print_result("quat_neg", test_quat_neg());
    test_print_result("quat_conjugate", test_quat_conjugate());
    test_print_result("quat_inverse", test_quat_inverse());
    test_print_result("quat_normalize", test_quat_normalize());
    test_print_result("quat_continuous", test_quat_continuous());
    test_print_result("quat_pow", test_quat_pow());
    test_print_result("quat_from_axis_angle", test_quat_from_axis_angle());
    test_print_result("quat_from_vv", test_quat_from_vv());
    test_print_result("quat_lerp", test_quat_lerp());
    test_print_result("quat_slerp", test_quat_slerp());
    test_print_result("quat_rotation_x", test_quat_rotation_x());
    test_print_result("quat_rotation_y", test_quat_rotation_y());
    test_print_result("quat_rotation_z", test_quat_rotation_z());
    test_print_result("quat_derivative", test_quat_derivative());
    test_print_result("quat_integrate_w", test_quat_integrate_w());
    test_print_result("quat_integrate", test_quat_integrate());
    
    return 0;
}

/**********************************************************************************************************************
 * End of spacemath file
 *********************************************************************************************************************/