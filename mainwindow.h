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

private slots:
    void processarPoligono(double x, double y, int l, double r); // polígono
    void processarPoligono(double x, double y, double c, double h); // retângulo

    void inputObjeto();
    void inputOperacao();
    void on_btn_winConfig_pressed();
    void setDeslocamento();

    void on_btn_cima_clicked();
    void on_btn_baixo_clicked();
    void on_btn_esquerda_clicked();
    void on_btn_direita_clicked();
    void on_btn_zoomMais_clicked();
    void on_btn_zoomMenos_clicked();
    void on_btn_girarEsq_clicked();
    void on_btn_girarDir_clicked();
    void on_btn_diagEsqCima_clicked();
    void on_btn_diagEsqBaixo_clicked();
    void on_btn_diagDirCima_clicked();
    void on_btn_diagDirBaixo_clicked();
    void on_btn_reset_clicked();
    void on_btn_zoomViewportMais_clicked();
    void on_btn_zoomViewportMenos_clicked();

    void on_btn_carregarModelo_clicked();

private:
    Ui::MainWindow *ui;
    double deslocamentoWindow;
};
#endif // MAINWINDOW_H
