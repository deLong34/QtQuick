#ifndef LOGINWIDGET_H
#define LOGINWIDGET_H

#include <QDialog>
#include <QPropertyAnimation>
#include <QSequentialAnimationGroup>
#include <QParallelAnimationGroup>

namespace Ui {
class LoginWidget;
}

class LoginWidget : public QDialog
{
    Q_OBJECT
    Q_PROPERTY(QColor color READ color WRITE setColor)
    Q_PROPERTY(float opacity READ opacity WRITE setOpacity)

public:
    explicit LoginWidget(QWidget *parent = nullptr);
    ~LoginWidget();

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();

private:
    Ui::LoginWidget *ui;
    QSequentialAnimationGroup *animationWindowGroup;
    QSequentialAnimationGroup *animationRedFlashGroup;
    QParallelAnimationGroup *animationAllGroups;
    bool animated;
    void SetAnimation();
    QColor m_color;
    const QColor &color() const {return m_color;};
    void setColor(const QColor &newColor);
    float m_opacity;
    const float &opacity() const {return m_opacity;};
    void setOpacity(const float &newOpacity);
    QPropertyAnimation *animationOpacity;
    QString login, password;
    bool isLoginCorrect();
    void CloseWindow();
};

#endif // LOGINWIDGET_H
