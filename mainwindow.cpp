#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    /****************************/
    Chart_Init();

    s_timer = new QTimer();
    rec_timer = new QTimer();
    connect(s_timer,SIGNAL(timeout()),this,SLOT(DrawLine()));
 //   connect(s_timer,SIGNAL(TimeOut()),this,SLOT(TimeOut()));

    /****************************/
    QStringList serialPortName;
    Serialport =new  QSerialPort(this);
    connect(Serialport,SIGNAL(readyRead()),this,SLOT(serialportread()));
    connect(rec_timer,SIGNAL(timeout()),this,SLOT(TimeRead()));
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
    rec_timer->start(100);
    buf.append( Serialport->readAll());

    bool ok;
    buf1 = buf.toInt(&ok,10);

}

void MainWindow::TimeRead()
{
    rec_timer->stop();
    if (buf.length() != 0)
    {
        ui->rec_Edit->appendPlainText(buf);
    }
    buf.clear();
}


void MainWindow::TimeOut()
{

}

void MainWindow::Chart_Init()
{
    chart = new QChart();
    splineserives = new QSplineSeries(this);
    splineserives->setName("绘图");

    chart->addSeries(splineserives);
    QValueAxis *axisX = new QValueAxis();
    QValueAxis *axisY = new QValueAxis();

    axisX->setMin(0);
    axisX->setMax(MAX_X);
    axisY->setMin(-50);
    axisY->setMax(MAX_Y);
    /*
    axisX->setRange(0,10);
    axisY->setRange(0,65);
*/
    axisX->setTickCount(5);
    axisY->setTickCount(1);

    QFont font("Microsoft YaHei",8,QFont::Normal);
    axisX->setTitleFont(font);
    axisY->setTitleFont(font);
    axisX->setTitleText("X-Test");
    axisY->setTitleText("Y-Test");
    chart->addAxis(axisX,Qt::AlignBottom);
    chart->addAxis(axisY,Qt::AlignLeft);

    splineserives->attachAxis(axisX);
    splineserives->attachAxis(axisY);
    ui->graphicsView->setChart(chart);
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);
}

void MainWindow::DrawLine()
{
//    qreal x =plotArea().width()/axisX-tickCount();


    static int count = 0;
    if(count > MAX_X)
    {
        splineserives->removePoints(0,splineserives->count() - MAX_X);
        chart->axisX()->setMin(count - MAX_X);
        chart->axisX()->setMax(count);
    }
//    splineserives->append(count,rand()%65);
    splineserives->append(count,buf1);
    count++;

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
    {
        QMessageBox::information(this,"提示","連接成功");
        s_timer->start(100);
    }
    else
        QMessageBox::information(this,"提示","連接失敗");
}


void MainWindow::on_Close_B_clicked()
{
    Serialport->close();
    s_timer->stop();
    QMessageBox::information(this,"提示","連接已斷開");
}

