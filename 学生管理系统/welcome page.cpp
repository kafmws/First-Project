#include"stdafx.h"
#include"statements.h"
//��ʾ����
void show_welcome() {
	    system("CLS");
		printf("\n\n");
		printf("     `;-.          ___,\n");
		printf("       `.`\\_...._/`.-\"`\n");
		printf("         \\        /      ,\n");
		printf("         /()   () \\    .' `-._\n");
		printf("        |)  .    ()\\  /   _.'\n");
		printf("        \\  -'-     ,; '. <\n");
		printf("         ;.__     ,;|   > \n");
		printf("        / ,    / ,  |.-'.-'\n");
		printf("       (_/    (_/ ,;|.<`\n");
		printf("         \\    ,     ;-`\n");
		printf("          >   \\    /\n");
		printf("         (_,-'`> .'\n");
		printf("              (_,' \n");
		printf("�ټ���˵��");
}
void show_sign() {//��¼����
	system("CLS");
	printf("		*******************************************\n");
	printf("				ѧ������ϵͳ\n");
	printf("		welcome�����¼\n");
	printf("				1.���ڵ�¼\n");
	printf("				2.ϵͳ����\n");
	printf("				3.ע���˺�\n");
	printf("				4.ͳ����Ϣ\n");
	printf("				0.�˳�ϵͳ\n\n");
	printf("						�汾��Ϊ����\n");
	printf("		*******************************************\n");
}

void show_stu() {//ѧ�����Ӳ˵�
	system("CLS");
	printf("		*********************************************\n");
	printf("		%sͬѧ,%s\n		����Ҫ��ʲô�أ�\n\n",present,greeting_get(1));
	printf("				1.�ɼ���ѯ	\n");
	printf("				2.�ǻ۽���\n");
	printf("				3.�����޸�\n");
	printf("				0.�˳�ϵͳ\n");
	printf("		*********************************************\n");
	rewind(stdin);
}

void show_teacher() {//��ʦ���Ӳ˵�
	system("CLS");
	printf("		*********************************************\n");
	printf("		%s��ʦ,%s\n		����Ҫ��ʲô�أ�\n\n", present,greeting_get(2));
	printf("				1.�ɼ���ѯ\n");
	printf("				2.ѧ�����\n");
	printf("				3.ѧ��ɾ��\n");
	printf("				4.�ɼ��޸�\n");
	printf("				5.�鿴����\n");
	printf("				6.�����޸�\n");
	printf("				0.�˳�ϵͳ\n");
	printf("		*********************************************\n");
	rewind(stdin);
}

void show_tergrade() {//��ʦ�˳ɼ���ѯ�Ӳ˵�
	system("CLS");
	printf("		*********************************************\n");
	printf("		Ҫѡ��һ���أ�\n");
	printf("				1.�����ֻ�ѧ�Ų�ѯ���˳ɼ�\n");
	printf("				2.�����ֻ�ѧ�ŷ������˳ɼ�\n");
	printf("				3.��ѯȫ��ĳ��Ŀ�ɼ�(�Ӹߵ���)\n");
	printf("				4.���۲��ӡȫ��ɼ�(�Ӹߵ���)\n");
	printf("				5.��ѧ��˳���ӡȫ��ɼ�\n");
	printf("				0.������һ��\n");
	printf("		*********************************************\n");
}

void show_admin() {//����Ա�Ӳ˵�
	system("CLS");
	printf("		*********************************************\n");
	printf("		%s,%s\n	\n", present, greeting_get(3));
	printf("				1.�˺����\n");
	printf("				2.�˺�ɾ��\n");
	printf("				3.�鿴�˺�\n");
	printf("				4.�����޸�\n");
	printf("		*********************************************\n");
}

void show_stugrade() {//ѧ���˳ɼ���ѯ�Ӳ˵�
	system("CLS");
	printf("		*********************************************\n");
	printf("		Ҫѡ��һ���أ�\n");
	printf("				1.�ҵĳɼ�\n");
	printf("				2.�ɼ�����\n");
	printf("				3.�ɼ�����\n");
	printf("				0.������һ��\n");
	printf("		*********************************************\n");
}


