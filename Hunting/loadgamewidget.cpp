#include "loadgamewidget.h"
#include <QMessageBox>

LoadGameWidget::LoadGameWidget(QWidget *parent) :
    SaveGameWidget(parent)
{
    setWindowTitle("Hunter game loading");


    disconnect(_okButton, SIGNAL(clicked()), this, SLOT(accept()));
    connect(_okButton, SIGNAL(clicked()), this, SLOT(okButton_Clicked()));
}

void LoadGameWidget::okButton_Clicked()
{
    if (_listWidget->currentItem()->text() == "empty")
    {

        QMessageBox::warning(this, trUtf8("Hunter"), trUtf8("No game selected"));
        return;
    }

    accept();
}
