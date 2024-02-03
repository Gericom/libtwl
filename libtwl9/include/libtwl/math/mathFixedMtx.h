#pragma once
#include "mathFixed.h"
#include "mathVec3.h"

typedef union
{
    fx32 elements[3][3];
    vec3_t rows[3];
} mtx33_t;

typedef union
{
    fx32 elements[4][3];
    vec3_t rows[4];
} mtx43_t;

typedef struct
{
    fx32 elements[4][4];
} mtx44_t;
