#ifndef PLOTTER_H
#define PLOTTER_H

#include <QFrame>
#include <QtCharts>
#include <QChartView>
#include <QLineSeries>
#include <QValueAxis>
#include <complex>
#include "fft.h"

class Plotter : public QFrame
{
public:
    Plotter(QFrame *parent = nullptr, int frequency = 0, int amplitude = 0, int signalRangeMin = 0, int signalRangeMax = 0);
    void generateSignal();
    void combineSignal(QVector<QPointF> &signalToCombinePoints);
    void updateAxisY();
    void updateAxisX(int minValue, int maxValue);
    void clearData();
    void setColor(QColor color);
    void generateWrappedSignal(QVector<QPointF> &combinedSignalDataPoints);
    void showFourierTransform(QVector<QPointF> &combinedSignalDataPoints);
    double maxSignalValue();
    QVector<QPointF> getSignalDataPoints() const;

    void setFrequency(int newFrequency);
    void setAmplitude(int newAmplitude);
    void setAxisXTitle(QString title);

    void setWrappingFrequency(double newWrappingFrequency);

    void setSignalRangeMin(int newSignalRangeMin);

    void setSignalRangeMax(int newSignalRangeMax);

private:
    int frequency;
    int amplitude;
    int signalRangeMin;
    int signalRangeMax;
    double wrappingFrequency;
    QChartView *chartView;
    QValueAxis *axisY;
    QValueAxis *axisX;
    QLineSeries *signalDataSeries;
    QVector<QPointF> signalDataPoints;
    QChart *chart;
    QFrame *chartFrame;
};

#endif // PLOTTER_H
