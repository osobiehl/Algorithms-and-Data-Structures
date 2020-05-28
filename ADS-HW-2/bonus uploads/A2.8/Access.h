//
// Created by Jose Ignacio Biehl on 11.02.20.
//

#ifndef A2_8_ACCESS_H
#define A2_8_ACCESS_H


class Access {
public:
	void activate(unsigned int code, unsigned int level);
	void deactivate(unsigned int code);
	bool isactive(unsigned int code, unsigned int level) const;
	Access(int n);
	int getSize() const;
	~Access();
private:
	int* hashmap;
	int size;
// add properties and/or method(s) if necessary
};


#endif //A2_8_ACCESS_H
