#include "janelagerenciavw.h"
#include "ui_janelagerenciavw.h"

JanelaViewportWindow::JanelaViewportWindow(QWidget *parent, MeuFrame *frame)
    : QMainWindow(parent)
    , ui(new Ui::JanelaViewportWindow)
    , frame(frame)
{
    ui->setupUi(this);

    // In your widget's constructor
    //this->setWindowFlags(this->windowFlags() & ~Qt::WindowCloseButtonHint);
    this->setWindowFlags(Qt::Tool | Qt::WindowMinMaxButtonsHint);
    //setWindowFlags(Qt::Tool);
}

JanelaViewportWindow::~JanelaViewportWindow()
{
    delete ui;
}

void JanelaViewportWindow::on_pushButton_pressed()
{

}

void JanelaViewportWindow::closeEvent(QCloseEvent *event) {
    // Prevent the window from closing
    //event->ignore();

    // Optional: Show a message box
    // QMessageBox::warning(this, "Close", "Cannot close this window!");
}