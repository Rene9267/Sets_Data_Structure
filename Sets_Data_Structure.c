#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include "Single_Linked_List.c"

#define NODE struct set_node *
#define Sets struct set_table *

typedef struct set_node
{
    struct set_node *next;
    void *key;
    size_t key_len;
} Set_node_t;

typedef struct set_table
{
    struct set_node **nodes;
    size_t hashmap_size;
    int num_collision;
} Set_Table_t;

int Search(Sets table, void *key, size_t index);

size_t KeyLenght(void *key)
{
    return strlen(key);
}

size_t djb33x_hash(const char *key)
{
    size_t keylen = KeyLenght((void *)key);
    size_t hash = 5381;
    for (size_t i = 0; i < keylen; i++)
    {
        hash = ((hash << 5) + hash) ^ key[i];
    }
    return hash;
}

struct set_table *set_table_new(const size_t hashmap_size)
{
    struct set_table *table = malloc(sizeof(struct set_table));
    if (!table)
    {
        return NULL;
    }
    table->num_collision = 0;
    table->hashmap_size = hashmap_size;
    table->nodes = calloc(table->hashmap_size, sizeof(struct set_node *));
    if (!table->nodes)
    {
        free(table);
        return NULL;
    }
    return table;
}

NODE set_insert(struct set_table *table, void *key, const size_t key_len)
{
    size_t hash = djb33x_hash(key);
    size_t index = hash % table->hashmap_size;
    if (Search(table, key, index) != -1)
    {
        printf("already in\n");
        return NULL;
    }

    if (Append((Singly_node_t **)&table->nodes[index], (void *)key, sizeof(struct set_node)) == 0)
        table->nodes[index]->key_len = key_len;
    else
    {
        printf("I found a collision at Index:[%d]\n\n", (int)index);
        table->num_collision++;
        struct set_node *current_node = (struct set_node *)Get_Tail((Singly_node_t **)&table->nodes[index]);
        current_node->key_len = key_len;
        return current_node;
    }

    return table->nodes[index];
}

int Search(Sets table, void *key, size_t index)
{
    if (index == -1)
    {
        size_t hash = djb33x_hash(key);
        index = hash % table->hashmap_size;
       
    }
    struct set_node **current_node = table->nodes;
    struct set_node *head_node = table->nodes[index];
    int linked_index = 0;

    while (head_node)
    {
        if (head_node->key == key)
        {
            printf("At index [%llu], in the [%d] th position of the Linked i found your Key: \"%s\"\n", index, linked_index, (char *)head_node->key);
            return linked_index;
        }
        linked_index++;
        head_node = head_node->next;
    }
    printf("I Searched for [%s] and no Key corresponded found at Index [%d]\n", (char *)key, (int)index);
    return -1;
}

int Remove_Sets(struct set_table *table, void *key)
{
    size_t hash = djb33x_hash(key);
    size_t index = hash % table->hashmap_size;
    Remove((Singly_node_t **)&table->nodes[index], Search(table, key, index));
    return 0;
}

#pragma region Main
// int main(int argc, char const *argv[])
// {
//     struct set_table *sets = set_table_new(2);

//     set_insert(sets, "Hello", 5);
//     set_insert(sets, "Hello World", 11);
//     set_insert(sets, "This is me", 10);
//     set_insert(sets, "New", 3);
//     set_insert(sets, "Computer", 9);
//     set_insert(sets, "Hello", 5);
//     set_insert(sets, "Hello mauro", 11);
//     set_insert(sets, "Hello isma", 10);
//     set_insert(sets, "Hello lorenzo", 13);

//     Remove_Sets(sets, "Hello mauro");
//     Remove_Sets(sets, "Hello");
//     struct set_node **current_node = sets->nodes;
//     size_t index = 0;
//     struct set_node *head_node;
//     for (index = 0; index < sets->hashmap_size; index++)
//     {
//         if ((head_node = current_node[index]))
//         {
//             printf("Index [%llu]:\n", index);
//             struct set_node *current_node = head_node;
//             while (current_node)
//             {
//                 printf("\t%s\n", current_node->key);
//                 current_node = (struct set_node *)current_node->next;
//             }
//         }
//     }
//     Search(sets, "This is me", -1);
// }
#pragma endregion
