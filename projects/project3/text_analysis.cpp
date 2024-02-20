#include"function.h"

int main(){
    char mode;
    cout<<"choose your mode(A/B):A.find topK words B.find specific words ";
    cin>>mode;
    
    ifstream file("D:/vscode_projects/Data_Structures/projects/project3/example.text");
    if (!file.is_open())
    {
    cout << "can't open file" << endl;
        return 1;
    }
    string words;
    string line;
    int row = 0;
    map<string,vector<int>> rows;
    vector<string> tokens;
    vector<pair<int,string>> top_k;
    while (getline(file, line)) 
    {
         tokens = split(line);
         top_k = kmp(words,tokens,top_k);
         row++;
         for(int i = 0;i<tokens.size();i++){
            rows[tokens[i]].push_back(row);
         }
    }
    file.close();
    if(mode == 'A'){
        sort(top_k.begin(),top_k.end(),[](const pair<int,string>&a,const pair<int,string>& b){
            return b.first<a.first;
        });
            int k;
        cout<<"input k: ";
        cin>>k;
        display(top_k,rows,k);
    }
    else{
        string specific_word;
        cout<<"input your word: ";
        cin>>specific_word;
        int flag = 0;
            for(int j = 0;j<top_k.size();j++){
                if(specific_word== top_k[j].second){
                	flag = 1;
                    cout<<"word:\""<<top_k[j].second<<"\" number_of_occurrences:"<<top_k[j].first<<" rows:";
                    for(int i = 0;i<rows[top_k[j].second].size();i++){
                        cout<<rows[top_k[j].second][i]<<" ";
                    }
                }
            }
            if(flag == 0){
            	cout<<"no such word!";
			}
        
    }
    
    
    return 0;
}
