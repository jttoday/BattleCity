#include <Phonon/MediaObject>
#include <QString>


void PlayMusic(const QString& name)
{
	QString url = QString("music/%1").arg(name);
	Phonon::MediaObject *mediaObject = Phonon::createPlayer(Phonon::NoCategory, Phonon::MediaSource(url));
	mediaObject->play();
}
