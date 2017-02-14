#include "monster.h"
#include <vector>
#include <list>

/**************************************************************************//**
* @author Lyndon Engel
*
* @par Description:
* Constructor sets up the graph of the play field using a 2d array of nodes
*
* @param[in]      p - inputs the playfield size
*****************************************************************************/
Monster::Monster(Playfield* p) 
{
	playfield = p;
	N       = playfield->size();

	if (made == 0)
	{
		gameb = new node *[N];

		for (int i = 0; i < N; i++)
		{
			gameb[i] = new node[N];
		}
		made = 1;
	}
	else
	{
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < N; j++)
			{
				resetnode(&gameb[i][j]);
			}
		}
	}
}

/**************************************************************************//**
* @author Lyndon Engel
*
* @par Description:
* Resets the nodes in the graph back to default
*
* @param[in]      temp  - the node you want to reset
*****************************************************************************/
void Monster::resetnode(node *temp)
{
	temp->x = 0;
	temp->y = 0;
	temp->f = 0;
	temp->g = 0;
	temp->h = 0;

	temp->status = Uknown;
	temp->walkable = false;

	temp->parent = NULL;
}

/**************************************************************************//**
* @author Lyndon Engel
*
* @par Description:
* This function generates the monsters move. Using the A-star algorithm
*
*****************************************************************************/
Site* Monster::move() 
{
   //vector<Site*> path;
   Site* monster = playfield->getMonsterSite(); //gets monster location
   Site* player = playfield->getPlayerSite(); //gets player location
   int mx = monster->i(), my = monster->j(); //sets two ints to monster x and y
   int px = player->i(), py = player->j(); //sets two ints to player x and y

   //if the graph is bigger than 10 it wont constantly generate new moves but
   // used a path previously made
   if (size > 10 || test == -1)
   { 
	   if (test > 6)
	   {
		   test = -1;
	   }
	   if (test < 7)
	   {
		   test++;
	   }
	   if (test < 1)
	   {
		   path = aStar(mx, my, px, py);
		   size = (int)path.size();
		   test++;
	   }
   }
   else
   {
	   path = aStar(mx, my, px, py);
	   size = (int)path.size();
   }
  
	//inputs one move from the path vector

   Site* ret = path[size-test];

   return ret;
}

/**************************************************************************//**
* @author Lyndon Engel
*
* @par Description:
* Fills a node with an x and y value, and then states whether it is walkable or
* not.
*
* @param[in]      temp - the node you want to fill
* @param[in]      x - x value
* @param[in]      y - y value
* @param[in]      w - can you walk to this node
*****************************************************************************/
void Monster::fillnode(node *temp, int x, int y, bool w)
{
	temp->x = x;
	temp->y = y;
	temp->walkable = w;
}


/**************************************************************************//**
* @author Lyndon Engel
*
* @par Description:
* This function generates the fastest path using the A-star algorithm and then 
* stores it into a vector. 
*
* @param[in]      x1- monster x coordinate
* @param[in]      x2 - player x coordinate
* @param[in]      y1 - monster y coordinate
* @param[in]      y2 - player y coordinate
*****************************************************************************/
vector<Site*> Monster::aStar(int x1, int y1, int x2, int y2)
{
	vector<Site*> path;

	// Define points to work with
	//tableNode  monster(x1, y1, true);
	int nx, ny; //temp values
	int size = playfield->size(); //size of field 
	node *monster; //node for monster location
	node *player; //node for player location
	node *child; //node for child location
	node *current; //node for current location

	//corresponding sites for the nodes above
	Site *monster1;
	Site *player1;
	Site *child1;
	Site *current1;

	//grab the location of the monster and player from the graph
	monster = &gameb[x1][y1];
	player = &gameb[x2][y2];

	//fill the nodes
	fillnode(monster, x1, y1, true);
	fillnode(player, x2, y2, true);

	monster1 = new Site(x1, y1);
	player1 = new Site(x2, y2);

	monster->f = 0;

	// Define the open and the close list for adgencey list
	list<node*> openList;
	list<node*> closedList;
	list<node*>::iterator itr;

	//set current to monster location
	current = monster;

	//checks to see if the player is within one square of him
	for (int x3 = -1; x3 < 2; x3++)
	{
		for (int y3 = -1; y3 < 2; y3++)
		{
			nx = x1 + x3;
			ny = y1 + y3;

			current1 = new Site(nx, ny);

			if (nx == player1->i() && ny == player1->j())
			{
				if ((x3 == -1 && y3 == -1) || (x3 == 1 && y3 == -1) || (x3 == -1 && y3 == 1) || (x3 == 1 && y3 == 1))
				{
					if (playfield->isCorridor(monster1))
					{
						break;
					}
				}
				path.push_back(current1);
				return path;
			}
		}
	}

	// Add the start point to the openList
	openList.push_back(current);
	current->status = Open;

	while (!openList.empty())
	{
		// Look for the smallest F value in the openList and make it the current point
		for (itr = openList.begin(); itr != openList.end(); ++itr)
		{
			if (itr == openList.begin() || (*itr)->f <= current->f)
			{
				current = (*itr);
			}
		}

		// Stop if we reached the end
		if (current == player)
		{
			break;
		}

		// Remove the current point from the openList
		openList.remove(current);

		// Add the current point to the closedList
		closedList.push_back(current);
		current->status = Closed;

		// Get all current's adjacent walkable points
		for (int x = -1; x < 2; x++)
		{
			for (int y = -1; y < 2; y++)
			{
				// If it's current point then pass
				if (x == 0 && y == 0)
				{
					continue;
				}

				// Get this point
				nx = current->x + x;
				ny = current->y + y;

				//fill current site
				current1 = new Site(current->x, current->y);

				//if the play field is a corridor and you try to move diagonal grab new loop point
				if (playfield->isCorridor(current1))
				{
					if ((x == -1 && y == -1) || (x == 1 && y == -1) || (x == -1 && y == 1) || (x == 1 && y == 1))
					{
						continue;
					}
				}
				//if the point is out of bounds grab new loop point
				if (nx < 0 || ny < 0 || nx > size - 1 || ny > size - 1)
				{
					continue;
				}
				//set child site
				child1 = new Site(nx, ny);

				child = &gameb[nx][ny];

				if (child->status == Closed)
				{
					continue;
				}
				//if the child is a corridor and you try to move diagonally into, get a new point
				else if ((playfield->isCorridor(child1)) && ((x == -1 && y == -1) || (x == 1 && y == -1) || (x == -1 && y == 1) || (x == 1 && y == 1)))
				{
					continue;
				}
				//if child is wall fill 
				else if (playfield->isWall(child1))
				{
					child->x = nx;
					child->y = ny;
					child->walkable = false;
				}
				//else fill with basic information
				else
				{
					child->x = nx;
					child->y = ny;
					child->walkable = true;

					if ((x == -1 && y == -1) || (x == 1 && y == -1) || (x == -1 && y == 1) || (x == 1 && y == 1))
					{
						child->g = current->g + .5;
					}
					else
					{
						child->g = current->g + 1;
					}

					child->h = player1->manhattanTo(child1);
					child->f = child->g + child->h;
					child->parent = current;
				}

				// If it's closed or not walkable then pass
				if (child->status == Closed || !child->walkable)
				{
					continue;
				}
				if (child->status == Open)
				{
					continue;
				}
				else
				{
					child->status = Open;
					openList.push_back(child);
				}
			}
		}
	}

		// Reset nodes statuses 
		for (itr = openList.begin(); itr != openList.end(); ++itr)
		{
			(*itr)->status = Uknown;
		}
		for (itr = closedList.begin(); itr != closedList.end(); ++itr)
		{
			(*itr)->status = Uknown;
		}

		// Resolve the path starting from the end point and place into a vector
		while (current->parent != NULL && current != monster)
		{
			nx = current->x;
			ny = current->y;

			current1 = new Site(nx, ny);

			path.push_back(current1);
			current = current->parent;
		}

		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < N; j++)
			{
				resetnode(&gameb[i][j]);
			}
		}

		//return vector
		return path;
}