#ifndef PLAYER_H
#define PLAYER_H 

#include "TrivialEngine.h"

using namespace std;

class Player : public Trivial::Sprite
{
private:
	float _totalCost;
	float _totalPeace;
public:	
	
	Player();
	~Player();
	void image(const string &name);
	void setTotalCost(float aCost);
	void setTotalPeace(float aPeace);
	float getTotalCost();
	float getTotalPeace();
	void update();
	
};

Player::Player()
{
	
}

void Player::image(const string &name)
{
	Sprite::image(name);
}

void Player::setTotalCost(float aCost)
{
	_totalCost = aCost;
}

void Player::setTotalPeace(float aPeace)
{
	_totalPeace = aPeace;
}

float Player::getTotalCost()
{
	return _totalCost;
}

float Player::getTotalPeace()
{
	return _totalPeace;
}

void Player::update()
{

}


Player::~Player()
{
	
}
#endif