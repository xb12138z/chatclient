#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)//构造函数
    //将所有窗口都放入父指针后，可以在析构的时候自动析构
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);//this为指向MainWindow自身的指针
    _login_dlg = new LoginDialog(this);//创建类,其中this为父窗口
    _login_dlg->setWindowFlags(Qt::CustomizeWindowHint|Qt::FramelessWindowHint);//改变窗口样式 ： 自定义 、 不边框
    setCentralWidget(_login_dlg);//将_login_dlg作为中央窗口控件   //setCentralWidget(QWidget *widget);传入QWideget类的指针
    //_login_dlg->show();//展示该窗口

    //创建和注册消息链接
    connect(_login_dlg, &LoginDialog::switchRegister,this,&MainWindow::SlotSwitchReg);//槽函数
    /*
    connect(sender, signal, receiver, slot);
    第一个参数（sender）：触发信号的对象。这个对象发出信号，通常是一个控件（比如按钮、文本框、等）或者任何 Qt 对象。
    第二个参数（signal）：发送的信号。信号是由 sender 发出的特定事件，比如按钮被点击、文本框内容变化等。例如，&QPushButton::clicked 表示按钮的 clicked() 信号。
    第三个参数（receiver）：接收信号的对象。这是在信号触发时响应信号的对象，通常是当前类的实例（如 this），也可以是其他类的实例。
    第四个参数（slot）：响应信号的槽函数。这是在信号触发时调用的函数，通常是类中定义的成员函数。
    */

    //链接登录页面忘记密码信号
    connect(_login_dlg, &LoginDialog::switchReset,this,&MainWindow::SlotSwitchReset);

    //链接登陆后的聊天界面
    connect(TcpMgr::GetInstance().get(),&TcpMgr::sig_switch_chatdlg,this,&MainWindow::SlotSwitchChat);

    //emit TcpMgr::GetInstance()->sig_switch_chatdlg();
}

MainWindow::~MainWindow()//析构函数
{
    delete ui;
    // if(_login_dlg){
    //     delete _login_dlg;
    //     _login_dlg = nullptr;
    // }
    // if(_reg_dlg){
    //     delete _reg_dlg;
    //     _reg_dlg = nullptr;
    // }
}

void MainWindow::SlotSwitchReg()
{
    _reg_dlg = new RegisterDialog(this);

    _reg_dlg->setWindowFlags(Qt::CustomizeWindowHint|Qt::FramelessWindowHint);
    //_reg_dlg->hide();

    //链接注册界面，返回登录界面
    connect(_reg_dlg, &RegisterDialog::sigSwitchLogin,this,&MainWindow::SlotSwitchLogin);

    setCentralWidget(_reg_dlg);
    _login_dlg->hide();
    _reg_dlg->show();
}

void MainWindow::SlotSwitchLogin()
{
    ui->setupUi(this);//this为指向MainWindow自身的指针
    _login_dlg = new LoginDialog(this);//创建类,其中this为父窗口
    _login_dlg->setWindowFlags(Qt::CustomizeWindowHint|Qt::FramelessWindowHint);//改变窗口样式 ： 自定义 、 不边框
    setCentralWidget(_login_dlg);//将_login_dlg作为中央窗口控件   //setCentralWidget(QWidget *widget);传入QWideget类的指针
    //_login_dlg->show();//展示该窗口

    //创建和注册消息链接
    connect(_login_dlg, &LoginDialog::switchRegister,this,&MainWindow::SlotSwitchReg);//槽函数

    //链接登录页面忘记密码信号
    connect(_login_dlg, &LoginDialog::switchReset,this,&MainWindow::SlotSwitchReset);
}

void MainWindow::SlotSwitchReset()
{
    _reset_dlg = new ResetDialog(this);

    _reset_dlg->setWindowFlags(Qt::CustomizeWindowHint|Qt::FramelessWindowHint);

    _login_dlg->hide();
    _reset_dlg->show();
    setCentralWidget(_reset_dlg);

    //链接注册界面，返回登录界面
    connect(_reset_dlg, &ResetDialog::switchLogin,this,&MainWindow::SlotSwitchLogin2);
}

void MainWindow::SlotSwitchLogin2()
{
    ui->setupUi(this);//this为指向MainWindow自身的指针
    _login_dlg = new LoginDialog(this);//创建类,其中this为父窗口
    _login_dlg->setWindowFlags(Qt::CustomizeWindowHint|Qt::FramelessWindowHint);//改变窗口样式 ： 自定义 、 不边框
    setCentralWidget(_login_dlg);//将_login_dlg作为中央窗口控件   //setCentralWidget(QWidget *widget);传入QWideget类的指针

    _reset_dlg->hide();
    _login_dlg->show();//展示该窗口

    //创建和注册消息链接
    connect(_login_dlg, &LoginDialog::switchRegister,this,&MainWindow::SlotSwitchReg);//槽函数

    //链接登录页面忘记密码信号
    connect(_login_dlg, &LoginDialog::switchReset,this,&MainWindow::SlotSwitchReset);
}

void MainWindow::SlotSwitchChat()
{
    _chat_dlg = new ChatDialog();
    _chat_dlg -> setWindowFlags(Qt::CustomizeWindowHint|Qt::FramelessWindowHint);
    setCentralWidget(_chat_dlg);
    _chat_dlg->show();
    _login_dlg->hide();
    this->setMinimumSize(QSize(1050,900));
    this->setMaximumSize(QWIDGETSIZE_MAX,QWIDGETSIZE_MAX);
}
