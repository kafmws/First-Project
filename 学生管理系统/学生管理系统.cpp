// ѧ������ϵͳ.cpp: �������̨Ӧ�ó������ڵ㡣
//
#include "stdafx.h"
#include"statements.h"
 int condition=0 ; //0δ��¼��1ѧ���ˣ�2��ʦ�ˣ�3����Ա�ˣ�-2�����˳���
List Class;
 struct tm *time_tm;
 void initialize();
int main()
{ 
	initialize();
    return 0;
}
void initialize() {
	present[0] = '\0';
	import_account();
	initialize_linklist(&(Class));
	import_stu(&Class);
	show_sign();
	process_sign();
}
