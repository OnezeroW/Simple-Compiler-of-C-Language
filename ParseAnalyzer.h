#ifndef PARSEANALYZER_H_INCLUDED
#define PARSEANALYZER_H_INCLUDED

#include <string>
#include <vector>
#include <fstream>
#include <stack>
#include "ConstDefine.h"
#include "LexicalAnalyzer.h"
using namespace std;

struct actionform
{
    char action; //r ��Լ  s �ƽ� a accept e error
    int state; //����״̬������ǹ�Լ�������򱣴��Լʽ���
};
struct parsenode
{
    int state;
    string symbol;
};
struct codenode
{
    vector<string> code;
    string result;
    bool isreg;  //�ǼĴ���
    bool isdig;  //������
};
struct reduce
{
    vector<string> tokenlist;
};
struct symform	//���ű�
{
    string name;
    int addr;
    int flag; //0 ���� 1 ����
};
class parse
{
public:
    parse();
    ~parse()
    {
        out.close();
        asmout.close();
    };
    void parse_analyze(Lexical &L);
    void lalr_analyze(spie s);
    void semantic_analyze(int label);
    void display();
private:
    actionform action[STATENUM][ENDNUM];  //������
    int go_to[STATENUM][NONENDNUM];  //ת�Ʊ�
    stack<parsenode> parsestack;
    vector<parsenode> tempparse;
    void readproduction();  //��ȡ����ʽ
    void readlalr();  //��ȡLALR
    string ignorelabel(string str);
    int stringtonum(string str);
    vector<reduce> reducelist;
    ofstream out,asmout;
    /**����*/
    vector<symform> form;
    stack<codenode> codestack;
    void gencode(string str);
    int offset;
    void addform(string name,int flag);
    int pushstack(codenode &tempnode1);
    int findeaxnum(string str)
    {
        int i,num = 0;
        if(str.substr(0,4) == "eax,")
            num++;
        i = str.find(",");
        while(i != -1)
        {
            if(i+4 < str.size())
            {
                if(str.substr(i+1,4) == "eax,")
                    num++;
            }
            else if(i+4 == str.size())
            {
                if(str.substr(i+1,3) == "eax")
                    num++;
            }
            str = str.substr(i+1,str.size()-i-1);
            i = str.find(",");
        }
        return num;
    }
    string randommake();
    int nownum;
    bool eaxreg;
    bool ebxreg;
};

#endif // PARSEANALYZER_H_INCLUDED
