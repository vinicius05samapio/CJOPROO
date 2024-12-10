// Deposit.cpp
// Definições de função-membro para a classe Deposit.
#include "Deposit.h" // definição da classe Deposit
#include "Screen.h" // definição da classe Screen
#include "BankDatabase.h" // definição da classe BankDatabase
#include "Keypad.h" // definição da classe Keypad
#include "DepositSlot.h" // definição da classe DepositSlot

const static int CANCELED = 0; // constante representando a opção de cancelamento

// o construtor Deposit inicializa os membros de dados da classe
Deposit::Deposit( int userAccountNumber, Screen &atmScreen,
    BankDatabase &atmBankDatabase, Keypad &atmKeypad,
    DepositSlot &atmDepositSlot )
: Transaction( userAccountNumber, atmScreen, atmBankDatabase ),
  keypad( atmKeypad ), depositSlot( atmDepositSlot )
{
    // corpo vazio
} // fim do construtor de Deposit

// realiza transação; sobrescreve a função virtual pura da Transaction
void Deposit::execute()
{
    BankDatabase &bankDatabase = getBankDatabase(); // obtém a referência
    Screen &screen = getScreen(); // obtém a referência

    amount = promptForDepositAmount(); // obtém a quantia de depósito do usuário

    // verifica se o usuário inseriu uma quantia de depósito ou cancelou
    if ( amount != CANCELED )
    {
        // solicita o envelope de depósito contendo a quantia especificada
        screen.displayMessage(
            "\nPor favor, insira um envelope de deposito contendo " );
        screen.displayDollarAmount( amount );
        screen.displayMessageLine( " no slot de deposito." );

        // recebe o envelope de depósito
        bool envelopeReceived = depositSlot.isEnvelopeReceived();

        // verifica se o envelope de depósito foi recebido
        if ( envelopeReceived )
        {
            screen.displayMessageLine( "\nSeu envelope foi recebido."
                "\nNOTA: O dinheiro nao estara disponivel ate que nos"
                "\nverifique o valor de qualquer dinheiro incluso e qualquer valor incluso "
                "\ncheques limpos." );

            // credita na conta para refletir o depósito
            bankDatabase.credit( getAccountNumber(), amount );
        } // fim do if
        else // o envelope de depósito não foi recebido
        {
            screen.displayMessageLine( "\nVoce nao inseriu um "
                "envelope, entao o caixa eletronico cancelou sua transacao." );
        } // fim do else
    } // fim do if
    else // o usuário cancelou em vez de inserir uma quantia
    {
        screen.displayMessageLine( "\nCancelando transacao..." );
    } // fim do else
} // fim da função execute

// solicita que o usuário insira uma quantia de depósito em centavos
double Deposit::promptForDepositAmount() const
{
    Screen &screen = getScreen(); // obtém a referência à tela

    // exibe o prompt e recebe a entrada
    screen.displayMessage( "\nPor favor, insira o valor do deposito "
        "CENTAVOS (ou 0 para cancelar): " );
    int input = keypad.getInput(); // recebe a entrada da quantia do depósito

    // verifica se o usuário cancelou ou inseriu uma quantia válida
    if ( input == CANCELED )
        return CANCELED;
    else
    {
        return static_cast< double >( input ) / 100; // retorna a quantia em dólares
    } // fim do else
} // fim da função promptForDepositAmount
