#include <iostream>
#include <vector>

using namespace std;

int main(void) {
    vector<int> v;
    
    for (int i=0; i<5; ++i) {
        v.push_back(i);
    }

    vector<int>::iterator itr = v.begin();

    ++itr;
    ++itr;
    for (;itr != v.end();) {
        v.erase(itr);
    }

    for (int i=0; i<v.size(); ++i) {
        cout << v[i]<<endl;
    }
}
