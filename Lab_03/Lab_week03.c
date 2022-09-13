#include<stdio.h>
#include<stdlib.h>
#include<time.h>
//polynomials(xishu+zhishu)
typedef struct Poly
{
	int coe;//xishu
	int index;//zhishu
}poly;
//node-base array(poly+next)
typedef struct Node_base
{
	poly p;
	int next;
}nb;

int stack[30]={0};
nb LP[30]={0};
nb LQ[30]={0};
nb LPQ[30]={0}; 
int usedlp,usedlq,usedlpq;
//stack array 
void Stack(){
	//static int stack[30] = {0};
	int a,j,i=29;
	srand((unsigned)time(0));
	while(i>=0)
	{
		a=rand()%30+1;
		for(j=i;j<30;j++)
		{
			if(a==stack[j]) break;
		}
		if(j==30)
		{
			stack[i] = a;
			i--;
		}
	}
	for(a=0;a<30;a++)
	{
		stack[a] -= 1;
		printf("%d-th node is %d, not used\n",a+1,stack[a]);
	}
	printf("----------------------------------------------\n\n");
}

//LP Node_base storge with arrays
void Arraylp()
{
	int coe,index=0,loc;
	int i=0,j,check=-1;
	int list_head=0,list_tail;
	srand((unsigned)time(0));
	list_head = stack[0];
	printf("-------------------set LP----------------------\n");
	while(index<30)
	{
		index += rand()%30;
		if(check==index) break;
		else if(index<30)
		{
			loc = stack[i];
			coe = rand()%100;
			LP[loc].p.coe = coe;
			LP[loc].p.index = index;
			printf("%d-th node is %d, used\n",i+1,stack[i]);
			i+=1;
			usedlp = i;
			LP[loc].next = stack[i];
			list_tail = loc;
			check = index;
		}
		else
		{
			LP[list_tail].next = -1;	
			printf("LP set poly success£¡there are %d node\n",i);
			printf("LP list_head = %d\nLP list_tail = %d\n",list_head,list_tail);
		}
	}		
	printf("********************LP map*********************\n");
	for(j=0;j<usedlp;j++)
	{
		printf("(%d,%d,%d)\n",LP[stack[j]].p.coe,LP[stack[j]].p.index,LP[stack[j]].next);
	}
	printf("----------------------------------------------\n\n");
}

//LQ Node_base storge with arrays
void Arraylq()
{
	int coe,index=0,loc;
	int i=0,j,check=-1;
	int list_head=0,list_tail;
	srand((unsigned)time(0));
	usedlq = usedlp;
	list_head = stack[usedlq];
	printf("-------------------set LQ----------------------\n");
	while(index<30)
	{
		index+=rand()%29+1;
		if(check==index) break;
		else if(index<30)
		{
			loc = stack[usedlq];
			coe = rand()%100-100;
			LQ[loc].p.coe = coe;
			LQ[loc].p.index = index;
			printf("%d-th node is %d, used\n",usedlq+1,stack[usedlq]);
			usedlq+=1;
			LQ[loc].next = stack[usedlq];
			list_tail = loc;
		}
		else
		{
			LQ[list_tail].next = -1;	
			printf("LQ set poly success£¡there are %d nodes\n",usedlq-usedlp);
			printf("LQ list_head = %d\nLQ list_tail = %d\n",list_head,list_tail);
		}
	}		
	printf("********************LQ map*********************\n");
	for(j=usedlp;j<usedlq;j++)
	{
		printf("(%d,%d,%d)\n",LQ[stack[j]].p.coe,LQ[stack[j]].p.index,LQ[stack[j]].next);
	}
	printf("----------------------------------------------\n\n");
}

void Add(nb *a,nb *b)
{
	int i=0,j=usedlp,k=usedlq,s,t=0;
	printf("------------------Add LP+LQ---------------------\n");
	while(i < usedlp && j < usedlq)
	{
		if(a[stack[i]].p.index < b[stack[j]].p.index)
		{
			LPQ[stack[k]].p.index = a[stack[i]].p.index;
			LPQ[stack[k]].p.coe = a[stack[i]].p.coe;
			k+=1;
			i+=1;
			LPQ[stack[k-1]].next = stack[k];
			printf("%d-th node is %d, used\n",k,stack[k-1]);
		}
		else if(a[stack[i]].p.index == b[stack[j]].p.index)
		{
			if(a[stack[i]].p.coe + b[stack[j]].p.coe == 0)
			{
				printf("coe's sum = 0");
				i+=1;
				j+=1;
			}
			else
			{
				LPQ[stack[k]].p.index = a[stack[i]].p.index;
				LPQ[stack[k]].p.coe = a[stack[i]].p.coe + b[stack[j]].p.coe;
				k+=1;
				i+=1;
				j+=1;
				LPQ[stack[k-1]].next = stack[k];
				printf("%d-th node is %d, used\n",k,stack[k-1]);				
			}
		}
		else
		{
			LPQ[stack[k]].p.index = b[stack[j]].p.index;
			LPQ[stack[k]].p.coe = b[stack[j]].p.coe;
			k+=1;
			j+=1;
			LPQ[stack[k-1]].next = stack[k];
			printf("%d-th node is %d, used\n",k,stack[k-1]);			
		}
	}
	if(i==usedlp)
	{
		for(j;j<usedlq;j++)
		{
			LPQ[stack[k]].p.coe = b[stack[j]].p.coe;
			LPQ[stack[k]].p.index = b[stack[j]].p.index;
			k+=1;
			printf("%d-th node is %d, used\n",k,stack[k-1]);
			if(j+1==usedlq) LPQ[stack[k-1]].next = -1;
			else LPQ[stack[k-1]].next = stack[k];
		}
	}
	else if(j==usedlq)
	{
		for(i;i<usedlp;i++)
		{
			LPQ[stack[k]].p.coe = a[stack[i]].p.coe;
			LPQ[stack[k]].p.index = a[stack[i]].p.index;
			k+=1;
			printf("%d-th node is %d, used\n",k,stack[k-1]);
			if(i+1 == usedlp) LPQ[stack[k-1]].next = -1;
			else LPQ[stack[k-1]].next = stack[k];
		}
	}
	usedlpq = k;
	printf("********************LPQ map*********************\n");	
	for(s=usedlq;s<k;s++)
	{
		printf("(%d,%d,%d)\n",LPQ[stack[s]].p.coe,LPQ[stack[s]].p.index,LPQ[stack[s]].next);
	}
	printf("----------------------------------------------\n\n");
	printf("---------------release--------------\n");
	//lp release
	for(int r=usedlpq-1;r>=usedlpq-usedlp;r--)
	{
		stack[r]=stack[t];
		t++;
	}
	//lq release
	for(int u=usedlpq-usedlp-1;u>=usedlpq-usedlq;u--)
	{
		int v=usedlp;
		stack[u]=stack[v];
		v++;
	}	
	for(int l=usedlpq-usedlq;l<30;l++)
	{
		printf("%d-th node %d, not used\n",l+1,stack[l]);
	}
	printf("---------------finish----------------\n");
}


//LP: 0->uselp-1
//LQ: usedlp->usedlq-1
//LPQ: usedlq->k-1


int main(){
	//set stack
	Stack();
	//set LP,LQ
	Arraylp();
	Arraylq();
	//Add LP,LQ
	Add(LP,LQ);
	printf("usedlp = %d\tusedlq = %d\tusedlpq = %d",usedlp,usedlq,usedlpq);
	return 0;
}
