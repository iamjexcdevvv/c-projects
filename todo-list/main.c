#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node
{
    char data[32 + 1];
    struct node *link;
};

void todo_add_node(struct node *head, struct node *new_node)
{
    if (head == NULL)
    {
        printf("Task list is empty!\n");
        exit(EXIT_SUCCESS);
    }

    struct node *node_ptr = head;

    while (node_ptr->link != NULL)
    {
        node_ptr = node_ptr->link;
    }

    node_ptr->link = new_node;
}

void todo_create_node(char task[], struct node *head, int current_line)
{
    struct node *new_node = (struct node *)malloc(sizeof(struct node));
    strcpy(new_node->data, task);
    new_node->link = NULL;

    if (current_line == 2)
    {
        head->link = new_node;
    }
    else
    {
        todo_add_node(head, new_node);
    }
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

    printf("Task List:\n");

    while (node_ptr != NULL)
    {
        printf("%s\n", node_ptr->data);
        node_ptr = node_ptr->link;
    }
}

void todo_load_task(FILE *file)
{
    char task[32 + 1];

    struct node *head = (struct node *)malloc(sizeof(struct node));

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
            todo_create_node(task, head, current_line);
        }
        current_line++;
    }

    todo_task_display(head);
}

void get_user_input(int operation)
{
    if (operation == 1)
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

        todo_load_task(fptr);
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
    printf("Enter 1 To Add Task\n");
    printf("Enter 2 To View Tasks\n");
    printf("Please enter a number:\t");
    scanf("%d", &operation);
    getchar(); // This will consume the new line that produced by scanf function so later on we can use fgets function
    get_user_input(operation);
}

int main()
{
    init_app();
    return 0;
}