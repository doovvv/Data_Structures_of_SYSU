template <typename T> class Queue {
public:
      Queue(){
        head = 0;
        tail = 0;
      }   // construct an empty queue
      ~Queue(){} // destructor
      Queue(const Queue &rhs){
        head = rhs.head;
        tail = rhs.tail;
        for(int i = 0;i<100;i++){
            data[i] = rhs.data[i];
        }
      }
      const Queue & operator = (const Queue &rhs){
        head = rhs.head;
        tail = rhs.tail;
        for(int i = 0;i<100;i++){
            data[i] = rhs.data[i];
        }
        return *this;
      }
      bool empty()const{
        return head == tail;
      }
      bool full()const{
        return (tail+1)%100 == head;
      }
      int size()const{
        if(tail<head){
            return tail+100-head;
        }
        return tail-head;
      }
      bool push(const T &x){
        data[tail] = x;
        tail++;
        tail = tail % 100;
        return true;
        }//enqueue
      bool pop(){
        if(empty()){
            return false;
        }
        head++;
        head = head % 100;
        return true;
        }//dequeue
      const T & front()const{
        return data[head];
        }//returns a reference to the front element
private:
    T data[100];
    int head;
    int tail;
 //using a static array of size 100.   

};