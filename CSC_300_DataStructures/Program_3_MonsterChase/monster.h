#ifndef __MONSTER_H
#define __MONSTER_H
#include <stdlib.h>
#include <iomanip>
#include <queue>
#include <string>
#include <math.h>
#include "site.h"
#include "playfield.h"


enum status { Open, Closed, Uknown }; /*!< statuses for the nodes */

class Monster 
{
    Playfield* playfield; /*!< playfield node */
    int N;/*!<n */

	struct node
	{
		int x = 0; /*!< x value */
		int y = 0; /*!< y value */
		unsigned int f = 0; /*!< g + h */
		unsigned int g = 0; /*!< distance */
		unsigned int h = 0; /*!< hereditary value */

		enum status status = Uknown; /*!< status of node */
		bool walkable = false; /*!< is it walkable */

		node *parent = NULL; /*!< null */
	};


	node **gameb; /*!< game board node */ 

    public:
       Monster(Playfield* play); /*!< funct */
       Site* move();/*!< funct */
	   void fillnode(node *temp,int x, int y, bool w);/*!< funct */
	   vector<Site*> aStar(int x1, int y1, int x2, int y2);/*!< funct */
	   void resetnode(node *temp);/*!< funct */
	   int made = 0; /*!< checks if graph has already been made */
	   int test = -1; /*!< checks if player if futher than 10 spaces */
	   vector<Site*> path; /*!< holds path */
	   int size; /*!< holds size */
	   int distance = 5;/*!< holds distance */
};
#endif

