// BalanceInquiry.h
// Definição da classe BalanceInquiry. Representa uma consulta de saldo.
#ifndef BALANCE_INQUIRY_H
#define BALANCE_INQUIRY_H

#include "Transaction.h" // definição da classe Transaction

class BalanceInquiry : public Transaction
{
public:
    BalanceInquiry( int, Screen &, BankDatabase & ); // construtor
    virtual void execute(); // realiza a transação
}; // fim da classe BalanceInquiry

#endif // BALANCE_INQUIRY_H
