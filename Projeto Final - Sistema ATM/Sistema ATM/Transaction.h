// Transaction.h
// Definição da classe básica abstrata Transaction.
#ifndef TRANSACTION_H
#define TRANSACTION_H

class Screen; // declaração antecipada da classe Screen
class BankDatabase; // declaração antecipada da classe BankDatabase

class Transaction
{
public:
    // o construtor inicializa recursos comuns de todas as Transactions
    Transaction( int, Screen &, BankDatabase & );

    virtual ~Transaction() { } // destrutor virtual com corpo vazio

    int getAccountNumber() const; // retorna o número da conta
    Screen &getScreen() const; // retorna a referência à tela
    BankDatabase &getBankDatabase() const; // retorna referência ao banco de dados

    // função virtual pura para realizar a transação
    virtual void execute() = 0; // sobrescrita em classes derivadas

private:
    int accountNumber; // indica conta envolvida
    Screen &screen; // referência à tela ATM
    BankDatabase &bankDatabase; // referência ao banco de dados de informações de conta
}; // fim da classe Transaction

#endif // TRANSACTION_H
