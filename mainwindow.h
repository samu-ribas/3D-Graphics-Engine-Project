#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

public slots:
    void processarDesenho(double x, double y); // ponto
    void processarDesenho(double x1, double y1, double x2, double y2); // reta
    void processarDesenho(double x, double y, int l, double r); // polígono
    void processarDesenho(QString nome, double x, double y, double c, double h); // retângulo

private slots:
    void inputCoordenadas();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
