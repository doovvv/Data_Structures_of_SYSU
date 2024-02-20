#include"Huffman.h"
vector<long long int> frequency(){
    ifstream file("ascii_text.txt");
    string text;
    string line;
    vector<long long int> freq(128,0);
    if(!file.is_open()){
        cout<<"can't open file"<<endl;
        return freq;
    }
    while(getline(file,line)){
        text += line;
        text += '\n';
    }
    file.close();
    int text_size = text.size();
    for(int i = 0;i<text_size;i++){
        freq[text[i]]++;
    }
    return freq;
}
map<char,string> get_code(vector<long long int> freq){
    Huffman huf;
    map<char,string> huffmancodes;
    Node* root = huf.build_tree(freq,1);
    huf.set_root(root);
    huf.build_code(huffmancodes,root,""); //以上为获得huffmancodes
    return huffmancodes;
}