#include <stdio.h>
#include <stdlib.h>

/*
GOAL OF THIS CODE:
Create a fully functional doubly linked list.
1. there should be a function that adds a new node in the start of the list.
2. there should be a function thats adds a new node in the end of the list.
3. there should be a function thats adds a new node in the middle of the list where ever the user wants the new node to be.
4. there should be a function that prints the whole list.
5. there should be a function that deletes a node from the start of the list.
6. there should be a function that deletes a node from the end of the list.
7. there should be a function that delters a node from the middle of the list whichever node user want to delete.
8. there should be a function that can tell if the particular data is present or not in the linked list.
*/

struct linked_list_ptrs
{
    struct node* head;
    struct node* tail;
};

struct node {
    int data;
    struct node* next;
    struct node* prev;
};

struct linked_list_ptrs list_initilizer(int node1_data, int node2_data, int node3_data, int node4_data)
{
    struct linked_list_ptrs doubly_linked_list;

    struct node* node1 = (struct node*) malloc(sizeof(struct node));
    struct node* node2 = (struct node*) malloc(sizeof(struct node));
    struct node* node3 = (struct node*) malloc(sizeof(struct node));
    struct node* node4 = (struct node*) malloc(sizeof(struct node));

    node1->data = node1_data;
    node1->next = node2;
    node1->prev = NULL;

    node2->data = node2_data;
    node2->next = node3;
    node2->prev = node1;

    node3->data = node3_data; 
    node3->next = node4;
    node3->prev = node2;

    node4->data = node4_data;
    node4->next = NULL;
    node4->prev = node3;

    doubly_linked_list.head = node1;
    doubly_linked_list.tail = node4;

    return doubly_linked_list;
}

void beginning_node_adder(struct node** head, int new_node_data)
{
    struct node* new_node = (struct node*) malloc(sizeof(struct node));
    
    if (new_node != NULL)
    {
        new_node->data = new_node_data;

        new_node->next = *head;
        (*head)->prev = new_node;
        new_node->prev = NULL;

        *head = new_node;

        printf("**node addition in the beginning successful**\n");
    }
}

void end_node_adder(struct node** tail, int new_node_data)
{
    struct node* new_node = (struct node*) malloc(sizeof(struct node));

    if (new_node != NULL)
    {
        new_node->data = new_node_data;

        new_node->next = NULL;
        (*tail)->next = new_node;
        new_node->prev = *tail;

        *tail = new_node;

        printf("**node addition in the end successful**\n");
    }
}

void middle_node_adder(struct node* head, int new_node_data, int node_finder_data)
{
    struct node* ptr = head;
    struct node* new_node = (struct node*) malloc(sizeof(struct node));
    new_node->data = new_node_data;

    while (ptr != NULL && ptr->data != node_finder_data)
    {
        ptr = ptr->next;
    }
    if (ptr->data == node_finder_data)
    {
        new_node->next = ptr->next;
        new_node->prev = ptr;
        ptr->next = new_node;

        printf("**node with data = \'%d\' addition after \'%d\' successful**\n", new_node_data, ptr->data);
    }
}

void beginning_node_deleter(struct node** head)
{
    struct node* ptr = *head;

    *head = ptr->next;
    ptr->next = NULL;
    free(ptr);

    printf("node deletion in the beginning succesful.\n");
}

void end_node_deleter(struct node** tail)
{
    struct node* ptr = *tail;

    (*tail)->prev->next = NULL;
    *tail = ptr->prev;
    ptr->prev = NULL;

    free(ptr);

    printf("node deletion in the end of the list successful\n");
}

void middle_node_deleter(struct node* head, int node_finder_data)
{
    struct node* ptr = head;

    while (ptr != NULL && ptr->next->data != node_finder_data)
    {
        ptr = ptr->next;    
    }
    if (ptr->next != NULL && ptr->next->data == node_finder_data)
    {
        struct node* temp = ptr->next;
        ptr->next = ptr->next->next;
        
        if (ptr->next != NULL)
        {
            ptr->next->prev = ptr;
        }
        
        free(temp);
        printf("deletion of node with data = \'%d\' successful.\n", node_finder_data);
    }
    else
    {
        printf("node with data = \'%d\' not found in the list. deletion aborted. please check and try again.\n", node_finder_data);
    }
}

void list_printer(struct node* head, struct node* tail)
{
    int mode = 1;
    struct node* front_iterator = head;
    struct node* back_iterator = tail;

    // printf("please enter the mode:\n1.print from head.\n2.print from tail\n");
    // scanf("%d", &mode);

    if (mode == 1)
    {
        printf("head -> ");
        while (front_iterator != NULL)
        {
            printf("%d <-> ", front_iterator->data);
            front_iterator = front_iterator->next;
        }
        printf("tail\n");
    }
    else
    {
        printf("tail -> ");
        while (back_iterator != NULL)
        {
            printf("%d <-> ", back_iterator->data);
            back_iterator = back_iterator->prev;
        }
        printf(" head\n");
    }
}

void node_checker(struct node* head, int node_finder_data)
{
    int position_of_node = 1;
    struct node* ptr = head;

    while (ptr != NULL)
    {
        if (ptr->data != node_finder_data)
        {
            ptr = ptr->next;
            position_of_node++;
            continue;
        }
        printf("node with data = \'%d\' found at node %d in the list.\n", node_finder_data, position_of_node);
        return;
    }
    printf("node with data = \'%d\' not found in the list.\n", node_finder_data);
}

int main()
{
    struct node* head;
    struct node* tail;
    struct linked_list_ptrs doubly_linked_list;
    int node1_data, node2_data, node3_data, node4_data;
    int new_node_data;
    int node_finder_data;
    int mode = 0;

    printf("this program depicts the use of doubly linked lists in C\n");

    printf("following are the Options avaliable for list manipulation:\n1.Re-Initialize List.\n2.Add node in the beginning.\n3.Add node in the middle.\n4.Add node in the end.\n5.delete node in the beginning.\n6.delete node in the middle.\n7.delete node in the end.\n8.check if a node is present in the list.\n9.Print the Linked list.\n10.Exit \n11.print the operations panel again\n");
    

    while(mode != 10)
    {
    printf("please enter the operation you want to perform\n");
    scanf("%d", &mode);

    switch (mode)
    {
    case 1:
        printf("please enter the node data\n");
        printf("node1 data:\n");
        scanf("%d", &node1_data);
        printf("node2 data:\n");
        scanf("%d", &node2_data);
        printf("node3 data:\n");
        scanf("%d", &node3_data);
        printf("node4 data:\n");
        scanf("%d", &node4_data);

        doubly_linked_list = list_initilizer(node1_data, node2_data, node3_data, node4_data);
        head = doubly_linked_list.head;
        tail = doubly_linked_list.tail; 

        break;
    case 2:
        printf("please enter the new node data:\n");
        scanf("%d", &new_node_data);
        beginning_node_adder(&head, new_node_data);
        break;

    case 3:
        printf("please enter the new node data:\n");
        scanf("%d", &new_node_data);
        printf("please enter the data of the node after which you would like to add the new node:\n");
        scanf("%d", &node_finder_data);

        middle_node_adder(head, new_node_data, node_finder_data);
        break;

    case 4:
        printf("please enter the new node data:\n");
        scanf("%d", &new_node_data);
        end_node_adder(&tail, new_node_data);
        break;

    case 5:
        printf("deleting node in the beginning...\n");

        beginning_node_deleter(&head);
        break;

    case 6:
        printf("please enter the data of the node you would like to delete:\n");
        scanf("%d", &node_finder_data);

        middle_node_deleter(head, node_finder_data);
        break;

    case 7:
        printf("deleting node in the end...\n");

        end_node_deleter(&tail);
        break;

    case 8:
        printf("please enter the data which you want to check:\n");
        scanf("%d", &node_finder_data);

        node_checker(head, node_finder_data);
        break;

    case 9:
        list_printer(head, tail);
        break;

    case 10:
        goto exit;
        break;

    case 11:
        printf("Options avaliable for list manipulation:\n1.Initialize List.\n2.Add node in the beginning.\n3.Add node in the middle.\n4.Add node in the end.\n5.delete node in the beginning.\n6.delete node in the middle.\n7.delete node in the end.\n8.check if a node is present in the list.\n9.Print the Linked list.\n10.Exit \n11.print the operations panel again\n");
        break;

    default:
        printf("operation not found!!! please check the operations list and try again.\n");
        break;
    }
    }

    exit:
    return 0;
}


/*
FOR TESTING ONLY
    doubly_linked_list = list_initilizer(head, tail);
    head = doubly_linked_list.head;
    tail = doubly_linked_list.tail;
    list_printer(head, tail);
    beginning_node_adder(&head, 999);
    beginning_node_adder(&head, 888);
    list_printer(head, tail);
    end_node_adder(&tail, 222);
    end_node_adder(&tail, 111);
    list_printer(head, tail);
    middle_node_adder(head, 555, 20);
    middle_node_adder(head, 444, 30);
    // list_printer(head, tail);
    node_checker(head, 40);
    node_checker(head, 456);
    list_printer(head, tail);
    beginning_node_deleter(&head);
    beginning_node_deleter(&head);
    list_printer(head, tail);
    end_node_deleter(&tail);
    end_node_deleter(&tail);
    list_printer(head, tail);
    middle_node_deleter(head, 555);
    middle_node_deleter(head, 444);
    list_printer(head, tail);

*/