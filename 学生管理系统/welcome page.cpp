#include"stdafx.h"
#include"statements.h"
//显示界面
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
		printf("再见的说！");
}
void show_sign() {//登录界面
	system("CLS");
	printf("		*******************************************\n");
	printf("				学生管理系统\n");
	printf("		welcome！请登录\n");
	printf("				1.现在登录\n");
	printf("				2.系统管理\n");
	printf("				3.注册账号\n");
	printf("				4.统计信息\n");
	printf("				0.退出系统\n\n");
	printf("						版本已为最新\n");
	printf("		*******************************************\n");
}

void show_stu() {//学生端子菜单
	system("CLS");
	printf("		*********************************************\n");
	printf("		%s同学,%s\n		你想要做什么呢？\n\n",present,greeting_get(1));
	printf("				1.成绩查询	\n");
	printf("				2.智慧教室\n");
	printf("				3.密码修改\n");
	printf("				0.退出系统\n");
	printf("		*********************************************\n");
	rewind(stdin);
}

void show_teacher() {//教师端子菜单
	system("CLS");
	printf("		*********************************************\n");
	printf("		%s老师,%s\n		您想要做什么呢？\n\n", present,greeting_get(2));
	printf("				1.成绩查询\n");
	printf("				2.学生添加\n");
	printf("				3.学生删除\n");
	printf("				4.成绩修改\n");
	printf("				5.查看申诉\n");
	printf("				6.密码修改\n");
	printf("				0.退出系统\n");
	printf("		*********************************************\n");
	rewind(stdin);
}

void show_tergrade() {//教师端成绩查询子菜单
	system("CLS");
	printf("		*********************************************\n");
	printf("		要选哪一个呢？\n");
	printf("				1.按名字或学号查询个人成绩\n");
	printf("				2.按名字或学号分析个人成绩\n");
	printf("				3.查询全班某科目成绩(从高到低)\n");
	printf("				4.按综测打印全班成绩(从高到低)\n");
	printf("				5.按学号顺序打印全班成绩\n");
	printf("				0.返回上一层\n");
	printf("		*********************************************\n");
}

void show_admin() {//管理员子菜单
	system("CLS");
	printf("		*********************************************\n");
	printf("		%s,%s\n	\n", present, greeting_get(3));
	printf("				1.账号添加\n");
	printf("				2.账号删除\n");
	printf("				3.查看账号\n");
	printf("				4.密码修改\n");
	printf("		*********************************************\n");
}

void show_stugrade() {//学生端成绩查询子菜单
	system("CLS");
	printf("		*********************************************\n");
	printf("		要选哪一个呢？\n");
	printf("				1.我的成绩\n");
	printf("				2.成绩分析\n");
	printf("				3.成绩申诉\n");
	printf("				0.返回上一层\n");
	printf("		*********************************************\n");
}


