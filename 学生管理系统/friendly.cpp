#include"stdafx.h"
#include"statements.h"

char choice() {//����ѡ��
	char num[100];
	printf("��ѡ��\n");
	scanf("%s", num);//��switch-case����������ж�
	rewind(stdin);
	if (strlen(num) > 1) {
		return 'z';
	}
	return num[0];
}

int judge() {//ȷ�ϲ������ж�
	int confirm=-1;
	printf("�Ƿ�ȷ�ϱ��β��� ? (1/0)\n");
	rewind(stdin);
	scanf("%d", &confirm);
	if (confirm != 1 && confirm != 0) {
		print_error();
		confirm = judge();
	}
	return confirm;
}

int warning() {//ȷ�ϲ����ľ���
	int confirm=-1;
	printf("�ò������ɻָ�QAQ���Ƿ���� ?(0/1)\n");
	rewind(stdin);
	scanf("%d", &confirm);
	if (confirm != 1 && confirm != 0) {
		print_error();
		confirm=warning();
	}
	return confirm;
}

void print_changeok() {//��ʾ�����ɹ�
	printf("�����ɹ��˵�˵��\n");rewind(stdin);
}

void print_no() {//�����޴���
	printf("��Ǹ��û����Ҫ�ҵ��˵�˵�����ˣ�����\n");
	//printf("��ȷ�Ϻ�����\n");
	rewind(stdin);
}

void print_examinput() {
	printf("���벻����Ҫ�������Ե�˵�r���s�ߨt���q\n");
	rewind(stdin);
}

void print_error() {//���벻�Ϸ�
	printf("�Բ��𣬲�����Ҫ��ʲô��˵(������)\"\n");
	rewind(stdin);
}

void go_on() {
	rewind(stdin);
	printf("�������������˵...\n");rewind(stdin);
	getch();
}

void print_blankhead() {
	printf("%-6s%6s      %6s    %-3s    %-3s    %-3s   %-3s    %-3s    %-3s\n", "����", "ѧ��", "����", "Ӣ��", "����", "��ɢ", "C����", "����","�ۺ�");
	rewind(stdin);
}

void print_re() {
	printf("������ִ����˵qwq����ϵ������QQ740721665\n");rewind(stdin);
	go_on();
}

void print_timetable() {
	initialize_time();
	char *weekday = (char *)malloc(sizeof(char) * 6);
	switch (time_tm->tm_wday ) {
	case 1:strcpy(weekday, "һ");break;
	case 2:strcpy(weekday, "��");break;
	case 3:strcpy(weekday, "��");break;
	case 4:strcpy(weekday, "��");break;
	case 5:strcpy(weekday, "��");break;
	case 6:strcpy(weekday, "��");break;
	case 7:strcpy(weekday, "��");break;
	default:
		print_re();
		break;
	}
	printf("������%d��%d��%d��  ����%s \n", time_tm->tm_year + 1900, time_tm->tm_mon + 1,time_tm->tm_mday,weekday);
	printf("      ��һ��	       �ڶ���	         ������	           ���Ľ�\n");
}

void print_subject() {//��ӡ��Ŀ����
	int i;
	for (i = 0;i < Subject;i++) {
		printf("%d.%s	", i + 1, SUBJECT[i]);
	}
	printf("\n");rewind(stdin);
}

int print_enquiry() {//ѯ���Ƿ�ɾ��
	printf("�Ƿ����������Ϣ��(0/1)\n");rewind(stdin);
	char judge = choice();
	while (judge != '1'&&judge != '0') {
		print_examinput();
		judge = choice();
	}
	return  judge - '0';
}