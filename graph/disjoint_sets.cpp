#include<vector>
using namespace std;
class DisjSet{
    private:
        vector<int> parent;
    public:
        DisjSet(int max_size){
            parent.resize(max_size);
            for(int i = 0;i<max_size;i++){
                parent[i] = i;
            }
        }
        int find(int x){
            return (parent[x] == x)?x:find(parent[x]);
        }
        void to_union(int x1,int x2){
            parent[find(x1)] = find(x2);
        }
        bool is_same(int x1,int x2){
            return find(x1) == find(x2);
        }
};

