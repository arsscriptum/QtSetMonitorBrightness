#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtCore>
#include <QtGui>
#include <QMessageBox>

#include <QApplication>
#include <QWidget>
#include <QSlider>
#include <QVBoxLayout>
#include <QLabel>
#include <Windows.h>
#include <highlevelmonitorconfigurationapi.h>

#pragma comment(lib, "Dxva2.lib")

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    isApplyChecked = false;
    currentSliderValue = 0;

    connect(ui->horizontalSlider, SIGNAL(valueChanged(int)), ui->progressBar, SLOT(setValue(int)));
    connect(ui->horizontalSlider, SIGNAL(valueChanged(int)), ui->progressBar_2, SLOT(setValue(int)));
    disconnect(ui->horizontalSlider, SIGNAL(valueChanged(int)), ui->progressBar, SLOT(setValue(int)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_applyButton_clicked()
{
    if(isApplyChecked){
        QMessageBox::information(this, "DOING WORK OFFICIAL MODE", "PROCESS (Checked)");
        setBrightness(currentSliderValue);
    }else{
        QMessageBox::information(this, "TEST MODE", "test (unchecked)");
    }

}

void MainWindow::on_checkBoxSystemSeetings_stateChanged(int checked)
{
    if(checked){
        isApplyChecked = true;
    }else{
        isApplyChecked = false;
    }
}

void MainWindow::on_closeButton_clicked()
{
    QCoreApplication::quit();
}

void MainWindow::on_checkBoxSystemSeetings_toggled(bool checked)
{
    if(checked){
        isApplyChecked = true;
    }else{
        isApplyChecked = false;
    }
}

void MainWindow::setBrightness(int value)
{
     HMONITOR hMonitor = MonitorFromWindow(GetDesktopWindow(), MONITOR_DEFAULTTOPRIMARY);
     if (hMonitor) {
         DWORD dwMonitorCount = 0;
         LPPHYSICAL_MONITOR pPhysicalMonitors = NULL;
         if (GetNumberOfPhysicalMonitorsFromHMONITOR(hMonitor, &dwMonitorCount)) {
             pPhysicalMonitors = (LPPHYSICAL_MONITOR)malloc(dwMonitorCount * sizeof(PHYSICAL_MONITOR));
             if (pPhysicalMonitors) {
                 if (GetPhysicalMonitorsFromHMONITOR(hMonitor, dwMonitorCount, pPhysicalMonitors)) {
                     for (DWORD i = 0; i < dwMonitorCount; i++) {
                         SetMonitorBrightness(pPhysicalMonitors[i].hPhysicalMonitor, value);
                     }
                     DestroyPhysicalMonitors(dwMonitorCount, pPhysicalMonitors);
                 }
                 free(pPhysicalMonitors);
             }
         }
     }
 }

void MainWindow::on_horizontalSlider_valueChanged(int value)
{
    currentSliderValue = value;
}
