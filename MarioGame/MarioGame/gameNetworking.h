#pragma once 


#include <iostream>
#include <vector>
#include <SFML\Network.hpp>

#define UDP_PORT 54500

using std::cout; // Testing
using std::endl;

using std::string; 
using std::vector;
using std::iterator;

class gNetwork
{
public:
	void setDefaultUsernameScore(); // Resets to default username and score

	struct gameStats
	{
		string userName; // Username of the client
		string highScore; // Given highscore for the client
	};

	void broadcastToNetwork(); // Broadcast the players username and stats 
	void listenToNetwork(); // Listen for UDP Broadcast - Adds entries to clients table

	void setUsername(string newUsername); // Sets the hosts username
	void setHighScore(string newHighScore); // Sets the hosts high score

	vector<gameStats> getClientsData(); // Returns the client list

private:
	bool allowNetworking; // If networking is allowed, respond to broadcast
	gameStats hostName; // Stores the hosts username and highscore

	vector<gameStats> clients; // List of clients found
};