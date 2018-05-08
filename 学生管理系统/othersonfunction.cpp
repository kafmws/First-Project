#include"stdafx.h"
#include"statements.h"
extern List Class;
extern struct tm *time_tm;

int password_cmp(char *password,int i) {//-1:密码错误   1：学生      2：老师    3：admin
	 int re=-1;//re stands for accountclass
	 if (strcmp(password, account_stu[i].password) == 0&& (strlen(present) == 0 ? 1 : strcmp(present, account_stu[i].name) == 0)){
		 re = 1;//strcpy_s(present, account_stu[i].name);
	 }
	 if (re == -1&&i < TERNUM)
		 if (strcmp(password, account_ter[i].password) == 0 && (strlen(present) == 0 ? 1 : strcmp(present, account_ter[i].name) == 0)) {
			 re = 2;//strcpy_s(present, account_ter[i].name);
		 }
	 if(re==-1&&i<ADMINNUM)
		 if (strcmp(password, account_admin[i].password) == 0 && (strlen(present) == 0 ?1:strcmp(present, account_admin[i].name) == 0)) {
			 re = 3;if(present[0]=='\0')strcpy_s(present, account_admin[i].name);
		 }
	 //free(password);
	return re;
}

int account_cmp(char *account) {//-1:账号不存在   re账号在结构体数组中的下标
	int i,re=-1;
	for (i = 0;i < STUNUM;i++) {
		if (strcmp(account, account_stu[i].name) == 0||strcmp(account,account_stu[i].stunum)==0) {
			re = i;if(strlen(present)==0)strcpy_s(present, account_stu[i].name);
			break;
		}
	}
	if (re == -1) {
		for (i = 0;i < TERNUM;i++) {
			if (strcmp(account, account_ter[i].name) == 0) {
				re = i;if (strlen(present) == 0)strcpy_s(present, account_ter[i].name);
				break;
			}
		}
	}
	if (re == -1) {
		for (i = 0;i < ADMINNUM;i++) {
			if (strcmp(account, account_admin[i].name) == 0) {
				re = i;if (strlen(present) == 0)strcpy_s(present, account_admin[i].name);
				break;
			}
		}
	}
	//free(account);
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
			strcpy(re, "嘘，你知道吗，为了减轻你(他)的工作量，开发者\n		取消了你管理成绩的功能哟");
		else if (12 <= time_tm->tm_hour &&time_tm->tm_hour <= 1)
			strcpy(re, "嘘，我什么都没说");
		else if (2 <= time_tm->tm_hour &&time_tm->tm_hour <= 18)
			strcpy(re, "其实只管理账号也挺好的2333");
		else if (19 <= time_tm->tm_hour &&time_tm->tm_hour <= 21)
			strcpy(re, "晚上好，偷偷告诉你，其实输入9\n		就可以管理成绩了哦");
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
		int exam = 0;
		for (int i = 0;i < Subject;i++) {
			if (strcmp(subject, SUBJECT[i]) == 0) {
				exam = 1;break;
			}
		}if (exam == 1) {
			if (account_cmp(teachername) == -1) {
				printf("没有这个老师(>︿<),请确认后重新来过。\n");rewind(stdin);
			}
			else if (find_classnum(&Class, present) == find_terclass(teachername)) {
				if (find_classnum(&Class, present) == -1 || find_terclass(teachername) == -1) {
					printf("班级查找错误！\n");
					print_re();
				}
				FILE *fp = fopen(".\\grade-appeal.txt", "a+");
				fprintf(fp, "%s	%s	%s\n", present, subject, teachername);
				fclose(fp);
				printf("申诉已被提交，请等待老师处理(/ω＼)\n");rewind(stdin);
			}
			else {
				printf("这不是你的老师！(￣_￣|||)\n");rewind(stdin);
			}
		}
		else {
			printf("没有这个科目(￣_￣|||)\n");rewind(stdin);
		}
	}
}

void process_stugrade() {//学生成绩界面的选择
	char tem, exam = 0;
	switch (tem = choice()) {
	case '0':break;
	case '1':print_blankhead();search(&Class, present);exam = 1;
	case '2':if (exam == 0) { singlegrade_cnt(&Class, find_classnum(&Class, present),present); exam = 2;}
	case '3':if (exam == 0) { grade_appeal();rewind(stdin); exam = 3; }
	default:
		if (exam == 0) { print_error();go_on();
		}
		if(exam!=0)go_on();show_stugrade();process_stugrade();
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
		if (strcmp(account, account_ter[i].name) == 0) {
			re = account_ter[i].classs;
			break;
		}
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
		printf("\n口令不对哦！\n");rewind(stdin);
	}
	else {
		printf("\n输入新的口令的说：\n");rewind(stdin);
		password = password_get();
		printf("\n请再输一次的说：\n");rewind(stdin);
		password2 = password_get();
		if (strcmp(password, password2) != 0) {
			printf("\n两次输入不一致的说！重新来过的说\n");rewind(stdin);
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
	}printf("\n");
	return re;
}

void process_tergrade() {//教师端成绩查询过程
	char judge = choice(),exam=0,i;
	switch (judge) {
	case'0':break;
	case'1':singlegrade_print();exam = 1;
	case'2':if (exam == 0) { singlegrade_analyze();exam = 2; }
	case'3':if (exam == 0) { print_subject();grade_analyze(&Class, find_terclass(present), choice()- '1');exam = 3; }
	case'4':if (exam == 0) {
		print_subject();sort_stu(&Class, (i=choice() - '1')> 5 ? 9 :i);/*防止功能越界*/
		print_class(&Class);rewind(stdin); exam = 4;}
	case'5':if (exam == 0) {
		sort_stu(&Class, 6);print_class(&Class);rewind(stdin); exam = 5;
	}
	case'6':if (exam == 0) {
		sort_stu(&Class, 7);print_class(&Class);rewind(stdin);exam = 6;
	}
	case'7':if (exam == 0) {
		printf("请选择名单顺序\n");print_subject();printf("7.综合	8.学号\n");rewind(stdin);sort_stu(&Class, choice() - '1');save_stu(1);print_changeok();exam = 7;
	}
	default:
		if (exam == 0) { print_error();go_on();
		}
		if(exam!=0)go_on(); show_tergrade();process_tergrade();
		break;
	}
}

void singlegrade_print() {//按学号或名字打印个人成绩
	char *obj = (char *)malloc(sizeof(char) * 100);
	obj = accountname_get();
	if (find_terclass(present) == find_classnum(&Class, obj)||find_terclass(present) == -1) {
		print_blankhead();
		search(&Class, obj);
	}
	else {
		if (change(&Class, obj) != NULL) { printf("这个学生不是你班的哟~\n");rewind(stdin); }
		else { (search(&Class, obj));}
	}
}

void singlegrade_analyze() {//教师按名字或学号分析个人成绩
	char *obj = (char *)malloc(sizeof(char) * 100);
	obj = accountname_get();
	int i = account_cmp(obj);
	if (i != -1) {
		if (strcmp(account_stu[i].name, obj) == 0 || strcmp(account_stu[i].stunum, obj) == 0) {//有此人并且是学生
			if (find_terclass(present) == find_classnum(&Class, obj)|| find_terclass(present)==-1) {//并且与教师班级相同   或者是管理员
				singlegrade_cnt(&Class, find_classnum(&Class, obj), obj);
			}
			else {//班级不相同
				printf("这个学生不是你班的哟~\n");rewind(stdin);
			}
		}
	}
	else { print_no();search(&Class, obj); }//查无此人
}

void stu_add(data *ptem) {//学生信息的添加
	int exam = 0, i,cnt=0;
	double sum = 0;
	ptem->evaluate = 0;
	for (i = 0;i < Subject;i++) {
		ptem->grade[i] = -1;
	}//初始化
	do {
		printf("请输入学生姓名:\n");rewind(stdin);
		scanf("%s", ptem->name);
		for (i = 0;(unsigned)i < strlen(ptem->name);i++) {//检查非法输入
			if (0 <= ptem->name[i] && ptem->name[i] <= 255) {
				exam = 1;print_examinput();break;
			}
		}
	} while (exam != 0&&(exam=0,1));//得到学生姓名     姓名不唯一   学号唯一
	exam = 0;
	do {
		printf("请输入八位学号：\n");rewind(stdin);
		scanf("%s", ptem->stunum);
		if (strlen(ptem->stunum) != 8) {//检查位数
			exam = 1;
		}
		if (0 == exam){
			for (i = 0;(unsigned)i < strlen(ptem->stunum);i++) {//检查非法输入
				if ('0' > ptem->stunum[i] || ptem->stunum[i] > '9') {
					exam = 1;break;
				}
			}
		}
		if (0 == exam) {
			node *p = NULL;
			for (p = Class.head->next;p->next;p = p->next) {
				if (strcmp(p->element.stunum, ptem->stunum) == 0) {//检查重复学号
					exam = 1;break;
				}
			}
		}
		if (exam) {
			printf("学号输入有误或该学号已存在！\n");
			rewind(stdin);
		}
	} while (exam != 0&&(exam=0,cnt++,1)&&cnt<2);
	if (cnt == 2) {
		show_teacher();
	}show_teacher();
	ptem->classes = atoi(ptem->stunum) % 100 / 30; //计算班级
	printf("是否录入成绩？(0/1):\n");rewind(stdin);
	int judge = choice();
	while (judge != '0'&&judge != '1') {
		print_error();
		printf("是否录入成绩？(0/1):\n");rewind(stdin);
		judge = choice();
	}//选择
	if (judge == '1') {
		printf("请按照以下顺序录入成绩(0~100)：\n");
		for (i = 0;i < Subject;i++) {
			printf("%s   ", SUBJECT[i]);
		}
		printf("\n");rewind(stdin);
		for (i = 0;i < Subject;i++) {
			scanf("%d", &ptem->grade[i]);sum += ptem->grade[i];
			if (0>ptem->grade[i]||ptem->grade[i]>100) {
				sum -= ptem->grade[i];i--;
				print_examinput();
			}
		}
	}
	else if(judge=='0'){
		printf("该同学所有成绩将默认为-1\n");rewind(stdin);
	}
	else {
		printf("其实执行该语句是不可能的\n");
		print_re();
	}
	ptem->evaluate = sum / Subject;//计算综合成绩
}

void process_account() {
	char judge = choice(), exam = 0;
	switch (judge) {
	case'0':break;
	case'1':account_add();exam = 1;
	case'2':if (exam == 0) { account_kill();exam = 1; }
	case'3':if (exam == 0) { account_print(); exam = 3; }
	case'4':if (exam == 0) { account_change();exam = 4; }
	default:
		if (exam == 0) { print_error();go_on();
		}
		if (exam != 0) { go_on(); }show_account();process_account();
	}
}

void log(int i) {//i      1 ：成功登陆     0：未成功登陆
	initialize_time();
	char con[15];
	if (i) {
		strcpy(con, "成功");
	}
	else {
		strcpy(con, "失败");
	}
	FILE *fp = fopen(".\\sign_log.txt", "a+");
	fprintf(fp, "%d-%d-%d	%02d:%02d	%s	%s\n", time_tm->tm_year+1900, time_tm->tm_mon, time_tm->tm_mday, time_tm->tm_hour, time_tm->tm_min, present,con);
	fclose(fp);
 }

void password_change(char *obj,int i) {//  i      1 :  加密     2:解密
	if (i == 1) {
		for (i = 0; i < strlen(obj); i++) {
			obj[i] += i;
		}
	}
	else if(i==2){
		for (i = 0; i < strlen(obj); i++) {
			obj[i] -= i;
		}
	}
	else {
		print_re();
	}
}

int validate() {//re: 0：验证失败  1：验证成功 
	char num[80], obj[8];
	int re = 1,i;
	printf("请输入随机验证码：\n"); rewind(stdin);
	for ( i = 0; i < 6; i++) {
		srand((unsigned int)time(NULL));
		int number = rand() % 9 + 1;//产生1~9的随机数
		printf("%d",number); obj[i] = number + '0';
		Sleep(1000);
	}obj[i] = '\0'; printf("\n"); rewind(stdin);
	scanf("%s", num);
	if (strcmp(num, obj) != 0) {
		re = 0;
		printf("验证失败！\n");
	}
	if (re) {
		printf("验证成功\n"); Sleep(1000);
		show_sign();
	}
	return re;
}