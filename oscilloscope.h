#ifndef OSCILLOSCOPE_H
#define OSCILLOSCOPE_H

#include <QThread>
#include <QCoreApplication>
#include <QVector>
#include <QByteArray>
#include <QtEndian>
#include <QTest>
#include <QAudioOutput>
#include <QAudioDeviceInfo>
#include <QAudioFormat>

class Oscilloscope : public QThread
{
    Q_OBJECT
public:
    explicit Oscilloscope(QAudioDeviceInfo info, int sampleRate, int channelCount, int channelX, int channelY, int fps, QObject *parent = nullptr);
    ~Oscilloscope();

    void run();
    int stop(int time = 0);
    bool state();
    int isFormatSupported();

    struct Point {
        qint16 x = 0;
        qint16 y = 0;
    };
    QVector<Point> points;
    int pointsDataSize = 0;
    bool refresh = false;
signals:

public slots:

private:
    bool stopMe = false;
    bool stateStart = false;

    QAudioDeviceInfo audioDeviceInfo;
    QAudioFormat format;
    QAudioOutput* output = nullptr;
    QIODevice* device = nullptr;
    QByteArray buffer;
    int bufferDataSize = 0;

    int sampleRate;
    int channelCount;
    int channelX;
    int channelY;
    int fps;
};

#endif // OSCILLOSCOPE_H
