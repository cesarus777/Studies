#include <stdlib.h>

struct added_nodes_t {
    int n_added;
    int capacity;
    int *add_arr;
};

void push_device(int priority, int nodeid, struct schedarray_t schedarray, struct added_nodes_t added_nodes);

int find_priority(struct dagnode_t *topnode, struct schedarray_t schedarray, struct added_nodes_t added_nodes)
{
    if(topnode->nchilds == 0)
        return 0;
    int max_child_priority = 0;
    for(int i = 0; i < topnode->nchilds; ++i)
    {
        int new_child_priority = find_priority(topnode->childs[i], schedarray, added_nodes);
        push_device(new_child_priority, topnode->nodeid, schedarray, added_nodes);

        if(new_child_priority > max_child_priority)
            max_child_priority = new_child_priority;
    }

    return max_child_priority + 1;
}

int comp(const void *a, const void *b)
{
    int *x = (int *) a;
    int *y = (int *) b;
    if(*x < *y)
        return 1;
    if(*x > *y)
        return -1;
    return 0;
}

void push_node_add(int nodeid, struct added_nodes_t added_nodes)
{
    if(added_nodes.n_added == added_nodes.capacity)
    {
        added_nodes.capacity += 10;
        added_nodes.add_arr = (int *) realloc(added_nodes.add_arr, added_nodes.capacity * sizeof(int));
    }
    added_nodes.add_arr[added_nodes.n_added] = nodeid;
    added_nodes.n_added++;
    qsort(added_nodes.add_arr, added_nodes.n_added, sizeof(int), comp);
}

int node_add_check(int nodeid, struct added_nodes_t added_nodes)
{
    void *not_add = bsearch(&nodeid, added_nodes.add_arr, added_nodes.n_added, sizeof(int), &comp);
    if(not_add == NULL)
    {
        push_node_add(nodeid, added_nodes);
        return 1;
    }
    return 0;
}

void push_device(int priority, int nodeid, struct schedarray_t schedarray, struct added_nodes_t added_nodes)
{
    int add_check = node_add_check(nodeid, added_nodes);
    if(add_check == 0)
        return;
    
    int realloc_check = 0;
    while(priority > schedarray.ndevices)
    {
        realloc_check = 1;
        schedarray.ndevices++;
    }
    if(realloc_check)
        schedarray.devicesizes = (int *) realloc(schedarray.devicesizes, schedarray.ndevices * sizeof(int));
    schedarray.devicesizes[priority]++;
}

struct schedarray_t task_schedule(struct dagnode_t **topnodes, int ntopnodes)
{
    struct schedarray_t schedarray;
    if(ntopnodes == 0)
    {
        schedarray.ndevices = 0;
        schedarray.devicesizes = NULL;
        return schedarray;
    }

    schedarray.ndevices = 2; 
    schedarray.devicesizes = (int *) calloc(schedarray.ndevices, sizeof(int));

    struct added_nodes_t added_nodes;
    added_nodes.add_arr = (int *) calloc(2, sizeof(int));

    for(int i = 0; i < ntopnodes; ++i)
    {
        int priority = find_priority(topnodes[i], schedarray, added_nodes);
        push_device(priority, topnodes[i]->nodeid, schedarray, added_nodes);
    }

    free(added_nodes.add_arr);

    return schedarray;
}
