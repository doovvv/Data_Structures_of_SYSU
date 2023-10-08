template<typename T>
class Stack{
    private:
        T* data;
        int size;
        int top;
    public:
        Stack(int s,int t);
        ~Stack();
        T get_top();
        bool push(T t);
        bool pop();
        bool is_empty();

}
