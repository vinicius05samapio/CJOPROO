// Screen.h
// Definição da classe Screen. Representa a tela do ATM.
#ifndef SCREEN_H
#define SCREEN_H

#include <string>
using std::string;

class Screen
{
public:
    void displayMessage( string ) const; // gera saída de uma mensagem
    void displayMessageLine( string ) const; // gera saída da mensagem com nova linha
    void displayDollarAmount( double ) const; // gera saída de um valor em dólar
}; // fim da classe Screen

#endif // SCREEN_H
