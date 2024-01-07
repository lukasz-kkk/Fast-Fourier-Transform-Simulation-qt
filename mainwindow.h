#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCharts>
#include <QChartView>
#include <QLineSeries>
#include <QValueAxis>
#include <plotter.h>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_frequencySlider_sliderMoved(int position);

    void on_combineButton_clicked();

    void on_frequencySlider_valueChanged(int value);

    void on_clearButton_clicked();

    void on_amplitudeSlider_valueChanged(int value);

    void on_amplitudeSlider_sliderMoved(int position);

    void on_wrappingFrequencySlider_valueChanged(int value);

    void on_wrappingFrequencyInfo_valueChanged(double arg1);

    void addEntryToHistoryBuffer();

private:
    Ui::MainWindow *ui;

    Plotter *chartCombinedSignals;
    Plotter *chartGeneratedSignal;
    Plotter *chartWrappedSignal;
    Plotter *chartFourierTransform;
};
#endif // MAINWINDOW_H
