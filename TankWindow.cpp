#include "TankWindow.h"
#include "Tank.h"
#include "EnemyTank.h"
#include "Missile.h"
#include "Blast.h"
#include "MapElement.h"
#include <stdlib.h>
#include <time.h>
#include <QtGui>
#include <QPoint>
#include <QRect>
#include <vector>
#include <QDebug>
#include <QTextOption>

#define DEBUGx
#ifdef DEBUG
#include <iostream>
using namespace std;
#endif

TankWindow::TankWindow()
	:walls("walls"), steels("steels"), grasses("grasses")
{
	choosing = true;
	setFixedSize(pic_width*(map_width+2), pic_height*map_height);
	srand(time(NULL));
	player1 = NULL;
	player2 = NULL;
	playerNumber = 1;
}

void TankWindow::addMissile(Missile *missile)
{
	missiles.push_back(missile);
}

void TankWindow::startGame()
{
	clearMap();
	loadMap();
	player1 = new Tank(startPoints[3], this,p1tank);
	if (playerNumber == 2)
		player2 = new Tank(startPoints[4], this, p2tank);
	enemies.push_back(new EnemyTank(startPoints[0], this, regular_tank));
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
				walls.add(p);
			}
			else if (current_map[j][i] == Map::steel)
			{
				QPoint p(pic_width*j, pic_height*i);
				steels.add(p);
			}
			else if (current_map[j][i] == Map::grass)
			{
				QPoint p(pic_width*j, pic_height*i);
				grasses.add(p);
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
	clearMissile();
	clearEnemy();
	lose = true;
	repaint();
}

void TankWindow::addEnemy()
{
	if (enemies.size() == max_enemy-1)
		return;
	QPoint p = startPoints[rand() % 3];	
	enemies.push_back(new EnemyTank(p, this, fast_tank));
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

Tank* TankWindow::killPlayer(Tank* player)
{
	if (player == NULL)
	{
		qDebug() << "Warning: kill a NULL player!";
		return NULL;
	}
	killTank(player);
	delete player;
	return NULL;
}


bool TankWindow::hitBarrier(const QRect& rect)
{
	return walls.hit(rect) || steels.hit(rect);
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
			if (player1 != NULL)
				player1 = killPlayer(player1);
			if (player2 != NULL)
				player2 = killPlayer(player2);
			userLose();
			break;
		}
		/* Do missiles hit wall ? */
		if (walls.hitAndErase((*it)->getRect()))
		{
			live = false;
			it = missiles.erase(it);
			if (it == missiles.end())
				break;
		}
		/* Do missiles hit steel? */
		if (steels.hit((*it)->getRect()))
		{
			live = false;
			it = missiles.erase(it);
			if (it == missiles.end())
				break;
		}

		/* Do missiles hit player1? */
		if (player1 != NULL && 
				(*it)-> hitRect(player1->getTankRect())) 
		{
			player1 = killPlayer(player1);
			if (player2 == NULL)
				userLose();
			break;
		}
		/* Do missiles hit player2? */
		if (player2 != NULL && 
				(*it)-> hitRect(player2->getTankRect())) 
		{
			player2 = killPlayer(player2);
			if (player1 == NULL)
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
			startGame();
			break;
		default:
			break;
		}
		repaint();
		return;
	}

	bool isRestart = event->key()==Qt::Key_R;
	/* Handle player1 */
	if (player1 == NULL && !isRestart)
		goto p2;
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

	case Qt::Key_W:
    default:
        break;
    }
p2:
	if (player2 == NULL && !isRestart)
		goto out;
	switch (event->key())
	{
	case Qt::Key_W:
		player2->moveUp();
		break;
	case Qt::Key_A:
		player2->moveLeft();
		break;
	case Qt::Key_S:
		player2->moveDown();
		break;
	case Qt::Key_D:
		player2->moveRight();
		break;
	case Qt::Key_J:
		player2->shoot();
		break;
	default:
		break;
	}
out:
	if (isRestart)
		choosing = true;
	repaint();

}


void TankWindow::drawSymbol(QPainter &painter)
{
	QImage symbol(":image/small/symbol.gif");
	painter.fillRect(symbolRect, symbol);
}


void TankWindow::drawChoose(QPainter &painter)
{
		QImage pic;
		/* draw logo */
		pic.load(":image/small/logo.gif");
		QImage logo = pic;
		QPoint t(-300,-180);
		painter.drawImage(t, pic);

		/* draw select */
		pic.load(":image/small/select.png");
		QImage select = pic.scaled(8*pic_width
				, 2.7*pic_height);
		QPoint p(2.8*pic_width, 7*pic_height);
		painter.drawImage(p, select);

		/* draw small tank */
		pic.load(":image/small/selecttank.gif");
		int height = (6.5+playerNumber)*pic_height;
		p.setY(height);
		p.setX(2.2*pic_width);
		painter.drawImage(p, pic);
}

void TankWindow::drawInfo(QPainter &painter)
{
	/* back ground */
	QRect infoBackground(pic_width*map_width, 0, 
						pic_width*(map_width+2), pic_height*map_height);
	painter.fillRect(infoBackground, Qt::gray);
	painter.setFont(QFont("Arial Black", 30));
	/* enemy info */
	QPoint p(pic_width*map_width+4, 40);
	int rem = max_enemy - enemies.size();
	painter.drawText(p, QString("%1").arg(rem));
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
	walls.draw(painter);
	steels.draw(painter);
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

	if (player2 !=NULL)
		player2->drawTank(painter);

	/* draw grass */
	grasses.draw(painter);

	/* draw inform */
	drawInfo(painter);

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


