#include "mainwindow.h"
#include <QApplication>
#include <QFile>
#include "global.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);//管理全局资源的GUI控件  ——  整个 GUI 应用程序必须有且仅有一个 QApplication 实例。
    QFile qss(":/style/stylesheet.qss");//打开示例样式
    if(qss.open(QFile::ReadOnly)){
        qDebug("open success");
        QString style = QLatin1String(qss.readAll());//读取.qss风格记录文件
        a.setStyleSheet(style);//对QApplication为整个应用程序设置全局样式表  ，对widget为单个控件生效
        qss.close();
    }else{
        qDebug("Open failed");
    }

    QString filename = "config.ini";
    QString app_path = QCoreApplication::applicationDirPath();
    QString config_path = QDir::toNativeSeparators(app_path + QDir::separator() +filename) ;//separator()用于将文件中的\转换为/  ,toNativeSeparators同理
    QSettings settings(config_path,QSettings::IniFormat);
    QString gate_host = settings.value("GateServer/host").toString();
    QString gate_port = settings.value("GateServer/port").toString();
    gate_url_prefix ="http://"+gate_host+":"+gate_port;
    MainWindow w;//整个控件的主窗口
    w.show();

    return a.exec();
}
