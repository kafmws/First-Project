#include"stdafx.h"
#include"statements.h"
extern List Class;
extern struct tm *time_tm;

int password_cmp(char *password,int i) {//-1:�������   1��ѧ��      2����ʦ    3��admin
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

int account_cmp(char *account) {//-1:�˺Ų�����   re�˺��ڽṹ�������е��±�
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

void initialize_time() {//��ȡ��ǰʱ��
	time_t now;
	time(&now);
	time_tm=localtime(&now);
}

char *greeting_get(int choice) {
	char *re=(char *)malloc(sizeof(char)*160);
	re[0] = '\0';
	initialize_time();//��ȡ��ǰʱ��
	switch (choice) {//1��ѧ��   2����ʦ  3������Ա
	case 1:
		if (6 <= time_tm->tm_hour &&time_tm->tm_hour <= 7)
			strcpy(re, "�簲qwq��һ��֮�����ڳ�");
		else if (8 <= time_tm->tm_hour &&time_tm->tm_hour <= 10)
			strcpy(re, "�����O(��_��)O������ҲԪ������\\(^o^)/");
		else if (11 <= time_tm->tm_hour &&time_tm->tm_hour <= 13)
			strcpy(re, "����ã�������orz");
		else if (14 <= time_tm->tm_hour &&time_tm->tm_hour <= 18)
			strcpy(re, "�����(�R�بQ),  QAQ�������ӿ���?");
		else if (19 <= time_tm->tm_hour &&time_tm->tm_hour <= 22)
			strcpy(re, "���Ϻ�qwq���ǵ�д��ҵ����");
		else {
			strcpy(re, "��ȥ˯������Ȼ���㹷ͷ��");
		}break;
	case 2:
		if (6 <= time_tm->tm_hour &&time_tm->tm_hour <= 11)
			strcpy(re, "�����");
		else if (12 <= time_tm->tm_hour &&time_tm->tm_hour <= 1)
			strcpy(re, "�����");
		else if (2 <= time_tm->tm_hour &&time_tm->tm_hour <= 18)
			strcpy(re, "�����");
		else if (19 <= time_tm->tm_hour &&time_tm->tm_hour <= 21)
			strcpy(re, "���Ϻ�");
		else {
			strcpy(re, "ҹ���ˣ��������Ϣ");
		}break;
	case 3:
		if (6 <= time_tm->tm_hour &&time_tm->tm_hour <= 11)
			strcpy(re, "�꣬��֪����Ϊ�˼�����(��)�Ĺ�������������\nȡ���������ɼ��Ĺ���Ӵ");
		else if (12 <= time_tm->tm_hour &&time_tm->tm_hour <= 1)
			strcpy(re, "�꣬��ʲô��û˵");
		else if (2 <= time_tm->tm_hour &&time_tm->tm_hour <= 18)
			strcpy(re, "��ʵֻ�����˺�Ҳͦ�õ�2333");
		else if (19 <= time_tm->tm_hour &&time_tm->tm_hour <= 21)
			strcpy(re, "���Ϻã�͵͵�����㣬��ʵ����һ��process_ter()��Ҳ�Ϳ��Թ���ɼ���Ŷ");
		else {
			strcpy(re, "ҹ���ˣ��������Ϣ");
		}break;
	default:
		printf("��ʵִ����������ǲ����ܵ�\n");
		print_re();
		break;
	}
	return re;
}

void grade_appeal() {
	printf("��������������Ҫ���ߵĿ�Ŀ��������ʦ����\n");
	printf("�ո��س�������\n");rewind(stdin);
	char *subject = (char *)malloc(sizeof(char) * 7);
	char *teachername = (char *)malloc(sizeof(char) * 14);
	if (scanf("%s %s", subject,teachername) != 2) {//���벻��ȷ
		rewind(stdin);
		print_examinput();
	}
	else {
		if (account_cmp(teachername) ==-1) {
			printf("û�������ʦ(>��<),��ȷ�Ϻ�����������\n");rewind(stdin);
		}
		else if(find_classnum(&Class,present)==find_terclass(teachername)){
			if (find_classnum(&Class, present) == -1 || find_terclass(teachername) == -1) {
				printf("�༶���Ҵ���\n");
				print_re();
			}
			FILE *fp = fopen(".\\grade-appeal.txt", "a+");
			fprintf(fp, "%d	%s	%s	%s\n",find_classnum(&Class,present),present, subject, teachername);
			fclose(fp);
			printf("�����ѱ��ύ����ȴ���ʦ����(/�أ�)\n");rewind(stdin);
		}
		else {
			printf("�ⲻ�������ʦ��(��_��|||)\n");rewind(stdin);
		}
	}
}

void process_stugrade() {//ѧ���ɼ������ѡ��
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

int find_classnum(List* list,char *present) {//���˺Ż�ѧ�ŷ��ص�ǰѧ�����ڰ༶
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

int find_terclass(char *account) {//����������ʦ�༶
	int i,re=-1;
	for (i = 0;i < TERNUM;i++) {
		if (strcmp(account, account_ter[i].name)==0)
		re = account_ter[i].classs;
	}
	return re;
}

int modify_password(int i) {// x�˻�����   i  Ҫ�޸ĵ��˻��±�   
	printf("������ԭ���\n");rewind(stdin);
	char *password = (char *)malloc(sizeof(char)*PASS);
	char *password2 = (char *)malloc(sizeof(char)*PASS);
	password = password_get();
	int x = password_cmp(password, i),re=0;
	if (x==-1) {
		printf("�����Ŷ��\n");rewind(stdin);
		go_on();
	}
	else {
		printf("\n�����µĿ����˵��\n");rewind(stdin);
		password = password_get();
		printf("\n������һ�ε�˵��\n");rewind(stdin);
		password2 = password_get();
		if (strcmp(password, password2) != 0) {
			printf("�������벻һ�µ�˵������������˵\n");rewind(stdin);
		}
		else {
			re = 1;
			switch (x) {//1:ѧ��  2:��ʦ   3:����Ա
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

void process_tergrade() {//��ʦ�˳ɼ���ѯ����
	char judge = choice(),exam=0;
	switch (judge) {
	case'1'://singlegrade_search();go_on();exam=1;
	case'2':if (exam == 0) { singlegrade_analyze();go_on();exam = 2; }
	}
}

void singlegrade_analyze() {//��ʦ�����ֻ�ѧ�Ų�ѯ���˳ɼ�
	char *obj = (char *)malloc(sizeof(char) * 100);
	obj = accountname_get();
	int i = account_cmp(obj);
	if ( i != -1&&(strcmp(account_stu[i].name,obj)==0|| strcmp(account_stu[i].stunum, obj) == 0)) {//�д��˲�����ѧ��
		grade_cnt(&Class, find_classnum(&Class, obj), obj);
	}
	else {
		print_no();
	}
}
/*void a1() {�������ɼ�
	for (p = Class.head->next;p;p++) {
		if (p->element.classes == 1) {
			printf("%s	%s", p->element.name, p->element.stunum);
		}
	}
}*/