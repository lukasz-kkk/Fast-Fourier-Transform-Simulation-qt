#include "fft.h"


QVector<QPointF> calculateWrappedSignalPoints(QVector<QPointF> &signalDataPoints, double wrappingFrequency){
    QVector<QPointF> resultVector;
    for(int i = 0; i < signalDataPoints.size(); ++i){
        double x = (double)i / 1000;
        std::complex<double> result = std::exp(std::complex<double>(0, -2 * M_PI * x * wrappingFrequency));

        QPointF point(result.real(), result.imag());
        point = point * signalDataPoints[i].y();
        resultVector.append(point);
    }

    return resultVector;
}

QVector<QPointF> calculateWrappedSignalPoints(QVector<QPointF> &signalDataPoints){
    QVector<QPointF> result;
    for(int i = 25; i < 300; i++){
        QPointF sum(0, 0);
        double frequency = (double)i / 25;
        QVector<QPointF> wrappedSignal = calculateWrappedSignalPoints(signalDataPoints, frequency);

        for (const QPointF& point : wrappedSignal) {
            sum += point;
        }


        QPointF avg = sum / wrappedSignal.size();
        double length = std::sqrt(avg.x() * avg.x() + avg.y() * avg.y());
        QPointF res(frequency, length);
        result.append(res);
    }
    return result;
}
