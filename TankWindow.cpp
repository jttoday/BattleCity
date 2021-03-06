#include "Config.h"
#include "TankWindow.h"
#include "Tank.h"
#include "PlayerTank.h"
#include "EnemyTank.h"
#include "Missile.h"
#include "Missiles.h"
#include "MapElement.h"
#include "Blasts.h"
#include <stdlib.h>
#include <time.h>
#include <QtGui>
#include <QPoint>
#include <QRect>
#include <vector>
#include <QDebug>
#include <QTextOption>
#include <QSound>

static TankType* p1tank;
static TankType* p2tank;
static TankType* regular_tank;
static TankType* fast_tank;
static TankType* heavy_tank;


TankWindow::TankWindow()
	:walls("walls"), steels("steels"), grasses("grasses"),
	 waters("waters")
{

    choosing = true;
	setFixedSize(pic_width*(map_width+2), pic_height*map_height);
	srand(time(NULL));
	player1 = NULL;
	player2 = NULL;
	powerUp = NULL;
	playerNumber = 1;
	enemyNumber = 0;
	QObject::connect(this, SIGNAL(eatingPowerUp(int, PlayerTank*)),
					 this, SLOT(onEatingPowerUp(int, PlayerTank*)));
	QObject::connect(this, SIGNAL(playerWin()),
					 this, SLOT(onPlayerWin()));
	p1tank = new TankType("p1tank", tank_speed, 3);
	p2tank = new TankType("p2tank", tank_speed, 3);
	regular_tank = new TankType("enemy1", tank_speed/3, 3);
	fast_tank = new TankType("enemy2", tank_speed*2/3, 3);
	heavy_tank = new TankType("enemy3", tank_speed/3, 5);		
}

void TankWindow::addMissile(Missile *missile)
{
	missiles.add(missile);
}

void TankWindow::startGame()
{
	PlayMusic("start.wav");
	clearMap();
	loadMap();
		/* add players */
	player1 = new PlayerTank(startPoints[3], this,*p1tank);
	p1life = max_life;
	if (playerNumber == 2)
	{
		player2 = new PlayerTank(startPoints[4], this, *p2tank);
		p2life = max_life;
	}
	/* add enemies */
	addEnemy();
	/* add timers */
	missileTimer = startTimer(30);
	enemyTimer = startTimer(100);
	produceTimer = startTimer(3000);
	strongTimer = startTimer(5000);
	powerUpTimer = startTimer(7000);
	lose = false;
	win = false;
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
			else if (current_map[j][i] == Map::water)
			{
				QPoint p(pic_width*j, pic_height*i);
				waters.add(p);
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

void TankWindow::onEatingPowerUp(int powerUpId, 
		PlayerTank* player)
{

	if (powerUpId == PowerUp::bomb)
		enemies.clear();
	else if (powerUpId == PowerUp::strong)
		player->setStrong(true);
	else if (powerUpId == PowerUp::fast)
		player->upgrade();

	powerUp == NULL;
}

void TankWindow::onPlayerWin()
{
	userLose();
	win = true;
}

void TankWindow::userLose()
{
	killTimer(missileTimer);
	killTimer(enemyTimer);
	clearMissile();
	clearEnemy();
	enemyNumber = 0;
	if (player1!= NULL)
	{
		delete player1;
		player1 = NULL;
	}
	if (player2!= NULL)
	{
		delete player2;
		player2 = NULL;
	}
	lose = true;
	repaint();
}

void TankWindow::addEnemy()
{
	if (enemyNumber == max_enemy)
		return;
	if (enemies.size() == 4)
		return;
	enemyNumber++;
	QPoint p = startPoints[rand() % 3];	
	TankType *t;
	int n = rand() % 3;
	if (n == 0) t = regular_tank;
	else if (n == 1) t = fast_tank;
	else t = heavy_tank;
	enemies.add(new EnemyTank(p, this, *t));
}

void TankWindow::clearMissile()
{
	missiles.clear();
}

void TankWindow::clearEnemy()
{
	enemies.clear();
}

void TankWindow::clearMap()
{
	walls.clear();
	steels.clear();
	grasses.clear();
	waters.clear();
}

void TankWindow::killTank(Tank* tank)
{
	tank->kill();
}

PlayerTank* TankWindow::killPlayer(PlayerTank* player, int n)
{
	if (player == NULL)
	{
		qDebug() << "Warning: kill a NULL player!";
		return NULL;
	}
	killTank(player);
	delete player;

	QPoint p;
	const TankType* t;
	p = startPoints[2+n];
	
	if (n == 1)
	{
		if (--p1life == 0)
			return NULL;
		t = p1tank;
	}
	else
	{
		if (--p2life == 0)
			return NULL;
		t = p2tank;
	}

	return new PlayerTank(p ,this, *t);
}


bool TankWindow::hitBarrier(const Tank& tank)
{
	return walls.hit(tank) || steels.hit(tank) || waters.hit(tank);
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
	else if (event->timerId() == strongTimer)
	{
		if (player1 != NULL)
			player1->setStrong(false);
		if (player2 != NULL)
			player2->setStrong(false);
	}
	else if (event->timerId() == powerUpTimer)
	{
		if (powerUp != NULL)
			delete powerUp;
		powerUp = new PowerUp(
				QPoint(rand() % (pic_width*map_width-40),
					   rand() % (pic_height*map_height-40)), 
					   rand() % 3 +1 );
	}


	repaint();
}

void TankWindow::moveEnemy()
{
	enemies.randomMove();
	enemies.randomShoot();

}

void TankWindow::moveMissile()
{
	missiles.move();
	/* hit symbol ? */
	if (missiles.hit(symbolRect))
	{
		if (player1 != NULL)
			player1 = killPlayer(player1, 1);
		if (player2 != NULL)
			player2 = killPlayer(player2, 2);
		userLose();
		return;
	}

	/* hit walls and steels */
	missiles.hitAndEraseAndRemove(walls);
	missiles.hitAndErase(steels);
	/* hit enemies */
	if	(enemies.hitAndEraseAndRemove(missiles, blasts))
		PlayMusic("blast.wav");
	/* check if in map */
	missiles.checkInMap();
	/* hit player? */
	if (player1 != NULL && missiles.hitAndEraseTank(*player1))
		player1 = killPlayer(player1, 1);
	if (player2 != NULL && missiles.hitAndEraseTank(*player2))
		player2 = killPlayer(player2, 2);
	/* is players lose? */
	if (player1 == NULL && player2 == NULL)
		userLose();
	if (enemies.size() == 0 && enemyNumber == max_enemy)
	{
		emit playerWin();
	}
	return;
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
	if (event->key() == Qt::Key_K)
	{
		enemies.clear();
		return;
	}
	/* Handle player1 */
	if (player1 == NULL)
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
    default:
        break;
    }
	if (powerUp != NULL &&
		(player1->getRect()).intersects(powerUp->getRect()))
	{
		emit eatingPowerUp(powerUp->powerUpId, player1);
		delete powerUp;
		powerUp = NULL;
	}

p2:
	if (player2 == NULL)
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
	if (powerUp != NULL &&
		(player2->getRect()).intersects(powerUp->getRect()))
	{
		emit eatingPowerUp(powerUp->powerUpId, player2);
		delete powerUp;
		powerUp = NULL;
	}
out:
	if (player1 == NULL && player2 == NULL && isRestart)
		choosing = true;
	repaint();

}


void TankWindow::drawSymbol(QPainter &painter)
{
	QImage symbol(":image/small/symbol.gif");
	if (!win && lose)
		symbol.load(":image/small/destroy.gif");
	painter.drawImage(symbolRect, symbol);

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
	int rem = max_enemy - enemyNumber;
	painter.drawText(p, QString("%1").arg(rem));
	p.setY(200);
	painter.drawText(p, QString("p1"));
	p.setY(250);
	painter.drawText(p, QString("%1").arg(p1life));
	if (playerNumber == 1)
		return;
	p.setY(300);
	painter.drawText(p, QString("p2"));
	p.setY(350);
	painter.drawText(p, QString("%1").arg(p2life));
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
	/* draw wall and steel and water*/
	walls.draw(painter);
	steels.draw(painter);
	waters.draw(painter);
	/* drawEnemy */
	enemies.draw(painter);

	/* drawBlasts */
	blasts.draw(painter);

	/* drawMissile */
	missiles.draw(painter);

	/* draw player */
	if (player1 !=NULL)
		player1->drawTank(painter);

	if (player2 !=NULL)
		player2->drawTank(painter);

	/* draw grass */
	grasses.draw(painter);

	/* draw power up */
	if (powerUp != NULL)
		powerUp -> draw(painter);

	/* draw inform */
	drawInfo(painter);

	/* if win the game */
	if (win)
	{
		QImage pic;
		pic.load(":image/small/win.gif");
		QImage gameOver = pic.scaled(5*pic_width
				, 5*pic_height);
		QPoint p(4*pic_width, 4*pic_height);
		painter.drawImage(p, gameOver);
		return; 
	}

	/* if lose draw game over*/
	if (lose)
	{
		QImage pic;
		pic.load(":image/small/gameOver.gif");
		QImage gameOver = pic.scaled(5*pic_width
				, 5*pic_height);
		QPoint p(4*pic_width, 4*pic_height);
		painter.drawImage(p, gameOver);
		return;
	}
}


