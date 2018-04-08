#include <iostream>

using namespace std;

int main(int argc, char* argv[]) {
    for(int i = 1; i < argc; ++i) {
        cout << atoi(argv[i])*2 << endl;
    }
}