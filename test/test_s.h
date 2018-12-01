/**
 *
 * @file
 *
 *  PLASMA is a software package provided by:
 *  University of Tennessee, US,
 *  University of Manchester, UK.
 *
 * @generated from test/test_z.h, normal z -> s, Sat Oct 27 15:01:38 2018
 *
 **/
#ifndef TEST_S_H
#define TEST_S_H

#include "test.h"

//==============================================================================
// test routines
//==============================================================================

void test_sgemm_batch(param_value_t param[], bool run);
void test_ssymm_batch(param_value_t param[], bool run);
void test_ssyr2k_batch(param_value_t param[], bool run);
void test_ssyrk_batch(param_value_t param[], bool run);
void test_ssymm_batch(param_value_t param[], bool run);
void test_ssyr2k_batch(param_value_t param[], bool run);
void test_ssyrk_batch(param_value_t param[], bool run);
void test_strmm_batch(param_value_t param[], bool run);
void test_strsm_batch(param_value_t param[], bool run);


#endif // TEST_S_H
