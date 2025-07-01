#include "mainwindow.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>

int main(int argc, char *argv[])
{
    // Cria o objeto principal que gerencia toda a aplicação
    QApplication a(argc, argv);

    // Bloco padrão para tentar carregar um arquivo de tradução para o idioma do sistema
    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "PaintBasico_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }

    // Cria a janela principal e a exibe na tela
    MainWindow w;
    w.show();

    // Inicia o loop de eventos da aplicação e aguarda a interação do usuário
    return a.exec();
}
