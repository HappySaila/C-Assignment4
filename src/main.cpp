#include<iostream>

int main(int argc, char const *argv[]){
    using namespace std;

    if (argv[1] == "-a"){
        cout << "adding images" << endl;
    }
    for (int i = 0; i < argc; i++){
        cout << argv[i] << endl;
    }
}