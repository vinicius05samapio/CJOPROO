#include "drawwidget.h"

// Construtor: chamado uma vez para configurar o estado inicial da área de desenho
DrawWidget::DrawWidget(QWidget *parent) : QWidget(parent)
{
    // Cria a imagem que servirá como nosso "canvas" e pinta o fundo de branco
    imagem = QImage(800, 600, QImage::Format_RGB32);
    imagem.fill(Qt::white);

    // Define as ferramentas padrão ao iniciar
    corAtual = Qt::black;
    tamanhoLapis = 2;
    formaAtual = Forma::Livre;
    desenhando = false;
    modoBorracha = false;

    // Otimização para widgets cujo conteúdo é estático
    setAttribute(Qt::WA_StaticContents);
}

// Funções 'set' simples para alterar as propriedades a partir da janela principal
void DrawWidget::setCor(const QColor &cor) {
    corAtual = cor;
}

void DrawWidget::setTamanho(int tamanho) {
    tamanhoLapis = tamanho;
}

void DrawWidget::setBorracha(bool ativada) {
    modoBorracha = ativada;
}

void DrawWidget::setForma(Forma forma) {
    formaAtual = forma;
}

// Limpa o canvas e pede para a tela ser redesenhada
void DrawWidget::limpar() {
    imagem.fill(Qt::white);
    update();
}

// Evento disparado quando o mouse é pressionado
void DrawWidget::mousePressEvent(QMouseEvent *event) {
    desenhando = true;
    ultimoPonto = pontoInicial = event->pos(); // Salva a posição do clique
}

// Evento disparado quando o mouse é arrastado
void DrawWidget::mouseMoveEvent(QMouseEvent *event) {
    // Só desenha em tempo real se a ferramenta for o pincel livre
    if (desenhando && formaAtual == Forma::Livre) {
        QPainter painter(&imagem);
        painter.setPen(QPen(modoBorracha ? Qt::white : corAtual, tamanhoLapis, Qt::SolidLine, Qt::RoundCap));
        painter.drawLine(ultimoPonto, event->pos());
        ultimoPonto = event->pos();
        update(); // Atualiza a tela para mostrar o traço
    }
}

// Evento disparado quando o botão do mouse é solto
void DrawWidget::mouseReleaseEvent(QMouseEvent *event) {
    if (!desenhando) return;
    desenhando = false; // Finaliza o modo de desenho

    // Para as formas geométricas, o desenho acontece aqui, no final do arrasto
    QPainter painter(&imagem);
    painter.setPen(QPen(modoBorracha ? Qt::white : corAtual, tamanhoLapis));
    QRect rect(pontoInicial, event->pos());

    switch (formaAtual) {
    case Forma::Linha:      painter.drawLine(pontoInicial, event->pos()); break;
    case Forma::Retangulo:  painter.drawRect(rect); break;
    case Forma::Circulo:    painter.drawEllipse(rect); break;
    default: break; // Não faz nada para o modo "Livre"
    }
    update();
}

// Evento final que efetivamente desenha nosso 'canvas' (a QImage) na tela do widget
void DrawWidget::paintEvent(QPaintEvent *) {
    QPainter painter(this);
    painter.drawImage(0, 0, imagem);
}
