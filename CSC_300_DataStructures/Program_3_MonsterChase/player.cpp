#include <vector>
#include <list>
#include "player.h"

using namespace std;


/**************************************************************************//**
* @author Lyndon Engel
*
* @par Description:
* Works the same way as the monster move except it generates a goal point. 
*
*****************************************************************************/
Site* Player::move()
{
	Site* monster = playfield->getMonsterSite();
	Site* player = playfield->getPlayerSite();
	int mx = monster->i(), my = monster->j();
	int px = player->i(), py = player->j();
	//vector<Site*> path;

	if (size2 > 10 || test2 == -1)
	{
		if (test2 > 10)
		{
			test2 = -1;
		}
		if (test2 < 11)
		{
			test2++;
		}
		if (test2 < 1)
		{
			findgoal(px, py, mx, my);
			Lpath = path2;
			size2 = (int)Lpath.size();
			test2++;
		}
	}
	else
	{
		findgoal(px, py, mx, my);
		Lpath = path2;
		size2 = (int)Lpath.size();
	}

	//get goal point
	//findgoal(px, py, mx, my);

	//size2 = (int)path2.size();

	Site* ret = Lpath[size2 - test2];

	return ret;
}

/**************************************************************************//**
* @author Lyndon Engel
*
* @par Description:
* Constructor to generate a map of the playfield
*
* @param[in]      p - used to get playfield size
*****************************************************************************/
Player::Player(Playfield* p)
{
	playfield = p;
	N = playfield->size();

	if (made == 0)
	{
		gameb = new pnode *[N];

		for (int i = 0; i < N; i++)
		{
			gameb[i] = new pnode[N];
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
void Player::resetnode(pnode *temp)
{
	temp->x = 0;
	temp->y = 0;
	temp->f = 0;
	temp->g = 0;
	temp->h = 0;

	temp->status = Uknown2;
	temp->walkable = false;

	temp->parent = NULL;
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
void Player::fillnode(pnode *temp, int x, int y, bool w)
{
	temp->x = x;
	temp->y = y;
	temp->walkable = w;
}

/**************************************************************************//**
* @author Lyndon Engel
*
* @par Description:
* Fills sites with positions around the monster so the player knows to avoid 
* them. 
*
* @param[in]      x - x coordinate of monster
* @param[in]      y - y coordinate of monster
*****************************************************************************/
void Player::avoid(int x, int y)
{
	avoid0 = new Site(x, y);
	avoid1 = new Site(x -1, y-1);
	avoid2 = new Site(x -1, y );
	avoid3 = new Site(x - 1, y + 1);
	avoid4 = new Site(x , y - 1);
	avoid5 = new Site(x , y + 1);
	avoid6 = new Site(x + 1, y - 1);
	avoid7 = new Site(x + 1, y );
	avoid8 = new Site(x + 1, y + 1);
}

/**************************************************************************//**
* @author Lyndon Engel
*
* @par Description:
* Generates a goal point thats about two points away from the monster. So 
* the player can have some type of goal. 
*
* @param[in]      x - player x
* @param[in]      y - player y
* @param[in]      x2 - monster x
* @param[in]      y2 - monster y
*****************************************************************************/
void Player::findgoal(int x, int y, int x2, int y2)
{
	vector<Site*> path;//vector path
	Site *t; //temp site
	int twall = 0, wall = -1;//how many walls are around each point
	goalL *temp = new(nothrow)goalL; //link list of goals 
	int gx, gy; //temp ints
	int tempdist = -1; //temp distances
	int size = playfield->size();//size of playfield


	//Fills a list up with possible goal points all are 2 squares away from the monster

	temp->pos = new Site(x2, y2 - 2);
	temp->next = new(nothrow)goalL;
	headptr = temp;
	temp = temp->next;

	temp->pos = new Site(x2 - 2, y2);
	temp->next = new(nothrow)goalL;
	temp = temp->next;

	temp->pos = new Site(x2 + 2, y2);
	temp->next = new(nothrow)goalL;
	temp = temp->next;

	temp->pos = new Site(x2, y2 + 2);
	temp->next = new(nothrow)goalL;
	temp = temp->next;

	temp->next = nullptr; 

	temp = headptr;

	//loop runs through each location in the list
	while (temp->next != nullptr)
	{
		//checks if position is a wall
		if (playfield->isWall(temp->pos))
		{
			temp = temp->next;
			continue;
		}
		//checks if already on position
		if (temp->pos == playfield->getPlayerSite())
		{
			temp = temp->next;
			continue;
		}
		//fills in positon x and y
		gx = temp->pos->i();
		gy = temp->pos->j();

		//checks if position is out of bounds
		if (gx < 0 || gy  < 0 || gx > size - 1 || gy > size - 1)
		{
			continue;
		}
		//sets up squares to avoid
		avoid(playfield->getMonsterSite()->i(), playfield->getMonsterSite()->j());

		//runs A star algorithm to find closest spot
		path = aStar(x, y, gx,gy);


		//runs through checking all adjacent sides for walls
		for (int x3 = -1; x3 < 2; x3++)
		{
			for (int y3 = -1; y3 < 2; y3++)
			{
				t = new Site(gx + x3, gy + y3);

				if (playfield->isWall(t) || (gx + x3 < 0) || (gy + y3 < 0) || (gx + x3 > size - 1) || (gy + y3 > size - 1))
				{
					twall++;
				}
			}
		}

		if (wall == -1)
		{
			wall = twall;
		}
		//if distance hasnt been set then set
		if (tempdist == -1)
		{
			tempdist = dist;
			zx = temp->pos->i();
			zy = temp->pos->j();
			wall = twall;
			path2 = path;
		}
		//if new distance is lower than temp or equal replace current coordinate 
		else if (dist > tempdist)
		{
			//if spot has shorter distance but is surrounded by more walls dont change
			if (twall > wall && size2 < 6)
			{
				temp = temp->next;
				continue;
			}
			zx = temp->pos->i(); //sets x position 
			zy = temp->pos->j(); //sets y position
			tempdist = dist;
			wall = twall;
			path2 = path;
		}
		temp = temp->next;
		twall = 0;
	}
	
	//free up memory
	temp = headptr;

	while (temp != nullptr)
	{
		headptr = headptr->next;

		delete temp;

		temp = headptr;
	}
	headptr = nullptr; 
}

/**************************************************************************//**
* @author Lyndon Engel
*
* @par Description:
* This function generates the fastest path using the A-star algorithm and then 
* stores it into a vector. Simular to that of the monsters.
*
* @param[in]      x1- player x coordinate
* @param[in]      y1 - player y coordinate
* @param[in]      x2 - goal x coordinate
* @param[in]      y2 - goal y coordinate
*****************************************************************************/
vector<Site*> Player::aStar(int x1, int y1, int x2, int y2)
{
	vector<Site*> path;

	// Define points to work with
	//tableNode  monster(x1, y1, true);
	int z = 0;
	int nx, ny;
	int size = playfield->size();
	pnode *goal;
	pnode *player;
	pnode *child;
	pnode *current;
	Site *monster;
	Site *goal1;
	Site *player1;
	Site *child1;
	Site *current1;

	player = &gameb[x1][y1];
	goal = &gameb[x2][y2];

	fillnode(player, x1, y1, true);
	fillnode(goal, x2, y2, true);

	player1 = new Site(x1, y1);
	goal1 = new Site(x2, y2);
	monster = playfield->getMonsterSite();

	player->f = 0;

	// Define the open and the close list
	list<pnode*> openList;
	list<pnode*> closedList;
	list<pnode*>::iterator itr;


	current = player;
	//Checks to see if the goal is within 1 space
	for (int x3 = -1; x3 < 2; x3++)
	{
		for (int y3 = -1; y3 < 2; y3++)
		{
			nx = x1 + x3;
			ny = y1 + y3;

			current1 = new Site(nx, ny);

			//prioritizes diagonal moves over anything else
			if (nx == goal1->i() && ny == goal1->j())
			{
				if ((x3 == -1 && y3 == -1) || (x3 == 1 && y3 == -1) || (x3 == -1 && y3 == 1) || (x3 == 1 && y3 == 1))
				{
					if (playfield->isCorridor(player1))
					{
						break;
					}
					else
					dist = .5;
				}
				else
				{
					dist = 1;
				}
				path.push_back(current1);
				return path;
			}
		}
	}

	// Add the start point to the openList
	openList.push_back(current);
	current->status = Open2;

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
		if (current == goal)
		{
			break;
		}

		// Remove the current point from the openList
		openList.remove(current);

		// Add the current point to the closedList
		closedList.push_back(current);
		current->status = Closed2;

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

				current1 = new Site(current->x, current->y);

				//makes sure you dont move diagonal in corridor
				if (playfield->isCorridor(current1))
				{
					if ((x == -1 && y == -1) || (x == 1 && y == -1) || (x == -1 && y == 1) || (x == 1 && y == 1))
					{
						continue;
					}
				}
				//checks bounds
				if (nx < 0 || ny < 0 || nx > size - 1 || ny > size - 1)
				{
					continue;
				}

				child1 = new Site(nx, ny);

				child = &gameb[nx][ny];

				if (child->status == Closed2)
				{
					continue;
				}
				else if ((playfield->isCorridor(child1)) && ((x == -1 && y == -1) || (x == 1 && y == -1) || (x == -1 && y == 1) || (x == 1 && y == 1)))
				{
					continue;
				}
				else if (playfield->isWall(child1)||child1->equals(monster))
				{
					child->x = nx;
					child->y = ny;
					child->walkable = false;
				}
				else
				{
					child->x = nx;
					child->y = ny;
					child->walkable = true;

					if ((x == -1 && y == -1) || (x == 1 && y == -1) || (x == -1 && y == 1) || (x == 1 && y == 1))
					{
						child->g = current->g += .5;
					}
					else
					{
						child->g = current->g += 1;
					}

					child->h = goal1->manhattanTo(child1);
					child->f = child->g + child->h;
					child->parent = current;
				}

				// If it's closed or not walkable then pass
				if (child->status == Closed2 || !child->walkable)
				{
					continue;
				}
				if (child->status == Open2)
				{
					continue;
				}
				else
				{
					child->status = Open2;
					openList.push_back(child);
				}
			}
		}
	}

	// Reset
	for (itr = openList.begin(); itr != openList.end(); ++itr)
	{
		(*itr)->status = Uknown2;
	}
	for (itr = closedList.begin(); itr != closedList.end(); ++itr)
	{
		(*itr)->status = Uknown2;
	}

	// Resolve the path starting from the end point
	while (current->parent != NULL && current != player)
	{
		nx = current->x;
		ny = current->y;

		if (z == 0)
		{
			dist = current->g;
			z++;
		}

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

	return path;
}
