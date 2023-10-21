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
vector<string> split(string words){
    int n = words.length();
    vector<string> tokens;
    string token;
    for(int i =0;i<n;i++){
        if((words[i]=='.' || words[i] == ' ' || words[i] == '(' || words[i] == ')' || words[i] == '\"') && token != ""){
            tokens.push_back(token);
            token.clear();
        }
        else{
            token += words[i];
        }
    }
    return tokens;
}
vector<pair<int,string>> kmp(string data,vector<string> tokens,vector<pair<int,string>>top_k){
    int tokens_size = tokens.size(); 
    int l = 0;
    for(int i = 0;i<tokens_size;i++){
        string subdata = tokens[i];
    
        vector<pair<string,int> > words;
        int row = 1;
        vector<int> rows;
        int sub_data_size = subdata.length();
        int next[sub_data_size+1];
        int nextval[sub_data_size+1];
        next[0] = 0;
        next[1] = 0;
        nextval[0] = 0;
        nextval[1] = 0;
        for(int i = 0;i<sub_data_size;i++){
            int maximum_common_element_length = 0;
            for(int j = 0;j<i;j++){
                if(subdata.substr(i,j+1) == subdata.substr(i-j,j+1)){
                    maximum_common_element_length++;
                }
            }
            next[i+1] = maximum_common_element_length;
        }
        for(int i = 2;i<sub_data_size;i++){
            if(subdata[next[i] == subdata[i]]){
                nextval[i] = next[next[i]];
            }
            else{
                nextval[i] = next[i];
            }
        }
        int count = 0;
        int n = data.length();
        for(int i = 0;i<n;i++){
            if(data[i] == '\n'){
                row++;
            }
            int index = 0;
            int flag = 0;
            for(int j = 0;j<sub_data_size;j++){
                if(data[i+j] != subdata[j]){
                    index = j;
                    flag = 1;
                    break;
                }
            }
            if(flag == 0){
                count++;
                rows.push_back(row);
            }
        i += index-nextval[index+1];
    }
        int check =0 ;
        for(int i = 0;i<top_k.size();i++){
            if(top_k[i].second == subdata){
                top_k[i].first++;
                check = 1;
                break;
            }
        }
        if(check == 0){
            top_k.push_back(make_pair(1,subdata));
        }
    }
    return top_k;
}
void display(vector<pair<int,string>> top_k,map<string,vector<int>> rows,int k){
    for(int i = 0;i<k;i++){
        cout<<"word:\""<<top_k[i].second<<"\" number_of_occurrences:"<<top_k[i].first<<" rows:";
        for(int j = 0;j<rows[top_k[i].second].size();j++){
            cout<<rows[top_k[i].second][j]<<" ";
        }
        cout<<endl;
    }
}
