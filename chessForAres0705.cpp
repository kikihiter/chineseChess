//Chinese Chess for AresLiu
//kiki 2018/07/01
#include <iostream> 
#include <string>
using namespace std;

//声明结构体piece，用来存储棋子信息
struct piece
{
	//用来判断棋子是否存活,false_alive,true_dead
	bool dead;

	//用来区分棋子所属阵营,false_red,true_black
	bool color;

	//用来判定棋子类型，7_兵，1_炮，2_车，3_马，4_象，5_士，6_帅
	int chessType;

	//棋子坐标
	int x;
	int y;
};

//用于返回命令中的位置坐标，应当注意的是，“炮八进五”这类命令中的后一个数“五”不应使用此函数;而“炮八平五”中的数字“八”“五”都属于位置坐标
//可以将命令中的数字分为两种，一种为位置坐标，另一种为移动距离，此函数仅用于位置坐标
int posNum(bool isBlack, string com)
{
	int position = 0;

	//红方命令
	if (isBlack == false)
	{
		if (com=="一")position = 1;
		else if (com == "二")position = 2;
		else if (com == "三")position = 3;
		else if (com == "四")position = 4;
		else if (com == "五")position = 5;
		else if (com == "六")position = 6;
		else if (com == "七")position = 7;
		else if (com == "八")position = 8;
		else if (com == "九")position = 9;
		else
		{
			cout << "Error001:outsize." << endl;
		}
	}

	//黑方命令
	else if (isBlack == true)
	{
		if (com == "一")position = 9;
		else if (com == "二")position = 8;
		else if (com == "三")position = 7;
		else if (com == "四")position = 6;
		else if (com == "五")position = 5;
		else if (com == "六")position = 4;
		else if (com == "七")position = 3;
		else if (com == "八")position = 2;
		else if (com == "九")position = 1;
		else
		{
			cout << "Error001:outsize." << endl;
		}
	}
	return position;
}

//打印棋盘（二维数组）
void showBoard(string checkerBoard[10][9])
{
	cout << endl;
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			std::cout << checkerBoard[i][j] << " ";
		}
		std::cout << endl;
		cout << endl;
	}
}

//棋子类型识别,返回字符串
string strType(int chessType)
{
	//chess.chessType
	switch (chessType)
	{
	case 1:
		return " 炮";
	case 2:
		return " 车";
	case 3:
		return " 马";
	case 4:
		return " 象";
	case 5:
		return " 士";
	case 6:
		return " 帅";
	case 7:
		return " 兵";
	default:
		cout << "Error404:no such chess type.";
		break;
	}
}

//更新棋盘
void updataBoard(string checkerBoard[10][9], piece chess[32])
{
	//棋盘归零
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			checkerBoard[i][j] = " + ";
		}
		
	}

	//重新绘制
	for (int i = 0; i < 32; i++)
	{
		if (chess[i].dead == false)
		{
			checkerBoard[10 - chess[i].y][chess[i].x - 1] = strType(chess[i].chessType);
		}
	}
}

//判断指定点是否存在障碍物,存在则返回障碍物序号，不存在返回-1
int chessBlock(piece chess[32],int x,int y)
{
	for (int i = 0; i < 32; i++)
	{
		if (chess[i].dead==false && chess[i].x == x && chess[i].y == y)
		{
			//cout << "Error002:there is a chessman here" << endl;//报错信息
			return i;
		}
	}
	return -1;
}

int main()
{
	//初始化棋盘
	string checkerBoard[10][9] = {};
	showBoard(checkerBoard);
	cout << endl;
	
	//(dead,color,chessType,x,y)
	//初始化全部红黑双方32个棋子，应当注意的是，初始化黑方的时候，坐标是按照红方来，设红方为基准，这里以红炮为例
	struct piece chess[32];
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
	chess[11] = { false, false, 7, 1, 5 };
	chess[12] = { false, false, 7, 3, 5 };
	chess[13] = { false, false, 7, 5, 5 };
	chess[14] = { false, false, 7, 7, 5 };
	chess[15] = { false, false, 7, 9, 5 };
	chess[16] = { false, true, 1, 5, 3 };

	updataBoard(checkerBoard, chess);
	showBoard(checkerBoard);

	//布尔变量确定下达命令的阵营,默认为红色
	bool isBlack = false;
	//判断是否异常
	bool ifError = false;
	//用来判断是否存在障碍物（指定点是否存在其他棋子）
	//bool chessmanHere = false;

	//输入命令，这里是控制台输入，正常应该语音识别出这部分内容，这里输入内容为“炮八平五”
	string command;
	cout << "your command:";
	cin >> command;


	//cout << posNum(isBlack, command.substr(2, 2)) << endl;//test
	//cout << command<<endl;//test
	//cout << command.substr(4, 2) << endl;//test

	//对传入命令进行分析，首先从第一个字开始，确定棋子类型，从而确定行动方式
	if (command.substr(0, 2) == "炮")
	{
		int posA = posNum(isBlack, command.substr(2, 2));
		if (isBlack == false && command.substr(2, 2) == "八")
		{
			//遍历所有棋子
			for (int i = 0; i<32; i++)
			{
				//cout << i << endl;//test
				//找到目标棋子，执行行动命令
				if (chess[i].dead == false && chess[i].color == false && chess[i].chessType == 1 && chess[i].x == 8)
				{
					//cout << "hello"<<endl;//test
					//读取第三个字，为行动类型,其他还有“进”、“退”两种类型
					if (command.substr(4, 2) == "平")
					{
						//读取第四个字，为落点
						if (command.substr(6, 2) == "五")
						{
							int posB = posNum(isBlack, command.substr(6, 2));
							
							//cout << "h" << endl;//test
							//观察运动路径及落点情况
							//for (int j = 0; j<32; j++)
							//{
							//	//cout << j << endl;//test
							//	//运动路径及落点
							//	if (chess[j].dead == false && chess[j].y == chess[i].y)
							//	{
							//		//运动路径上如果有其它棋子的话，报错退出循环
							//		if (chess[j].x == 7 || chess[j].x == 6)
							//		{
							//			cout << "error";
							//			ifError = true;
							//			break;
							//		}

							//		//落点为己方棋子，报错退出循环
							//		else if (chess[j].x == 5 && chess[j].color == chess[i].color)
							//		{
							//			cout << "error";
							//			ifError = true;
							//			break;
							//		}

							//		//落点为对方棋子，则吃掉对方棋子，改变对方棋子存活状况
							//		else if (chess[j].x == 5 && chess[j].color != chess[i].color)
							//		{
							//			//对方棋子死亡
							//			chess[j].dead = true;
							//		}
							//	}
							//}

							//向右移动
							if (posA < posB)
							{
								for (int j = posA+1; j < posB; j++)
								{
									cout << j << endl;
									if (chessBlock(chess, j, chess[i].y) != -1)
									{
										ifError == true;
										break;
									}
								}
							}
							//向左移动
							else if (posA > posB)
							{
								for (int j = posA-1; j > posB; j--)
								{
									cout << j << endl;
									if (chessBlock(chess,j,chess[i].y) != -1)
									{
										cout << "Error002:there is a chessman here" << endl;
										ifError == true;
										break;
									}
								}
							}
							
							//落点检测，如果为己方棋子则报错
							if (chessBlock(chess, posB, chess[i].y) != -1 && chess[chessBlock(chess, posB, chess[i].y)].color == chess[i].color)
							{
								cout << "Error003:here your chessman.";
								ifError == true;
								break;
							}
							//为敌方棋子，则吃掉对方，改变敌方棋子状态(炮不能直接吃，需要判定“炮架”)
							else if (chessBlock(chess, posB, chess[i].y) != -1 && isBlack != chess[i].color)
							{
								chess[chessBlock(chess, posB, chess[i].y)].dead = true;
							}

							//目标棋子坐标改变，平移至落点
							if (ifError == true)
							{
								ifError = false;
								break;
							}
							else if (ifError == false)
							{
								chess[i].x = posB;
								//ifError = false;
								//cout << "ok"<<endl;//test
							}
							//cout << "五";//test
						}
						//cout << "平";//test
					}
				}
			}

			//轮到黑方执子
			isBlack = true;
			//cout << "八";//test
		}

		//这里为轮到黑子行动的时刻，对于黑子来说，命令中的“八”，对应的是红方的“二”，简单的坐标变换，其它类似
		/*else if (isBlack == true && command.substr(2, 4) == '八')
		{

		}*/
		//cout << "炮";//test
	}

	updataBoard(checkerBoard, chess);
	showBoard(checkerBoard);
	
	std::system("pause");
	return 0;
}
