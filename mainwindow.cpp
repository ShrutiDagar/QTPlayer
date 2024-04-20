#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPixmap>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    Player = new QMediaPlayer();
    Audio = new QAudioOutput();

    ui->pushButton_Play_Pause->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
    ui->pushButton_Stop->setIcon(style()->standardIcon(QStyle::SP_MediaStop));
    ui->pushButton_Seek_Backward->setIcon(style()->standardIcon(QStyle::SP_MediaSeekBackward));
    ui->pushButton_Seek_Forward->setIcon(style()->standardIcon(QStyle::SP_MediaSeekForward));
    ui->pushButton_Volume->setIcon(style()->standardIcon(QStyle::SP_MediaVolume));


    // Install event filter on the video widget
    QPixmap pix("C:/Users/Lenovo/OneDrive/Documents/MyVideoPlayer/theia.png");
    ui->overlayLabel->setPixmap(pix.scaled(700,500, Qt::KeepAspectRatio));
    ui->groupBox_Video->installEventFilter(this);
    ui->overlayLabel->setVisible(false);
    ui->overlayLabel->raise();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionOpen_triggered()
{
    QString FileName = QFileDialog::getOpenFileName(this, tr("Select Video File"), "", tr("MP4 Files (*.mp4)"));
    if (!FileName.isEmpty()) {
        Video = new QVideoWidget(ui->groupBox_Video);
        Video->setGeometry(5, 5, ui->groupBox_Video->width() - 10, ui->groupBox_Video->height() - 10);
        Player->setVideoOutput(Video);
        Player->setAudioOutput(Audio);
        Player->setSource(QUrl::fromLocalFile(FileName));
        Video->show();
    }
}



void MainWindow::on_pushButton_Play_Pause_clicked()
{
    if (IS_Pause) {
        Player->play();
        ui->pushButton_Play_Pause->setIcon(style()->standardIcon(QStyle::SP_MediaPause));
    } else {
        Player->pause();
        ui->pushButton_Play_Pause->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
    }
    IS_Pause = !IS_Pause;
}

void MainWindow::on_pushButton_Stop_clicked()
{
    Player->stop();
}

void MainWindow::on_pushButton_Volume_clicked()
{
    if (IS_Muted) {
        Audio->setMuted(false);
        ui->pushButton_Volume->setIcon(style()->standardIcon(QStyle::SP_MediaVolume));
    } else {
        Audio->setMuted(true);
        ui->pushButton_Volume->setIcon(style()->standardIcon(QStyle::SP_MediaVolumeMuted));
    }
    IS_Muted = !IS_Muted;
}


void MainWindow::on_pushButton_Seek_Forward_clicked()
{
    int currentPosition = Player->position() + 20000;  // 20 seconds forward
    Player->setPosition(currentPosition);
}

void MainWindow::on_pushButton_Seek_Backward_clicked()
{
    int currentPosition = Player->position() - 20000;  // 20 seconds backward
    Player->setPosition(currentPosition);
}

bool MainWindow::eventFilter(QObject *obj, QEvent *event)
{
    if (obj == ui->groupBox_Video && event->type() == QEvent::MouseButtonDblClick) {
        QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
        if (mouseEvent->button() == Qt::LeftButton) {
            // Double-click handling
            if (!IS_Pause) {
                Player->pause();

                ui->pushButton_Play_Pause->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
                Video->setVisible(false); // Hide video widget
                ui->overlayLabel->setVisible(true);
                ui->overlayLabel->raise();
            } else {
                Player->play();
                ui->pushButton_Play_Pause->setIcon(style()->standardIcon(QStyle::SP_MediaPause));
                ui->overlayLabel->setVisible(false); // Hide overlay label
                Video->setVisible(true);
            }


            IS_Pause = !IS_Pause;

            return true;  // Event handled
        }
    }
    return QObject::eventFilter(obj, event);
}
