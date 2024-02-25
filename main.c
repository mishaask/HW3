#include "StrList.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define BUFFER_SIZE 1000
char* UserInput();
int newInput();
int checkIndex();

int main(){

StrList* listP= StrList_alloc();
int input;
scanf("%d",&input);
getchar();

while(input != EOF&&input !=0){
if(input == 1){
    size_t n;
    size_t i = 0;
    char *word;
    scanf("%zu",&n);
    getchar();

    while(i < n){
    word = UserInput();
    StrList_insertLast(listP,word);
    i++;
    }
}

else if(input == 2){
    size_t i = checkIndex();
    char* string = UserInput();
    StrList_insertAt(listP,string,i-1);
}

else if(input == 3){
    if(StrList_size(listP)!=0) StrList_print(listP);
}

else if(input == 4){printf("%ld\n",StrList_size(listP));}

else if(input == 5){
    size_t i = checkIndex();
    StrList_printAt(listP,i);
}

else if(input == 6){printf("%d\n",StrList_printLen(listP));}

else if(input == 7){char* string = UserInput();
printf("%d\n",StrList_count(listP,string));
}

else if(input == 8){
    char* string = UserInput();
    StrList_remove(listP,string);
}


else if(input == 9){
    size_t i = checkIndex();
    StrList_removeAt(listP,i);
}

else if(input == 10){StrList_reverse(listP);}

else if(input == 11){
    while(StrList_size(listP)>0)
    StrList_removeAt(listP,1);
}

else if(input == 12){StrList_sort(listP);}

else if(input == 13){
    if(StrList_isSorted(listP))
    printf("true\n");
    else
    printf("false\n");
}

else{printf("wrong input please reinput");}
input = newInput();
}
StrList_free(listP);
    return 0;
}

int checkIndex(){//for recieving index
    size_t i;
    scanf("%ld",&i);
    getchar();
    return i;
}

int newInput(){//scan input func
    int input;
    scanf("%d",&input);
    getchar();
    return input;
}

char* UserInput(){// we use a Buffer to know how much memory to allocate for each input dynamically 
    char buffer[BUFFER_SIZE];
    char c;
    int buffIndex = 0;
    int strLength = 0;

    while((c = getchar()) != '\n' && c != ' '&& c != EOF&&strLength < BUFFER_SIZE-1){
        buffer[buffIndex] = c;
        buffIndex++;
        strLength++;
    }
    buffer[buffIndex]='\0';

    char *string = (char*)malloc(sizeof(char)*(strLength+1));
    if(string == NULL){return NULL;}
     
    strcpy(string, buffer);
    return string;
}