#include <iostream>
#include <fstream>
#include <netinet/in.h>
#include <unistd.h>

#include "FileTree.h"

#pragma once

class Server {
	private:
		std::string directory;
		FileTree* websiteFiles;
		int host, client;
		int portNum;
		bool running = false;
		int bufsize = 1024;
		char buffer[1024];
		char recieve[1024];
		struct sockaddr_in server_addr;
		socklen_t size;
	
	public:
		Server(int portNum, std::string directory);
		int Init();
		void Listen();
		bool GetClient();
		void SendPage();
		
		bool isRunning(){ return running; }
};