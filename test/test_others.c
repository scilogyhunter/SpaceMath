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
 * @file test_others.c
 * @brief 测试辅助函数实现文件
 * @author scilogyhunter
 * @date 2026.10.22
 * @version V0.1.3
 *
 * 本文件定义了测试辅助函数和全局变量，用于各个测试模块的实现。
 */

/*!
 * @defgroup test_others_modify 修改记录
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

/** @} */ /* end of group test_others_modify */

#include "test_main.h"
#include <math.h>

// 辅助函数测试

int test_safe_is_equal(void) {
    // 测试边界值
    if (!safe_is_equal(0.0, 0.0)) return -1;
    if (safe_is_equal(0.0, 1.0)) return -1;
    if (!safe_is_equal(1.0, 1.0)) return -1;
    
    return 0;
}

int test_safe_is_equal_eps(void) {
    // 测试边界值
    if (!safe_is_equal_eps(0.0, 0.0, MEPSILON)) return -1;
    if (safe_is_equal_eps(0.0, 1.0, MEPSILON)) return -1;
    if (!safe_is_equal_eps(1.0, 1.0, MEPSILON)) return -1;

    return 0;
}

int test_safe_is_zero(void) {
    // 测试边界值
    if (!safe_is_zero(0.0)) return -1;
    if (safe_is_zero(1.0)) return -1;

    return 0;
}
int test_safe_asin(void) {
    // 测试边界值
    ftype_t result1 = safe_asin(1.0);
    ftype_t result2 = safe_asin(-1.0);
    ftype_t result3 = safe_asin(0.0);
    
    if (!float_equal(result1, MPI_2, MEPSILON)) return -1;
    if (!float_equal(result2, -MPI_2, MEPSILON)) return -1;
    if (!float_equal(result3, 0.0, MEPSILON)) return -1;
    
    return 0;
}

int test_safe_acos(void) {
    // 测试边界值
    ftype_t result1 = safe_acos(1.0);
    ftype_t result2 = safe_acos(-1.0);
    ftype_t result3 = safe_acos(0.0);
    
    if (!float_equal(result1, 0.0, MEPSILON)) return -1;
    if (!float_equal(result2, MPI, MEPSILON)) return -1;
    if (!float_equal(result3, MPI_2, MEPSILON)) return -1;
    
    return 0;
}

int test_safe_atan2(void) {
    // 测试各种情况
    ftype_t result1 = safe_atan2(MFLOAT_C(0.0), MFLOAT_C(1.0));
    ftype_t result2 = safe_atan2(MFLOAT_C(1.0), MFLOAT_C(0.0));
    ftype_t result3 = safe_atan2(MFLOAT_C(1.0), MFLOAT_C(1.0));

    if (!float_equal(result1, MFLOAT_C(0.0), MEPSILON)) return -1;
    if (!float_equal(result2, MPI_2, MEPSILON/1.5)) return -1;
    if (!float_equal(result3, MPI_4, MEPSILON/0.7)) return -1;
    
    return 0;
}

// 辅助函数模块所有测试
int test_others_all(void) {
    test_print_result("safe_is_equal", test_safe_is_equal());
    test_print_result("safe_is_equal_eps", test_safe_is_equal_eps());
    test_print_result("safe_is_zero", test_safe_is_zero());
    test_print_result("safe_asin", test_safe_asin());
    test_print_result("safe_acos", test_safe_acos());
    test_print_result("safe_atan2", test_safe_atan2());
    
    return 0;
}

/**********************************************************************************************************************
 * End of spacemath file
 *********************************************************************************************************************/