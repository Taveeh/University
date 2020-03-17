//
// Created by Octavian Custura on 16/03/2020.
//

#ifndef ASSIGNMENT_3_TESTDOMAIN_H
#define ASSIGNMENT_3_TESTDOMAIN_H

#include "domain.h"

void testAllDomain();

void test_getCatalogueNumber_ValidInput_UnsignedInt();

void test_getCatalogueNumber_InvalidInput_MinusOne();

void test_getYearsOfStorage_ValidInput_UnsignedInt();

void test_getYearsOfStorage_InvalidInput_MinusOne();

void test_getStateOfDeterioration_ValidInput_CharPointer();

void test_getStateOfDeterioration_InvalidInput_NULL();

void test_getMapType_ValidInput_CharPointer();

void test_getMapType_InvalidInput_NULL();

void test_changeStateOfDeterioration_ValidInput_StateOfDeteriorationModified();

void test_changeStateOfDeterioration_InvalidInput_StateOfDeteriorationNotModified();

void test_changeMapType_ValidInput_MapTypeModified();

void test_changeMapType_InvalidInput_MapTypeNotModified();

void test_changeYearsOfStorage_ValidInput_YearsOfStorageModified();

void test_changeYearsOfStorage_InvalidInput_YearsOfStorageNotModified();


#endif //ASSIGNMENT_3_TESTDOMAIN_H
