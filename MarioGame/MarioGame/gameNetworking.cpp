#include "gameNetworking.h"

void gNetwork::setDefaultUsernameScore()
{
	this->allowNetworking = true;
	this->hostName.highScore = "0";
	this->hostName.userName = "TestUser";
}

// Implement me
void gNetwork::broadcastToNetwork()
{
	if (this->allowNetworking)
	{
		sf::UdpSocket socket;

		hostName.userName = "TestUser";
		hostName.highScore = "25";

		string dataToSend = this->hostName.userName + "," + this->hostName.highScore;
		if (socket.send(dataToSend.c_str(), dataToSend.size(), sf::IpAddress::Broadcast, UDP_PORT) != sf::Socket::Done)
		{
			return; 
		}
		else
			cout << "Sent Packet" << endl;
	}
}

gNetwork::gameStats gNetwork::listenToNetwork()
{
	gameStats clientStats; // New clients stats

	clientStats.highScore = "";
	clientStats.userName = ""; 

	if (this->allowNetworking)
	{
		sf::UdpSocket socket;

		socket.setBlocking(false); // Do not block the current thread
		if (socket.bind(UDP_PORT) == sf::Socket::Done)
		{
			char dataRecv[100]; // Data that was recieved - Max 100 bytes
			size_t bytesRecv = 0;
			sf::IpAddress sender;
			unsigned short portRecv;

			if (socket.receive(dataRecv, 100, bytesRecv, sender, portRecv) == sf::Socket::Done)
			{
				bool usernameOrScore = false; // False if username, true if score

				for (size_t index = 0; index < bytesRecv && index < 100; index++)
				{
					if (dataRecv[index] != ',' && !usernameOrScore)
						clientStats.userName += dataRecv[index]; 
					else if (dataRecv[index] != ',' && usernameOrScore)
						clientStats.highScore += dataRecv[index]; 
					else // The character is a , - our delimiter
						usernameOrScore = true; 
				}

				cout << "Sender" << sender << endl;

				cout << clientStats.userName << ", " << clientStats.highScore << endl; 

				return clientStats; 
			}
			else
				cout << "No data on socket" << endl; 
		}
		else
			cout << "ERROR: Socket not bound" << endl; 
	}

	return clientStats;
}

void gNetwork::network()
{
	this->broadcastToNetwork();
	gameStats respondingClient = this->listenToNetwork(); 

	for (vector<gameStats>::iterator index = clients.begin(); index < clients.end(); index++)
	{
		if (respondingClient.userName == (*index).userName)
		{
			if (respondingClient.highScore != (*index).highScore)
				(*index).highScore = respondingClient.highScore;

			return; 
		}
	}

	clients.push_back(respondingClient); 
}

vector<gNetwork::gameStats> gNetwork::getClientsData()
{
	return clients;
}

void gNetwork::setHighScore(string newHighScore)
{
	this->hostName.highScore = newHighScore;
}

void gNetwork::setUsername(string newUsername)
{
	this->hostName.userName = newUsername;
}