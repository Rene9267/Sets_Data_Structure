#include <Sets_Data_Structure.h>

int main(int argc, char const *argv[])
{
    set_table_t *sets = Set_TableNew(2);

    Set_Insert(sets, "Hello", 5);
    Set_Insert(sets, "Hello World", 11);
    Set_Insert(sets, "This is me", 10);
    Set_Insert(sets, "New", 3);
    Set_Insert(sets, "Computer", 9);
    Set_Insert(sets, "Hello", 5);
    Set_Insert(sets, "Hello mauro", 11);
    Set_Insert(sets, "Hello isma", 10);
    Set_Insert(sets, "Hello lorenzo", 13);

    Set_Remove(sets, "Hello mauro");
    Set_Remove(sets, "Hello");
    struct set_node **current_node = sets->nodes;
    size_t index = 0;
    struct set_node *head_node;
    for (index = 0; index < sets->hashmap_size; index++)
    {
        if ((head_node = current_node[index]))
        {
            printf("Index [%llu]:\n", index);
            struct set_node *current_node = head_node;
            while (current_node)
            {
                printf("\t%s\n", (char *)current_node->node.data);
                current_node = (struct set_node *)current_node->node.linked_node;
            }
        }
    }
    Set_Search(sets, "This is me", -1);
}