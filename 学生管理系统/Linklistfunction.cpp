#include "stdafx.h"
#include"statements.h"
extern List Class;
void add(List *list, data temp) {//增加
	if (node *p=(node *)malloc(sizeof(node))) {
		p->next = NULL;
		strncpy_s(p->element.name, temp.name, Name);
		strncpy_s(p->element.stunum, temp.stunum, StuNum);
		for (int i = 0;i < Subject;i++) {
			p->element.grade[i] = temp.grade[i];
		}//尾插
		list->tail->next = p;
		list->tail = p;
	}
	else {
		printf("sorry,we can't have more.\n");
	}
}

//按或姓名学号查找name,stunum均为字符串
void kill(List *list, char *obj) {//删
	node *p,*dead;
	for (p = list->head->next;p->next;p = p->next) {
		if (strcmp(p->next->element.stunum, obj) == 0 || strcmp(p->next->element.name, obj) == 0) {
			dead = p->next;
			p->next = dead->next;
			free(dead);
		}
	}
}

//按或姓名学号查找    返回目标节点的指针
node * change(List *list, char *obj) {//改
	node *p = list->head->next;
	for (p;p->next;p = p->next) {
		if (strcmp(p->element.stunum, obj) == 0 || strcmp(p->element.name, obj) == 0) {
			return p;
		}
	}
	print_error();
	return NULL;
}

//遍历打印链表内容
void print_all(List *list) {//遍历输出所有成绩
	node *p = list->head->next;
	for (p;p;p = p->next) {
		printf("%s %s ", p->element.name, p->element.stunum);
		for (int i = 0;i < Subject;i++) {
			printf("%d ", p->element.grade[i]);
		}
		printf("\n");
	}
}

void print_class(List *list) {//遍历输出本班成绩
	node *p = list->head->next;
	for (p;p;p = p->next) {
		printf("%s %s ", p->element.name, p->element.stunum);
		for (int i = 0;i < Subject;i++) {
			printf("%d ", p->element.grade[i]);
		}
		printf("\n");
	}
}
//查
void search(List *list, char *obj) {
	int flaghead = 1,emm=0;
	node *p = list->head->next;
	for (p;p->next;p = p->next) {
		if ( strcmp(p->element.name, obj) == 0|| strcmp(p->element.stunum, obj) == 0) {
			printf("%s	%s ", p->element.name, p->element.stunum);
			for (int i = 0;i < Subject;i++) {
				printf("%6d  ", p->element.grade[i]);
			}
			printf("%8.2f",p->element.evaluate);
			printf("\n");emm = 1;
			break;
		}
		else if (strstr(p->element.name, obj) != NULL || strstr(p->element.stunum, obj) != NULL) {//输入不完整用strstr比较
			if (flaghead) {
				flaghead = 0;
				printf("你想要找的也许是:\n");emm = 1;
			}
			printf("%s %s\n", p->element.name, p->element.stunum);
			if (p->next=NULL) {//查找完毕
				printf("请确认后重新查找\n");
				go_on();
			}
		}
	}if(emm==0) {
			print_no();
		}
}

void grade_cnt(List *list,int classnum,char *object) {//学生端   计算并输出本班排名
	node *p = list->head->next;
	node *obj = change(list, object);
	strcpy(object, obj->element.name);
	int cnt[Subject] = { 1,1,1,1,1,1 },cnt_evaluate=1, i;
	for (p;p;p = p->next) {
		if (p->element.classes == classnum) {//classnum为find_classnum
			for (i = 0;i < Subject;i++) {
				if (p->element.grade[i] > obj->element.grade[i]) {
					cnt[i]++;
				}
			}
		}
		if (p->element.evaluate > obj->element.evaluate)
			cnt_evaluate++;
	}//计数完毕
	printf("%s同学,%d班中高数成绩排在第%d名，英语成绩第%d名,大物成绩第%d名,离散成绩第%d名,C语言成绩第%d名,体育成绩第%d名,综合成绩全年级%d名，要继续加油哦(? ?_?)?\n",object,classnum,cnt[0], cnt[1], cnt[2], cnt[3], cnt[4], cnt[5], cnt_evaluate);
}
void initialize_linklist(List *Class) {//初始化链表
		node *p = (node *)malloc(sizeof(node));
		p->next = NULL;
		Class->head= Class->tail=p;
	}