#pragma once

enum node_kind_t { NODE_OP, NODE_VAL };

struct node_data_t {
    enum node_kind_t k;
    union {
        enum operation op;
        int d;
    } u;
};

struct tree_t {
    struct node_data_t data;
    struct tree_t *left;
    struct tree_t *right;
    struct tree_t *parent;
};
