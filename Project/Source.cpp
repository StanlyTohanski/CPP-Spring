#include<iostream>
using namespace std;

void g() {}

int main() {
	int error;
	int b;
	int c; /// web comment
//<<<<<<< HEAD
	int d;   /// new master comment
	int branch;
//=======
	d = 5;  // master comment
//>>>>>>> master
	c = 5;
	int new_branch;
	return 0;
}
