#include "ui_mainwindow.h"
#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->inputNumber, &QLineEdit::textChanged, this, &MainWindow::inputNumber);

    connect(ui->convertButton, &QPushButton::clicked, this, &MainWindow::convert);
    connect(ui->swapButton, &QPushButton::clicked, this, &MainWindow::swap);
    connect(ui->copyButton, &QPushButton::clicked, this, &MainWindow::copy);

    connect(ui->binaryInput, &QRadioButton::clicked, this, &MainWindow::onPressInputButton);
    connect(ui->decimalInput, &QRadioButton::clicked, this, &MainWindow::onPressInputButton);
    connect(ui->eighthInput, &QRadioButton::clicked, this, &MainWindow::onPressInputButton);
    connect(ui->userInput, &QRadioButton::clicked, this, &MainWindow::onPressInputButton);
    connect(ui->setInput, &QSpinBox::valueChanged, this, &MainWindow::userInputNumberSystem);

    connect(ui->binaryOutput, &QRadioButton::clicked, this, &MainWindow::onPressOutputButton);
    connect(ui->decimalOutput, &QRadioButton::clicked, this, &MainWindow::onPressOutputButton);
    connect(ui->eighthOutput, &QRadioButton::clicked, this, &MainWindow::onPressOutputButton);
    connect(ui->userOutput, &QRadioButton::clicked, this, &MainWindow::onPressOutputButton);
    connect(ui->setOutput, &QSpinBox::valueChanged, this, &MainWindow::userOutputNumberSystem);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateLabels()
{
    setInputNumberSystem(context.inputNumberSystem);
    setOutputNumberSystem(context.outputNumberSystem);
    ui->inputNumber->setText(QString::fromStdString(context.inputNumber));
    ui->outputNumber->setText(QString::fromStdString(context.outputNumber));
}

unsigned MainWindow::getInputNumberSystem()
{
    unsigned numberSystem = 0;
    if (ui->decimalInput->isChecked())
    {
        numberSystem = 10;
    }
    else if (ui->eighthInput->isChecked())
    {
        numberSystem = 8;
    }
    else if (ui->binaryInput->isChecked())
    {
        numberSystem = 2;
    }
    else
    {
        numberSystem = ui->setInput->value();
    }
    return numberSystem;
}

unsigned MainWindow::getOutputNumberSystem()
{
    unsigned numberSystem = 0;
    if (ui->decimalOutput->isChecked())
    {
        numberSystem = 10;
    }
    else if (ui->eighthOutput->isChecked())
    {
        numberSystem = 8;
    }
    else if (ui->binaryOutput->isChecked())
    {
        numberSystem = 2;
    }
    else
    {
        numberSystem = ui->setOutput->value();
    }
    return numberSystem;
}

void MainWindow::setInputNumberSystem(unsigned numberSystem)
{
    if (numberSystem == 10)
    {
        ui->decimalInput->setChecked(1);
    } else if (numberSystem == 2)
    {
        ui->binaryInput->setChecked(1);
    } else if (numberSystem == 8)
    {
        ui->eighthInput->setChecked(1);
    }
    else
    {
        ui->userInput->setChecked(1);
        ui->setInput->setValue(numberSystem);
    }
}

void MainWindow::setOutputNumberSystem(unsigned numberSystem)
{
    if (numberSystem == 10)
    {
        ui->decimalOutput->setChecked(1);
    }
    else if (numberSystem == 2)
    {
        ui->binaryOutput->setChecked(1);
    }
    else if (numberSystem == 8)
    {
        ui->eighthOutput->setChecked(1);
    }
    else
    {
        ui->userOutput->setChecked(1);
        ui->setOutput->setValue(numberSystem);
    }
}

void MainWindow::swap() {
    Error error = doOperation(Operation::SWAP, &context, 0);
    if (error == NO_ERROR)
    {
        ui->outputNumber->setText(QString::fromStdString(context.outputNumber));
    }
    else
    {
        handleError(error);
    }
    updateLabels();
}

void MainWindow::inputNumber(QString value)
{
    std::string str = value.toStdString();
    AppParameters params;
    params.number = str.c_str();
    doOperation(Operation::SET_INPUT_NUMBER, &context, &params);
    updateLabels();
}

void MainWindow::onPressInputButton()
{
    AppParameters params;
    params.numberSystem = getInputNumberSystem();
    doOperation(Operation::SET_INPUT_SYSTEM, &context, &params);
    updateLabels();
}

void MainWindow::onPressOutputButton()
{
    AppParameters params;
    params.numberSystem = getOutputNumberSystem();
    doOperation(Operation::SET_OUTPUT_SYSTEM, &context, &params);
    updateLabels();
}

void MainWindow::userInputNumberSystem(int value)
{
    AppParameters params;
    params.numberSystem = value;
    doOperation(Operation::SET_INPUT_SYSTEM, &context, &params);
    updateLabels();
}

void MainWindow::userOutputNumberSystem(int value)
{
    AppParameters params;
    params.numberSystem = value;
    doOperation(Operation::SET_OUTPUT_SYSTEM, &context, &params);
    updateLabels();
}

void MainWindow::convert()
{
    Error error = doOperation(Operation::CONVERT, &context, 0);
    if (error == NO_ERROR)
    {
        ui->outputNumber->setText(QString::fromStdString(context.outputNumber));
    }
    else
    {
        handleError(error);
    }
}

void MainWindow::copy()
{
    QString outputNumber = ui->outputNumber->text();
    QClipboard *clipboard = QApplication::clipboard();
    clipboard->setText(outputNumber);
}
