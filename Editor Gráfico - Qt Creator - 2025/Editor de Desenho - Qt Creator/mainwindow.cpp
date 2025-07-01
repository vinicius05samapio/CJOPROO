#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "drawwidget.h"

#include <QColorDialog>
#include <QInputDialog>

// Construtor da janela principal
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    // Carrega os componentes visuais do arquivo .ui e prepara a janela
    ui->setupUi(this);

    // Conecta os sinais da interface (cliques de botão, etc.) às suas respectivas ações
    connect(ui->btnLimpar, &QPushButton::clicked, ui->drawArea, &DrawWidget::limpar);

    connect(ui->btnCor, &QPushButton::clicked, this, [&]() {
        QColor cor = QColorDialog::getColor(Qt::black, this, "Escolher Cor");
        if (cor.isValid()) ui->drawArea->setCor(cor);
    });

    connect(ui->btnTamanho, &QPushButton::clicked, this, [&]() {
        int tamanho = QInputDialog::getInt(this, "Tamanho do Lápis", "Pixels:", 2, 1, 50);
        ui->drawArea->setTamanho(tamanho);
    });

    connect(ui->btnBorracha, &QPushButton::clicked, this, [&]() {
        ui->drawArea->setForma(Forma::Livre);
        ui->drawArea->setBorracha(true);
    });

    connect(ui->comboForma, &QComboBox::currentTextChanged, this, [&](const QString &texto){
        ui->drawArea->setBorracha(false);

        if (texto == "Livre") ui->drawArea->setForma(Forma::Livre);
        else if (texto == "Linha") ui->drawArea->setForma(Forma::Linha);
        else if (texto == "Retângulo") ui->drawArea->setForma(Forma::Retangulo);
        else if (texto == "Círculo") ui->drawArea->setForma(Forma::Circulo);
    });
}

// Destrutor é chamado quando a janela é fechada
MainWindow::~MainWindow()
{
    delete ui; // Libera a memória usada pela interface
}
