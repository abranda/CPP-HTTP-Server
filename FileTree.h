#include <iostream>
#include <unistd.h>
#include <fstream>
#include <map>

#pragma once

class FileTree {
	private:
		std::map<std::string, std::string> fileMap;
	
		std::string readFile(std::string path);
	public:
		FileTree(std::string root);
	
		std::string getFile(std::string path);
};