#ifndef MAINSCREEN_H
#define MAINSCREEN_H

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>

#include "ui.h"

class MainScreen : public QWidget
{
public:
    MainScreen(UI* IParent);
    UI* Parent;
};

#endif // MAINSCREEN_H
