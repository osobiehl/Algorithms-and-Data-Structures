//
// Created by Jose Ignacio Biehl on 11.02.20.
//

#ifndef A2_6_ACCESS_H
#define A2_6_ACCESS_H


class Access {
public:
	void activate(unsigned int code);
	void deactivate(unsigned int code);
	bool isactive(unsigned int code) const;
	Access(int n);
	~Access();
	int size;
private:
	bool* hashtable;
// add properties and/or method(s) if necessary

};


#endif //A2_6_ACCESS_H
