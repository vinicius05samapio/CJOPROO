// Brick Breaker.cpp : Este arquivo contém a função 'main'. A execução do programa começa e termina ali.
//

#include "raylib.h"
#include <vector>
#include <string>

using namespace std;

// Define a dimensão da tela
const int larguraTela = 1000;
const int alturaTela = 600;

// Configurações da plataforma
Rectangle plataforma = { larguraTela / 2 - 50, alturaTela - 20, 100, 10 };
float velocidadePlataforma = 500.f;

// Configurações da bola
Vector2 posicaoBola = { larguraTela / 2, alturaTela / 2 };
Vector2 velocidadeBola = { 200.0f, -200.0f }; // pode-se adaptar
float raioBola = 8.0f;

// Configurações dos blocos
const int linhas = 7;
const int colunas = 15;
const int larguraBloco = 60;
const int alturaBloco = 20;
vector<Rectangle> blocos;

// Estado do jogo
int pontuacao = 0;
bool jogoEncerrado = false;
bool jogoVencido = false;

void InicializarBlocos() {
    blocos.clear(); // Limpa qualquer bloco existente
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            // Cria um objeto retangular e define suas propriedades
            Rectangle bloco = { j * (larguraBloco + 5) + 40, i * (alturaBloco + 5) + 40, larguraBloco, alturaBloco };
            // Adiciona o bloco ao vetor de blocos
            blocos.push_back(bloco);
        }
    }
}

//função pra atualizar a bola
void AtualizarBola(float deltaTempo) {
    if (!jogoEncerrado && !jogoVencido) {
        // Move a bola
        posicaoBola.x += velocidadeBola.x * deltaTempo;
        posicaoBola.y += velocidadeBola.y * deltaTempo;

        // Procura por colisões com as paredes
        if (posicaoBola.x <= raioBola || posicaoBola.x >= larguraTela - raioBola) {
            velocidadeBola.x *= -1;
        }
        if (posicaoBola.y <= raioBola) {
            velocidadeBola.y *= -1;
        }

        // Procura por colisões com a plataforma
        if (CheckCollisionCircleRec(posicaoBola, raioBola, plataforma)) {
            velocidadeBola.y *= -1;
        }

        // Procura por colisões com os blocos
        for (auto it = blocos.begin(); it != blocos.end();) {
            if (CheckCollisionCircleRec(posicaoBola, raioBola, *it)) {
                velocidadeBola.y *= -1;
                it = blocos.erase(it); // Remove o bloco
                pontuacao += 10; // Aumenta a pontuação
            }
            else {
                ++it;
            }
        }

        // Verifica se todos os blocos foram destruídos
        if (blocos.empty()) {
            jogoVencido = true;
        }

        // Verifica se o jogador perdeu
        if (posicaoBola.y >= alturaTela) {
            jogoEncerrado = true;
            velocidadeBola = { 0, 0 }; // Para a bola
        }
    }
}

//função para a renderização das telas finais
void RenderizarTelaFinal() {
    if (jogoVencido) {
        DrawText("Você Venceu!", larguraTela / 2 - 80, alturaTela / 2 - 20, 40, GREEN);
        DrawText(("Pontos: " + to_string(pontuacao)).c_str(), larguraTela / 2 - 60, alturaTela / 2 + 30, 20, WHITE);
    }
    else if (jogoEncerrado) {
        DrawText("FIM DE JOGO", larguraTela / 2 - 100, alturaTela / 2 - 20, 40, RED);
        DrawText(("Pontuação Final: " + to_string(pontuacao)).c_str(), larguraTela / 2 - 80, alturaTela / 2 + 30, 20, WHITE);
    }
}


//função pra renderização dos blocos
void RenderizarBlocos() {
    for (const auto& bloco : blocos) {
        DrawRectangleRec(bloco, RED);
    }
}

// Função principal
int main() {

    InitWindow(larguraTela, alturaTela, "Brick Breaker");

    SetTargetFPS(60);

    InicializarBlocos();

    while (!WindowShouldClose()) {
        float deltaTempo = GetFrameTime();

        // Movimento da plataforma
        if (IsKeyDown(KEY_LEFT) && plataforma.x > 0) plataforma.x -= velocidadePlataforma * deltaTempo;
        if (IsKeyDown(KEY_RIGHT) && plataforma.x < larguraTela - plataforma.width) plataforma.x += velocidadePlataforma * deltaTempo;

        // Atualizar a bola
        AtualizarBola(deltaTempo);

        // Renderizando
        BeginDrawing();
        ClearBackground(BLACK);

        if (jogoEncerrado || jogoVencido) {
            RenderizarTelaFinal();
        }
        else {
            DrawRectangleRec(plataforma, BLUE);
            DrawCircleV(posicaoBola, raioBola, WHITE);
            RenderizarBlocos();
            DrawText(("Pontuação: " + to_string(pontuacao)).c_str(), 20, 20, 20, WHITE);
        }

        EndDrawing();
    }

    // Fim do programa
    CloseWindow();
    return 0;
}

// Executar programa: Ctrl + F5 ou Menu Depurar > Iniciar Sem Depuração
// Depurar programa: F5 ou menu Depurar > Iniciar Depuração

// Dicas para Começar: 
//   1. Use a janela do Gerenciador de Soluções para adicionar/gerenciar arquivos
//   2. Use a janela do Team Explorer para conectar-se ao controle do código-fonte
//   3. Use a janela de Saída para ver mensagens de saída do build e outras mensagens
//   4. Use a janela Lista de Erros para exibir erros
//   5. Ir Para o Projeto > Adicionar Novo Item para criar novos arquivos de código, ou Projeto > Adicionar Item Existente para adicionar arquivos de código existentes ao projeto
//   6. No futuro, para abrir este projeto novamente, vá para Arquivo > Abrir > Projeto e selecione o arquivo. sln
