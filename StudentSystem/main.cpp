﻿#include "LoginDialog.h"
#include "GBK.h"
#include <QApplication>
#include <QIcon>
#include <QSqlDatabase>
#include <QDebug>
#include <QMessageBox>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //设置app的图标
    a.setWindowIcon(QIcon("logo.ico"));
    //连接mysql数据库
    QSqlDatabase db=QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("127.0.0.1");
    db.setUserName("root");
    db.setPassword("ykf201497");
    db.setDatabaseName("school");
    if(db.open())
    {
    LoginDialog w;
    w.show();
    return a.exec();
    }
    else
    {
        QMessageBox::information(NULL,GBK::a2w("提示"),
			GBK::a2w("系统载入数据库失败，无法运行"),QMessageBox::Yes);
		return 0;
    }
    return 0;
}
