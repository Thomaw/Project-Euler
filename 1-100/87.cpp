#include<stdio.h>
#include<malloc.h>
#include<math.h>

long p[910]={2},square[910],count,size;
int a[7100];

struct node{
  long n;
  int pos;
  struct node*next;
  }*head=0,*cur=0,*tail=0,*temp=0;

void prime(){
  int i,j,n=0;
  for(i=4;i<=7080;i+=2) a[i]=1;
  for(i=3;i<=7080;i+=2){
    if(!a[i]){
      p[++n]=i;
      for(j=i*2;j<=7080;j+=i) a[j]=1;
      }
    }
  }

void sort_and_count(){
  int x,i;
  long sum;
  while(1){
    x=head->pos;
    sum=head->n;
    temp=head->next;
    free(head);
    head=temp;
    count++;
    if(!head) break;
    while(1){
      sum-=square[x++];
      sum+=square[x];
      if(sum>49999999) break;
      if(sum<head->n){
	cur=(struct node*)malloc(size);
	cur->n=sum;
	cur->pos=x;
	cur->next=head;
	head=cur;
	break;
	}
      else if(sum>tail->n){
	cur=(struct node*)malloc(size);
	cur->n=sum;
	cur->pos=x;
	tail->next=cur;
	tail=cur;
	tail->next=0;
	break;
	}
      else if(sum>head->n&&sum<tail->n){
	while(temp->next->n<sum) temp=temp->next;
	if(temp->next->n>sum){
	  cur=(struct node*)malloc(size);
	  cur->n=sum;
	  cur->pos=x;
	  cur->next=temp->next;
	  temp->next=cur;
	  break;
	  }
	}
      }
    }
  }

void third_fourth_power_addition(){
  int i,j;
  long x,cube[75],quad[25];
  size=sizeof(struct node);
  for(i=0;i<909;i++) square[i]=p[i]*p[i];
  for(i=0;i<73;i++) cube[i]=square[i]*p[i];
  for(i=0;i<23;i++) quad[i]=cube[i]*p[i];
  for(i=0;i<23;i++){
    for(j=0;j<73;j++){
      if(!head){
	head=(struct node*)malloc(size);
	head->n=quad[0]+cube[0]+4;
	head->pos=0;
	tail=head;
	head->next=0;
	}
      else{
	x=quad[i]+cube[j]+4;
	if(x>49999999) break;
	if(head->n>x){
	  cur=(struct node*)malloc(size);
	  cur->n=x;
	  cur->pos=0;
	  cur->next=head;
	  head=cur;
	  }
	else if(tail->n<x){
	  cur=(struct node*)malloc(size);
	  cur->n=x;
	  cur->pos=0;
	  tail->next=cur;
	  tail=cur;
	  tail->next=0;
	  }
	else if(head->n<x&&tail->n>x){
	  for(temp=head;temp->next->n<x;temp=temp->next);
	  if(temp->next->n>x){
	    cur=(struct node*) malloc(size);
	    cur->n=x;
	    cur->pos=0;
	    cur->next=temp->next;
	    temp->next=cur;
	    }
	  }
	}
      }
    }
  }

void main(){
  prime();
  third_fourth_power_addition();
  sort_and_count();
  printf("%li\n",count);
  }