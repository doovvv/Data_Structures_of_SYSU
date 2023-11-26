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
        unsigned char myself;
        long long int freq;
        Node* left;
        Node* right;
    public:
        Node(unsigned char ch,int f = 0,Node* l = nullptr,Node* r = nullptr){
            myself = ch;
            freq = f;
            left = l;
            right = r;
        }
        long long int get_freq() const;
        Node* get_left()const;
         Node* get_right()const;
        unsigned char get_char()const;
        bool operator <(const Node& other)const;
        bool is_leaf()const;

        
        
};
class Huffman{
    private:
        Node* root;
    public:
        Node* build_tree(long long int freq[]);
        void set_root(Node* n);
        void build_code(map<unsigned char,string>& huffmancodes,Node* n,string s);
};
struct CompareNodes {
    bool operator() (Node* a, Node* b) {
        return a->get_freq() > b->get_freq();
    }
};
void compression(string infilename,string outfilename);
void expand(string infilename,string outfilename);
void convertToGray(const string& inputFileName, const string& outputFileName);
void interpolation(const string& inputFileName, const string& outputFileName,int new_width,int new_height);