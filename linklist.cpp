#include<iostream>
using namespace std;
class Node {
public:
    int data;
    Node* next;
    Node(int data){
        this->data=data;
        this->next=NULL;
    }
    ~Node() {
        int val= this->data;
        if(this->next != NULL){
            delete next;
            next=NULL;
        }

    }
};
void incertAtTail(int data, Node* head ){
    Node* ptr = head;
    while(ptr->next!=NULL){
        ptr=ptr->next;
    }
    Node* temp = new Node(data);
    ptr->next=temp;
    

}
void print(Node* head){
    while(head != NULL){
        cout<<head->data<<" ";
        head=head->next;
    }
}
Node* reverse_knode(int k, Node* head){
    if(head==NULL){
        return NULL;
    }
    Node* forward = NULL;
    Node* prev = NULL;
    Node* curr = head;
    int count=0;
    while(count<k && curr!=NULL){
        forward=curr->next;
        curr->next=prev;
        prev=curr;
        curr=forward;
        count++;
    }
    if(curr!=NULL){

        head->next=reverse_knode(k,curr);
    }
    return prev;

}
int main(){
    Node* node1 = new Node(10);
    Node* head = node1;
    incertAtTail(20,head);
    incertAtTail(30,head);
    incertAtTail(40,head);
    incertAtTail(50,head);
    incertAtTail(60,head);
    incertAtTail(70,head);
    incertAtTail(80,head);
    Node* new_head=reverse_knode(4,head);
    // print(head);
    print(new_head);
    return 0;
}