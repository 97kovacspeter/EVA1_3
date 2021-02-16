#include "hunterdataaccess.h"
#include <QDateTime>
#include <QFileInfo>
#include <QFile>
#include <QTextStream>


QVector<QString> HunterDataAccess::saveGameList() const
{
    QVector<QString> result(5);


    for (int i = 0; i < 5; i++)
    {
        if (QFile::exists("game" + QString::number(i) + ".sav"))
        {
            QFileInfo info("game"+ QString::number(i) + ".sav");
            result[i] = "[" + QString::number(i + 1) + "] " + info.lastModified().toString("yyyy.MM.dd HH:mm:ss");


        }
    }

    return result;
}

bool HunterDataAccess::loadGame(int gameIndex, QVector<int> &saveGameData)
{
    QFile file("game" + QString::number(gameIndex) + ".sav");
    if (!file.open(QFile::ReadOnly))
        return false;

    QTextStream stream(&file);

    saveGameData.resize(1);
    saveGameData[0]=stream.readLine().toInt();
    int size=saveGameData[0];
    saveGameData.resize(size*size+4);
   // saveGameData[0]=size; //safety line after resize

    // soronként beolvassuk az adatokat a fájlból
    for (int i = 1; i <size*size+4; i++)
        saveGameData[i] = stream.readLine().toInt();

    file.close();

    return true;
}

bool HunterDataAccess::saveGame(int gameIndex, const QVector<int> &saveGameData,int size)
{
    QFile file("game" + QString::number(gameIndex) + ".sav");
    if (!file.open(QFile::WriteOnly))
        return false;

    QTextStream stream(&file);

    // soronként egy adatot írunk ki
    for (int i = 0; i < size; i++)
        stream << saveGameData[i] << endl;

    file.close();

    return true;
}

