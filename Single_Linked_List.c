#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>

typedef struct Node Singly_node_t;

#define NULL_CHECK(item)                           \
    {                                              \
        if (!item)                                 \
        {                                          \
            printf("Unable to allocate memory\n"); \
            return -1;                             \
        }                                          \
    }

struct Node
{
    Singly_node_t *linked_node;
    void *data;
};

Singly_node_t *Get_Tail(Singly_node_t **head)
{
    if (!*head)
    {
        return NULL;
    }
    Singly_node_t *current_node = *head;
    Singly_node_t *last_node = NULL;
    while (current_node)
    {
        last_node = current_node;
        current_node = current_node->linked_node;
    }

    return last_node;
}

int Append(Singly_node_t **head, void *item, size_t struct_type)
{
    Singly_node_t *current_node = Get_Tail(head);
    Singly_node_t *appended_node = malloc(struct_type);
    NULL_CHECK(appended_node);
    appended_node->data = item;
    appended_node->linked_node = NULL;
    if (!current_node)
    {
        *head = appended_node;
        printf("I added an element at the begin :%s\n\n", (char *)item);
        
        return 0;
    }
    // define the link at the appended node
    current_node->linked_node = appended_node;
    return 1;
}

Singly_node_t *Pop_First(Singly_node_t **head)
{
    if (!*head)
        return NULL;

    Singly_node_t *current_node = *head;

    *head = (*head)->linked_node;
    current_node->linked_node = NULL;
    return current_node;
}

Singly_node_t *Pop_Last(Singly_node_t **head)
{
    if (!*head)
        return NULL;

    Singly_node_t *previous_node = *head;
    Singly_node_t *current_node = *head;
    while (current_node->linked_node)
    {
        previous_node = current_node;
        current_node = current_node->linked_node;
    }
    previous_node->linked_node = NULL;

    return current_node;
}

Singly_node_t *Remove(Singly_node_t **head, int index)
{
    Singly_node_t *current_node = *head;
    Singly_node_t *previous_node = *head;
    if (index == 0)
    {
        Pop_First(head);
        return current_node;
    }

    for (int i = 0; i < index; i++)
    {
        previous_node = current_node;
        current_node = current_node->linked_node;
        if (!current_node)
        {
            printf("Index out of range");
            return NULL;
        }
    }

    previous_node->linked_node = current_node->linked_node;
    return current_node;
}

int LinkedListLenght(Singly_node_t **head)
{
    Singly_node_t *temp = *head;
    int lenght = 1;
    while (temp->linked_node)
    {
        lenght++;
        temp = temp->linked_node;
    }
    return lenght;
}

Singly_node_t *Revert(Singly_node_t **head)
{
    Singly_node_t **copy_node = head;
    Singly_node_t *new_Linked = NULL;
    Singly_node_t *Popped;
    int prova = LinkedListLenght(head);

    for (size_t i = 0; i < prova; i++)
    {
        Append(&new_Linked, (struct list_node *)Pop_Last(head)->data, sizeof(Singly_node_t));
    }
    return new_Linked;
}

#pragma region Main
// int main()
// {
//     Singly_node_t * head = NULL;
//     Append(&head, "Primo");
//     Append(&head, "Secondo");
//     Append(&head, "Terzo");
//     Append(&head, "Quarto");
//     Append(&head, "Quinto");
//     Append(&head, "Sesto");
//     Append(&head, "Last append");

//     printf("%s\n", (char *)(head)->data);
//     printf("Get Tail: %s\n", (char *)Get_Tail(&head)->data);
//     printf("%s\n", (char *)Pop_First(&head));
//     printf("%s\n", (char *)(head)->data);
//     printf("Remove: %s\n", (char *)Remove(&head, 0));
//     printf("%s\n", (char *)(head)->linked_node->data);
//     printf("%s\n", (char *)(((struct list_node *)Pop_Last(&head)->data)));
//     printf("%s\n", (char *)(((struct list_node *)Pop_Last(&head)->data)));

//     Singly_node_t * prova = head;
//     while (prova)
//     {
//         printf("%s\n", (char *)prova->data);
//         prova = prova->linked_node;
//     }

//     Singly_node_t * reverted = Revert(&head);
//     Singly_node_t * Revert_head = reverted;
//     while (Revert_head)
//     {
//         printf("%s\n", (char *)Revert_head->data);
//         Revert_head = Revert_head->linked_node;
//     }

//     return 0;
// }
#pragma endregion