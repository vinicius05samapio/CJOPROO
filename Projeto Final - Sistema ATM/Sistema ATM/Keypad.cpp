// Keypad.cpp
// Definição da função-membro da classe Keypad (o teclado do ATM).
#include <iostream>
using std::cin;

#include "Keypad.h" // definição da classe Keypad

// retorna um valor de inteiro inserido pelo usuário
int Keypad::getInput() const
{
    int input; // variável para armazenar a entrada
    cin >> input; // supomos que o usuário insere um inteiro
    return input; // retorna o valor inserido pelo usuário
} // fim da função getInput
