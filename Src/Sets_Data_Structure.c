#include <Sets_Data_Structure.h>

size_t djb33x_hash(const char *key)
{
    size_t keylen = strlen(key);
    size_t hash = 5381;
    for (size_t i = 0; i < keylen; i++)
        hash = ((hash << 5) + hash) ^ key[i];
    return hash;
}

set_table_t *Set_TableNew(const size_t hashmap_size)
{
    set_table_t *table = malloc(sizeof(struct set_table));
    if (!table)
        return NULL;

    table->num_collision = 0;
    table->hashmap_size = hashmap_size;
    table->nodes = calloc(table->hashmap_size, sizeof(set_node_t *));
    if (!table->nodes)
    {
        free(table);
        return NULL;
    }
    return table;
}

set_node_t *Set_Insert(set_table_t *table, void *key, const size_t key_len)
{
    size_t hash = djb33x_hash(key);
    size_t index = hash % table->hashmap_size;
    if (Set_Search(table, key, index) != -1)
    {
        printf("already in\n");
        return NULL;
    }

    if (SLL_Append((singly_node_t **)&table->nodes[index], (void *)key, sizeof(set_node_t)) == 0)
        table->nodes[index]->key_len = key_len;
    else
    {
        printf("I found a collision at Index:[%d]\n\n", (int)index);
        table->num_collision++;
        set_node_t *current_node = (set_node_t *)SLL_GetTail((singly_node_t **)&table->nodes[index]);
        current_node->key_len = key_len;
        return current_node;
    }

    return table->nodes[index];
}

int Set_Search(set_table_t *table, void *key, size_t index)
{
    if (index == -1)
    {
        size_t hash = djb33x_hash(key);
        index = hash % table->hashmap_size;
    }

    singly_node_t *head_node = &table->nodes[index]->node;
    int linked_index = 0;

    while (head_node)
    {
        if (head_node->data == key)
        {
             printf("At index [%llu], in the [%d] th position of the Linked i found your Key: \"%s\"\n", index, linked_index, (char *)head_node->data);
            return linked_index;
        }
        linked_index++;
        head_node = head_node->linked_node;
    }
    printf("I Searched for [%s] and no Key corresponded found at Index [%d]\n", (char *)key, (int)index);
    return -1;
}

int Set_Remove(set_table_t *table, void *key)
{
    size_t hash = djb33x_hash(key);
    size_t index = hash % table->hashmap_size;
    SLL_Remove((singly_node_t **)&table->nodes[index], Set_Search(table, key, index));
    return 0;
}

