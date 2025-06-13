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

=IF(A2<=10, 0.1,
 IF(A2<=20, 0.15,
 IF(A2<=40, 0.26,
 IF(A2<=60, 0.5,
 IF(A2<=80, 0.6,
 IF(A2<=120, 0.7,
 IF(A2<=140, 0.8,
 IF(A2<=150, 1,
 IF(A2<=300, 1 + (A2-150)*(1/150),
 IF(A2<=2658, 2 + (A2-300)*(1/2358),
 3))))))))))
