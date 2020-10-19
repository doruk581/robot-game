#include <string>
#include "MiniFW_Modified.h"
#include "Robots_Modified.h"
#include "randgen.h"

bool Movement(Robot &play,Robot & m1,Robot &m2,Robot &m3,Robot &m4,bool &space);
void Go(Robot &play1, Direction dir);
void Pick(Robot &play2);
void MonsterMovement(Robot &mons1,Robot &mons2,Robot &mons3,Robot &mons4,bool checker);
void VerticalRoute(Robot &rob);
void ClockWiseRoute(Robot &rob);
void lifeControl(Robot &myRobot, int &lifeOfLight);

bool Movement(Robot & play, Robot & m1,Robot &m2,Robot &m3,Robot &m4,bool &space)
{
	if (IsPressed(keyRightArrow))		//if gamer press right arow robot moves the right cell
	{				
		Go(play,east);
	}
	else if (IsPressed(keyUpArrow))		//if gamer press up arow robot moves the up cell
	{
		Go(play, north);
	}
	else if (IsPressed(keyDownArrow))	//if gamer press down arow robot moves the down cell
	{
		Go(play, south);
	}
	else if(IsPressed(32))
	{
		if(play.GetBagCount() >= 20)
		{
			if(m1.GetXCoordinate() == 14 && m1.GetYCoordinate() == 4)
			{
				space = false;
			}
			if(m2.GetXCoordinate() == 14 && m2.GetYCoordinate() == 4)
			{
				space = false;
			}
			if(m3.GetXCoordinate() == 14 && m3.GetYCoordinate() == 4)
			{
				space = false;
			}
			if(m4.GetXCoordinate() == 14 && m4.GetYCoordinate() == 4)
			{
				space = false;
			}
			play.SetBagCount(play.GetBagCount() - 20);
		return false;
		}
	}
	return true;
}

void Go(Robot & play1, Direction dir)
{
	play1.TurnFace(dir);
	play1.Move();
	Pick(play1);
}
void Pick(Robot & play2)
{
	play2.PickAllThings();
}


void VerticalRoute(Robot &rob)
{
	if(!rob.isAlive())
	{
		rob.Resurrect();
	}
	if(rob.FacingWall())
	{
		rob.TurnBack();
		rob.Move();
	}
	else
	{
		rob.Move();
	}
}

void ClockWiseRoute(Robot &rob)
{
	if(!rob.isAlive())
	{
		rob.Resurrect();
	}
	if(rob.FacingWall())
	{
		while(rob.FacingWall())
		{
			rob.TurnRight();
		}
		rob.Move();
	}
	else
	{
		rob.Move();
	}
}
void MonsterMovement(Robot &mons1,Robot &mons2,Robot &mons3,Robot &mons4,bool checker)
{
	if(checker == false)
	{
	}
	else{
	RandGen random;
	int n = random.RandInt(1,4);

	if(n == 1 || n == 4)
	{
		switch (n)
		{
		case 1:VerticalRoute(mons1);
			break;
		case 4:VerticalRoute(mons4);
		default:
			break;
		}
	}
	else
	{
		switch (n)
		{
		case 2: ClockWiseRoute(mons2);
			break;
		case 3: ClockWiseRoute(mons3);
			break;
		default:
			break;
		}
	}
	}
}

void lifeControl(Robot &myRobot, int &lifeOfLight)
{
	if(!myRobot.isAlive())
	{
	lifeOfLight--;
	myRobot.Resurrect();
	}
}
int main()
{
	Robot player(0,4,east),monster1(3,8,south),monster2(6,2,south),monster3(13,5,east),monster4(13,0,north); // Initialization of robots
	bool spacecheck = true;
	player.SetBagCount(0); // Set player bag count to 0 
	bool check = true;
	int playerLife = 3; // he will die when it reaches 0 
	bool check2 = true;

	/*Give them Color*/
	player.SetColor(green);
	monster1.SetColor(red);
	monster2.SetColor(blue);
	monster3.SetColor(blue);
	monster4.SetColor(red);
	/**********************/

	while(playerLife != 0 && !(player.GetXCoordinate() == 14 && player.GetYCoordinate() ==4))
	{
		Sleep(200);
		check = Movement(player,monster1,monster2,monster3,monster4,spacecheck);
		if(check == false)
		{
			check2 = false;
		}
		if(spacecheck == false)
		{
			break;
		}
		MonsterMovement(monster1,monster2,monster3,monster4,check2);
		lifeControl(player,playerLife);

	}
	if(playerLife != 0)
	{
		if(player.GetXCoordinate() == 14 && player.GetYCoordinate() == 4)
		{
			if(player.GetBagCount() >= 50)
			{
				ShowMessage("Congratulations,you win!");	
			}
			else
			{
				ShowMessage("You reached the end but could not gather enough things… You lost the Game!");	
			}
		}
		else if(spacecheck == false)
		{
			ShowMessage("You blocked the target… You lost the Game!");
		}
	}
	else
	{
		ShowMessage("You run out of lives… You lost the Game!");	
	}
	return 0;
}