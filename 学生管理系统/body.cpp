#include "stdafx.h"
#include "statements.h"
extern List Class;
char present[Name];
StuAccount account_stu[STUNUM], waitting[STUNUM];
TerAccount account_ter[TERNUM];
AdminAccount account_admin[ADMINNUM];


void process_sign() {//登录界面菜单选择
	int exam = 0, cnt = 0, judgement = -1; //exam  用来检查执行了哪个标签
	switch ( char judge = choice()) {
	case '0':condition=-2,system("CLS");exit(0);break;
	case '3':signin_judge(0);break;
	case '1':
			judgement = signin_judge(1);
			if (judgement == 1) {
				show_stu();
				process_stu();
				break;
			}
			else if (judgement == 2) {
				show_teacher();
				process_ter();
				break;
			}
			else if (judgement == 3) {
				show_admin();
				///
				break;
			}exam = 1; 
	case '2':if (exam == 0) {
		while (cnt < 2 && judgement != 3) {
			cnt++;printf("请输入管理员密码：\n");rewind(stdin);
			judgement = password_cmp(password_get(), 0);
			if (judgement != 3) {
				printf("\n密码错误！\n");rewind(stdin);
			}
		}
		if (cnt == 2) { printf("即将退出的说\n");Sleep(1000);exit(0); }
		show_admin();
		/////
		}exam = 2;
	case '4':
	default:
		if ( exam == 0) {
			print_error();
		}if (judgement <0) {
			Sleep(2000);
		}
		show_sign();process_sign();
		break;
	}
}



int signin_judge(int n) {//账号密码的处理  n0:注册     1:登录    re  -2:账号不存在   -1：密码错误
	int flag = 0,re=0,cnt=0;
	char *account = (char *)malloc(Name * sizeof(char));
	char *password = (char *)malloc(PASS * sizeof(char));
	account = accountname_get();
	if (n == 0) {//注册
		int i,flag=0;
		for (i = 0;i < STUNUM;i++) {
			if (strcmp(account, account_stu[i].name) == 0 || strcmp(account, account_stu[i].stunum) == 0) {
				printf("用户名已存在！╮（╯＿╰）╭\n");rewind(stdin);
				flag = 1;
				break;
			}
		}if (flag == 0) {
			char *phonenum = (char *)malloc(sizeof(char) * 19);
			printf("请输入你的口令(6~12位)：\n");rewind(stdin);
			password = password_get();
			printf("\n请你的输入手机号(18位以内)：\n");rewind(stdin);
			scanf("%18s", phonenum);
			FILE *fp = fopen(".\\account_sign_up.txt", "w+");
			fprintf(fp, "%s\t%s\t%s\n", account, password,phonenum);
			fclose(fp);
			printf("请等待管理员通知。\n");rewind(stdin);
		}
	}
	else if (n == 1) {//登录
		int i=-1;//i   结构体中的下标
		i=account_cmp(account);
		if (i == -1) {
			printf("账号不存在！╮（╯＿╰）╭\n");rewind(stdin);
			return -2;
		}
		else {
			while(cnt < 2&&(re<=0)) {
				if(cnt==0)printf("请输入口令(6~12位)：\n");rewind(stdin);
				password = password_get();
				re = password_cmp(password, i);
			if (re == -1 && i != -1) {//密码错误
				printf("\n口令错误╮（╯＿╰）╭");rewind(stdin);
				if (cnt < 2) {
					cnt++;if (cnt < 2) { printf("请重新输入:\n");rewind(stdin); }
					if(cnt==2) { printf("请进行账号申诉!\n");rewind(stdin); }
					}
				}
			}
		}
		if(re!=-1&&i!=-1){//密码正确  re表示账号类型
			printf("\n登陆成功");
			Sleep(1000);
			condition = re;
		}
	}
	return re;
}

char *accountname_get(){//读取用户名输入并进行判断
	char *str=(char *)malloc(100*sizeof(char));
	printf("请输入用户名或学号：\n");
	rewind(stdin);
	scanf("%s", str);
	rewind(stdin);
	int len = strlen(str);
	if (len -1> Name||len<4) {
		print_examinput();
		str = accountname_get();
	}
	return str;
}
char *password_get() {//读取密码输入并进行判断
	int i;
	char *str = (char *)malloc(PASS * sizeof(char)), c, flag = 1;
	for (i = -1; i<PASS;) {
		c = getch();
		if (c != '\r'&&c != 8) {
			if (flag) {
				flag = 0;
				i = 0;
			}
			str[i++] = c;
		}
		else if (c == 8) {
			if (i >= 0) {
				if (i>0) {
					i--;
				}
				printf("\b\b  \b\b");
				continue;
			}
			else {
				continue;
			}
		}
		else{
			break;
		}
		printf("●");
	}
	if (i == -1) {
		str[0] = '\0';
	}
	str[i] = '\0';
	rewind(stdin);
	if (strlen(str) < 6 || strlen(str) > PASS - 1) {
		print_examinput();
		str = password_get();
	}
	return str;
}

void process_stu() {//学生功能选择
	char judge = choice(),exam=0;
	switch (judge) {
	case '0':show_welcome();break;
	case '1':show_stugrade();process_stugrade();show_stu();exam = 1;
	case '2':if (exam == 0) { print_timetable();import_timetable();go_on(); }exam = 2;
	case '3':if (exam == 0) {
		if (modify_password(account_cmp(present))) { save_account(); }
	}exam = 3;
	default:
		if (exam == 0) {
			print_error();
		}process_stu();
		break;
	}
}

void process_ter() {
	char judge = choice();
		switch (judge) {
		case '1':show_tergrade();process_tergrade();
	}
}