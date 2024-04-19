#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    QSqlDatabase sqlitedb = QSqlDatabase::addDatabase("QSQLITE");
    sqlitedb.setDatabaseName("D:/login_work/login.db");

    QString username = ui->lineEdit->text();
    QString password = ui->lineEdit_2->text();

    if (sqlitedb.open()) {
        QSqlQuery query(sqlitedb);
        query.prepare("SELECT * FROM loginDetails WHERE username = :username AND password = :password");
        query.bindValue(":username", username);
        query.bindValue(":password", password);

        if (query.exec()) {
            if (query.next()) { // Username and password found
                ui->lineEdit_3->setText("Login successful!");
            } else {
                ui->lineEdit_3->setText("Invalid username or password.");
            }
        }
        else {
            ui->lineEdit_3->setText("Login failed (database error).");
        }

    }else {
        // Handle database connection error
        ui->lineEdit_3->setText("Connection failed!");
    }

     sqlitedb.close(); // Close the database connection after use
}

