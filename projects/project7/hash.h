#include<string>
#include<vector>
#include<iostream>
using namespace std;
class name{
    public:
    string name;
    int ascii_value;
};
class Hash{
    public:
    string name;
    int key;
    int sum;
    //Hash* next; //计算当前key下的存储的名字数
    Hash(){
        name = "";
        key = 0;
        sum = 0;
        //next = nullptr;
    }
};
class PseudoRandomGenerator {
private:
    int seed;   // 初始种子
    int a;      // 乘数
    int c;      // 偏移
    int m;      // 模数

public:
    PseudoRandomGenerator(int initialSeed, int multiplier, int increment, int modulus)
        : seed(initialSeed), a(multiplier), c(increment), m(modulus) {}

    // 生成下一个伪随机数
    int getNextRandom() {
        seed = (a * seed + c) % m;
        return seed;
    }
};
void create_hash_table(vector<vector<Hash>>& hash_table,string chineseNames[],int mode);
int get_key(string name);
void search_name(vector<vector<Hash>>& hash_table,int mode);
void display_table(vector<vector<Hash>>& hash_table);
void display_name_and_key(string chineseNames[]);
