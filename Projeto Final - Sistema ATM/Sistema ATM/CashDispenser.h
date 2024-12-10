// CashDispenser.h
// Definição da classe CashDispenser. Representa o ATM para o dispensador de cédulas.
#ifndef CASH_DISPENSER_H
#define CASH_DISPENSER_H

class CashDispenser
{
public:
    CashDispenser(); // o construtor inicializa contagem de conta para 500

    // simula a entrega da quantia especificada de cédulas
    void dispenseCash( int );

    // indica se o dispensador de cédulas pode entregar a quantia desejada
    bool isSufficientCashAvailable( int ) const;

private:
    const static int INITIAL_COUNT = 500;
    int count; // número de cédulas de $20 remanescente
}; // fim da classe CashDispenser

#endif // CASH_DISPENSER_H
