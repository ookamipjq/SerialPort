#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QStringList>
#include <QString>
#include <QComboBox>
#include <QMessageBox>
#include <QPlainTextEdit>
//********* *Charts*****************//
#include <QtCharts/QChartView>
#include <QtCharts/QSplineSeries>
#include <QTimer>
#include <QtCharts/QChart>
#include <QValueAxis>
#include <QGraphicsView>

#define MAX_X 50
#define MAX_Y 50
QT_BEGIN_NAMESPACE

namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QSerialPort *Serialport;
    QChart *chart;
    QSplineSeries *splineserives;
    QTimer *s_timer;
    QTimer *rec_timer;
     int buf1 = 0;
     QByteArray buf;
private slots:
    void on_cont_B_clicked();
    void serialportread();
    void on_Close_B_clicked();
    void Chart_Init();
    void DrawLine();
    void TimeOut();
    void TimeRead();
private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
