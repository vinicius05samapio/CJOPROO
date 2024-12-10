// Account.cpp
// Definições de função-membro para a classe Account.
#include "Account.h" // definição da classe Account

// o construtor Account inicializa os atributos
Account::Account( int theAccountNumber, int thePIN,
                  double theAvailableBalance, double theTotalBalance )
: accountNumber( theAccountNumber ),
  pin( thePIN ),
  availableBalance( theAvailableBalance ),
  totalBalance( theTotalBalance )
{
    // corpo vazio
} // fim do construtor Account

// determina se um PIN especificado pelo usuário corresponde ao PIN em Account
bool Account::validatePIN( int userPIN ) const
{
    if ( userPIN == pin )
        return true;
    else
        return false;
} // fim da função validatePIN

// retorna o saldo disponível
double Account::getAvailableBalance() const
{
    return availableBalance;
} // fim da função getAvailableBalance

// retorna o saldo total
double Account::getTotalBalance() const
{
    return totalBalance;
} // fim da função getTotalBalance

// credita uma quantia à conta
void Account::credit( double amount )
{
    totalBalance += amount; // adiciona ao saldo total
} // fim da função credit

// debita uma quantia da conta
void Account::debit( double amount )
{
    availableBalance -= amount; // subtrai do saldo disponível
    totalBalance -= amount; // subtrai do saldo total
} // fim da função debit

// retorna o número da conta
int Account::getAccountNumber() const
{
    return accountNumber;
} // fim da função getAccountNumber
