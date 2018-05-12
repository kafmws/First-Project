// 学生管理系统.cpp: 定义控制台应用程序的入口点。
//
#include "stdafx.h"
#include"statements.h"
 int condition=0 ; //0未登录，1学生端，2教师端，3管理员端，-2即将退出。
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
