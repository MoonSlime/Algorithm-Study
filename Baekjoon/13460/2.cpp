#include <iostream>

using namespace std;

typedef struct _PAIR {
    int x,y;

    _PAIR():x(1),y(2){}

    _PAIR(int _x,int _y):x(_x),y(_y) {}

    int print() {
        cout << x << ',' << y << endl;
        return x+y;
    }
}PAIR;

class PAIR1 {
public:
    int x,y;

    void setXY(int _x, int _y) {
        x = _x;
        y = _y;
    }
};

int main(void) {
    /**
    PAIR p1,p2;

    cout << &p2<<endl;
    p2 = PAIR(3,4);
    cout << &p2<<endl;

    cout << p1.print()<<endl;
    cout << p2.print()<<endl;
    **/

    PAIR1 p1;
    p1.setXY(1,2);
    cout << p1.x << p1.y <<endl;

    return 0;
}
