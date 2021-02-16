#include "gamemanager.h"
#include <fstream>
#include <qmath.h>


GameManager::GameManager(){

    _timer = new QTimer();
    connect(_timer, SIGNAL(timeout()), this, SLOT(timerUpdate()));
}

void GameManager::newGame(int size){

    _timer->start(1000);

    _gameTime  = 0;
    _steps = 0;
    _currentPlayer=RED;

    grid = std::vector<std::vector<Player> >(size, std::vector<Player>(size, GRAY));



    if(size==3){
        grid[1][1]=RED;
        red.x=1;
        red.y=1;
        grid[0][0]=YELLOW;
        grid[0][2]=YELLOW;
        grid[2][0]=YELLOW;
        grid[2][2]=YELLOW;

    }
    else if(size==5){
        grid[2][2]=RED;
        red.x=2;
        red.y=2;
        grid[0][0]=YELLOW;
        grid[0][4]=YELLOW;
        grid[4][0]=YELLOW;
        grid[4][4]=YELLOW;

    }
    else if(size==7){

        grid[3][3]=RED;
        red.x=3;
        red.y=3;
        grid[0][0]=YELLOW;
        grid[0][6]=YELLOW;
        grid[6][0]=YELLOW;
        grid[6][6]=YELLOW;

    }

}


void GameManager::directionChecker(int x, int y){
    if( x>=0 && y>=0 && x<(int)grid.size() && y<(int)grid.size() && ( (grid[x][y]==YENABLED &&_currentPlayer==YENABLED) || (grid[x][y]==RED && _currentPlayer==RED )))
        grid[x][y]=GRAY;
}

void GameManager::stepGame(int x, int y){

   if (_timer->isActive()){

        grid[x][y]=_currentPlayer;
        if(_currentPlayer==RED){
            red.x=x;
            red.y=y;
        }

        directionChecker(x-1,y);
        directionChecker(x,y-1);
        directionChecker(x+1,y);
        directionChecker(x,y+1);

        checkGame(red.x,red.y);



        if(_currentPlayer==YENABLED)
            _currentPlayer=RED;
        else if(_currentPlayer==RED){
            _currentPlayer=YELLOW;
            _steps++;
        }
        if(_steps==4*(int)grid.size()){

            _timer->stop();
            gameWon(RED);
        }
        else if( _canstep==false){

             _timer->stop();
            gameWon(YELLOW);
        }

        if(grid[x][y]==YENABLED){
            grid[x][y]=YELLOW;
        }
        viewSignal();
   }
}
bool GameManager::canstepTester(){
    return _canstep;
}

void GameManager::checkGame(int x, int y){

    if(grid[x][y]==RED){

        _canstep=_up=_down=_right=_left=false;

        if( x>0 && grid[x-1][y]==GRAY){

            _left=true;
        }
        else if( y>0 && grid[x][y-1]==GRAY){

            _up=true;
        }
        else if( x+1<(int)grid.size() && grid[x+1][y]==GRAY){

            _right=true;
        }
        else if( y+1<(int)grid.size() && grid[x][y+1]==GRAY){

            _down=true;
        }
        if(_up || _down || _right || _left ){

            _canstep=true;
        }
    }
}

void GameManager::enableYellow(int x, int y){
    if(_timer->isActive()){

    if(grid[x][y]==YELLOW){

        grid[x][y]=YENABLED;
        _currentPlayer=YENABLED;
    }
    else{

        grid[x][y]=YELLOW;
        _currentPlayer=YELLOW;
    }
    viewSignal();
    }
}

//QVector<QString> GameManager::saveGameList() const
//{
//    return _dataAccess.saveGameList();
//}

//bool GameManager::saveGame(int gameIndex,int size)
//{
//    QVector<int> saveGameData;

//    saveGameData.push_back(size);
//    saveGameData.push_back(_gameTime);
//    saveGameData.push_back((int)_currentPlayer);
//    saveGameData.push_back((int)_steps);

//    for (int i = 0; i < size; ++i)
//        for (int j = 0; j < size; ++j)
//        {
//            saveGameData.push_back((int)grid[i][j]);
//        }

//    return _dataAccess.saveGame(gameIndex, saveGameData,size*size+4);
//}

//bool GameManager::loadGame(int gameIndex)
//{
//    QVector<int> saveGameData;


//    if (!_dataAccess.loadGame(gameIndex, saveGameData))
//        return false;

//     int size=saveGameData[0];
//     setTable(saveGameData[0]);
//    _gameTime = saveGameData[1];
//    _currentPlayer = (Player)saveGameData[2];
//    _steps = (int) saveGameData[3];

//    grid=std::vector<std::vector<Player> >(size,std::vector<Player>(size,GRAY));
//    for (int i = 0; i < size; ++i)
//        for (int j = 0; j < size; ++j)
//        {
//            grid[i][j] = (Player)saveGameData[4 + i * size + j];
//        }
//    viewSignal();
//    return true;
//}

void GameManager::pauseTester(){
    pauseGame();
}

void GameManager::pauseGame(){

    if (_timer->isActive()){
        _timer->stop();
        pause();
    }
    else
        _timer->start();
}

void GameManager::timerUpdate(){

     _gameTime++;
     update();
}

GameManager::~GameManager(){

    _timer->stop();
    delete _timer;
}
