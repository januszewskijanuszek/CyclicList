// januszewskijanuszek Patryk Januszewski
#include <stdio.h>
#include <malloc.h>

struct Element{
    struct Element* nextElement;
    struct Element* previousElement;
    int value;
};

struct Element elementConstructor(struct Element* previousElement, struct Element* nextElement, int value){
    struct Element element;
    element.value = value;
    element.nextElement = nextElement;
    element.previousElement = previousElement;
    return element;
}

struct CyclicList{
    struct Element* elementsArray;
    struct Element* pivot;
    int counter;
};

void addElement(struct CyclicList* array, int value){
    array -> counter ++;
    if(array -> counter > 1){
        realloc(
                array -> elementsArray,
                array -> counter * sizeof (struct Element));
    }
    if(array -> counter == 1){
        array -> elementsArray = malloc(sizeof (struct Element));
        array -> elementsArray[array -> counter - 1] = elementConstructor(
                NULL,
                NULL,
                value);
        array -> pivot = &(array -> elementsArray[array -> counter - 1]);
    } else if(array -> counter == 2){
        array -> elementsArray[array -> counter - 1] = elementConstructor(
                array -> pivot,
                array -> pivot, value);
        array
        -> pivot
        -> previousElement
        = &(array -> elementsArray[array -> counter - 1]);
        array
        -> pivot
        -> nextElement
        = &(array -> elementsArray[array -> counter - 1]);
    } else{
        struct Element* memory = array -> pivot -> nextElement;
        array -> elementsArray[array -> counter - 1] = elementConstructor(
                array -> pivot,
                memory,
                value);
        array -> pivot -> nextElement = &(array -> elementsArray[array -> counter - 1]);
        memory -> previousElement = &(array -> elementsArray[array -> counter - 1]);
    }
}

void movePivot(struct CyclicList* array, int input){
    if(array -> counter >= 2){
        switch(input){
            case 0:{
                array -> pivot = array
                        -> pivot
                        -> previousElement;
                break;
            }
            case 1:{
                array -> pivot = array
                        -> pivot
                        -> nextElement;
                break;
            }
            default:{exit(400); break;}
        }
    } else{
        exit(403);
    }
}

void printAllElements(struct CyclicList array){
    for(int i = 0 ; i < array.counter ; i++){
        printf("%d\n", array.pivot -> value);
        movePivot(&array, 1);
    }
}

int searchElement(struct CyclicList array, int value){
    for(int i = 0 ; i < array.counter ; i++){
        if(array.pivot -> value == value){
            return 1;
        } else{
            movePivot(&array, 1);
        }
    }
    return 0;
}

void deleteElement(struct CyclicList* array, int value){
    if(searchElement(*array, value)){
        for(int i = 0 ; i < array -> counter ; i++){
            if(array -> pivot -> value == value){
                array -> counter--;
                if(array -> counter == 0){
                    free(array -> elementsArray);
                    break;
                } else if(array -> counter == 1){
                    struct Element* memory = array -> pivot -> nextElement;
                    memory -> nextElement = NULL;
                    memory -> previousElement = NULL;
                    array
                    -> pivot
                    -> nextElement = NULL;
                    array
                    -> pivot
                    -> previousElement = NULL;
                    array -> pivot = memory;
                    break;
                } else{
                    struct Element* previousMemory = array
                            -> pivot
                            -> previousElement;
                    struct Element* nextMemory = array
                            -> pivot
                            -> nextElement;
                    previousMemory -> nextElement = nextMemory;
                    nextMemory -> previousElement = previousMemory;
                    array
                    -> pivot
                    -> nextElement = NULL;
                    array
                    -> pivot
                    -> previousElement = NULL;
                    array -> pivot = nextMemory;
                    break;
                }
            } else{
                movePivot(array, 1);
            }
        }
    } else{
        exit(404);
    }
}

int main() {
    struct CyclicList array;
    array.counter = 0;
    addElement(&array, 5);
    addElement(&array, 4);
    addElement(&array, 8);
    addElement(&array, 11);
    printAllElements(array);
    printf("--------\n");
    deleteElement(&array, 5);
    deleteElement(&array, 4);
    deleteElement(&array, 8);
    deleteElement(&array, 11);
    printAllElements(array);

    return 0;
}
