#include"stdafx.h"
#include"statements.h"
int STUNUM, TERNUM, ADMINNUM=3;
extern List Class;
void import_account() {//读入文件中的账号密码
	int i;
	FILE *fp1=fopen(".\\account_stu.txt","r");
	i = 0;
	while (fscanf(fp1, "%s\t%s\t%s", account_stu[i].name, account_stu[i].stunum, account_stu[i].password) != EOF) { password_change(account_stu[i].password, 2); i++; }
	STUNUM = i;
	fclose(fp1);
	FILE *fp2 = fopen(".\\account_ter.txt", "r");
	i = 0;
	while (fscanf(fp2, "%s\t%d\t%s", account_ter[i].name, &account_ter[i].classs, account_ter[i].password) != EOF) { password_change(account_ter[i].password, 2); i++; }
	TERNUM = i;
	fclose(fp2);
	FILE *fp3 = fopen(".\\account_admin.txt", "r");
	i = 0;
	while (fscanf(fp3, "%s\t%s", account_admin[i].name, account_admin[i].password) != EOF) { password_change(account_admin[i].password, 2);i++; }
	fclose(fp3);
}

void import_stu(List *list) {//读取学生信息到链表   evaluate每次重新计算
	FILE *fp = fopen(".\\student.txt", "r");
	//while (fscanf(fp, "%s	%s	%d	%d %d %d %d %d %d", tem.name,tem.stunum,tem.grade[0]) {
	data tem;
	//strcpy(tem.name, "\0"), strcpy(tem.stunum,"\0"),tem.classes=tem.evaluate;
	while(fscanf(fp, "%s	%s	%d",&tem.name,&tem.stunum,&tem.classes)!=EOF){
		int sum=0;
		node *p =(node *)malloc(sizeof(node));
		p->next = NULL;
		for (int i = 0;i < Subject;i++) {
			fscanf(fp,"%d", &tem.grade[i]);
			sum += tem.grade[i];
		}
		tem.evaluate = sum * 1.0 / Subject;
		p->element = tem;
		list->tail->next = p;
		list->tail = p;
	}
}

void import_timetable() {//读取并输出课表
	char *tablestr = (char *)malloc(sizeof(char) * 80);
	int day = time_tm->tm_wday;
	if (1 <= day&&day <= 5) {
		FILE *fp = fopen(".\\timetable.txt", "r");
		while (day--) {
			fscanf(fp,"%[^\n]%*c",tablestr);
		}
		fclose(fp);
		puts(tablestr);
		printf("认真上课哦，不然打爆你狗头(╯‵0′)╯︵ ┴─┴ \n");rewind(stdin);
	}
	else {
		printf("今天没课呢！(＞▽＜)\n");rewind(stdin);
	}
}

void fileadd(node* p,data tem) {//文件中读取存储到节点数据域
	strcpy(p->element.name, tem.name), strcpy(p->element.stunum, tem.stunum), p->element.classes=tem.classes;
	for (int i = 0;i < Subject;i++) {
		p->element.grade[i] = tem.grade[i];
	}
}

void save_account() {
	int i;
	FILE *fp1 = fopen(".\\account_stu.txt", "w+");
	for (i = 0;i < STUNUM;i++) {
		if (strlen(account_stu[i].name)) {
			password_change(account_stu[i].password, 1);
			fprintf(fp1, "%s\t%s\t%s\n", account_stu[i].name, account_stu[i].stunum, account_stu[i].password);
		}
	}
	fclose(fp1);
	FILE *fp2 = fopen(".\\account_ter.txt", "w+");
	for (i = 0; i < TERNUM; i++) {
		if (strlen(account_ter[i].name)) {
			password_change(account_ter[i].password, 1);
			fprintf(fp2, "%s\t%d\t%s\n", account_ter[i].name, account_ter[i].classs, account_ter[i].password);
		}
	}
	fclose(fp2);
	FILE *fp3 = fopen(".\\account_admin.txt", "w+");
	
	for (i = 0; i < ADMINNUM; i++) {
		if (strlen(account_admin[i].name)) {
			password_change(account_admin[i].password, 1);
			fprintf(fp3, "%s\t%s\n", account_admin[i].name, account_admin[i].password);
		}
	}
	fclose(fp3);
	print_changeok();
}

void save_stu(int i) {//保存学生信息   i  0:保存学生信息  1：下载到指定文件目录
	char file[50];
	if (i) {//下载
		printf("建议使用TXT文件\n");
		printf("请以.\\\\xxx.xx的格式输入文件名：\n");rewind(stdin);
		int exam = 0;
		do {
			scanf("%s", file);
			if (file[0] != '.'&&file[1] != '\\'&&file[2] != '\\') {
				print_error();
				exam = 1;
			}
		} while (exam != 0 && (exam = 0, 1));
	}
	else if (i == 0) {//保存学生信息
		strcpy(file, "student.txt");
	}if (i) { printf("正在下载......\n");rewind(stdin); }
	FILE * fp = fopen(file, "w");
	for (node *p = Class.head->next;p;p = p->next) {
		fprintf(fp,"%s	%s	%d	%d	%d	%d	%d	%d	%d\n", p->element.name, p->element.stunum, p->element.classes, p->element.grade[0], p->element.grade[1], p->element.grade[2], p->element.grade[3], p->element.grade[4], p->element.grade[5]);
	}
	fclose(fp);
}

int appeal_get() {
	int exam = 0;
	char apper[Name], sub[8], tername[Name];
	FILE *fp = fopen("grade-appeal.txt", "r");
	while (fscanf(fp, "%s	%s	%s", apper, sub, tername)!=EOF) {
		if (strcmp(tername, present) == 0) {
			printf("%s认为自己的%s成绩有误。\n", apper, sub);rewind(stdin);exam = 1;
		}
	}
	if (0 == exam) {
		printf("没有任何申诉哦\n");rewind(stdin);
	}
	fclose(fp);
	return exam;
}

int signup_get() {//读取并呈现账号申请
	char str[4][100],c='0';
	int re = 0;
	FILE *fp = fopen(".\\account_sign_up.txt", "r");
	if (c=fgetc(fp),c=fgetc(fp) && c != EOF) {
		fclose(fp);
		FILE *fp = fopen(".\\account_sign_up.txt", "r");
		while (fscanf(fp, "%s\t%s\t%s\t%s", str[0], str[1], str[2], str[3]) != EOF) {
			printf("信息:  %s   %s  口令或信息类型：%s  信息来源：%s\n", str[0], str[1], str[2], str[3]);
		}
		re = 1;
	}
	else {
		printf("暂无申请\n");rewind(stdin);
	}
	fclose(fp);
	return re;
}

void account_appeal() {//账号申诉
	printf("请输入用户名、学号、老师姓名和你的联系方式\n");
	printf("空格或回车隔开：\n");rewind(stdin);
	char str[4][50];
	scanf("%s%s%s%s", str[0], str[1], str[2], str[3]);
	FILE *fp = fopen(".\\account_sign_up.txt", "a+");
	fprintf(fp, "%s	%s	%s学生申诉	%s\n", str[0], str[1], str[2], str[3]);
	fclose(fp);
	printf("请等待管理员通知\n");rewind(stdin);
}

void del_infomation(int i) {//清空申诉或账号申请  i  1: 账号申请   2:成绩申诉   3:账号登录记录
	char obj[30];
	if (i == 1) {
		strcpy(obj, ".\\account_sign_up.txt");
	}
	else if (i == 2) {
		strcpy(obj, ".\\grade-appeal.txt");
	}
	else if (i == 3) {
		strcpy(obj, ".\\sign_log.txt");
	}
	else {
		print_re();
	}
	FILE *fp = fopen(obj,"w");
	fclose(fp);
}

void account_add() {//增加账号
	char name[Name], stunumber[25], password[PASS],exam=0;
	printf("请输入姓名：\n");rewind(stdin);
		do {
			scanf("%s", name);
			for (int i = 0;(unsigned)i < strlen(name);i++) {//检查非法输入
				if (0 <= name[i] && name[i] <= 255) {
					exam = 1;print_examinput();break;
				}
			}
		} while (exam != 0 && (exam = 0, 1));
		printf("请输入九位学号：\n");rewind(stdin);
		do {//学号检查
			scanf("%s", stunumber);
				if (strlen(stunumber)!=8) {
					exam = 1;
				}if (exam) {
					print_examinput();
				}
				for (int i = 0;i < STUNUM;i++) {
					if (strcmp(account_stu[i].stunum, stunumber) == 0) {//查重
						printf("该学号已存在！请重新输入：\n");exam = 1;
					}
				}
				
		} while (exam != 0 && (exam = 0, 1));
		printf("已自动设置初始密码\n");rewind(stdin);
		FILE *fp = fopen(".\\account_stu.txt", "a+");
		fprintf(fp,"%s	%s	%s\n", name, stunumber,"123456");
		fclose(fp);
		import_account();//重新加载文件
}

void account_print() {//查看账号
	printf("1.教师账号   2.学生账号\n"); rewind(stdin);
	int judge = choice()-'0';
	while (judge != 1 && judge != 2) {
		print_examinput();
		judge = choice()-'0';
	}
	char *account = accountname_get();
	int i = account_cmp(account);
	if (i != -1) {
		if (judge == 2 ) {
			if((strcmp(account, account_stu[i].name)==0 || strcmp(account, account_stu[i].stunum)==0))
			printf("用户名:%s	 学号:%s	密码%s\n", account_stu[i].name, account_stu[i].stunum, account_stu[i].password);
			else {
				printf("这个人不是学生哟\n"); rewind(stdin);
			}
		}else if (judge == 1) {
			if(strcmp(account, account_ter[i].name)==0)
			printf("用户名:%s	 班级:%d	密码%s\n", account_ter[i].name, account_ter[i].classs, account_ter[i].password); 
			else {
				printf("这个人不是老师哟\n"); rewind(stdin);
			}
		}
	}
	else { printf("账号不存在！"); }
}

void account_kill() {//删除账号
	char *account = accountname_get();
	int i = account_cmp(account);
	if (i == -1) {
		printf("账号不存在!\n");
	}
	else {
		if (warning()) {
			account_stu[i].name[0] = '\0';
			save_account();
			import_account();
		}
	}
	
}

void account_change() {//修改账号
	printf("1.教师账号   2.学生账号\n"); rewind(stdin);
	int judgement = choice() - '0';
	while (judgement != 1 && judgement != 2) {
		print_examinput();
		judgement = choice()-'0';
	}
	char *account = accountname_get();
	int i = account_cmp(account),j=0;
	show_account();
	if (judgement == 2) {
		if (strcmp(account, account_stu[i].name) != 0 && strcmp(account, account_stu[i].stunum) != 0) {
			printf("这不是学生账号哟\n"); rewind(stdin);
			return;
		}
		if (i != -1) {
			printf("1.用户名 2.学生学号 3.登录口令\n"); rewind(stdin);
			char judgement = choice();
			while (judgement != '1'&&judgement != '2'&&judgement != '3') {
				print_examinput();
				judgement = choice();
			}
			int exam = 0; char name[50]; printf("请输入:\n"); rewind(stdin);
			switch (judgement) {
			case'1':do {
				scanf("%s", name);
				for (j = 0; (unsigned)j < strlen(name); j++) {//检查非法输入
					if (0 <= name[j] && name[j] <= 255) {
						exam = 1; print_examinput(); break;
					}
				}
			} while (exam != 0 && (exam = 0, 1));
			strcpy(account_stu[i].name, name); break;
			case'2':
				scanf("%s", name);
				while (strlen(name) != 8) {
					print_examinput();
					scanf("%s", name);
				}
				strcpy(account_stu[i].stunum, name);
				break;
			case'3':
				scanf("%s", name);
				while (strlen(name) < 6 || strlen(name) > 12) {
					print_examinput();
					scanf("%s", name);
				}strcpy(account_stu[i].password, name); break;
			default:
				print_re();
				break;
			}
		}
		else { printf("账号不存在！"); }
	}
	else if (judgement == 1) {
		if (strcmp(account, account_ter[i].name) != 0 ) {
			printf("这不是教师账号哟\n"); rewind(stdin);
			return;
		}
		if (i != -1) {
			printf("1.用户名 2.教师班级 3.登录口令\n"); rewind(stdin);
			char judgement = choice();
			while (judgement != '1'&&judgement != '2'&&judgement != '3') {
				print_examinput();
				judgement = choice();
			}
			int exam = 0; char name[50]; printf("请输入:\n"); rewind(stdin);
			switch (judgement) {
			case'1':do {
				scanf("%s", name);
				for (j = 0; (unsigned)j < strlen(name); j++) {//检查非法输入
					if (0 <= name[j] && name[j] <= 255) {
						exam = 1; print_examinput(); break;
					}
				}
			} while (exam != 0 && (exam = 0, 1));
			strcpy(account_ter[i].name, name); break;
			case'2':
				int t;
				scanf("%d", &t);
				while (t <= 0) {
					print_examinput();
					scanf("%d", &t);
				}
				account_ter[i].classs = t;
				break;
			case'3':
				scanf("%s", name);
				while (strlen(name) < 6 || strlen(name) > 12) {
					print_examinput();
					scanf("%s", name);
				}strcpy(account_ter[i].password, name); break;
			default:
				print_re();
				break;
			}
		}
		else {
			printf("账号不存在！");
		}
	}
	else {
		print_re();
	}
	if (judge()) {
		save_account();
		import_account();
	}
	else {
		import_account();
	}
}

int log_get() {//登录记录的读取及呈现
	char str[4][50], re = 0, c;
	FILE *fp = fopen(".\\sign_log.txt", "r");
	if (c = fgetc(fp), c = fgetc(fp) && c != EOF) {
		fclose(fp);
		printf("以下是近日登录记录:\n"); 
		printf("时间			用户名		登录状况：\n"); rewind(stdin);
		FILE *fp = fopen(".\\sign_log.txt", "r");
		while (fscanf(fp, "%s\t%s\t%s\t%s", str[0], str[1], str[2],str[3]) != EOF) {
			printf("%s  %s          %-6s             %-6s\n", str[0], str[1], str[2], str[3]);
		}
		re = 1;
	}
	else {
		printf("暂无记录\n"); rewind(stdin);
	}
	fclose(fp);
	return re;
}