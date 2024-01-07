#include "plotter.h"

Plotter::Plotter(QFrame *parent, int frequency, int amplitude, int signalRangeMin, int signalRangeMax)
    : frequency(frequency), amplitude(amplitude), signalRangeMin(signalRangeMin), signalRangeMax(signalRangeMax), chartFrame(parent) {
    signalDataSeries = new QLineSeries();

    chart = new QChart();
    chart->legend()->hide();
    chart->addSeries(signalDataSeries);

    axisY = new QValueAxis();
    axisY->setRange(-4.0, 4.0);
    chart->addAxis(axisY, Qt::AlignLeft);
    signalDataSeries->attachAxis(axisY);

    axisX = new QValueAxis();
    axisX->setRange(signalRangeMin, signalRangeMax);
    chart->addAxis(axisX, Qt::AlignBottom);
    signalDataSeries->attachAxis(axisX);

    chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setParent(chartFrame);

    chartView->resize(chartFrame->width(), chartFrame->height());
}

void Plotter::setColor(QColor color){
    QPen pen(color);
    signalDataSeries->setPen(pen);
}

void Plotter::generateSignal(){
    signalDataSeries->clear();
    signalDataPoints.clear();
    for(int i = signalRangeMin; i < signalRangeMax * 1000; ++i){
        double x = (double)i / 1000;
        double y = amplitude * std::sin(frequency * x * 2 * M_PI) + amplitude;
        signalDataPoints.append(QPointF(x, y));
    }
    signalDataSeries->replace(signalDataPoints);
    updateAxisY();
}

void Plotter::combineSignal(QVector<QPointF> &signalToCombinePoints){
    for (int i = 0; i < signalDataPoints.size(); ++i) {
        signalDataPoints[i].setY(signalDataPoints[i].y() + signalToCombinePoints[i].y());
    }
    signalDataSeries->replace(signalDataPoints);
    updateAxisY();
}

QVector<QPointF> Plotter::getSignalDataPoints() const{
    return signalDataPoints;
}

void Plotter::setFrequency(int newFrequency)
{
    frequency = newFrequency;
}

void Plotter::setAmplitude(int newAmplitude)
{
    amplitude = newAmplitude;
}

void Plotter::setAxisXTitle(QString title){
    axisX->setTitleText(title);
}

void Plotter::setWrappingFrequency(double newWrappingFrequency)
{
    wrappingFrequency = newWrappingFrequency;
}

void Plotter::setSignalRangeMin(int newSignalRangeMin)
{
    signalRangeMin = newSignalRangeMin;
}

void Plotter::setSignalRangeMax(int newSignalRangeMax)
{
    signalRangeMax = newSignalRangeMax;
}

void Plotter::updateAxisY(){
    double maxY = maxSignalValue();
    axisY->setRange(-1, maxY + 2);
}

void Plotter::updateAxisX(int minValue, int maxValue){
    axisX->setRange(minValue, maxValue);
}

double Plotter::maxSignalValue(){
    double maxY = std::numeric_limits<double>::lowest();

    for (const QPointF& point : signalDataPoints) {
        if (point.y() > maxY) {
            maxY = point.y();
        }
    }

    return maxY;
}

void Plotter::clearData(){
    setFrequency(0);
    setAmplitude(0);
    generateSignal();
}

void Plotter::generateWrappedSignal(QVector<QPointF> &combinedSignalDataPoints){
    signalDataSeries->clear();

    QVector<QPointF> wrappedSignalDataPoints = calculateWrappedSignalPoints(combinedSignalDataPoints, wrappingFrequency);

    double maxY = std::numeric_limits<double>::lowest();

    for (const QPointF& point : combinedSignalDataPoints) {
        if (point.y() > maxY) {
            maxY = point.y();
        }
    }

    maxY = maxY + 2;
    axisX->setRange(-maxY, maxY);
    axisY->setRange(-maxY, maxY);
    signalDataSeries->replace(wrappedSignalDataPoints);
}

void Plotter::showFourierTransform(QVector<QPointF> &combinedSignalDataPoints){
    signalDataSeries->clear();
    signalDataPoints.clear();

    signalDataPoints = calculateFourierTransform(combinedSignalDataPoints);

    signalDataSeries->replace(signalDataPoints);
    updateAxisY();
    axisX->setTickType(QValueAxis::TicksDynamic);
    axisX->setTickAnchor(0.0);
    axisX->setTickInterval(1);
}






