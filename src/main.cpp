#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QTranslator>
#include <QLocale>
#include <QFile>

#include "recordingmodel.h"
#include "utils.h"
#include "audioplayer.h"
#include "audiorecorder.h"
#include "audioprober.h"
#include "settingsmodel.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    qmlRegisterType<Recording>("Recorder", 1, 0, "Recording");
    qmlRegisterType<AudioProber>("Recorder", 1, 0, "AudioProber");
    qmlRegisterSingletonType<Utils>("Recorder", 1, 0, "Utils", [] (QQmlEngine *, QJSEngine *) -> QObject* {
        return new Utils;
    });
    qmlRegisterSingletonType<SettingsModel>("Recorder", 1, 0, "AudioPlayer", [] (QQmlEngine *, QJSEngine *) -> QObject* {
       return AudioPlayer::instance();
    });
    qmlRegisterSingletonType<SettingsModel>("Recorder", 1, 0, "AudioRecorder", [] (QQmlEngine *, QJSEngine *) -> QObject* {
       return AudioRecorder::instance();
    });
    qmlRegisterSingletonType<RecordingModel>("Recorder", 1, 0, "RecordingModel", [] (QQmlEngine *, QJSEngine *) -> QObject* {
        return RecordingModel::instance();
    });
    qmlRegisterSingletonType<SettingsModel>("Recorder", 1, 0, "SettingsModel", [] (QQmlEngine *, QJSEngine *) -> QObject* {
       return SettingsModel::instance();
    });

    QQmlApplicationEngine engine;

    // Translations
    QLocale locale;
    QString qmFilePath = QString("%1/%2.qm").arg("/usr/share/cyber-recorder/translations/").arg(locale.name());
    if (QFile::exists(qmFilePath)) {
        QTranslator *translator = new QTranslator(QGuiApplication::instance());
        if (translator->load(qmFilePath)) {
            QGuiApplication::installTranslator(translator);
        } else {
            translator->deleteLater();
        }
    }

    engine.load(QUrl(QStringLiteral("qrc:/qml/main.qml")));

    if (engine.rootObjects().isEmpty()) {
        return -1;
    }

    return app.exec();
}
