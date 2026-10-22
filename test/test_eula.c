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
 * @file test_eula.c
 * @brief 测试欧拉角等于函数实现文件
 * @author scilogyhunter
 * @date 2026.10.22
 * @version V0.1.3
 *
 * 本文件定义了测试欧拉角等于函数和全局变量，用于各个测试模块的实现。
 */

/*!
 * @defgroup test_eula_modify 修改记录 
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

/** @} */ /* end of group test_eula_modify */

#include "test_main.h"
#include <math.h>

// 辅助函数测试

int test_eula_is_zero(void) {
    eula_st zero = eula_zero();
    eula_st non_zero = eula(MPI_2, 0.0, 0.0);
    
    if (!eula_is_zero(zero)) return -1;
    if (eula_is_zero(non_zero)) return -1;
    
    return 0;
}

int test_eula(void) {
    eula_st e = eula(MPI_2, MPI_4, 0.0);
    eula_st expected = {.x = MPI_2, .y = MPI_4, .z = 0.0};
    
    if (!eula_equal(e, expected, MEPSILON)) return -1;
    
    return 0;
}

int test_eula_zero(void) {
    eula_st zero = eula_zero();
    eula_st expected = {.x = 0.0, .y = 0.0, .z = 0.0};
    
    if (!eula_equal(zero, expected, MEPSILON)) return -1;
    
    return 0;
}

int test_eula_add(void) {
    eula_st e0 = eula(MFLOAT_C(0.0), MFLOAT_C(0.0), MFLOAT_C(0.0));
    eula_st e1 = eula(MFLOAT_C(1.0), MFLOAT_C(1.0), MFLOAT_C(1.0));
    eula_st expected_add = eula(MFLOAT_C(1.0), MFLOAT_C(1.0), MFLOAT_C(1.0));
    eula_st result_add = eula_add(e0, e1);

    if (!eula_equal(result_add, expected_add, MEPSILON)) return -1;

    return 0;
}

int test_eula_sub(void) {
    eula_st e0 = eula(MFLOAT_C(0.0), MFLOAT_C(0.0), MFLOAT_C(0.0));
    eula_st e1 = eula(MFLOAT_C(1.0), MFLOAT_C(1.0), MFLOAT_C(1.0));
    eula_st expected_sub = eula(MFLOAT_C(-1.0), MFLOAT_C(-1.0), MFLOAT_C(-1.0));
    eula_st result_sub = eula_sub(e0, e1);

    if (!eula_equal(result_sub, expected_sub, MEPSILON)) return -1;
    return 0;
}
int test_eula_deg2rad(void) {
    eula_st deg = eula(90.0, 45.0, 0.0);
    eula_st rad = eula_deg2rad(deg);
    eula_st expected = {.x = MPI_2, .y = MPI_4, .z = 0.0};
    
    if (!eula_equal(rad, expected, MEPSILON)) return -1;
    
    return 0;
}

int test_eula_rad2deg(void) {
    eula_st rad = eula(MPI_2, MPI_4, 0.0);
    eula_st deg = eula_rad2deg(rad);
    eula_st expected = {.x = 90.0, .y = 45.0, .z = 0.0};
    
    if (!eula_equal(deg, expected, MEPSILON)) return -1;
    
    return 0;
}

int test_eula_v(void) {
    ftype_t v[3] = {MPI_2, MPI_4, 0.0};
    eula_st e = eula_v(v);
    eula_st expected = {.x = MPI_2, .y = MPI_4, .z = 0.0};
    
    if (!eula_equal(e, expected, MEPSILON)) return -1;
    
    return 0;
}

int test_eula_remainder(void) {
    eula_st e = eula(MFLOAT_C(3.1) * MPI, MFLOAT_C(2.0) * MPI, MFLOAT_C(-1.0) * MPI);
    eula_st normalized = eula_remainder(e, MPI);
    eula_st expected = {.x = MFLOAT_C(-0.9) * MPI, .y = MFLOAT_C(0.0), .z = MFLOAT_C(-1.0) * MPI};

    if (!eula_equal(normalized, expected, TEST_EPSILON)) return -1;
    
    return 0;
}

int test_eula_validate(void) {
    eula_st e = eula(MPI_2, MPI_4, 0.0);
    char *order = "zyx";
    
    if (!eula_validate(e, order)) return -1;
    
    return 0;
}

// 辅助函数模块所有测试
int test_eula_all(void) {
    test_print_result("eula_is_zero", test_eula_is_zero());
    test_print_result("eula", test_eula());
    test_print_result("eula_zero", test_eula_zero());
    test_print_result("eula_v", test_eula_v());
    test_print_result("eula_deg2rad", test_eula_deg2rad());
    test_print_result("eula_rad2deg", test_eula_rad2deg());
    test_print_result("eula_add", test_eula_add());
    test_print_result("eula_sub", test_eula_sub());
    test_print_result("eula_remainder", test_eula_remainder());
    test_print_result("eula_validate", test_eula_validate());
    
    return 0;
}

/**********************************************************************************************************************
 * End of spacemath file
 *********************************************************************************************************************/