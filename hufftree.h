#ifndef HUFFTREE_H
#define HUFFTREE_H
#include <iostream>
#include <queue>
#include <iomanip>
#include <string>
using namespace std;
//有n个叶结点的树----2n-1个结点

typedef struct
{
    int weight;
    int parent,lchild,rchild;
}HTNode,*HuffmanTree;


typedef struct
{
    int pos;
    char ch;
    vector<int> charCode;
}Node,*NodeList;

void createHTree(HuffmanTree &HTree,int w[],int n)
//w权值向量，n个字符，构造哈夫曼树HT
{
    if(n<=1)return;
    int totalNum=2*n-1;
    HTree=(HuffmanTree)malloc((totalNum+1)*sizeof (HTNode));
    //输入哈夫曼树的初态,从下标为1开始输入，0号单元不使用
    int i;
    for(i=1;i<=n;i++)
    {
        HTree[i].weight=w[i-1];
        HTree[i].parent=0;
        HTree[i].lchild=0;
        HTree[i].rchild=0;
    }
    for(;i<=totalNum;i++)
    {
        HTree[i].weight=0;
        HTree[i].parent=0;
        HTree[i].lchild=0;
        HTree[i].rchild=0;
    }//初态构造

    priority_queue<int,vector<int>,greater<int> > myqueue;//优先队列，用来操作结点
    for(int i=0;i<n;i++)
    {
        //将权值放到优先队列中
        myqueue.push(w[i]);
    }

    //优先队列中的结点个数大于等于2时，将最小的两个元素记住，求和
    //最小的两个元素出队，新生成的和入队
    //在哈夫曼树中相应进行操作——两个最小结点---填写parent结点
    //并且生成新的结点，权值为和，并填写其孩子结点
    for(int current=n+1;current<=totalNum;current++)//current是当前正在构造的结点的位置
    {
        double minW1=myqueue.top();
        myqueue.pop();
        double minW2=myqueue.top();
        myqueue.pop();
        //得到队列中权值最小的两个权值，出队
        double addW=minW1+minW2;
        myqueue.push(addW);
        int minPos1,minPos2;//最小权值的存储位置
        for(int i=1;i<=totalNum;i++)
        {
            if(HTree[i].weight==minW1)
            {
                minPos1=i;
                break;
            }
        }
        for(int i=1;i<=totalNum;i++)
        {
            if(HTree[i].weight==minW2&&i!=minPos1)
            {
                minPos2=i;
            }
        }
        //下面构造新结点
        HTree[current].weight=addW;
        HTree[minPos1].parent=current;
        HTree[minPos2].parent=current;


        HTree[current].lchild=minPos1;
        HTree[current].rchild=minPos2;
        //这样构造使得左子树小于右子树
    }
}
void findCode(HuffmanTree &HTree,int n,int pos,vector<int> &charCode)
{
    //已经有哈夫曼树之后，给定某叶结点的位置，写出哈夫曼编码，放到charcode里面
    int cur_pos=pos;
    int find_parent=0;
    while(1)
    {
        int i=0;
        for(i=0;i<2*n;i++)
        {
            if(HTree[i].lchild==cur_pos)
            {
                find_parent=i;
                //再记下哈夫曼编码
                charCode.insert(charCode.begin(),0);//头插
                cur_pos=find_parent;
            }
            else if(HTree[i].rchild==cur_pos)
            {
                find_parent=i;
                charCode.insert(charCode.begin(),1);//头插
                cur_pos=find_parent;
            }
        }
        if(find_parent==2*n-1)
        {
            break;
        }
    }
}
void HuffmanCoding(HuffmanTree HTree,char charList[],int n,Node codeList[])
//根据哈夫曼树，将所有字符的编码保存到codelist里面
{
    for(int i=1;i<=n;i++)//i是哈夫曼表里面的下标，从1开始
    {
        codeList[i].ch=charList[i-1];
        findCode(HTree,n,i,codeList[i].charCode);
    }
}
void PrintVector(vector<int> vec)
{
    int n=vec.size();
    for(int i=0;i<n;i++)
    {
        cout<<vec[i];
    }
}
void printAllCode(int n,Node codeList[])
{
    for(int i=1;i<=n;i++)
    {
        cout.flags(ios::left);
        cout<<codeList[i].ch<<":  ";
        PrintVector(codeList[i].charCode);
        cout<<endl;
    }
}
void passageCoding(vector<char> str,Node codelist[],int n)
{
    for(int i;;i++)
    {
        if(str[i]=='#')
            break;
        for(int j=1;j<=n;j++)
        {
            if(str[i]==codelist[j].ch)
            {
                PrintVector(codelist[j].charCode);
                break;
            }
        }
    }
}
bool checkLeaf(HuffmanTree Htree,int pos)
{
    if(Htree[pos].lchild==0&&Htree[pos].rchild==0)
        return 1;
    else return 0;
}
void decode(HuffmanTree HTree,int n,char charList[])
//根据哈夫曼树进行解码,n是叶结点个数
{
    int curPos=2*n-1;//在哈夫曼树上遍历，从根结点开始往下走，走到叶结点又拉回根结点
    char ch;
    while(cin>>ch)
    {
        if(ch=='1')
        {
            curPos=HTree[curPos].rchild;
        }
        else if(ch=='0')
        {
            curPos=HTree[curPos].lchild;
        }
        if(checkLeaf(HTree,curPos))//走到了叶子结点
        {
            cout<<charList[curPos-1];
            curPos=2*n-1;
        }
    }
}
#endif // HUFFTREE_H
