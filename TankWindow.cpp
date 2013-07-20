#include "TankWindow.h"
#include "Tank.h"
#include "EnemyTank.h"
#include "Missile.h"
#include "Blast.h"
#include <stdlib.h>
#include <time.h>
#include <QtGui>
#include <QPoint>
#include <QRect>
#include <vector>

#define DEBUGx
#ifdef DEBUG
#include <iostream>
using namespace std;
#endif

TankWindow::TankWindow()
{
	startGame();
	setFixedSize(pic_width*map_width, pic_height*map_height);
	srand(time(NULL));
}

void TankWindow::addMissile(Missile *missile)
{
	missiles.push_back(missile);
}

void TankWindow::startGame()
{
	loadMap();
	player = new Tank(startPoints[3], this);
	enemies.push_back(new EnemyTank(startPoints[0], this));
	enemies.push_back(new EnemyTank(startPoints[1], this));
	enemies.push_back(new EnemyTank(startPoints[2], this));
	missileTimer = startTimer(30);
	enemyTimer = startTimer(250);
	produceTimer = startTimer(3000);
	lose = false;
}

void TankWindow::loadMap()
{
	for (int i=0;i < map_width; ++i)
		for (int j=0; j < map_height; ++j)
		{
			current_map[j][i] = Map::firstMap[i][j];
			if (current_map[j][i]==Map::wall)
			{
				QPoint p(pic_width*j, pic_height*i);
				addWall(p);
			}
			else if (current_map[j][i] == Map::steel)
			{
				QPoint p(pic_width*j, pic_height*i);
				addSteel(p);
			}
			else if (current_map[j][i] == Map::symbol)
			{
				QRect rect(pic_width*j, pic_height*i, 
						pic_width, pic_height);
				symbolRect = rect;
			}
			else if (current_map[j][i] == Map::startPoint)
			{
				startPoints.push_back(QPoint(pic_width*j,
								pic_height*i));
			}
		}
}


void TankWindow::userLose()
{
	killTimer(missileTimer);
	killTimer(enemyTimer);
	killTank(player);
	delete player;
	player = NULL;
	clearMissile();
	clearEnemy();
	clearMap();
	lose = true;
	repaint();
}

rect_list& TankWindow::getWalls()
{
	return walls;
}

rect_list& TankWindow::getSteels()
{
	return steels;
}

enemy_list& TankWindow::getEnemies()
{
	return enemies;
}

void TankWindow::addWall(QPoint p)
{
	QRect wall(p.x(), p.y(), pic_width, pic_height);
	walls.push_back(wall);
}

void TankWindow::addSteel(QPoint p)
{
	QRect steel(p.x(), p.y(), pic_width, pic_height);
	steels.push_back(steel);
}

void TankWindow::addEnemy()
{
	if (enemies.size() == max_enemy-1)
		return;
	QPoint p = startPoints[rand() % 3];	
	enemies.push_back(new EnemyTank(p, this));
}

void TankWindow::clearMissile()
{
	for (std::list<Missile*>::iterator it=missiles.begin();
			it != missiles.end(); ++it)
	{
		delete *it;
	}
	missiles.clear();
}

void TankWindow::clearEnemy()
{
	for (enemy_it it = enemies.begin();
			it != enemies.end(); ++it)
	{
		delete *it;
	}
	enemies.clear();
}

void TankWindow::clearMap()
{
	walls.clear();
	steels.clear();
}

void TankWindow::killTank(Tank* tank)
{
	tank->kill();
}


int TankWindow::getMap(int x, int y)
{
	return current_map[x][y];
}


void TankWindow::timerEvent(QTimerEvent *event)
{

	if (lose)
		return;
	if (event->timerId() == missileTimer)
	{
		moveMissile();
	}
	else if (event->timerId() == enemyTimer)	
	{
		moveEnemy();
	}
	else if (event->timerId() == produceTimer)
	{
		addEnemy();
	}
	repaint();
}

void TankWindow::moveEnemy()
{
	for (std::list<EnemyTank*>::iterator it = enemies.begin();
			it != enemies.end(); ++it)
	{
		if (!(*it)->isAlive())
			continue;
		(*it)->randomMove();
		if (rand() %4 == 0)
			(*it) -> shoot();
	}

}

void TankWindow::moveMissile()
{
	std::list<Missile*>::iterator it=missiles.begin();
	while (it != missiles.end())
	{
		(*it)->move();
		bool live = true;

		/* Do missiles hit symbol ? */
		if ((*it) -> hitRect(symbolRect)){
			userLose();
			break;
		}
		/* Do missiles hit wall ? */
		for (std::list<QRect>::iterator wit=walls.begin();
				wit != walls.end(); ++wit)
			if ((*it) -> hitRect(*wit))
			{
				live = false;
				it = missiles.erase(it);
				int x = wit->left() / pic_width;
				int y = wit->top() / pic_height;
				current_map[x][y] = 0;
				walls.erase(wit);
				break; // break 'wall' loop
			}
		/* Do missiles hit steel? */
		for (std::list<QRect>::iterator sit=steels.begin();
				sit != steels.end(); ++sit)
			if ((*it) -> hitRect(*sit))
			{
				live = false;
				it = missiles.erase(it);
				break; // break 'steel' loop
			}

		/* Do missiles hit player? */
		if ((*it)-> hitRect(player->getTankRect())) 
		{
			userLose();
			break;
		}

		/* Do missiles hit enemies? */
		std::list<EnemyTank*>::iterator eit = enemies.begin();
		while (eit != enemies.end())
		{
			if ((*eit)->isAlive() &&
					(*it)-> hitRect((*eit)->getTankRect()))
			{
				it = missiles.erase(it);
				killTank(*eit);
				live = false;
				break; // break 'enemies' loop
			}
			else
			{
				++eit;
			}
		}


		if (live && (*it)->outOfMap())
		{
			live = false;
			it = missiles.erase(it);
		}
		if (live) it++;
	}

}

void TankWindow::keyPressEvent(QKeyEvent *event)
{
	bool isRestart = event->key()==Qt::Key_R;
	if (player == NULL && !isRestart)
		return;
	if (player == NULL && isRestart)
		startGame();
	switch (event->key())
	{
    case Qt::Key_Up:
		player->moveUp();
        break;
    case Qt::Key_Down:
		player->moveDown();
        break;
    case Qt::Key_Left:
		player->moveLeft();
        break;
    case Qt::Key_Right:
		player->moveRight();
        break;
	case Qt::Key_Space:
		player->shoot();
		break;
    default:
        break;
    }
	repaint();
}

void TankWindow::drawMap(QPainter &painter)
{
	/* first draw back ground */
	QRect background(0, 0, pic_width*map_width, pic_height*map_height);
	painter.fillRect(background,Qt::black);
	
	QImage grass;
	grass.load(":image/small/grass.gif");
	QImage wall;
	wall.load(":image/small/walls.gif");
	QImage steel;
	steel.load(":image/small/steels.gif");
	QImage symbol;
	symbol.load(":image/small/symbol.gif");
	for (int i=0; i< map_width; ++i)
		for (int j=0; j < map_height; ++j)
		{
			QPoint p(pic_height*i, pic_width*j);	
			switch(current_map[i][j])
			{
				case Map::grass:
					painter.drawImage(p,grass);
					break;
				case Map::wall:
					painter.drawImage(p,wall);
					break;
				case Map::steel:
					painter.drawImage(p,steel);
					break;
				case Map::symbol:
					painter.drawImage(p,symbol);
				default:
					break;
			}
		}
}

void TankWindow::paintEvent(QPaintEvent *)
{
	QPainter painter(this);
	drawMap(painter);
	for (std::list<EnemyTank*>::iterator it = enemies.begin();
			it != enemies.end();++it)
	{
		(*it)->drawTank(painter);
	}

	for (std::list<Missile*>::iterator it=missiles.begin();
			it != missiles.end();++it)
	{
		(*it)->drawMissile(painter);
	}
	if (player !=NULL)
		player->drawTank(painter);
	if (lose)
	{
		QImage pic;
		pic.load(":image/small/gameOver.gif");
		QImage gameOver = pic.scaled(5*pic_width
				, 5*pic_height);
		QPoint p(4*pic_width, 4*pic_height);
		painter.drawImage(p, gameOver);

	}

}


