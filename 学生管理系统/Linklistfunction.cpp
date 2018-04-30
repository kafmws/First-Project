#include "stdafx.h"
#include"statements.h"
extern List Class;
void add(List *list, data temp) {//����
	if (node *p=(node *)malloc(sizeof(node))) {
		p->next = NULL;
		strncpy_s(p->element.name, temp.name, Name);
		strncpy_s(p->element.stunum, temp.stunum, StuNum);
		for (int i = 0;i < Subject;i++) {
			p->element.grade[i] = temp.grade[i];
		}//β��
		list->tail->next = p;
		list->tail = p;
	}
	else {
		printf("sorry,we can't have more.\n");
	}
}

//��������ѧ�Ų���name,stunum��Ϊ�ַ���
void kill(List *list, char *obj) {//ɾ
	node *p,*dead;
	for (p = list->head->next;p->next;p = p->next) {
		if (strcmp(p->next->element.stunum, obj) == 0 || strcmp(p->next->element.name, obj) == 0) {
			dead = p->next;
			p->next = dead->next;
			free(dead);
		}
	}
}

//��������ѧ�Ų���    ����Ŀ��ڵ��ָ��
node * change(List *list, char *obj) {//��
	node *p = list->head->next;
	for (p;p->next;p = p->next) {
		if (strcmp(p->element.stunum, obj) == 0 || strcmp(p->element.name, obj) == 0) {
			return p;
		}
	}
	print_error();
	return NULL;
}

//������ӡ��������
void print_all(List *list) {//����������гɼ�
	node *p = list->head->next;
	for (p;p;p = p->next) {
		printf("%s %s ", p->element.name, p->element.stunum);
		for (int i = 0;i < Subject;i++) {
			printf("%d ", p->element.grade[i]);
		}
		printf("\n");
	}
}

void print_class(List *list) {//�����������ɼ�
	node *p = list->head->next;
	for (p;p;p = p->next) {
		printf("%s %s ", p->element.name, p->element.stunum);
		for (int i = 0;i < Subject;i++) {
			printf("%d ", p->element.grade[i]);
		}
		printf("\n");
	}
}
//��
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
		else if (strstr(p->element.name, obj) != NULL || strstr(p->element.stunum, obj) != NULL) {//���벻������strstr�Ƚ�
			if (flaghead) {
				flaghead = 0;
				printf("����Ҫ�ҵ�Ҳ����:\n");emm = 1;
			}
			printf("%s %s\n", p->element.name, p->element.stunum);
			if (p->next=NULL) {//�������
				printf("��ȷ�Ϻ����²���\n");
				go_on();
			}
		}
	}if(emm==0) {
			print_no();
		}
}

void grade_cnt(List *list,int classnum,char *object) {//ѧ����   ���㲢�����������
	node *p = list->head->next;
	node *obj = change(list, object);
	strcpy(object, obj->element.name);
	int cnt[Subject] = { 1,1,1,1,1,1 },cnt_evaluate=1, i;
	for (p;p;p = p->next) {
		if (p->element.classes == classnum) {//classnumΪfind_classnum
			for (i = 0;i < Subject;i++) {
				if (p->element.grade[i] > obj->element.grade[i]) {
					cnt[i]++;
				}
			}
		}
		if (p->element.evaluate > obj->element.evaluate)
			cnt_evaluate++;
	}//�������
	printf("%sͬѧ,%d���и����ɼ����ڵ�%d����Ӣ��ɼ���%d��,����ɼ���%d��,��ɢ�ɼ���%d��,C���Գɼ���%d��,�����ɼ���%d��,�ۺϳɼ�ȫ�꼶%d����Ҫ��������Ŷ(? ?_?)?\n",object,classnum,cnt[0], cnt[1], cnt[2], cnt[3], cnt[4], cnt[5], cnt_evaluate);
}
void initialize_linklist(List *Class) {//��ʼ������
		node *p = (node *)malloc(sizeof(node));
		p->next = NULL;
		Class->head= Class->tail=p;
	}