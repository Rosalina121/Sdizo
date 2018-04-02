#pragma once
#include <iostream>

class FileNotFoundException {
public:
	FileNotFoundException() {}
	~FileNotFoundException() {}
	friend std::ostream& operator <<(std::ostream& output, FileNotFoundException ex) {
		output << "\nFileNotFoundException\n";
		return output;
	}

};
