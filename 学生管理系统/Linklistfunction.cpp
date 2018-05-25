#include "stdafx.h"
#include"statements.h"
extern List Class;
//extern char present[Name];
void  add(List *list) {//����ѧ��  
	data temp;
	stu_add(&temp);
	if (node *p=(node *)malloc(sizeof(node))) {
		p->next = NULL;
		p->element = temp;
		list->tail->next = p;
		list->tail = p;
		FILE *fp = fopen(".\\account_sign_up.txt","a+");
		fprintf(fp,"%s\t%s\t%s\t%s��ʦ���\n",p->element.name,p->element.stunum,"123456",present);
		fclose(fp);
		printf("�����ѹ���Ա�����˺�\n");rewind(stdin);
	}
	else {
		printf("ʮ�ֱ�Ǹ����������Ӹ���ѧ����\n");
		print_re();
	}
}

//��������ѧ�Ų���name,stunum��Ϊ�ַ���
int kill(List *list, char *obj) {//ɾ
	int re = 0;
	node *p, *dead = NULL;
	for (p = list->head;p->next;p = p->next) {
		if (strcmp(p->next->element.stunum, obj) == 0 || strcmp(p->next->element.name, obj) == 0) {
			if (find_classnum(&Class, p->next->element.name) == find_terclass(present)) {
				//֪ͨ����Աɾ���˺�
				dead = p->next;
				FILE *fp = fopen(".\\account_sign_up.txt", "a+");
				fprintf(fp, "%s	%s	%s	%s��ʦɾ��", dead->element.name, dead->element.stunum, "  ", present);
				fclose(fp);
				p->next = dead->next;
				free(dead);
				re = 1;
				break;
			}
			else {
				printf("���ѧ������������\n");rewind(stdin);
			}
		}
	}
	return re;
}

//��������ѧ�Ų���    ����Ŀ��ڵ��ָ��
node * change(List *list, char *obj) {//��
	node *p = list->head->next;
	for (p;p;p = p->next) {
		if (strcmp(p->element.stunum, obj) == 0 || strcmp(p->element.name, obj) == 0) {
			return p;
		}
	}
	print_no();
	return NULL;
}

void modify_grade(node *p) {
	if (find_classnum(&Class, p->element.name) == find_terclass(present) || find_terclass(present) == -1) {
		show_teacher();
		printf("ѡ����Ҫ���ĵĿ�Ŀ��\n");rewind(stdin);
		print_subject();
		char judge = choice();
		while (judge <'1'&&judge >'6') {
			print_error();
			printf("������ѡ��\n");rewind(stdin);
			show_teacher();
			printf("ѡ����Ҫ���ĵĿ�Ŀ��\n");rewind(stdin);
			print_subject();
			judge = choice();
		}
		int tem, exam = 0, sum = 0;
		do {
			printf("�������µķ�����\n");rewind(stdin);
			scanf("%d", &tem);
			if (0 > tem || tem > 100) {
				print_examinput();
				show_teacher();
				exam = 1;
			}
		} while (exam != 0 && (exam = 0, 1));
		p->element.grade[judge - '1'] = tem;
		for (int i = 0;i < Subject;i++) {
			sum += p->element.grade[i];
		}
		p->element.evaluate = sum * 1.0 / Subject;
		print_changeok();
	}
	else {
		printf("�ⲻ������ѧ����\n");rewind(stdin);
	}
}

//������ӡ��������
void print_all(List *list) {//����������гɼ�
	node *p = list->head->next;
	for (p;p;p = p->next) {
		printf("%s %s ", p->element.name, p->element.stunum);
		for (int i = 0;i < Subject;i++) {
			printf("%d ", p->element.grade[i]);
		}
		printf("\n");
	}
}

void print_class(List *list) {//�����������ɼ�
	print_blankhead();
	node *p = list->head->next;
	for (p;p->next;p = p->next) {
		if (find_terclass(present) == p->element.classes || find_terclass(present) == -1) {
			printf("%s	%s ", p->element.name, p->element.stunum);
			for (int i = 0;i < Subject;i++) {
				printf("%6d  ", p->element.grade[i]);
			}
			printf("%8.2f", p->element.evaluate);
			printf("\n");rewind(stdin);
		}
	}
}
//��
void search(List *list, char *obj) {
	int flaghead = 1,emm=0;
	node *p = list->head->next;
	if(p)
	for (p;p->next;p = p->next) {
		if ( strcmp(p->element.name, obj) == 0|| strcmp(p->element.stunum, obj) == 0) {
			printf("%s	%s ", p->element.name, p->element.stunum);
			for (int i = 0;i < Subject;i++) {
				printf("%6d  ", p->element.grade[i]);
			}
			printf("%8.2f",p->element.evaluate);
			printf("\n");rewind(stdin);emm = 1;
			break;
		}
		else if (strstr(p->element.name, obj) != NULL || strstr(p->element.stunum, obj) != NULL) {//���벻������strstr�Ƚ�
			if (flaghead) {
				flaghead = 0;
				Sleep(500);printf("��������");Sleep(1500);printf(" ��   ");Sleep(1500);
				printf("Ҳ����Ҫ�ҵ���:\n");rewind(stdin);emm = 2;//emm  2��������   1�ҵ���
			}
			printf("%s %s\n", p->element.name, p->element.stunum);
		}
	}//if(emm==0) {print_no();}
		if (emm==2) {//��������
				printf("�����²���\n");rewind(stdin);
			}
}

void singlegrade_cnt(List *list,int classnum,char *object) {//ѧ����   ���㲢�����������
	node *p = list->head->next;
	node *obj = change(list, object);
	strcpy(object, obj->element.name);
	int cnt[Subject] = { 1,1,1,1,1,1 },cnt_evaluate=1, i;
	for (p;p;p = p->next) {
		if (p->element.classes == classnum) {//classnumΪfind_classnum
			for (i = 0;i < Subject;i++) {
				if (p->element.grade[i] > obj->element.grade[i]) {
					cnt[i]++;
				}
			}
		}
		if (p->element.evaluate > obj->element.evaluate)
			cnt_evaluate++;
	}//�������
	printf("%sͬѧ,%d���и����ɼ����ڵ�%d����Ӣ��ɼ���%d��,����ɼ���%d��,��ɢ�ɼ���%d��,C���Գɼ���%d��,�����ɼ���%d��,�ۺϳɼ�ȫ�꼶%d����Ҫ��������Ŷ  >v<\n",object,classnum,cnt[0], cnt[1], cnt[2], cnt[3], cnt[4], cnt[5], cnt_evaluate);
}

void grade_analyze(List *list, int classnum, int i) {//i ��ʾ��Ŀ
	if (i < 0 || i>5) { print_error(); }
	else {
		node *p = list->head->next;
		double classaver = 0, majoraver = 0;
		int class_cnt[2] = { 0 };// ���±�[0]����������   [1] ��߷�
		int major_max = 0;//���±� [0]��߷� 
		for (p;p;p = p->next) {
			if (p->element.classes == classnum||classnum==-1) {//ͳ�Ʊ���
				if (p->element.grade[i] < 60) {//����������
					class_cnt[0]++;
				}
				if (p->element.grade[i] > class_cnt[1]) {//��߷�
					class_cnt[1] = p->element.grade[i];
				}
				classaver += p->element.grade[i];
			}//ͳ��ȫרҵ
			if (p->element.grade[i] > major_max) {
				major_max = p->element.grade[i];
			}
			majoraver += p->element.grade[i];
		}//�ÿ�Ŀ�����������
		//����ƽ����
		classaver /= 30;
		majoraver /= STUNUM;
		if (classnum == -1) { classaver = majoraver; }
		printf("����%s�ɼ�%d�˲�������߷�Ϊ%d��ƽ����Ϊ%.2f��ȫרҵ��߷�%d��ƽ����%.2f��\n", SUBJECT[i], class_cnt[0], class_cnt[1], classaver, major_max, majoraver);
	}
}

void initialize_linklist(List *Class) {//��ʼ������
		node *p = (node *)malloc(sizeof(node));
		p->next = NULL;
		Class->head= Class->tail=p;
	}

void sort_stu(List *list,int i) {//��ѧ����������  0~5   subject�ɼ�   6�ۺ�����   7ѧ��˳��
	data tem;
	if (0 <= i&&i < 6) {
		for (int j = 1;j<STUNUM;j++)
		for (node *p = list->head->next;p->next;p = p->next) {
			if (p->element.grade[i] < p->next->element.grade[i]) {
				tem = p->element, p->element = p->next->element, p->next->element = tem;
			}
		}
	}
	else if (i==6) {//evaluate
		for (int j = 1;j<STUNUM;j++)
		for (node *p = list->head->next;p->next;p = p->next) {
			if (p->element.evaluate < p->next->element.evaluate) {
				tem = p->element, p->element = p->next->element, p->next->element = tem;
			}
		}
	}
	else if(i==7){
		for(int j=1;j<STUNUM;j++)
		for (node *p = list->head->next;p->next;p = p->next) {
			if (strcmp(p->element.stunum,p->next->element.stunum)>0) {
				tem = p->element, p->element = p->next->element, p->next->element = tem;
			}
		}
	}
	else {
		print_error();
	}
}
