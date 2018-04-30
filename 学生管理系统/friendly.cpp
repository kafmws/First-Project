#include"stdafx.h"
#include"statements.h"

char choice() {//界面选择
	char num[100];
	printf("请选择：\n");
	scanf("%s", num);//在switch-case里进行输入判断
	rewind(stdin);
	if (strlen(num) > 1) {
		return '9';
	}
	return num[0];
}

int judge() {//确认操作的判断
	int confirm=-1;
	printf("是否确认该操作 ? (1/0)\n");
	rewind(stdin);
	scanf("%d", &confirm);
	if (confirm != 1 && confirm != 0) {
		print_error();
		confirm = judge();
	}
	return confirm;
}

int warning() {//确认操作的警告
	int confirm=-1;
	printf("该操作不可恢复QAQ，是否继续 ?(1/0)\n");
	rewind(stdin);
	scanf("%d", &confirm);
	if (confirm != 1 && confirm != 0) {
		print_error();
		confirm=warning();
	}
	return confirm;
}

void print_changeok() {//提示操作成功
	printf("\n操作成功了的说！\n");rewind(stdin);
}

void print_no() {//报告无此项
	printf("抱歉，没有你要找的人的说（＞人＜；）\n");
	printf("请确认后再来\n");
	rewind(stdin);
}
void print_examinput() {
	printf("输入不符合要求，请重试的说╮（╯＿╰）╭\n");
	rewind(stdin);
}
void print_error() {//输入不合法
	printf("对不起，不明白要干什么的说(￣▽￣)\"\n");
	rewind(stdin);
}

void go_on() {
	printf("按任意键继续的说...\n");rewind(stdin);
	getch();
}

void print_blankhead() {
	printf("%-6s%6s      %6s    %-3s    %-3s    %-3s   %-3s    %-3s    %-3s\n", "姓名", "学号", "高数", "英语", "大物", "离散", "C语言", "体育","综合");
}

void print_re() {
	printf("发生奇怪错误的说qwq请联系开发者QQ740721665\n");rewind(stdin);
	go_on();
}

void print_timetable() {
	initialize_time();
	char *weekday = (char *)malloc(sizeof(char) * 6);
	switch (time_tm->tm_wday ) {
	case 1:strcpy(weekday, "一");break;
	case 2:strcpy(weekday, "二");break;
	case 3:strcpy(weekday, "三");break;
	case 4:strcpy(weekday, "四");break;
	case 5:strcpy(weekday, "五");break;
	case 6:strcpy(weekday, "六");break;
	case 7:strcpy(weekday, "日");break;
	default:
		print_re();
		break;
	}
	printf("现在是%d年%d月%d日  星期%s   %2d : %02d\n", time_tm->tm_year + 1900, time_tm->tm_mon + 1,time_tm->tm_mday,weekday,time_tm->tm_hour,time_tm->tm_min);
	printf("    第一节	    第二节	    第三节	    第四节\n");
}