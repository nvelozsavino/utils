//
// Created by nico on 1/3/21.
//


#pragma once
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
typedef struct _node_t node_t;
struct _node_t{
    struct {
        node_t* parent;
        bool is_left;
    } parent;
    node_t* left;
    node_t* right;
    bool is_red;
    const void* value;
};
