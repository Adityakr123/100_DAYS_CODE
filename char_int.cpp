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

(for /R %f in (*.js *.jsx *.ts *.tsx) do @for /f %%l in ('find /c /v "" "%f"') do @echo %~nxf,%%l) > component_document.csv

@echo File,LineCount > component_document.csv && for /R %f in (*.js *.jsx *.ts *.tsx) do @for /f "tokens=3 delims=:" %l in ('find /c /v "" "%f"') do @echo %~nxf,%l >> component_document.csv

