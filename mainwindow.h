#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>
#include <QFile>
#include <QDir>
#include <QFileInfo>
#include <QDesktopServices>
#include <QUrl>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void connectToServer();
    void chooseFile();
    void sendFile();
    void on_btnEncrypt_clicked(); // Add this method
    void onConnected();
    void onErrorOccurred(QAbstractSocket::SocketError socketError);
    void onServerResponse();

private:
    Ui::MainWindow *ui;
    QTcpSocket *socket;
    QFile file;
    QString serverKey;  // Store the received server key
};

#endif // MAINWINDOW_H
