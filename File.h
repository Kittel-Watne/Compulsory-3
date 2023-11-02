#pragma once
#ifndef _IOSTREAM_
#include <iostream>
#endif
#ifndef _CSTDLIB_
#include <cstdlib>
#endif
#ifndef _CTIME_
#include <ctime>
#endif
#pragma warning(disable : 4996)

class File {
private:
	std::string name;
	time_t createDate;
	int size;
public:
	File(std::string name) {
		File::name = name;
		File::createDate = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
		File::size = rand() % 100;
	}
	File() {
		File::createDate = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
		File::size = rand() % 100;
	}

	std::string getName() {
		return name;
	}

	time_t getTime() {
		return createDate;
	}

	int getSize() {
		return size;
	}

	void showTime() {
		std::cout << std::put_time(localtime(&createDate), "%F %T") << std::endl;
	}

	void printFile() {
		std::cout << name << " has a size of " << size << "MB and was created " << std::put_time(localtime(&createDate), "%F %T") << "\n";
	}
};