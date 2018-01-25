#include <iostream>
#include <unistd.h>

#include "server.h"

using namespace std;

//find www -type f | wc -l

int main(){
	
	
	
	Server server(8000, "www");
	
	bool attempt = false;

bind:
	if(attempt){
		usleep(5000000);
	}
	
	attempt = true;
	
	switch(server.Init()){
		case 1:
			cout << "Error establishing connection." << endl;
			goto exit;
			break;
		case 2:
			cout << "Error binding to socket." << endl;
			goto bind;
			break;
		case 0:
			cout << "Server init complete." << endl;
			break;
	}
	
	server.Listen();
	
	while(server.isRunning()){
		if(server.GetClient())
			server.SendPage();
	}
	
exit:
	return 0;
}