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
private slots:
    void on_cont_B_clicked();
    void serialportread();
    void on_Close_B_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
