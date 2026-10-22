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
 * @file test_rotation.c
 * @brief 旋转运算测试文件
 * @author scilogyhunter
 * @date 2026.10.22
 * @version V0.1.3
 *
 * 本文件实现了三维旋转运算的单元测试，验证了旋转矩阵、四元数和轴角表示之间的转换及旋转效果。
 */

/*!
 * @defgroup test_rotation_modify 修改记录
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

/** @} */ /* end of group test_rotation_modify */

#include "test_main.h"
#include <math.h>

// 旋转测试函数

int test_rotation_a2m(void) {
    axis_st a = axis(0.0, 0.0, 1.0, MPI_2); // 绕Z轴旋转90度
    mat3_st m = rotation_a2m(a);
    
    // 验证旋转效果
    vec3_st v = vec3(1.0, 0.0, 0.0);
    vec3_st rotated = mat3_mul_vec(m, v);
    vec3_st expected = {.x = 0.0, .y = 1.0, .z = 0.0};
    
    if (!vec3_equal(rotated, expected, MEPSILON)) return -1;
    
    return 0;
}

int test_rotation_a2q(void) {
    axis_st a = axis(0.0, 0.0, 1.0, MPI_2); // 绕Z轴旋转90度
    quat_st q = rotation_a2q(a);
    
    // 验证旋转效果
    vec3_st v = vec3(1.0, 0.0, 0.0);
    vec3_st rotated = quat_rotate_vec3(q, v);
    vec3_st expected = {.x = 0.0, .y = 1.0, .z = 0.0};
    
    if (!vec3_equal(rotated, expected, MEPSILON)) return -1;
    
    return 0;
}

int test_rotation_m2a(void) {
    mat3_st m = mat3_rotation_z(MPI_2); // 绕Z轴旋转90度
    axis_st axis = rotation_m2a(m);
    
    // 验证轴角
    axis_st expected = {.v3 = {.x = 0.0, .y = 0.0, .z = 1.0}, .angle = MPI_2};
    
    if (!axis_equal(axis, expected, MEPSILON)) return -1;
    
    return 0;
}

int test_rotation_m2q(void) {
    mat3_st m = mat3_rotation_z(MPI_2); // 绕Z轴旋转90度
    quat_st q = rotation_m2q(m);
    
    // 验证旋转效果
    vec3_st v = vec3(1.0, 0.0, 0.0);
    vec3_st rotated = quat_rotate_vec3(q, v);
    vec3_st expected = {.x = 0.0, .y = 1.0, .z = 0.0};
    
    if (!vec3_equal(rotated, expected, MEPSILON)) return -1;
    
    return 0;
}

int test_rotation_q2a(void) {
    quat_st q = quat_rotation_z(MPI_2); // 绕Z轴旋转90度
    axis_st axis = rotation_q2a(q);
    
    // 验证轴角
    axis_st expected = {.v3 = {.x = 0.0, .y = 0.0, .z = 1.0}, .angle = MPI_2};
    
    if (!axis_equal(axis, expected, MEPSILON)) return -1;
    
    return 0;
}

int test_rotation_q2m(void) {
    quat_st q = quat_rotation_z(MPI_2); // 绕Z轴旋转90度
    mat3_st m = rotation_q2m(q);
    
    // 验证旋转效果
    vec3_st v = vec3(1.0, 0.0, 0.0);
    vec3_st rotated = mat3_mul_vec(m, v);
    vec3_st expected = {.x = 0.0, .y = 1.0, .z = 0.0};
    
    if (!vec3_equal(rotated, expected, MEPSILON)) return -1;
    
    return 0;
}

int test_rotation_vv2q(void) {
    vec3_st from = vec3(1.0, 0.0, 0.0);
    vec3_st to = vec3(0.0, 1.0, 0.0);
    quat_st q = rotation_vv2q(to, from);
    
    // 验证旋转效果
    vec3_st rotated = quat_rotate_vec3(q, from);
    
    if (!vec3_equal(rotated, to, MEPSILON)) return -1;
    
    return 0;
}

int test_rotation_vv2m(void) {
    vec3_st from = vec3(1.0, 0.0, 0.0);
    vec3_st to = vec3(0.0, 1.0, 0.0);
    mat3_st m = rotation_vv2m(to, from);
    
    // 验证旋转效果
    vec3_st rotated = mat3_mul_vec(m, from);
    
    if (!vec3_equal(rotated, to, MEPSILON)) return -1;
    
    return 0;
}

int test_rotation_qq2q(void) {
    quat_st from = quat_identity();
    quat_st to = quat_rotation_z(MPI_2); // 绕Z轴旋转90度
    quat_st relative = rotation_qq2q(to, from);
    
    // 相对旋转应该等于目标旋转
    if (!quat_equal(relative, to, MEPSILON)) return -1;
    
    return 0;
}

int test_rotation_mm2m(void) {
    mat3_st from = mat3_identity();
    mat3_st to = mat3_rotation_z(MPI_2); // 绕Z轴旋转90度
    mat3_st relative = rotation_mm2m(to, from);
    
    // 相对旋转应该等于目标旋转
    if (!mat3_equal(relative, to, MEPSILON)) return -1;
    
    return 0;
}

int test_rotation_aRv(void) {
    axis_st a = axis(0.0, 0.0, 1.0, MPI_2); // 绕Z轴旋转90度
    vec3_st v = vec3(1.0, 0.0, 0.0);
    vec3_st rotated = rotation_aRv(a, v);
    vec3_st expected = {.x = 0.0, .y = 1.0, .z = 0.0};
    
    if (!vec3_equal(rotated, expected, MEPSILON)) return -1;
    
    return 0;
}

int test_rotation_eRv(void) {
    eula_st euler = eula(0.0, 0.0, MPI_2); // 绕Z轴旋转90度
    vec3_st v = vec3(1.0, 0.0, 0.0);
    vec3_st rotated = rotation_eRv(euler, v);
    vec3_st expected = {.x = 0.0, .y = 1.0, .z = 0.0};
    
    if (!vec3_equal(rotated, expected, MEPSILON)) return -1;
    
    return 0;
}

int test_rotation_mRv(void) {
    mat3_st m = mat3_rotation_z(MPI_2); // 绕Z轴旋转90度
    vec3_st v = vec3(1.0, 0.0, 0.0);
    vec3_st rotated = rotation_mRv(m, v);
    vec3_st expected = {.x = 0.0, .y = 1.0, .z = 0.0};
    
    if (!vec3_equal(rotated, expected, MEPSILON)) return -1;
    
    return 0;
}

int test_rotation_qRv(void) {
    quat_st q = quat_rotation_z(MPI_2); // 绕Z轴旋转90度
    vec3_st v = vec3(1.0, 0.0, 0.0);
    vec3_st rotated = rotation_qRv(q, v);
    vec3_st expected = {.x = 0.0, .y = 1.0, .z = 0.0};
    
    if (!vec3_equal(rotated, expected, MEPSILON)) return -1;
    
    return 0;
}

int test_rotation_aRq(void) {
    axis_st a = axis(0.0, 0.0, 1.0, MPI_2); // 绕Z轴旋转90度
    quat_st q = quat_identity();
    quat_st rotated = rotation_aRq(a, q);
    
    // 旋转后的四元数应该等于绕Z轴旋转90度的四元数
    quat_st expected = quat_rotation_z(MPI_2);
    
    if (!quat_equal(rotated, expected, MEPSILON)) return -1;
    
    return 0;
}

int test_rotation_eRq(void) {
    eula_st euler = eula(0.0, 0.0, MPI_4); // 绕Z轴旋转45度
    quat_st q = quat_identity();
    quat_st rotated = rotation_eRq(euler, q);
    
    // 旋转后的四元数应该等于绕Z轴旋转45度的四元数
    quat_st expected = quat_rotation_z(MPI_4);
    
    if (!quat_equal(rotated, expected, MEPSILON)) return -1;
    
    return 0;
}

int test_rotation_mRq(void) {
    mat3_st m = mat3_rotation_z(MPI_2); // 绕Z轴旋转90度
    quat_st q = quat_identity();
    quat_st rotated = rotation_mRq(m, q);
    
    // 旋转后的四元数应该等于绕Z轴旋转90度的四元数
    quat_st expected = quat_rotation_z(MPI_2);
    
    if (!quat_equal(rotated, expected, MEPSILON)) return -1;
    
    return 0;
}

int test_rotation_qRq(void) {
    quat_st rq = quat_rotation_z(MPI_2); // 绕Z轴旋转90度
    quat_st q = quat_identity();
    quat_st rotated = rotation_qRq(rq, q);
    
    // 旋转后的四元数应该等于绕Z轴旋转90度的四元数
    quat_st expected = quat_rotation_z(MPI_2);
    
    if (!quat_equal(rotated, expected, MEPSILON)) return -1;
    
    return 0;
}

// ==================== 基本旋转操作测试 ====================

int test_rotation_a_rvs(void) {
    axis_st a = axis(0.0, 0.0, 1.0, MPI_2); // 绕Z轴旋转90度
    axis_st result = rotation_a_rvs(a);
    
    // 期望结果：旋转轴取反，角度保持不变
    axis_st expected = axis(0.0, 0.0, -1.0, MPI_2);
    
    if (!axis_equal(result, expected, MEPSILON)) return -1;
    
    return 0;
}

int test_rotation_a_rx(void) {
    ftype_t angle = MPI_2;
    axis_st result = rotation_a_rx(angle);
    
    // 期望结果：绕X轴旋转90度的轴角
    axis_st expected = axis(1.0, 0.0, 0.0, MPI_2);
    
    if (!axis_equal(result, expected, MEPSILON)) return -1;
    
    return 0;
}

int test_rotation_a_ry(void) {
    ftype_t angle = MPI_2;
    axis_st result = rotation_a_ry(angle);
    
    // 期望结果：绕Y轴旋转90度的轴角
    axis_st expected = axis(0.0, 1.0, 0.0, MPI_2);
    
    if (!axis_equal(result, expected, MEPSILON)) return -1;
    
    return 0;
}

int test_rotation_a_rz(void) {
    ftype_t angle = MPI_2;
    axis_st result = rotation_a_rz(angle);
    
    // 期望结果：绕Z轴旋转90度的轴角
    axis_st expected = axis(0.0, 0.0, 1.0, MPI_2);
    
    if (!axis_equal(result, expected, MEPSILON)) return -1;
    
    return 0;
}

int test_rotation_e_rvs(void) {
    eula_st euler = eula(MPI_4, MPI_4, MPI_4);
    eula_st result = rotation_e_rvs(euler);
    
    // 期望结果：所有角度分量取反
    eula_st expected = eula(-MPI_4, -MPI_4, -MPI_4);
    
    if (!eula_equal(result, expected, MEPSILON)) return -1;
    
    return 0;
}

int test_rotation_e_rx(void) {
    ftype_t angle = MPI_2;
    eula_st result = rotation_e_rx(angle);
    
    // 期望结果：绕X轴旋转90度的欧拉角
    eula_st expected = eula(MPI_2, 0.0, 0.0);
    
    if (!eula_equal(result, expected, MEPSILON)) return -1;
    
    return 0;
}

int test_rotation_e_ry(void) {
    ftype_t angle = MPI_2;
    eula_st result = rotation_e_ry(angle);
    
    // 期望结果：绕Y轴旋转90度的欧拉角
    eula_st expected = eula(0.0, MPI_2, 0.0);
    
    if (!eula_equal(result, expected, MEPSILON)) return -1;
    
    return 0;
}

int test_rotation_e_rz(void) {
    ftype_t angle = MPI_2;
    eula_st result = rotation_e_rz(angle);
    
    // 期望结果：绕Z轴旋转90度的欧拉角
    eula_st expected = eula(0.0, 0.0, MPI_2);
    
    if (!eula_equal(result, expected, MEPSILON)) return -1;
    
    return 0;
}

int test_rotation_q_rvs(void) {
    quat_st q = quat_rotation_z(MPI_2); // 绕Z轴旋转90度
    quat_st result = rotation_q_rvs(q);
    
    // 期望结果：共轭四元数（逆旋转）
    quat_st expected = quat_conjugate(q);
    
    if (!quat_equal(result, expected, MEPSILON)) return -1;
    
    return 0;
}

int test_rotation_q_rx(void) {
    ftype_t angle = MPI_2;
    quat_st result = rotation_q_rx(angle);
    
    // 期望结果：绕X轴旋转90度的四元数
    quat_st expected = quat_rotation_x(MPI_2);
    
    if (!quat_equal(result, expected, MEPSILON)) return -1;
    
    return 0;
}

int test_rotation_q_ry(void) {
    ftype_t angle = MPI_2;
    quat_st result = rotation_q_ry(angle);
    
    // 期望结果：绕Y轴旋转90度的四元数
    quat_st expected = quat_rotation_y(MPI_2);
    
    if (!quat_equal(result, expected, MEPSILON)) return -1;
    
    return 0;
}

int test_rotation_q_rz(void) {
    ftype_t angle = MPI_2;
    quat_st result = rotation_q_rz(angle);
    
    // 期望结果：绕Z轴旋转90度的四元数
    quat_st expected = quat_rotation_z(MPI_2);
    
    if (!quat_equal(result, expected, MEPSILON)) return -1;
    
    return 0;
}

// ==================== 旋转转换函数测试 ====================

int test_rotation_e2m_order(void) {
    eula_st e = eula(0.0, 0.0, MPI_2); // 绕Z轴旋转90度
    char *order = "xyz";
    mat3_st m = rotation_e2m_order(e, order);
    
    // 验证旋转效果
    vec3_st v = vec3(1.0, 0.0, 0.0);
    vec3_st rotated = mat3_mul_vec(m, v);
    vec3_st expected = {.x = 0.0, .y = 1.0, .z = 0.0};
    
    if (!vec3_equal(rotated, expected, MEPSILON)) return -1;
    
    return 0;
}

int test_rotation_m2e_order(void) {
    mat3_st m = mat3_rotation_z(MPI_2); // 绕Z轴旋转90度
    char *order = "xyz";
    eula_st e = rotation_m2e_order(m, order);
    
    // 期望结果：绕Z轴旋转90度的欧拉角
    eula_st expected = eula(0.0, 0.0, MPI_2);
    
    if (!eula_equal(e, expected, MEPSILON)) return -1;
    
    return 0;
}

int test_rotation_q2e_order(void) {
    quat_st q = quat_rotation_z(MPI_2); // 绕Z轴旋转90度
    char *order = "xyz";
    eula_st e = rotation_q2e_order(q, order);

    // 期望结果：绕Z轴旋转90度的欧拉角  
    eula_st expected = eula(0.0, 0.0, MPI_2);

    if (!eula_equal(e, expected, MEPSILON)) return -1;

    return 0;
}

int test_rotation_e2q_order(void) {
    eula_st e = eula(0.0, 0.0, MPI_2); // 绕Z轴旋转90度
    char *order = "xyz";
    quat_st q = rotation_e2q_order(e, order);

    // 期望结果：绕Z轴旋转90度的四元数
    quat_st expected = quat_rotation_z(MPI_2);

    if (!quat_equal(q, expected, MEPSILON)) return -1;

    return 0;
}

int test_rotation_a2e(void) {
    axis_st a = axis(1.0, 0.0, 0.0, MPI_4); // 绕X轴旋转45度
    eula_st e = rotation_a2e(a);
    
    // 期望结果：绕X轴旋转45度的欧拉角
    eula_st expected = eula( MPI_4, 0.0, 0.0);

    if (!eula_equal(e, expected, MEPSILON)) return -1;
    
    return 0;
}

int test_rotation_e2a(void) {
    eula_st e = eula(0.0, 0.0, MPI_2); // 绕Z轴旋转90度
    axis_st a = rotation_e2a(e);
    
    // 期望结果：绕Z轴旋转90度的轴角
    axis_st expected = axis(0.0, 0.0, 1.0, MPI_2);
    
    if (!axis_equal(a, expected, MEPSILON)) return -1;
    
    return 0;
}

int test_rotation_q2e(void) {
    quat_st q = quat_rotation_z(MPI_4); // 绕Z轴旋转45度
    eula_st e = rotation_q2e(q);
    
    // 期望结果：绕Z轴旋转45度的欧拉角
    eula_st expected = eula(0.0, 0.0, MPI_4);
    
    if (!eula_equal(e, expected, MEPSILON)) return -1;
    
    return 0;
}

int test_rotation_vv2a(void) {
    vec3_st from = vec3(1.0, 0.0, 0.0);
    vec3_st to = vec3(0.0, 1.0, 0.0);
    axis_st a = rotation_vv2a(to, from);
    
    // 验证旋转效果
    vec3_st rotated = rotation_aRv(a, from);
    
    if (!vec3_equal(rotated, to, MEPSILON)) return -1;
    
    return 0;
}

int test_rotation_vv2e(void) {
    vec3_st from = vec3(1.0, 0.0, 0.0);
    vec3_st to = vec3(MSQRT1_2, MSQRT1_2, 0.0);
    eula_st e = rotation_vv2e(to, from);
    
    // 验证旋转效果
    vec3_st rotated = rotation_eRv(e, from);
    
    if (!vec3_equal(rotated, to, MEPSILON*1000)) return -1;
    
    return 0;
}

int test_rotation_aa2a(void) {
    axis_st from = axis_zero();
    axis_st to = axis(0.0, 0.0, 1.0, MPI_2); // 绕Z轴旋转90度
    axis_st relative = rotation_aa2a(to, from);
    
    // 相对旋转应该等于目标旋转
    if (!axis_equal(relative, to, MEPSILON)) return -1;
    
    return 0;
}

int test_rotation_ee2e(void) {
    eula_st from = eula_zero();
    eula_st to = eula(0.0, 0.0, MPI_4); // 绕Z轴旋转45度
    eula_st relative = rotation_ee2e(to, from);
    
    // 相对旋转应该等于目标旋转
    if (!eula_equal(relative, to, MEPSILON)) return -1;
    
    return 0;
}

// ==================== 旋转应用函数测试 ====================

int test_rotation_aRa(void) {
    axis_st ra = axis(0.0, 0.0, 1.0, MPI_2); // 绕Z轴旋转90度
    axis_st a = axis_zero();
    axis_st rotated = rotation_aRa(ra, a);
    
    // 旋转后的轴角应该等于旋转轴角
    if (!axis_equal(rotated, ra, MEPSILON)) return -1;
    
    return 0;
}

int test_rotation_eRa(void) {
    eula_st re = eula(0.0, 0.0, MPI_2); // 绕Z轴旋转90度
    axis_st a = axis_zero();
    axis_st rotated = rotation_eRa(re, a);
    
    // 旋转后的轴角应该等于绕Z轴旋转90度的轴角
    axis_st expected = axis(0.0, 0.0, 1.0, MPI_2);
    
    if (!axis_equal(rotated, expected, MEPSILON)) return -1;
    
    return 0;
}

int test_rotation_mRa(void) {
    mat3_st rm = mat3_rotation_z(MPI_2); // 绕Z轴旋转90度
    axis_st a = axis_zero();
    axis_st rotated = rotation_mRa(rm, a);
    
    // 旋转后的轴角应该等于绕Z轴旋转90度的轴角
    axis_st expected = axis(0.0, 0.0, 1.0, MPI_2);
    
    if (!axis_equal(rotated, expected, MEPSILON)) return -1;
    
    return 0;
}

int test_rotation_qRa(void) {
    quat_st rq = quat_rotation_z(MPI_2); // 绕Z轴旋转90度
    axis_st a = axis_zero();
    axis_st rotated = rotation_qRa(rq, a);
    
    // 旋转后的轴角应该等于绕Z轴旋转90度的轴角
    axis_st expected = axis(0.0, 0.0, 1.0, MPI_2);
    
    if (!axis_equal(rotated, expected, MEPSILON)) return -1;
    
    return 0;
}

int test_rotation_aRe(void) {
    axis_st ra = axis(1.0, 0.0, 0.0, MPI_4); // 绕X轴旋转45度
    eula_st e = eula_zero();
    eula_st rotated = rotation_aRe(ra, e);
    
    // 旋转后的欧拉角应该等于绕X轴旋转45度的欧拉角
    eula_st expected = eula(MPI_4, 0.0, 0.0);
    
    if (!eula_equal(rotated, expected, MEPSILON)) return -1;
    
    return 0;
}

int test_rotation_eRe(void) {
    eula_st re = eula(MPI_4, 0.0, 0.0); // 绕X轴旋转45度
    eula_st e = eula_zero();
    eula_st rotated = rotation_eRe(re, e);
    
    // 旋转后的欧拉角应该等于绕X轴旋转45度的欧拉角
    eula_st expected = eula(MPI_4, 0.0, 0.0);
    
    if (!eula_equal(rotated, expected, MEPSILON)) return -1;
    
    return 0;
}

int test_rotation_mRe(void) {
    mat3_st rm = mat3_rotation_z(MPI_4); // 绕Z轴旋转45度
    eula_st e = eula_zero();
    eula_st rotated = rotation_mRe(rm, e);
    
    // 旋转后的欧拉角应该等于绕Z轴旋转45度的欧拉角
    eula_st expected = eula(0.0, 0.0, MPI_4);
    
    if (!eula_equal(rotated, expected, MEPSILON)) return -1;
    
    return 0;
}

int test_rotation_qRe(void) {
    quat_st rq = quat_rotation_z(MPI_4); // 绕Z轴旋转45度
    eula_st e = eula_zero();
    eula_st rotated = rotation_qRe(rq, e);
    
    // 旋转后的欧拉角应该等于绕Z轴旋转45度的欧拉角
    eula_st expected = eula(0.0, 0.0, MPI_4);
    
    if (!eula_equal(rotated, expected, MEPSILON)) return -1;
    
    return 0;
}

int test_rotation_aRm(void) {
    axis_st ra = axis(0.0, 0.0, 1.0, MPI_2); // 绕Z轴旋转90度
    mat3_st m = mat3_identity();
    mat3_st rotated = rotation_aRm(ra, m);
    
    // 旋转后的矩阵应该等于绕Z轴旋转90度的矩阵
    mat3_st expected = mat3_rotation_z(MPI_2);
    
    if (!mat3_equal(rotated, expected, MEPSILON)) return -1;
    
    return 0;
}

int test_rotation_eRm(void) {
    eula_st re = eula(0.0, 0.0, MPI_2); // 绕Z轴旋转90度
    mat3_st m = mat3_identity();
    mat3_st rotated = rotation_eRm(re, m);
    
    // 旋转后的矩阵应该等于绕Z轴旋转90度的矩阵
    mat3_st expected = mat3_rotation_z(MPI_2);
    
    if (!mat3_equal(rotated, expected, MEPSILON)) return -1;
    
    return 0;
}

int test_rotation_mRm(void) {
    mat3_st rm = mat3_rotation_z(MPI_2); // 绕Z轴旋转90度
    mat3_st m = mat3_identity();
    mat3_st rotated = rotation_mRm(rm, m);
    
    // 旋转后的矩阵应该等于绕Z轴旋转90度的矩阵
    mat3_st expected = mat3_rotation_z(MPI_2);
    
    if (!mat3_equal(rotated, expected, MEPSILON)) return -1;
    
    return 0;
}

int test_rotation_qRm(void) {
    quat_st rq = quat_rotation_z(MPI_2); // 绕Z轴旋转90度
    mat3_st m = mat3_identity();
    mat3_st rotated = rotation_qRm(rq, m);
    
    // 旋转后的矩阵应该等于绕Z轴旋转90度的矩阵
    mat3_st expected = mat3_rotation_z(MPI_2);
    
    if (!mat3_equal(rotated, expected, MEPSILON)) return -1;
    
    return 0;
}

int test_rotation_m_rvs(void) {
    mat3_st m = mat3_rotation_z(MPI_2); // 绕Z轴旋转90度
    mat3_st result = rotation_m_rvs(m);
    
    // 期望结果：转置矩阵（逆旋转）
    mat3_st expected = mat3_transpose(m);
    
    if (!mat3_equal(result, expected, MEPSILON)) return -1;
    
    return 0;
}

int test_rotation_m_rx(void) {
    ftype_t angle = MPI_2;
    mat3_st result = rotation_m_rx(angle);
    
    // 期望结果：绕X轴旋转90度的矩阵
    mat3_st expected = mat3_rotation_x(MPI_2);
    
    if (!mat3_equal(result, expected, MEPSILON)) return -1;
    
    return 0;
}

int test_rotation_m_ry(void) {
    ftype_t angle = MPI_2;
    mat3_st result = rotation_m_ry(angle);
    
    // 期望结果：绕Y轴旋转90度的矩阵
    mat3_st expected = mat3_rotation_y(MPI_2);
    
    if (!mat3_equal(result, expected, MEPSILON)) return -1;
    
    return 0;
}

int test_rotation_m_rz(void) {
    ftype_t angle = MPI_2;
    mat3_st result = rotation_m_rz(angle);
    
    // 期望结果：绕Z轴旋转90度的矩阵
    mat3_st expected = mat3_rotation_z(MPI_2);
    
    if (!mat3_equal(result, expected, MEPSILON)) return -1;
    
    return 0;
}

int test_rotation_e2m(void) {
    eula_st e = eula(0.0, 0.0, MPI_2); // 绕Z轴旋转90度
    mat3_st m = rotation_e2m(e);
    
    // 验证旋转效果
    vec3_st v = vec3(1.0, 0.0, 0.0);
    vec3_st rotated = mat3_mul_vec(m, v);
    vec3_st expected = {.x = 0.0, .y = 1.0, .z = 0.0};
    
    if (!vec3_equal(rotated, expected, MEPSILON)) return -1;
    
    return 0;
}

int test_rotation_e2q(void) {
    eula_st e = eula(0.0, 0.0, MPI_2); // 绕Z轴旋转90度
    quat_st q = rotation_e2q(e);
    
    // 验证旋转效果
    vec3_st v = vec3(1.0, 0.0, 0.0);
    vec3_st rotated = quat_rotate_vec3(q, v);
    vec3_st expected = {.x = 0.0, .y = 1.0, .z = 0.0};
    
    if (!vec3_equal(rotated, expected, MEPSILON)) return -1;
    
    return 0;
}

int test_rotation_m2e(void) {
    mat3_st m = mat3_rotation_z(MPI_4); // 绕Z轴旋转45度
    eula_st e = rotation_m2e(m);
    
    // 期望结果：绕Z轴旋转45度的欧拉角
    eula_st expected = eula(0.0, 0.0, MPI_4);
    
    if (!eula_equal(e, expected, MEPSILON)) return -1;
    
    return 0;
}

// 旋转模块所有测试
int test_rotation_all(void) {
    
    // 基本旋转操作测试
    test_print_result("rotation_a_rvs", test_rotation_a_rvs());
    test_print_result("rotation_a_rx", test_rotation_a_rx());
    test_print_result("rotation_a_ry", test_rotation_a_ry());
    test_print_result("rotation_a_rz", test_rotation_a_rz());
    test_print_result("rotation_e_rvs", test_rotation_e_rvs());
    test_print_result("rotation_e_rx", test_rotation_e_rx());
    test_print_result("rotation_e_ry", test_rotation_e_ry());
    test_print_result("rotation_e_rz", test_rotation_e_rz());
    test_print_result("rotation_m_rvs", test_rotation_m_rvs());
    test_print_result("rotation_m_rx", test_rotation_m_rx());
    test_print_result("rotation_m_ry", test_rotation_m_ry());
    test_print_result("rotation_m_rz", test_rotation_m_rz());
    test_print_result("rotation_q_rvs", test_rotation_q_rvs());
    test_print_result("rotation_q_rx", test_rotation_q_rx());
    test_print_result("rotation_q_ry", test_rotation_q_ry());
    test_print_result("rotation_q_rz", test_rotation_q_rz());

    // 旋转转换函数测试
    test_print_result("rotation_e2m_order", test_rotation_e2m_order());
    test_print_result("rotation_m2e_order", test_rotation_m2e_order());
    test_print_result("rotation_e2q_order", test_rotation_e2q_order());
    test_print_result("rotation_q2e_order", test_rotation_q2e_order());


    test_print_result("rotation_a2e", test_rotation_a2e());
    test_print_result("rotation_a2m", test_rotation_a2m());
    test_print_result("rotation_a2q", test_rotation_a2q());
    test_print_result("rotation_e2a", test_rotation_e2a());
    test_print_result("rotation_e2m", test_rotation_e2m());
    test_print_result("rotation_e2q", test_rotation_e2q());
    test_print_result("rotation_m2a", test_rotation_m2a());
    test_print_result("rotation_m2e", test_rotation_m2e());
    test_print_result("rotation_m2q", test_rotation_m2q());
    test_print_result("rotation_q2a", test_rotation_q2a());
    test_print_result("rotation_q2e", test_rotation_q2e());
    test_print_result("rotation_q2m", test_rotation_q2m());

    test_print_result("rotation_vv2a", test_rotation_vv2a());
    test_print_result("rotation_vv2e", test_rotation_vv2e());
    test_print_result("rotation_vv2m", test_rotation_vv2m());
    test_print_result("rotation_vv2q", test_rotation_vv2q());

    test_print_result("rotation_aa2a", test_rotation_aa2a());
    test_print_result("rotation_ee2e", test_rotation_ee2e());
    test_print_result("rotation_mm2m", test_rotation_mm2m());
    test_print_result("rotation_qq2q", test_rotation_qq2q());
    
    // 旋转应用函数测试
    test_print_result("rotation_aRa", test_rotation_aRa());
    test_print_result("rotation_eRa", test_rotation_eRa());
    test_print_result("rotation_mRa", test_rotation_mRa());
    test_print_result("rotation_qRa", test_rotation_qRa());
    test_print_result("rotation_aRe", test_rotation_aRe());
    test_print_result("rotation_eRe", test_rotation_eRe());
    test_print_result("rotation_mRe", test_rotation_mRe());
    test_print_result("rotation_qRe", test_rotation_qRe());
    test_print_result("rotation_aRm", test_rotation_aRm());
    test_print_result("rotation_eRm", test_rotation_eRm());
    test_print_result("rotation_mRm", test_rotation_mRm());
    test_print_result("rotation_qRm", test_rotation_qRm());
    test_print_result("rotation_aRq", test_rotation_aRq());
    test_print_result("rotation_eRq", test_rotation_eRq());
    test_print_result("rotation_mRq", test_rotation_mRq());
    test_print_result("rotation_qRq", test_rotation_qRq());

    test_print_result("rotation_aRv", test_rotation_aRv());
    test_print_result("rotation_eRv", test_rotation_eRv());
    test_print_result("rotation_mRv", test_rotation_mRv());
    test_print_result("rotation_qRv", test_rotation_qRv());
    
    return 0;
}

/**********************************************************************************************************************
 * End of spacemath file
 *********************************************************************************************************************/