#include "FileTree.h"

using namespace std;

FileTree::FileTree(string root){
	FILE *fpipe;
	string command = "find " + root + " -type f";
	char c = 0;
	
	if(0 == (fpipe = (FILE*)popen(command.c_str(), "r"))){
		perror("popen() failed.");
		exit(1);
	}
	
	int count = 0;
	string result = "";
	while(fread(&c, sizeof c, 1, fpipe)){
		result += c;
		
		if(c == 10)
			count++;
	}
	
	pclose(fpipe);
	
	string files[count];
	int fileIndex = 0;
	
	for(int i = 0; i < result.length(); i++){
		if(result[i] == 10)
			fileIndex++;
		else
			files[fileIndex] += result[i];
		
	}
	
	for(int i = 0; i < count; i++){
		fileMap[files[i]] = readFile(files[i]);
	}
}

string FileTree::getFile(string path){
	return fileMap[path];
}

string FileTree::readFile(string path){
	std::ifstream file;
	
	file.open(path);
	
	string output = "";
	
	fstream::traits_type::int_type x;
	
	while((x = file.get()) != fstream::traits_type::eof())
		output += x;
	
	file.close();
	
	return output;
}