#include<iostream>
#include<fstream>
#include<queue>
#include<map>
#include<vector>
#include<stdlib.h>
#include<bitset>
using namespace std;
class Node{
    private:
         char myself;
        long long int freq;
        Node* left;
        Node* right;
    public:
        Node(char ch,int f = 0,Node* l = nullptr,Node* r = nullptr){
            myself = ch;
            freq = f;
            left = l;
            right = r;
        }
        long long int get_freq() const;
        Node* get_left()const;
         Node* get_right()const;
         char get_char()const;
        bool operator <(const Node& other)const;
        bool is_leaf()const;

        
        
};
class Huffman{
    private:
        Node* root;
    public:
        Node* build_tree(vector<long long int>freq,int mode);
        void set_root(Node* n);
        void build_code(map<char,string>& huffmancodes,Node* n,string s);
};
struct CompareNodes {
    bool operator() (Node* a, Node* b) {
        return a->get_freq() > b->get_freq();
    }
};
void compression(string infilename,string outfilename,int mode);
void expand(string infilename,string outfilename,int mode);
vector<long long int> frequency();
map<char,string> get_code(vector<long long int> freq);