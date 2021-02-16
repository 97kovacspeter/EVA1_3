#include "hunter.h"
#include <QMessageBox>
#include <QKeyEvent>
#include <QApplication>


Hunter::Hunter(QWidget *parent): QWidget(parent){

    setWindowTitle(trUtf8("Hunter"));

    _gameManager = new GameManager();
        connect(_gameManager, SIGNAL(gameOver()), this, SLOT(gameManager_gameOver()));

        connect(_gameManager,SIGNAL(viewSignal()),this,SLOT(viewUpdate()));

        connect(_gameManager,SIGNAL(setTable(int)),this,SLOT(senderSize(int)));
    _threeButton = new QPushButton(trUtf8("Little(3)"));
        connect(_threeButton, SIGNAL(clicked()), this, SLOT(startNewGame()));
        _threeButton->setFixedSize(130,50);
    _fiveButton = new QPushButton(trUtf8("Medium(5)"));
        connect(_fiveButton, SIGNAL(clicked()), this, SLOT(startNewGame()));
        _fiveButton->setFixedSize(130,50);
    _sevenButton = new QPushButton(trUtf8("Big(7)"));
        connect(_sevenButton, SIGNAL(clicked()), this, SLOT(startNewGame()));
        _sevenButton->setFixedSize(130,50);
    _pauseButton = new QPushButton(trUtf8("Stop/start"));
        _pauseButton->setEnabled(false);
        connect(_pauseButton, SIGNAL(clicked()), _gameManager, SLOT(pauseGame()));
        connect(_gameManager,SIGNAL(pause()),this,SLOT(pauseMsg()));
        _pauseButton->setFixedSize(130,50);
    _timerLabel=new QLabel("Timer: "+ QString::number(0));
        connect(_gameManager,SIGNAL(update()),this,SLOT(doTimerUpdate()));

     connect(_gameManager,SIGNAL(gameWon(GameManager::Player)),this,SLOT(gameManager_gameWon(GameManager::Player)));

    _stepLabel=new QLabel("Steps: " + QString::number(0));

    QHBoxLayout *hLayout = new QHBoxLayout();

    QVBoxLayout *vLayout = new QVBoxLayout();
    hLayout->addWidget(_threeButton);
    hLayout->addWidget(_fiveButton);
    hLayout->addWidget(_sevenButton);
    hLayout->addWidget(_pauseButton);

    vLayout->addLayout(hLayout);
    vLayout->addWidget(_timerLabel);
    vLayout->addWidget(_stepLabel);

    buttonGrid = std::vector<std::vector<QPushButton*> >(7, std::vector<QPushButton*>(7, NULL));

    _sightGrid = new QGridLayout();
    _sightGrid->setSpacing(0);
    _sightGrid->setContentsMargins(0,0,0,0);

    for(int i=0;i<7;++i){
        for(int j=0;j<7;++j){
             QPushButton *cell  = new QPushButton();
             buttonGrid[i][j]=cell;
             _sightGrid->addWidget(cell,i,j);
             buttonGrid[i][j]->setEnabled(false);
             buttonGrid[i][j]->setFixedSize(80,60);
             buttonGrid[i][j]->setStyleSheet("background-color:gray");
             connect(buttonGrid[i][j],SIGNAL(clicked()),this,SLOT(clickDecider()));
        }
    }

    vLayout->addLayout(_sightGrid);
    setLayout(vLayout);

//    QMessageBox::information(this,trUtf8("Info"), trUtf8("Player one is the red square."));
//    QMessageBox::information(this,trUtf8("Info"), trUtf8("Player two is with the yellow squares"));
//    QMessageBox::information(this,trUtf8("Info"), trUtf8("Gray squares are either walls or the dark parts you don't see yet"));
//    QMessageBox::information(this,trUtf8("Info"), trUtf8("Press the Stop/start button to pause the game and to continue"));

}

void Hunter::senderSize(int size){

    _gameManager->newGame(size);
    for(int i=0;i<(int)buttonGrid.size();++i){
        for(int j=0;j<(int)buttonGrid.size();++j){
            _sightGrid->removeWidget(buttonGrid[j][i]);
            disconnect(buttonGrid[j][i],SIGNAL(clicked()),this,SLOT(clickDecider()));
            delete buttonGrid[j][i];

        }
    }

    if(size==3){
        buttonGrid = std::vector<std::vector<QPushButton*> >(3, std::vector<QPushButton*>(3, NULL));
        for(int i=0;i<3;++i){
            for(int j=0;j<3;++j){
                 QPushButton *cell  = new QPushButton();

                 buttonGrid[j][i]=cell;
                 _sightGrid->addWidget(cell,i,j);
                 buttonGrid[j][i]->setEnabled(false);
                 buttonGrid[j][i]->setFixedSize(190,160);
                 connect(buttonGrid[j][i],SIGNAL(clicked()),this,SLOT(clickDecider()));

            }
        }

    }

    if(size==5){
        buttonGrid = std::vector<std::vector<QPushButton*> >(5, std::vector<QPushButton*>(5, NULL));
        for(int i=0;i<5;++i){
            for(int j=0;j<5;++j){
                 QPushButton *cell  = new QPushButton();

                 buttonGrid[j][i]=cell;
                 _sightGrid->addWidget(cell,i,j);
                 buttonGrid[j][i]->setEnabled(false);
                 buttonGrid[j][i]->setFixedSize(115,80);
                 connect(buttonGrid[j][i],SIGNAL(clicked()),this,SLOT(clickDecider()));

            }
        }


    }

    if(size==7){

        buttonGrid = std::vector<std::vector<QPushButton*> >(7, std::vector<QPushButton*>(7, NULL));
        for(int i=0;i<7;++i){
            for(int j=0;j<7;++j){
                 QPushButton *cell  = new QPushButton();

                 buttonGrid[j][i]=cell;
                 _sightGrid->addWidget(cell,i,j);
                 buttonGrid[j][i]->setEnabled(false);
                 buttonGrid[j][i]->setFixedSize(85,65);
                 connect(buttonGrid[j][i],SIGNAL(clicked()),this,SLOT(clickDecider()));
            }
        }

    }

    Hunter::adjustSize();
    Hunter::viewUpdate();
    _pauseButton->setEnabled(true);
}

void Hunter::startNewGame(){

    if (QObject::sender() == _threeButton){
        senderSize(3);

    }
    else if (QObject::sender() == _fiveButton){
        senderSize(5);
    }
    else{
        senderSize(7);
    }

}



void Hunter::viewUpdate(){
    _stepLabel->setText("Steps: "+ QString::number(_gameManager->stepCount()));
    for(int i=0;i<(int)buttonGrid.size();++i){
        for(int j=0;j<(int)buttonGrid.size();++j){
            if(_gameManager->getField(j,i)!=GameManager::YENABLED)
            buttonGrid[j][i]->setEnabled(false);
        }
    }
    for(int i=0;i<(int)buttonGrid.size();++i){
        for(int j=0;j<(int)buttonGrid.size();++j){



            if(_gameManager->getField(j,i)==GameManager::RED){

                buttonGrid[j][i]->setStyleSheet("background-color:red");
                if((GameManager::Player)_gameManager->currentPlayer()==GameManager::RED){

                    if( i+1<(int)buttonGrid.size() && (_gameManager->getField(j,i+1)==GameManager::GRAY)){

                        buttonGrid[j][i+1]->setEnabled(true);

                    }
                    if( j+1<(int)buttonGrid.size() && (_gameManager->getField(j+1,i)==GameManager::GRAY)){

                        buttonGrid[j+1][i]->setEnabled(true);

                    }
                    if( i>0 && (_gameManager->getField(j,i-1)==GameManager::GRAY)){

                        buttonGrid[j][i-1]->setEnabled(true);

                    }
                    if( j>0 && (_gameManager->getField(j-1,i)==GameManager::GRAY)){

                        buttonGrid[j-1][i]->setEnabled(true);

                    }
                }
            }
            if(_gameManager->getField(j,i)==GameManager::YENABLED){

                buttonGrid[j][i]->setStyleSheet("background-color:green");
                if((GameManager::Player)_gameManager->currentPlayer()==GameManager::YENABLED){

                    if( i+1<(int)buttonGrid.size() && (_gameManager->getField(j,i+1)==GameManager::GRAY)){

                        buttonGrid[j][i+1]->setEnabled(true);

                    }
                    if( j+1<(int)buttonGrid.size() && (_gameManager->getField(j+1,i)==GameManager::GRAY)){

                        buttonGrid[j+1][i]->setEnabled(true);

                    }
                    if( i>0 && (_gameManager->getField(j,i-1)==GameManager::GRAY)){

                        buttonGrid[j][i-1]->setEnabled(true);

                    }
                    if( j>0 && (_gameManager->getField(j-1,i)==GameManager::GRAY)){

                        buttonGrid[j-1][i]->setEnabled(true);

                    }
                }
            }
            if(_gameManager->getField(j,i)==GameManager::GRAY){

                buttonGrid[j][i]->setStyleSheet("background-color:gray");
            }
            if(_gameManager->getField(j,i)==GameManager::YELLOW){

                buttonGrid[j][i]->setStyleSheet("background-color:yellow");
                 if((GameManager::Player)_gameManager->currentPlayer()==GameManager::YELLOW){
                     buttonGrid[j][i]->setEnabled(true);

                 }
                 else if((GameManager::Player)_gameManager->currentPlayer()==GameManager::YENABLED){
                     buttonGrid[j][i]->setEnabled(false);

//                     if( i+1<(int)buttonGrid.size() && (_gameManager->getField(j,i+1)==GameManager::GRAY)){

//                         buttonGrid[j][i+1]->setEnabled(false);
//                     }
//                     if( j+1<(int)buttonGrid.size() && (_gameManager->getField(j+1,i)==GameManager::GRAY)){

//                         buttonGrid[j+1][i]->setEnabled(false);
//                     }
//                     if( i>0 && (_gameManager->getField(j,i-1)==GameManager::GRAY)){

//                         buttonGrid[j][i-1]->setEnabled(false);
//                     }
//                     if( j>0 && (_gameManager->getField(j-1,i)==GameManager::GRAY)){

//                         buttonGrid[j-1][i]->setEnabled(false);
//                     }
                 }
            }

        }
    }
}
void Hunter::clickDecider(){
    QObject* obj = sender();

    for(int i=0;i<(int)buttonGrid.size();++i){
        for(int j=0;j<(int)buttonGrid.size();++j){
            if(obj==buttonGrid[j][i]){
                if((_gameManager->currentPlayer()==GameManager::RED || _gameManager->currentPlayer()==GameManager::YENABLED)&&_gameManager->getField(j,i)==GameManager::GRAY){
                _gameManager->stepGame(j,i);
                }
                else if((_gameManager->currentPlayer()==GameManager::YELLOW ||_gameManager->currentPlayer()==GameManager::YENABLED) &&(_gameManager->getField(j,i)==GameManager::YELLOW || _gameManager->getField(j,i)==GameManager::YENABLED)){
                _gameManager->enableYellow(j,i);
                }
            }
        }
    }
}

void Hunter::doTimerUpdate(){

    _timerLabel->setText("Timer: "+ QString::number(_gameManager->timerData()));
}

void Hunter::keyPressEvent(QKeyEvent *event)
{
    // load
    if (event->key() == Qt::Key_L && QApplication::keyboardModifiers() == Qt::ControlModifier)
    {
        if (_loadGameWidget == NULL) //never opened
        {
            _loadGameWidget = new LoadGameWidget();

            connect(_loadGameWidget, SIGNAL(accepted()), this, SLOT(loadGame()));
        }


        _loadGameWidget->setGameList(_gameManager->saveGameList());
        _loadGameWidget->open();
    }

    // save
    if (event->key() == Qt::Key_S && QApplication::keyboardModifiers() == Qt::ControlModifier)
    {
        if (_saveGameWidget == NULL) // never opened
        {
            _saveGameWidget = new SaveGameWidget();

            connect(_saveGameWidget, SIGNAL(accepted()), this, SLOT(saveGame()));
        }


        _saveGameWidget->setGameList(_gameManager->saveGameList());
        _saveGameWidget->open();
    }
    viewUpdate();
}

void Hunter::gameManager_gameOver(){

        QMessageBox::information(this, trUtf8("Game over"), trUtf8("DRAW"));
        _gameManager->newGame((int)_gameManager->gridSize());
}

void Hunter::gameManager_gameWon(GameManager::Player player){
        if(player==GameManager::RED)
            _won="Red";
        else
           _won="Yellow";

        QMessageBox::information(this, trUtf8("Game over"), _won+ trUtf8(" won the game."));
        _gameManager->newGame((int)_gameManager->gridSize());
}

void Hunter::pauseMsg(){
    QMessageBox::information(this,trUtf8("Game is paused "), trUtf8("Reminder : Yellow player wins, if Red can't move within 4n steps, where n is the size of the area (ex. n=3 on the 3x3 grid)"));
}

void Hunter::loadGame()
{
    if (_gameManager->loadGame(_loadGameWidget->selectedGame()))
    {
        viewUpdate();
        QMessageBox::information(this, trUtf8("Hunter"), trUtf8("Game loaded successfully, next : ") + ((_gameManager->currentPlayer() == GameManager::RED ) ? "RED" : "YELLOW") + "!");
    }
    else
    {
        QMessageBox::warning(this, trUtf8("Hunter"), trUtf8("Failed to load game"));
    }
}

void Hunter::saveGame()
{
    int size=_gameManager->gridSize();

    if (_gameManager->saveGame(_saveGameWidget->selectedGame(),size))
    {
        viewUpdate();
        QMessageBox::information(this, trUtf8("Hunter"), trUtf8("Game successfully saved"));
    }
    else
    {
        QMessageBox::warning(this, trUtf8("Hunter"), trUtf8("Failed to save game"));
    }
}


Hunter::~Hunter(){

    delete _gameManager;
}
