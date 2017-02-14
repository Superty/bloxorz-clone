#include <bits/stdc++.h>
using namespace std;
using ll = long long;

class X {
  public:
	int y;
	X() {
		y = -1;
		cerr << "default\n";
	}
	// X(X const & rhs) :
	// 	y(rhs.y)
	// {
	// 	cerr << "copy\n";
	// }
	X(X && rhs) :
		y(rhs.y)
	{
		cerr << "move\n";
	}
};

void foo(int c, const vector<int> &x) {
	if(c == 0) return;
	else foo(c - 1, x);
	// cerr << "copy" << "\n";
}
// void foo(int&& x) {
// 	cerr << "move " << x << "\n";
// }

vector<int> make() {
	vector<int> x = vector<int>(1000000,2);
	cerr << "made\n";
	return x;
}

int main() {
	ios::sync_with_stdio(false);
	// cin.tie(NULL);

	// f(3);
	// X a;
	// cerr << a.y << '\n';
	// // X b(a);
	// // cerr << b.y << '\n';
	// X c = X(X());
	// cerr << c.y << '\n';

	// int x = 1;
	foo(100000, make());
	cerr <<"done\n";
	// for(int i = 0; i <= 1000000; i++) {
	// 	foo(make());
	// }
	// foo(1);

	return 0;
}