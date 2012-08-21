
#include "network.h"
#include "tcpip.h"
#include <string.h>

void send_data(SuPong * suPong)
{
	SuPongNet suPongNet;
	encodeNetPacket(suPong,&suPongNet);
	memcpy(TCP_TX_BUF,&suPongNet,sizeof(SuPongNet));
	TCPTxDataCount = sizeof(SuPongNet);	
	TCPTransmitTxBuffer();
}

void recieve_data(SuPong * suPong)
{
	SuPongNet suPongNet;
	memcpy(&suPongNet,TCP_RX_BUF,sizeof(SuPongNet));
	TCPReleaseRxBuffer();
	decodeNetPacket(&suPongNet,suPong);
}

void encodeNetPacket(SuPong *suPong, SuPongNet *suPongNet)
{
	//mPlayer1
		suPongNet->mPlayer1_mPoints = suPong->mPlayer1->mPoints;
		memcpy(suPongNet->mPlayer1_mName,suPong->mPlayer1->mName,NAMELENGTH);

	//mPlayer2
		suPongNet->mPlayer2_mPoints = suPong->mPlayer2->mPoints;
		memcpy(suPongNet->mPlayer2_mName,suPong->mPlayer2->mName,NAMELENGTH);
	
	//GameBoard
		suPongNet->GameBoard_mWidth = suPong->mGameBoard->mWidth;
		suPongNet->GameBoard_mHeight = suPong->mGameBoard->mHeight;
			//mBall
				suPongNet->GameBoard_Ball_mX = suPong->mGameBoard->mBall->mX;
				suPongNet->GameBoard_Ball_mY = suPong->mGameBoard->mBall->mY;
				suPongNet->GameBoard_Ball_mDirX = suPong->mGameBoard->mBall->mDirX;
				suPongNet->GameBoard_Ball_mDirY = suPong->mGameBoard->mBall->mDirY;
			//mPong1
                suPongNet->GameBoard_mPong1_mX = suPong->mGameBoard->mPong1->mX;
				suPongNet->GameBoard_mPong1_mY = suPong->mGameBoard->mPong1->mY;
				suPongNet->GameBoard_mPong1_mLength = suPong->mGameBoard->mPong1->mLength;
			//mPong2
                suPongNet->GameBoard_mPong2_mX = suPong->mGameBoard->mPong2->mX;
				suPongNet->GameBoard_mPong2_mY = suPong->mGameBoard->mPong2->mY;
				suPongNet->GameBoard_mPong2_mLength = suPong->mGameBoard->mPong2->mLength;
}

void decodeNetPacket(SuPongNet *suPongNet, SuPong *suPong)
{
	//mPlayer1
		suPong->mPlayer1->mPoints = suPongNet->mPlayer1_mPoints;
		memcpy(suPong->mPlayer1->mName,suPongNet->mPlayer1_mName,NAMELENGTH);

	//mPlayer2
		suPong->mPlayer2->mPoints = suPongNet->mPlayer2_mPoints;
		memcpy(suPong->mPlayer2->mName,suPongNet->mPlayer2_mName,NAMELENGTH);
	
	//GameBoard
		suPong->mGameBoard->mWidth = suPongNet->GameBoard_mWidth;
		suPong->mGameBoard->mHeight= suPongNet->GameBoard_mHeight;
			//mBall
				suPong->mGameBoard->mBall->mX = suPongNet->GameBoard_Ball_mX;
				suPong->mGameBoard->mBall->mY = suPongNet->GameBoard_Ball_mY;
				suPong->mGameBoard->mBall->mDirX = suPongNet->GameBoard_Ball_mDirX;
				suPong->mGameBoard->mBall->mDirY = suPongNet->GameBoard_Ball_mDirY;
			//mPong1
                suPong->mGameBoard->mPong1->mX = suPongNet->GameBoard_mPong1_mX;
				suPong->mGameBoard->mPong1->mY = suPongNet->GameBoard_mPong1_mY;
				suPong->mGameBoard->mPong1->mLength = suPongNet->GameBoard_mPong1_mLength;
			//mPong2
                suPong->mGameBoard->mPong2->mX = suPongNet->GameBoard_mPong2_mX;
				suPong->mGameBoard->mPong2->mY = suPongNet->GameBoard_mPong2_mY;
				suPong->mGameBoard->mPong2->mLength = suPongNet->GameBoard_mPong2_mLength;
}
