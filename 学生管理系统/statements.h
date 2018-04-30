#pragma once
#include"stdafx.h"
#include<stdio.h>
const int Name = 15, StuNum = 9, Subject = 6, PASS = 13;
const int STUNUM = 30, TERNUM = 15, ADMINNUM = 3;
extern int condition; //0δ��¼��1ѧ���ˣ�2��ʦ�ˣ�3����Ա�ˣ�-1�����˳���
extern char present[Name];
extern struct tm *time_tm;

typedef struct student {
	char name[Name];//����
	char stunum[StuNum];//ѧ��
	int classes;//�༶
	int grade[Subject];//�ɼ�
	double evaluate;//�۲�
} data;//��������   ¼������ʱ���˽ṹ����Ϊ����

typedef struct Linklist {
	data element;
	struct Linklist *next;
} node;

typedef struct ctrl {
	node *head;
	node *tail;
} List;

typedef struct Acc1 {//ѧ���˺�
	char name[Name];
	char stunum[StuNum];
	char password[PASS];
} StuAccount;

typedef struct Acc2 {//��ʦ�˺�
	char name[Name];
	int classs;
	char password[PASS];
} TerAccount;

typedef struct Acc3 {//����Ա�˺�
	char name[Name];
	char password[PASS];
} AdminAccount;

extern StuAccount account_stu[STUNUM], waitting[STUNUM];
extern TerAccount account_ter[TERNUM];
extern AdminAccount account_admin[ADMINNUM];


//��������
void add(List *list, data temp);
void kill(List *list, char *obj);
node * change(List *list, char *obj);
void print_all(List *list);
void search(List *list, char *obj);
void initialize_linklist(List *Class);//��ʼ������
void grade_cnt(List *list, int classnum,char *object);//ѧ����   ���㲢�����������
//Linklistfunction.cpp

void show_sign();//��¼����
void show_stu();//ѧ�����Ӳ˵�
void show_stugrade();//ѧ���˳ɼ���ѯ����
void show_teacher();//��ʦ���Ӳ˵�
void show_tergrade();//��ʦ�˳ɼ���ѯ����
void show_admin();//����Ա�Ӳ˵�
void show_welcome();//Ƥ����
//welcome page.cpp

char choice();
int judge();
int warning();
void print_error();
void print_no();
void print_examinput();
void go_on();
void print_timetable();//��ӡ��ǰʱ��
void print_blankhead();//��ӡ�ɼ�����ͷ
void print_re();//���������Ϣ
void print_changeok();//��ʾ�����ɹ�

//friendly.cpp


int signin_judge(int n);//�˺�������ж�
char *accountname_get();//�õ��û��������������ж�
char *password_get();//��ȡ�������벢���������ж�
void process_sign();//��¼����
void process_stu();//ѧ��ִ�й���
void process_ter();//��ʦִ�й���
//body.cpp

void fileadd(node* p, data tem);//�ļ��������ݴ洢������
void import_stu(List *list);//��ȡ�ļ����ݵ�����
void import_account();//�����ļ��е��˺�����
void import_timetable();//��ȡ������α�
void save_account();//�˺ű���
//filefunction.cpp

int password_cmp(char *password, int i);//����ıȶ�   ���������±�  �����ڷ���-1
int account_cmp(char *account);//�˺ŵıȶ�   �����˺�����   ������󷵻�-1
int find_classnum(List* list, char *present);//���ص�ǰѧ�����ڰ༶
void initialize_time();//��ȡ��ǰʱ��
char *greeting_get(int choice);//�ʺ����ȡ   1:ѧ����    2:��ʦ��      3:����Ա��
void grade_appeal();//�ɼ�����
int find_terclass(char *account);//����������ʦ�༶
int modify_password(int i);//�����޸�    0:δ�޸�   1���޸ĳɹ�
void process_stugrade();//ѧ���ɼ��������
void process_tergrade();//��ʦ�ɼ��������
void singlegrade_search();//��ʦ�����ֻ�ѧ�Ų�ѯ���˳ɼ�
void singlegrade_analyze();//��ʦ�����ֻ�ѧ�ŷ������˳ɼ�

//othersonfunctions.cpp