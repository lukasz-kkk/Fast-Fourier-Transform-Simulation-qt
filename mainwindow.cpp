#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->frequencyInfo->setText(QString::number(ui->frequencySlider->value()));
    ui->amplitudeInfo->setText(QString::number(ui->amplitudeSlider->value()));

    chartGeneratedSignal = new Plotter(ui->chartGenerated, 2, 2, 0, 6);
    chartGeneratedSignal->setAxisXTitle("time (s)");
    chartGeneratedSignal->generateSignal();

    chartCombinedSignals = new Plotter(ui->chartCombined, 0, 0, 0, 6);
    chartCombinedSignals->setAxisXTitle("time (s)");
    chartCombinedSignals->generateSignal();

    chartWrappedSignal = new Plotter(ui->chartWrappedSignal, 0, 0);
    chartFourierTransform = new Plotter(ui->chartFourierTransform, 2, 2, 1, 12);
    QColor color(255, 94, 5); // orange
    chartFourierTransform->setColor(color);
    chartFourierTransform->setAxisXTitle("frequency (Hz)");

    ui->signalsList->setAlternatingRowColors(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_combineButton_clicked()
{
    QVector<QPointF> generatedsignalDataPoints = chartGeneratedSignal->getSignalDataPoints();
    chartCombinedSignals->combineSignal(generatedsignalDataPoints);

    QVector<QPointF> combinedSignalPoints = chartCombinedSignals->getSignalDataPoints();
    double wrappingFrequency = (double)ui->wrappingFrequencySlider->value() / 100;
    chartWrappedSignal->setWrappingFrequency(wrappingFrequency);
    chartWrappedSignal->generateWrappedSignal(combinedSignalPoints);
    ui->wrappingFrequencyInfo->setValue(wrappingFrequency);

    chartFourierTransform->showFourierTransform(combinedSignalPoints);
    addEntryToHistoryBuffer();
}

void MainWindow::on_clearButton_clicked()
{
    chartCombinedSignals->clearData();
    chartWrappedSignal->clearData();
    chartFourierTransform->clearData();
    ui->signalsList->clear();
}

void MainWindow::on_frequencySlider_valueChanged(int value)
{
    chartGeneratedSignal->setFrequency(value);
    chartGeneratedSignal->generateSignal();
    ui->frequencyInfo->setText(QString::number(value));
}

void MainWindow::on_frequencySlider_sliderMoved(int position)
{
    chartGeneratedSignal->setFrequency(position);
    chartGeneratedSignal->generateSignal();
    ui->frequencyInfo->setText(QString::number(position));
}

void MainWindow::on_amplitudeSlider_valueChanged(int value)
{
    chartGeneratedSignal->setAmplitude(value);
    chartGeneratedSignal->generateSignal();
    ui->amplitudeInfo->setText(QString::number(value));
}

void MainWindow::on_amplitudeSlider_sliderMoved(int position)
{
    chartGeneratedSignal->setAmplitude(position);
    chartGeneratedSignal->generateSignal();
    ui->amplitudeInfo->setText(QString::number(position));
}

void MainWindow::on_wrappingFrequencySlider_valueChanged(int value)
{
    QVector<QPointF> combinedSignalPoints = chartCombinedSignals->getSignalDataPoints();
    double wrappingFrequency = (double)ui->wrappingFrequencySlider->value() / 100;
    chartWrappedSignal->setWrappingFrequency(wrappingFrequency);
    chartWrappedSignal->generateWrappedSignal(combinedSignalPoints);
    ui->wrappingFrequencyInfo->setValue(wrappingFrequency);
}

void MainWindow::on_wrappingFrequencyInfo_valueChanged(double arg1)
{
    QVector<QPointF> combinedSignalPoints = chartCombinedSignals->getSignalDataPoints();
    double wrappingFrequency = arg1;
    chartWrappedSignal->setWrappingFrequency(wrappingFrequency);
    chartWrappedSignal->generateWrappedSignal(combinedSignalPoints);
}

void MainWindow::addEntryToHistoryBuffer(){
    QString entry;
    int numOfElements = ui->signalsList->count();
    int frequency = ui->frequencySlider->value();
    int amplitude = ui->amplitudeSlider->value();

    entry += QString::number(numOfElements + 1);
    entry += ". ";
    entry += "Frequency: ";
    entry += QString("%1").arg(frequency, 2, 10, QChar(' '));
    entry += "Hz ";
    entry += "Amplitude: ";
    entry += QString::number(amplitude);

    ui->signalsList->addItem(entry);
}
