#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include "des.h" // Add DES header

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , socket(new QTcpSocket(this))
{
    ui->setupUi(this);

    // Set StyleSheet
    this->setStyleSheet(
        "QMainWindow {"
        "   background-color: #B3E5FC;"  // Màu xanh nhạt
        "}"
        "QPushButton {"
        "   background-color: #0288D1;"  // Màu xanh đậm
        "   color: white;"
        "   border-radius: 10px;"
        "   padding: 10px 20px;"
        "   font-size: 16px;"
        "   transition: all 0.3s ease-in-out;"
        "   cursor: pointer;"
        "}"
        "QPushButton:hover {"
        "   background-color: #0277BD;"  // Đổi màu khi hover
        "}"
        "QPushButton:pressed {"
        "   background-color: #01579B;"
        "   transform: scale(0.95);"  // Hiệu ứng nhấn
        "}"
        "QLineEdit {"
        "   border: 1px solid #0288D1;"
        "   border-radius: 5px;"
        "   padding: 10px;"
        "   background-color: white;"
        "   color: black;"
        "   font-size: 16px;"
        "}"
        "QTextEdit {"
        "   border: 1px solid #0288D1;"
        "   border-radius: 5px;"
        "   background-color: white;"
        "   color: black;"
        "   font-size: 16px;"
        "   padding: 5px 10px;"
        "}"
        "QLabel {"
        "   color: black;"
        "   font-size: 16px;"
        "}"
        "QGroupBox {"
        "   padding: 0px;"
        "   border: none;"
        "}"
        );

    // Kết nối các sự kiện UI với các hàm xử lý
    connect(ui->btnConnect, &QPushButton::clicked, this, &MainWindow::connectToServer);
    connect(ui->btnChooseFile, &QPushButton::clicked, this, &MainWindow::chooseFile);
    connect(ui->btnSendFile, &QPushButton::clicked, this, &MainWindow::sendFile);
    connect(ui->btnEncrypt, &QPushButton::clicked, this, &MainWindow::on_btnEncrypt_clicked); // Update encryption handler

    // Kết nối tín hiệu socket
    connect(socket, &QTcpSocket::connected, this, &MainWindow::onConnected);
    connect(socket, &QTcpSocket::errorOccurred, this, &MainWindow::onErrorOccurred);
    connect(socket, &QTcpSocket::readyRead, this, &MainWindow::onServerResponse);
}

MainWindow::~MainWindow()
{
    delete ui;
}

// Kết nối tới server
void MainWindow::connectToServer()
{
    QString serverIP = ui->txtServerIP->text();
    int serverPort = ui->txtServerPort->text().toInt();

    if (serverIP.isEmpty() || serverPort == 0) {
        ui->txtLog->append("Please enter a valid Server IP and Port.");
        return;
    }

    ui->txtLog->append("Connecting to server...");
    socket->connectToHost(serverIP, serverPort);
}

// Khi kết nối thành công
void MainWindow::onConnected()
{
    ui->txtLog->append("Connected to server!");
}

// Khi có lỗi xảy ra
void MainWindow::onErrorOccurred(QAbstractSocket::SocketError socketError)
{
    Q_UNUSED(socketError);
    ui->txtLog->append("onnection error: " + socket->errorString());
}

// Chọn file từ máy local
void MainWindow::chooseFile()
{
    QString filePath = QFileDialog::getOpenFileName(this, "Select a file");
    if (!filePath.isEmpty()) {
        ui->txtFilePath->setText(filePath);
    }
}

// Gửi file lên server
void MainWindow::sendFile()
{
    QString filePath = ui->txtFilePath->text();
    if (filePath.isEmpty()) {
        ui->txtLog->append("No file selected.");
        return;
    }

    file.setFileName(filePath);
    if (!file.open(QIODevice::ReadOnly)) {
        ui->txtLog->append("Failed to open file.");
        return;
    }

    QByteArray fileData = file.readAll();
    file.close();

    ui->txtLog->append("Sending file: " + file.fileName());
    socket->write(fileData);
}

// Nhận phản hồi từ server
void MainWindow::onServerResponse()
{
    QByteArray response = socket->readAll();
    QString receivedKey = QString::fromUtf8(response).trimmed();

    if (!receivedKey.isEmpty()) {
        ui->txtKey->setText(receivedKey);
        ui->txtLog->append("Received Key from server: " + receivedKey);
    }
}

// Encrypt file using DES
void MainWindow::on_btnEncrypt_clicked()
{
    // Get the file path and key
    QString filePath = ui->txtFilePath->text();
    QString key = ui->txtKey->text();
    
    // Validate inputs
    if (filePath.isEmpty() || filePath == "No file selected") {
        ui->txtLog->append("Error: Please select a file first");
        return;
    }
    
    if (key.isEmpty()) {
        ui->txtLog->append("Error: Please connect to server first to get a key");
        return;
    }
    
    ui->txtLog->append("Starting encryption of file: " + filePath);
    ui->txtLog->append("Using key: " + key);
    
    try {
        // Check if input file exists and is readable
        // QFile inputFile(filePath);
        // if (!inputFile.exists()) {
        //     ui->txtLog->append("Error: Input file does not exist: " + filePath);
        //     return;
        // }
        
        // if (!inputFile.open(QIODevice::ReadOnly)) {
        //     ui->txtLog->append("Error: Cannot read input file: " + inputFile.errorString());
        //     return;
        // }
        
        // // Close the file after checking
        // inputFile.close();
        
        // Call the DES encryption function
        ui->txtLog->append("Calling DES encryption with key: " + key);
        std::string resultFile = perform_DES(key.toStdString(), filePath.toStdString());
        
        // Check if result is empty
        if (resultFile.empty()) {
            ui->txtLog->append("Error: Encryption returned an empty result filename");
            return;
        }
        
        // // Store the result file path
        // QString encryptedFilePath = QString::fromStdString(resultFile);
        
        // // Verify the encrypted file was created
        // QFile encryptedFile(encryptedFilePath);
        // if (!encryptedFile.exists()) {
        //     ui->txtLog->append("Warning: Encryption completed but output file not found: " + encryptedFilePath);
            
        //     // Try to create the output file with a default name if it doesn't exist
        //     QString defaultOutputPath = filePath + ".enc";
        //     ui->txtLog->append("Attempting to create output file: " + defaultOutputPath);
            
        //     // Check if we have the encrypted data somewhere
        //     // This would require modifying perform_DES to return the encrypted data
        //     // For now, just update the path
        //     encryptedFilePath = defaultOutputPath;
        // } else {
        //     // Check file size
        //     qint64 fileSize = encryptedFile.size();
        //     if (fileSize <= 0) {
        //         ui->txtLog->append("Warning: Encrypted file is empty: " + encryptedFilePath);
        //     } else {
        //         ui->txtLog->append("Encrypted file size: " + QString::number(fileSize) + " bytes");
        //     }
        // }
        
        // // Log the success
        // ui->txtLog->append("File encrypted successfully: " + encryptedFilePath);
        
        // // Update the file path to the encrypted file
        // ui->txtFilePath->setText(encryptedFilePath);
        
    } catch (const std::exception& e) {
        ui->txtLog->append("Encryption error: " + QString(e.what()));
    } catch (...) {
        ui->txtLog->append("Unknown error occurred during encryption");
    }
}
