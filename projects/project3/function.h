#ifndef FUNCTION_H
#define FUNCTION_H

#include<string>
#include<vector>
#include<iostream>
#include <iostream>
#include <fstream>
#include<algorithm>
#include<map>

using namespace std;
vector<string> split(string words);
vector<pair<int,string> > kmp(string data,vector<string> tokens,vector<pair<int,string>>top_k);
void display(vector<pair<int,string>> top_k,map<string,vector<int>> rows,int k);
#endif //FUNCTION_H_