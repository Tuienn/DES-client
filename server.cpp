#include "server.h"
#include <QDateTime>
#include <QCryptographicHash>
#include <QDebug>

Server::Server(QObject *parent)
    : QObject(parent)
    , server(new QTcpServer(this))
    , serverPort(0)
{
    connect(server, &QTcpServer::newConnection, this, &Server::handleNewConnection);
}

Server::~Server()
{
    stop();
}

bool Server::start(quint16 port)
{
    if (!server->listen(QHostAddress::Any, port)) {
        qDebug() << "Server failed to start. Error:" << server->errorString();
        return false;
    }

    serverPort = port;
    serverAddress = server->serverAddress().toString();
    qDebug() << "Server started on" << serverAddress << ":" << serverPort;
    return true;
}

void Server::stop()
{
    for (QTcpSocket* client : clients) {
        client->disconnectFromHost();
        delete client;
    }
    clients.clear();
    server->close();
}

QString Server::getServerAddress() const
{
    return serverAddress;
}

quint16 Server::getServerPort() const
{
    return serverPort;
}

void Server::handleNewConnection()
{
    QTcpSocket *clientSocket = server->nextPendingConnection();
    clients.append(clientSocket);

    connect(clientSocket, &QTcpSocket::disconnected, this, &Server::handleClientDisconnected);
    connect(clientSocket, &QTcpSocket::readyRead, this, &Server::handleClientData);

    // Generate and send random key to the new client
    QString key = generateRandomKey();
    clientSocket->write(key.toUtf8());
    qDebug() << "New client connected. Sent key:" << key;
}

void Server::handleClientDisconnected()
{
    QTcpSocket *clientSocket = qobject_cast<QTcpSocket*>(sender());
    if (clientSocket) {
        clients.removeOne(clientSocket);
        clientSocket->deleteLater();
        qDebug() << "Client disconnected";
    }
}

void Server::handleClientData()
{
    QTcpSocket *clientSocket = qobject_cast<QTcpSocket*>(sender());
    if (!clientSocket) return;

    QDataStream in(clientSocket);
    in.setVersion(QDataStream::Qt_DefaultCompiledVersion);

    // Read file header
    qint64 fileSize;
    QString fileName;
    in >> fileSize >> fileName;

    // Create a file to store the received data
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly)) {
        qDebug() << "Failed to open file for writing:" << fileName;
        return;
    }

    // Read and write file data in chunks
    const qint64 chunkSize = 1024 * 64; // 64KB chunks
    qint64 remainingBytes = fileSize;
    QByteArray buffer;

    while (remainingBytes > 0 && !clientSocket->atEnd()) {
        qint64 bytesToRead = qMin(remainingBytes, chunkSize);
        buffer = clientSocket->read(bytesToRead);
        file.write(buffer);
        remainingBytes -= buffer.size();
    }

    file.close();
    qDebug() << "File received successfully:" << fileName;
}

QString Server::generateRandomKey()
{
    // Generate a random 16-character hex key
    QByteArray randomData;
    randomData.append(QDateTime::currentMSecsSinceEpoch());
    randomData.append(QDateTime::currentDateTime().toString("yyyyMMddhhmmss"));
    
    QByteArray hash = QCryptographicHash::hash(randomData, QCryptographicHash::Sha256);
    return hash.left(16).toHex();
} 