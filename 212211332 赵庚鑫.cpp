#include <stdio.h>
#include <string.h>
#include <easyx.h>
#include <graphics.h>
#include <Windows.h>
#include <conio.h>
#include <stdlib.h>

struct account{
	char name[18];
	char password[18];
	int book_num;
	char book[6][30];
};//定义用户结构体

struct booklist{
	char name[30];
	char writer[30];
	char publish[30];
	int num;
	int maxnum;
	char FILE[20];
};//定义书单结构体

/*在指定位置输入文本，回车后复制入字符串*/
char* input(int x, int y, char str2[], int n,IMAGE a) {
	int i = 0;
	char str[20];
	while (true)
	{
		if (i < n-2 ) str[i++] = _getch();
		else str[i-1] = _getch();

		str[i] = '\0';
		if (str[i - 1] == '\b') {
			if (i > 1) i -= 2;
			else i -= 1;

			str[i] = ' ';
			str[i + 1] = '\0';
		}
		else if (str[i - 1] == '\r') {
			str[i - 1] = '\0';
			str[i]='\0';
			strcpy(str2, str);
			break;
		}
		putimage(x, y, &a);
		outtextxy(x, y, str);
		//putimage(0, 0, &a, SRCPAINT);
	}
}

/*在指定区域检测鼠标是否按下，按下则返回true*/
bool button(int x, int y, int w, int h,IMAGE a,IMAGE b,ExMessage mouse) {
	if (mouse.x >= x && mouse.x <= x + w && mouse.y >= y && mouse.y <= y + h) { //鼠标坐标在指定坐标内返回true，否则false
		putimage(x, y, &b);
		if (mouse.message == WM_LBUTTONDOWN) {	//如果按下左键就进行一次判断，否则返回false
			return true;
		}
		else return false;
	}
	else {
		putimage(x, y, &a);
		return false;
	}
}

/*单独作为借还书部分的按钮，当鼠标停在按钮区域内有返回值*/
int button2(int x, int y, int w, int h, IMAGE a, IMAGE b,ExMessage mouse) {
	if (mouse.x >= x && mouse.x <= x + w && mouse.y >= y && mouse.y <= y + h) { //鼠标坐标在指定坐标内返回1，否则0
		putimage(472, 60, &a);
		if (mouse.message == WM_LBUTTONDOWN) {	//按下左键返回2
			return 2;
		}
		else return 1;
	}
	else {
		putimage(x, y, &b);
		return 0;
	}
}

/*透明按钮*/
bool button3(int x, int y, int w, int h, IMAGE a, IMAGE b,ExMessage mouse) {
	if (mouse.x >= x && mouse.x <= x + w && mouse.y >= y && mouse.y <= y + h) { //鼠标坐标在指定坐标内返回true，否则false
		putimage(x, y, &b,SRCPAINT);//过滤黑色
		if (mouse.message == WM_LBUTTONDOWN) {	//如果按下左键就进行一次判断，否则返回false
			return true;
		}
	}
	else {
		putimage(x, y, &a, SRCAND);//过滤白色
		return false;
	}
}


/*主函数*/
int main() {
	IMAGE Load, Start, Borrow, Return, Loading, Load_finish, Button, Text, Button2, Back, Hudong, Hudong2, EnrollButton, EnrollButton2, Start_Text, OP1, OP2, OP;
	IMAGE LoginButton, LoginButton2, Y[8], left1, left2, right1, right2, out1, out2, Borrow1, Borrow2, Return1, Return2, out_save1, out_save2, Text3, Text4;
	IMAGE ADD1, ADD2, Book_Add1, Book_Add2, Book_Sub1, Book_Sub2, Book_FILE1, Book_FILE2, Book_Name1, Book_Name2, Book_Writer1, Book_Writer2, Book_Add;
	HWND window;
	ExMessage mouse;
	int return_book[6];

	window = initgraph(1280, 720);
	//初始化一个窗口

	loadimage(&Book_Sub2, "减2.png", 120, 120);
	loadimage(&Book_Sub1, "减1.png", 120, 120);
	loadimage(&Book_Add2, "加2.png", 120, 120);
	loadimage(&Book_Add1, "加1.png", 120, 120);
	loadimage(&Book_FILE1, "修改封面1.png", 240, 120);
	loadimage(&Book_FILE2, "修改封面2.png", 240, 120);
	loadimage(&Book_Name1, "修改书名1.png", 240, 120);
	loadimage(&Book_Name2, "修改书名2.png", 240, 120);
	loadimage(&Book_Writer1, "修改作者1.png", 240, 120);
	loadimage(&Book_Writer2, "修改作者2.png", 240, 120);
	loadimage(&Book_Add, "修改数量.png", 240, 120);
	loadimage(&ADD1, "添加书籍1.png", 240, 120);
	loadimage(&ADD2, "添加书籍2.png", 240, 120);
	loadimage(&OP, "管理员.png", 1280, 720);
	loadimage(&OP2, "管理员模式2.png", 240, 120);
	loadimage(&OP1, "管理员模式1.png", 240, 120);
	loadimage(&Text4, "文本框4.png", 240, 60);
	loadimage(&Text3, "文本框3.png", 240, 60);
	loadimage(&out_save1, "退出按钮1.png", 240, 120);
	loadimage(&out_save2, "退出按钮2.png", 240, 120);
	loadimage(&Borrow1, "借书按钮1.png", 240, 120);
	loadimage(&Borrow2, "借书按钮2.png", 240, 120);
	loadimage(&Return1, "还书按钮1.png", 240, 120);
	loadimage(&Return2, "还书按钮2.png", 240, 120);
	loadimage(&out1, "退出1.png", 128, 72);
	loadimage(&out2, "退出2.png", 128, 72);
	loadimage(&left1, "翻页待机左.png", 150, 16);
	loadimage(&left2, "向左翻.png", 150, 16);
	loadimage(&right1, "翻页待机右.png", 150, 16);
	loadimage(&right2, "向右翻.png", 150, 16);
	loadimage(&Text, "文本框.png", 200, 16);
	loadimage(&Start_Text, "开始背景文本框.png", 654, 301);
	loadimage(&Load, "load.png", 1280, 720);
	loadimage(&Start, "背景.png", 1280, 720);
	loadimage(&Borrow, "借书.png", 1280, 720);
	loadimage(&Return, "还书.png", 1280, 720);
	loadimage(&Loading, "Loading.png", 288, 64);
	loadimage(&Load_finish, "Load_finish.png", 288, 64);
	loadimage(&Button, "按钮.png", 240, 120);
	loadimage(&Button2, "按钮2.png", 240, 120);
	loadimage(&Back, "信息.png", 576, 324);
	loadimage(&Hudong, "互动.png", 240, 240);
	loadimage(&Hudong2, "互动2.png", 240, 240);
	loadimage(&EnrollButton, "注册按钮1.png", 240, 120);
	loadimage(&EnrollButton2, "注册按钮2.png", 240, 120);
	loadimage(&LoginButton, "登录按钮1.png", 240, 120);
	loadimage(&LoginButton2, "登录按钮2.png", 240, 120);
	//初始化资源

	settextcolor(BLACK);
	setbkmode(TRANSPARENT);
	//设置字体背景为透明
	//设置字体颜色为黑

	//输出图片,开始初始化

	bool f/*用于执行while循环*/, op = false/*当前用户是否为管理员*/, login = false/*系统是否处于登录状态*/,del=false;

	int point = -1/*指向当前用户*/, book_point = -1/*指向正在操作的书*/, flag = 1/*用于界面的切换*/, i = 0, j = 0, j2 = 0/*次数指针*/, user_num = 0/*记录用户数量*/, book_num = 0/*记录书的数量*/;

	FILE* p/*指向用户文件*/, * q/*指向书单文件*/;

	char str[20]/*临时存放字符串*/, str_null[20] = "\0"/*用于清空临时存放的字符串*/, pas[5] = "1234"/*管理员密码*/;

	account user[20], * user_p;
	booklist* book_q, book[40];
	user_p = user;
	book_q = book;
	//初始化用户和书单

	/*用户初始化*/
	if ((p = fopen("account_list.txt", "r")) == NULL) {
		p = fopen("account_list.txt", "w");
		fclose(p);
	}
	else {
		for (i = 0; i < 20; i++) {
			if (fread(user + i, sizeof(struct account), 1, p) == 0) {
				break;
			}
			user_num = i + 1;
		}
		fclose(p);
	}

	/*书单初始化*/
	if ((q = fopen("book_list.txt", "r")) == NULL) {
		q = fopen("book_list.txt", "w");
		booklist book2[4] =
		{ "《切·格瓦拉传》", "乔恩·李·安德森" ,"未知",2,2,"切格瓦拉.png","《我们的故事》","Zhao","Aila",2,2,"我们的故事.png","《樱之刻》","枕社","无",2,2,"樱之刻.png","《樱之诗》","枕社","无",2,2,"樱之诗.png" };
		book[0] = book2[0]; book[1] = book2[1]; book[2] = book2[2]; book[3] = book2[3];
		book_num = 4;
		fwrite(book, sizeof(struct booklist), book_num, q);
		fclose(q);
	}
	else {
		for (i = 0; i < 40; i++) {
			if (fread(book + i, sizeof(struct booklist), 1, q) == 0) {
				break;
			}
			book_num = i + 1;
		}
		fclose(q);
	}

xunhuan:
	/*开始界面*/
	if (flag == 1) {
		cleardevice();
		putimage(0, 0, &Start);
		 //outtextxy(300, 0, user[0].name); 
	xunhuan1:

		mouse = getmessage(EX_MOUSE);//初始化变量，变量mouse只获取鼠标消息
		if (button3(0, 0, 240, 120, EnrollButton, EnrollButton2, mouse) == true) {
			flag = 2;
		}
		if (button3(0, 120, 240, 120, LoginButton, LoginButton2, mouse) == true) {
			flag = 3;
		}
		if (button3(0, 240, 240, 120, Borrow1, Borrow2, mouse) == true) {
			flag = 4;
		}
		if (button3(0, 360, 240, 120, Return1, Return2, mouse) == true) {
			flag = 5;
		}
		if (button(0, 480, 240, 240, Hudong, Hudong2, mouse) == true) {
			flag = 6;
		}
		if (button3(1024, 0, 240, 120, OP1, OP2, mouse) == true) {
			flag = 7;
		}
		if ((button3(1024, 576, 128, 72, out_save1, out_save2, mouse)) == true) {
			flag = 0;
			goto xunhuan;
		}
		if (flag == 1) goto xunhuan1;
		else goto xunhuan;//脱离循环
	}//开始界面

	/*注册*/
	else if (flag == 2) {
		strcpy(str, str_null);
		if (user_num == 20) {
			putimage(382, 164, &Text);
			outtextxy(382, 164, "用户已满，按任意键退出");
			flag = 1;
			system("pause");
			goto xunhuan;
		}
		f = true;
		/*用户输入数据*/
		while (f) {
			strcpy(str, str_null);
			outtextxy(432, 60, "请输入用户名(仅支持英文和数字)");
			input(382, 86, str, 20, Text);
			if (strlen(str) == 0) {
				MessageBox(window, "用户名不能为空，请重新输入", "至诚图书管理系统", MB_OK);
				continue;
			}
			for (i = 0; i < user_num; i++) {
				if (strcmp(str, user[i].name) == 0) {
					MessageBox(window, "用户名重复，请重新输入", "至诚图书管理系统", MB_OK);
					break;
				}
			}
			/*存入数据，离开循环*/
			if (i == user_num) {
				f = false;
				strcpy(user[user_num].name, str);
				outtextxy(432, 112, "请输入密码(仅支持英文和数字)");
			}
		}
		strcpy(str, str_null);
	error:
		input(382, 138, str, 20, Text);
		if (strlen(str) == 0) {
			MessageBox(window, "密码不能为空，请重新输入", "至诚图书管理系统", MB_OK);
			goto error;
		}
		//user[user_num].book_num = 0;
		strcpy(user[user_num++].password, str);
		flag = 1;
		MessageBox(window, "注册完成", "至诚图书管理系统", MB_OK);
		user[user_num - 1].book_num = 0;
		goto xunhuan;
	}

	/*登录*/
	else if (flag == 3) {
		j = 0;
		login = false;
		if (user_num == 0) {
			MessageBox(window, "系统内没有用户，请先注册", "至诚图书管理系统", MB_OK);
			flag = 1;
			goto xunhuan;
		}
		f = true;
		while (f) {
			outtextxy(432, 60, "请输入用户名");
			putimage(382, 86, &Text);
			strcpy(str, str_null);
			input(382, 86, str, 20, Text);
			for (i = 0; i < user_num; i++) {
				if (strcmp(user[i].name, str) == 0) {
					point = i;
					break;
				}
			}
			if (i == user_num) {
				MessageBox(window, "用户名错误", "至诚图书管理系统", MB_OK);
				j++;
				if (j < 5) continue;
				else {
					MessageBox(window, "错误次数达到上限，退出登录", "至诚图书管理系统", MB_OK);
					flag = 1;
					goto xunhuan;
				}
			}
			strcpy(str, str_null);
			outtextxy(432, 112, "请输入密码");
			j2 = 0;
			input(382, 138, str, 20, Text);
			if (strcmp(str, user[point].password) == 0) {
				MessageBox(window, "登录成功", "至诚图书管理系统", MB_OK);
				login = true;
				op = false;
				flag = 1;
				goto xunhuan;
			}
			else {
				MessageBox(window, "密码错误", "至诚图书管理系统", MB_OK);
				j2++;
				if (j2 < 5) continue;
				else {
					MessageBox(window, "错误次数达到上限，退出登录", "至诚图书管理系统", MB_OK);
					flag = 1;
					goto xunhuan;
				}
			}
		}
	}//登录

	/*借书*/
	else if (flag == 4) {
		if (login == false) {
			MessageBox(window, "请先登录", "至诚图书管理系统", MB_OK);
			flag = 1;
			goto xunhuan;
		}
		/*清空指针，将其作为页数指针*/
		i = 0;

	jieshu:
		if (user[point].book_num == 6) {
			MessageBox(window, "借书数量达到上限", "至诚图书管理系统", MB_OK);
			flag = 1;
			goto xunhuan;
		}
		cleardevice();
		putimage(0, 0, &Borrow);
		f = true;

		/*打印书单*/
		for (j = 0; j < 4; j++) {
			if (book[i * 4 + j].num == 0) continue;
			if (i * 4 + j >= book_num) break;
			outtextxy(0, (j * 144), book[i * 4 + j].name);
			outtextxy(200, (j * 144), book[i * 4 + j].num+'0');
			outtextxy(200, (j * 144)+60, book[i * 4 + j].writer);
			loadimage(&Y[j * 2], book[i * 4 + j].FILE, 576, 324);
			loadimage(&Y[j * 2 + 1], book[i * 4 + j].FILE, 177, 100);
		}
		outtextxy(0, 576, "翻页在下面！！！！！！！！！");

		/*操作区*/
		while (f) {
			mouse = getmessage(EX_MOUSE);
			if (book[i * 4].num > 0) {
				if ((button2(16, 16, 177, 100, Y[0], Y[1], mouse)) == 2) {
					book[i * 4].num--;
					strcpy(user[point].book[user[point].book_num++], book[i * 4].name);
					MessageBox(window, "借书成功", "至诚图书管理系统", MB_OK);
					goto jieshu;
				}
			}
			if (book[i * 4 + 1].num > 0) {
				if ((button2(16, 160, 177, 100, Y[2], Y[3], mouse)) == 2) {
					book[i * 4 + 1].num--;
					strcpy(user[point].book[user[point].book_num++], book[i * 4 + 1].name);
					MessageBox(window, "借书成功", "至诚图书管理系统", MB_OK);
					goto jieshu;
				}
			}
			if (book[i * 4 + 2].num > 0) {
				if ((button2(16, 304, 177, 100, Y[4], Y[5], mouse)) == 2) {
					book[i * 4 + 2].num--;
					strcpy(user[point].book[user[point].book_num++], book[i * 4 + 2].name);
					MessageBox(window, "借书成功", "至诚图书管理系统", MB_OK);
					goto jieshu;
				}
			}
			if (book[i * 4 + 3].num > 0) {
				if ((button2(16, 448, 177, 100, Y[6], Y[7], mouse)) == 2) {
					book[i * 4 + 3].num--;
					strcpy(user[point].book[user[point].book_num++], book[i * 4 + 3].name);
					MessageBox(window, "借书成功", "至诚图书管理系统", MB_OK);
					goto jieshu;
				}
			}
			if ((button3(1024, 576, 128, 72, out1, out2, mouse)) == true) {
				flag = 1;
				goto xunhuan;
			}

			/*翻页*/
			if ((button3(150, 704, 150, 16, right1, right2, mouse)) == true) {
				if ((i * 4 + j) < book_num)
				{
					i++;
					goto jieshu;
				}
				else {
					MessageBox(window, "当前已经是最后一页了，试试加一本书吧", "至诚图书管理系统", MB_OK);
					goto jieshu;
				}
			}
			if ((button3(0, 704, 150, 16, left1, left2, mouse)) == true) {
				if (i > 0)
				{
					i--;
					goto jieshu;
				}
				else {
					MessageBox(window, "当前已经是第一页了", "至诚图书管理系统", MB_OK);
					goto jieshu;
				}
			}
		}
	}

	/*还书*/
	else if (flag == 5) {
		if (login == false) {
			MessageBox(window, "请先登录", "至诚图书管理系统", MB_OK);
			flag = 1;
			goto xunhuan;
		}
	huanshu:
		cleardevice();
		putimage(0, 0, &Return);
		i = 0;
		outtextxy(432, 0, "点击书名将自动归还书本：");
		for (i = 0; i < user[point].book_num; i++) {
			outtextxy(464, 60 * (i + 1)+10, user[point].book[i]);
			return_book[i] = i;
		}
		while (f) {
			mouse = getmessage(EX_MOUSE);
			if ((button3(1024, 576, 128, 72, out1, out2, mouse)) == true) {
				flag = 1;
				goto xunhuan;
			}
			for (i = 0; i < user[point].book_num; i++) {
				if ((button3(432, 60 * (i + 1) - 7, 240, 60, Text3, Text4, mouse)) == true) {
					for (j = 0; j < book_num; j++) {
						if (strcmp(user[point].book[i], book[j].name) == 0) {
							book[j].num++;
							break;
						}
					}
					for (j = i; j < user[point].book_num - 1; j++) {
						strcpy(user[point].book[j], user[point].book[j + 1]);
					}
					user[point].book_num--;
					goto huanshu;
				}
			}
		}
		system("pause");
	}

	/*互动界面*/
	else if (flag == 6) {

	}

	/*管理员界面*/
	else if (flag == 7) {
		if (login == false) {
			MessageBox(window, "请先登录", "至诚图书管理系统", MB_OK);
			flag = 1;
			goto xunhuan;
		}
		if (op == false) {
			MessageBox(window, "请输入管理员密码(1234)", "至诚图书管理系统", MB_OK);
			strcpy(str, str_null);
			putimage(382, 86, &Text);
			input(382, 86, str, 20, Text);
			if (strcmp(str, pas) == 0) {
				op = true;
			}
			else {
				flag = 1;
				MessageBox(window, "密码错误", "至诚图书管理系统", MB_OK);
				goto xunhuan;
			}
		}
	OP:
		putimage(0, 0, &OP);
		outtextxy(432, 0, "选择您要操作的书籍:");
		f = true;
		/*选择操作模式*/
		while (f) {
			mouse = getmessage(EX_MOUSE);
			if ((button3(1024, 576, 128, 72, out1, out2, mouse)) == true) {
				flag = 1;
				goto xunhuan;
			}
			for (i = 0; i < book_num; i++) {
				outtextxy(464, 60 * (i + 1), book[i].name);
				outtextxy(704, 60 * (i + 1), book[i].num+'0');
				outtextxy(768, 60 * (i + 1), book[i].writer);
				if ((button3(432, 60 * (i + 1) - 17, 240, 60, Text3, Text4, mouse)) == true) {
					book_point = i;
					flag = 2;
					del = false;
					f = false;
					break;
				}
			}
			if ((button3(1024, 0, 240, 120, ADD1, ADD2, mouse)) == true) {
				flag = 3;
				break;
			}
		}

		/*添加书籍*/
		if (flag == 3) {
			outtextxy(0, 0, "请输入书名（仅支持英文和数字)");
			strcpy(str, str_null);
			while (f) {
				input(0, 32, str, 20, Text);
				if (strlen(str) == 0) {
					MessageBox(window, "书名不能为空，请重新输入", "至诚图书管理系统", MB_OK);
					continue;
				}
				else break;
			}
			strcpy(book[book_num].name, str);
			outtextxy(0, 64, "请输入封面文件名（仅支持英文和数字,包括后缀名)");
			strcpy(str, str_null);
			while (f) {
				input(0, 96, str, 20, Text);
				if (strlen(str) == 0) {
					MessageBox(window, "文件名不能为空，请重新输入", "至诚图书管理系统", MB_OK);
					continue;
				}
				else break;
			}
			strcpy(book[book_num].FILE, str);
			outtextxy(0, 128, "请输入作者（仅支持英文和数字)");
			strcpy(str, str_null);
			while (f) {
				input(0, 160, str, 20, Text);
				if (strlen(str) == 0) {
					MessageBox(window, "作者不能为空，请重新输入", "至诚图书管理系统", MB_OK);
					continue;
				}
				else break;
			}
			strcpy(book[book_num].writer, str);
			book[book_num].num = 1;
			book[book_num++].maxnum = 1;
			MessageBox(window, "数据入库成功", "至诚图书管理系统", MB_OK);
			goto OP;
		}

		/*操作某本书*/
		if (flag == 2) {
			f = true;
			putimage(0, 360, &Book_Add, SRCAND);
			while (f) {
				mouse = getmessage(EX_MOUSE);
				if ((button3(0, 0, 240, 120, Book_Name1, Book_Name2, mouse)) == true) {
					putimage(240, 60, &Text);
					strcpy(str, str_null);
					while (f) {
						input(0, 32, str, 20, Text);
						if (strlen(str) == 0) {
							MessageBox(window, "书名不能为空，请重新输入", "至诚图书管理系统", MB_OK);
							continue;
						}
						else break;
					}
					strcpy(book[book_point].name, str);
					goto OP;
				}
				if ((button3(0, 120, 240, 120, Book_FILE1, Book_FILE2, mouse)) == true) {
					putimage(240, 180, &Text);
					strcpy(str, str_null);
					while (f) {
						input(0, 32, str, 20, Text);
						if (strlen(str) == 0) {
							MessageBox(window, "文件名不能为空，请重新输入", "至诚图书管理系统", MB_OK);
							continue;
						}
						else break;
					}
					strcpy(book[book_point].FILE, str);
					goto OP;
				}
				if ((button3(0, 240, 240, 120, Book_Writer1, Book_Writer2, mouse)) == true) {
					putimage(240, 300, &Text);
					strcpy(str, str_null);
					while (f) {
						input(0, 32, str, 20, Text);
						if (strlen(str) == 0) {
							MessageBox(window, "作者不能为空，请重新输入", "至诚图书管理系统", MB_OK);
							continue;
						}
						else break;
					}
					strcpy(book[book_point].writer, str);
					goto OP;
				}
				if ((button3(0, 480, 120, 120, Book_Add1, Book_Add2, mouse)) == true) {
					book[book_point].num++;
					book[book_point].maxnum++;
					MessageBox(window, "成功添加了一本书", "至诚图书管理系统", MB_OK);
					goto OP;
				}
				if ((button3(120, 480, 120, 120, Book_Sub1, Book_Sub2, mouse)) == true) {
					if (book[book_point].num > 0) {
						book[book_point].maxnum--;
						book[book_point].num--;
						MessageBox(window, "成功删除了一本书", "至诚图书管理系统", MB_OK);
						goto OP;
					}
					else if (book[book_point].num == 0&& book[book_point].maxnum!=0) {
						MessageBox(window, "馆内已经没有这本书了，但有用户借走了", "至诚图书管理系统", MB_OK);
						goto OP;
					}
					else if (book[book_point].maxnum == 0&&del==false) {
						MessageBox(window, "馆内已经没有这本书了，并且没有用户借走，再次点击执行删除", "至诚图书管理系统", MB_OK);
						del = true;
					}
					else if (del = true) {
						for (int j = book_point; j < book_num - 1; j++) {
							book[j] = book[j + 1];
						}
						book_num--;
						goto OP;
					}
				}
				if ((button3(60, 600, 128, 72, out1, out2, mouse)) == true) {
					goto OP;
				}
			}
		}
	}
		/*退出*/
		else if (flag == 0) {
			p = fopen("account_list.txt", "w");
			fwrite(user, sizeof(struct account), user_num, p);
			fclose(p);

			q = fopen("book_list.txt", "w");
			fwrite(book, sizeof(struct booklist), book_num, q);
			fclose(q);
		}
}