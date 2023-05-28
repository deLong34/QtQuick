#include "loginwidget.h"
#include "ui_loginwidget.h"

LoginWidget::LoginWidget(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginWidget)
{
    ui->setupUi(this);
    animated = false;
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::Window);
    QPalette pal(palette());
    pal.setColor(QPalette::Window, Qt::white);
    this->setAutoFillBackground(true);
    this->setPalette(pal);
    login = "login";
    password = "password";
    animationOpacity = new QPropertyAnimation(this, "opacity", this);
    connect(animationOpacity, &QAbstractAnimation::finished, this, &LoginWidget::CloseWindow);
}

LoginWidget::~LoginWidget()
{
    delete ui;
}

void LoginWidget::on_pushButton_clicked()
{
    this->close();
}

void LoginWidget::on_pushButton_2_clicked()
{
    if(!animated)
    {
        SetAnimation();
    }
    if(isLoginCorrect())
    {
        animationOpacity->start();
    } else
    {
        animationAllGroups->start();
    }
}

void LoginWidget::SetAnimation()
{
    animationWindowGroup = new QSequentialAnimationGroup(this);

    QPropertyAnimation *animationToLeft = new QPropertyAnimation(this, "geometry");
    animationToLeft->setDuration(40);
    animationToLeft->setStartValue(this->geometry());
    animationToLeft->setEndValue(this->geometry().translated(-5, 0));

    animationWindowGroup->addAnimation(animationToLeft);

    QPropertyAnimation *animationToRight = new QPropertyAnimation(this, "geometry");
    animationToRight->setDuration(80);
    animationToRight->setStartValue(animationToLeft->endValue());
    animationToRight->setEndValue(animationToLeft->endValue().toRect().translated(10,0));

    animationWindowGroup->addAnimation(animationToRight);

    QPropertyAnimation *animationToMidle = new QPropertyAnimation(this, "geometry");
    animationToMidle->setDuration(40);
    animationToMidle->setStartValue(animationToRight->endValue());
    animationToMidle->setEndValue(animationToRight->endValue().toRect().translated(-5, 0));

    animationWindowGroup->addAnimation(animationToMidle);

    animationRedFlashGroup = new QSequentialAnimationGroup(this);

    QPropertyAnimation *animationRedToBlack = new QPropertyAnimation(this, "color", this);
    animationRedToBlack->setDuration(1000);
    animationRedToBlack->setStartValue(QColor(Qt::red));
    animationRedToBlack->setEndValue(QColor(Qt::black));

    animationRedFlashGroup->addAnimation(animationRedToBlack);
    animationAllGroups = new QParallelAnimationGroup(this);
    animationAllGroups->addAnimation(animationWindowGroup);
    animationAllGroups->addAnimation(animationRedFlashGroup);
    animationOpacity->setDuration(1000);
    animationOpacity->setStartValue(1.0);
    animationOpacity->setEndValue(0.0);
    animated = true;
}

void LoginWidget::setColor(const QColor &newColor)
{
    QString style = QString("QLineEdit {color: rgb(%1, %2, %3); }").
                    arg(newColor.red()).
                    arg(newColor.green()).
                    arg(newColor.blue());
    ui->lineEdit_Name->setStyleSheet(style);
    ui->lineEdit_Password->setStyleSheet(style);
    m_color = newColor;
}

void LoginWidget::setOpacity(const float &newOpacity)
{
    this->setWindowOpacity(newOpacity);
    m_opacity = newOpacity;
}

bool LoginWidget::isLoginCorrect()
{
    if(ui->lineEdit_Name->text() == login && ui->lineEdit_Password->text() == password)
    {
        return true;
    }
    return false;
}

void LoginWidget::CloseWindow()
{
    this->close();
    this->setWindowOpacity(1.0);
}
