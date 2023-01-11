#include <string.h>
#include <..\Singly_Linked_List\Include\Singly_Linked_List.h>


typedef struct set_node set_node_t;
typedef struct set_table set_table_t;

size_t djb33x_hash(const char *key);
int Set_Remove(set_table_t *table, void *key);
set_table_t *Set_TableNew(const size_t hashmap_size);
int Set_Search(set_table_t *table, void *key, size_t index);
set_node_t *Set_Insert(set_table_t *table, void *key, const size_t key_len);

struct set_node
{
    singly_node_t node;
    size_t key_len;
};

struct set_table
{
    set_node_t **nodes;
    size_t hashmap_size;
    int num_collision;
};
