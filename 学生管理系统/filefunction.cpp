#include"stdafx.h"
#include"statements.h"

void import_account() {//读入文件中的账号密码
	int i;
	FILE *fp=fopen(".\\account.txt","r");
	for (i = 0;i < STUNUM;i++) {
		fscanf(fp, "%s\t%s\t%s", account_stu[i].name,account_stu[i].stunum,account_stu[i].password);
	}
	for (i = 0;i < TERNUM;i++) {
		fscanf(fp, "%s\t%d\t%s", account_ter[i].name,&account_ter[i].classs, account_ter[i].password);
	}
	for (i = 0;i < ADMINNUM;i++) {
		fscanf(fp, "%s\t%s", account_admin[i].name, account_admin[i].password);
	}
	fclose(fp);
}

void import_stu(List *list) {//读取学生信息到链表
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
	int day = time_tm->tm_wday + 1;
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
	FILE *fp = fopen(".\\account.txt", "w+");
	if (fp == NULL) {
		print_re();
	}
	else {
		for (i = 0;i < STUNUM;i++) {
			fprintf(fp, "%s\t%s\t%s\n", account_stu[i].name, account_stu[i].stunum, account_stu[i].password);
		}
		for (i = 0;i < TERNUM;i++) {
			fprintf(fp, "%s\t%d\t%s\n", account_ter[i].name, account_ter[i].classs, account_ter[i].password);
		}
		for (i = 0;i < ADMINNUM;i++) {
			fprintf(fp, "%s\t%s\n", account_admin[i].name, account_admin[i].password);
		}
		fclose(fp);
		print_changeok();
	}
}