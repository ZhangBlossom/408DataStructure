#include<iostream>
#include <cstdio>
#include<cstdlib>
#include <string.h>
#include<iomanip>
typedef int Status;
typedef int ElemType;
typedef char cElemType;
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define MAXSIZE 20
#define make (struct student*)malloc(sizeof(struct student));
using namespace std;

typedef struct HuffmanTree
{
	int weight;				   //权值
	char character;			   //字符
	int parent, lchild, rchild;//双亲以及左右孩子
}HuffmanTree,*p_HuffmanTree;
//用于找到两个最小的权值  m1和m2指针传递回最小两个值
void Decode(char** arr, char* bcode, int num);
void FindTwoMin(p_HuffmanTree T, int n, int* m1, int* m2)
{
	int min1, min2; //定义两个存放最小数据的整型
	min1 = min2 = 300;	//最小值初始化
	for (int i = 0; i < n; i++)//第一个for循环遍历一次 得到最小min1
	{
		if (T[i].weight < min1 && T[i].parent == 0)
		{
			min1 = T[i].weight;
			*m1 = i;  //将最小的数据的下标赋值给指针
		}
	}
	for (int i = 0; i < n; i++)//第二个for循环遍历一次，得到最小min2
	{	
		//这个if这样写的原因是由于如果我输入4 3 2 1 由于1+2=3 那么就会有两个3
		//如果单纯只有一个T[i].weight != min1
		//那么由于新生成的3不能等于输入的3，那么这个3就会被忽略，而导致3+4=7
		//而本来应该是3+3=6的
		if (T[i].weight < min2 && (T[i].weight != min1 || (i>*m1 && T[i].weight==min1)) && T[i].parent == 0)//判断条件 不能等于最小且不能是初始化值
		{
			min2 = T[i].weight;
			*m2 = i; //将最小的数据的下标赋值给指针
		}
	}
	
}
void InitHuffmanTree(p_HuffmanTree T, int n)
{
	int i;
	int* m1, * m2;
	m1 = (int*)malloc(sizeof(int)); //开辟两个存放最小数据下标的指针
	m2 = (int*)malloc(sizeof(int));
	if (n < 1)
	{
		cout << "初始化错误" << endl;
		exit(-1);
	}
	for (i = 0; i < 2 * n - 1; i++)//初始化为全0
	{
		T[i].lchild = 0; T[i].parent = 0; T[i].rchild = 0;
	}
	cout << "输入权值以及对应字符(先输入权值再输出字符)" << endl;
	for (i = 0; i < n; i++)//初始化节点权值
	{
		cin >> T[i].weight;
		cin >> T[i].character;  //先输入权值再输入字符 只有最初的几个节点有字符
	}
	for (i = n ; i < 2 * n - 1; i++)//这段代码用于将两个最小合并成一个新结点，补充数组
	{
		FindTwoMin(T, i , m1, m2);		//找到最小两个数据的下标此时以及初始化的数据有n个也就是i-1个
		T[*m1].parent = i; T[*m2].parent = i;			//让最小两个节点的双亲指向这个新数组下标
		T[i].lchild = *m1; T[i].rchild = *m2;			//左孩子指向最小数据的下标，右孩子指向第二小的
		T[i].weight = T[*m1].weight + T[*m2].weight;	//让两个数据的权值相加变为新结点权值
		T[i].character = '0';							//两个节点合成的数不需要字符
	}
}
//这段代码用来输出哈夫曼树各节点信息
void ShowHuffmanTree(const p_HuffmanTree T,int n,char**codearr)
{
	cout << "character   weight   parent   lchild   rchild" << endl;
	for (int i = 0; i < 2 * n - 1; i++)//输出各种属性
	{
		cout <<T[i].character << setw(15)<< T[i].weight << setw(10)<< T[i].parent << setw(10)
			<< T[i].lchild << setw(10) << T[i].rchild << endl;
	}
	for (int i = 0; i < n; i++)   //下面就是二维数组的输出数据的方法
	{
		for (int j = 0;  codearr[i][j] != '\0'; j++)
		{
			cout << codearr[i][j];
		}
		cout << endl;
	}
}
//这段代码用来实现哈夫曼编码  编码个数为初始节点个数num(main中定义)
//同时我们需要做到从下向上遍历，左孩子为0右孩子为1这标志放入一个数组(大小为n)
void CreateHuffmanCode(p_HuffmanTree T,char** codearr ,int num)
{
	int p;						//用于指向当前节点的双亲结点在数组的下标位置
	int j;						//j用来表示当前结点所在数组的位置
	int start;					//编码数组的下标，每存放一个数据向前移动一位
	char* code = new char[num + 1]; //生成一个存放编码的数组(倒序编码，从下往上的)
	code[num] = '\0';			//d110'\0' 最长编码的长度应该是n
	for (int i = 0; i < num; i++)
	{
		j = i;			//赋值当前结点位置
		start = num;//初始位置应该是n-1 3
		p = T[i].parent;//当前节点的双亲节点，循环向上得到各双亲结点
		while (p != 0)	//我们直到最后一个结点它的parent是0，因此如果遇到了0说明到了根节点
		{
			--start;
			if(T[p].lchild==j)	//判断是否是左孩子
			{ 
				code[start] = '0';  //左孩子为0
			}
			else
			{
				code[start] = '1'; //右孩子为1
			}
			j = p;			//当前结点变为双亲结点位置
			p = T[p].parent;	//结点变为双亲节点 回溯
		}
		codearr[i] = new char [num-start+1];  //开辟一个刚刚好能存放编码以及字符的数组
		code[--start] = T[i].character;		 //再向前移动一个位置然后存放字符例如abcd
		strcpy(codearr[i], &code[start]);	//把编码数组的其实地址放入到二维数组中去
	}
	delete code;//释放空间
}
//输入ABCDABCD得出对应的编码 编码已知 
void Code(char**arr,int num)
{
	int length = 0; char code[100]; char bcode[300];
	cout << "输入你明文(明文应该只包含你之前输入的字符)" << endl;
	cin >> code; 
	for (int i = 0; code[i] != '\0'; i++)//对每一个字符进行编码操作
	{
		for (int j = 0; j < num; j++)//对当前字符进行判断，判断当前字符是哪一个编码
		{
			if (code[i] == arr[j][0])//如果是当前编码 那就取出对应的编码然后放入编码数组
			{
				for (int h = 1; arr[j][h] != '\0'; h++)//编码数组的结尾是结束符
				{
					bcode[length++] = arr[j][h];//将密文数组赋值编码
				}
			}
		}
	}
	bcode[length] = '\0';		//密文结尾放上结束标识符
	cout << "密文是:";
	for(int i=0;bcode[i]!='\0';i++)
		cout << bcode[i];
	cout << endl;
	Decode(arr, bcode, num);
}
//已知字符对应的编码 已知密文 已知字符个数，字符个数-1可以得到最长的字符对应的编码
//strcmp函数可以用来比较两个字符串是否相同，我先取出num-1个字符串，然后逐一比较编码
//如果相同那么下标+num-1，不同则num-2，比较是否相同，循环往复
/*
需要引用#include <string.h>
比较字符串s1和s2: int strcmp(const char *s1, const char *s2);
比较字符串s1和s2前n个字符: int strncmp(const char *s1, const char *s2, size_t n);
如果两个字符一样大,返回值为 0, 如果s1>s2,则返回正值, 如果s1<s2,则返回负值
	int i = 0;
	char a[10] ;
	for (i = 0; i < 3; i++)
		cin >> a[i];
	a[i] = '\0';
	char b[10] = "asd";
	cout << strcmp(a, b);  返回0 说明可以使用这种方法，截取一部分的字符然后比较
	可以先取长度为1，也就是只取密文中的1个字符，然后用这个字符去遍历二维编码字符
	如果相同就输出对应的数据，然后数组后移去得到下一个，如果遍历完一次没有一样的，
	那么就增加这个数组中的数据，从密文中多取1一个数据，循环往复
*/
//解码函数 通过传递密文进去，解密
void Decode(char**arr,char*bcode,int num)
{
	int i; int j;
	int np = 0;//记录当前位置
	int flag = 0; //标志位 判断是否成功解码了一个字符
	int len = 1;//当前数据个数 初始为一个字符
	char cmp[10];//比较数组，用于比较编码是否一样
	char arrcmp[10];//二维数组中的编码
	cout << "收到的密文是:" << bcode << endl;
	while (bcode[np]!='\0')
	{
		for (len=1; flag != 1&&len<= num - 1; len++)
		{
			cmp[len - 1] = bcode[np];
			np++;
			cmp[len] = '\0';
			for (i = 0; i < num; i++)//二维数组中每一个行的遍历
			{
				for (j = 1; arr[i][j]!='\0'; j++)//二维数组中编码的遍历从1开始才是编码
				{
					arrcmp[j - 1] = arr[i][j]; //这个for用于先获取当前字符对应的编码
				}
				arrcmp[j - 1] = '\0'; //结束封顶 获取编码后下一步比较
				if (!strcmp(cmp, arrcmp))//两个数组内容一样
				{
					cout << arr[i][0];
					flag = 1;
				}
			}
		}
		flag = 0;
	}
}
int main()
{
	int num;
	cout << "输入节点个数" << endl;
	cin >> num;
	char** codearr = new char*[num];  //二维数组 用来存放所有的编码 以便之后输出
	p_HuffmanTree T = new HuffmanTree[2 * num - 1]; //创建二叉树节点数组
	InitHuffmanTree(T, num);  //初始化二叉树
	CreateHuffmanCode(T, codearr, num); //创建二叉树编码
	ShowHuffmanTree(T, num,codearr); //显示编码
	Code(codearr, num);
}