#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);
//########################################################################################################


//    return app.exec();
//########################################################################################################        
}

Dialog::~Dialog()
{
    delete ui;
}

