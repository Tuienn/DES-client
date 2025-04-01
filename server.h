#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QHostAddress>
#include <QString>

class Server : public QObject
{
    Q_OBJECT

public:
    explicit Server(QObject *parent = nullptr);
    ~Server();

    bool start(quint16 port);
    void stop();
    QString getServerAddress() const;
    quint16 getServerPort() const;

private slots:
    void handleNewConnection();
    void handleClientDisconnected();
    void handleClientData();

private:
    QString generateRandomKey();
    QTcpServer *server;
    QList<QTcpSocket*> clients;
    QString serverAddress;
    quint16 serverPort;
};

#endif // SERVER_H 