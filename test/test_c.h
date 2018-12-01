/**
 *
 * @file
 *
 *  PLASMA is a software package provided by:
 *  University of Tennessee, US,
 *  University of Manchester, UK.
 *
 * @generated from test/test_z.h, normal z -> c, Sat Oct 27 15:01:38 2018
 *
 **/
#ifndef TEST_C_H
#define TEST_C_H

#include "test.h"

//==============================================================================
// test routines
//==============================================================================

void test_cgemm_batch(param_value_t param[], bool run);
void test_chemm_batch(param_value_t param[], bool run);
void test_cher2k_batch(param_value_t param[], bool run);
void test_cherk_batch(param_value_t param[], bool run);
void test_csymm_batch(param_value_t param[], bool run);
void test_csyr2k_batch(param_value_t param[], bool run);
void test_csyrk_batch(param_value_t param[], bool run);
void test_ctrmm_batch(param_value_t param[], bool run);
void test_ctrsm_batch(param_value_t param[], bool run);


#endif // TEST_C_H
