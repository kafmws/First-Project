#include"stdafx.h"
#include"statements.h"
extern List Class;
extern struct tm *time_tm;

int password_cmp(char *password,int i) {//-1:密码错误   1：学生      2：老师    3：admin
	 int re=-1;//re stands for accountclass
	 if (strcmp(password, account_stu[i].password) == 0&& (present[0] == '\0' ? 1 : strcmp(present, account_stu[i].name) == 0)){
		 re = 1;strcpy_s(present, account_stu[i].name);
	 }
	 if (re == -1&&i < TERNUM)
		 if (strcmp(password, account_ter[i].password) == 0 && (present[0] == '\0' ? 1 : strcmp(present, account_ter[i].name) == 0)) {
			 re = 2;strcpy_s(present, account_ter[i].name);
		 }
	 if(re==-1&&i<ADMINNUM)
		 if (strcmp(password, account_admin[i].password) == 0 && (present[0]=='\0'?1:strcmp(present, account_admin[i].name) == 0)) {
			 re = 3;strcpy_s(present, account_admin[i].name);
		 }
	return re;
}

int account_cmp(char *account) {//-1:账号不存在   re账号在结构体数组中的下标
	int i,re=-1;
	for (i = 0;i < STUNUM;i++) {
		if (strcmp(account, account_stu[i].name) == 0||strcmp(account,account_stu[i].stunum)==0) {
			re = i;
			break;
		}
	}
	if (re == -1) {
		for (i = 0;i < TERNUM;i++) {
			if (strcmp(account, account_ter[i].name) == 0) {
				re = i;
				break;
			}
		}
	}
	if (re == -1) {
		for (i = 0;i < ADMINNUM;i++) {
			if (strcmp(account, account_admin[i].name) == 0) {
				re = i;
				break;
			}
		}
	}
	return re;
}

void initialize_time() {//获取当前时间
	time_t now;
	time(&now);
	time_tm=localtime(&now);
}

char *greeting_get(int choice) {
	char *re=(char *)malloc(sizeof(char)*160);
	re[0] = '\0';
	initialize_time();//获取当前时间
	switch (choice) {//1：学生   2：老师  3：管理员
	case 1:
		if (6 <= time_tm->tm_hour &&time_tm->tm_hour <= 7)
			strcpy(re, "早安qwq，一日之计在于晨");
		else if (8 <= time_tm->tm_hour &&time_tm->tm_hour <= 10)
			strcpy(re, "上午好O(∩_∩)O，今天也元气满满\\(^o^)/");
		else if (11 <= time_tm->tm_hour &&time_tm->tm_hour <= 13)
			strcpy(re, "中午好，好困啊orz");
		else if (14 <= time_tm->tm_hour &&time_tm->tm_hour <= 18)
			strcpy(re, "下午好(≧ω≦),  QAQ今天有逃课吗?");
		else if (19 <= time_tm->tm_hour &&time_tm->tm_hour <= 22)
			strcpy(re, "晚上好qwq，记得写作业！！");
		else {
			strcpy(re, "快去睡觉，不然打爆你狗头！");
		}break;
	case 2:
		if (6 <= time_tm->tm_hour &&time_tm->tm_hour <= 11)
			strcpy(re, "上午好");
		else if (12 <= time_tm->tm_hour &&time_tm->tm_hour <= 1)
			strcpy(re, "中午好");
		else if (2 <= time_tm->tm_hour &&time_tm->tm_hour <= 18)
			strcpy(re, "下午好");
		else if (19 <= time_tm->tm_hour &&time_tm->tm_hour <= 21)
			strcpy(re, "晚上好");
		else {
			strcpy(re, "夜深了，请早点休息");
		}break;
	case 3:
		if (6 <= time_tm->tm_hour &&time_tm->tm_hour <= 11)
			strcpy(re, "嘘，你知道吗，为了减轻你(他)的工作量，开发者\n取消了你管理成绩的功能哟");
		else if (12 <= time_tm->tm_hour &&time_tm->tm_hour <= 1)
			strcpy(re, "嘘，我什么都没说");
		else if (2 <= time_tm->tm_hour &&time_tm->tm_hour <= 18)
			strcpy(re, "其实只管理账号也挺好的2333");
		else if (19 <= time_tm->tm_hour &&time_tm->tm_hour <= 21)
			strcpy(re, "晚上好，偷偷告诉你，其实调用一下process_ter()你也就可以管理成绩了哦");
		else {
			strcpy(re, "夜深了，请早点休息");
		}break;
	default:
		printf("其实执行这条语句是不可能的\n");
		print_re();
		break;
	}
	return re;
}

void grade_appeal() {
	printf("请依次输入你想要申诉的科目名称与老师姓名\n");
	printf("空格或回车隔开：\n");rewind(stdin);
	char *subject = (char *)malloc(sizeof(char) * 7);
	char *teachername = (char *)malloc(sizeof(char) * 14);
	if (scanf("%s %s", subject,teachername) != 2) {//输入不正确
		rewind(stdin);
		print_examinput();
	}
	else {
		if (account_cmp(teachername) ==-1) {
			printf("没有这个老师(>︿<),请确认后重新来过。\n");rewind(stdin);
		}
		else if(find_classnum(&Class,present)==find_terclass(teachername)){
			if (find_classnum(&Class, present) == -1 || find_terclass(teachername) == -1) {
				printf("班级查找错误！\n");
				print_re();
			}
			FILE *fp = fopen(".\\grade-appeal.txt", "a+");
			fprintf(fp, "%d	%s	%s	%s\n",find_classnum(&Class,present),present, subject, teachername);
			fclose(fp);
			printf("申诉已被提交，请等待老师处理(/ω＼)\n");rewind(stdin);
		}
		else {
			printf("这不是你的老师！(￣_￣|||)\n");rewind(stdin);
		}
	}
}

void process_stugrade() {//学生成绩界面的选择
	char tem, exam = 0;
	switch (tem = choice()) {
	case '0':break;
	case '1':print_blankhead();search(&Class, present);exam = 1;
	case '2':if (exam == 0) { grade_cnt(&Class, find_classnum(&Class, present),present); exam = 2;}
	case '3':if (exam == 0) { grade_appeal();rewind(stdin); exam = 3; }
	default:
		if (exam == 0) { print_error(); }
		go_on();show_stugrade();process_stugrade();
		break;
	}
}

int find_classnum(List* list,char *present) {//按账号或学号返回当前学生所在班级
	int classnum=-1;
	node *p = list->head->next;
	for (p;p;p = p->next) {
		if (strcmp(present, p->element.name) == 0||strcmp(present,p->element.stunum)==0) {
			classnum = p->element.classes;
			break;
		}
	}
	return classnum;
}

int find_terclass(char *account) {//按名查找老师班级
	int i,re=-1;
	for (i = 0;i < TERNUM;i++) {
		if (strcmp(account, account_ter[i].name)==0)
		re = account_ter[i].classs;
	}
	return re;
}

int modify_password(int i) {// x账户类型   i  要修改的账户下标   
	printf("请输入原口令：\n");rewind(stdin);
	char *password = (char *)malloc(sizeof(char)*PASS);
	char *password2 = (char *)malloc(sizeof(char)*PASS);
	password = password_get();
	int x = password_cmp(password, i),re=0;
	if (x==-1) {
		printf("口令不对哦！\n");rewind(stdin);
		go_on();
	}
	else {
		printf("\n输入新的口令的说：\n");rewind(stdin);
		password = password_get();
		printf("\n请再输一次的说：\n");rewind(stdin);
		password2 = password_get();
		if (strcmp(password, password2) != 0) {
			printf("两次输入不一致的说！重新来过的说\n");rewind(stdin);
		}
		else {
			re = 1;
			switch (x) {//1:学生  2:老师   3:管理员
			case 1:strcpy(account_stu[i].password, password);break;
			case 2:strcpy(account_ter[i].password, password);break;
			case 3:strcpy(account_admin[i].password, password);break;
			default:
				print_re();
				break;
			}
		}
	}
	return re;
}

void process_tergrade() {//教师端成绩查询过程
	char judge = choice(),exam=0;
	switch (judge) {
	case'1'://singlegrade_search();go_on();exam=1;
	case'2':if (exam == 0) { singlegrade_analyze();go_on();exam = 2; }
	}
}

void singlegrade_analyze() {//教师按名字或学号查询个人成绩
	char *obj = (char *)malloc(sizeof(char) * 100);
	obj = accountname_get();
	int i = account_cmp(obj);
	if ( i != -1&&(strcmp(account_stu[i].name,obj)==0|| strcmp(account_stu[i].stunum, obj) == 0)) {//有此人并且是学生
		grade_cnt(&Class, find_classnum(&Class, obj), obj);
	}
	else {
		print_no();
	}
}
/*void a1() {输出本班成绩
	for (p = Class.head->next;p;p++) {
		if (p->element.classes == 1) {
			printf("%s	%s", p->element.name, p->element.stunum);
		}
	}
}*/