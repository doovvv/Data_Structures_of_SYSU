#include<iostream>
template <typename T> 
struct QueueNode
{
	T val;
    QueueNode<T>* next;
    QueueNode(T v,QueueNode<T>* n = nullptr){
        val = v;
        next = n;
    }
};

template <typename T> 
class Queue {
public:
	Queue(){
        head = new QueueNode<T>(0);
        tail = head;
        cnt = 0;
    }   // construct an empty queue
	~Queue(){
        QueueNode<T>* node = head;
        while(node){
            QueueNode<T>* post = node->next;
            delete node;
            node = post;
        }
    } // destructor
	
	Queue(const Queue &rhs){
        head = new QueueNode<T>(0);
        QueueNode<T>* node = head;
        QueueNode<T>* copy  = rhs.head;
        for(int i = 0;i<rhs.cnt;i++){
            QueueNode<T>* node_copy = new QueueNode<T>(copy->next->val);
            node->next = node_copy;
            node = node->next;
            copy = copy->next;
        }
        tail = node;
        cnt = rhs.cnt;
    }  //拷贝构造函数 
	const Queue & operator = (const Queue &rhs){
        head = new QueueNode<T>(0);
        QueueNode<T>* node = head;
        QueueNode<T>* copy  = rhs.head;
        for(int i = 0;i<rhs.cnt;i++){
            QueueNode<T>* node_copy = new QueueNode<T>(copy->next->val);
            node->next = node_copy;
            node = node->next;
            copy = copy->next;
        }
        tail = node;
        cnt = rhs.cnt;
        return *this;
    } //操作符重载 
	
	bool empty() const{
        return cnt == 0;
    }
	int size() const{
        return cnt;
    }
	bool push(const T &x){
        //QueueNode<T>* node = head;
        //for(node;node->next;node=node->next){
        //}
        QueueNode<T>* new_tail = new QueueNode<T>(x);
        tail->next = new_tail;
        tail = new_tail;
       // std::cout<<tail->val;
        cnt++;
        return true;
    }	//正常入队则返回true，若无空闲内存则返回false
	bool pop(){
        if(empty()){
            return false;
        }
        else{
            QueueNode<T>* node = head->next->next;
            if(tail == head->next){
                tail = head;
            }
            //for(node;node->next->next;node = node->next);
            delete head->next;
            head->next = node;
            cnt--;
        }
        return true;
    }	//正常出队则返回true，队内无元素则返回false
	const T & front() const{
        return head->next->val;
    }
private:
	QueueNode<T> *head, *tail;
	int cnt;
};
