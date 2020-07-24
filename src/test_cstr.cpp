#include <string>
#include <iostream>

int main(){
    int i{1};
    // char 1 byte 
    // int is 4 byte let's assign 6 as max
    std::string x = std::to_string(1)+std::to_string(2);
    std::cout<< x;
}