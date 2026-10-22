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
 * @file test_matrix.c
 * @brief 矩阵运算测试文件
 * @author scilogyhunter
 * @date 2026.10.22
 * @version V0.1.3
 *
 * 本文件实现了3x3矩阵运算的单元测试，验证了矩阵的创建、比较、行列式、迹、乘法等基本功能。
 */

/*!
 * @defgroup test_matrix_modify 修改记录
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

/** @} */ /* end of group test_matrix_modify */

#include "test_main.h"
#include <math.h>

// 矩阵测试函数

int test_mat3_is_zero(void) {
    mat3_st zero = mat3_zero();
    mat3_st non_zero = mat3_identity();
    
    if (!mat3_is_zero(zero)) return -1;
    if (mat3_is_zero(non_zero)) return -1;
    
    return 0;
}

int test_mat3_is_identity(void) {
    mat3_st identity = mat3_identity();
    mat3_st non_identity = mat3_zero();
    
    if (!mat3_is_identity(identity)) return -1;
    if (mat3_is_identity(non_identity)) return -1;
    
    return 0;
}

int test_mat3_is_equal(void) {
    mat3_st m1 = mat3_identity();
    mat3_st m2 = mat3_identity();
    mat3_st m3 = mat3_zero();
    
    if (!mat3_is_equal(m1, m2)) return -1;
    if (mat3_is_equal(m1, m3)) return -1;
    
    return 0;
}

int test_mat3_det(void) {
    mat3_st identity = mat3_identity();
    ftype_t det = mat3_det(identity);
    
    if (!float_equal(det, 1.0, MEPSILON)) return -1;
    
    return 0;
}

int test_mat3_trace(void) {
    mat3_st identity = mat3_identity();
    ftype_t trace = mat3_trace(identity);
    
    if (!float_equal(trace, 3.0, MEPSILON)) return -1;
    
    return 0;
}

int test_mat3_mul_vec(void) {
    mat3_st identity = mat3_identity();
    vec3_st v = vec3(1.0, 2.0, 3.0);
    vec3_st result = mat3_mul_vec(identity, v);
    
    if (!vec3_equal(result, v, MEPSILON)) return -1;
    
    return 0;
}

int test_mat3_create(void) {
    mat3_st m = mat3(1.0, 0.0, 0.0,
                     0.0, 1.0, 0.0,
                     0.0, 0.0, 1.0);
    
    if (!mat3_is_identity(m)) return -1;
    
    return 0;
}

int test_mat3_v(void) {
    ftype_t v[9] = {1.0, 0.0, 0.0,
                    0.0, 1.0, 0.0,
                    0.0, 0.0, 1.0};
    mat3_st m = mat3_v(v);
    
    if (!mat3_is_identity(m)) return -1;
    
    return 0;
}

int test_mat3_zero(void) {
    mat3_st zero = mat3_zero();
    
    for (int i = 0; i < 9; i++) {
        if (!float_equal(zero.v[i], 0.0, MEPSILON)) return -1;
    }
    
    return 0;
}

int test_mat3_one(void) {
    mat3_st one = mat3_one();
    
    for (int i = 0; i < 9; i++) {
        if (!float_equal(one.v[i], 1.0, MEPSILON)) return -1;
    }
    
    return 0;
}

int test_mat3_identity(void) {
    mat3_st identity = mat3_identity();
    mat3_st expected = mat3(1.0, 0.0, 0.0,
                            0.0, 1.0, 0.0,
                            0.0, 0.0, 1.0);

    if (!mat3_equal(identity, expected, MEPSILON)) return -1;

    return 0;
}

int test_mat3_transpose(void) {
    mat3_st m = mat3(1.0, 2.0, 3.0,
                     4.0, 5.0, 6.0,
                     7.0, 8.0, 9.0);
    mat3_st transposed = mat3_transpose(m);
    
    mat3_st expected = mat3(1.0, 4.0, 7.0,
                           2.0, 5.0, 8.0,
                           3.0, 6.0, 9.0);
    
    if (!mat3_equal(transposed, expected, MEPSILON)) return -1;
    
    return 0;
}

int test_mat3_inverse(void) {
    mat3_st identity = mat3_identity();
    mat3_st inverse = mat3_inverse(identity);
    
    if (!mat3_equal(inverse, identity, MEPSILON)) return -1;
    
    return 0;
}

int test_mat3_negate(void) {
    mat3_st m = mat3_identity();
    mat3_st negated = mat3_negate(m);
    
    for (int i = 0; i < 9; i++) {
        if (!float_equal(negated.v[i], -m.v[i], MEPSILON)) return -1;
    }
    
    return 0;
}

int test_mat3_add(void) {
    mat3_st m1 = mat3_identity();
    mat3_st m2 = mat3_identity();
    mat3_st result = mat3_add(m1, m2);
    
    for (int i = 0; i < 9; i++) {
        if (!float_equal(result.v[i], m1.v[i] + m2.v[i], MEPSILON)) return -1;
    }
    
    return 0;
}

int test_mat3_sub(void) {
    mat3_st m1 = mat3_identity();
    mat3_st m2 = mat3_identity();
    mat3_st result = mat3_sub(m1, m2);
    
    for (int i = 0; i < 9; i++) {
        if (!float_equal(result.v[i], m1.v[i] - m2.v[i], MEPSILON)) return -1;
    }
    
    return 0;
}

int test_mat3_mul(void) {
    mat3_st m1 = mat3_identity();
    mat3_st m2 = mat3_identity();
    mat3_st result = mat3_mul(m1, m2);
    
    if (!mat3_equal(result, m1, MEPSILON)) return -1;
    
    return 0;
}

int test_mat3_scale(void) {
    mat3_st m = mat3_identity();
    mat3_st scaled = mat3_scale(m, 2.0);
    
    for (int i = 0; i < 9; i++) {
        if (!float_equal(scaled.v[i], m.v[i] * 2.0, MEPSILON)) return -1;
    }
    
    return 0;
}

int test_mat3_rotation_x(void) {
    ftype_t angle = MPI_2;  // 90度
    mat3_st rotation = mat3_rotation_x(angle);
    
    // 绕X轴旋转90度，Y轴应该变成Z轴，Z轴应该变成-Y轴
    vec3_st y_axis = vec3(0.0, 1.0, 0.0);
    vec3_st z_axis = vec3(0.0, 0.0, 1.0);
    
    vec3_st rotated_y = mat3_mul_vec(rotation, y_axis);
    vec3_st rotated_z = mat3_mul_vec(rotation, z_axis);
    
    vec3_st expected_y = vec3(0.0, 0.0, 1.0);
    vec3_st expected_z = vec3(0.0, -1.0, 0.0);
    
    if (!vec3_equal(rotated_y, expected_y, MEPSILON)) return -1;
    if (!vec3_equal(rotated_z, expected_z, MEPSILON)) return -1;
    
    return 0;
}

int test_mat3_rotation_y(void) {
    ftype_t angle = MPI_2;  // 90度
    mat3_st rotation = mat3_rotation_y(angle);
    
    // 绕Y轴旋转90度，X轴应该变成Z轴，Z轴应该变成-X轴
    vec3_st x_axis = vec3(1.0, 0.0, 0.0);
    vec3_st z_axis = vec3(0.0, 0.0, 1.0);
    
    vec3_st rotated_x = mat3_mul_vec(rotation, x_axis);
    vec3_st rotated_z = mat3_mul_vec(rotation, z_axis);
    
    vec3_st expected_x = vec3(0.0, 0.0, -1.0);
    vec3_st expected_z = vec3(1.0, 0.0, 0.0);
    
    if (!vec3_equal(rotated_x, expected_x, MEPSILON)) return -1;
    if (!vec3_equal(rotated_z, expected_z, MEPSILON)) return -1;
    
    return 0;
}

int test_mat3_rotation_z(void) {
    ftype_t angle = MPI_2;  // 90度
    mat3_st rotation = mat3_rotation_z(angle);
    
    // 绕Z轴旋转90度，X轴应该变成Y轴，Y轴应该变成-X轴
    vec3_st x_axis = vec3(1.0, 0.0, 0.0);
    vec3_st y_axis = vec3(0.0, 1.0, 0.0);
    
    vec3_st rotated_x = mat3_mul_vec(rotation, x_axis);
    vec3_st rotated_y = mat3_mul_vec(rotation, y_axis);
    
    vec3_st expected_x = vec3(0.0, 1.0, 0.0);
    vec3_st expected_y = vec3(-1.0, 0.0, 0.0);
    
    if (!vec3_equal(rotated_x, expected_x, MEPSILON)) return -1;
    if (!vec3_equal(rotated_y, expected_y, MEPSILON)) return -1;
    
    return 0;
}

int test_mat3_lerp(void) {
    mat3_st from = mat3_zero();
    mat3_st to = mat3_identity();
    mat3_st result = mat3_lerp(from, to, 0.5);
    
    for (int i = 0; i < 9; i++) {
        ftype_t expected = from.v[i] + (to.v[i] - from.v[i]) * 0.5;
        if (!float_equal(result.v[i], expected, MEPSILON)) return -1;
    }
    
    return 0;
}

int test_mat3_add_f(void) {
    mat3_st m = mat3_identity();
    mat3_st result = mat3_add_f(m, 2.0);
    
    for (int i = 0; i < 9; i++) {
        ftype_t expected = m.v[i] + 2.0;
        if (!float_equal(result.v[i], expected, MEPSILON)) return -1;
    }
    
    return 0;
}

int test_mat3_sub_f(void) {
    mat3_st m = mat3_identity();
    mat3_st result = mat3_sub_f(m, 1.0);
    
    for (int i = 0; i < 9; i++) {
        ftype_t expected = m.v[i] - 1.0;
        if (!float_equal(result.v[i], expected, MEPSILON)) return -1;
    }
    
    return 0;
}

int test_mat3_mul_f(void) {
    mat3_st m = mat3_identity();
    mat3_st result = mat3_mul_f(m, 2.0);
    
    for (int i = 0; i < 9; i++) {
        ftype_t expected = m.v[i] * 2.0;
        if (!float_equal(result.v[i], expected, MEPSILON)) return -1;
    }
    
    return 0;
}

int test_mat3_is_diagonal(void) {
    mat3_st diagonal = mat3(1.0, 0.0, 0.0,
                           0.0, 2.0, 0.0,
                           0.0, 0.0, 3.0);
    mat3_st non_diagonal = mat3(1.0, 2.0, 0.0,
                               0.0, 2.0, 0.0,
                               0.0, 0.0, 3.0);
    
    if (!mat3_is_diagonal(diagonal)) return -1;
    if (mat3_is_diagonal(non_diagonal)) return -1;
    
    return 0;
}

int test_mat3_is_one(void) {
    mat3_st one = mat3_one();
    mat3_st non_one = mat3_identity();
    
    if (!mat3_is_one(one)) return -1;
    if (mat3_is_one(non_one)) return -1;
    
    return 0;
}

int test_mat3_is_symmetric(void) {
    mat3_st symmetric = mat3(1.0, 2.0, 3.0,
                            2.0, 4.0, 5.0,
                            3.0, 5.0, 6.0);
    mat3_st non_symmetric = mat3(1.0, 2.0, 3.0,
                                4.0, 5.0, 6.0,
                                7.0, 8.0, 9.0);
    
    if (!mat3_is_symmetric(symmetric)) return -1;
    if (mat3_is_symmetric(non_symmetric)) return -1;
    
    return 0;
}

int test_mat3_is_orthogonal(void) {
    mat3_st orthogonal = mat3_identity();
    mat3_st non_orthogonal = mat3_one();
    
    if (!mat3_is_orthogonal(orthogonal)) return -1;
    if (mat3_is_orthogonal(non_orthogonal)) return -1;
    
    return 0;
}

int test_mat3_norm(void) {
    mat3_st m = mat3_identity();
    ftype_t norm = mat3_norm(m, 2); // Frobenius norm
    
    if (!float_equal(norm, 1, MEPSILON)) return -1;
    
    return 0;
}

int test_mat3_cond(void) {
    mat3_st identity = mat3_identity();
    ftype_t cond = mat3_cond(identity);
    
    // 单位矩阵的条件数应该接近1（因为||I|| * ||I⁻¹|| = √3 * √3 = 3）
    if (!float_equal(cond, 3.0, 1e-12)) return -1;
    
    return 0;
}

int test_mat3_exp(void) {
    mat3_st zero = mat3_zero();
    mat3_st exp_zero = mat3_exp(zero);
    
    // 零矩阵的指数应该是单位矩阵
    if (!mat3_equal(exp_zero, mat3_identity(), MEPSILON)) return -1;
    
    return 0;
}

int test_mat3_log(void) {
    mat3_st identity = mat3_identity();
    mat3_st log_identity = mat3_log(identity);
    
    // 单位矩阵的对数应该是零矩阵
    if (!mat3_equal(log_identity, mat3_zero(), MEPSILON)) return -1;
    
    return 0;
}

int test_mat3_pow(void) {
    mat3_st identity = mat3_identity();
    mat3_st pow_identity = mat3_pow(identity, 2.0);
    
    // 单位矩阵的任意次幂还是单位矩阵
    if (!mat3_equal(pow_identity, identity, MEPSILON)) return -1;
    
    return 0;
}

int test_mat3_scale_matrix(void) {
    mat3_st scale = mat3_scale_matrix(2.0, 3.0, 4.0);
    mat3_st expected = mat3(2.0, 0.0, 0.0,
                            0.0, 3.0, 0.0,
                            0.0, 0.0, 4.0);

    if (!mat3_equal(scale, expected, MEPSILON)) return -1;

    return 0;
}

int test_mat3_orthonormalization(void) {
    mat3_st basis = mat3(1.0, 0.0, 0.0,
                        0.0, 1.0, 0.0,
                        0.0, 0.0, 1.0);
    mat3_st orthonormal = mat3_orthonormalization(basis);
    
    // 已经是正交基，应该保持不变
    if (!mat3_equal(orthonormal, basis, MEPSILON)) return -1;
    
    return 0;
}

int test_mat3_vv(void) {
    ftype_t vv[3][3] = {{1.0, 0.0, 0.0},
                        {0.0, 1.0, 0.0},
                        {0.0, 0.0, 1.0}};
    mat3_st m = mat3_vv(vv);
    
    if (!mat3_is_identity(m)) return -1;
    
    return 0;
}

// 矩阵模块所有测试
int test_matrix_all(void) {
    test_print_result("mat3_is_zero", test_mat3_is_zero());
    test_print_result("mat3_is_identity", test_mat3_is_identity());
    test_print_result("mat3_is_equal", test_mat3_is_equal());
    test_print_result("mat3_is_diagonal", test_mat3_is_diagonal());
    test_print_result("mat3_is_one", test_mat3_is_one());
    test_print_result("mat3_is_symmetric", test_mat3_is_symmetric());
    test_print_result("mat3_is_orthogonal", test_mat3_is_orthogonal());
    test_print_result("mat3_det", test_mat3_det());
    test_print_result("mat3_trace", test_mat3_trace());
    test_print_result("mat3_norm", test_mat3_norm());
    test_print_result("mat3_cond", test_mat3_cond());
    test_print_result("mat3_mul_vec", test_mat3_mul_vec());
    test_print_result("mat3_create", test_mat3_create());
    test_print_result("mat3_v", test_mat3_v());
    test_print_result("mat3_vv", test_mat3_vv());
    test_print_result("mat3_zero", test_mat3_zero());
    test_print_result("mat3_one", test_mat3_one());
    test_print_result("mat3_identity", test_mat3_identity());
    test_print_result("mat3_transpose", test_mat3_transpose());
    test_print_result("mat3_inverse", test_mat3_inverse());
    test_print_result("mat3_negate", test_mat3_negate());
    test_print_result("mat3_add", test_mat3_add());
    test_print_result("mat3_add_f", test_mat3_add_f());
    test_print_result("mat3_sub", test_mat3_sub());
    test_print_result("mat3_sub_f", test_mat3_sub_f());
    test_print_result("mat3_mul", test_mat3_mul());
    test_print_result("mat3_mul_f", test_mat3_mul_f());
    test_print_result("mat3_scale", test_mat3_scale());
    test_print_result("mat3_scale_matrix", test_mat3_scale_matrix());
    test_print_result("mat3_exp", test_mat3_exp());
    test_print_result("mat3_log", test_mat3_log());
    test_print_result("mat3_pow", test_mat3_pow());
    test_print_result("mat3_rotation_x", test_mat3_rotation_x());
    test_print_result("mat3_rotation_y", test_mat3_rotation_y());
    test_print_result("mat3_rotation_z", test_mat3_rotation_z());
    test_print_result("mat3_lerp", test_mat3_lerp());
    test_print_result("mat3_orthonormalization", test_mat3_orthonormalization());
    
    return 0;
}

/**********************************************************************************************************************
 * End of spacemath file
 *********************************************************************************************************************/