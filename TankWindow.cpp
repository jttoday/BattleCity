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
#include <QDebug>

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
	clearMap();
	choosing = true;
	playerNumber = 1;
	loadMap();
	player1 = new Tank(startPoints[3], this);
	enemies.push_back(new EnemyTank(startPoints[0], this));
	enemies.push_back(new EnemyTank(startPoints[1], this));
	enemies.push_back(new EnemyTank(startPoints[2], this));
	missileTimer = startTimer(30);
	enemyTimer = startTimer(250);
	produceTimer = startTimer(3000);
	lose = false;
}

int TankWindow::chooseType()
{
	return 0;
}

bool TankWindow::isChoosing()
{
	return choosing;
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
			else if (current_map[j][i] == Map::grass)
			{
				QPoint p(pic_width*j, pic_height*i);
				addGrass(p);
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
	killTank(player1);
	delete player1;
	player1 = NULL;
	clearMissile();
	clearEnemy();
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

void TankWindow::addGrass(QPoint p)
{
	QRect grass(p.x(), p.y(), pic_width, pic_height);
	grasses.push_back(grass);
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
	grasses.clear();
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

	
	if (lose || isChoosing())
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

		/* Do missiles hit player1? */
		if ((*it)-> hitRect(player1->getTankRect())) 
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
	if (isChoosing())
	{
		switch (event->key())
		{
		case Qt::Key_Up: case Qt::Key_Down:
			playerNumber = 3- playerNumber;
			break;
		case Qt::Key_Enter: case Qt::Key_Return:
			choosing = false;
			break;
		default:
			break;
		}
		repaint();
		return;
	}

	bool isRestart = event->key()==Qt::Key_R;
	if (player1 == NULL && !isRestart)
		return;
	if (player1 == NULL && isRestart)
		startGame();
	switch (event->key())
	{
    case Qt::Key_Up:
		player1->moveUp();
        break;
    case Qt::Key_Down:
		player1->moveDown();
        break;
    case Qt::Key_Left:
		player1->moveLeft();
        break;
    case Qt::Key_Right:
		player1->moveRight();
        break;
	case Qt::Key_Space:
		player1->shoot();
		break;
    default:
        break;
    }
	repaint();
}


void TankWindow::drawWall(QPainter &painter)
{
	QImage wall;
	wall.load(":image/small/walls.gif");
	drawRects(painter, wall, walls);
}

void TankWindow::drawSteel(QPainter &painter)
{
	QImage steel;
	steel.load(":image/small/steels.gif");
	drawRects(painter, steel, steels);
}

void TankWindow::drawGrass(QPainter &painter)
{
	QImage grass;
	grass.load(":image/small/grass.gif");
	drawRects(painter, grass, grasses);
}

void TankWindow::drawSymbol(QPainter &painter)
{
	QImage symbol(":image/small/symbol.gif");
	painter.fillRect(symbolRect, symbol);
}

void TankWindow::drawRects(QPainter &painter, const QImage& image,
							rect_list& rects)
{
	for (rect_it it = rects.begin(); it!= rects.end();++it)
	{
		painter.fillRect(*it, image);
	}
}

void TankWindow::drawChoose(QPainter &painter)
{
		QImage pic;
		/* draw logo */
		pic.load(":image/small/logo.gif");
		QImage logo = pic;
		QPoint t(-320,-180);
		painter.drawImage(t, pic);

		/* draw select */
		pic.load(":image/small/select.png");
		QImage select = pic.scaled(8*pic_width
				, 2.7*pic_height);
		QPoint p(2.3*pic_width, 7*pic_height);
		painter.drawImage(p, select);

		/* draw small tank */
		pic.load(":image/small/selecttank.gif");
		int height = (6.5+playerNumber)*pic_height;
		p.setY(height);
		p.setX(1.7*pic_width);
		painter.drawImage(p, pic);
}


void TankWindow::paintEvent(QPaintEvent *)
{
	QPainter painter(this);
	/* first draw back ground */
	QRect background(0, 0, pic_width*map_width, pic_height*map_height);
	painter.fillRect(background,Qt::black);
	/* if is choosing */
	if (isChoosing())
	{
		drawChoose(painter);
		return;
	}

	/* draw symbol */
	drawSymbol(painter);
	/* draw wall and steel */
	drawWall(painter);
	drawSteel(painter);
	/* drawEnemy */
	for (std::list<EnemyTank*>::iterator it = enemies.begin();
			it != enemies.end();++it)
	{
		(*it)->drawTank(painter);
	}

	/* drawMissile */
	for (std::list<Missile*>::iterator it=missiles.begin();
			it != missiles.end();++it)
	{
		(*it)->drawMissile(painter);
	}

	/* draw player */
	if (player1 !=NULL)
		player1->drawTank(painter);

	/* draw grass */
	drawGrass(painter);

	/* if lose draw game over*/
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


