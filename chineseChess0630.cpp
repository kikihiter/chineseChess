//Chinese Chess for AresLiu
//kiki 2018/06/30
#include <iostream> 
using namespace std;

//声明结构体piece，用来存储棋子信息
struct piece
{
    //用来判断棋子是否存活,false_alive,true_dead
    bool dead;
    
    //用来区分棋子所属阵营,false_red,true_black
    bool color;
    
    //用来判定棋子类型，0_兵，1_炮，2_车，3_马，4_象，5_士，6_帅
    int chessType;
    
    //棋子坐标
    int x;
    int y;
};

//用于返回命令中的位置坐标，应当注意的是，“炮八进五”这类命令中的后一个数“五”不应使用此函数
//可以将命令中的数字分为两种，一种为位置坐标，另一种为移动距离，此函数仅用于位置坐标
int posNum(bool isBlack , char com )
{
    int position;
    
    //红方命令
    if (isBlack == false)
    {
        if (com == '一')
        {
            position = 1;
        }
        else if (com == '五')
        {
            position = 5;
        }
        // else if (com == '...')
        // {
            // position = ...;
        // }
        // ...
        // 1-9
    }
    
    //黑方命令
    else if (isBlack == true)
    {
        if (com == '一')
        {
            position = 9;
        }
        else if (com == '五')
        {
            position = 5;
        }
        // else if (com == '...')
        // {
            // position = ...;
        // }
        // ...
        // 1-9
    }
    return position;
}

int main()
{
    //初始化全部红黑双方32个棋子，应当注意的是，初始化黑方的时候，坐标是按照红方来，设红方为基准，这里以红炮为例
    struct piece chess[32];
    chess[6] = {false,false,1,8,3};
    
    //布尔变量确定下达命令的阵营,默认为红色
    bool isBlack = false;
    //判断是否异常
    bool ifError = false;
    
    //输入命令，这里是控制台输入，正常应该语音识别出这部分内容，这里输入内容为“炮八平五”
    string command;
    cout<<"your command:";
    cin>>command;
    
    //对传入命令进行分析，首先从第一个字开始，确定棋子类型，从而确定行动方式
    if (command[0] == "炮")
    {
        if (isBlack == false and command[1] == "八")
        {
            //遍历所有棋子
            for (int i=0 ; i<32 ;i++)
            {
                //找到目标棋子，执行行动命令
                if (chess[i].dead == false and chess[i].color == false and chess[i].chessType == 1 and chess[i].x == 8 )
                {
                    //读取第三个字，为行动类型,其他还有“进”、“退”两种类型
                    if (command[2] == "平")
                    {
                        //读取第四个字，为落点
                        if (command[3] == "五")
                        {
                            //观察运动路径及落点情况
                            for (int j=0 ; j<32 ;j++)
                            {
                                //运动路径及落点
                                if (chess[j].dead == false and chess[j].y == 3)
                                {
                                    //运动路径上如果有其它棋子的话，报错退出循环
                                    if (chess[j].x == 7 or chess[j].x == 6)
                                    {
                                        cout<<"error";
                                        ifError = true;
                                        break;
                                    }
                                    
                                    //落点为己方棋子，报错退出循环
                                    else if (chess[j].x == 5 and chess[j].color == chess[i].color)
                                    {
                                        cout<<"error";
                                        ifError = true;
                                        break;
                                    }
                                    
                                    //落点为对方棋子，则吃掉对方棋子，改变对方棋子存活状况
                                    else if (chess[j].x == 5 and chess[j].color != chess[i].color)
                                    {
                                        //对方棋子死亡
                                        chess[j].dead = true;
                                    }
                                }
                            }
                            //目标棋子坐标改变，平移至落点
                            if (ifError = true;)
                            {
                                ifError = false;
                                break;
                            }
                            else if (ifError == false)
                            {
                                chess[i].x = 5;
                                //ifError = false;
                            }
                            
                        }
                    }
                }
            }
            
            //轮到黑方执子
            isBlack = true;
        }
        
        //这里为轮到黑子行动的时刻，对于黑子来说，命令中的“八”，对应的是红方的“二”，简单的坐标变换，其它类似
        else if (isBlack == true and command[1] == "八")
        {
            
        }
    }
return 0;
}