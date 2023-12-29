#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define max 3
#define price 1
int b=1;
typedef struct {
	int day;          
	int hour;       
	int min;
}TIME;		//时间结点	
typedef struct{
	char num[10];   //车牌号
	TIME time;      //进入停车场的时间 
	int n;          //进入停车场的位置
}information;
//栈结构体定义
typedef struct node{
	information data;
	struct node *next;
}stacknode;	stacknode *top1,*top2;
//队列结构体定义
typedef struct {
	information data;
	stacknode *front,*rear;
}LQueue;LQueue *Q;	
//函数声明部分//
stacknode *Init();							   //栈的初始化
stacknode *into(stacknode *top1,LQueue *Q);       //初始化车辆进入                     
int expenses(stacknode *p,int x,int y);        //停车费用计算函数
stacknode *leave(stacknode *top1,char str[],LQueue *Q);   //车辆驶出出场函数
LQueue *InitLQue();                  //初始化队列函数   
LQueue *wait(LQueue *q,stacknode *s);              //车辆进入候车便道函数   
int EmptyLQue(LQueue *q);                   //判断候车便道有无等待车辆函数
stacknode *out(LQueue *q);                       //候车区车辆出队                                       
stacknode *LQinto(stacknode *p,stacknode *top1); //从候车便道进入停车场函数                 
void show(stacknode *top1);      //显示停车场所有信息函数
void T_shou(LQueue *Q);				  //显示候车区信息
					/*函数部分*/
//主函数
int main(){	
	char str[10];
	Q=InitLQue();
	top1=Init();
	top2=Init();

	int i;
	printf("\t\t\t*************************************\n");
	printf("\t\t\t\t  停车场管理系统\n");
	printf("\t\t\t||    1. 车辆进入停车场            ||\n");
	printf("\t\t\t||    2. 车辆离开停车场            ||\n");
	printf("\t\t\t||    3. 显示停车场内所有车辆信息  ||\n");
	printf("\t\t\t||    4. 显示候车区内所有车辆信息  ||\n");
	printf("\t\t\t||    5. 退出                      ||\n");
	printf("\t\t\t*************************************\n");
	while(i!=5){
		printf("\t请输入选项1-5:");
		scanf("%d",&i);
		switch(i){
		case 1:
			top1=into(top1,Q);
			break;
		case 2:
			printf("请输入离开车辆的车牌号：");
			scanf("%s",str);
			top1=leave(top1,str,Q);
			break;
		case 3:show(top1);break;
		case 4:T_shou(Q);break;
		case 5:exit(1);
		default:printf("输入错误，请重新输入1-5:");
			break;
		}		
	}
}
                    /*子函数*/
//初始化
stacknode *Init(){
	stacknode *top;
	top=(stacknode *)malloc(sizeof(stacknode));
	top=NULL;
	return top;
}
//初始化车辆进入
stacknode *into(stacknode *top1,LQueue *Q){	
	stacknode *p,*q;
	time_t rawtime;     //调用系统时间函数
	struct tm *timeinfo;  //时间结点
	time(&rawtime);
	timeinfo=localtime(&rawtime);
	p=(stacknode *)malloc(sizeof(stacknode));
	if(p==NULL){
		printf("内存分配失败");
		return top1;
	}
	printf("请输入进入停车场车辆的车牌号:");
	scanf("%s",p->data.num);
	q=top1;
	p->data.time.day=timeinfo->tm_mday;
	p->data.time.hour=timeinfo->tm_hour;
	p->data.time.min=timeinfo->tm_min;
	p->data.n=b;
	if(b>max){
		printf("停车场已满,请在便道等候!\n");
		wait(Q,p);
		return top1;
	}
	if(top1==NULL){
		p->next=NULL;
		top1=p;		
	}
	else{
		p->next=top1;
		top1=p;
	}
	b++;
	printf("车辆进入停车场成功，时间已经自动载入!\n");
	printf("车牌为%s的汽车驶入时间为:%d号%d点%d分\n",top1->data.num,top1->data.time.day,top1->data.time.hour,top1->data.time.min);
	return top1;
}
//停车费用计算函数
int expenses(stacknode *p,int x1,int x2,int x3){
	int w;
	if(x3!=0)
		w=(x1*24+x2+1-(p->data.time.day*24+p->data.time.hour))*price;
	else
		w=(x1*24+x2-(p->data.time.day*24+p->data.time.hour))*price;	
	return w;
}
//车辆驶出出场函数
stacknode *leave(stacknode *top1,char str[],LQueue *Q){
	int i,day,hour,min;
	time_t rawtime;
	struct tm *timeinfo;
	time(&rawtime);
	timeinfo=localtime(&rawtime);
	day=timeinfo->tm_mday;
	hour=timeinfo->tm_hour;
	min=timeinfo->tm_min;
	stacknode *p,*q;	
	if(top1==NULL){
		printf("停车场没有车辆!\n");
		return top1;
	}
	q=(stacknode *)malloc(sizeof(stacknode));
	if(q==NULL){
		printf("内存分配失败");
		return top1;
	}
	q=top1;
	while(q!=NULL){
		if(strcmp(q->data.num,str)==0)
			break;
		q=q->next;
	}	
	if(q==NULL){
		printf("输入有误，该车辆不在停车场!\n");
		return top1;
	}
	for(i=top1->data.n;i>q->data.n;i--){ //将该车辆之前的车停入临时地点 
		p=(stacknode *)malloc(sizeof(stacknode));
		if(p==NULL){
			printf("内存分配失败");
			return top1;
		}
		strcpy(p->data.num,top1->data.num);
		p->data.time=top1->data.time;
		p->data.n=top1->data.n-1;
		top1=top1->next;
		if(top2==NULL){
			p->next=NULL;
			top2=p;
		}
		else{
			p->next=top2;
			top2=p;
		}
	}
	top1=top1->next;//将该车辆出停车场 
	while(top2!=NULL){//将临时停放的车辆停入停车场 
		p=(stacknode *)malloc(sizeof(stacknode));
		if(p==NULL){
			printf("内存分配失败");
			return top1;
		}
		p->data.n=top2->data.n;
		strcpy(p->data.num,top2->data.num);
		p->data.time=top2->data.time;
		p->next=top1;
		top1=p;
		top2=top2->next;
	}
		if(EmptyLQue(Q)){//车辆停出，判断便道是否有车辆等候 
			p=out(Q);
			p->data.n--;
			top1=LQinto(p,top1);
		}
		else 
			b--;
		printf("车牌为%s的汽车驶出时间为:%d号%d点%d分\n",q->data.num,day,hour,min);
		printf("车辆驶出停车场需要缴纳的费用为:%d元\n",expenses(q,day,hour,min));		
		return top1;
}
//队列函数初始化
	LQueue *InitLQue(){
		LQueue *Q;
		stacknode *p;
		Q=(LQueue *)malloc(sizeof(LQueue));
		p=(stacknode *)malloc(sizeof(stacknode));
		p->next=NULL;
		Q->front=Q->rear=p;
		return Q;
	}
	//候车区队列入队
	LQueue *wait(LQueue *q,stacknode *s){		
		s->next=NULL;
		q->rear->next=s;
		q->rear=s;
		return q;		
	}
	//判断候车便道有无车辆等待
	int EmptyLQue(LQueue *q){
		if(q->front==q->rear)
			return 0;
		else
			return 1; 
	}
	//候车区车辆出队
	stacknode *out(LQueue *q){
		stacknode *p;
		p=q->front->next;
		if(q->front->next==q->rear){
			q->rear=q->front;
			return p;
		}
		else
			q->front->next=p->next;
		p->next=NULL;
		return p;
	}
	//候车队列进入停车场
	stacknode *LQinto(stacknode *p,stacknode *top1){	
        p->next=top1;
		top1=p;
		return top1;
	}
	//显示停车场内所有车辆信息
	void show(stacknode *top1){
		printf("   停车场内全部车辆信息表\n");
		if(top1==NULL)
			printf("  停车场内无车!\n");
		else{
				printf("车牌号      进入时间       位置\n");
			while(top1!=NULL){
				printf(" %s        %d号%d点%d分   第%d位\n",top1->data.num,top1->data.time.day,top1->data.time.hour,top1->data.time.min,top1->data.n);
				top1=top1->next;
			}
		}		
	}
	//显示候车区的汽车信息
	void T_shou(LQueue *Q){
		LQueue *q;
		q=(LQueue *)malloc(sizeof(LQueue));
		q->rear=Q->rear->next;
		printf("     候车区信息\n");
		if(q->front==q->rear)
			printf("候车区没有车辆!\n");
		else{
			printf("车牌号      进入时间\n");
			while(q!=NULL){
				printf("%s		%d号%d点%d分",q->data.num,q->data.time.day,q->data.time.hour,q->data.time.min);
				q->rear=q->rear->next;
			}
		}
	}

