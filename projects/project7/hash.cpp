#include"hash.h"
int get_key(string name){
    int sum = 0;
    for(int i = 0;i<name.length();i++){
        sum += name[i]-'A';
    }
    return sum;
}
void create_hash_table(vector<vector<Hash>>& hash_table,string chineseNames[],int mode){
    for(int i = 0;i<30;i++){
        int k = get_key(chineseNames[i]);
        PseudoRandomGenerator prg(k,13,17,49);
        int address = k % 50;
        int temp_address = address;
        if(mode == 1 || mode == 2 || mode == 3){ //mode 1,2,3 only need one-dimension vector
            if(hash_table[address][0].sum == 0){ //no collision
                hash_table[address][0].sum = 1;
                hash_table[address][0].name = chineseNames[i];
                hash_table[address][0].key = k;
            }
            else{ //collison
                int count = 1;
                    while(1){
                        if(mode == 1){
                            int rand_num = prg.getNextRandom();
                            temp_address += rand_num;
                            temp_address %= 50;                    
                        }
                        else if(mode == 2){
                            temp_address = (temp_address+1)%50;
                        }
                        else if(mode == 3){
                            temp_address = (count % 2 == 1)?temp_address+((count+1)/2)*((count+1)/2):temp_address-((count+1)/2)*((count+1)/2);
                            temp_address %= 50;
                        }
                        count++;
                        if(hash_table[temp_address][0].sum == 0){
                            hash_table[temp_address][0].name = chineseNames[i];
                            hash_table[temp_address][0].key = k;
                            hash_table[temp_address][0].sum = count;
                            break;
                        }
                    }
            }
        }
        else if(mode == 4){
            if(hash_table[temp_address][0].sum == 0){
                hash_table[temp_address][0].name = chineseNames[i];
                hash_table[temp_address][0].key = k;
                hash_table[temp_address][0].sum = 1;
            }
            else{
                Hash temp_hash;
                temp_hash.key = k;
                temp_hash.name = chineseNames[i];
                temp_hash.sum = hash_table[address].back().sum+1;
                hash_table[address].push_back(temp_hash);
            }
        }
    }
}
void search_name(vector<vector<Hash>>& hash_table,int mode){
    string name;
    cout<<"input the name: ";
    cin>>name;
    int k = get_key(name);
    int address = k % 50;
    int temp_address = address;
    if(mode == 1 || mode == 2||mode == 3){
        PseudoRandomGenerator prg(k,13,17,49);
        if(hash_table[address][0].name == name){
            cout<<"name:"<<name<<"  "<<"key:"<<hash_table[address][0].key<<"  "<<"search_length:"<<hash_table[address][0].sum<<"  "<<"address:"<<address<<endl;
        }
        else{
            int count = 1;
            while(1){
                if(hash_table[temp_address][0].sum == 0){
                    cout<<"don't find the name"<<endl;
                    break;
                }
                if(mode == 1){
                    temp_address += prg.getNextRandom();
                    temp_address %= 50;            
                }
                else if(mode == 2){
                    temp_address = (temp_address+1) %50;
                }
                else if(mode == 3){
                    temp_address = (count % 2 == 1)?temp_address+((count+1)/2)*((count+1)/2):temp_address-((count+1)/2)*((count+1)/2);
                    temp_address %= 50;
                }
                count++;
                if(hash_table[temp_address][0].name == name){
                    cout<<"name:"<<name<<"  "<<"key:"<<hash_table[temp_address][0].key<<"  "<<"search_length:"<<hash_table[temp_address][0].sum<<"  "<<"address:"<<temp_address<<endl;
                    break;
                }        
            }

        }
    }
    else if(mode == 4){
        int flag = 0;
        for(int i = 0;i<hash_table[address].size();i++){
            if(hash_table[address][i].name == name){
                cout<<"name:"<<name<<"  "<<"key:"<<hash_table[temp_address][0].key<<"  "<<"search_length:"<<hash_table[temp_address][0].sum<<"  "<<"address:"<<temp_address<<endl;
                flag = 1;
                break;
            }
        }
        if(flag == 0){
            cout<<"don't find the name"<<endl;
        }
    }
}
void display_table(vector<vector<Hash>>& hash_table){
    int count = 0;
    double asl;
    cout<<"\naddress\tkey\t\tsearch_length\tname\n";
    for(int i = 0;i<50;i++){
        cout<<i;
        cout<<"\t"<<hash_table[i][0].key;
        cout<<"\t\t"<<hash_table[i][0].sum;
        cout<<"\t\t"<<hash_table[i][0].name;
        for(int j=1;j<hash_table[i].size();j++){
            cout<<"->"<<"("<<hash_table[i][j].sum<<")"<<hash_table[i][j].name;
        }
        cout<<endl;
        for(int j = 0;j<hash_table[i].size();j++){
            count+= hash_table[i][j].sum;
        }
    }
    asl = (double)count/30;
    cout<<"average search length(ASL(30)): "<<asl<<endl;

}
void display_name_and_key(string chineseNames[]){
    cout<<"\tkey"<<"\t\tname"<<endl;
    for(int i = 0;i<30;i++){
        cout<<"\t"<<get_key(chineseNames[i])<<"\t\t"<<chineseNames[i]<<endl;
    }
    cout<<endl;
}