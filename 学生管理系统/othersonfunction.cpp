#include"stdafx.h"
#include"statements.h"
extern List Class;
extern struct tm *time_tm;

int password_cmp(char *password,int i) {//-1:�������   1��ѧ��      2����ʦ    3��admin
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

int account_cmp(char *account) {//-1:�˺Ų�����   re�˺��ڽṹ�������е��±�
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
			strcpy(re, "�꣬��֪����Ϊ�˼�����(��)�Ĺ�������������\n		ȡ���������ɼ��Ĺ���Ӵ");
		else if (12 <= time_tm->tm_hour &&time_tm->tm_hour <= 1)
			strcpy(re, "�꣬��ʲô��û˵");
		else if (2 <= time_tm->tm_hour &&time_tm->tm_hour <= 18)
			strcpy(re, "��ʵֻ�����˺�Ҳͦ�õ�2333");
		else if (19 <= time_tm->tm_hour &&time_tm->tm_hour <= 21)
			strcpy(re, "���Ϻã�͵͵�����㣬��ʵ����9\n		�Ϳ��Թ���ɼ���Ŷ");
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
		int exam = 0;
		for (int i = 0;i < Subject;i++) {
			if (strcmp(subject, SUBJECT[i]) == 0) {
				exam = 1;break;
			}
		}if (exam == 1) {
			if (account_cmp(teachername) == -1) {
				printf("û�������ʦ(>��<),��ȷ�Ϻ�����������\n");rewind(stdin);
			}
			else if (find_classnum(&Class, present) == find_terclass(teachername)) {
				if (find_classnum(&Class, present) == -1 || find_terclass(teachername) == -1) {
					printf("�༶���Ҵ���\n");
					print_re();
				}
				FILE *fp = fopen(".\\grade-appeal.txt", "a+");
				fprintf(fp, "%s	%s	%s\n", present, subject, teachername);
				fclose(fp);
				printf("�����ѱ��ύ����ȴ���ʦ����(/�أ�)\n");rewind(stdin);
			}
			else {
				printf("�ⲻ�������ʦ��(��_��|||)\n");rewind(stdin);
			}
		}
		else {
			printf("û�������Ŀ(��_��|||)\n");rewind(stdin);
		}
	}
}

void process_stugrade() {//ѧ���ɼ������ѡ��
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
		if (strcmp(account, account_ter[i].name) == 0) {
			re = account_ter[i].classs;
			break;
		}
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
		printf("\n�����Ŷ��\n");rewind(stdin);
	}
	else {
		printf("\n�����µĿ����˵��\n");rewind(stdin);
		password = password_get();
		printf("\n������һ�ε�˵��\n");rewind(stdin);
		password2 = password_get();
		if (strcmp(password, password2) != 0) {
			printf("\n�������벻һ�µ�˵������������˵\n");rewind(stdin);
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
	}printf("\n");
	return re;
}

void process_tergrade() {//��ʦ�˳ɼ���ѯ����
	char judge = choice(),exam=0,i;
	switch (judge) {
	case'0':break;
	case'1':singlegrade_print();exam = 1;
	case'2':if (exam == 0) { singlegrade_analyze();exam = 2; }
	case'3':if (exam == 0) { print_subject();grade_analyze(&Class, find_terclass(present), choice()- '1');exam = 3; }
	case'4':if (exam == 0) {
		print_subject();sort_stu(&Class, (i=choice() - '1')> 5 ? 9 :i);/*��ֹ����Խ��*/
		print_class(&Class);rewind(stdin); exam = 4;}
	case'5':if (exam == 0) {
		sort_stu(&Class, 6);print_class(&Class);rewind(stdin); exam = 5;
	}
	case'6':if (exam == 0) {
		sort_stu(&Class, 7);print_class(&Class);rewind(stdin);exam = 6;
	}
	case'7':if (exam == 0) {
		printf("��ѡ������˳��\n");print_subject();printf("7.�ۺ�	8.ѧ��\n");rewind(stdin);sort_stu(&Class, choice() - '1');save_stu(1);print_changeok();exam = 7;
	}
	default:
		if (exam == 0) { print_error();go_on();
		}
		if(exam!=0)go_on(); show_tergrade();process_tergrade();
		break;
	}
}

void singlegrade_print() {//��ѧ�Ż����ִ�ӡ���˳ɼ�
	char *obj = (char *)malloc(sizeof(char) * 100);
	obj = accountname_get();
	if (find_terclass(present) == find_classnum(&Class, obj)||find_terclass(present) == -1) {
		print_blankhead();
		search(&Class, obj);
	}
	else {
		if (change(&Class, obj) != NULL) { printf("���ѧ����������Ӵ~\n");rewind(stdin); }
		else { (search(&Class, obj));}
	}
}

void singlegrade_analyze() {//��ʦ�����ֻ�ѧ�ŷ������˳ɼ�
	char *obj = (char *)malloc(sizeof(char) * 100);
	obj = accountname_get();
	int i = account_cmp(obj);
	if (i != -1) {
		if (strcmp(account_stu[i].name, obj) == 0 || strcmp(account_stu[i].stunum, obj) == 0) {//�д��˲�����ѧ��
			if (find_terclass(present) == find_classnum(&Class, obj)|| find_terclass(present)==-1) {//�������ʦ�༶��ͬ   �����ǹ���Ա
				singlegrade_cnt(&Class, find_classnum(&Class, obj), obj);
			}
			else {//�༶����ͬ
				printf("���ѧ����������Ӵ~\n");rewind(stdin);
			}
		}
	}
	else { print_no();search(&Class, obj); }//���޴���
}

void stu_add(data *ptem) {//ѧ����Ϣ�����
	int exam = 0, i,cnt=0;
	double sum = 0;
	ptem->evaluate = 0;
	for (i = 0;i < Subject;i++) {
		ptem->grade[i] = -1;
	}//��ʼ��
	do {
		printf("������ѧ������:\n");rewind(stdin);
		scanf("%s", ptem->name);
		for (i = 0;(unsigned)i < strlen(ptem->name);i++) {//���Ƿ�����
			if (0 <= ptem->name[i] && ptem->name[i] <= 255) {
				exam = 1;print_examinput();break;
			}
		}
	} while (exam != 0&&(exam=0,1));//�õ�ѧ������     ������Ψһ   ѧ��Ψһ
	exam = 0;
	do {
		printf("�������λѧ�ţ�\n");rewind(stdin);
		scanf("%s", ptem->stunum);
		if (strlen(ptem->stunum) != 8) {//���λ��
			exam = 1;
		}
		if (0 == exam){
			for (i = 0;(unsigned)i < strlen(ptem->stunum);i++) {//���Ƿ�����
				if ('0' > ptem->stunum[i] || ptem->stunum[i] > '9') {
					exam = 1;break;
				}
			}
		}
		if (0 == exam) {
			node *p = NULL;
			for (p = Class.head->next;p->next;p = p->next) {
				if (strcmp(p->element.stunum, ptem->stunum) == 0) {//����ظ�ѧ��
					exam = 1;break;
				}
			}
		}
		if (exam) {
			printf("ѧ������������ѧ���Ѵ��ڣ�\n");
			rewind(stdin);
		}
	} while (exam != 0&&(exam=0,cnt++,1)&&cnt<2);
	if (cnt == 2) {
		show_teacher();
	}show_teacher();
	ptem->classes = atoi(ptem->stunum) % 100 / 30; //����༶
	printf("�Ƿ�¼��ɼ���(0/1):\n");rewind(stdin);
	int judge = choice();
	while (judge != '0'&&judge != '1') {
		print_error();
		printf("�Ƿ�¼��ɼ���(0/1):\n");rewind(stdin);
		judge = choice();
	}//ѡ��
	if (judge == '1') {
		printf("�밴������˳��¼��ɼ�(0~100)��\n");
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
		printf("��ͬѧ���гɼ���Ĭ��Ϊ-1\n");rewind(stdin);
	}
	else {
		printf("��ʵִ�и�����ǲ����ܵ�\n");
		print_re();
	}
	ptem->evaluate = sum / Subject;//�����ۺϳɼ�
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

void log(int i) {//i      1 ���ɹ���½     0��δ�ɹ���½
	initialize_time();
	char con[15];
	if (i) {
		strcpy(con, "�ɹ�");
	}
	else {
		strcpy(con, "ʧ��");
	}
	FILE *fp = fopen(".\\sign_log.txt", "a+");
	fprintf(fp, "%d-%d-%d	%02d:%02d	%s	%s\n", time_tm->tm_year+1900, time_tm->tm_mon, time_tm->tm_mday, time_tm->tm_hour, time_tm->tm_min, present,con);
	fclose(fp);
 }

void password_change(char *obj,int i) {//  i      1 :  ����     2:����
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

int validate() {//re: 0����֤ʧ��  1����֤�ɹ� 
	char num[80], obj[8];
	int re = 1,i;
	printf("�����������֤�룺\n"); rewind(stdin);
	for ( i = 0; i < 6; i++) {
		srand((unsigned int)time(NULL));
		int number = rand() % 9 + 1;//����1~9�������
		printf("%d",number); obj[i] = number + '0';
		Sleep(1000);
	}obj[i] = '\0'; printf("\n"); rewind(stdin);
	scanf("%s", num);
	if (strcmp(num, obj) != 0) {
		re = 0;
		printf("��֤ʧ�ܣ�\n");
	}
	if (re) {
		printf("��֤�ɹ�\n"); Sleep(1000);
		show_sign();
	}
	return re;
}