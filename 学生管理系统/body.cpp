#include "stdafx.h"
#include "statements.h"
extern List Class;
char present[Name];
StuAccount account_stu[NEW];
TerAccount account_ter[Name];
AdminAccount account_admin[3];


void process_sign() {//登录界面菜单选择
	int exam = 0, cnt = 0, judgement = -1; //exam  用来检查执行了哪个标签
	switch ( char judge = choice()) {
	case '0':printf("再见！\n");rewind(stdin);exit(0);break;
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
				process_admin();
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
		process_admin();
	}exam = 2;break;
	case '4':account_appeal();break;
	default:
		if ( exam == 0) {
			print_error();
		}if (judgement <0) {
			go_on();
		}
		show_sign();process_sign();
		break;
	}
}

int signin_judge(int n) {//账号密码的处理  n0:注册     1:登录    re  -2:账号不存在   -1：密码错误
	int flag = 0,re=0,cnt=0;
	char *account=NULL;// = (char *)malloc(Name * sizeof(char));
	char *password=NULL;// = (char *)malloc(PASS * sizeof(char));
	if (n == 0) {//注册
		if (validate()) {
			account = accountname_get();
			int i, flag = 0;
			char *stunumber = NULL;
			printf("接下来输入另一项\n"); rewind(stdin);
			stunumber = accountname_get();
			for (i = 0; i < STUNUM; i++) {
				if (strcmp(account, account_stu[i].name) == 0 || strcmp(account, account_stu[i].stunum) == 0 || strcmp(stunumber, account_stu[i].name) == 0 || strcmp(stunumber, account_stu[i].stunum) == 0) {
					printf("该用户名或学号已存在！╮（╯＿╰）╭\n"); rewind(stdin);
					flag = 1;
					break;
				}
			}if (flag == 0) {
				char *password2 = (char *)malloc(PASS * sizeof(char));
				char *phonenum = (char *)malloc(sizeof(char) * 19);
				printf("请输入你的登录口令(6~12位)：\n"); rewind(stdin);
				password = password_get();
				printf("\n请再次输入：\n"); rewind(stdin);
				password2 = password_get();
				if (strcmp(password, password2) != 0) {
					printf("\n两次输入不一致，请重新来过\n"); rewind(stdin);
				}
				else {
					printf("\n请你的输入手机号(18位以内)：\n"); rewind(stdin);
					scanf("%18s", phonenum);
					FILE *fp = fopen(".\\account_sign_up.txt", "a+");
					fprintf(fp, "%s\t%s\t%s\t%s\n", account, stunumber, password, phonenum);
					fclose(fp);
					printf("请等待管理员通知。\n"); rewind(stdin);
				}
			}
		}
		else {
			exit(0);
		}
	}
	else if (n == 1) {//登录
		account = accountname_get();
		int i=-1;//i   结构体中的下标
		i=account_cmp(account);
		if (i == -1) {
			printf("账号不存在！╮（╯＿╰）╭\n");rewind(stdin);present[0] = '\0';
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
					if (cnt == 2) { printf("请进行账号申诉!\n");rewind(stdin);log(0);present[0] = '\0';  }
					}
				}
			}
		}
		if(re!=-1&&i!=-1){//密码正确  re表示账号类型
			printf("\n登陆成功");log(1);
			Sleep(1000);
		}
	}
	free(account);
	if(password)free(password);
	return re;
}

char *accountname_get(){//读取用户名输入并进行判断
	char *str=(char *)malloc(100*sizeof(char));
	printf("请输入用户名或学号：\n");
	rewind(stdin);
	scanf("%s", str);
	rewind(stdin);
	int len = strlen(str);
	if (len -1> Name||(len<2)) {
		print_examinput();
		str = accountname_get();
	}
	return str;
}

char *password_get() {//读取密码输入并进行判断
	int i,cnt=0;
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
			if (i > 0) {
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
		if (cnt <= 3) {
			printf("\n"); print_examinput();
			str = password_get();
			cnt++;
		}
	}
	return str;
}

void process_stu() {//学生功能选择
	char judge = choice(),exam=0;
	switch (judge) {
	case '0':show_welcome();break;
	case '1':show_stugrade();process_stugrade();exam = 1;
	case '2':if (exam == 0) { print_timetable();import_timetable();}exam = 2;
	case '3':if (exam == 0) {
		if (modify_password(account_cmp(present))) { save_account(); }
	}exam = 3;
	default:
		if (exam == 0) {
			print_error();
		}if (exam != 0)go_on();show_stu();process_stu();
		break;
	}
}

void process_ter() {//教师端功能选择
	char judge = choice(),exam=0;char *tem;
		switch (judge) {
		case '0':exit(0);break;
		case '1':show_tergrade();process_tergrade();exam = 1;
		case '2':if (0 == exam) { add(&Class);sort_stu(&Class, 7);save_stu(0);printf("已通知管理员删除账号");exam = 2; }
		case'3':if (0 == exam) {
			
			if (change(&Class, tem = accountname_get())) { if (warning()) { if (kill(&Class, tem)) { save_stu(0); print_changeok(); } } }exam = 3;
		}
		case'4':if (0 == exam) { if (change(&Class, tem = accountname_get())) { modify_grade(change(&Class, tem));save_stu(0);}exam = 4; }
		case '5':if (0 == exam) { if (appeal_get()) { if (print_enquiry())if (warning()) { del_infomation(2); } }exam = 5; }
		case '6':if (0 == exam) {
			if (modify_password(account_cmp(present))) { save_account(); }
			exam = 6; }
		default:
			if (exam == 0) { print_error(); }
			if (exam != 0)go_on();show_teacher();process_ter();
			break;
	}
}

void process_admin() {
	char judgement = choice(),exam=0;
	switch (judgement) {
	case'0':show_welcome();exit(0);break;
	case'1':if (signup_get()) { if (print_enquiry())if (warning()) { del_infomation(1); } }exam = 1;
	case'2':if (0 == exam) { show_account();process_account();exam = 2; }
	case'3':if (0 == exam) { if (log_get()) { if (print_enquiry())if (warning()) { del_infomation(3); } }exam = 3; }
	case'4':if (0 == exam) { if (modify_password(account_cmp(present))) { print_changeok(); }exam = 4; }
	case'9':if (0 == exam) { show_teacher();process_ter(); }exam = 9;
	default:
		if (exam == 0) {print_error();}
		if(exam!=0)go_on();show_admin();process_admin();
	}
}