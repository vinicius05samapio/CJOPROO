// Screen.cpp
// Definições de função-membro para a classe Screen.
#include <iostream>
using std::cout;
using std::endl;
using std::fixed;

#include <iomanip>
using std::setprecision;

#include "Screen.h" // definição da classe Screen

// gera saída de uma mensagem sem uma nova linha
void Screen::displayMessage( string message ) const
{
    cout << message;
} // fim da função displayMessage

// gera saída de uma mensagem com uma nova linha
void Screen::displayMessageLine( string message ) const
{
    cout << message << endl;
} // fim da função displayMessageLine

// gera saída de um valor em dólar
void Screen::displayDollarAmount( double amount ) const
{
    cout << fixed << setprecision( 2 ) << "$" << amount;
} // fim da função displayDollarAmount
