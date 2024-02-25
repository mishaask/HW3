#include "StrList.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


typedef struct _node {
    char *string;
    struct _node * _next;
} Node;


typedef struct _StrList {
    Node* _head;
    size_t _size;
}StrList;

Node* Node_alloc(const char *string, Node* next) {
	Node* p= (Node*)malloc(sizeof(Node));
    if (p == NULL) {return NULL;}
    
	p->string= strdup(string);
    if (p->string == NULL) {
        free(p);
        return NULL;}

	p->_next= next;
	return p;
}

StrList* StrList_alloc() {
	StrList* p= (StrList*)malloc(sizeof(StrList));
    if (p == NULL) {return NULL;}

	p->_head= NULL;
	p->_size= 0;
	return p;
}

void Node_free(Node* node) {
	free(node);
}

void StrList_free(StrList* StrList) {
	if (StrList==NULL) return;
	Node* p1= StrList->_head;
	Node* p2;
	while(p1) {
		p2= p1;
		p1= p1->_next;
		Node_free(p2);
	}
	free(StrList);
}

size_t StrList_size(const StrList* StrList) {
	return StrList->_size;
}

char* StrList_firstString(const StrList* StrList) {
	return StrList->_head->string;
}

void StrList_insertFirst(StrList* StrList,const char *string) {
	StrList->_head= Node_alloc(string,StrList->_head);
	++(StrList->_size);
}

void StrList_insertAt(StrList* StrList,const char* data,int index){
    size_t size = StrList_size(StrList);
    Node* currentNode = StrList -> _head;
    if(index>size+1||index<0) {printf("invalid index"); 
    return;}
    if(index == 0){StrList_insertFirst(StrList,data);
    return;}

    size_t i = 1;//i=1 because we start at head and move to index
    while(i <= index-1){
        currentNode = currentNode->_next;
        i++;
    }

    if(currentNode->_next == NULL){currentNode->_next = Node_alloc(data,NULL);}//we need to insert last
    else{//we insert between 2 nodes
    Node* helperNode = currentNode->_next->_next;
    currentNode->_next->_next = Node_alloc(data,helperNode);
    }

    StrList->_size++;
}

void StrList_insertLast(StrList* StrList,const char* data){
    size_t size = StrList_size(StrList);
    StrList_insertAt(StrList,data,size);
}

void StrList_print(const StrList* StrList) {
	const Node* p= StrList->_head;
    printf("%s",p->string);
	p= p->_next;
	while(p) {
		printf(" %s",p->string);
		p= p->_next;
	}
    printf("\n");
}

void StrList_printAt(const StrList* Strlist,int index) {
	const Node* p= Strlist->_head;
    size_t i = 1;
    
	while(i<=index) {
        p = p->_next;
        i++;
	}
    printf("%s\n",p->string);
}
int StrList_printLen(const StrList* Strlist){
    int size=0;
    const Node* p= Strlist->_head;
	while(p) {
		size += strcspn(p->string," ");
		p= p->_next;
	}
    return size;
}
int StrList_count(StrList* StrList, const char* data){
    int count=0;
    const Node* p= StrList->_head;
	while(p) {
		if(strcmp(data,p->string)==0) count++;
		p= p->_next;
	}
    return count;
}
void StrList_remove(StrList* StrList, const char* data){
    Node* p= StrList->_head;
    while(p && strcmp(data,p->string)==0){
        Node* phelper = p;
        p = p->_next;
        Node_free(phelper);
        StrList->_size--;
        StrList->_head = p;
    }
	while(p && p->_next) {
		if(strcmp(data,p->_next->string)==0) {
            Node* phelper =p->_next;
            p->_next = p->_next->_next;
            Node_free(phelper);
            StrList->_size--;
        } else {
            p = p->_next;
        }
	}
}

void StrList_removeAt(StrList* StrList, int index){
    Node* p= StrList->_head;
    size_t size = StrList->_size;
    if(index>size || index <1)return;
    if(index == 1){StrList->_head = StrList->_head->_next;
    Node_free(p);
    StrList->_size--;
    }
    else{
    int i = 1;
    while(i<index){
    p= p->_next;
    i++;}

    Node* phelper =p->_next;
    p->_next = p->_next->_next;
    Node_free(phelper);
    StrList->_size--;}
}


char* StrList_firstData(const StrList* StrList){
    return StrList->_head->string;
}

int StrList_isEqual(const StrList* StrList1, const StrList* StrList2) {
	const int eq= 1;
	const int neq= 0;
	
	const Node* p1= StrList1->_head;
	const Node* p2= StrList2->_head;
	while(p1) {
		if (p2==NULL||strcmp(p1->string,p2->string) != 0) return neq;
		p1= p1->_next;
		p2= p2->_next;
	}
	if (p2!=NULL) return neq;
	return eq;
}

StrList* StrList_clone(const StrList* StrList) {
	struct _StrList* ret= StrList_alloc();
	const Node* old= StrList->_head;
	Node* * copy= &(ret->_head);
	ret->_size= StrList->_size;
	while(old) {
		*copy= Node_alloc(old->string,NULL);
		old= old->_next;
		copy= &((*copy)->_next);
	}
	return ret;
}
void StrList_reverse(StrList* StrList) {
    Node* prev = NULL;
    Node* current = StrList->_head;
    Node* next = NULL;

    while (current != NULL) {
        next = current->_next;
        current->_next = prev;
        prev = current;
        current = next;
    }

    StrList->_head = prev;
}
void StrList_sort(StrList* StrList) {//Sort using bubble sort
    Node* current = StrList->_head;
    Node* index = NULL;
    char* temp;

    if (StrList->_head == NULL) {
        return; 
    } else {
        while (current != NULL) {
            index = current->_next;
            while (index != NULL) {
                if (strcmp(current->string, index->string) > 0) {
                    temp = current->string;
                    current->string = index->string;
                    index->string = temp;
                }
                index = index->_next;
            }
            current = current->_next;
        }
    }
}

int StrList_isSorted(StrList* StrList) {
    Node* current = StrList->_head;

    if (current == NULL || current->_next == NULL) {
        return 1;
    }

    while (current->_next != NULL) {
        if (strcmp(current->string, current->_next->string) > 0) {
            return 0;
        }
        current = current->_next;
    }
    return 1;
}
