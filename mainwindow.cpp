#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPixmap>
#include <QLineEdit>
#include <QLabel>
#include "myvalidator.h"
#include "caculate.h"
#include <QKeyEvent>
#include <QTimer>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    ,editString("")
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setFixedSize(this->width(),this->height());
    setWindowTitle("簡易計算機");
    setWindowIcon(QIcon(":/machinePhoto.png"));
    //限制輸入為0~9,+-*/%()等符號 並設定為唯讀
    ui->lineEditResult->setValidator(new myValidator());
    ui->lineEditResult->setReadOnly(true);
    ui->listWidget->setStyleSheet("QListWidget{border:0px}");

    //連接所有按鈕輸入 加入字串最後 並重新輸出至輸入框
    connect(ui->integerBtn0,&QPushButton::clicked,[=](){
        this->editString += '0';
        ui->lineEditResult->setText(this->editString);
    });
    connect(ui->integerBtn1,&QPushButton::clicked,[=](){
        this->editString += '1';
        ui->lineEditResult->setText(this->editString);
    });
    connect(ui->integerBtn2,&QPushButton::clicked,[=](){
        this->editString += '2';
        ui->lineEditResult->setText(this->editString);
    });
    connect(ui->integerBtn3,&QPushButton::clicked,[=](){
        this->editString += '3';
        ui->lineEditResult->setText(this->editString);
    });
    connect(ui->integerBtn4,&QPushButton::clicked,[=](){
        this->editString += '4';
        ui->lineEditResult->setText(this->editString);
    });
    connect(ui->integerBtn5,&QPushButton::clicked,[=](){
        this->editString += '5';
        ui->lineEditResult->setText(this->editString);
    });
    connect(ui->integerBtn6,&QPushButton::clicked,[=](){
        this->editString += '6';
        ui->lineEditResult->setText(this->editString);
    });
    connect(ui->integerBtn7,&QPushButton::clicked,[=](){
        this->editString += '7';
        ui->lineEditResult->setText(this->editString);
    });
    connect(ui->integerBtn8,&QPushButton::clicked,[=](){
        this->editString += '8';
        ui->lineEditResult->setText(this->editString);
    });
    connect(ui->integerBtn9,&QPushButton::clicked,[=](){
        this->editString += '9';
        ui->lineEditResult->setText(this->editString);
    });
    connect(ui->operatorBtnAdd,&QPushButton::clicked,[=](){
        this->editString += '+';
        ui->lineEditResult->setText(this->editString);
    });
    connect(ui->operatorBtnSub,&QPushButton::clicked,[=](){
        this->editString += '-';
        ui->lineEditResult->setText(this->editString);
    });
    connect(ui->operatorBtnMultiple,&QPushButton::clicked,[=](){
        this->editString += '*';
        ui->lineEditResult->setText(this->editString);
    });
    connect(ui->operatorBtnDivision,&QPushButton::clicked,[=](){
        this->editString += '/';
        ui->lineEditResult->setText(this->editString);
    });
    connect(ui->operatorBtnMod,&QPushButton::clicked,[=](){
        this->editString += '%';
        ui->lineEditResult->setText(this->editString);
    });
    connect(ui->operatorBtnRight,&QPushButton::clicked,[=](){
       this->editString += ')';
        ui->lineEditResult->setText(this->editString);
    });
    connect(ui->operatorBtnLeft,&QPushButton::clicked,[=](){
       this->editString += '(';
        ui->lineEditResult->setText(this->editString);
    });
    connect(ui->operatorBtnDelete,&QPushButton::clicked,[=](){
        this->editString.erase(editString.end()-1,editString.end());
        ui->lineEditResult->setText(this->editString);
    });
    connect(ui->functionBtnReset,&QPushButton::clicked,[=](){
        this->editString = "";
        ui->lineEditResult->setText(this->editString);
    });
    connect(ui->lineEditResult,&QLineEdit::textChanged,[=](QString s){
        this->editString = s;
        ui->lineEditResult->setText(this->editString);
    });
    connect(ui->operatorBtnPower,&QPushButton::clicked,[=](){
        this->editString += '^';
        ui->lineEditResult->setText(this->editString);
    });


    // 連接等於按鈕
    connect(ui->operatorBtnEqual,&QPushButton::clicked,[=](){
        //轉為不帶有引號的c風格字串 再轉為std::string類別進行big_int運算
        std::string str(qPrintable(this->editString));
        bool isValid = true;
        // 判斷輸入是否合法
        // 左右括弧數是否相同
        // 運算子數是否比運算元數少1
        // 不合法輸出Unknown
        for(int i=0,lCnt=0,rCnt=0,numCnt=0,operatorCnt=0;i<(int)str.size();i++){
            if(str[i] <='9' && str[i]>='0'){
                while(str[i] <='9' && str[i]>='0'){
                    i++;
                }
                numCnt++;
            }
            if(str[i] == '(') lCnt++;
            if(str[i] == ')') rCnt++;
            if(str[i] == '+' || str[i] == '/' || str[i] == '*' || str[i] == '-' || str[i] == '%' || str[i] == '^'){
                   operatorCnt++;
            }
            if((i == (int)str.size()-1 || i==(int)str.size()) && (lCnt != rCnt  || operatorCnt != numCnt-1)) isValid = false;
            if(i == (int)str.size()-1 || i==(int)str.size()) qDebug()<<"lCnt :"<<lCnt << " rCnt :"<<rCnt<<" operatorCnt :"<<operatorCnt<<" numCnt :"<<numCnt;
        }
        if(isValid){
            QString s = QString::fromStdString(caculateAnwser(str).get());
            if(!caculateAnwser(str).get_pos()){
                s.push_front('-');
            }
            qDebug()<<"Answer : "<< s;
            // 將輸出歷史紀錄至listWidget
            // 最多22筆資料
            if(ui->listWidget->count() > 22){
                ui->listWidget->takeItem(ui->listWidget->count()-1);
                ui->listWidget->insertItem(0,QString::fromStdString(str+"="+s.toStdString()));
            } else {
                ui->listWidget->insertItem(0,QString::fromStdString(str+"="+s.toStdString()));
            }


            ui->lineEditResult->setText(s);
        } else {
            ui->lineEditResult->setText("Unknown!!");
            QTimer::singleShot(1000,this,[=](){
                ui->lineEditResult->setText("");
            });
        }
    });

    // 顯示/關閉 history 視窗
    connect(ui->actionHistory,&QAction::triggered,[=](){
        static int w = this->width(),h = this->height();
        if(isOpenHistory){
            ui->widget_4->hide();
            setFixedWidth(357);
            isOpenHistory = false;
        } else {
            setFixedWidth(w);
            ui->widget_4->show();
            isOpenHistory = true;
        }


    });
}
MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent *event){
    switch (event ->key()) {
    case Qt::Key_Return:
    case Qt::Key_Enter:
        ui->operatorBtnEqual->click();
        break;
    case Qt::Key_0:
        this->editString += '0';
        ui->lineEditResult->setText(this->editString);
        break;
    case Qt::Key_1:
        this->editString += '1';
        ui->lineEditResult->setText(this->editString);
        break;
    case Qt::Key_2:
        this->editString += '2';
        ui->lineEditResult->setText(this->editString);
        break;
    case Qt::Key_3:
        this->editString += '3';
        ui->lineEditResult->setText(this->editString);
        break;
    case Qt::Key_4:
        this->editString += '4';
        ui->lineEditResult->setText(this->editString);
        break;
    case Qt::Key_5:
        this->editString += '5';
        ui->lineEditResult->setText(this->editString);
        break;
    case Qt::Key_6:
        this->editString += '6';
        ui->lineEditResult->setText(this->editString);
        break;
    case Qt::Key_7:
        this->editString += '7';
        ui->lineEditResult->setText(this->editString);
        break;
    case Qt::Key_8:
        this->editString += '8';
        ui->lineEditResult->setText(this->editString);
        break;
    case Qt::Key_9:
        this->editString += '9';
        ui->lineEditResult->setText(this->editString);
        break;
    case Qt::Key_Backspace:
    case Qt::Key_Delete:
        this->editString.erase(editString.end()-1,editString.end());
        ui->lineEditResult->setText(this->editString);
        break;
    case Qt::Key_Plus:
        this->editString += '+';
        ui->lineEditResult->setText(this->editString);
        break;
    case Qt::Key_Asterisk:
        this->editString += '*';
        ui->lineEditResult->setText(this->editString);
        break;
    case Qt::Key_Minus:
        this->editString += '-';
        ui->lineEditResult->setText(this->editString);
        break;
    case Qt::Key_Slash:
        this->editString += '/';
        ui->lineEditResult->setText(this->editString);
        break;
    default:
        break;
    }
}



