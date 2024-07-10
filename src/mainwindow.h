#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
  void on_applyButton_clicked();

  void on_checkBoxSystemSeetings_stateChanged(int arg1);

  void on_closeButton_clicked();

  void on_checkBoxSystemSeetings_toggled(bool checked);

  void on_horizontalSlider_valueChanged(int value);

private:
    void setBrightness(int value);
    Ui::MainWindow *ui;
    QPushButton *m_button;

    bool isApplyChecked;

    int currentSliderValue;
};

#endif // MAINWINDOW_H
