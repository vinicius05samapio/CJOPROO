// CashDispenser.cpp
// Definições de função-membro da classe CashDispenser.
#include "CashDispenser.h" // definição da classe CashDispenser

// o construtor-padrão CashDispenser inicializa a contagem como padrão
CashDispenser::CashDispenser()
{
    count = INITIAL_COUNT; // configura atributo count como o padrão
} // fim do construtor-padrão CashDispenser

// simula a liberação da quantia em dinheiro especificada; supõe que há dinheiro suficiente
// disponível (chamada anterior para isSufficientCashAvailable retornou true)
void CashDispenser::dispenseCash( int amount )
{
    int billsRequired = amount / 20; // número de cédulas de $20 requerido
    count -= billsRequired; // atualiza a contagem das cédulas
} // fim da função dispenseCash

// indica se o dispensador de cédulas pode entregar a quantia desejada
bool CashDispenser::isSufficientCashAvailable( int amount ) const
{
    int billsRequired = amount / 20; // número de cédulas de $20 requerido

    if ( count >= billsRequired )
        return true; // cédulas suficientes estão disponíveis
    else
        return false; // não há cédulas suficientes disponíveis
} // fim da função isSufficientCashAvailable
