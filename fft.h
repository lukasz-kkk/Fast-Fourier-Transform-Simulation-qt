#ifndef FFT_H
#define FFT_H

#include <QLineSeries>
#include <QVector>
#include <complex>
#include <iostream>

QVector<QPointF> calculateWrappedSignalPoints(QVector<QPointF> &signalDataPoints, double wrappingFrequency);

QVector<QPointF> calculateFourierTransform(QVector<QPointF> &signalDataPoints);

#endif // FFT_H


