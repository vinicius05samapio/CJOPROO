// Account.h
// Definição da classe Account. Representa uma conta bancária.
#ifndef ACCOUNT_H
#define ACCOUNT_H

class Account
{
public:
    Account( int, int, double, double ); // o construtor configura atributos
    bool validatePIN( int ) const; // o PIN especificado pelo usuário é correto?
    double getAvailableBalance() const; // retorna o saldo disponível
    double getTotalBalance() const; // retorna o saldo total
    void credit( double ); // adiciona um valor ao de Account
    void debit( double ); // subtrai uma quantia do saldo de Account
    int getAccountNumber() const; // retorna o número da conta

private:
    int accountNumber; // número da conta
    int pin; // PIN para autenticação
    double availableBalance; // fundos disponíveis para retirada
    double totalBalance; // fundos disponíveis + fundos esperando compensação
}; // fim da classe Account

#endif // ACCOUNT_H
