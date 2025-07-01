#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow; // Bloco padrão para a interface criada no Designer
}
QT_END_NAMESPACE

// Declaração da classe de janela principal
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr); // Construtor da janela
    ~MainWindow();

private:
    Ui::MainWindow *ui; // Ponteiro para acessar os componentes do arquivo .ui
};
#endif // MAINWINDOW_H
