#include"Huffman.h"
void convertToGray(const string& inputFileName, const string& outputFileName) {
    ifstream inFile(inputFileName, ios::binary);
    if (!inFile.is_open()) {
        cerr << "Unable to open the input file.\n";
        return;
    }
    // 读取文件头
    string fileType;
    int width, height, maxColorValue;
    inFile >> fileType >> width >> height >> maxColorValue;                                          
    // 创建一个灰度图像数据存储向量
    vector<unsigned char> grayData(width * height);
    // 读取彩色图像数据并转换为灰度
    for (int i = 0; i < width * height; ++i) {
        int red, green, blue;
        inFile >> red >> green >> blue;        
        // 灰度转换公式
        unsigned char grayValue = static_cast<unsigned char>(0.299 * red + 0.587 * green + 0.114 * blue);
        // 存储灰度值
        grayData[i] = grayValue;
    }
    inFile.close();
    // 写入灰度图像数据到新的 PPM 文件
    std::ofstream outFile(outputFileName, ios::out);
    if (!outFile.is_open()) {
        std::cerr << "Unable to open the output file.\n";
        return;
    }
    // 写入文件头
    outFile << "P2\n" << width << " " << height << "\n" << maxColorValue << "\n";
    // 写入灰度图像数据
    for (int i = 0; i < width * height; ++i) {
        outFile<<to_string(grayData[i])<<" ";
    }
    outFile.close();
}