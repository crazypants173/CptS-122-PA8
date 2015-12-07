#pragma once 

#include "game.h"
#include <vector>
#include <SFML\Network.hpp>

#define NETWORK_CONNECT 23412
#define NETWORK_RECV 23414

using std::string;
using std::vector;

class gNetwork
{
public:
	struct gameStats
	{
		string userName; // Username of the client
		string highScore; // Given highscore for the client
	};

	bool gatherClients(); // Broadcast on the network - connect to any clients
	vector<gameStats> getClientsData(); // Calls gather clients, then returns the client list

private:
	bool allowNetworking; // If networking is allowed, respond to broadcast
	gameStats hostName; // Stores the hosts username and highscore

	vector<gameStats> clients; // List of clients found

};