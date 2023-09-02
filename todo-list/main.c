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

void todo_remove_task(struct node **head, int position_to_remove)
{
    struct node *temp_ptr = *head;
    struct node *prev_ptr = NULL;

    if (*head == NULL)
    {
        printf("Task list is empty!\n");
    }
    else if ((*head)->link == NULL)
    {
        free(*head);
        *head = NULL;
    }
    else if (position_to_remove == 1)
    {
        *head = (*head)->link;
        free(temp_ptr);
        temp_ptr = NULL;
    }
    else
    {
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
    fptr = fopen("D:/DSA/projects/todo-list/database/data.txt", "a");
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

struct node *todo_load_task()
{
    FILE *file = fopen("D:/DSA/projects/todo-list/database/data.txt", "r");

    if (file == NULL)
    {
        printf("The specified file cannot be read!\n");
        exit(EXIT_FAILURE);
    }

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

    fclose(file);

    return head;
}

void todo_remove_from_file(int line_to_remove)
{
    FILE *source_file = fopen("D:/DSA/projects/todo-list/database/data.txt", "r");
    char task[32 + 1];
    FILE *temp_file = fopen("D:/DSA/projects/todo-list/database/temp.txt", "w");
    int current_line = 1;

    if (source_file == NULL)
    {
        printf("Cannot open the specified file!");
        exit(EXIT_SUCCESS);
    }

    while (fgets(task, sizeof(task), source_file))
    {
        if (current_line == line_to_remove)
        {
            current_line++;
            continue;
        }

        fprintf(temp_file, "%s", task);
        current_line++;
    }

    fclose(source_file);
    fclose(temp_file);

    remove("todo-list/database/data.txt");
    rename("todo-list/database/temp.txt", "todo-list/database/data.txt");
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
        struct node *head = todo_load_task();
        todo_task_display(head);
    }
    else if (operation == 3)
    {
        int position;

        struct node *head = todo_load_task();
        todo_task_display(head);

        printf("Please enter the position of a task you want to remove:\t");
        scanf(" %d", &position);

        todo_remove_from_file(position);
        todo_remove_task(&head, position);
        todo_task_display(head);
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