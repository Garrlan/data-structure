# Lab week 03实验报告

姓名： 学号：

### 内容及目的：

![image-20220913143740905](C:\Users\garla\AppData\Roaming\Typora\typora-user-images\image-20220913143740905.png)

1. 写一个栈存储未使用的节点

2. 用node-base数组写两个list存放多项式polynomial，LP和LQ

3. 写加法，用LPQ存储LP、LQ
4. 释放的节点要放回设计的栈中





### 实验重点：

  首先设计一个栈stack，实验要求给出的n是30，那么stack的大小设置为30，由于这个栈在整个实验中都要用到，所以设置stack数组为全局变量。栈中存放的数据为抽象的地址，可以用随机数字来代替，数据类型为int。

##### 1.Stack函数

```
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
```

  由于使用到随机数，那么需要用到**time.h**头文件。这里我用的是逆放置，所以设置i=29，一直赋值到i=0。又由于数组初始化为0，为了避免在检查重复的过程中地址0与初始化的0有冲突，所以随机数是1~30。最后要打印每个stack的节点值（地址），按顺序打印，并附上not used的标签，栈初始化完成。

##### 2.不定式数据类型

  多项式由系数和指数组成，根据这一点可以先构造一个struct存储。（int，int）

  由于还有增加一个地址位，所以再构造一个struct存储。（int）

```
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
}nb;`
```



##### 3.Arraylp和Arraylq函数

  a.为了保证LP和LQ的随机性，还是要使用随机数来赋值系数，同时设置list_head和list_tail.

  b.保证指数的赋值是递增的，且指数范围0~29。注意：随机数为0时，指数将不变，不能出现这种情况，所以要有一个检测条件，我这里是设int check = -1，指数先赋值，后与check进行比较，如果一致，那么证明前一个指数和本轮指数一样，应该break排除。

  c.排除完指数一致之后，还要保证指数的范围在0~29，条件为index < 30，这种情况就可以进行赋值了。系数我选择的是0~99的随机数，LP是首先设置的，所以list_head 为 stack[0]，每使用一个栈的分配地址，就打印一条语句说明使用了栈里的具体值。

  d.如果本轮指数>=30，那么说明构建LP结束，LP尾节点应该指向NULL（这里以-1代替）。打印语句，说明LP构建成功以及list_head,list_tail的值。

  e.设置LQ的过程类似，只是系数和指数的随机数范围不同，因为随机数的原理是通过电脑时间构造的，如果范围相同，那么将得到两个一模一样的数值。

  f.分别打印LP和LQ的数据，（系数，指数，地址）

```
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
			printf("LP set poly success！there are %d node\n",i);
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
			printf("LQ set poly success！there are %d nodes\n",usedlq-usedlp);
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
```



##### 4.Add函数

  a.参数为两个nb类型的指针，即LP和LQ。

  b.基本思想是在两个数组LP和LQ分别设置一个表示遍历位置的 i 和 j，由于指数都是递增的，所以把其中一个数组遍历完，未遍历的那个数组就可以直接写入。系数之和为零的不写入LPQ

  c.打印LPQ的数值

```
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
```



##### 5.回收不使用的地址

```
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
```

  在LP、LQ、LPQ都分配完地址后，将LP、LQ的地址回收。

### 结果分析：

![stack](C:\Users\garla\AppData\Roaming\Typora\typora-user-images\image-20220913153118824.png)



![set_lp_lq_lpq](C:\Users\garla\AppData\Roaming\Typora\typora-user-images\image-20220913153213864.png)

![release](C:\Users\garla\AppData\Roaming\Typora\typora-user-images\image-20220913153259031.png)

