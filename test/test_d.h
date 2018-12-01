/**
 *
 * @file
 *
 *  PLASMA is a software package provided by:
 *  University of Tennessee, US,
 *  University of Manchester, UK.
 *
 * @generated from test/test_z.h, normal z -> d, Sat Oct 27 15:01:38 2018
 *
 **/
#ifndef TEST_D_H
#define TEST_D_H

#include "test.h"

//==============================================================================
// test routines
//==============================================================================

void test_dgemm_batch(param_value_t param[], bool run);
void test_dsymm_batch(param_value_t param[], bool run);
void test_dsyr2k_batch(param_value_t param[], bool run);
void test_dsyrk_batch(param_value_t param[], bool run);
void test_dsymm_batch(param_value_t param[], bool run);
void test_dsyr2k_batch(param_value_t param[], bool run);
void test_dsyrk_batch(param_value_t param[], bool run);
void test_dtrmm_batch(param_value_t param[], bool run);
void test_dtrsm_batch(param_value_t param[], bool run);


#endif // TEST_D_H
