template<typename T>
class Node{
    public:
        T value;
        Node<T>* next;
        Node(const T val,Node<T>* node = nullptr):value(val),next(node){}
};
template<typename T>
class Linked_List{
        Node<T>* head;
    public:
        Linked_List(const T& val){
            head = new Node(val);
        }
        ~Linked_List(){
            Node<T>* prev = head;
            while(prev){
                Node<T>* post = prev->next;
                delete prev;
                prev = post; 
            }
        }
        bool isempty(){
            if(head->next == nullptr){
                return true;
            }
            return false;
        }
        void clear(){
            Node<T>* prev = head->next;
            head->next = nullptr;
            while(prev){
                Node<T>* post = prev->next;
                delete prev;
                prev = post; 
            }
        }
        int length(){
            int num = 0;
            Node<T>* node = head->next;
            for(node;node;node = node->next){
                num++;
            }
            return num;
        }
        bool append(const T value){
            Node<T>* node = new Node(value);
            Node<T>* temp = head;
            for(temp;temp->next;temp = temp->next);
            temp->next = node;
            return true;
        }
        bool insert(const int pos,const T value){
            Node<T>* node = new Node(value);
            Node<T>* temp = head;
            for(int i = 0;i<pos;i++){
                temp = temp->next;
            }
            node->next = temp->next;
            temp->next = node;
            return true;
        }
        bool detele(const int pos){
            Node<T>* temp = head;
            for(int i = 0;i<pos;i++){
                temp = temp->next;
            }
            Node<T>* node = temp->next;
            temp->next = node->next;
            delete node;
            return true;
        }
        int getValue(const int pos){
            Node<T>* temp = head;
            for(int i = 0;i<pos;i++){
                temp = temp->next;
            }
            return temp->next->value;
        }
        int getPos(const T value){
            Node<T>* node = head->next;
            int index = 0;
            for(node;node;node = node->next){
                if(node->value == value){
                    return index;
                }
                index++;
            }
            return -1;
        }
        
};