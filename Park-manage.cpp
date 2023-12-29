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
}TIME;		//ʱ����	
typedef struct{
	char num[10];   //���ƺ�
	TIME time;      //����ͣ������ʱ�� 
	int n;          //����ͣ������λ��
}information;
//ջ�ṹ�嶨��
typedef struct node{
	information data;
	struct node *next;
}stacknode;	stacknode *top1,*top2;
//���нṹ�嶨��
typedef struct {
	information data;
	stacknode *front,*rear;
}LQueue;LQueue *Q;	
//������������//
stacknode *Init();							   //ջ�ĳ�ʼ��
stacknode *into(stacknode *top1,LQueue *Q);       //��ʼ����������                     
int expenses(stacknode *p,int x,int y);        //ͣ�����ü��㺯��
stacknode *leave(stacknode *top1,char str[],LQueue *Q);   //����ʻ����������
LQueue *InitLQue();                  //��ʼ�����к���   
LQueue *wait(LQueue *q,stacknode *s);              //��������򳵱������   
int EmptyLQue(LQueue *q);                   //�жϺ򳵱�����޵ȴ���������
stacknode *out(LQueue *q);                       //������������                                       
stacknode *LQinto(stacknode *p,stacknode *top1); //�Ӻ򳵱������ͣ��������                 
void show(stacknode *top1);      //��ʾͣ����������Ϣ����
void T_shou(LQueue *Q);				  //��ʾ������Ϣ
					/*��������*/
//������
int main(){	
	char str[10];
	Q=InitLQue();
	top1=Init();
	top2=Init();

	int i;
	printf("\t\t\t*************************************\n");
	printf("\t\t\t\t  ͣ��������ϵͳ\n");
	printf("\t\t\t||    1. ��������ͣ����            ||\n");
	printf("\t\t\t||    2. �����뿪ͣ����            ||\n");
	printf("\t\t\t||    3. ��ʾͣ���������г�����Ϣ  ||\n");
	printf("\t\t\t||    4. ��ʾ���������г�����Ϣ  ||\n");
	printf("\t\t\t||    5. �˳�                      ||\n");
	printf("\t\t\t*************************************\n");
	while(i!=5){
		printf("\t������ѡ��1-5:");
		scanf("%d",&i);
		switch(i){
		case 1:
			top1=into(top1,Q);
			break;
		case 2:
			printf("�������뿪�����ĳ��ƺţ�");
			scanf("%s",str);
			top1=leave(top1,str,Q);
			break;
		case 3:show(top1);break;
		case 4:T_shou(Q);break;
		case 5:exit(1);
		default:printf("�����������������1-5:");
			break;
		}		
	}
}
                    /*�Ӻ���*/
//��ʼ��
stacknode *Init(){
	stacknode *top;
	top=(stacknode *)malloc(sizeof(stacknode));
	top=NULL;
	return top;
}
//��ʼ����������
stacknode *into(stacknode *top1,LQueue *Q){	
	stacknode *p,*q;
	time_t rawtime;     //����ϵͳʱ�亯��
	struct tm *timeinfo;  //ʱ����
	time(&rawtime);
	timeinfo=localtime(&rawtime);
	p=(stacknode *)malloc(sizeof(stacknode));
	if(p==NULL){
		printf("�ڴ����ʧ��");
		return top1;
	}
	printf("���������ͣ���������ĳ��ƺ�:");
	scanf("%s",p->data.num);
	q=top1;
	p->data.time.day=timeinfo->tm_mday;
	p->data.time.hour=timeinfo->tm_hour;
	p->data.time.min=timeinfo->tm_min;
	p->data.n=b;
	if(b>max){
		printf("ͣ��������,���ڱ���Ⱥ�!\n");
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
	printf("��������ͣ�����ɹ���ʱ���Ѿ��Զ�����!\n");
	printf("����Ϊ%s������ʻ��ʱ��Ϊ:%d��%d��%d��\n",top1->data.num,top1->data.time.day,top1->data.time.hour,top1->data.time.min);
	return top1;
}
//ͣ�����ü��㺯��
int expenses(stacknode *p,int x1,int x2,int x3){
	int w;
	if(x3!=0)
		w=(x1*24+x2+1-(p->data.time.day*24+p->data.time.hour))*price;
	else
		w=(x1*24+x2-(p->data.time.day*24+p->data.time.hour))*price;	
	return w;
}
//����ʻ����������
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
		printf("ͣ����û�г���!\n");
		return top1;
	}
	q=(stacknode *)malloc(sizeof(stacknode));
	if(q==NULL){
		printf("�ڴ����ʧ��");
		return top1;
	}
	q=top1;
	while(q!=NULL){
		if(strcmp(q->data.num,str)==0)
			break;
		q=q->next;
	}	
	if(q==NULL){
		printf("�������󣬸ó�������ͣ����!\n");
		return top1;
	}
	for(i=top1->data.n;i>q->data.n;i--){ //���ó���֮ǰ�ĳ�ͣ����ʱ�ص� 
		p=(stacknode *)malloc(sizeof(stacknode));
		if(p==NULL){
			printf("�ڴ����ʧ��");
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
	top1=top1->next;//���ó�����ͣ���� 
	while(top2!=NULL){//����ʱͣ�ŵĳ���ͣ��ͣ���� 
		p=(stacknode *)malloc(sizeof(stacknode));
		if(p==NULL){
			printf("�ڴ����ʧ��");
			return top1;
		}
		p->data.n=top2->data.n;
		strcpy(p->data.num,top2->data.num);
		p->data.time=top2->data.time;
		p->next=top1;
		top1=p;
		top2=top2->next;
	}
		if(EmptyLQue(Q)){//����ͣ�����жϱ���Ƿ��г����Ⱥ� 
			p=out(Q);
			p->data.n--;
			top1=LQinto(p,top1);
		}
		else 
			b--;
		printf("����Ϊ%s������ʻ��ʱ��Ϊ:%d��%d��%d��\n",q->data.num,day,hour,min);
		printf("����ʻ��ͣ������Ҫ���ɵķ���Ϊ:%dԪ\n",expenses(q,day,hour,min));		
		return top1;
}
//���к�����ʼ��
	LQueue *InitLQue(){
		LQueue *Q;
		stacknode *p;
		Q=(LQueue *)malloc(sizeof(LQueue));
		p=(stacknode *)malloc(sizeof(stacknode));
		p->next=NULL;
		Q->front=Q->rear=p;
		return Q;
	}
	//�����������
	LQueue *wait(LQueue *q,stacknode *s){		
		s->next=NULL;
		q->rear->next=s;
		q->rear=s;
		return q;		
	}
	//�жϺ򳵱�����޳����ȴ�
	int EmptyLQue(LQueue *q){
		if(q->front==q->rear)
			return 0;
		else
			return 1; 
	}
	//������������
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
	//�򳵶��н���ͣ����
	stacknode *LQinto(stacknode *p,stacknode *top1){	
        p->next=top1;
		top1=p;
		return top1;
	}
	//��ʾͣ���������г�����Ϣ
	void show(stacknode *top1){
		printf("   ͣ������ȫ��������Ϣ��\n");
		if(top1==NULL)
			printf("  ͣ�������޳�!\n");
		else{
				printf("���ƺ�      ����ʱ��       λ��\n");
			while(top1!=NULL){
				printf(" %s        %d��%d��%d��   ��%dλ\n",top1->data.num,top1->data.time.day,top1->data.time.hour,top1->data.time.min,top1->data.n);
				top1=top1->next;
			}
		}		
	}
	//��ʾ������������Ϣ
	void T_shou(LQueue *Q){
		LQueue *q;
		q=(LQueue *)malloc(sizeof(LQueue));
		q->rear=Q->rear->next;
		printf("     ������Ϣ\n");
		if(q->front==q->rear)
			printf("����û�г���!\n");
		else{
			printf("���ƺ�      ����ʱ��\n");
			while(q!=NULL){
				printf("%s		%d��%d��%d��",q->data.num,q->data.time.day,q->data.time.hour,q->data.time.min);
				q->rear=q->rear->next;
			}
		}
	}

