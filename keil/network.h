#ifndef __NETWORK_H__
#define __NETWORK_H__

#include "supong.h"

typedef struct
{
	int a;
	int count;
	char somedata[50];
}data_s;

typedef struct
{
	//mPlayer1
		int mPlayer1_mPoints;
		char mPlayer1_mName[NAMELENGTH];
	//mPlayer2
		int mPlayer2_mPoints;
		char mPlayer2_mName[NAMELENGTH];
	//GameBoard
		int GameBoard_mWidth;
		int GameBoard_mHeight;
		//mBall
			int GameBoard_Ball_mX;
			int GameBoard_Ball_mY;
			int GameBoard_Ball_mDirX;
			int GameBoard_Ball_mDirY;
		//mPong1
			int GameBoard_mPong1_mX;
			int GameBoard_mPong1_mY;
			int GameBoard_mPong1_mLength;
		//mPong2
			int GameBoard_mPong2_mX;
			int GameBoard_mPong2_mY;
			int GameBoard_mPong2_mLength;
} SuPongNet;

void send_data(SuPong * suPong);
void recieve_data(SuPong * suPong);
void encodeNetPacket(SuPong *suPong, SuPongNet *suPongNet);
void decodeNetPacket(SuPongNet *suPongNet, SuPong *suPong);


#endif
