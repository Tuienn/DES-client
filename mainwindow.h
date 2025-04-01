#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>
#include <QFile>

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
    void connectToServer();  // Kết nối tới server
    void chooseFile();       // Chọn file từ local
    void sendFile();         // Gửi file tới server
    void onConnected();      // Xử lý khi kết nối thành công
    void onErrorOccurred(QAbstractSocket::SocketError socketError); // Xử lý lỗi
    void onServerResponse(); // Nhận phản hồi từ server

private:
    Ui::MainWindow *ui;
    QTcpSocket *socket;
    QFile file;
    QString serverKey;  // Store the received server key
};

#endif // MAINWINDOW_H
