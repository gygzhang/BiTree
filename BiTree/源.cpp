#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#define OK 1
#define FALSE 0;
#define TRUE 1;
#define OVERFLOW -2
typedef struct BiTNode {
	int data;
	struct BiTNode * lchild, *rchild;
}BiTNode, *BiTree;
typedef struct QNode {
	BiTree tree;
	struct QNode * next;
}QNode, *QueuePtr;
typedef struct {
	QueuePtr front;
	QueuePtr rear;
}LinkQueue;
int InitBiTree(BiTree *T);
int CreatBiTree(BiTree *T);
int InitQueue(LinkQueue * Q);
int EnQueue(LinkQueue * Q, BiTree p);
int DeQueue(LinkQueue * Q, BiTree *p);
void LevelOrderTraverse(BiTree);
void Visit(int);
int main(int argc, char **argv) {
	BiTree T;
	InitBiTree(&T);
	CreatBiTree(&T);
	LevelOrderTraverse(T);
	system("pause");
	return 0;
}

int InitBiTree(BiTree *T) {
	T = NULL;
	//(*T)->lchild = (*T)->rchild = NULL;
	return OK;
}
int CreatBiTree(BiTree *T) {
	int num;
	scanf_s("%d", &num);
	if (!num) *T = NULL;
	else {
		*T = (BiTree)malloc(sizeof(BiTNode));
		if (!T)
			exit(OVERFLOW);
		else {
			(*T)->data = num;
			CreatBiTree(&(*T)->lchild);
			CreatBiTree(&(*T)->rchild);
		}
	}
	return OK;
}
void LevelOrderTraverse(BiTree T) {
	LinkQueue Q;
	BiTree t;
	char a = 'a';
	InitQueue(&Q);
	EnQueue(&Q, T);
	while (Q.front != Q.rear) {
		DeQueue(&Q, &t);
		Visit(t->data);
		if (t->lchild) {
			EnQueue(&Q, t->lchild);
		}
		if (t->rchild) {
			EnQueue(&Q, t->rchild);
		}

	}
}
void Visit(int elem) {
	printf("%d ", elem);
}
int InitQueue(LinkQueue * Q) {
	Q->front = Q->rear = (QueuePtr)malloc(sizeof(QNode));
	if (!Q->front)
		exit(OVERFLOW);
	Q->front->next = NULL;
	return OK;
}
int EnQueue(LinkQueue *Q, BiTree t) {
	QueuePtr p = (QueuePtr)malloc(sizeof(QNode));
	if (!p)
		exit(OVERFLOW);
	p->tree = t;
	p->next = NULL;
	Q->rear->next = p;
	Q->rear = p;
	return OK;
}
int DeQueue(LinkQueue *Q, BiTree *t) {
	QueuePtr  p;
	if (Q->front == Q->rear)
		return FALSE;
	p = Q->front->next;
	*t = p->tree;
	Q->front->next = p->next;
	if (Q->rear == p)
		Q->front = Q->rear;
	free(p);
	return OK;
}
