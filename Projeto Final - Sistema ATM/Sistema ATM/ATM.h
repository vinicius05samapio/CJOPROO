// ATM.h
// Definição da classe ATM. Representa um caixa automático.
#ifndef ATM_H
#define ATM_H

#include "Screen.h" // definição da classe Screen
#include "Keypad.h" // definição da classe Keypad
#include "CashDispenser.h" // definição da classe CashDispenser
#include "DepositSlot.h" // definição da classe DepositSlot
#include "BankDatabase.h" // definição da classe BankDatabase
class Transaction; // declaração forward da classe Transaction

class ATM
{
public:
    ATM(); // o construtor inicializa membros de dados
    void run(); // inicia o ATM
private:
    bool userAuthenticated; // se o usuário foi autenticado
    int currentAccountNumber; // número atual da conta de usuário
    Screen screen; // tela do ATM
    Keypad keypad; // teclado do ATM
    CashDispenser cashDispenser; // dispensador de cédulas do ATM
    DepositSlot depositSlot; // abertura para depósito do ATM
    BankDatabase bankDatabase; // banco de dados com as informações sobre as contas

    // funções utilitárias private
    void authenticateUser(); // tenta autenticar o usuário
    void performTransactions(); // realiza transações
    int displayMainMenu() const; // exibe o menu principal

    // retorna o objeto da classe derivada Transaction especificada
    Transaction *createTransaction( int );
}; // fim da classe ATM

#endif // ATM_H