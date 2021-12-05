#include <iostream>
#include <string>
#include <limits>
#include <cstring>
#include "myarray.hpp"

using namespace std;

// ------------------------- METODOS E FUNCOES --------------------------------

void pause (string text)
{
    cout << text << endl;
    getchar();
}



/**
 * leString - funcao para ler string
 * @return string lida
 * @param text - texto a ser mostrado
*/
string leString ( string text)
{
    string x = "";

    cout << text;
    cin >> x;

    return x;
}

// ------------------------- PRINCIPAIS ---------------------------------------

void verCategoria ()
{
    string categoria = leLinha("\nEntrar com nome da categoria: ");

    Array <string> arranjo( 0, categoria, "falha" );

    arranjo.fread(categoria);
    arranjo.print();
    // arranjo.atualizarPosicao(3);
    // arranjo.print();
    // arranjo.print();
    // arranjo.trocarPosicao(1,3);
    // arranjo.print();

    arranjo.free();

    pause ("\nApertar ENTER para continuar\n");
}

void novaCategoria ()
{
    string categoria = leLinha("\nEntrar com nome da categoria: ");

    int n = 0;
    n = leValorInteiro(1,10,"\nEntrar com quantidade de itens: ");

    Array <string> arranjo( n, categoria, "falha" );

    arranjo.read();
    arranjo.print();
    // arranjo.atualizarPosicao(3);
    // arranjo.print();
    arranjo.fprintData(categoria);
    arranjo.fprintFile(categoria);
    // arranjo.trocarPosicao(3,1);
    // arranjo.print();
    // arranjo.trocarPosicao(1,3);
    // arranjo.print();

    arranjo.free();

    pause ("\nApertar ENTER para continuar\n");
}

void adicionarItem ()
{
    string categoria = leLinha("\nEntrar com nome da categoria: ");
    Array <string> arranjo( 0, categoria, "falha" );
    arranjo.newItem(categoria);
    arranjo.print();
    arranjo.atualizarPosicao((arranjo.getLength())-1);
    arranjo.print();
    arranjo.fprintData(categoria);
    arranjo.fprintFile(categoria);
    arranjo.free();

}

void editarItem ()
{
    string categoria = leLinha("\nEntrar com nome da categoria: ");
    int n = 0;

    Array <string> arranjo(0,categoria,"falha");

    arranjo.fread(categoria);
    arranjo.print();
    n = leValorInteiro(1,(arranjo.getLength()), "\nEscolher item(posicao): ");
    arranjo.atualizarPosicao(n-1);
    arranjo.print();
    arranjo.fprintData(categoria);
    arranjo.fprintFile(categoria);
    arranjo.free();
}

// ------------------------- FUNCAO PRINCIPAL ---------------------------------

int main ()
{ 
    int x = 0;

    do 
    {
        cout << "Opcoes:" << endl;
        cout << "0 - parar" << endl;
        cout << "1 - ver categoria" << endl;
        cout << "2 - adicionar categoria" << endl;
        cout << "3 - adicionar item" << endl;
        cout << "4 - editar item" << endl;
        cout << "\nEscolher opcao: ";
        cin >> x;

        switch (x)
        {
        case 0:
        break;
        case 1:
        verCategoria();
        break;
        case 2:
        novaCategoria();
        break;
        case 3:
        adicionarItem();
        break;
        case 4:
        editarItem();
        break;
        default:
        cout << "\nValor invalido" << endl;
        break;
        }
    } while (x!=0);
 
    return 0;
}