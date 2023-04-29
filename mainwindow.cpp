#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QStringList serialPortName;
    Serialport =new  QSerialPort(this);
    connect(Serialport,SIGNAL(readyRead()),this,SLOT(serialportread()));
    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts()) {
        serialPortName<<info.portName();
    }
    ui->serial_com->addItems(serialPortName);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::serialportread()
{
    QString buf;
    buf = QString(Serialport->readAll());
    ui->rec_Edit->appendPlainText(buf);
}

void MainWindow::on_cont_B_clicked()
{
    QSerialPort::DataBits Data_Bits;
    QSerialPort::StopBits Stop_Bits;
    QSerialPort::BaudRate Baud_Bits;
    QSerialPort::Parity Parity_Bits;
    if(ui->Baud_Text->currentText() == "9600")
        Baud_Bits = QSerialPort::Baud9600;
    else if(ui->Baud_Text->currentText() == "115200")
            Baud_Bits = QSerialPort::Baud115200;
    if(ui->Data_Text->currentText() == "8")
        Data_Bits = QSerialPort::Data8;
    else if(ui->Data_Text->currentText() == "7")
        Data_Bits = QSerialPort::Data7;
    else if(ui->Data_Text->currentText() == "6")
        Data_Bits = QSerialPort::Data6;
    else if(ui->Data_Text->currentText() == "5")
        Data_Bits = QSerialPort::Data5;
    if(ui->Stop_Text->currentText() == "1")
        Stop_Bits = QSerialPort::OneStop;
    else if(ui->Stop_Text->currentText() == "1.5")
        Stop_Bits = QSerialPort::OneAndHalfStop;
    else if(ui->Stop_Text->currentText() == "2")
        Stop_Bits = QSerialPort::TwoStop;
    if(ui->Parity_Text->currentText() == "1")
        Parity_Bits = QSerialPort::NoParity;
    Serialport->setPortName(ui->serial_com->currentText());
    Serialport->setDataBits(Data_Bits);
    Serialport->setParity(Parity_Bits);
    Serialport->setStopBits(Stop_Bits);
    Serialport->setBaudRate(Baud_Bits);
    if(Serialport->open(QIODevice::ReadWrite) == true)
        QMessageBox::information(this,"提示","連接成功");
    else
        QMessageBox::information(this,"提示","連接失敗");
}


void MainWindow::on_Close_B_clicked()
{
    Serialport->close();
    QMessageBox::information(this,"提示","連接已斷開");
}

