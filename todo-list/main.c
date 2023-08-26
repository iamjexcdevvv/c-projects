#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// TODO - Fix removing node at position 1 program crash

struct node
{
    char data[32 + 1];
    struct node *link;
};

void todo_remove_node(struct node **head, int position_to_remove)
{
    if (*head == NULL)
    {
        printf("Task list is empty!\n");
    }
    else if ((*head)->link == NULL)
    {
        free(*head);
        *head = NULL;
    }
    else
    {
        struct node *temp_ptr = *head;
        struct node *prev_ptr = NULL;

        int current_pos = 1;
        while (current_pos != position_to_remove)
        {
            prev_ptr = temp_ptr;
            temp_ptr = temp_ptr->link;
            current_pos++;
        }
        prev_ptr->link = temp_ptr->link;
        free(temp_ptr);
        temp_ptr = NULL;
    }
}

void todo_add_node(char task[], struct node **tail, struct node *head)
{
    struct node *new_node = (struct node *)malloc(sizeof(struct node));
    strcpy(new_node->data, task);

    if (head->link == NULL)
    {
        head->link = new_node;
    }
    else
    {
        (*tail)->link = new_node;
    }
    *tail = new_node;
}

void todo_save(char task[])
{
    FILE *fptr;
    fptr = fopen("D:/DSA/projects/todo-list/database/todo-list.txt", "a");
    fprintf(fptr, "%s", task);
    fclose(fptr);
}

void todo_task_display(struct node *head)
{
    struct node *node_ptr = head;
    int position = 1;

    printf("Task List:\n");

    while (node_ptr != NULL)
    {
        printf("%d.%s\n", position, node_ptr->data);
        node_ptr = node_ptr->link;
        position++;
    }
}

struct node *todo_load_task(FILE *file)
{
    char task[32 + 1];

    struct node *head = (struct node *)malloc(sizeof(struct node));
    struct node *tail = NULL;

    int current_line = 1;

    while (fgets(task, sizeof(task), file))
    {
        size_t task_len = strlen(task);

        if (task_len > 0 && task[task_len - 1] == '\n')
        {
            task[task_len - 1] = '\0';
        }

        if (current_line == 1)
        {
            strcpy(head->data, task);
            head->link = NULL;
        }
        else
        {
            todo_add_node(task, &tail, head);
        }
        current_line++;
    }

    return head;
}

void get_user_input(int operation)
{
    if (operation == 0)
    {
        exit(EXIT_SUCCESS);
    }
    else if (operation == 1)
    {
        char task[32 + 1];
        fgets(task, sizeof(task), stdin);
        todo_save(task);
    }
    else if (operation == 2)
    {
        FILE *fptr = fopen("D:/DSA/projects/todo-list/database/todo-list.txt", "r");

        if (fptr == NULL)
        {
            printf("The specified file cannot be read!\n");
            exit(EXIT_FAILURE);
        }

        struct node *head = todo_load_task(fptr);
        todo_task_display(head);
        fclose(fptr);
    }
    else if (operation == 3)
    {
        FILE *fptr = fopen("D:/DSA/projects/todo-list/database/todo-list.txt", "r");

        if (fptr == NULL)
        {
            printf("The specified file cannot be read!\n");
            exit(EXIT_FAILURE);
        }

        int position;

        struct node *head = todo_load_task(fptr);
        todo_task_display(head);

        printf("Please enter the position of a task you want to remove:\t");
        scanf(" %d", &position);

        todo_remove_node(&head, position);

        fclose(fptr);
    }
    else
    {
        printf("Invalid option!\n");
        exit(EXIT_FAILURE);
    }
}

void init_app()
{
    int operation;
    while (true)
    {
        printf("Enter 0 To end the program\n");
        printf("Enter 1 To Add Task\n");
        printf("Enter 2 To View Tasks\n");
        printf("Enter 3 To Delete a task\n");
        printf("Please enter a number:\t");
        scanf("%d", &operation);
        getchar(); // This will consume the new line that produced by scanf function so later on we can use fgets function
        get_user_input(operation);
    }
}

int main()
{
    init_app();
    return 0;
}