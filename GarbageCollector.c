#include <stdio.h>
#include <stdlib.h>

#define STACK_MAX_SIZE 256

typedef enum {
    INT,
    TWIN
}oType;

typedef struct sObject {
    oType type;
    
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
    
    return mainVm;
}

Object* newObject(vm* vm, oType type) {
    Object* object = (Object*) malloc(sizeof(Object))
    object->type = type;
    
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

int main(int artc, const char** argv) {
    
    return 0;
}
