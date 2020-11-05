#include <stdio.h>
#include <stdlib.h>

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
};

int main(int artc, const char** argv) {
    
    return 0;
}
