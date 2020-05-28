#include <iostream>
#include "Access.h"

using namespace std;

int main() {
	Access security(10000);
	security.activate(1234, 1);
	security.activate(9999, 5);
	security.activate(9876, 5);
	int code;
	while (1){
		cin>>code;
		if (code < security.getSize() && security.isactive(code, 5) )
			break;
		cout<<"invalid code! enter again: "<<endl;
	}
	cout<<"access granted!\n";
	security.deactivate(code);
	security.activate(9999, 8);
	security.activate(1111, 7);
	while (1){
		cin>>code;
		if (security.isactive(code, 7))
			break;
		cout<<"invalid code! enter again: "<<endl;
	}
	cout<<"access granted! door is open\n";
	return 0;
}

