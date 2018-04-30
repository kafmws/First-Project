#pragma once
#include"stdafx.h"
#include<stdio.h>
const int Name = 15, StuNum = 9, Subject = 6, PASS = 13;
const int STUNUM = 30, TERNUM = 15, ADMINNUM = 3;
extern int condition; //0未登录，1学生端，2教师端，3管理员端，-1即将退出。
extern char present[Name];
extern struct tm *time_tm;

typedef struct student {
	char name[Name];//姓名
	char stunum[StuNum];//学号
	int classes;//班级
	int grade[Subject];//成绩
	double evaluate;//综测
} data;//用作参数   录入数据时将此结构体作为参数

typedef struct Linklist {
	data element;
	struct Linklist *next;
} node;

typedef struct ctrl {
	node *head;
	node *tail;
} List;

typedef struct Acc1 {//学生账号
	char name[Name];
	char stunum[StuNum];
	char password[PASS];
} StuAccount;

typedef struct Acc2 {//老师账号
	char name[Name];
	int classs;
	char password[PASS];
} TerAccount;

typedef struct Acc3 {//管理员账号
	char name[Name];
	char password[PASS];
} AdminAccount;

extern StuAccount account_stu[STUNUM], waitting[STUNUM];
extern TerAccount account_ter[TERNUM];
extern AdminAccount account_admin[ADMINNUM];


//函数声明
void add(List *list, data temp);
void kill(List *list, char *obj);
node * change(List *list, char *obj);
void print_all(List *list);
void search(List *list, char *obj);
void initialize_linklist(List *Class);//初始化链表
void grade_cnt(List *list, int classnum,char *object);//学生端   计算并输出本班排名
//Linklistfunction.cpp

void show_sign();//登录界面
void show_stu();//学生端子菜单
void show_stugrade();//学生端成绩查询界面
void show_teacher();//教师端子菜单
void show_tergrade();//教师端成绩查询界面
void show_admin();//管理员子菜单
void show_welcome();//皮卡丘
//welcome page.cpp

char choice();
int judge();
int warning();
void print_error();
void print_no();
void print_examinput();
void go_on();
void print_timetable();//打印当前时间
void print_blankhead();//打印成绩单表头
void print_re();//输出回馈信息
void print_changeok();//提示操作成功

//friendly.cpp


int signin_judge(int n);//账号密码的判断
char *accountname_get();//得到用户名并进行输入判断
char *password_get();//读取密码输入并进行输入判断
void process_sign();//登录过程
void process_stu();//学生执行过程
void process_ter();//教师执行过程
//body.cpp

void fileadd(node* p, data tem);//文件所读内容存储到链表
void import_stu(List *list);//读取文件内容到链表
void import_account();//读入文件中的账号密码
void import_timetable();//读取并输出课表
void save_account();//账号保存
//filefunction.cpp

int password_cmp(char *password, int i);//密码的比对   返回所在下标  不存在返回-1
int account_cmp(char *account);//账号的比对   返回账号类型   密码错误返回-1
int find_classnum(List* list, char *present);//返回当前学生所在班级
void initialize_time();//获取当前时间
char *greeting_get(int choice);//问候语获取   1:学生端    2:教师端      3:管理员端
void grade_appeal();//成绩申诉
int find_terclass(char *account);//按名查找老师班级
int modify_password(int i);//密码修改    0:未修改   1：修改成功
void process_stugrade();//学生成绩界面过程
void process_tergrade();//教师成绩界面过程
void singlegrade_search();//教师按名字或学号查询个人成绩
void singlegrade_analyze();//教师按名字或学号分析个人成绩

//othersonfunctions.cpp