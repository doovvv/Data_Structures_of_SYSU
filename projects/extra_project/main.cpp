#include"Huffman.h"
int main(int argc,char* argv[]){
    string op;
    
        op = argv[1];
        if(op == "exit"){ //输入exit退出程序
            return 0;
        }
        else if(op == "zip" || op == "minidata_zip"){
            string infilename;
            string outfilename;
            infilename =argv[2];
            outfilename = argv[3];
            int start = 0;
            int in_or_out = 0;
            if(op == "zip"){
                compression(infilename,outfilename,0);
            }
            else if(op == "minidata_zip"){
                compression(infilename,outfilename,1);
            }
        }
        else if(op == "unzip" || op == "minidata_unzip"){
            string infilename;
            string outfilename;
            infilename =argv[2];
            outfilename = argv[3];
            int start = 0;
            int in_or_out = 0;
            if(op == "unzip"){
                expand(infilename,outfilename,0);
            }
            else if(op == "minidata_unzip"){
                expand(infilename,outfilename,1);
            }
        }
            
}