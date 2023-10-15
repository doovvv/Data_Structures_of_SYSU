#include"function.h"
int main(){
    ifstream file("D:/vscode_projects/Data_Structures/projects/project3/example.text");
    if (!file.is_open())
    {
    cout << "无法打开文件！" << endl;
        return 1;
    }
    string words;
    string line;
    int row = 0;
    map<string,vector<int>> rows;
    vector<string> tokens;
    vector<pair<int,string>> top_k;
    while (getline(file, line)) // 逐行读取文件内容
    {
         tokens = split(line);
         top_k = kmp(words,tokens,top_k);
         row++;
         for(int i = 0;i<tokens.size();i++){
            rows[tokens[i]].push_back(row);
         }
    }
    file.close();
   sort(top_k.begin(),top_k.end(),[](const pair<int,string>&a,const pair<int,string>& b){
        return b.first<a.first;
    });
    int k;
    scanf("%d",&k);
    display(top_k,rows,k);
    return 0;
}