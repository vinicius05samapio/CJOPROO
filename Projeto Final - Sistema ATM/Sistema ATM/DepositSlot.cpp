// DepositSlot.cpp
// Definição de função-membro da classe DepositSlot.
#include "DepositSlot.h" // definição da classe DepositSlot

// indica se o envelope foi recebido (sempre retorna true,
// porque esta é apenas uma simulação do software de uma abertura para depósito real)
bool DepositSlot::isEnvelopeReceived() const
{
    return true; // o envelope de depósito foi recebido
} // fim da função isEnvelopeReceived
