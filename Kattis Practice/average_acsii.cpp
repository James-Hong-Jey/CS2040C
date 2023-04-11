#include <string>
#include <iostream>
using namespace std;

int main(){
    string input;
    int total;
    int denom;
    cin >> input;
    
    /*
    if(input[0] != '\0'){ 
        for(int i = 0; input[i] != '\0'; i ++)  {
            denom++;
            total += int(input[i]);
        }
    }
    */
    cout << char(total/denom);
}