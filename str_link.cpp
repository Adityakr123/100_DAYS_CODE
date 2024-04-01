#include<string>
#include<iostream>
#include<stdio.h>
using namespace std;
class Node{
public:
    string str;
    Node* next;
    Node(string val){
        this->str=val;
        this->next=NULL;
    }

};
string reverse(string a){
    int i=0;
    while(a[i]==' '){
        
    }
}
int main(){
    string a;
    getline(cin,a);
    string b=reverse(a);
    for(int i=0;i<b.length();i++){
        cout<<b[i];
    }
    return 0;
}