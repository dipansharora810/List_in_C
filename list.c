//
//  list.c
//  xCodeAs1_300
//
//  Created by Dipansh Arora on 2020-05-27.
//  Copyright © 2020 Dipansh Arora. All rights reserved.
//

#include "list.h"

static List headsArray[LIST_MAX_NUM_HEADS];
static Node nodesArray[LIST_MAX_NUM_NODES];

static int headsUsed = 0; //num of elements used in headsArray
static int nodesUsed = 0; //

void* reusableHeads[LIST_MAX_NUM_HEADS];
void* reusableNodes[LIST_MAX_NUM_NODES];
static int reuseableHeadsCount = 0;
static int reuseableNodesCount = 0;


void Head_initializer(List* pList)
{
    pList->pCurrent = NULL;
    pList->pFirst = NULL;
    pList->pLast = NULL;
    pList->size  = 0;
    pList->afterEnd = 0;
    pList->beforeStart = 0;
}

List* List_create()
{
    
    printf("LIST CREATE (headused = %d)\n\n",headsUsed);
    if (headsUsed < LIST_MAX_NUM_HEADS)
    {
        headsArray[headsUsed].pFirst = NULL;
        headsArray[headsUsed].pLast = NULL;
        headsArray[headsUsed].pCurrent = NULL;
        headsArray[headsUsed].size = 0;
        headsArray[headsUsed].afterEnd = false;
        headsArray[headsUsed].beforeStart = false;
        headsUsed++;
        return &headsArray[headsUsed-1];
    }
    
    else if(reuseableHeadsCount!=0) //check if there's any previously deleted node is available for use
    {
        reuseableHeadsCount--;
        return reusableHeads[reuseableHeadsCount];
    }
    
    else
    {
        return NULL;
    }
}

int List_count(List* pList)
{
    printf("List_Count \n\n");
    return pList->size;
}

void* List_first(List* pList)
{
    if(pList->pFirst == NULL)
    {
        printf("List_first 1.0 \n\n");
        pList->pCurrent = NULL;
        return NULL;
    }
    else
    {
        printf("List_first 2.0 \n\n");
        
        if(pList->afterEnd == 1 || pList->beforeStart == 1)
        {
            pList->afterEnd = 0;
            pList->beforeStart = 0;
        }
        pList->pCurrent = pList->pFirst;
        return pList->pFirst->item;
    }
}

void* List_last(List* pList)
{
    
    
    if(pList->pLast == NULL)
    {
        printf("List_last 1.0 \n\n");
        pList->pCurrent = NULL;
        return NULL;
    }
    
    
    else
    {
        printf("List_last 2.0 \n\n");
        if(pList->afterEnd == 1 || pList->beforeStart == 1)
        {
            pList->afterEnd = 0;
            pList->beforeStart = 0;
        }
        pList->pCurrent = pList->pLast;
        return pList->pLast->item;
    }
}

void* List_next(List* pList)  //check this for errors
{
    if(pList->size == 0)
    {
        printf("List_next 1.0 \n\n");
        return NULL;
    }
    else if (pList->afterEnd == 1)
    {
        printf("List_next 2.0 \n\n");
        return NULL;
    }
    
    else if(pList->pCurrent == pList->pLast)
    {
        printf("List_next 3.0 \n\n");
        pList->pCurrent =NULL;
        pList->afterEnd = 1;
        return NULL;
    }
    
    else if(pList->beforeStart == 1)
    {
        printf("List_next 4.0 \n\n");
        
        pList->pCurrent = pList->pFirst;
        pList->beforeStart = 0;
        return pList->pCurrent->item;
    }
    
    else
    {
        printf("List_next 5.0 \n\n");
        pList->pCurrent = pList->pCurrent->pNext;
        return pList->pCurrent->item;
    }
}

void* List_prev(List* pList)
{
    if(pList->size == 0)
    {
        printf("List_prev 1.0 \n\n");
        return NULL;
    }
    
    else if(pList->beforeStart == 1)
    {
        printf("List_prev 2.0 \n\n");
        //         pList->pCurrent = NULL;
        return NULL;
    }
    
    else if(pList->pCurrent == pList->pFirst)
    {
        printf("List_prev 3.0 \n\n");
        pList->pCurrent = NULL;
        pList->beforeStart = true;
        return NULL;
    }
    
    else if (pList->afterEnd == 1)
    {
        printf("List_prev 4.0 \n\n");
        pList->pCurrent = pList->pLast;
        pList->afterEnd = 0;
        return pList->pCurrent->item;
        
    }
    else if(pList->pCurrent == pList->pLast)
    {
        printf("List_prev 5.0 \n\n");
        pList->pCurrent = pList->pLast->pPrev;
        return pList->pCurrent->item;
    }
    
    else
    {
        printf("List_prev 6.0 \n\n");
        pList->pCurrent = pList->pCurrent->pPrev;
        return pList->pCurrent->item;
    }
    
}

void* List_curr(List* pList)
{
    if(pList->afterEnd==1||pList->beforeStart==1)
    {
        printf("List_curr 1.0 \n\n");
        return NULL;
    }
    
    else if(pList->pCurrent!= NULL)
    {
        printf("List_curr 2.0 \n\n");
        return pList->pCurrent->item;
    }
    else
        return NULL;
}

int List_add(List* pList, void* pItem)
{
    if(pList == NULL || pItem == NULL)
        return -1;
    
    Node* temp = NULL;
    if(nodesUsed<LIST_MAX_NUM_NODES||reuseableNodesCount!=0)
    {
        
        if(nodesUsed<LIST_MAX_NUM_NODES)
        {
            temp = &nodesArray[nodesUsed];
            nodesUsed++;
        }
        else if(reuseableNodesCount!=0)
        {
            reuseableNodesCount--;
            temp = reusableNodes[reuseableNodesCount];
        }
        else
            return -1;
    }
    
    if(pList->size ==  0)  //means we are adding the first element to the list
    {
        printf("LIST_ADD   1.0 \n");
        
        temp->item = pItem;
        
        pList->pCurrent = temp;
        pList->pFirst = temp;
        pList->pLast = temp;
        
        pList->size++;
        
        temp->pNext = NULL;
        temp->pPrev = NULL;
        
        return 0;
        
    }
    else if (pList->beforeStart == 1) //if current is pointing to before the start of the list
    {
        printf("LIST_ADD   2.0 \n");
        temp->item = pItem;
        
        temp ->pNext = pList->pFirst;
        temp->pPrev = NULL;
        
        pList->pFirst->pPrev = temp;
        
        pList->pCurrent = temp;
        pList->pFirst =temp;
        
        pList->beforeStart=0;
        
        pList->size++;
        
        return 0;
        
    }
    
    
    else if(pList->afterEnd == 1) //if current is pointing to after the end of the list
    {
        printf("LIST_ADD   3.0 \n");
        temp->item = pItem;
        
        temp->pNext = NULL;
        temp->pPrev = pList->pLast;
        
        pList->pLast->pNext = temp;
        
        pList->pCurrent = temp;
        pList->pLast = temp;
        
        pList->afterEnd = 0;
        
        pList->size++;
        
        return 0;
    }
    
    else if(pList->size == 1)
    {
        printf("LIST_ADD   4.0 \n");
        temp->item = pItem;
        
        temp ->pNext = pList->pCurrent->pNext;
        temp->pPrev = pList->pCurrent;
        
        pList->pCurrent->pNext = temp;
        pList->pCurrent = temp;
        pList->pLast = temp;
        
        pList->size ++;
        return 0;
        
    }
    
    else if(pList->pCurrent == pList->pFirst) //if current is pointing to the first element
    {
        printf("LIST_ADD   5.0 \n");
        
        temp->item = pItem;
        
        temp ->pNext = pList->pCurrent->pNext;
        temp->pPrev = pList->pCurrent;
        
        pList->pCurrent->pNext->pPrev = temp;
        
        pList->pCurrent->pNext = temp;
        pList->pCurrent = temp;
        
        pList->size++;
        return 0;
    }
    
    else if(pList->pCurrent == pList->pLast) //if current is pointing to the last element
    {
        printf("LIST_ADD   6.0 \n");
        temp->item = pItem;
        
        temp ->pNext = pList->pCurrent->pNext;
        temp->pPrev = pList->pCurrent;
        
        pList->pCurrent->pNext = temp;
        pList->pCurrent = temp;
        pList->pLast = temp;
        
        pList->size++;
        
        return 0;
        
    }
    

    
    else if(pList->pCurrent!= NULL)  //current is pointing to the any element in the middle
    {
        printf("LIST_ADD   7.0 \n");
        temp->item = pItem;
        
        temp->pNext = pList->pCurrent->pNext;
        temp->pPrev = pList->pCurrent;
        
        pList->pCurrent->pNext->pPrev = temp;
        pList->pCurrent->pNext = temp;
        pList->pCurrent = temp;
        pList->size++;
        
        return 0;
        
    }
    else
    {
        printf("LIST_ADD   8.0 \n");
        return -1;
    }
        
    
}

int List_insert(List* pList, void* pItem)
{
    if(pList == NULL || pItem == NULL)
        return -1;
    Node* temp = NULL;
    if(nodesUsed<LIST_MAX_NUM_NODES||reuseableNodesCount!=0)
    {
        
        if(nodesUsed<LIST_MAX_NUM_NODES)
        {
            temp = &nodesArray[nodesUsed];
            nodesUsed++;
        }
        else if(reuseableNodesCount!=0)
        {
            reuseableNodesCount--;
            temp = reusableNodes[reuseableNodesCount];
        }
        else
            return -1;
    }
    
    if(pList->size ==  0)  //means we are adding the first element to the list
    {
        printf("LIST_INSERT   1.0 \n");
        temp->item = pItem;
        
        pList->pCurrent = temp;
        pList->pFirst = temp;
        pList->pLast = temp;
        
        pList->size++;
        
        temp->pNext = NULL;
        temp->pPrev = NULL;
        
        return 0;
        
    }
    
    
    else if(pList->afterEnd == true) //if current is pointing to after the end of the list
    {
        printf("LIST_INSERT   2.0 \n");
        temp->item = pItem;
        
        temp->pNext = NULL;
        temp->pPrev = pList->pLast;
        
        pList->pLast->pNext = temp;
        
        pList->pCurrent = temp;
        pList->pLast = temp;
        
        pList->afterEnd = 0;
        
        pList->size++;
        
        return 0;
    }
    
    else if (pList->beforeStart == true) //if current is pointing to before the start of the list
    {
        printf("LIST_INSERT   3.0 \n");
        temp->item = pItem;
        
        temp ->pNext = pList->pFirst;
        temp->pPrev = NULL;
        
        pList->pFirst->pPrev = temp;
        
        pList->pCurrent = temp;
        pList->pFirst =temp;
        
        pList->beforeStart=0;
        
        pList->size++;
        
        return 0;
        
    }
    
    else if(pList->pCurrent == pList->pFirst) //if current is pointing to the first element
    {
        printf("LIST_INSERT   4.0 \n");
        temp->item = pItem;
        
        temp->pNext = pList->pCurrent;
        temp ->pPrev =pList->pCurrent->pPrev; //in this case it'll point to NULL
        
        pList->pCurrent->pPrev = temp;
        
        pList->pFirst = temp;
        pList->pCurrent = temp;
        
        pList->size++;
        
        return 0;
    }
    
    else if(pList->pCurrent == pList->pLast) //if current is pointing to the last element
    {
        printf("LIST_INSERT   5.0 \n");
        temp->item = pItem;
        
        temp ->pNext = pList->pCurrent;
        temp->pPrev = pList->pCurrent->pPrev;
        
        pList->pCurrent->pPrev->pNext =temp;
        pList->pCurrent->pPrev = temp;
        
        pList->pCurrent = temp;
        
        pList->size++;
        
        return 0;
        
    }
    


    
    else if(pList->pCurrent!= NULL)  //current is pointing to the any element in the middle
    {
        printf("LIST_INSERT   6.0 \n");
        temp->item = pItem;
        
        temp->pNext = pList->pCurrent;
        temp->pPrev = pList->pCurrent->pPrev;
        
        
        pList->pCurrent->pPrev->pNext = temp;
        pList->pCurrent->pPrev = temp;
        
        pList->size++;
        
        return 0;
        
    }
    else
    {
        printf("LIST_INSERT   7.0 \n");
        return -1;
    }
        
    
}

int List_append(List* pList, void* pItem) //add an element at the end of the list
{
    printf("LIST_APPEND   \n\n");
    pList->pCurrent = pList->pLast;
    return List_add(pList, pItem);
    
}

int List_prepend(List* pList, void* pItem)
{
    printf("LIST_prepend   \n\n");
    pList->pCurrent = pList->pFirst;
    return List_insert(pList, pItem);
}

// Return current item and take it out of pList. Make the next item the current one.
// If the current pointer is before the start of the pList, or beyond the end of the pList,
// then do not change the pList and return NULL.
void* List_remove(List* pList)
{
    if(pList->pCurrent == NULL)
    {
        return NULL;
    }
    
    else if(pList->size==0)
    {
        printf("List_remove 1.0\n");
        return NULL;
    }
    else if(pList->beforeStart==1||pList->afterEnd==1)
    {
        printf("List_remove 3.0\n");
        return NULL;
    }
    
    
    else if (pList->size ==1) //only one element in the list
    {
        printf("List_remove 2.0\n");
        
        Node* temp = pList->pCurrent;
        pList->pCurrent = NULL;
        pList->pFirst = NULL;
        pList->pLast = NULL;
        
        pList->size--;
        
        reusableNodes[reuseableNodesCount] = temp;
        reuseableNodesCount++;
        return temp->item;
        
    }
    

    else if(pList->pCurrent == pList->pFirst)  //if first element is the current element
    {
        printf("List_remove 4.0\n");
        
        Node* temp = pList->pCurrent;
        
        pList->pCurrent = pList->pCurrent->pNext;
        pList->pFirst = pList->pCurrent;
        pList->pFirst->pPrev = NULL;
        
        pList->size--;
        
        reusableNodes[reuseableNodesCount] = temp;
        reuseableNodesCount++;
        return temp->item;
        
    }
    
    
    
    else if(pList->pCurrent == pList->pLast)
    {
        printf("List_remove 5.0\n");
        
        Node* temp = pList->pCurrent;
        
        
        pList->pLast= pList->pCurrent->pPrev;
        pList->pLast->pNext= NULL;
        
        pList->pCurrent = NULL;
        pList->afterEnd = 1;
        
        pList->size --;
        
        
        reusableNodes[reuseableNodesCount] = temp;
        reuseableNodesCount++;
        return temp->item;
        
        //        void* retitem = temp->item;
        //
        //        Node_initializer(temp);
        //        return retitem;
    }
    
    
    
    else
    {
        printf("List_remove 6.0\n");
        
        Node* temp = pList->pCurrent;
        pList->pCurrent = pList->pCurrent->pNext;
        temp->pPrev->pNext = temp->pNext;
        temp->pNext->pPrev = temp->pPrev;
        
        
        pList->size--;
        reusableNodes[reuseableNodesCount] = temp;
        reuseableNodesCount++;
        return temp->item;
    }
}

// Adds pList2 to the end of pList1. The current pointer is set to the current pointer of pList1.
// pList2 no longer exists after the operation; its head is available
// for future operations.
void List_concat(List* pList1, List* pList2)
{
    if(pList1 == NULL|| pList2 == NULL)
    {
        printf("LIST _ CONCAT   1.0\n");
        
        return;
    }
    
    if(pList1->size==0)
    {
        printf("LIST _ CONCAT   2.0\n");
        pList1->pFirst = pList2->pFirst;
        pList1->pCurrent= pList2->pCurrent;
        pList1->pLast = pList2->pLast;
        pList1->size = pList2->size;
        pList1->afterEnd= pList2->afterEnd;
        pList1->beforeStart= pList2->beforeStart;
        
        Head_initializer(pList2);
        
        reusableHeads[reuseableHeadsCount] = pList2; //now pList2 is a reusable head
        reuseableHeadsCount++;
        
    }
    else if(pList2->size==0)
    {
        printf("LIST _ CONCAT   3.0\n");
        Head_initializer(pList2);
        reusableHeads[reuseableHeadsCount] = pList2; //now pList2 is a reusable head
        reuseableHeadsCount++;
    }
    else
    {
        printf("LIST _ CONCAT   4.0\n");
        pList2->pFirst->pPrev = pList1->pLast;
        pList1->pLast->pNext = pList2->pFirst;
        pList1->pLast = pList2->pLast;
        pList1->size= pList1->size+pList2->size;
        
        Head_initializer(pList2);
        reusableHeads[reuseableHeadsCount] = pList2; //now pList2 is a reusable head
        reuseableHeadsCount++;
        
    }
    
}


// Return last item and take it out of pList. Make the new last item the current one.
// Return NULL if pList is initially empty.
void* List_trim(List* pList)
{
    if(pList->size == 0)
    {
        printf("LIST _ TRIM   1.0\n");
        return NULL;
    }
    
    else if(pList->size == 1)
    {
        printf("List_TRim 2.0\n");
        
        Node* temp = pList->pCurrent;
        pList->pCurrent = NULL;
        pList->pFirst = NULL;
        pList->pLast = NULL;
        
        pList->size--;
        
        reusableNodes[reuseableNodesCount] = temp;
        reuseableNodesCount++;
        return temp->item;
    }
        
    else
    {
        printf("LIST _ TRIM   3.0\n");
        pList->afterEnd = 0;
        pList->beforeStart = 0;
        
        
        pList->pCurrent = pList->pLast;
    
        Node* temp = pList->pCurrent;
        
        
        pList->pLast= pList->pCurrent->pPrev;
        pList->pLast->pNext= NULL;
        
        pList->pCurrent = pList->pLast;
        pList->size --;
        
        
        reusableNodes[reuseableNodesCount] = temp;
        reuseableNodesCount++;
        return temp->item;
        
    }
    
    
}


// Delete pList. pItemFreeFn is a pointer to a routine that frees an item.
// It should be invoked (within List_free) as: (*pItemFreeFn)(itemToBeFreedFromNode);
// pList and all its nodes no longer exists after the operation; its head and nodes are
// available for future operations.
// UPDATED: Changed function pointer type, May 19
void List_free(List* pList, FREE_FN pItemFreeFn)
{
    printf("LIST _FREE  \n\n");
    printf("LIST SIZE = %d\n\n",pList->size);
    
    int size = pList->size;
    for(int i= 0;i<size;i++)
    {
        printf( "i = %d\n\n",i);
        pList->pCurrent = pList->pLast;
        pItemFreeFn(pList->pCurrent->item);
        List_trim(pList);
    }
    
    printf("LIST _FREE  ENDS \n\n");
    
    Head_initializer(pList);
    reusableHeads[reuseableHeadsCount] = pList; //now pList is a reusable head
    reuseableHeadsCount++;
}
// Search pList, starting at the current item, until the end is reached or a match is found.
// In this context, a match is determined by the comparator parameter. This parameter is a
// pointer to a routine that takes as its first argument an item pointer, and as its second
// argument pComparisonArg. Comparator returns 0 if the item and comparisonArg don't match,
// or 1 if they do. Exactly what constitutes a match is up to the implementor of comparator.
//
// If a match is found, the current pointer is left at the matched item and the pointer to
// that ireturned.tem is returned. If no match is found, the current pointer is left beyond the end of
// the list and a NULL pointer is
//
// UPDATED: Added clarification of behaviour May 19
// If the current pointer is before the start of the pList, then start searching from
// the first node in the list (if any).

void* List_search(List* pList, COMPARATOR_FN pComparator, void* pComparisonArg)
{
   
    if(pList->beforeStart == 1)
    {
        
        printf("LIST_SEARCH  1.0 \n");
        pList->pCurrent = pList->pFirst;
    }
    
    while(pList->pCurrent!=NULL)
    {
        printf("USING WHILE LOOP IN LIST_SEARCH \n");
        
        if( pComparator(pList->pCurrent->item,pComparisonArg)==1 )
        {
            return pList->pCurrent->item;
        }
        List_next(pList);
    }
    
    pList->pCurrent = NULL;
    pList->afterEnd = 1;
    
    return NULL;
    
}



