#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_DESCRIPTION_SIZE 100
#define MAX_SIZE 10

typedef struct Task {
    int id;
    char description[MAX_DESCRIPTION_SIZE];
    struct Task* prox;
} TASK;

typedef struct queue {
    int inicio;
    int fim;
    TASK* items[MAX_SIZE];
} QUEUE;

// CONSTRUCTOR
TASK* createTask(int id, char* description);
TASK* createTaskByScanf();

// LIST
void addToCompletedList(TASK* newTask);
TASK* removeFromCompletedListByItsId(int id);
void seeAllCompletedList();

// QUEUE
void initQueue(QUEUE* q);
void putToPendingQueue(QUEUE* q, TASK* newTask);
TASK* getFromPendingQueue(QUEUE* q);
void seeAllPendingQueue(QUEUE* q);

// STACK
void pushToDraftStack(TASK* newTask);
TASK* popFromDraftStack();
void seeAllDraftStack();

// MENU
void displayMenu();

int main() {
    int choice;
    QUEUE pendingQueue;
    initQueue(&pendingQueue);
    
    printf("################# TASK MANAGER SYSTEM #################");

    do {
        displayMenu();
        printf("Choose an option: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                // CREATE A TASK, THEN ADD TO PENDING QUEUE
                TASK* newTask = createTaskByScanf();
                putToPendingQueue(&pendingQueue, newTask);
                break;

            case 2:
                // SEE ALL TASKS FROM PENDING QUEUE
                seeAllPendingQueue(&pendingQueue);
                break;

            case 3:
                // COMPLETE FIRST PENDING TASK
                TASK* firstTask = getFromPendingQueue(&pendingQueue);
                if(firstTask != NULL) {
                    addToCompletedList(firstTask);
                }
                break;

            case 4:
                // SEE ALL TASKS FROM COMPLETED LIST
                seeAllCompletedList();
                break;

            case 5:
                // SET COMPLETED TASK TO DRAFT
                int id;
                printf("Enter Task ID (number): ");
                scanf("%d", &id);

                TASK* task = removeFromCompletedListByItsId(id);
                if(task != NULL) {
                    pushToDraftStack(task);
                }
                break;

            case 6:
                // SEE ALL TASKS FROM DRAFT STACK
                seeAllDraftStack();
                break;

            case 7:
                // SET LAST DRAFT AS PENDING TASK
                TASK* lastTask = popFromDraftStack();
                if(task != NULL) {
                    putToPendingQueue(&pendingQueue, task);
                }
                break;

            case 0:
                printf("Exiting program\n");
                break;
            default:
                printf("Invalid choice\n");
                break;
        }
    } while (choice != 0);

    printf("################# SYSTEM SHUT DOWN #################");
}

// CONSTRUCTOR
TASK* createTask(int id, char* description) {
    TASK* newTask = (TASK*) malloc(sizeof(TASK));

    newTask->id = id;
    strcpy(newTask->description, description);
    newTask->prox = NULL;

    return newTask;
}

TASK* createTaskByScanf() {
    int id;
    char description[MAX_DESCRIPTION_SIZE];

    printf("Enter Task ID (number): ");
    scanf("%d", &id);

    getchar();
    printf("Enter Task Description (string): ");

    fgets(description, MAX_DESCRIPTION_SIZE, stdin);
    description[strcspn(description, "\n")] = '\0';

    return createTask(id, description);
}

// LIST
void addToCompletedList(TASK* newTask) {
    printf("Adding Task to Completed List");

    // YOUR CODE HERE
}

TASK* removeFromCompletedListByItsId(int id) {
    printf("Removing Task from Completed List");

    // YOUR CODE HERE
    return NULL; // Return NULL if ID not exist
}

void seeAllCompletedList() {
    printf("Printing All Completed List");

    // YOUR CODE HERE
}

// QUEUE

void initQueue(QUEUE* q){
    q->inicio = -1;
    q->fim = -1;
}

void putToPendingQueue(QUEUE* q, TASK* newTask) {
    printf("Putting Task to Pending Queue\n");
    
    if(q->inicio == -1){
        q->inicio = 0;
    }
    q->fim = (q->fim + 1) % MAX_SIZE;
    q->items[q->fim] = newTask;
    
    printf("Task added into the pending queue!\n\n");
}

TASK* getFromPendingQueue(QUEUE* q) {
    int id;
    printf("Getting Task from Pending Queue\n");
    printf("Write the task ID please: \n");
    scanf("%d", &id);
    
    for(int i = q->inicio; i != (q->fim + 1) % MAX_SIZE; i = (i + 1) % MAX_SIZE){
        TASK* task = q->items[i];
        
        if(task->id){
            printf("Task %d found!\n", id);
            return task;
        }
        
        printf("The task ID was not found!");
    }
    
    return NULL; // Return NULL if Queue is empty
}

void seeAllPendingQueue(QUEUE* q) {
    printf("Printing All Pending Queue\n");
    
    for(int i = q->inicio; i != (q->fim + 1) % MAX_SIZE; i = (i + 1) % MAX_SIZE){
        TASK* task = q->items[i];
        printf("Task ID: %d, \nDescription: %s\n", task->id, task->description);
    }
}

// STACK
void pushToDraftStack(TASK* newTask) {
    printf("Pushing Task to Draft Stack");

    // YOUR CODE HERE
}

TASK* popFromDraftStack() {
    printf("Popping Task to Draft Stack");

    // YOUR CODE HERE
    return NULL; // Return NULL if Stack is empty
}

void seeAllDraftStack() {
    printf("Printing All Draft Stack");

    // YOUR CODE HERE
}

// MENU
void displayMenu() {
    printf("\nMenu:\n");
    printf("1 - Create New Pending Task\n");
    printf("2 - See All Pending Tasks\n");
    printf("3 - Complete First Pending Task\n");
    printf("4 - See All Completed Tasks\n");
    printf("5 - Set Completed Task as Draft by its ID\n");
    printf("6 - See All Draft Tasks\n");
    printf("7 - Set Last Draft Task as Pending Task\n");
    printf("0 - Exit\n");
}
