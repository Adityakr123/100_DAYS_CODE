#include<iostream>
#include<stack>
using namespace std;
stack<int> pushAtBottom(stack<int>& myStack, int x) 
{
    // Write your code here
    int arr[myStack.size()];
    int arr_size=myStack.size();
   for(int count =0 ;count<arr_size;count++){
      arr[count]=myStack.top();
    //   cout<<arr[count];
      myStack.pop();   
   }
   myStack.push(x);
   for(int i=arr_size-1;i>=0;i--){

    myStack.push(arr[i]);
    
   }
   return myStack;
}
// void deleteMiddle(stack<int>&inputStack, int N){
	
//    // Write your code here
//    int middle=0;
//    if(N%2==0){
//     middle= N/2;
//    }
//    else{
//     middle=(N/2)+1;
    
//    }
//    int arr[middle-1];
   
//    int count=1;
//    while(count<middle){
//       arr[count-1]=inputStack.top();
//       cout<<arr[count-1];
//       inputStack.pop();
//       count++;
      
//    }
//    inputStack.pop();
//    for(int i=middle-2;i>=0;i--){
//     inputStack.push(arr[i]);
//     cout<<arr[i]<<endl;
    
//    }
   
// }
void printStack(stack<int> s) {
    while (!s.empty()) {
        cout << s.top() << " ";
        s.pop();
    }
    cout<< endl;
}
int main(){
    stack<int> stack;
    stack.push(5);
    stack.push(10);
    stack.push(3);
    // stack.push(4);
    // stack.push(5);
    pushAtBottom(stack,2);
    printStack(stack);
    // cout<<"adi";

}