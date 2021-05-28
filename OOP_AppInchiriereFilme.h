#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_OOP_AppInchiriereFilme.h"

class OOP_AppInchiriereFilme : public QMainWindow
{
    Q_OBJECT

public:
    OOP_AppInchiriereFilme(QWidget *parent = Q_NULLPTR);

private:
    Ui::OOP_AppInchiriereFilmeClass ui;
};
