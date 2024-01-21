#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct block{
    char nameblock[10];
    size_t size;
    int status;
    struct block *link;
};
typedef struct block *BLOCK;

BLOCK getblock(size_t blocksize)
{
    BLOCK temp;
    temp=(BLOCK)malloc(sizeof(struct block)+ blocksize);
    if(temp==NULL){
        printf("\n no memory left for allocation\n");
        exit(0);
    }
    if(temp!=NULL)
    {   printf("enter the name of the block : ");
        scanf("%s",temp->nameblock);
        temp->size=blocksize;
        temp->status=0;
        temp->link=NULL;
    }
    return temp;
}

BLOCK allocate_memory(BLOCK memorylist,size_t blocksize,int* no_of_blocks)
{
    BLOCK temp,next;
    temp=getblock(blocksize);
    if(memorylist==NULL){
        temp->status=1;
        *no_of_blocks=*no_of_blocks+1;
        printf("%d: memory block: %p allocated for %s \tsize: %ld \n",*no_of_blocks,temp,temp->nameblock,temp->size);
        return temp;
    }
    next=memorylist;
    while(next->link!=NULL){
        next=next->link;
    }
    next->link=temp;
    temp->status=1;
    *no_of_blocks=*no_of_blocks+1;
     printf("%d memory block: %p allocated for %s \tsize: %ld\n ",*no_of_blocks,temp,temp->nameblock,temp->size);
    return memorylist;
}

BLOCK deallocatememory(BLOCK memorylist, char n[]) {
    BLOCK temp, pre, cur;

    if (memorylist == NULL) {
        printf("Error: Never allocated memory(memory blocks are empty)\n");
        return NULL;
    }
    
    if (strcmp(memorylist->nameblock, n) == 0) {
        printf("The memory block %p for %s is deallocated\n", memorylist, memorylist->nameblock);
        temp=memorylist;
        memorylist=memorylist->link;
        free(temp);
        return memorylist;
    }
    
    pre=memorylist;
    cur=memorylist->link;
    
    while(cur!=NULL)
    {
        if(strcmp(cur->nameblock,n)==0){
            pre->link=cur->link;
            printf("The memory block %p for %s is deallocated\n", cur, cur->nameblock);
            free(cur);
            return memorylist;
        }
        pre=cur;
        cur=cur->link;
    }
    printf("the memory was never allocated to %s to deallocate it\n",n);
    return memorylist;
}

void display(BLOCK memorylist)
{
   if(memorylist==NULL)
   {
       printf("no memory blocks are allocated to display\n");
       return;
   } 
   printf("THE MEMORY BLOCKS ALLOCATED ARE:\n");
   while(memorylist!=NULL)
   {
       printf("Memory block: %p\t\tSize:%ld\t\tBlock Name:%s\n",memorylist,memorylist->size,memorylist->nameblock);
       memorylist=memorylist->link;
   }
   return;
}

void main()
{   int no_of_blocks=0;
    size_t size;
    char name[10];
    BLOCK memorylist=NULL;    
    int choice;
    printf("Enter\n1.allocation of memoryblock\n2.deallocation of a memory block\n3.display all the addresses of allocated memory blocks\n4.exit\nMOTE:NAMES GIVEN TO MEMORY BLOCKS CANNOT BE REPEATED\n");
    for(;;)
    {   printf("\n");
        printf("Enter your choice: ");
        scanf("%d",&choice);
        switch(choice)
        {
            case 1:printf("enter the size of the block to be allocated: ");
                  scanf("%ld",&size);
                  memorylist=allocate_memory(memorylist,size,&no_of_blocks);
                  break;
                  
            case 2:printf("enter the name of the block that should be deallocated to free memory: ");
                   scanf("%s",name);
                   memorylist=deallocatememory(memorylist,name);
                   break;
                   
            case 3:display(memorylist);
                   break;
            
            case 4:exit(0);
            
            default:printf("please enter the right choice\n");
        }
    }
}
