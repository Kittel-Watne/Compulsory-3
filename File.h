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
	/// <summary>
	/// constructor the only information that needs to be given is the name
	/// </summary>
	/// <param name="name">name of file</param>
	File(std::string name) {
		File::name = name;
		File::createDate = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
		File::size = rand() % 100;
	}
	/// <summary>
	/// overload of basic constructor to create a file without any userinput
	/// </summary>
	File() {
		File::createDate = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
		File::size = rand() % 100;
	}
	/// <summary>
	/// finds the name of the file
	/// </summary>
	/// <returns>name of file</returns>
	std::string getName() {
		return name;
	}
	/// <summary>
	/// finds the date of creation of the file
	/// </summary>
	/// <returns>date of creation</returns>
	time_t getTime() {
		return createDate;
	}
	/// <summary>
	/// finds the size of the file
	/// </summary>
	/// <returns>size of the file</returns>
	int getSize() {
		return size;
	}
	/// <summary>
	/// prints the date of creation cleanly and orderly
	/// </summary>
	void showTime() {
		std::cout << std::put_time(localtime(&createDate), "%F %T") << std::endl;
	}
	/// <summary>
	/// prints all the information of the file
	/// </summary>
	void printFile() {
		std::cout << name << " has a size of " << size << "MB and was created " << std::put_time(localtime(&createDate), "%F %T") << "\n";
	}
};