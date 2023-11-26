#include"Huffman.h"
long long int Node::get_freq() const{
        return freq;
    }
bool Node::operator <(const Node& other) const{
    return this->freq<other.freq;
}
 Node* Node::get_left() const{
    return left;
}
 Node* Node::get_right() const{
    return right;
}
unsigned char Node::get_char()const{
    return myself;
}
bool Node::is_leaf()const{
    return !left && !right;
}
void Huffman:: set_root(Node* n){
    root = n;
}
Node* Huffman::build_tree(long long int freq[]){
    
    priority_queue<Node*,vector<Node*>,CompareNodes> pq;
    for(int i = 0;i<256;i++){
        unsigned char ichar = i;
        if(freq[ichar]>0){
            Node* node = new Node(ichar,freq[ichar],nullptr,nullptr);
             //Node node(i, freq[ichar], nullptr, nullptr);
            pq.push(node);
            //delete node;
        }
        
    }
    while(pq.size()>1){
        Node* l = pq.top();
        pq.pop();
        Node* r =pq.top();
        pq.pop();
       //Node parent(-1, l.get_freq() + r.get_freq(), &l, &r);
        Node* parent= new Node(-1,l->get_freq()+r->get_freq(),l,r);
        pq.push(parent);
        //delete parent;
    }
    return pq.top();
}
void Huffman:: build_code(map<unsigned char,string>& huffmancodes,Node* n,string s){
    if(!n->is_leaf()){
        Node* l = n->get_left();
        Node* r = n->get_right();
        build_code(huffmancodes,l,s+'0');
        build_code(huffmancodes,r,s+'1');
    }
    else{
        huffmancodes[n->get_char()] = s; 
    }
}
void compression(string infilename,string outfilename){
     ifstream file(infilename,ios::binary);
    vector<unsigned char> text;
    string line;
    unsigned char c;
    long long int freq[256]={0};
    if(!file.is_open()){
        cout<<"can't open file"<<endl;
        return;
    }
    //while(getline(file,line)){
        //text += line;
        //text += '\n';
    //}
    size_t text_size = 0;
    while(file.read((char*)&c,sizeof(c))){
        text.push_back((unsigned char)c);
        text_size++;
    }
    file.close();
    
    for(size_t i = 0;i<text_size;i++){
        freq[text[i]]++;
    }
    Huffman huf;
    map<unsigned char,string> huffmancodes;
    Node* root = huf.build_tree(freq);
    huf.set_root(root);
    huf.build_code(huffmancodes,root,""); //以上为获得huffmancodes
    ofstream outputfile(outfilename.c_str(),ios::out|ios::binary);
    //size_t n = text_size;
    outputfile<<huffmancodes.size()<<'\n';
    for (auto it = huffmancodes.begin(); it != huffmancodes.end(); ++it) {
        outputfile << it->first << it->second << '\n';
    } //把Huffmancodes写入压缩文件                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                     
    string buffer;
    char bit;
    size_t i = 0;
    while (i<text_size) {
        buffer += huffmancodes[text[i]];
        while (buffer.length() >= 8) {
            bitset<8> bits(buffer.substr(0, 8));
            outputfile.put(char(bits.to_ulong()));
            buffer = buffer.substr(8);
        }
        i++;
    }

    // Write the remaining bits in the buffer
   
    if (!buffer.empty()) {
        bitset<8> bits(buffer);
        outputfile.put(char(bits.to_ulong()));
    }    
    outputfile.close();
}
void expand(string infilename,string outfilename){
    ifstream inputfile(infilename.c_str(),ios::binary);
    ofstream outputfile(outfilename.c_str(),ios::out|ios::binary);
    int size_huffmancodes = 0;
    string temp;
    getline(inputfile,temp);
    size_huffmancodes = atoi(temp.c_str());
    map<string,char> huffmancodes;
    string code;
    for(int i = 0;i<size_huffmancodes;i++){
        getline(inputfile,code);
        if(code == ""){
            getline(inputfile,code);
            huffmancodes[code.substr(0)] = '\n';
            continue;
        }
        huffmancodes[code.substr(1)] = code[0];

    } //得到huffmancodes
       string text;
       char c;
    while (inputfile.get(c)) {
        bitset<8> bits(c);
        text += bits.to_string();
    }
    code = "";
    int text_size = text.size();
    for(int i = 0;i<text_size;i++){
        code += text[i];
        if(huffmancodes.find(code) != huffmancodes.end()){
            outputfile<<huffmancodes[code];
            code = "";
        }
    }
    
}
