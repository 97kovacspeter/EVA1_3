#ifndef TICTACTOEDATAACCESS_H
#define TICTACTOEDATAACCESS_H

#include <QString>
#include <QVector>

class HunterDataAccess
{
public:
    explicit HunterDataAccess() {}

    QVector<QString> saveGameList() const;

    bool loadGame(int gameIndex, QVector<int> &saveGameData);
    bool saveGame(int gameIndex, const QVector<int> &saveGameData,int size);
};

#endif // TICTACTOEDATAACCESS_H
