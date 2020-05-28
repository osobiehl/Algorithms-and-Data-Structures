#include <iostream>
#include <fstream>
#include <map>
using namespace std;
int main() {
	map<string, string> container;
	ifstream in;
	in.open("data.txt");
	if (!in)
		throw new runtime_error("no input file!");
	string name, birthday;

	while(!in.eof()){
		getline(in, name);
		name[name.length()] = '\0';
		getline(in, birthday);
		birthday[birthday.length()] = '\0';
		container[name] = birthday;
	}
	map<string, string>::iterator it;
	while(1){
		cout<<"enter a name to query, END will end the program: ";
		getline(cin, name );
		name[name.length()] = '\0';
		if (name == "END")
			break;
		//iterator to check for name/birthday
		it = container.find(name);
		if (it == container.end()){
			cout<<"Name not found!\n";
		}
		else{

			cout<<"birthday found for "<<name<<": "<<container[name]<<endl;
		}
	}
	return 0;
}
