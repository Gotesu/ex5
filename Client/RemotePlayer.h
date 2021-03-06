#ifndef REMOTEPLAYER_H
#define REMOTEPLAYER_H

#include <iostream>
#include <sstream>
#include <string>
#include <cstring>
#include "Player.h"
#include "RemoteConnection.h"
#include "Logic.h"
#include "Board.h"

using namespace std;
/************************
 * class RemotePlayer is a type of player that makes his move according to
 * the user's input and not automaticly (like an A.I).
 */
class RemotePlayer: public Player {
public:
	  /*******************
	 * constructor
	 * @param l Logic
	 * @param b Board
	 * @param s side
	 * @param rc RemoteConnection
	 ***********************/
    RemotePlayer(Logic& l, Board& b, Side s, RemoteConnection& rc);
	//destructor
    ~RemotePlayer();
    /***********************
  * function name: doMove
  * @return true if the player had a possible move, false otherwise.
  * Note: the function change this->last value, to the current Move.
     ***********************/
    bool doMove();
    /***********************
 * Function name: upload
 * @param choice the last moves values.
 * Operation: this function send the last move to the server.
     ***********************/
    void upload(Move* choice);
  /***********************
 * Function name: download
 * @return a Move from the server.
 * Operation: this function get the last move from the server.
     ***********************/
    Move* download();
  /***********************
 * Function name: disconnect
 * Operation: the function send "End" to the server.
     ***********************/
    void disconnect();
private:
    RemoteConnection rc;
    char* moveToChar(Move* move, char* dst);
    int charToInt (char* info);
};

#endif //REMOTEPLAYER_H
