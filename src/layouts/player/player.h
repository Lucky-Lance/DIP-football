/****************************************************************************
**
** Copyright (C) 2017 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef PLAYER_H
#define PLAYER_H

#include <QWidget>
#include <QMediaPlayer>
#include "player/qmediaplaylist.h"
#include <QMediaMetaData>
#include <QProcess>
#include "common.h"
#include "connection.h"
#include "fileUploader.h"
#include "imageViewer.h"
QT_BEGIN_NAMESPACE
class QAbstractItemView;
class QLabel;
class QMediaPlayer;
class QModelIndex;
class QPushButton;
class QComboBox;
class QSlider;
class QStatusBar;
class QVideoWidget;
QT_END_NAMESPACE

class PlaylistModel;
class HistogramWidget;

class Player : public QWidget
{
    Q_OBJECT

public:
    explicit Player(QWidget *parent, ConfigMessage*, Connection*, FileUploader*);
    ~Player();

    bool isPlayerAvailable() const;

signals:
    void fullScreenChanged(bool fullScreen);

private slots:
    void open();
    void durationChanged(qint64 duration);
    void positionChanged(qint64 progress);
    void previousClicked();
    void seek(int seconds);
    void statusChanged(QMediaPlayer::MediaStatus status);
    void bufferingProgress(float progress);
    void videoAvailableChanged(bool available);
    void displayErrorMessage();
    void audioOutputChanged(int);
    void calibrateFinished();
private:
    void setSource();
    void changeSource();
    bool loadJson();
    void setPlayerModel(QAbstractItemModel*);
    void setTrackInfo(const QString &info);
    void setStatusInfo(const QString &info);
    void handleCursor(QMediaPlayer::MediaStatus status);
    void updateDurationInfo(qint64 currentInfo);
    void calibrate();
    void saveJson();
    int getCurrentFrame();
    void loadPlayerModel();
    QAbstractItemModel *createPlayerModel(int frame, int team);
    QString getTimeInfo(qint64);
    QString trackName(const QMediaMetaData &metaData, int index);
    int currentSource = 0;
    QMap<int, QMap<int, FootballPlayer>>* frames1 = nullptr;
    QMap<int, QMap<int, FootballPlayer>>* frames2 = nullptr;
    QMediaPlayer *m_player_left = nullptr;
    QMediaPlayer *m_player_right = nullptr;
    QAudioOutput *m_audioOutput = nullptr;
    QVideoWidget *m_videoWidget_left = nullptr;
    QVideoWidget* m_videoWidget_right = nullptr;
    QSlider *m_slider = nullptr;
    QLabel *m_labelDuration = nullptr;
//    QPushButton *m_fullScreenButton = nullptr;
    QPushButton* calibrationButton = nullptr;
    QPushButton* loadJsonButton = nullptr;
    QPushButton* saveJsonButton = nullptr;
    QComboBox *m_audioOutputCombo = nullptr;
    QLabel *m_statusLabel = nullptr;
    QStatusBar *m_statusBar = nullptr;
    QString m_trackInfo;
    QString m_statusInfo;
    qint64 m_duration;
    QTextBrowser* textBrowser = nullptr;
    // player QComboBox
    QSortFilterProxyModel* playerDisplayModel = nullptr;
    QTreeView* playerDisplayView = nullptr;
    int currentFrameViewed = 0;
    int currentTeamViewed = 0;
    QAbstractItemModel* currentModel;
    // config message
    ConfigMessage* configMessage;
    // networking
    Connection* connection;
    FileUploader* fileUploader;
    QProcess* calibrateProgress;
    // image Viewer

public:
    void updateSource();

};

#endif // PLAYER_H
