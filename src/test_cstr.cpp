#include <string>
#include <iostream>
#include <vector>

int main(){
    std::vector<int> v {1,2,3,4};
    
    auto it = remove_if(v.begin(),v.end(), [](int &i){return (i%2)==0;});
    v.erase(it, v.end());
    for(int i=0;i<v.size(); i++){
       std::cout << v[i] << " ";
    }
}
