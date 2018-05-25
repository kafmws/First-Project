#pragma once
#include"stdafx.h"
#include<stdio.h>
const int Name = 15, StuNum = 9, Subject = 6, PASS = 13,NEW=150;
const char SUBJECT[Subject][10] = { "高数", "英语", "大物", "离散", "C语言", "体育" };
extern int STUNUM , TERNUM , ADMINNUM;
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

extern StuAccount account_stu[NEW];
extern TerAccount account_ter[Name];
extern AdminAccount account_admin[3];


//函数声明
void add(List *list);
int kill(List *list, char *obj);
node * change(List *list, char *obj);
void print_all(List *list);
void search(List *list, char *obj);
void initialize_linklist(List *Class);//初始化链表
void singlegrade_cnt(List *list, int classnum,char *object);//学生端   计算并输出本班排名
void grade_analyze(List *list, int classnum,int i);//分析全班成绩,i表示科目
void print_class(List *list);//遍历输出本班成绩
void modify_grade(node *p);//按科目修改成绩并重新计算综测
//Linklistfunction.cpp

void show_sign();//登录界面
void show_stu();//学生端子菜单
void show_stugrade();//学生端成绩查询界面
void show_teacher();//教师端子菜单
void show_tergrade();//教师端成绩查询界面
void show_admin();//管理员子菜单
void show_account();//管理员账户管理界面
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
void print_subject();//打印科目编号
int print_enquiry();//询问是否删除申诉，注册信息

//friendly.cpp


int signin_judge(int n);//账号密码的判断
char *accountname_get();//得到用户名并进行输入判断
char *password_get();//读取密码输入并进行输入判断
void process_sign();//登录过程
void process_stu();//学生执行过程
void process_ter();//教师执行过程
void process_admin();//管理员执行过程
//body.cpp

void fileadd(node* p, data tem);//文件所读内容存储到链表
void import_stu(List *list);//读取文件内容到链表
void import_account();//读入文件中的账号密码
void import_timetable();//读取并输出课表
void save_account();//账号保存
void sort_stu(List *list, int i);//对学生进行排序  1~6   subject成绩   7综合评价   8学号顺序
int appeal_get();//读取并呈现申诉信息   0无申诉
void save_stu(int i);//保存学生信息   i  0:保存学生信息  1：下载到指定文件目录
void del_infomation(int i);//清空申诉或账号申请  i  1: 账号申请   2:成绩申诉   3：登录记录
int signup_get();//读取并呈现账号申请    0 无申请  
void account_appeal();//账号申诉
void account_print();//查看账号
void account_add();//增加账号
void account_kill();//删除账号
void account_change();//修改账号信息
void log(int i);//i      1 ：成功登陆     0：未成功登陆

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
void singlegrade_print();//教师按名字或学号查询个人成绩
void singlegrade_analyze();//教师按名字或学号分析个人成绩
void stu_add(data *ptem);//学生信息的添加
void process_account();
void password_change(char *obj, int i);//  i      1 :  加密     2:解密
int log_get();//登录记录的读取及呈现
int validate();//re: 0：验证失败  1：验证成功 
//othersonfunctions.cpp