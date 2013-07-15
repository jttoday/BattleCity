#include "TankWindow.h"
#include "Tank.h"
#include "Missile.h"
#include <QtGui>
#include <QPoint>
#include <QRect>


const QPoint startPoint(1,1);

TankWindow::TankWindow()
{
	startGame();
	setFixedSize(pic_width*map_width, pic_height*map_height);
}

void TankWindow::addMissile(Missile *missile)
{
	missiles.push_back(missile);
}

void TankWindow::startGame()
{
	loadMap();
	player = new Tank(startPoint, this);
	timer = startTimer(20);
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
		}
}

/* TODO: */
void TankWindow::userLose()
{
	killTimer(timer);
	player->kill();
	delete player;
	player = NULL;
	clearMissile();
	clearMap();
	lose = true;
	repaint();
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

void TankWindow::clearMissile()
{
	for (std::list<Missile*>::iterator it=missiles.begin();
			it != missiles.end(); ++it)
	{
		delete *it;
	}
	missiles.clear();
}

void TankWindow::clearMap()
{
	walls.clear();
	steels.clear();
}


int TankWindow::getMap(int x, int y)
{
	return current_map[x][y];
}

void TankWindow::timerEvent(QTimerEvent *)
{
	std::list<Missile*>::iterator it=missiles.begin();
	while (it != missiles.end())
	{
		(*it)->move();
		bool live = true;
		if ((*it) -> hitRect(symbolRect)){
			userLose();
			break;
		}
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
		for (std::list<QRect>::iterator sit=steels.begin();
				sit != steels.end(); ++sit)
			if ((*it) -> hitRect(*sit))
			{
				live = false;
				it = missiles.erase(it);
				break; // break 'steel' loop
			}
		if (live && (*it)->outOfMap())
		{
			live = false;
			it = missiles.erase(it);
		}
		if (live) it++;
	}
	repaint();
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
	QImage plain;
	plain.load(":image/small/plain.gif");
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
				case Map::plain:
					painter.drawImage(p,plain);
					break;
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


