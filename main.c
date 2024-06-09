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

typedef struct listNo {
    TASK* task;
    struct listNo* next;
} listNo;

typedef struct list {
    listNo* head;
} LIST;

typedef struct stackNo {
    TASK* task;
    struct stackNo* next;
} stackNo;

typedef struct stack {
    stackNo* top;
} STACK;

// CONSTRUCTOR
TASK* createTask(int id, char* description);
TASK* createTaskByScanf();

// LIST
void initList(LIST* list);
void addToCompletedList(LIST* list, TASK* newTask);
TASK* removeFromCompletedListByItsId(LIST* list, int id);
void seeAllCompletedList(LIST* list);

// QUEUE
void initQueue(QUEUE* q);
void putToPendingQueue(QUEUE* q, TASK* newTask);
TASK* getFromPendingQueue(QUEUE* q);
void seeAllPendingQueue(QUEUE* q);

// STACK
void initStack(STACK* stack);
void pushToDraftStack(STACK* stack, TASK* newTask);
TASK* popFromDraftStack();
void seeAllDraftStack(STACK* stack);

// MENU
void displayMenu();

int main() {
    int choice;
    QUEUE pendingQueue;
    initQueue(&pendingQueue);
    
    LIST completedList;
    initList(&completedList);
    
    STACK draftStack;
    initStack(&draftStack);
    
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
                    addToCompletedList(&completedList, firstTask);
                }
                break;

            case 4:
                // SEE ALL TASKS FROM COMPLETED LIST
                seeAllCompletedList(&completedList);
                break;

            case 5:
                // SET COMPLETED TASK TO DRAFT
                int id;
                printf("Enter Task ID (number): ");
                scanf("%d", &id);

                TASK* task = removeFromCompletedListByItsId(&completedList, id);
                if(task != NULL) {
                    pushToDraftStack(&draftStack, task);
                }
                break;

            case 6:
                // SEE ALL TASKS FROM DRAFT STACK
                seeAllDraftStack(&draftStack);
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
void initList(LIST* list){
    list->head = NULL;
}

void addToCompletedList(LIST* list, TASK* newTask) {
    printf("Adding Task to Completed List");
    
    listNo* newNo = (listNo*) malloc(sizeof(listNo));
    
    newNo->task = newTask;
    newNo->next = list->head;
    
    list->head = newNo;
}

TASK* removeFromCompletedListByItsId(LIST* list, int id) {
    printf("Removing Task from Completed List\n");
    
    listNo* current = list->head;
    listNo* previous = NULL;
    
    while(current != NULL){
        if(current->task->id == id){
            if(previous == NULL){
                list->head = current->next;
            } else {
                previous->next = current->next;
            }
            
            TASK* removedTask = current->task;
            free(current);
            printf("Task ID %d was found and removed!", id);
            return removedTask;
        }
        
        previous = current;
        current = current->next;
    }
    
    printf("Task ID %d not found!\n", id);
    return NULL; // Return NULL if ID not exist
}

void seeAllCompletedList(LIST* list) {
    printf("Printing All Completed List\n");
    
    listNo* current = list->head;
    
    while(current != NULL){
        TASK* task = current->task;
         printf("Task ID: %d,\nDescription: %s\n", task->id, task->description);
         printf("- - - - - - - - - - - - - -\n");
         current = current->next;
    }
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
    
    if(q->inicio == -1){
        printf("The queue is empty!\n");
        return NULL;  // Return NULL if Queue is empty
    } else {
        printf("Getting Task from Pending Queue\n");
            TASK* task = q->items[q->inicio];
            q->inicio = (q->inicio + 1) % MAX_SIZE;
        
        printf("First task catched\n");
        
        return task;
    }
}

void seeAllPendingQueue(QUEUE* q) {
    printf("Printing All Pending Queue\n");
    
    for(int i = q->inicio; i != (q->fim + 1) % MAX_SIZE; i = (i + 1) % MAX_SIZE){
        TASK* task = q->items[i];
        printf("Task ID: %d, \nDescription: %s\n", task->id, task->description);
    }
}

// STACK
void initStack(STACK* stack){
    stack->top = NULL;
}

void pushToDraftStack(STACK* stack, TASK* newTask) {
    printf("Pushing Task to Draft Stack\n");
    
    stackNo* newNo = (stackNo*) malloc(sizeof(stackNo));
    
    newNo->task = newTask;
    newNo->next = stack->top;
    
    stack->top = newNo;
    
    printf("Task ID %d pushed to stack.\n", newTask->id);

    // YOUR CODE HERE
}

TASK* popFromDraftStack() {
    printf("Popping Task to Draft Stack");

    // YOUR CODE HERE
    return NULL; // Return NULL if Stack is empty
}

void seeAllDraftStack(STACK* stack) {
    printf("Printing All Draft Stack\n");
    
    stackNo* current = stack->top;
    printf("Printing All Stack Items:\n");
    while(current != NULL){
        printf("Task ID: %d,\nDescription: %s\n", current->task->id, current->task->description);
        current = current->next;
    }
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
