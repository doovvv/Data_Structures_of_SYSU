
#include"CImg-3.3.1\CImg.h"
#include<iostream>
#include"Huffman.h"
using namespace std;
using namespace cimg_library;
int main() 
{
    cout<<"you can choose:"<<endl<<"A:open the picture"<<endl<<"B:compress the picture"<<endl<<"C:unzip the picture"<<endl<<"D:change into gray picture"<<endl<<"E:scale size"<<endl<<"F:exit"<<endl;
    while(1){
        string op;
        cout<<"input options: ";
        cin>>op;
        if(op == "A" || op == "a"){
            string name;
            cout<<"the name of picture you want open: ";
            cin>>name;
            CImg<unsigned char> img(name.c_str());
            img.display();
        }
        else if(op == "B" || op == "b"){
            string inputname,outputname;
            cout<<"input the infilename and outfilename: ";
            cin>>inputname>>outputname;
            compression(inputname,outputname);
        }
        else if(op == "C" || op == "c"){
            string inputname,outputname;
            cout<<"input the infilename and outfilename: ";
            cin>>inputname>>outputname;
            expand(inputname,outputname);
        }
        else if(op == "D" || op == "d"){
            string inputname,outputname;
            cout<<"input the infilename and outfilename: ";
            cin>>inputname>>outputname;
            convertToGray(inputname,outputname);
        }
        else if(op == "E" || op == "e"){
            string inputname,outputname;
            int width,height;
            cout<<"input the infilename and outfilename: ";
            cin>>inputname>>outputname;
            cout<<"input the new width and height: ";
            cin>>width>>height;
            interpolation(inputname,outputname,width,height);
            CImg<unsigned char> img(outputname.c_str());
            CImgDisplay dis(img);
            dis.resize(width,height);
            while (!dis.is_closed()) {
                dis.wait();
            }
        }
        else{
            break;
        }
    } 
 return 0; 
}
