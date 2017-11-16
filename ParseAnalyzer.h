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
    char action; //r 规约  s 移进 a accept e error
    int state; //现在状态，如果是规约动作，则保存规约式编号
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
    bool isreg;  //是寄存器
    bool isdig;  //是数字
};
struct reduce
{
    vector<string> tokenlist;
};
struct symform	//符号表
{
    string name;
    int addr;
    int flag; //0 变量 1 数组
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
    actionform action[STATENUM][ENDNUM];  //动作表
    int go_to[STATENUM][NONENDNUM];  //转移表
    stack<parsenode> parsestack;
    vector<parsenode> tempparse;
    void readproduction();  //读取产生式
    void readlalr();  //读取LALR
    string ignorelabel(string str);
    int stringtonum(string str);
    vector<reduce> reducelist;
    ofstream out,asmout;
    /**语义*/
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
