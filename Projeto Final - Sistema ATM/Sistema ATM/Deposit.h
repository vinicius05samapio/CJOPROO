// Deposit.h
// Definição da classe Deposit. Representa uma transação de depósito.
#ifndef DEPOSIT_H
#define DEPOSIT_H

#include "Transaction.h" // definição da classe Transaction
class Keypad; // declaração antecipada da classe Keypad
class DepositSlot; // declaração antecipada da classe DepositSlot

class Deposit : public Transaction
{
public:
    Deposit( int, Screen &, BankDatabase &, Keypad &, DepositSlot & );
    virtual void execute(); // realiza a transação
private:
    double amount; // quantia a depositar
    Keypad &keypad; // referência ao teclado do ATM
    DepositSlot &depositSlot; // referência à abertura de depósito do ATM
    double promptForDepositAmount() const; // obtém a quantia de depósito do usuário
}; // fim da classe Deposit

#endif // DEPOSIT_H
