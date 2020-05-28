#include <iostream>
#include "Access.h"

using namespace std;

int main() {
	Access security(10000);
	security.activate(1234);
	security.activate(9999);
	security.activate(9876);
	int code;
	while (1){
		cin>>code;
		if (security.isactive(code))
			break;
		cout<<"invalid code! enter again: "<<endl;
	}
	cout<<"access granted!\n";
	security.deactivate(code);
	security.deactivate(9999);
	security.activate(1111);
	while (1){
		cin>>code;
		if (security.isactive(code))
			break;
		cout<<"invalid code! enter again: "<<endl;
	}
	cout<<"access granted!\n";
	return 0;
}
