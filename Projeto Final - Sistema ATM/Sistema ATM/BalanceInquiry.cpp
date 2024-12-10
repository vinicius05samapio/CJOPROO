// BalanceInquiry.cpp
// Definições de função-membro da classe BalanceInquiry.
#include "BalanceInquiry.h" // definição da classe BalanceInquiry
#include "Screen.h" // definição da classe Screen
#include "BankDatabase.h" // definição da classe BankDatabase

// o construtor BalanceInquiry inicializa os membros de dados de classe básica
BalanceInquiry::BalanceInquiry( int userAccountNumber, Screen &atmScreen,
    BankDatabase &atmBankDatabase )
    : Transaction( userAccountNumber, atmScreen, atmBankDatabase )
{
    // corpo vazio
} // fim do construtor de BalanceInquiry

// realiza transação; sobrescreve a função virtual pura da Transaction
void BalanceInquiry::execute()
{
    // obtém as referências ao banco de dados e tela do banco
    BankDatabase &bankDatabase = getBankDatabase();
    Screen &screen = getScreen();

    // obtém o saldo disponível da Account do usuário atual
    double availableBalance = 
        bankDatabase.getAvailableBalance( getAccountNumber() );

    // obtém o saldo total da Account do usuário atual
    double totalBalance = 
        bankDatabase.getTotalBalance( getAccountNumber() );

    // exibe as informações sobre o saldo na tela
    screen.displayMessageLine( "\nInformacoes de saldo:" );
    screen.displayMessage( " - Saldo disponivel: " );
    screen.displayDollarAmount( availableBalance );
    screen.displayMessage( "\n - Saldo total: " );
    screen.displayDollarAmount( totalBalance );
    screen.displayMessageLine( "" );
} // fim da função execute