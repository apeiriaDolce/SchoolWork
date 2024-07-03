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
};//�����û��ṹ��

struct booklist{
	char name[30];
	char writer[30];
	char publish[30];
	int num;
	int maxnum;
	char FILE[20];
};//�����鵥�ṹ��

/*��ָ��λ�������ı����س��������ַ���*/
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

/*��ָ������������Ƿ��£������򷵻�true*/
bool button(int x, int y, int w, int h,IMAGE a,IMAGE b,ExMessage mouse) {
	if (mouse.x >= x && mouse.x <= x + w && mouse.y >= y && mouse.y <= y + h) { //���������ָ�������ڷ���true������false
		putimage(x, y, &b);
		if (mouse.message == WM_LBUTTONDOWN) {	//�����������ͽ���һ���жϣ����򷵻�false
			return true;
		}
		else return false;
	}
	else {
		putimage(x, y, &a);
		return false;
	}
}

/*������Ϊ�軹�鲿�ֵİ�ť�������ͣ�ڰ�ť�������з���ֵ*/
int button2(int x, int y, int w, int h, IMAGE a, IMAGE b,ExMessage mouse) {
	if (mouse.x >= x && mouse.x <= x + w && mouse.y >= y && mouse.y <= y + h) { //���������ָ�������ڷ���1������0
		putimage(472, 60, &a);
		if (mouse.message == WM_LBUTTONDOWN) {	//�����������2
			return 2;
		}
		else return 1;
	}
	else {
		putimage(x, y, &b);
		return 0;
	}
}

/*͸����ť*/
bool button3(int x, int y, int w, int h, IMAGE a, IMAGE b,ExMessage mouse) {
	if (mouse.x >= x && mouse.x <= x + w && mouse.y >= y && mouse.y <= y + h) { //���������ָ�������ڷ���true������false
		putimage(x, y, &b,SRCPAINT);//���˺�ɫ
		if (mouse.message == WM_LBUTTONDOWN) {	//�����������ͽ���һ���жϣ����򷵻�false
			return true;
		}
	}
	else {
		putimage(x, y, &a, SRCAND);//���˰�ɫ
		return false;
	}
}


/*������*/
int main() {
	IMAGE Load, Start, Borrow, Return, Loading, Load_finish, Button, Text, Button2, Back, Hudong, Hudong2, EnrollButton, EnrollButton2, Start_Text, OP1, OP2, OP;
	IMAGE LoginButton, LoginButton2, Y[8], left1, left2, right1, right2, out1, out2, Borrow1, Borrow2, Return1, Return2, out_save1, out_save2, Text3, Text4;
	IMAGE ADD1, ADD2, Book_Add1, Book_Add2, Book_Sub1, Book_Sub2, Book_FILE1, Book_FILE2, Book_Name1, Book_Name2, Book_Writer1, Book_Writer2, Book_Add;
	HWND window;
	ExMessage mouse;
	int return_book[6];

	window = initgraph(1280, 720);
	//��ʼ��һ������

	loadimage(&Book_Sub2, "��2.png", 120, 120);
	loadimage(&Book_Sub1, "��1.png", 120, 120);
	loadimage(&Book_Add2, "��2.png", 120, 120);
	loadimage(&Book_Add1, "��1.png", 120, 120);
	loadimage(&Book_FILE1, "�޸ķ���1.png", 240, 120);
	loadimage(&Book_FILE2, "�޸ķ���2.png", 240, 120);
	loadimage(&Book_Name1, "�޸�����1.png", 240, 120);
	loadimage(&Book_Name2, "�޸�����2.png", 240, 120);
	loadimage(&Book_Writer1, "�޸�����1.png", 240, 120);
	loadimage(&Book_Writer2, "�޸�����2.png", 240, 120);
	loadimage(&Book_Add, "�޸�����.png", 240, 120);
	loadimage(&ADD1, "����鼮1.png", 240, 120);
	loadimage(&ADD2, "����鼮2.png", 240, 120);
	loadimage(&OP, "����Ա.png", 1280, 720);
	loadimage(&OP2, "����Աģʽ2.png", 240, 120);
	loadimage(&OP1, "����Աģʽ1.png", 240, 120);
	loadimage(&Text4, "�ı���4.png", 240, 60);
	loadimage(&Text3, "�ı���3.png", 240, 60);
	loadimage(&out_save1, "�˳���ť1.png", 240, 120);
	loadimage(&out_save2, "�˳���ť2.png", 240, 120);
	loadimage(&Borrow1, "���鰴ť1.png", 240, 120);
	loadimage(&Borrow2, "���鰴ť2.png", 240, 120);
	loadimage(&Return1, "���鰴ť1.png", 240, 120);
	loadimage(&Return2, "���鰴ť2.png", 240, 120);
	loadimage(&out1, "�˳�1.png", 128, 72);
	loadimage(&out2, "�˳�2.png", 128, 72);
	loadimage(&left1, "��ҳ������.png", 150, 16);
	loadimage(&left2, "����.png", 150, 16);
	loadimage(&right1, "��ҳ������.png", 150, 16);
	loadimage(&right2, "���ҷ�.png", 150, 16);
	loadimage(&Text, "�ı���.png", 200, 16);
	loadimage(&Start_Text, "��ʼ�����ı���.png", 654, 301);
	loadimage(&Load, "load.png", 1280, 720);
	loadimage(&Start, "����.png", 1280, 720);
	loadimage(&Borrow, "����.png", 1280, 720);
	loadimage(&Return, "����.png", 1280, 720);
	loadimage(&Loading, "Loading.png", 288, 64);
	loadimage(&Load_finish, "Load_finish.png", 288, 64);
	loadimage(&Button, "��ť.png", 240, 120);
	loadimage(&Button2, "��ť2.png", 240, 120);
	loadimage(&Back, "��Ϣ.png", 576, 324);
	loadimage(&Hudong, "����.png", 240, 240);
	loadimage(&Hudong2, "����2.png", 240, 240);
	loadimage(&EnrollButton, "ע�ᰴť1.png", 240, 120);
	loadimage(&EnrollButton2, "ע�ᰴť2.png", 240, 120);
	loadimage(&LoginButton, "��¼��ť1.png", 240, 120);
	loadimage(&LoginButton2, "��¼��ť2.png", 240, 120);
	//��ʼ����Դ

	settextcolor(BLACK);
	setbkmode(TRANSPARENT);
	//�������屳��Ϊ͸��
	//����������ɫΪ��

	//���ͼƬ,��ʼ��ʼ��

	bool f/*����ִ��whileѭ��*/, op = false/*��ǰ�û��Ƿ�Ϊ����Ա*/, login = false/*ϵͳ�Ƿ��ڵ�¼״̬*/,del=false;

	int point = -1/*ָ��ǰ�û�*/, book_point = -1/*ָ�����ڲ�������*/, flag = 1/*���ڽ�����л�*/, i = 0, j = 0, j2 = 0/*����ָ��*/, user_num = 0/*��¼�û�����*/, book_num = 0/*��¼�������*/;

	FILE* p/*ָ���û��ļ�*/, * q/*ָ���鵥�ļ�*/;

	char str[20]/*��ʱ����ַ���*/, str_null[20] = "\0"/*���������ʱ��ŵ��ַ���*/, pas[5] = "1234"/*����Ա����*/;

	account user[20], * user_p;
	booklist* book_q, book[40];
	user_p = user;
	book_q = book;
	//��ʼ���û����鵥

	/*�û���ʼ��*/
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

	/*�鵥��ʼ��*/
	if ((q = fopen("book_list.txt", "r")) == NULL) {
		q = fopen("book_list.txt", "w");
		booklist book2[4] =
		{ "���С�����������", "�Ƕ��������ɭ" ,"δ֪",2,2,"�и�����.png","�����ǵĹ��¡�","Zhao","Aila",2,2,"���ǵĹ���.png","��ӣ֮�̡�","����","��",2,2,"ӣ֮��.png","��ӣ֮ʫ��","����","��",2,2,"ӣ֮ʫ.png" };
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
	/*��ʼ����*/
	if (flag == 1) {
		cleardevice();
		putimage(0, 0, &Start);
		 //outtextxy(300, 0, user[0].name); 
	xunhuan1:

		mouse = getmessage(EX_MOUSE);//��ʼ������������mouseֻ��ȡ�����Ϣ
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
		else goto xunhuan;//����ѭ��
	}//��ʼ����

	/*ע��*/
	else if (flag == 2) {
		strcpy(str, str_null);
		if (user_num == 20) {
			putimage(382, 164, &Text);
			outtextxy(382, 164, "�û���������������˳�");
			flag = 1;
			system("pause");
			goto xunhuan;
		}
		f = true;
		/*�û���������*/
		while (f) {
			strcpy(str, str_null);
			outtextxy(432, 60, "�������û���(��֧��Ӣ�ĺ�����)");
			input(382, 86, str, 20, Text);
			if (strlen(str) == 0) {
				MessageBox(window, "�û�������Ϊ�գ�����������", "����ͼ�����ϵͳ", MB_OK);
				continue;
			}
			for (i = 0; i < user_num; i++) {
				if (strcmp(str, user[i].name) == 0) {
					MessageBox(window, "�û����ظ�������������", "����ͼ�����ϵͳ", MB_OK);
					break;
				}
			}
			/*�������ݣ��뿪ѭ��*/
			if (i == user_num) {
				f = false;
				strcpy(user[user_num].name, str);
				outtextxy(432, 112, "����������(��֧��Ӣ�ĺ�����)");
			}
		}
		strcpy(str, str_null);
	error:
		input(382, 138, str, 20, Text);
		if (strlen(str) == 0) {
			MessageBox(window, "���벻��Ϊ�գ�����������", "����ͼ�����ϵͳ", MB_OK);
			goto error;
		}
		//user[user_num].book_num = 0;
		strcpy(user[user_num++].password, str);
		flag = 1;
		MessageBox(window, "ע�����", "����ͼ�����ϵͳ", MB_OK);
		user[user_num - 1].book_num = 0;
		goto xunhuan;
	}

	/*��¼*/
	else if (flag == 3) {
		j = 0;
		login = false;
		if (user_num == 0) {
			MessageBox(window, "ϵͳ��û���û�������ע��", "����ͼ�����ϵͳ", MB_OK);
			flag = 1;
			goto xunhuan;
		}
		f = true;
		while (f) {
			outtextxy(432, 60, "�������û���");
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
				MessageBox(window, "�û�������", "����ͼ�����ϵͳ", MB_OK);
				j++;
				if (j < 5) continue;
				else {
					MessageBox(window, "��������ﵽ���ޣ��˳���¼", "����ͼ�����ϵͳ", MB_OK);
					flag = 1;
					goto xunhuan;
				}
			}
			strcpy(str, str_null);
			outtextxy(432, 112, "����������");
			j2 = 0;
			input(382, 138, str, 20, Text);
			if (strcmp(str, user[point].password) == 0) {
				MessageBox(window, "��¼�ɹ�", "����ͼ�����ϵͳ", MB_OK);
				login = true;
				op = false;
				flag = 1;
				goto xunhuan;
			}
			else {
				MessageBox(window, "�������", "����ͼ�����ϵͳ", MB_OK);
				j2++;
				if (j2 < 5) continue;
				else {
					MessageBox(window, "��������ﵽ���ޣ��˳���¼", "����ͼ�����ϵͳ", MB_OK);
					flag = 1;
					goto xunhuan;
				}
			}
		}
	}//��¼

	/*����*/
	else if (flag == 4) {
		if (login == false) {
			MessageBox(window, "���ȵ�¼", "����ͼ�����ϵͳ", MB_OK);
			flag = 1;
			goto xunhuan;
		}
		/*���ָ�룬������Ϊҳ��ָ��*/
		i = 0;

	jieshu:
		if (user[point].book_num == 6) {
			MessageBox(window, "���������ﵽ����", "����ͼ�����ϵͳ", MB_OK);
			flag = 1;
			goto xunhuan;
		}
		cleardevice();
		putimage(0, 0, &Borrow);
		f = true;

		/*��ӡ�鵥*/
		for (j = 0; j < 4; j++) {
			if (book[i * 4 + j].num == 0) continue;
			if (i * 4 + j >= book_num) break;
			outtextxy(0, (j * 144), book[i * 4 + j].name);
			outtextxy(200, (j * 144), book[i * 4 + j].num+'0');
			outtextxy(200, (j * 144)+60, book[i * 4 + j].writer);
			loadimage(&Y[j * 2], book[i * 4 + j].FILE, 576, 324);
			loadimage(&Y[j * 2 + 1], book[i * 4 + j].FILE, 177, 100);
		}
		outtextxy(0, 576, "��ҳ�����棡����������������");

		/*������*/
		while (f) {
			mouse = getmessage(EX_MOUSE);
			if (book[i * 4].num > 0) {
				if ((button2(16, 16, 177, 100, Y[0], Y[1], mouse)) == 2) {
					book[i * 4].num--;
					strcpy(user[point].book[user[point].book_num++], book[i * 4].name);
					MessageBox(window, "����ɹ�", "����ͼ�����ϵͳ", MB_OK);
					goto jieshu;
				}
			}
			if (book[i * 4 + 1].num > 0) {
				if ((button2(16, 160, 177, 100, Y[2], Y[3], mouse)) == 2) {
					book[i * 4 + 1].num--;
					strcpy(user[point].book[user[point].book_num++], book[i * 4 + 1].name);
					MessageBox(window, "����ɹ�", "����ͼ�����ϵͳ", MB_OK);
					goto jieshu;
				}
			}
			if (book[i * 4 + 2].num > 0) {
				if ((button2(16, 304, 177, 100, Y[4], Y[5], mouse)) == 2) {
					book[i * 4 + 2].num--;
					strcpy(user[point].book[user[point].book_num++], book[i * 4 + 2].name);
					MessageBox(window, "����ɹ�", "����ͼ�����ϵͳ", MB_OK);
					goto jieshu;
				}
			}
			if (book[i * 4 + 3].num > 0) {
				if ((button2(16, 448, 177, 100, Y[6], Y[7], mouse)) == 2) {
					book[i * 4 + 3].num--;
					strcpy(user[point].book[user[point].book_num++], book[i * 4 + 3].name);
					MessageBox(window, "����ɹ�", "����ͼ�����ϵͳ", MB_OK);
					goto jieshu;
				}
			}
			if ((button3(1024, 576, 128, 72, out1, out2, mouse)) == true) {
				flag = 1;
				goto xunhuan;
			}

			/*��ҳ*/
			if ((button3(150, 704, 150, 16, right1, right2, mouse)) == true) {
				if ((i * 4 + j) < book_num)
				{
					i++;
					goto jieshu;
				}
				else {
					MessageBox(window, "��ǰ�Ѿ������һҳ�ˣ����Լ�һ�����", "����ͼ�����ϵͳ", MB_OK);
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
					MessageBox(window, "��ǰ�Ѿ��ǵ�һҳ��", "����ͼ�����ϵͳ", MB_OK);
					goto jieshu;
				}
			}
		}
	}

	/*����*/
	else if (flag == 5) {
		if (login == false) {
			MessageBox(window, "���ȵ�¼", "����ͼ�����ϵͳ", MB_OK);
			flag = 1;
			goto xunhuan;
		}
	huanshu:
		cleardevice();
		putimage(0, 0, &Return);
		i = 0;
		outtextxy(432, 0, "����������Զ��黹�鱾��");
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

	/*��������*/
	else if (flag == 6) {

	}

	/*����Ա����*/
	else if (flag == 7) {
		if (login == false) {
			MessageBox(window, "���ȵ�¼", "����ͼ�����ϵͳ", MB_OK);
			flag = 1;
			goto xunhuan;
		}
		if (op == false) {
			MessageBox(window, "���������Ա����(1234)", "����ͼ�����ϵͳ", MB_OK);
			strcpy(str, str_null);
			putimage(382, 86, &Text);
			input(382, 86, str, 20, Text);
			if (strcmp(str, pas) == 0) {
				op = true;
			}
			else {
				flag = 1;
				MessageBox(window, "�������", "����ͼ�����ϵͳ", MB_OK);
				goto xunhuan;
			}
		}
	OP:
		putimage(0, 0, &OP);
		outtextxy(432, 0, "ѡ����Ҫ�������鼮:");
		f = true;
		/*ѡ�����ģʽ*/
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

		/*����鼮*/
		if (flag == 3) {
			outtextxy(0, 0, "��������������֧��Ӣ�ĺ�����)");
			strcpy(str, str_null);
			while (f) {
				input(0, 32, str, 20, Text);
				if (strlen(str) == 0) {
					MessageBox(window, "��������Ϊ�գ�����������", "����ͼ�����ϵͳ", MB_OK);
					continue;
				}
				else break;
			}
			strcpy(book[book_num].name, str);
			outtextxy(0, 64, "����������ļ�������֧��Ӣ�ĺ�����,������׺��)");
			strcpy(str, str_null);
			while (f) {
				input(0, 96, str, 20, Text);
				if (strlen(str) == 0) {
					MessageBox(window, "�ļ�������Ϊ�գ�����������", "����ͼ�����ϵͳ", MB_OK);
					continue;
				}
				else break;
			}
			strcpy(book[book_num].FILE, str);
			outtextxy(0, 128, "���������ߣ���֧��Ӣ�ĺ�����)");
			strcpy(str, str_null);
			while (f) {
				input(0, 160, str, 20, Text);
				if (strlen(str) == 0) {
					MessageBox(window, "���߲���Ϊ�գ�����������", "����ͼ�����ϵͳ", MB_OK);
					continue;
				}
				else break;
			}
			strcpy(book[book_num].writer, str);
			book[book_num].num = 1;
			book[book_num++].maxnum = 1;
			MessageBox(window, "�������ɹ�", "����ͼ�����ϵͳ", MB_OK);
			goto OP;
		}

		/*����ĳ����*/
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
							MessageBox(window, "��������Ϊ�գ�����������", "����ͼ�����ϵͳ", MB_OK);
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
							MessageBox(window, "�ļ�������Ϊ�գ�����������", "����ͼ�����ϵͳ", MB_OK);
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
							MessageBox(window, "���߲���Ϊ�գ�����������", "����ͼ�����ϵͳ", MB_OK);
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
					MessageBox(window, "�ɹ������һ����", "����ͼ�����ϵͳ", MB_OK);
					goto OP;
				}
				if ((button3(120, 480, 120, 120, Book_Sub1, Book_Sub2, mouse)) == true) {
					if (book[book_point].num > 0) {
						book[book_point].maxnum--;
						book[book_point].num--;
						MessageBox(window, "�ɹ�ɾ����һ����", "����ͼ�����ϵͳ", MB_OK);
						goto OP;
					}
					else if (book[book_point].num == 0&& book[book_point].maxnum!=0) {
						MessageBox(window, "�����Ѿ�û���Ȿ���ˣ������û�������", "����ͼ�����ϵͳ", MB_OK);
						goto OP;
					}
					else if (book[book_point].maxnum == 0&&del==false) {
						MessageBox(window, "�����Ѿ�û���Ȿ���ˣ�����û���û����ߣ��ٴε��ִ��ɾ��", "����ͼ�����ϵͳ", MB_OK);
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
		/*�˳�*/
		else if (flag == 0) {
			p = fopen("account_list.txt", "w");
			fwrite(user, sizeof(struct account), user_num, p);
			fclose(p);

			q = fopen("book_list.txt", "w");
			fwrite(book, sizeof(struct booklist), book_num, q);
			fclose(q);
		}
}