#include"hash.h"
   std::string chineseNames[30] = {
        "ZhangXiaoSan", "LiXiaoSi", "WangXiaoWu", "ZhaoLiu", "QianQi",
        "SunMeiHua", "LiXinYang", "WangJingLian", "ZhouYiMin", "WangShi",
        "FengYi", "ChenEr", "ChuSan", "ZhuSi", "QinWu",
        "HanLiu", "TangQi", "SongBa", "YuanJiu", "CaoShi",
        "WeiShi", "ShuYi", "XiaEr", "GaoSan", "XuSi",
        "LiangWu", "LiuHanZhe", "JinQi", "DongChunJiang", "MoJiu"
    };
int main() {
    int mode;
    string choose;
    cout<<"how to deal with collision:"<<endl<<"A.preudo_random probing"<<endl<<"B.linear probing"<<endl<<"C.square proning"<<endl<<"D.chaining address"<<endl;
    cin>>choose;
    if(choose == "A" || choose == "a"){
        mode = 1;
    }
    else if(choose == "B" || choose == "b"){
        mode = 2;
    }
    else if(choose == "C" || choose == "c"){
        mode = 3;
    }
    else if(choose == "D" || choose == "d"){
        mode = 4;
    }
    vector<vector<Hash>> hash_table(50,vector<Hash>(1));
    create_hash_table(hash_table,chineseNames,mode);
    cout<<"A.search key"<<endl<<"B.display key and name"<<endl<<"C.display hash table"<<endl<<"D.exit"<<endl;
    while(1){
        cout<<"choose your operation:";
        string op;
        cin>>op;
        if(op == "A" || op == "c"){
            search_name(hash_table,mode);
        }
        else if(op == "C" || op == "c"){
            display_table(hash_table);
        }
        else if(op == "B" || op == "b"){
            display_name_and_key(chineseNames);
        }
        else{
            break;;
        }
    }
}