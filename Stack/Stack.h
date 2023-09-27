template<class T>
class Stack{
    private:
        T* data;
        int size;
        int top;
    public:
        Stack(int s = 100);
        ~Stack();
        T get_top();
        bool push(T t);
        bool pop();
        bool isempty();
};
