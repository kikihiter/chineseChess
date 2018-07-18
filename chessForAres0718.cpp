//Chinese Chess for AresLiu
//kiki 2018/07/14
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// * ��������                                                                                                               //
// * ��Ӵ���Ŀ¼                                                                                                           //
// * ���ڵ�ƽ���жϽ��з�װ��paoPing����ƽ���ڵ�ƽ�ƣ�                                                                      //
// * ������һ��paoPing�й��ڼ��������쳣�ж�����                                                                          //
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//--------------------------------------------------------------------------------------------------------------------------//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// * Error001:outsize.                                                                                                      //
// * Error002:there is a chessman here                                                                                      //
// * Error003:here your chessman.                                                                                           //
// * Error404:no such chess type.                                                                                           //
// * Error005:can not move so far.                                                                                          //
// * Error006:the chessman not only 1.                                                                                      //
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <iostream> 
#include <string>
#include <windows.h>
using namespace std;

//�����ṹ��piece�������洢������Ϣ
struct piece
{
	//�����ж������Ƿ���,false_alive,true_dead
	bool dead;

	//������������������Ӫ,false_red,true_black
	bool color;

	//�����ж��������ͣ�7_����1_�ڣ�2_����3_��4_��5_ʿ��6_˧
	int chessType;

	//��������
	int x;
	int y;
};

//���ڷ��������е�λ�����꣬Ӧ��ע����ǣ����ڰ˽��塱���������еĺ�һ�������塱��Ӧʹ�ô˺���;�����ڰ�ƽ�塱�е����֡��ˡ����塱������λ������
//���Խ������е����ַ�Ϊ���֣�һ��Ϊλ�����꣬��һ��Ϊ�ƶ����룬�˺���������λ������
int posNum(bool isBlack, string com)
{
	int position = 0;

	//�췽����
	if (isBlack == false)
	{
		if (com=="һ")position = 1;
		else if (com == "��")position = 2;
		else if (com == "��")position = 3;
		else if (com == "��")position = 4;
		else if (com == "��")position = 5;
		else if (com == "��")position = 6;
		else if (com == "��")position = 7;
		else if (com == "��")position = 8;
		else if (com == "��")position = 9;
		else
		{
			cout << "Error001:outsize." << endl;
		}
	}

	//�ڷ�����
	else if (isBlack == true)
	{
		if (com == "һ")position = 9;
		else if (com == "��")position = 8;
		else if (com == "��")position = 7;
		else if (com == "��")position = 6;
		else if (com == "��")position = 5;
		else if (com == "��")position = 4;
		else if (com == "��")position = 3;
		else if (com == "��")position = 2;
		else if (com == "��")position = 1;
		else
		{
			cout << "Error001:outsize." << endl;
		}
	}
	return position;
}

//���ڷ��������е��ƶ��������꣬Ӧ��ע����ǣ�����ִ��˫����ǰ���ͺ���������������Եģ���������������֣���������������߼���ϵ��Ӧע��
//���Խ������е����ַ�Ϊ���֣�һ��Ϊλ�����꣬��һ��Ϊ�ƶ����룬�˺����������ƶ�����
int moveNum( string com)
{
	int position = 0;

	if (com == "һ")position = 1;
	else if (com == "��")position = 2;
	else if (com == "��")position = 3;
	else if (com == "��")position = 4;
	else if (com == "��")position = 5;
	else if (com == "��")position = 6;
	else if (com == "��")position = 7;
	else if (com == "��")position = 8;
	else if (com == "��")position = 9;
	else
	{
		cout << "Error005:can not move so far." << endl;
	}

	return position;
}

//��ӡ���̣���ά���飩
void showBoard(string checkerBoard[10][9],bool boardColor[10][9])
{
	cout << endl;
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			if (boardColor[i][j] == true)
			{
				std::cout << checkerBoard[i][j] << " ";
			}
			else if (boardColor[i][j] == false)
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);//| COMMON_LVB_UNDERSCORE);
				std::cout << checkerBoard[i][j] << " ";
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);  // ϵͳĬ����ɫ
			}
		}
		if (i == 4)
		{
			std::cout << endl;
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | COMMON_LVB_UNDERSCORE);
			std::cout << "     ��     ��       ��     ��     " << endl;
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);  // ϵͳĬ����ɫ
			continue;
		}
		else if (i == 0 || i == 7)
		{
			std::cout << endl;
			//--- --- --- --- --- --- --- --- ---
			std::cout << "             | \\ | / |             " << endl;
			continue;
		}
		else if (i == 1 || i == 8)
		{
			std::cout << endl;
			std::cout << "             | / | \\ |             " << endl;
			continue;
		}
		std::cout << endl;
		cout << endl;
	}
}

//��������ʶ��,�����ַ���
string strType(int chessType)
{
	//chess.chessType
	switch (chessType)
	{
	case 1:
		return " ��";
	case 2:
		return " ��";
	case 3:
		return " ��";
	case 4:
		return " ��";
	case 5:
		return " ʿ";
	case 6:
		return " ˧";
	case 7:
		return " ��";
	default:
		cout << "Error404:no such chess type.";
		break;
	}
}

//��������
void updataBoard(string checkerBoard[10][9], piece chess[32],bool boardColor[10][9])
{
	//���̹���
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			checkerBoard[i][j] = " ��";
			if (i == 4 )
			{
				//checkerBoard[i][j] = "___";
			}
			if (i == 2 && (j==4 || j== 5 || j == 3) )
			{
				//checkerBoard[i][j] = "---";
			}
			boardColor[i][j] = true;
		}
		
	}
	checkerBoard[2][1] = " + "; checkerBoard[2][7] = " + "; checkerBoard[7][1] = " + "; checkerBoard[7][7] = " + ";

	//���»���
	for (int i = 0; i < 32; i++)
	{
		if (chess[i].dead == false)
		{
			checkerBoard[10 - chess[i].y][chess[i].x - 1] = strType(chess[i].chessType);
			if (chess[i].color == false)
			{
				boardColor[10 - chess[i].y][chess[i].x - 1] = false;
			}
		}
	}
}

//�ж�ָ�����Ƿ�����ϰ���,�����򷵻��ϰ�����ţ������ڷ���-1
int chessBlock(piece chess[32],int x,int y)
{
	for (int i = 0; i < 32; i++)
	{
		if (chess[i].dead==false && chess[i].x == x && chess[i].y == y)
		{
			//cout << "Error002:there is a chessman here" << endl;//������Ϣ
			return i;
		}
	}
	return -1;
}

//��ʼ������
void chessBegin(piece chess[32])
{
	//�췽
	chess[0] = { false, false, 2, 1, 1 };
	chess[1] = { false, false, 3, 2, 1 };
	chess[2] = { false, false, 4, 3, 1 };
	chess[3] = { false, false, 5, 4, 1 };
	chess[4] = { false, false, 6, 5, 1 };
	chess[5] = { false, false, 5, 6, 1 };
	chess[6] = { false, false, 4, 7, 1 };
	chess[7] = { false, false, 3, 8, 1 };
	chess[8] = { false, false, 2, 9, 1 };
	chess[9] = { false, false, 1, 2, 3 };
	chess[10] = { false, false, 1, 8, 3 };
	chess[11] = { false, false, 7, 1, 4 };
	chess[12] = { false, false, 7, 3, 4 };
	chess[13] = { false, false, 7, 5, 4 };
	chess[14] = { false, false, 7, 7, 4 };
	chess[15] = { false, false, 7, 9, 4 };

	//�ڷ�
	chess[16] = { false, true, 2, 1, 10 };
	chess[17] = { false, true, 3, 2, 10 };
	chess[18] = { false, true, 4, 3, 10 };
	chess[19] = { false, true, 5, 4, 10 };
	chess[20] = { false, true, 6, 5, 10 };
	chess[21] = { false, true, 5, 6, 10 };
	chess[22] = { false, true, 4, 7, 10 };
	chess[23] = { false, true, 3, 8, 10 };
	chess[24] = { false, true, 2, 9, 10 };
	chess[25] = { false, true, 1, 2, 8 };
	chess[26] = { false, true, 1, 8, 8 };
	chess[27] = { false, true, 7, 1, 7 };
	chess[28] = { false, true, 7, 3, 7 };
	chess[29] = { false, true, 7, 5, 7 };
	chess[30] = { false, true, 7, 7, 7 };
	chess[31] = { false, true, 7, 9, 7 };
}

//paoPing����ƽ���ڵ�ƽ�Ʋ�������bool�������ж�ƽ��·�����Լ�����Ƿ�����ϰ������ifError
bool paoPing(int posA ,int posB,int i ,piece chess[32] , bool ifError)
{
	if (posA < posB)
	{
		for (int j = posA + 1; j < posB; j++)
		{
			//cout << j << endl;//test
			if (chessBlock(chess, j, chess[i].y) != -1)
			{
				ifError = true;
				break;
			}
		}
	}
	//�����ƶ�
	else if (posA > posB)
	{
		for (int j = posA - 1; j > posB; j--)
		{
			//cout << j << endl;//test
			if (chessBlock(chess, j, chess[i].y) != -1)
			{
				cout << "Error002:there is a chessman here" << endl;
				ifError = true;
				break;
			}
		}
	}

	//����⣬���Ϊ���������򱨴�
	if (chessBlock(chess, posB, chess[i].y) != -1 && chess[chessBlock(chess, posB, chess[i].y)].color == chess[i].color)
	{
		cout << "Error003:here your chessman.";
		ifError = true;
		//.break;
	}
	//Ϊ�з����ӣ���Ե��Է����ı�з�����״̬(�ڲ���ֱ�ӳԣ���Ҫ�ж����ڼܡ�)
	else if (chessBlock(chess, posB, chess[i].y) != -1 && chess[chessBlock(chess, posB, chess[i].y)].color != chess[i].color)
	{
		chess[chessBlock(chess, posB, chess[i].y)].dead = true;
	}

	return ifError;
}

//juPing����ƽ������ƽ�Ʋ�������bool�������ж�ƽ��·�����Լ�����Ƿ�����ϰ������ifError
bool juPing(int posA, int posB, int i, piece chess[32], bool ifError)
{
	if (posA < posB)
	{
		for (int j = posA + 1; j < posB; j++)
		{
			//cout << j << endl;//test
			if (chessBlock(chess, j, chess[i].y) != -1)
			{
				ifError = true;
				break;
			}
		}
	}
	//�����ƶ�
	else if (posA > posB)
	{
		for (int j = posA - 1; j > posB; j--)
		{
			//cout << j << endl;//test
			if (chessBlock(chess, j, chess[i].y) != -1)
			{
				cout << "Error002:there is a chessman here" << endl;
				ifError = true;
				break;
			}
		}
	}

	//����⣬���Ϊ���������򱨴�
	if (chessBlock(chess, posB, chess[i].y) != -1 && chess[chessBlock(chess, posB, chess[i].y)].color == chess[i].color)
	{
		cout << "Error003:here your chessman.";
		ifError = true;
		//.break;
	}
	//Ϊ�з����ӣ���Ե��Է����ı�з�����״̬(�ڲ���ֱ�ӳԣ���Ҫ�ж����ڼܡ�)
	else if (chessBlock(chess, posB, chess[i].y) != -1 && chess[chessBlock(chess, posB, chess[i].y)].color != chess[i].color)
	{
		chess[chessBlock(chess, posB, chess[i].y)].dead = true;
	}

	return ifError;
}


int main()
{
	//��ʼ������
	string checkerBoard[10][9] = {};
	//����һ�������ж�������ɫ�Ķ�ά���飬false_red,true_black
	bool boardColor[10][9] = {};
	//showBoard(checkerBoard);
	cout << endl;
	
	//(dead,color,chessType,x,y)
	//��ʼ��ȫ�����˫��32�����ӣ�Ӧ��ע����ǣ���ʼ���ڷ���ʱ�������ǰ��պ췽������췽Ϊ��׼�������Ժ���Ϊ��
	struct piece chess[32];
	chessBegin(chess);

	updataBoard(checkerBoard, chess,boardColor);
	showBoard(checkerBoard, boardColor);

	//��������ȷ���´��������Ӫ,Ĭ��Ϊ��ɫ
	bool isBlack = false;
	//cout << isBlack << endl;//test
	//�ж��Ƿ��쳣
	bool ifError = false;
	//�����ж��Ƿ�����ϰ��ָ�����Ƿ�����������ӣ�
	//bool chessmanHere = false;

	//������������ǿ���̨���룬����Ӧ������ʶ����ⲿ�����ݣ�������������Ϊ���ڰ�ƽ�塱
	string command;

	//������ս��ʼ
	while (true)
	{
		//��ӡִ�ӷ�
		if (isBlack == false)
		{
			cout << "Red party." << endl;
		}
		else if (isBlack == true)
		{
			cout <<  "Black party" << endl;
		}
		cout << "Please enter your command:";
		cin >> command;


		//cout << posNum(isBlack, command.substr(2, 2)) << endl;//test
		//cout << command<<endl;//test
		//cout << command.substr(4, 2) << endl;//test

		//�Դ���������з��������ȴӵ�һ���ֿ�ʼ��ȷ���������ͣ��Ӷ�ȷ���ж���ʽ���˴�Ϊ��
		if (command.substr(0, 2) == "��")
		{
			//��ȡĿ������λ������
			int posA = posNum(isBlack, command.substr(2, 2));
			//���������쳣�ж�
			if (posA==0)
			{
				ifError = true;
			}

			//������������
			//����Ŀ�������������������������ӣ�������������������Ϊ1�����쳣
			int targetNum = 0;
			for (int i = 0; i < 32; i++)
			{
				if (chess[i].dead == false && chess[i].color == isBlack && chess[i].chessType == 1 && chess[i].x == posA)
				{
					targetNum = targetNum + 1;
				}
			}
			if (targetNum != 1)
			{
				std::cout << "Error006:the chessman not only 1." << endl;
				ifError = true;
			}

			for (int i = 0; i < 32; i++)
			{
				//cout << i << endl;//test
				//�ҵ�Ŀ�����ӣ�ִ���ж�����
				if (chess[i].dead == false && chess[i].color == isBlack && chess[i].chessType == 1 && chess[i].x == posA)
				{
					//��ȡ�������֣�Ϊ�ж�����,�������С����������ˡ���������
					if (command.substr(4, 2) == "ƽ")
					{
						//��ȡ���ĸ��֣�Ϊ���
						//if (command.substr(6, 2) == "��")
						//{
						int posB = posNum(isBlack, command.substr(6, 2));
						//���������쳣�ж�
						if (posB == 0)
						{
							ifError = true;
						}

						//�۲��˶�·����������
						//���ú���paoPing���ж�ƽ�ƹ����Ƿ�����쳣
						ifError = paoPing(posA, posB, i, chess, ifError);

						//���ִ˴��ж����ִ��󣬲������ƶ�
						if (ifError == true)
						{
							ifError = false;
							break;
						}
						//Ŀ����������ı䣬ƽ�������
						else if (ifError == false)
						{
							chess[i].x = posB;
							//�ֵ���һ��ִ��
							isBlack =! isBlack;
							break;
						}
					}
				}
			}

		}
		
		//�Դ���������з��������ȴӵ�һ���ֿ�ʼ��ȷ���������ͣ��Ӷ�ȷ���ж���ʽ���˴�Ϊ��
		else if (command.substr(0, 2) == "��")
		{
			int posA = posNum(isBlack, command.substr(2, 2));
			//������������
			for (int i = 0; i < 32; i++)
			{
				//�ҵ�Ŀ�����ӣ�ִ���ж�����
				if (chess[i].dead == false && chess[i].color == isBlack && chess[i].chessType == 2 && chess[i].x == posA)
				{
					//��ȡ�������֣�Ϊ�ж�����,�������С����������ˡ���������,�˴�Ϊƽ
					if (command.substr(4, 2) == "ƽ")
					{
						//��ȡ���ĸ��֣�Ϊ���
						int posB = posNum(isBlack, command.substr(6, 2));

						//�۲��˶�·����������
						//���ú���paoPing���ж�ƽ�ƹ����Ƿ�����쳣
						ifError = juPing(posA, posB, i, chess, ifError);

						//���ִ˴��ж����ִ��󣬲������ƶ�
						if (ifError == true)
						{
							ifError = false;
							break;
						}
						//Ŀ����������ı䣬ƽ�������
						else if (ifError == false)
						{
							chess[i].x = posB;
							//�ֵ���һ��ִ��
							isBlack = !isBlack;
							break;
						}
					}

					//�˴�Ϊ������
					if (command.substr(4, 2) == "��")
					{
						//��ȡ���ĸ��֣�Ϊǰ������
						int posB = moveNum( command.substr(6, 2));

						//�۲��˶�·����������
						//���ú���paoPing���ж�ƽ�ƹ����Ƿ�����쳣
						ifError = juPing(posA, posB, i, chess, ifError);

						//���ִ˴��ж����ִ��󣬲������ƶ�
						if (ifError == true)
						{
							ifError = false;
							break;
						}
						//Ŀ����������ı䣬ƽ�������
						else if (ifError == false)
						{
							chess[i].x = posB;
							//�ֵ���һ��ִ��
							isBlack = !isBlack;
							break;
						}
					}
				}
			}

		}

		//cout << isBlack << endl; //test
		updataBoard(checkerBoard, chess, boardColor);
		showBoard(checkerBoard, boardColor);
	}
	std::system("pause");
	

	return 0;
}