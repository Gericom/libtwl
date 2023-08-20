#pragma once

enum
{
    RTOS_OBJECT_TYPE_MUTEX,
    RTOS_OBJECT_TYPE_EVENT
};

typedef struct rtos_object_t
{
    struct rtos_object_t* prev;
    struct rtos_object_t* next;
    u8 type;
} rtos_object_t;
