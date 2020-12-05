#include <iostream>
#include <iomanip>
#include <hufftree.h>
using namespace std;
#define MAX_CHAR_NUM 31


int main()
{

    cout<<"please input a string, only contain letters, blanks or ',' '.' '?' '!' ,end with a '#'"<<endl;
    char charList[MAX_CHAR_NUM];//a到z在0到25，26，27，28，29为标点符号,30为空格
    for(int i=0;i<MAX_CHAR_NUM;i++)
    {
        if(i<26)
        {
            charList[i]=i+'a';
        }
        charList[26]=',';
        charList[27]='.';
        charList[28]='?';
        charList[29]='!';
        charList[30]=' ';
    }

    int weight[MAX_CHAR_NUM]={0};//计数，出现次数

    vector<char> myinput;

    for(int i=0;;i++)
    {
        char ch;
        scanf("%c",&ch);
        //cin>>ch;
        myinput.push_back(ch);//将输入保存到数组里面

        if(ch=='#')
        {
            break;
        }

        if(ch>='a'&&ch<='z')
        {
            weight[ch-'a']++;
        }
        else if(ch>='A'&&ch<='Z')
        {
            weight[ch-'A']++;
        }
        else if(ch==',')
        {
            weight[26]++;
        }
        else if(ch=='.')
        {
            weight[27]++;
        }
        else if(ch=='?')
        {
            weight[28]++;
        }
        else if(ch=='!')
        {
            weight[29]++;
        }
        else if(ch==' ')
        {
            weight[30]++;
        }
    }

    int inputLength=myinput.size();
    vector<char> newCharList;
    vector<int> newWeight;
    //去掉权重为0的字符
    for(int i=0;i<MAX_CHAR_NUM;i++)
    {
        if(weight[i]!=0)
        {
            newWeight.push_back(weight[i]);
            newCharList.push_back(charList[i]);
        }
    }
    int n=newWeight.size();//权重不为零的字符个数
    //int weightList[30];
    for(int i=0;i<n;i++)
    {
        weight[i]=newWeight[i];
        charList[i]=newCharList[i];
    }
    HuffmanTree HTree;
    createHTree(HTree,weight,n);


    cout<<"-------------------------------------------"<<endl;
    cout<<"the HC chart is"<<endl;
    cout.flags(ios::left);
    cout<<setw(5)<<"pos"<<setw(5)<<"ch"<<setw(5)<<"ww"<<setw(5)<<"p"<<setw(5)<<"l"<<setw(5)<<"r"<<endl;
    for(int i=1;i<=n;i++)
    {
        cout.flags(ios::left);
        cout<<setw(5)<<i<<setw(5)<<charList[i-1]<<setw(5)<<HTree[i].weight<<setw(5)<<HTree[i].parent<<setw(5)<<HTree[i].lchild<<setw(5)<<HTree[i].rchild<<endl;
    }
    for(int i=n+1;i<2*n;i++)
    {
        cout.flags(ios::left);
        cout<<setw(5)<<i<<setw(5)<<"-"<<setw(5)<<setw(5)<<HTree[i].weight<<setw(5)<<HTree[i].parent<<setw(5)<<HTree[i].lchild<<setw(5)<<HTree[i].rchild<<endl;
    }
    cout<<"-------------------------------------------"<<endl;
    //调试可以正确建立哈夫曼树


    Node codeList[2*MAX_CHAR_NUM];
    HuffmanCoding(HTree,charList,n,codeList);
    cout<<endl;
    cout<<"-------------------------------------------"<<endl;
    cout<<"the Huffmancode is"<<endl;
    printAllCode(n,codeList);
    cout<<"-------------------------------------------"<<endl;
    //输出每个字符的编码

    cout<<"coding the input passage"<<endl;
    passageCoding(myinput,codeList,n);//输出一开始输入的“文章”的编码
    cout<<endl;
    cout<<"-------------------------------------------"<<endl;
    cout<<"input a string of Huffman code, using the coding method as afore-mentioned"<<endl;
    cout<<"you can copy the code output above, and input it to see if it can be successfully decoded"<<endl;

    decode(HTree,n,charList);

    return 0;
}










