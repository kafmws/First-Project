#pragma once
#include"stdafx.h"
#include<stdio.h>
const int Name = 15, StuNum = 9, Subject = 6, PASS = 13,NEW=150;
const char SUBJECT[Subject][10] = { "����", "Ӣ��", "����", "��ɢ", "C����", "����" };
extern int STUNUM , TERNUM , ADMINNUM;
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

extern StuAccount account_stu[NEW];
extern TerAccount account_ter[Name];
extern AdminAccount account_admin[3];


//��������
void add(List *list);
int kill(List *list, char *obj);
node * change(List *list, char *obj);
void print_all(List *list);
void search(List *list, char *obj);
void initialize_linklist(List *Class);//��ʼ������
void singlegrade_cnt(List *list, int classnum,char *object);//ѧ����   ���㲢�����������
void grade_analyze(List *list, int classnum,int i);//����ȫ��ɼ�,i��ʾ��Ŀ
void print_class(List *list);//�����������ɼ�
void modify_grade(node *p);//����Ŀ�޸ĳɼ������¼����۲�
//Linklistfunction.cpp

void show_sign();//��¼����
void show_stu();//ѧ�����Ӳ˵�
void show_stugrade();//ѧ���˳ɼ���ѯ����
void show_teacher();//��ʦ���Ӳ˵�
void show_tergrade();//��ʦ�˳ɼ���ѯ����
void show_admin();//����Ա�Ӳ˵�
void show_account();//����Ա�˻��������
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
void print_subject();//��ӡ��Ŀ���
int print_enquiry();//ѯ���Ƿ�ɾ�����ߣ�ע����Ϣ

//friendly.cpp


int signin_judge(int n);//�˺�������ж�
char *accountname_get();//�õ��û��������������ж�
char *password_get();//��ȡ�������벢���������ж�
void process_sign();//��¼����
void process_stu();//ѧ��ִ�й���
void process_ter();//��ʦִ�й���
void process_admin();//����Աִ�й���
//body.cpp

void fileadd(node* p, data tem);//�ļ��������ݴ洢������
void import_stu(List *list);//��ȡ�ļ����ݵ�����
void import_account();//�����ļ��е��˺�����
void import_timetable();//��ȡ������α�
void save_account();//�˺ű���
void sort_stu(List *list, int i);//��ѧ����������  1~6   subject�ɼ�   7�ۺ�����   8ѧ��˳��
int appeal_get();//��ȡ������������Ϣ   0������
void save_stu(int i);//����ѧ����Ϣ   i  0:����ѧ����Ϣ  1�����ص�ָ���ļ�Ŀ¼
void del_infomation(int i);//������߻��˺�����  i  1: �˺�����   2:�ɼ�����   3����¼��¼
int signup_get();//��ȡ�������˺�����    0 ������  
void account_appeal();//�˺�����
void account_print();//�鿴�˺�
void account_add();//�����˺�
void account_kill();//ɾ���˺�
void account_change();//�޸��˺���Ϣ
void log(int i);//i      1 ���ɹ���½     0��δ�ɹ���½

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
void singlegrade_print();//��ʦ�����ֻ�ѧ�Ų�ѯ���˳ɼ�
void singlegrade_analyze();//��ʦ�����ֻ�ѧ�ŷ������˳ɼ�
void stu_add(data *ptem);//ѧ����Ϣ�����
void process_account();
void password_change(char *obj, int i);//  i      1 :  ����     2:����
int log_get();//��¼��¼�Ķ�ȡ������
int validate();//re: 0����֤ʧ��  1����֤�ɹ� 
//othersonfunctions.cpp