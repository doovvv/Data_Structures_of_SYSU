#include"Huffman.h"
#include<cmath>
void interpolation(const string& inputFileName, const string& outputFileName,int new_width,int new_height) {
    ifstream inFile(inputFileName, ios::binary);
    if (!inFile.is_open()) {
        cerr << "Unable to open the input file.\n";
        return;
    }
    // 读取文件头
    string fileType;
    int width, height, maxColorValue;
    inFile >> fileType >> width >> height >> maxColorValue;                                          
    vector<vector<vector<int>>> Data;
    vector<vector<int>> row;
    for (int i = 0; i <height; ++i) {
        //Data[i].resize(height);
        for(int j = 0;j<width;j++){        
            int red, green, blue;
            inFile >> red >> green >> blue;
            vector<int> dot = {red,green,blue};        
            row.push_back(dot);
        }
        Data.push_back(row);
        row.clear();
    }
    vector<vector<vector<int>>> newData;
    vector<vector<int>> new_row;
    for(int i = 0;i<new_height;i++){
        for(int j = 0;j<new_width;j++){
            double old_x = (double)((double)j)*width / new_width;
            double old_y = (double)((double)i)*height /new_height;
            int x1,y1,x2,y2;
            x1 = floor(old_x);
            y1 = floor(old_y);
            x2 = x1 ==width-1?width-1:x1+1;
            y2 = y1 ==height-1?height-1:y1+1;
            vector<int> dot;
            for(int c = 0;c<3;c++){
                if(x1 == width-1 && y1 != height-1){
                    dot.push_back(Data[y1][x1][c]*(y2-old_y)+Data[y2][x1][c]*(old_y-y1));
                }
                else if(x1 != width-1 && y1 == height-1){
                    dot.push_back(Data[y1][x2][c]*(old_x-x1)+Data[y1][x1][c]*(x2-old_x));
                }
                else if(x1 == width-1 && y1 == height-1){
                    dot.push_back(Data[x1][y1][c]);
                }
                else{
                    dot.push_back(Data[y1][x1][c]*(x2-old_x)*(y2-old_y)+Data[y2][x1][c]*(x2-old_x)*(old_y-y1)+Data[y1][x2][c]*(old_x-x1)*(y2-old_y)+Data[y2][x2][c]*(old_x-x1)*(old_y-y1));
                }
                  
            }
            new_row.push_back(dot);
        }
        newData.push_back(new_row);
        new_row.clear();
    }
    ofstream outFile(outputFileName, ios::out);
    if (!outFile.is_open()) {
        cerr << "Unable to open the output file.\n";                          
        return;
    }
    // 写入文件头
    outFile << fileType<<"\n" << new_width << " " << new_height << "\n" << maxColorValue << "\n";
    // 写入灰度图像数据
    for(int i = 0;i<new_height;i++){
        for(int j = 0;j<new_width;j++){
            for(int c = 0;c<3;c++){
                outFile<<to_string(newData[i][j][c])<<" ";
            }
        }
    }
    outFile.close();
}