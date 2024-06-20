#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QClipboard>

#include "user_entry.h"

QT_BEGIN_NAMESPACE
namespace Ui {class MainWindow;}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void userInputNumberSystem(int value);
    void userOutputNumberSystem(int value);

private:
    Ui::MainWindow *ui;

    AppContext context;

    void inputNumber(QString value);
    unsigned getInputNumberSystem();
    unsigned getOutputNumberSystem();
    void setInputNumberSystem(unsigned numberSystem);
    void setOutputNumberSystem(unsigned numberSystem);

    void onPressInputButton();
    void onPressOutputButton();

    void convert();
    void copy();
    void swap();
    void updateLabels();
};

#endif // MAINWINDOW_H
