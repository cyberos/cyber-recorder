/*
 * SPDX-FileCopyrightText: 2020 Jonah Brüchert <jbb@kaidan.im>
 * SPDX-FileCopyrightText: 2020 Devin Lin <espidev@gmail.com>
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef AUDIORECORDER_H
#define AUDIORECORDER_H

#include <QAudioRecorder>
#include <QAudioProbe>
#include <QAudioEncoderSettings>
#include <QStandardPaths>
#include <QUrl>
#include <QFileInfo>
#include <QTimer>
#include <QQmlEngine>
#include <QCoreApplication>

#include "audioprober.h"
#include "recordingmodel.h"

class AudioRecorder;
static AudioRecorder *s_audioRecorder = nullptr;

class AudioRecorder : public QAudioRecorder
{
    Q_OBJECT
    Q_PROPERTY(QStringList audioInputs READ audioInputs CONSTANT)
    Q_PROPERTY(QStringList supportedAudioCodecs READ supportedAudioCodecs CONSTANT)
    Q_PROPERTY(QStringList supportedContainers READ supportedContainers CONSTANT)
    Q_PROPERTY(QString audioCodec READ audioCodec WRITE setAudioCodec NOTIFY audioCodecChanged)
    Q_PROPERTY(int audioQuality READ audioQuality WRITE setAudioQuality NOTIFY audioQualityChanged)
    Q_PROPERTY(QString containerFormat READ containerFormat WRITE setContainerFormat)
    Q_PROPERTY(AudioProber* prober READ prober CONSTANT)
    
private:
    explicit AudioRecorder(QObject *parent = nullptr);
    void handleStateChange(QAudioRecorder::State state);

    void checkFolder();

    QAudioEncoderSettings m_encoderSettings {};
    AudioProber *m_audioProbe;

    QString recordingName = {}; // rename recording after recording finishes
    QString savedPath = {}; // updated after the audio file is renamed
    int cachedDuration = 0; // cache duration (since it is set to zero when the recorder is in StoppedState)
    bool resetRequest = false;
    
public:
    static AudioRecorder* instance()
    {
        if (!s_audioRecorder) {
            s_audioRecorder = new AudioRecorder(qApp);
        }
        return s_audioRecorder;
    }
    
    AudioProber* prober()
    {
        return m_audioProbe;
    }
    
    QString audioCodec() 
    {
        return m_encoderSettings.codec();
    }

    void setAudioCodec(const QString &codec);

    int audioQuality() 
    {
        return m_encoderSettings.quality();
    }
    void setAudioQuality(int quality);
    
    Q_INVOKABLE void reset()
    {
        resetRequest = true;
        stop();
    }
    
    Q_INVOKABLE void saveRecording();

    void renameCurrentRecording();
    Q_INVOKABLE void setRecordingName(const QString &rName) {
        recordingName = rName;
    }
    
signals:
    void audioCodecChanged();
    void audioQualityChanged();
};

#endif // AUDIORECORDER_H
