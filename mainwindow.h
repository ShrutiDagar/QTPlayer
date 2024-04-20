#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMediaPlayer>
#include <QVideoWidget>
#include <QAudioOutput>
#include <QFileDialog>
#include <QStyle>
#include <QMouseEvent>
#include <QLabel>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionOpen_triggered();
    void on_pushButton_Play_Pause_clicked();
    void on_pushButton_Stop_clicked();
    void on_pushButton_Volume_clicked();
    void on_pushButton_Seek_Forward_clicked();
    void on_pushButton_Seek_Backward_clicked();

protected:
    bool eventFilter(QObject *obj, QEvent *event) override;

private:
    Ui::MainWindow *ui;
    QMediaPlayer *Player;
    QVideoWidget *Video;
    QAudioOutput *Audio;
    //QPixmap overlayLabel;
    bool IS_Pause = true;
    bool IS_Muted = false;
};

#endif // MAINWINDOW_H
