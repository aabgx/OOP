#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Seminar5_GestiuneMelodii_Qt.h"

class Seminar5_GestiuneMelodii_Qt : public QMainWindow
{
    Q_OBJECT

public:
    Seminar5_GestiuneMelodii_Qt(QWidget *parent = Q_NULLPTR);

private:
    Ui::Seminar5_GestiuneMelodii_QtClass ui;
};
