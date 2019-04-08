#include <stddef.h>

struct node_t *the_right(struct node_t *n) {
    while(n->right != NULL) n = n->right;
    return n;
}

struct node_t *to_dlist(struct node_t *top)
{
    struct node_t *res = NULL, *tmp = NULL;

    if (top == NULL)
        return res;

    if (top->left == NULL) {
        if(top->right == NULL)
            return top;
        tmp = to_dlist(top->right);
        top->right = tmp;
        tmp->left = top;
        return top;
    }

    if (top->left != NULL) {
            res = to_dlist(top->left);
            tmp = the_right(res);
            top->left = tmp;
            tmp->right = top;
        if (top->right != NULL) {
            top->right = to_dlist(top->right);
            top->right->left = top;
        }
        return res;
    }

    return res;
}
