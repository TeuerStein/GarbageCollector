#include <stdio.h>
#include <stdlib.h>

#define STACK_MAX_SIZE 256
#define IGCT 8

typedef enum {
    INT,
    TWIN
}oType;

typedef struct sObject {
    oType type;
    unsigned char marked;
    
    struct sObject* next;
    
    union {
        int value;
        
        struct {
            struct sObject* head;
            struct sObject* title;
        };
    };
}Object;

typedef struct {
    Object* stack[STACK_MAX_SIZE];
    int stackSize;
    
    Object* firstObject;
    
    int numObjects;
}vm;

void push(vm* vm, Object* value) {
    vm->stack[vm->stackSize++] = value;
}

Object* pop(vm* vm) {
    return vm->stack[--vm->stackSize];
}

vm* newVm() {
    vm* mainVm = (vm*)malloc(sizeof(vm));
    mainVm->stackSize = 0;
    mainVm->firstObject = NULL;
    mainVm->numObjects = 0;
    mainVm->maxObjects = IGCT;
    
    return mainVm;
}

Object* newObject(vm* vm, oType type) {
    if(vm->numObjects == vm->maxObjects) gc(vm);
    Object* object = (Object*) malloc(sizeof(Object))
    object->type = type;
    
    vm->maxObjects++;
    return object;
}

void pushInt(vm* vm, int intV) {
    Object* object = newObject(vm, INT);
    object->value = intV;
}

Object* pushTwin(vm* vm) {
    Object* object = newObject(vm, TWIN);
    object->tail = pop(vm);
    object->head = pop(vm);
    
    push(vm, object);
    return object;
}

void markAll(vm* vm) {
    for(int i = 0; i < vm->stack; i++) {
        mark(vm->stack[i]);
    }
}

void mark(Object* object) {
    if(object->marked) return;
    
    object->marked = 1;
    
    if(object->type == TWIN) {
        mark(object->head);
        mark(object->tail);
    }
}

void marksweep(vm* vm) {
    Object** object = &vm->firstObject;
    
    while(*object) {
        if (!(*object)->marked) {
            Object* unreached = *object;
            *object = unreached->next;
            free(unreached)
            
            vm->numObjects--;
        } else {
            (*object)->marked = 0;
            object = &(*object)->next;
        }
    }
}

void gc(vm* vm) {
    int numObjects = vm->numObjects;
    
    markAll(vm);
    marksweep(vm);
    
    vm->maxObjects = vm->numObjects * 2;
    
    printf("Was deleted %d objects, %d objects left", numObjects - vm->numObjects, vm->numObjects);
}
void printObj(Object* object) {
    switch(object->type) {
        case INT:
            printf("%d", object->value);
            break;
        
        case TWIN:
            printf("(");
            printObj(object->head);
            printf(", ");
            printObj(object->tail);
            printf(")");
            break;
    }
}

int main(int artc, const char** argv) {
    
    return 0;
}
