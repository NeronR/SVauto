#ifndef MAINSCREEN_H
#define MAINSCREEN_H

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>

#include "ui.h"

class MainScreen : public QWidget
{
Q_OBJECT;
public:
    MainScreen(UI* IParent);
    UI* Parent;
//signals:
//public slots:
};

#endif // MAINSCREEN_H
