#include<iostream>
#include<string>
#include<algorithm>
using namespace std;
int main(){
    char ch = '5';
 
    // Subtracting 48 will produce desired results
    cout << int(ch) << "\n";
 
    // Also subtracting '0' will result in same output
    cout << int(ch - '0');
    return 0;
    
  
}
Get-ChildItem -Recurse -Include *.js,*.jsx,*.ts,*.tsx | ForEach-Object {
    $lineCount = (Get-Content $_.FullName).Count
    "$($_.FullName),$lineCount"
} > component_document.csv
