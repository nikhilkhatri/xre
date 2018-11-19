#include "double_linked_list.h"
#include "xmalloc.h"

void create_node(Node **new_node,Node *prev, Node *next, int data) {
	//Node *new_node = (Node *)malloc(sizeof(Node));
	node_malloc(sizeof(Node), new_node);
	if (new_node) {
		ptrcpy(&((*new_node)->prev),prev);
		ptrcpy(&((*new_node)->next),next);
		(*new_node)->data = data;
		if (next) {
		  ptrcpy(&(next->prev),new_node);
		}
		if (prev) {
		  ptrcpy(&(prev->next),new_node);
		}
	}
}


int isEmpty(Node *list) {
	return list == NULL;
}


Node *prepend(Node *list, int data) {
     Node *new_node;
	 create_node(&new_node,NULL, list, data);
	 //printf("%p\n", new_node);
	 return new_node;
}


Node *append(Node *list, int data) 
{ 
   Node* new_node; 
   //Node *last = list; 
   create_node(&new_node, NULL, NULL, data);
   if (isEmpty(list)) { 
        return new_node; 
    } 
    Node *last = list;
    
    //ptrcpy(&last,list);  
    while (last->next != NULL) 
        last = last->next; 
  
  
    ptrcpy(&(last->next),new_node); 
    ptrcpy(&(new_node->prev),last); 
  
    return list; 
} 


Node* deleteNode(Node *list, Node *del) 
{ 
  printf("%p\n",del); 
  if (isEmpty(list) || del == NULL) 
    return list; 

  if (list == del) {
    ptrcpy(&(list) ,list->next);
  }

  if (del->next) {
    ptrcpy(&(del->next->prev),del->prev);
  }

  if (del->prev) {
    ptrcpy(&(del->prev->next) , del->next);
  }  

  printf("%p\n",del); 

  //free(del);
  return list;
  
}  



Node* deleteNodeAtGivenPos(Node *list, int index) 
{ 
   
  if (isEmpty(list) || index <= 0) 
    return list; 
  
  Node *cur = list; 
  
  
    //while(cur != NULL)
  for (int i = 1; i < index; cur != NULL, i++) 
    cur = cur->next;
  
    
  if (cur == NULL) 
    return list; 
  
    
  return deleteNode(list, cur); 
    
}     

Node* deleteAllOccurences(Node *list, int occur) 
{ 
   
  if (isEmpty(list)) 
      return; 

  Node *cur = list; 
  Node *next; 

 
  while (cur != NULL) { 

    if (cur->data == occur) { 
      next = cur->next; 
		  list = deleteNode(list, cur); 
		    ptrcpy(&(cur) , next); 
    } 
    else
      cur = cur->next;
  }

  return list;
} 
/*

void freelist(Node *list)
{
   Node *temp;

   while (list != NULL)
    {
       temp = list;
       list = list->next;
       free(temp);
    }

}*/
