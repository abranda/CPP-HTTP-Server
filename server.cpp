#include "server.h"

Server::Server(int portNum, std::string directory){
	this->portNum = portNum;
	this->directory = directory;
	this->websiteFiles = new FileTree(directory);
}

int Server::Init(){
	
	host = socket(AF_INET, SOCK_STREAM, 0);
	
	if(host < 0)
		return 1;
		//Error establishing connection.
	
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = htons(INADDR_ANY);
	server_addr.sin_port = htons(portNum);
		
	if(bind(host, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0)
		return 2;
		//Error binding to socket.
	
	this->running = true;
	return 0;
}

void Server::Listen(){
	listen(host, 0);
	size = sizeof(server_addr);
}

bool Server::GetClient(){
	client = accept(host, (struct sockaddr*)&server_addr, &size);
	
	if(client < 0)
		return false;
		//Error accepting client.
	return true;
}

std::string getTag(std::string);
std::string getType(std::string);
std::string readFile(std::string);

void Server::SendPage(){
	
	recv(client, recieve, bufsize, 0);
	std::cout << "New Request:" << std::endl << std::endl << recieve << std::endl << std::endl << std::endl;
	
	std::string tag = getTag(recieve);
	std::string type = getType(tag);
	
	//if(tag == "/mail_sent"){
		//std::cout << "I AM IN THE IF STATEMENT!" << std::endl;
		//tag = getTag("GET /contact.html HTTP/1.1");
		//type = getType(tag);
		//std::string command = "";
		//command += "echo ";
		//command += recieve;
		//command += " | mail adbranda@gmail.com";
		//system(command.c_str());
	//}
	
	//std::cout << "Tag : " << tag << std::endl;
	//std::cout << "Type : " << type << std::endl;
	
	send(client, "HTTP/1.1 200 OK\n", 16, 0);
	send(client, "Server: TEST\n", 13, 0);
	send(client, "Connection: close\n", 18, 0);
	
	std::string content = "Content-type: text/" + type + "\n";
	
	send(client, content.c_str(), content.length(), 0);
	send(client, "\n", 1, 0);
	
	std::string text = "";
	std::string currentDirectory = directory + "/" + tag;
	
	text = websiteFiles->getFile(directory + "/" + tag);
	
	send(client, text.c_str(), text.length(), 0);
	
	close(client);
}

std::string getTag(std::string get){
	std::string tag = "";
	
	for(int i = 5; i < get.length(); i++){
		if(get[i] == ' ')
			break;
		else
			tag += get[i];
	}
	if(tag.length() == 0)
		tag = "index.html";
	
	return tag;
}

std::string getType(std::string get){
	std::string type = "";
	bool foundExtension = false;
	
	for(int i = 0; i < get.length(); i++){
		if(get[i] == '.'){
			foundExtension = true;
			i++;
		}
		if(foundExtension)
			type += get[i];
	}
	if(type.length() == 0)
		type = "html";
	else if(type == "js")
		type = "javascript";
	//else if(type == "php")
	//	type = "html";
		
	return type;
}















