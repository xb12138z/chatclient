#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>
#include "global.h"
#include "ui_logindialog.h"


namespace Ui {
class LoginDialog;
}
//C++中的多态性的体现，子类指针可以被赋给父指针
class LoginDialog : public QDialog//QLoginDialog 继承于 QDialog  而QDialog 继承于 QWiget  所以   LoginDialog是QWiget的子类，有其所有功能
{
    Q_OBJECT

public:
    explicit LoginDialog(QWidget *parent = nullptr);//禁止隐式类型转换 ：
    //eg:
    // class MyClass {
    // public:
    //     MyClass(int x) { /*...*/ }
    // };
    // void func(MyClass m) { }
    // func(42);  // ✅ 允许隐式转换 int -> MyClass
    //但是如果有了explicit修饰以上语句不能执行，要改为：
    // func（MyClass（42））

    ~LoginDialog();

private:
    void initHttpHandlers();//登录回调函数注册
    void initHead();//样式设计
    Ui::LoginDialog *ui;
    bool checkUserValid();
    bool checkPwdValid();
    void AddTipErr(TipErr te,QString tips);
    void DelTipErr(TipErr te);
    QMap<TipErr, QString> _tip_errs;
    void showTip(QString str,bool b_ok);
    bool enableBtn(bool enabled);
    QMap<ReqId, std::function<void(const QJsonObject&)>> _handlers;//ReqId对应的回调函数的处理
    int _uid;
    QString _token;


public slots:
    void slot_forget_pwd();
    void on_loginButton_clicked();
    void slot_login_mod_finish(ReqId id , QString res , ErrorCodes err);
    void slot_tcp_con_finish(bool bsuccess);
    void slot_login_failed(int );

signals:
    void switchRegister();
    void switchReset();
    void sig_connect_tcp(ServerInfo);
};

#endif // LOGINDIALOG_H
