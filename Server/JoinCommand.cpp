#include "JoinCommand.h"
#include "MenuManager.h"
#include "GameManager.h"
#include "Message.h"
#include "serverClients.h"

void JoinCommand::execute(int socket2, string gameName) {
	Message sendy;
	// get the other client socket from map
	int socket = MenuManager::getInstance()->removeGame(gameName);
	// check if gameName key was in the map
	if (socket == -1) {
		// if the name wasn't in the map - send an error massage to client
		sendy.error(socket2);
		return;
	}
	// send the client a massage that the command accepted
	sendy.accept(socket2);
	playGame(socket, socket2);
    //removing the thread from the thread vector after play
    serverClients::getInstance()->removeThread(pthread_self());
}

void JoinCommand::playGame(int client1Socket, int client2Socket) {
	int check;
	//adding thread to thread vector
	serverClients::getInstance()->addThread(pthread_self());
    // send player-number
	int first = 1;
	check = write(client1Socket, &first, 4);
	if (check == 0 || check == -1) {
        cout << "disconnection of client " << client1Socket << endl;
        return;
    }
	first++;
	check = write(client2Socket, &first, 4);
	if (check == 0 || check == -1) {
        cout << "disconnection of client " << client2Socket << endl;
        return;
    }
	// create a output char[]
	char input[INSIZE] = {0};
	int readen = client1Socket, writen = client2Socket;
	// a loop to handle the game, continue until checkServer() = false
	while (true) {
		// read readen-player command
		check = read(readen, input, sizeof(input));
        if (check == 0 || check == -1) {
            cout << "failed to read from client" << readen << endl;
            return;
        }
		// send the command to GameManager
		try {
			GameManager::getInstance()->executeCommand(input, writen, readen);
		} catch (const char* e) {
			cout << e;
            return;
		}
		// swap between the players
		int swap = readen;
		readen = writen;
		writen = swap;
	}
}