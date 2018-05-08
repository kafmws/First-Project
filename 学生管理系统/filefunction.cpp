#include"stdafx.h"
#include"statements.h"
int STUNUM, TERNUM, ADMINNUM=3;
extern List Class;
void import_account() {//�����ļ��е��˺�����
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

void import_stu(List *list) {//��ȡѧ����Ϣ������   evaluateÿ�����¼���
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

void import_timetable() {//��ȡ������α�
	char *tablestr = (char *)malloc(sizeof(char) * 80);
	int day = time_tm->tm_wday;
	if (1 <= day&&day <= 5) {
		FILE *fp = fopen(".\\timetable.txt", "r");
		while (day--) {
			fscanf(fp,"%[^\n]%*c",tablestr);
		}
		fclose(fp);
		puts(tablestr);
		printf("�����Ͽ�Ŷ����Ȼ���㹷ͷ(�s�F0��)�s�� �ة��� \n");rewind(stdin);
	}
	else {
		printf("����û���أ�(������)\n");rewind(stdin);
	}
}

void fileadd(node* p,data tem) {//�ļ��ж�ȡ�洢���ڵ�������
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

void save_stu(int i) {//����ѧ����Ϣ   i  0:����ѧ����Ϣ  1�����ص�ָ���ļ�Ŀ¼
	char file[50];
	if (i) {//����
		printf("����ʹ��TXT�ļ�\n");
		printf("����.\\\\xxx.xx�ĸ�ʽ�����ļ�����\n");rewind(stdin);
		int exam = 0;
		do {
			scanf("%s", file);
			if (file[0] != '.'&&file[1] != '\\'&&file[2] != '\\') {
				print_error();
				exam = 1;
			}
		} while (exam != 0 && (exam = 0, 1));
	}
	else if (i == 0) {//����ѧ����Ϣ
		strcpy(file, "student.txt");
	}if (i) { printf("��������......\n");rewind(stdin); }
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
			printf("%s��Ϊ�Լ���%s�ɼ�����\n", apper, sub);rewind(stdin);exam = 1;
		}
	}
	if (0 == exam) {
		printf("û���κ�����Ŷ\n");rewind(stdin);
	}
	fclose(fp);
	return exam;
}

int signup_get() {//��ȡ�������˺�����
	char str[4][100],c='0';
	int re = 0;
	FILE *fp = fopen(".\\account_sign_up.txt", "r");
	if (c=fgetc(fp),c=fgetc(fp) && c != EOF) {
		fclose(fp);
		FILE *fp = fopen(".\\account_sign_up.txt", "r");
		while (fscanf(fp, "%s\t%s\t%s\t%s", str[0], str[1], str[2], str[3]) != EOF) {
			printf("ע����Ϣ:  %s   %s  �������Ϣ���ͣ�%s  ��Ϣ��Դ��%s\n", str[0], str[1], str[2], str[3]);
		}
		re = 1;
	}
	else {
		printf("��������\n");rewind(stdin);
	}
	fclose(fp);
	return re;
}

void account_appeal() {//�˺�����
	printf("�������û�����ѧ�š���ʦ�����������ϵ��ʽ\n");
	printf("�ո��س�������\n");rewind(stdin);
	char str[4][50];
	scanf("%s%s%s%s", str[0], str[1], str[2], str[3]);
	FILE *fp = fopen(".\\account_sign_up.txt", "a+");
	fprintf(fp, "%s	%s	%sѧ������	%s\n", str[0], str[1], str[2], str[3]);
	fclose(fp);
	printf("��ȴ�����Ա֪ͨ\n");rewind(stdin);
}

void del_infomation(int i) {//������߻��˺�����  i  1: �˺�����   2:�ɼ�����   3:�˺ŵ�¼��¼
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

void account_add() {//�����˺�
	char name[Name], stunumber[25], password[PASS],exam=0;
	printf("������������\n");rewind(stdin);
		do {
			scanf("%s", name);
			for (int i = 0;(unsigned)i < strlen(name);i++) {//���Ƿ�����
				if (0 <= name[i] && name[i] <= 255) {
					exam = 1;print_examinput();break;
				}
			}
		} while (exam != 0 && (exam = 0, 1));
		printf("�������λѧ�ţ�\n");rewind(stdin);
		do {//ѧ�ż��
			scanf("%s", stunumber);
				if (strlen(stunumber)!=8) {
					exam = 1;
				}if (exam) {
					print_examinput();
				}
				for (int i = 0;i < STUNUM;i++) {
					if (strcmp(account_stu[i].stunum, stunumber) == 0) {//����
						printf("��ѧ���Ѵ��ڣ����������룺\n");exam = 1;
					}
				}
				
		} while (exam != 0 && (exam = 0, 1));
		printf("���Զ����ó�ʼ����\n");rewind(stdin);
		FILE *fp = fopen(".\\account_stu.txt", "a+");
		fprintf(fp,"%s	%s	%s\n", name, stunumber,"123456");
		fclose(fp);
		import_account();//���¼����ļ�
}

void account_print() {//�鿴�˺�
	char *account = accountname_get();
	int i = account_cmp(account);
	if(i!=-1)printf("�û���:%s	 ѧ��:%s	����%s\n", account_stu[i].name, account_stu[i].stunum, account_stu[i].password);
	else { printf("�˺Ų����ڣ�"); }
}

void account_kill() {//ɾ���˺�
	char *account = accountname_get();
	int i = account_cmp(account);
	if (i == -1) {
		printf("�˺Ų�����!\n");
	}
	else {
		if (warning()) {
			account_stu[i].name[0] = '\0';
			save_account();
			import_account();
		}
	}
	
}

void account_change(){//�޸��˺�
	char *account = accountname_get();
	int i = account_cmp(account);
	if (i != -1) {
		printf("1.�û��� 2.ѧ�� 3.��¼����\n");rewind(stdin);
		char judgement = choice();
		while (judgement != '1'&&judgement != '2'&&judgement != '3') {
			print_examinput();
			judgement = choice();
		}
		int exam = 0;char name[50];printf("������:\n");rewind(stdin);
		switch (judgement) {
		case'1':do {
			scanf("%s", name);
			for (i = 0;(unsigned)i < strlen(name);i++) {//���Ƿ�����
				if (0 <= name[i] && name[i] <= 255) {
					exam = 1;print_examinput();break;
				}
			}
		} while (exam != 0 && (exam = 0, 1));
		strcpy(account_stu[i].name, name);break;
		case'2':
			scanf("%s", name);
			while (strlen(name) != 8) {
				print_examinput();
				scanf("%s", name);
			}
			strcpy(account_stu[i].stunum, name);break;
		case'3':
			scanf("%s", name);
			while (strlen(name) < 6 || strlen(name) > 12) {
				print_examinput();
				scanf("%s", name);
			}strcpy(account_stu[i].password, name);break;
		default:
			print_re();
			break;
		}if (judge()) {
			save_account();
			import_account();
		}
		else {
			import_account();
		}
	}
	else { printf("�˺Ų����ڣ�"); }
}

int log_get() {//��¼��¼�Ķ�ȡ������
	char str[4][50], re = 0, c;
	FILE *fp = fopen(".\\sign_log.txt", "r");
	if (c = fgetc(fp), c = fgetc(fp) && c != EOF) {
		fclose(fp);
		printf("�����ǽ��յ�¼��¼:\n"); 
		printf("ʱ��			�û���		��¼״����\n"); rewind(stdin);
		FILE *fp = fopen(".\\sign_log.txt", "r");
		while (fscanf(fp, "%s\t%s\t%s\t%s", str[0], str[1], str[2],str[3]) != EOF) {
			printf("%s  %s          %-6s             %-6s\n", str[0], str[1], str[2], str[3]);
		}
		re = 1;
	}
	else {
		printf("���޼�¼\n"); rewind(stdin);
	}
	fclose(fp);
	return re;
}