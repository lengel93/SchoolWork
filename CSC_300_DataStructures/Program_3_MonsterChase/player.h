ifndef __PLAYER_H
#define __PLAYER_H
#include <stdlib.h>
#include "site.h"
#include "playfield.h"

enum status2 { Open2, Closed2, Uknown2 };/*!< statuses for the nodes */

class Player 
{
   Playfield* playfield; /*!< playfield node */
   int N;/*!<n */

   struct goalL /*!< holds goal sites*/
   {
	   Site *pos; /*!< goal site*/
	   goalL *next; /*!< next */
   };
   goalL *headptr = nullptr;

   struct pnode /*!< holds graph detail */
   {
	   int x = 0;
	   int y = 0;
	   unsigned int f = 0;
	   unsigned int g = 0;
	   unsigned int h = 0;

	   enum status2 status = Uknown2;
	   bool walkable = false;

	   pnode *parent = NULL;
   };

   pnode **gameb;

   public:
      Player(Playfield* p); /*!< funct */
      Site* move();/*!< funct */
	  void fillnode(pnode *temp, int x, int y, bool w);/*!< funct */
	  vector<Site*> aStar(int x1, int y1, int x2, int y2);/*!< funct */
	  void resetnode(pnode *temp);/*!< funct */
	  int made = 0;/*!< checks if graph has already been made */
	  Site *player2; /*!< holds player */
	  Site *avoid1;/*!< avoid square */
	  Site *avoid2;/*!< avoid square */
	  Site *avoid3;/*!< avoid square */
	  Site *avoid4;/*!< avoid square */
	  Site *avoid5;/*!< avoid square */
	  Site *avoid6;/*!< avoid square */
	  Site *avoid7;/*!< avoid square */
	  Site *avoid8;/*!< avoid square */
	  Site *avoid0;/*!< avoid square */
	  vector<Site*> path2;/*!< vector for path */
	  vector<Site*> Lpath;
	  int size2;
	  int test2 = -1;
	  int dist; /*!< distance */
	  int zx;/*!< x */
	  int zy;/*!< y */
	  void avoid(int x, int y); /*!< funct */
	  void findgoal(int x, int y, int x2, int y2);/*!< funct */
};
#endif
