#include "stdafx.h"
#include"statements.h"
extern List Class;
//extern char present[Name];
void  add(List *list) {//增加学生  
	data temp;
	stu_add(&temp);
	if (node *p=(node *)malloc(sizeof(node))) {
		p->next = NULL;
		p->element = temp;
		list->tail->next = p;
		list->tail = p;
		FILE *fp = fopen(".\\account_sign_up.txt","a+");
		fprintf(fp,"%s\t%s\t%s\t%s老师添加\n",p->element.name,p->element.stunum,"123456",present);
		fclose(fp);
		printf("已提醒管理员分配账号\n");rewind(stdin);
	}
	else {
		printf("十分抱歉，不能再添加更多学生了\n");
		print_re();
	}
}

//按或姓名学号查找name,stunum均为字符串
int kill(List *list, char *obj) {//删
	int re = 0;
	node *p, *dead = NULL;
	for (p = list->head;p->next;p = p->next) {
		if (strcmp(p->next->element.stunum, obj) == 0 || strcmp(p->next->element.name, obj) == 0) {
			if (find_classnum(&Class, p->next->element.name) == find_terclass(present)) {
				//通知管理员删除账号
				dead = p->next;
				FILE *fp = fopen(".\\account_sign_up.txt", "a+");
				fprintf(fp, "%s	%s	%s	%s老师删除", dead->element.name, dead->element.stunum, "  ", present);
				fclose(fp);
				p->next = dead->next;
				free(dead);
				re = 1;
				break;
			}
			else {
				printf("这个学生不是你班的呦\n");rewind(stdin);
			}
		}
	}
	return re;
}

//按或姓名学号查找    返回目标节点的指针
node * change(List *list, char *obj) {//改
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
		printf("选择你要更改的科目：\n");rewind(stdin);
		print_subject();
		char judge = choice();
		while (judge <'1'&&judge >'6') {
			print_error();
			printf("请重新选择\n");rewind(stdin);
			show_teacher();
			printf("选择你要更改的科目：\n");rewind(stdin);
			print_subject();
			judge = choice();
		}
		int tem, exam = 0, sum = 0;
		do {
			printf("请输入新的分数：\n");rewind(stdin);
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
		printf("这不是你班的学生呦\n");rewind(stdin);
	}
}

//遍历打印链表内容
void print_all(List *list) {//遍历输出所有成绩
	node *p = list->head->next;
	for (p;p;p = p->next) {
		printf("%s %s ", p->element.name, p->element.stunum);
		for (int i = 0;i < Subject;i++) {
			printf("%d ", p->element.grade[i]);
		}
		printf("\n");
	}
}

void print_class(List *list) {//遍历输出本班成绩
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
//查
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
		else if (strstr(p->element.name, obj) != NULL || strstr(p->element.stunum, obj) != NULL) {//输入不完整用strstr比较
			if (flaghead) {
				flaghead = 0;
				Sleep(500);printf("让我想想");Sleep(1500);printf(" 嗯   ");Sleep(1500);
				printf("也许你要找的是:\n");rewind(stdin);emm = 2;//emm  2有疑似项   1找到了
			}
			printf("%s %s\n", p->element.name, p->element.stunum);
		}
	}//if(emm==0) {print_no();}
		if (emm==2) {//有疑似项
				printf("请重新查找\n");rewind(stdin);
			}
}

void singlegrade_cnt(List *list,int classnum,char *object) {//学生端   计算并输出本班排名
	node *p = list->head->next;
	node *obj = change(list, object);
	strcpy(object, obj->element.name);
	int cnt[Subject] = { 1,1,1,1,1,1 },cnt_evaluate=1, i;
	for (p;p;p = p->next) {
		if (p->element.classes == classnum) {//classnum为find_classnum
			for (i = 0;i < Subject;i++) {
				if (p->element.grade[i] > obj->element.grade[i]) {
					cnt[i]++;
				}
			}
		}
		if (p->element.evaluate > obj->element.evaluate)
			cnt_evaluate++;
	}//计数完毕
	printf("%s同学,%d班中高数成绩排在第%d名，英语成绩第%d名,大物成绩第%d名,离散成绩第%d名,C语言成绩第%d名,体育成绩第%d名,综合成绩全年级%d名，要继续加油哦  >v<\n",object,classnum,cnt[0], cnt[1], cnt[2], cnt[3], cnt[4], cnt[5], cnt_evaluate);
}

void grade_analyze(List *list, int classnum, int i) {//i 表示科目
	if (i < 0 || i>5) { print_error(); }
	else {
		node *p = list->head->next;
		double classaver = 0, majoraver = 0;
		int class_cnt[2] = { 0 };// 列下标[0]不及格人数   [1] 最高分
		int major_max = 0;//列下标 [0]最高分 
		for (p;p;p = p->next) {
			if (p->element.classes == classnum||classnum==-1) {//统计本班
				if (p->element.grade[i] < 60) {//不及格人数
					class_cnt[0]++;
				}
				if (p->element.grade[i] > class_cnt[1]) {//最高分
					class_cnt[1] = p->element.grade[i];
				}
				classaver += p->element.grade[i];
			}//统计全专业
			if (p->element.grade[i] > major_max) {
				major_max = p->element.grade[i];
			}
			majoraver += p->element.grade[i];
		}//该科目分数遍历完毕
		//计算平均分
		classaver /= 30;
		majoraver /= STUNUM;
		if (classnum == -1) { classaver = majoraver; }
		printf("本班%s成绩%d人不及格，最高分为%d，平均分为%.2f，全专业最高分%d，平均分%.2f。\n", SUBJECT[i], class_cnt[0], class_cnt[1], classaver, major_max, majoraver);
	}
}

void initialize_linklist(List *Class) {//初始化链表
		node *p = (node *)malloc(sizeof(node));
		p->next = NULL;
		Class->head= Class->tail=p;
	}

void sort_stu(List *list,int i) {//对学生进行排序  0~5   subject成绩   6综合评价   7学号顺序
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
