﻿#include "raylib.h"
#include <vector>
#include <cmath>
#include <cstdlib> 
#include <algorithm> 
#include <limits>    

using namespace std;

// Configuracoes globais do jogo
const int larguraTela = 800;
const int alturaTela = 600;
const int tamanhoTile = 40;
const int larguraMapa = 20;
const int alturaMapa = 15;
const float limiteTempoFase2 = 30.0f;
const float limiteTempoFase3 = 20.0f;

// Variaveis de estado do jogo
int faseAtual = 0;
float timerFase = 0.0f;
bool jogoIniciado = false;
bool fimDeJogo = false;
bool jogoVencido = false;

// Array com os mapas de todas as fases
// 0=caminho, 1=parede, 2=moeda, 3=armadilha, 4=portao fechado, 5=portao aberto
int mapas[3][alturaMapa][larguraMapa] = {
    { // Fase 1
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
        {1,0,0,0,3,1,0,3,0,1,1,1,1,1,1,1,1,1,1,1},
        {1,0,1,0,0,1,0,1,0,1,1,1,1,1,1,1,1,1,1,1},
        {1,0,1,1,0,1,0,1,2,1,1,1,1,1,1,1,1,1,1,1},
        {1,0,0,0,0,0,0,1,0,1,1,1,1,1,1,1,1,1,1,1},
        {1,1,1,0,1,1,0,1,0,1,1,1,1,1,1,1,1,1,1,1},
        {1,2,3,0,1,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1},
        {1,0,1,0,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
        {1,0,0,0,0,0,0,0,4,1,1,1,1,1,1,1,1,1,1,1},
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
        },
        { // Fase 2
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
        {1,0,0,0,0,1,0,0,0,3,0,0,0,1,0,0,0,0,4,1},
        {1,0,1,1,0,1,0,1,1,1,1,1,2,1,0,1,1,1,1,1},
        {1,0,0,0,2,0,0,0,0,0,0,0,0,1,0,0,2,0,0,1},
        {1,0,1,0,1,0,1,1,2,1,0,1,0,1,0,1,0,1,0,1},
        {1,2,0,0,1,0,0,1,0,1,0,1,0,0,0,0,0,1,0,1},
        {1,1,1,0,1,0,1,1,0,1,0,1,1,1,1,1,2,1,0,1},
        {1,0,0,0,0,2,3,0,0,1,2,0,0,0,0,0,0,1,0,1},
        {1,0,1,1,1,0,1,1,0,1,0,1,1,1,0,1,0,1,0,1},
        {1,0,0,0,1,2,0,1,0,0,0,0,0,1,2,0,0,0,0,1},
        {1,1,1,0,1,1,0,1,1,1,1,1,0,1,1,1,1,1,0,1},
        {1,0,0,0,0,1,0,0,0,0,0,1,2,0,0,0,0,1,0,1},
        {1,0,1,0,0,1,1,1,0,1,0,1,1,1,1,1,0,1,2,1},
        {1,0,2,1,0,0,0,0,0,1,2,0,0,0,0,1,0,3,0,1},
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
        },
        { // Fase 3
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
        {1,0,0,0,1,2,0,0,0,0,0,0,0,1,0,0,0,0,4,1},
        {1,0,1,0,1,0,1,1,0,1,0,1,0,1,0,1,0,1,0,1},
        {1,0,1,2,0,0,0,1,3,0,0,1,2,0,0,0,0,1,0,1},
        {1,0,1,1,1,1,0,1,1,1,0,1,1,1,1,1,0,1,0,1},
        {1,0,0,0,0,1,0,0,0,1,0,0,0,0,0,1,2,0,3,1},
        {1,1,1,0,0,1,0,1,1,1,0,1,0,1,0,1,1,1,1,1},
        {1,0,0,0,0,0,0,0,2,0,0,0,0,1,0,0,0,0,0,1},
        {1,0,1,3,1,1,0,1,0,1,1,1,0,1,0,1,3,1,0,1},
        {1,0,1,0,0,2,0,0,0,0,0,0,0,0,0,0,0,1,0,1},
        {1,0,1,0,1,1,1,1,0,1,0,1,1,1,1,1,0,1,0,1},
        {1,0,0,0,1,0,0,0,0,1,0,0,0,3,2,0,0,1,0,1},
        {1,1,1,0,1,0,1,1,0,1,0,1,0,1,0,1,0,1,0,1},
        {1,2,0,0,0,0,1,1,0,0,2,1,0,1,0,0,0,0,2,1},
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
        }
};
// Mapa que sera usado no jogo
int mapa[alturaMapa][larguraMapa];

// Recursos do jogo
Texture2D texturaMoeda;
Sound somMoeda;
Music musicaFundo;
Sound somDerrota;
Sound somVitoria;

// CLASSE do jogador
class Jogador
{
public:
    Vector2 posicao;
    Vector2 direcao;
    bool movendo;

    // Construtores
    Jogador() {
        posicao = { 0.0f, 0.0f };
        direcao = { 0.0f, 0.0f };
        movendo = false;
    }
    Jogador(Vector2 posInicial) : posicao(posInicial), direcao({ 0.0f,0.0f }), movendo(false) {}

    // Define uma nova direçao e comeca a mover
    void IniciarMovimento(Vector2 novaDirecao) {
        if (!movendo) { direcao = novaDirecao; movendo = true; }
    }

    // Atualiza o jogador a cada frame
    bool Atualizar(float dt)
    {
        if (!movendo) return false;

        Vector2 proximaPos = posicao;
        proximaPos.x += direcao.x * tamanhoTile; proximaPos.y += direcao.y * tamanhoTile;

        int tx = (int)(proximaPos.x / tamanhoTile);
        int ty = (int)(proximaPos.y / tamanhoTile);

        // verifica se o proximo tile eh um obstaculo
        if (tx >= 0 && tx < larguraMapa && ty >= 0 && ty < alturaMapa && mapa[ty][tx] != 1 && mapa[ty][tx] != 4) {
            posicao = proximaPos;
        }
        else {
            movendo = false;
        }

        int tileAtualX = (int)(posicao.x / tamanhoTile); int tileAtualY = (int)(posicao.y / tamanhoTile);
        if (tileAtualX < 0 || tileAtualX >= larguraMapa || tileAtualY < 0 || tileAtualY >= alturaMapa) { movendo = false; return false; }

        // Colisao com moeda
        if (mapa[tileAtualY][tileAtualX] == 2) {
            mapa[tileAtualY][tileAtualX] = 0; // some com a moeda do mapa
            if (somMoeda.frameCount > 0) PlaySound(somMoeda);

            int moedasRestantes = 0;
            for (int y = 0; y < alturaMapa; y++) {
                for (int x = 0; x < larguraMapa; x++) if (mapa[y][x] == 2) moedasRestantes++;
            }
            // se nao tem mais moeda, abre o portao
            if (moedasRestantes == 0) for (int y_p = 0; y_p < alturaMapa; y_p++) for (int x_p = 0; x_p < larguraMapa; x_p++) if (mapa[y_p][x_p] == 4) mapa[y_p][x_p] = 5;
        }
        // Colisão com armadilha
        if (mapa[tileAtualY][tileAtualX] == 3) {
            if (!fimDeJogo) {
                if (musicaFundo.frameCount > 0 && IsMusicStreamPlaying(musicaFundo)) StopMusicStream(musicaFundo);
                if (somDerrota.frameCount > 0) PlaySound(somDerrota);
            }
            fimDeJogo = true;
        }
        // Colisão com o portão de saida
        if (mapa[tileAtualY][tileAtualX] == 5) {
            faseAtual++;
            if (faseAtual < 3) return true; // indica que mudou de fase
            else {
                if (!jogoVencido) { // toca o som de vitoria so uma vez
                    if (musicaFundo.frameCount > 0 && IsMusicStreamPlaying(musicaFundo)) StopMusicStream(musicaFundo);
                    if (somVitoria.frameCount > 0) PlaySound(somVitoria);
                }
                jogoVencido = true;
            }
        }
        return false;
    }

    void Desenhar() const { DrawRectangleV({ posicao.x + 5.0f,posicao.y + 5.0f }, { (float)tamanhoTile - 10.0f, (float)tamanhoTile - 10.0f }, GREEN); }
    Rectangle ObterRetangulo() const {
        return { posicao.x, posicao.y, (float)tamanhoTile, (float)tamanhoTile };
    }
};

// CLASSE do projetil
class Projetil
{
public:
    Vector2 posicao;
    Vector2 direcao;
    bool ativo;
    Jogador* jogadorAlvo;

    Projetil(Vector2 pos, Vector2 dir, Jogador* alvo) : posicao(pos), direcao(dir), ativo(true), jogadorAlvo(alvo) {}

    void Atualizar(float dt) {
        if (!ativo) return;
        posicao.x += direcao.x * 200 * dt;
        posicao.y += direcao.y * 200 * dt;
        int bx = (int)(posicao.x / tamanhoTile);
        int by = (int)(posicao.y / tamanhoTile);
        if (bx < 0 || bx >= larguraMapa || by < 0 || by >= alturaMapa || mapa[by][bx] == 1) { ativo = false; return; }

        Rectangle recProjetil = { posicao.x, posicao.y, 10.0f, 10.0f };
        if (jogadorAlvo && CheckCollisionRecs(recProjetil, jogadorAlvo->ObterRetangulo())) {
            if (!fimDeJogo) {
                if (musicaFundo.frameCount > 0 && IsMusicStreamPlaying(musicaFundo)) StopMusicStream(musicaFundo);
                if (somDerrota.frameCount > 0) PlaySound(somDerrota);
            }
            fimDeJogo = true;
            ativo = false;
        }
    }
    void Desenhar() const { if (ativo) DrawRectangleV(posicao, { 10.0f, 10.0f }, ORANGE); }
};

// CLASSE atirador
class Inimigo
{
public:
    Vector2 posicao;
    float recargaTiro; Vector2 direcaoTiro;
    Inimigo(Vector2 pos, Vector2 dirTiro, float recargaIni) : posicao(pos), direcaoTiro(dirTiro), recargaTiro(recargaIni) {}

    void Atualizar(float dt, Jogador& jogadorReferencia, vector<Projetil>& listaProjeteis) {
        recargaTiro -= dt;
        if (recargaTiro <= 0) {
            Atirar(jogadorReferencia, listaProjeteis);
            recargaTiro = 2.1f + ((float)GetRandomValue(0, 5) / 10.0f); // recarga meio aleatoria
        }
    }

    void Atirar(Jogador& jogadorReferencia, vector<Projetil>& listaProjeteis) {
        float largProjetil = 10.0f, altProjetil = 10.0f;
        float centroXInimigo = posicao.x + tamanhoTile / 2.0f;
        float centroYInimigo = posicao.y + tamanhoTile / 2.0f;
        Vector2 posProjetil = { 0.0f,0.0f };

        if (direcaoTiro.x == -1.0f) { posProjetil.x = posicao.x - largProjetil; posProjetil.y = centroYInimigo - altProjetil / 2.0f; }
        else if (direcaoTiro.x == 1.0f) { posProjetil.x = posicao.x + tamanhoTile; posProjetil.y = centroYInimigo - altProjetil / 2.0f; }
        else if (direcaoTiro.y == -1.0f) { posProjetil.x = centroXInimigo - largProjetil / 2.0f; posProjetil.y = posicao.y - altProjetil; }
        else if (direcaoTiro.y == 1.0f) { posProjetil.x = centroXInimigo - largProjetil / 2.0f; posProjetil.y = posicao.y + tamanhoTile; }
        else { posProjetil.x = centroXInimigo - largProjetil / 2.0f; posProjetil.y = centroYInimigo - altProjetil / 2.0f; }

        listaProjeteis.push_back(Projetil(posProjetil, direcaoTiro, &jogadorReferencia)); // cria um projetil novo
    }
    void Desenhar() const { DrawRectangleV({ posicao.x + 5.0f, posicao.y + 5.0f }, { (float)tamanhoTile - 10.0f, (float)tamanhoTile - 10.0f }, PURPLE); }
};

// CLASSE do perseguidor
class Perseguidor
{
public:
    Vector2 posicao, direcaoMovimentoAtual;
    float timerMovimento, recargaMovimento;

    Perseguidor() : posicao({ 0.0f,0.0f }), direcaoMovimentoAtual({ 0.0f,0.0f }), timerMovimento(0.25f), recargaMovimento(0.25f) {}
    Perseguidor(Vector2 posInicial) : posicao(posInicial), direcaoMovimentoAtual({ 0.0f,0.0f }), timerMovimento(0.25f), recargaMovimento(0.25f) {}

    // ve se pode andar tranquilamente
    static bool EhObstaculo(int x, int y) {
        if (x < 0 || x >= larguraMapa || y < 0 || y >= alturaMapa) return true;
        return (mapa[y][x] == 1 || mapa[y][x] == 3);
    }

    void DecidirMovimento(const Jogador& alvo) {
        int cx = (int)(posicao.x / tamanhoTile), cy = (int)(posicao.y / tamanhoTile);
        int px = (int)(alvo.posicao.x / tamanhoTile), py = (int)(alvo.posicao.y / tamanhoTile);

        Vector2 dirs[] = { {0.0f,-1.0f},{-1.0f,0.0f},{0.0f,1.0f},{1.0f,0.0f} };
        Vector2 melhorDir = { 0.0f,0.0f };
        float menorDist = 99999.0f;
        vector<Vector2> movsPossiveis;

        for (const auto& dirOpcao : dirs) {
            int proxCx = cx + (int)dirOpcao.x, proxCy = cy + (int)dirOpcao.y;
            if (EhObstaculo(proxCx, proxCy)) { continue; }

            bool ehOposto = (dirOpcao.x == -direcaoMovimentoAtual.x && dirOpcao.y == -direcaoMovimentoAtual.y);
            if (direcaoMovimentoAtual.x == 0 && direcaoMovimentoAtual.y == 0) ehOposto = false;

            // nao deixa ele voltar por onde veio, a menos que seja um beco sem saida
            if (!ehOposto) { movsPossiveis.push_back(dirOpcao); }
            else {
                int outrasOpcoesValidas = 0;
                for (const auto& outraDirOpcao : dirs) {
                    if (outraDirOpcao.x == dirOpcao.x && outraDirOpcao.y == dirOpcao.y)continue;
                    if (!EhObstaculo(cx + (int)outraDirOpcao.x, cy + (int)outraDirOpcao.y)) outrasOpcoesValidas++;
                }
                if (outrasOpcoesValidas == 0) movsPossiveis.push_back(dirOpcao);
            }
        }
        // se travou de algum jeito, tenta de novo sem a restrição
        if (movsPossiveis.empty() && (direcaoMovimentoAtual.x != 0 || direcaoMovimentoAtual.y != 0)) {
            for (const auto& dirOpcao : dirs) {
                int proxCx = cx + (int)dirOpcao.x, proxCy = cy + (int)dirOpcao.y;
                if (!EhObstaculo(proxCx, proxCy)) movsPossiveis.push_back(dirOpcao);
            }
        }
        // escolhe a melhor direção (a que mais se aproxima do jogador)
        if (!movsPossiveis.empty()) {
            melhorDir = movsPossiveis[0];
            for (const auto& dirMov : movsPossiveis) {
                int potCx = cx + (int)dirMov.x, potCy = cy + (int)dirMov.y;
                float distJogador = (float)abs(potCx - px) + abs(potCy - py);
                if (distJogador < menorDist) { menorDist = distJogador; melhorDir = dirMov; }
            }
        }
        direcaoMovimentoAtual = melhorDir;
    }

    void Atualizar(float dt, const Jogador& alvo) {
        timerMovimento -= dt;
        if (timerMovimento <= 0.0f) {
            DecidirMovimento(alvo);

            if (direcaoMovimentoAtual.x != 0.0f || direcaoMovimentoAtual.y != 0.0f) {
                int cx = (int)(posicao.x / tamanhoTile), cy = (int)(posicao.y / tamanhoTile);
                int proxFinalCx = cx + (int)direcaoMovimentoAtual.x, proxFinalCy = cy + (int)direcaoMovimentoAtual.y;

                if (!EhObstaculo(proxFinalCx, proxFinalCy)) {
                    posicao.x = (float)proxFinalCx * tamanhoTile; posicao.y = (float)proxFinalCy * tamanhoTile;
                }
                else direcaoMovimentoAtual = { 0.0f,0.0f };
            }
            timerMovimento = recargaMovimento;
        }
        // colisao com jogador
        if (CheckCollisionRecs(ObterRetangulo(), alvo.ObterRetangulo())) {
            if (!fimDeJogo) {
                if (musicaFundo.frameCount > 0 && IsMusicStreamPlaying(musicaFundo)) StopMusicStream(musicaFundo);
                if (somDerrota.frameCount > 0) PlaySound(somDerrota);
            }
            fimDeJogo = true;
        }
    }
    void Desenhar() const { DrawRectangleV({ posicao.x + 5.0f,posicao.y + 5.0f }, { (float)tamanhoTile - 10.0f, (float)tamanhoTile - 10.0f }, MAROON); }
    Rectangle ObterRetangulo() const { return { posicao.x,posicao.y,(float)tamanhoTile,(float)tamanhoTile }; }
};

// objetos globais
Jogador jogadorGlobal;
Perseguidor perseguidorGlobal;
vector<Inimigo> inimigosAtiradores;
vector<Projetil> projeteis;

// funções do jogo
void ConfigurarInimigosAtiradores() {
    inimigosAtiradores.clear(); float recargaBase = 2.0f;
    if (faseAtual == 0) {
        inimigosAtiradores.push_back(Inimigo(Vector2{ (float)tamanhoTile * 7.0f, (float)tamanhoTile * 5.0f }, Vector2{ -1.0f,0.0f }, recargaBase));
    }
    else if (faseAtual == 1) {
        inimigosAtiradores.push_back(Inimigo(Vector2{ (float)tamanhoTile * 15.0f,(float)tamanhoTile * 13.0f }, Vector2{ -1.0f,0.0f }, recargaBase));
        inimigosAtiradores.push_back(Inimigo(Vector2{ (float)tamanhoTile * 12.0f,(float)tamanhoTile * 6.0f }, Vector2{ 0.0f,-1.0f }, recargaBase + 0.2f));
        inimigosAtiradores.push_back(Inimigo(Vector2{ (float)tamanhoTile * 7.0f,(float)tamanhoTile * 9.0f }, Vector2{ -1.0f,0.0f }, recargaBase + 0.4f));
    }
    else if (faseAtual == 2) {
        inimigosAtiradores.push_back(Inimigo(Vector2{ (float)tamanhoTile * 7.0f,(float)tamanhoTile * 0.0f }, Vector2{ 0.0f,1.0f }, recargaBase + 0.4f));
        inimigosAtiradores.push_back(Inimigo(Vector2{ (float)tamanhoTile * 2.0f,(float)tamanhoTile * 10.0f }, Vector2{ -1.0f,0.0f }, recargaBase + 0.2f));
        inimigosAtiradores.push_back(Inimigo(Vector2{ (float)tamanhoTile * 17.0f,(float)tamanhoTile * 12.0f }, Vector2{ 1.0f,0.0f }, recargaBase));
    }
}

void CarregarMapa() {
    int h = alturaMapa, w = larguraMapa;
    if (faseAtual == 0) { h = 10; w = 10; }
    for (int y = 0; y < alturaMapa; y++) {
        for (int x = 0; x < larguraMapa; x++) {
            if (faseAtual == 0 && (y >= h || x >= w)) { mapa[y][x] = 1; }
            else { mapa[y][x] = mapas[faseAtual][y][x]; }
        }
    }
    ConfigurarInimigosAtiradores(); projeteis.clear();
}


// função principal
int main()
{
    InitWindow(larguraTela, alturaTela, "Deslize Apex - O jogo");
    InitAudioDevice();
    SetTargetFPS(60);

    // Carrega os assets do jogo
    texturaMoeda = LoadTexture("assets/moedaImagem.png");
    somMoeda = LoadSound("assets/somMoeda.wav");
    musicaFundo = LoadMusicStream("assets/musicaFundo.mp3");
    somDerrota = LoadSound("assets/somDerrota.wav");
    somVitoria = LoadSound("assets/somVitoria.wav");

    if (musicaFundo.frameCount > 0) { PlayMusicStream(musicaFundo); SetMusicVolume(musicaFundo, 0.4f); musicaFundo.looping = true; }

    static float temporizadorPiscaBorda = 0.0f;
    static bool mostrarBordaPiscante = true;

    jogadorGlobal = Jogador();
    perseguidorGlobal = Perseguidor();

    // Loop PRINCIPAL do jogo
    while (!WindowShouldClose()) {
        float dt = GetFrameTime();
        if (musicaFundo.frameCount > 0) { UpdateMusicStream(musicaFundo); }

        if (!jogoIniciado) {
            // Logica da tela de inicio
            if (IsKeyPressed(KEY_R)) {
                jogoIniciado = true; faseAtual = 0; fimDeJogo = false; jogoVencido = false;
                jogadorGlobal = Jogador(Vector2{ (float)tamanhoTile * 1.0f,(float)tamanhoTile * 1.0f });
                perseguidorGlobal = Perseguidor(Vector2{ (float)tamanhoTile * 8.0f,(float)tamanhoTile * 1.0f });
                CarregarMapa();
                if (faseAtual == 1)timerFase = limiteTempoFase2;
                else if (faseAtual == 2)timerFase = limiteTempoFase3;
                else timerFase = 0.0f;
                if (musicaFundo.frameCount > 0) { if (IsMusicStreamPlaying(musicaFundo))StopMusicStream(musicaFundo); PlayMusicStream(musicaFundo); }
            }

            // Atualiza o pisca-pisca
            temporizadorPiscaBorda += dt;
            if (temporizadorPiscaBorda >= 0.4f) { mostrarBordaPiscante = !mostrarBordaPiscante; temporizadorPiscaBorda = 0.0f; }
            BeginDrawing();
            ClearBackground(DARKGRAY);
            // Desenha o titulo do jogo
            const char* nomeJogo = "Deslize Apex"; int tamFonteNomeJogo = 60; Color corNomeJogo = GREEN;
            int larguraNomeJogo = MeasureText(nomeJogo, tamFonteNomeJogo);
            Vector2 posNomeJogo = { larguraTela / 2.0f - larguraNomeJogo / 2.0f,alturaTela * 0.25f };
            DrawText(nomeJogo, (int)posNomeJogo.x, (int)posNomeJogo.y, tamFonteNomeJogo, corNomeJogo);
            if (mostrarBordaPiscante) {
                Rectangle rectBordaTitulo = { posNomeJogo.x - 10.0f,posNomeJogo.y - 10.0f,(float)larguraNomeJogo + 20.0f,(float)tamFonteNomeJogo + 10.0f };
                DrawRectangleLinesEx(rectBordaTitulo, 3.0f, YELLOW);
            }
            // Desenha as instruções
            const char* msgInstrucao = "COLETE TODAS AS MOEDAS PARA LIBERAR O FINAL!"; int tamFonteInstrucao = 20; Color corInstrucao = RAYWHITE;
            int larguraTextoInstrucao = MeasureText(msgInstrucao, tamFonteInstrucao); float paddingInstrucao = 8.0f;
            Rectangle recFundoInstrucao = { larguraTela / 2.0f - larguraTextoInstrucao / 2.0f - paddingInstrucao,(float)posNomeJogo.y + tamFonteNomeJogo + 40,(float)larguraTextoInstrucao + paddingInstrucao * 2.0f,(float)tamFonteInstrucao + paddingInstrucao * 2.0f };
            Vector2 posInstrucao = { recFundoInstrucao.x + paddingInstrucao,recFundoInstrucao.y + paddingInstrucao };
            DrawRectangleRec(recFundoInstrucao, Fade(BLACK, 0.6f)); DrawRectangleLinesEx(recFundoInstrucao, 2, GRAY);
            DrawText(msgInstrucao, (int)posInstrucao.x, (int)posInstrucao.y, tamFonteInstrucao, corInstrucao);
            const char* msgInicio = "Pressione R para comecar"; int tamFonteInicio = 20; Color corMsgInicio = LIGHTGRAY;
            int larguraTextoInicio = MeasureText(msgInicio, tamFonteInicio);
            DrawText(msgInicio, larguraTela / 2 - larguraTextoInicio / 2, (int)(recFundoInstrucao.y + recFundoInstrucao.height + 25), tamFonteInicio, corMsgInicio);
            EndDrawing();

        }
        else { // se o jogo começou
            // Roda a logica principal, se nao for fim de jogo ou vitoria
            if (!fimDeJogo && !jogoVencido) {
                if (IsKeyPressed(KEY_RIGHT)) jogadorGlobal.IniciarMovimento({ 1.0f,0.0f });
                if (IsKeyPressed(KEY_LEFT)) jogadorGlobal.IniciarMovimento({ -1.0f,0.0f });
                if (IsKeyPressed(KEY_UP)) jogadorGlobal.IniciarMovimento({ 0.0f,-1.0f });
                if (IsKeyPressed(KEY_DOWN)) jogadorGlobal.IniciarMovimento({ 0.0f,1.0f });

                if (jogadorGlobal.Atualizar(dt)) { // se o jogador passou de fase
                    CarregarMapa();
                    jogadorGlobal.posicao = { (float)tamanhoTile * 1.0f,(float)tamanhoTile * 1.0f };
                    jogadorGlobal.direcao = { 0.0f,0.0f }; jogadorGlobal.movendo = false;
                    perseguidorGlobal.posicao = { (float)tamanhoTile * 8.0f,(float)tamanhoTile * 1.0f };
                    perseguidorGlobal.direcaoMovimentoAtual = { 0.0f,0.0f };
                    if (faseAtual == 1)timerFase = limiteTempoFase2; else if (faseAtual == 2)timerFase = limiteTempoFase3; else timerFase = 0.0f;
                }

                for (auto& inimigo : inimigosAtiradores) { inimigo.Atualizar(dt, jogadorGlobal, projeteis); }
                for (auto it = projeteis.begin(); it != projeteis.end();) { it->Atualizar(dt); if (!it->ativo) it = projeteis.erase(it); else ++it; }

                // logica do tempo
                if (faseAtual == 1 || faseAtual == 2) {
                    timerFase -= dt;
                    if (timerFase <= 0) { if (!fimDeJogo) { if (musicaFundo.frameCount > 0 && IsMusicStreamPlaying(musicaFundo))StopMusicStream(musicaFundo); if (somDerrota.frameCount > 0)PlaySound(somDerrota); } fimDeJogo = true; }
                }

                if (faseAtual == 2) { perseguidorGlobal.Atualizar(dt, jogadorGlobal); }
            }

            // RENDERIZAÇÕES
            BeginDrawing();
            ClearBackground(DARKGRAY);
            for (int y = 0; y < alturaMapa; y++) {
                for (int x = 0; x < larguraMapa; x++) {
                    int v = mapa[y][x]; Color corTileBase = BLACK; bool desenharRecBase = true;
                    switch (v) {
                    case 1:corTileBase = GRAY; break;
                    case 2:desenharRecBase = false; DrawRectangle(x * tamanhoTile, y * tamanhoTile, tamanhoTile - 2, tamanhoTile - 2, BLACK);
                        if (texturaMoeda.id > 0) { float tam = tamanhoTile * 0.8f; Rectangle o = { 0,0,(float)texturaMoeda.width,(float)texturaMoeda.height }; Rectangle d = { (float)x * tamanhoTile + (tamanhoTile - tam) / 2.0f,(float)y * tamanhoTile + (tamanhoTile - tam) / 2.0f,tam,tam }; DrawTexturePro(texturaMoeda, o, d, { 0.0f,0.0f }, 0.0f, WHITE); }
                        else { DrawRectangle(x * tamanhoTile + (tamanhoTile * 0.2f) / 2.0f, y * tamanhoTile + (tamanhoTile * 0.2f) / 2.0f, tamanhoTile * 0.8f, tamanhoTile * 0.8f, YELLOW); }
                        break;
                    case 3:corTileBase = RED; break; case 4:corTileBase = DARKBLUE; break; case 5:corTileBase = SKYBLUE; break;
                    }
                    if (desenharRecBase) DrawRectangle(x * tamanhoTile, y * tamanhoTile, tamanhoTile - 2, tamanhoTile - 2, corTileBase);
                }
            }

            jogadorGlobal.Desenhar();
            for (const auto& inimigo : inimigosAtiradores) inimigo.Desenhar();
            for (const auto& projetil : projeteis) projetil.Desenhar();
            if (faseAtual == 2)perseguidorGlobal.Desenhar();

            if (faseAtual == 1 || faseAtual == 2) DrawText(TextFormat("Tempo: %.0f", timerFase), 10, 10, 20, WHITE);

            if (fimDeJogo) { DrawText("FIM DE JOGO!", larguraTela / 2 - MeasureText("FIM DE JOGO!", 40) / 2, alturaTela / 2 - 40, 40, RED); DrawText("Pressione R para reiniciar", larguraTela / 2 - MeasureText("Pressione R para reiniciar", 20) / 2, alturaTela / 2 + 10, 20, WHITE); }
            if (jogoVencido) { DrawText("PARABENS, VOCE VENCEU!!!", larguraTela / 2 - MeasureText("PARABÉNS, VOCÊ VENCEU!", 40) / 2, alturaTela / 2 - 40, 40, GOLD); DrawText("Pressione R para reiniciar", larguraTela / 2 - MeasureText("Pressione R para reiniciar", 20) / 2, alturaTela / 2 + 10, 20, WHITE); }
            EndDrawing();

            // Volta para a tela de inicio se o jogo acabar
            if ((fimDeJogo || jogoVencido) && IsKeyPressed(KEY_R)) { jogoIniciado = false; }
        }
    }

    // Limpeza final
    UnloadSound(somVitoria);
    UnloadSound(somDerrota);
    UnloadSound(somMoeda);
    UnloadMusicStream(musicaFundo);
    UnloadTexture(texturaMoeda);
    CloseAudioDevice();
    CloseWindow();

    //FIMM DO PROGRAMA
    return 0;
}




