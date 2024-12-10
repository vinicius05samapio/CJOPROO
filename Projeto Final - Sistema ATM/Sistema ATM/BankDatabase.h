// BankDatabase.h
// Definição da classe BankDatabase. Representa o banco de dados do banco.
#ifndef BANK_DATABASE_H
#define BANK_DATABASE_H

#include <vector> // a classe utiliza vector para armazenar objetos Account
using std::vector;

#include "Account.h" // definição da classe Account

class BankDatabase
{
public:
    BankDatabase(); // o construtor inicializa as contas

    // determina se o número de conta e o PIN correspondem aos de uma Account
    bool authenticateUser( int, int ); // retorna true se a Account for autêntica

    double getAvailableBalance( int ); // obtém um saldo disponível
    double getTotalBalance( int ); // obtém o saldo total de uma Account
    void credit( int, double ); // adiciona o valor ao saldo de Account
    void debit( int, double ); // subtrai o valor do saldo de Account

private:
    vector< Account > accounts; // vector das Accounts do banco

    // função utilitária private
    Account * getAccount( int ); // obtém ponteiro para o objeto Account
}; // fim da classe BankDatabase

#endif // BANK_DATABASE_H
