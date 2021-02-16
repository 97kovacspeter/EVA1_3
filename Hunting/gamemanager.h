#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include <QTimer>
#include <string>
#include <vector>
#include "hunterdataaccess.h"

class GameManager : public QObject{

    Q_OBJECT
public:
    GameManager();
    virtual ~GameManager();


    enum Player{RED,YELLOW,YENABLED,GRAY,ENABLED};

    Player currentPlayer() const {return _currentPlayer;}
    Player getField(int x, int y) const{return grid[x][y];}

    int timerData() const { return _gameTime; }
    int stepCount() const {return _steps;}
    int gridSize(){return grid.size();}

    bool loadGame(int gameIndex);
    bool saveGame(int gameIndex,int size);
    void newGame(int size);
    void stepGame(int x,int y);
    void checkGame(int x, int y);

    void enableYellow(int x,int y);

    void directionChecker(int x, int y);

    QVector<QString> saveGameList() const; // mentett játékok lekérdezése


private slots:
    void timerUpdate();
    void pauseGame();


signals:
    void gameWon(GameManager::Player player); //when one of the players win
    void gameOver(); //for ending with draw
    void update(); //timer updating signal
    void viewSignal();
    void pause();
    void setTable(int size);

private:
    std::vector<std::vector<Player> > grid;

    struct Position{

        int x;
        int y;
    } red;

    int _gameTime;
    bool _canstep;
    int _steps;

    bool _up;
    bool _down;
    bool _right;
    bool _left;

    int _loadSize;

    Player _currentPlayer;

    QTimer* _timer;

    HunterDataAccess _dataAccess;

};

#endif // GAMEMANAGER_H











