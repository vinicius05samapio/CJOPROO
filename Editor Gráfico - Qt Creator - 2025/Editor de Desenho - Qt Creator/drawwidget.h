#ifndef DRAWWIDGET_H
#define DRAWWIDGET_H

// componentes do Qt para a interface, desenho e eventos do mouse
#include <QWidget>
#include <QPainter>
#include <QMouseEvent>

// define os tipos de ferramentas que nosso Paint suporta
enum class Forma { Livre, Linha, Retangulo, Circulo };

class DrawWidget : public QWidget
{
    Q_OBJECT

public: // Funções de controle, para serem chamadas pela janela principal
    explicit DrawWidget(QWidget *parent = nullptr);
    void setCor(const QColor &cor);
    void setTamanho(int tamanho);
    void setBorracha(bool ativada);
    void setForma(Forma forma);
    void limpar();

protected: // Eventos do Qt que precisamos redefinir para criar nosso comportamento
    void paintEvent(QPaintEvent *) override;
    void mousePressEvent(QMouseEvent *) override;
    void mouseMoveEvent(QMouseEvent *) override;
    void mouseReleaseEvent(QMouseEvent *) override;

private: // Variáveis internas que guardam o estado atual do desenho
    QImage imagem;
    QPoint ultimoPonto, pontoInicial;
    QColor corAtual;
    int tamanhoLapis;
    bool desenhando, modoBorracha;
    Forma formaAtual;
};

#endif // DRAWWIDGET_H
