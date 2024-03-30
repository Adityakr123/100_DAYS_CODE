#include <iostream>
using namespace std;

void string_reverse(int i, int j, string& String) {
    if (i >= j) {
        return ;
    }
    swap(String[i], String[j]);
    i++;
    j--;
    string_reverse(i, j, String);  // Use i + 1 and j - 1
    return;
}

int main() {
    string name = "aditya";
    int i = 0;
    int j = name.length() - 1;
    string_reverse(i, j, name);
    cout << name;
    return 0;
}
