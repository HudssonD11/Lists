/*
  myarray.hpp - v0.0 - 16 / 11 / 2021
  Author: Hudsson Davih Apolinario de Andrade
*/

// --------------------------------------------- definicoes globais

#ifndef _MYARRAY_HPP_
#define _MYARRAY_HPP_

// dependencias
#include <iostream>
using std::cin;  // para entrada
using std::cout; // para saida
using std::endl; // para mudar de linha

#include <iomanip>
using std::setw; // para definir espacamento

#include <string>
using std::string; // para cadeia de caracteres

#include <fstream>
using std::ofstream; //para gravar arquivo
using std::ifstream; //para ler arquivo

int leValorInteiro (int inf, int sup, string text)
{
    int x = 0;

    do 
    {
        cout << text;
        cin >> x;
    } while (x<inf || x>sup);

    return x;
}

/**
    Funcao para ler uma linha inteira.
    @return linha lida
    @param  text - mensagem a ser exibida antes da leitura
 */
char* leLinha ( string text )
{
  string buffer;
  static char tmp [80];

  cout << text ;
  char x = '0';
  do { x = getchar( ); } while ( '\n' != x );     // limpar a entrada de dados
  getline ( cin, buffer, '\n' );

  strcpy ( tmp, buffer.c_str( ) );
  return ( &(tmp[0]) );
} // fim IO_readln ( )

string adcTXT (string nome)
{
    string nova = nome;
    nova += ".TXT";
    return nova;
}

string adcDADOSTXT (string nome)
{
    string nova = nome;
    nova += "Dados.TXT";
    return nova;
}

string underline (string nome)
{
    string nova = nome;

    for (int i=0; i<nova.length(); i++)
    {
        if (nova[i] == ' ')
        {
            nova[i] = '_';
        }
    }

    return nova;
}

string noUnderline (string nome)
{
    string nova = nome;

    for (int i=0; i<nova.length(); i++)
    {
        if (nova[i] == '_')
        {
            nova[i] = ' ';
        }
    }

    return nova;
}


template <typename T>
class Array
{
    private: //area reservada
        T optional;
        int length;
        T *data;
        T nome;
        int *posicoes;
    
    public: // area aberta
        Array (int n,string name, T initial)
        {
         // definir valores iniciais
            optional = initial;
            length   = 0;
            data     = nullptr;
            posicoes = nullptr;
            nome = name;

         // reservar area
            if (n>0)
            {
                length   = n;
                data     = new T [length];
                posicoes = new int [length];
            }
        } // end constructor

        Array () // construtor padrao
        {
         // definir valores iniciais
            length = 0;
         // reservar area
            data = nullptr;
        } // end constructor()

        Array (const Array & other)
        {
            if (other.length<=0)
            {
                cout << "\nERROR: Missing data.\n" << endl;
            }
            else
            {
             // criar copia
                length = other.length;
             // reservar area
                data = new T [other.length];
             // ler dados
                for (int x=0; x<length; x++)
                {
                    data[x] = other.data[x];
                } // end for
            } // end if
        } // end constructor()

        Array & operator= (const Array <T> other)
        {
            if (other.length<=0)
            {
                cout << "\nERROR: Missing data.\n" << endl;
            }
            else
            {
                this->length = other.length;
                this->data   = new T [other.length];
                for (int x=0; x<this->length; x++)
                {
                    data[x] = other.data[x];
                } // end for
            } // end if
            return (*this);
        } // end operator=()

        const int getLength ()
        {
            return length;
        } // end getLength()

        T & operator[] (const int position)
        {
            static T value = optional;

            if (position < 0 || length<=position)
            {
                cout << endl << "\nERROR: Invalid position.\n" << endl;
            }
            else
            {
                value = data[position];
            } // end if
            return value;
        } // end operator[]

        void free ()
        {
            if (data!=nullptr)
            {
                for (int i=0; i<length; i++)
                {
                    data[i].clear();
                }
                data = nullptr;
            } // end if
            if (posicoes!=nullptr)
            {
                delete (posicoes);
                posicoes = nullptr;
            } // end if
        } // end free()

        void set (int position, T value)
        {
            if (0<=position && position<length)
            {
                data[position] = value;
            } // end if
        } // end set()

        T get (int position)
        {
            T value = optional;

            if (0<=position && position<length)
            {
                value = data[position];
            } // end if

            return (value);
        } // end get()

        int getId (int position)
        {
            int value = -1;

            if (0<=position && position<length)
            {
                value = posicoes[position];
            } // end if

            return (value);
        } // end get()

        void print()
        {
            int aux = -1;
            cout<<endl;
            cout << "\n" << nome << endl << endl;
            for (int x = 0; x<length; x=x+1)
            {
                aux = this->getId(x);
                cout<< (x+1) <<": " << data[aux] <<endl;
            } // end for
            cout<<endl;
        } // end print()

        string getItem (int n)
        {
            int a = 0;
            a = posicoes[n];
            string value = data[a];
            return value;
        }

        void newItem (string fileName)
        {
            ifstream afile;  // input file
            string file = adcDADOSTXT(underline(fileName));
            int n = 0;
            afile.open(file);
            afile >> n;
            if (n<=0)
            {
                cout << "\nERROR: Invalid file.\n" << endl;
            }
            else
            {
            // guardar a quantidade de dados
                length = n+1;
            // reservar area
                posicoes = new int [n+1];
                data = new T[n+1];
            // ler dados
                for (int x=0; x<length-1; x++)
                {
                    afile >> posicoes[x];
                } // end for
                for (int x=0; x<length-1; x++)
                {
                    afile >> data[x];
                    data[x] = noUnderline(data[x]);
                } // end for
                posicoes[n] = n;
                string novoitem = "";
                cout << "\nEntrar com novo item: ";
                cin >> novoitem;
                data[n] = noUnderline(novoitem);
            } // end if
            afile.close();
        }

        void read()
        {
            cout << endl;
            for (int x=0; x<length; x=x+1)
            {
                cout << setw(3) << x << " : ";
                cin >> data[x];
                data[x] = noUnderline(data[x]);
                posicoes[x] = x;
            } // end for
            cout << endl;
        } // end read()

        void fprintData (string fileName)
        {
            ofstream afile;  // output file
            string file = adcDADOSTXT(underline(fileName));
            afile.open (file);
            afile << length << endl;
            for (int x=0; x<length; x=x+1)
            {
                afile << posicoes[x] << endl;
            } // end for
            for (int x=0; x<length; x=x+1)
            {
                afile << underline(data[x]) << endl;
            } // end for
            afile.close();
        } // end fprint()

        void fprintFile (string fileName)
        {
            int aux = -1;
            ofstream afile;  // output file
            string file = adcTXT(underline(fileName));
            
            afile.open (file);
            // afile << length << endl;
            // for (int x=0; x<length; x=x+1)
            // {
                // afile << posicoes[x] << endl;
            // } // end for
            afile << noUnderline(fileName) << endl << endl;
            for (int x=0; x<length; x=x+1)
            {
                aux = this->getId(x);
                afile << (x+1) << ": ";
                afile << data[aux] << endl;
            } // end for
            afile.close();
        } // end fprint()

        void fread(string fileName)
        {
            ifstream afile;  // input file
            string file = adcDADOSTXT(underline(fileName));
            int n = 0;
            afile.open(file);
            afile >> n;
            if (n<=0)
            {
                cout << "\nERROR: Invalid length.\n" << endl;
            }
            else
            {
            // guardar a quantidade de dados
                length = n;
            // reservar area
                posicoes = new int [n];
                data = new T[n];
            // ler dados
                for (int x=0; x<length; x++)
                {
                    afile >> posicoes[x];
                } // end for
                for (int x=0; x<length; x++)
                {
                    afile >> data[x];
                    data[x] = noUnderline(data[x]);
                } // end for
            } // end if
            afile.close();
        } // end fread()

        void trocarPosicao (int origem, int destino)
        {
            if (origem!=destino && origem>=0 && destino>=0 && origem<length && destino<length)
            {
                if (origem>destino)
                {
                    for (int i=origem; i>destino; i--)
                    {
                        this->swapPosition(i,true);
                    }
                }
                else
                {
                    for (int i=origem; i<destino; i++)
                    {
                        this->swapPosition(i,false);
                    }
                }
            }
        }

        void atualizarPosicao (int x)
        {
            if (x<length && x>=0)
            {
                int i = length-1;
                bool melhor = true;
                int auxiliar = -1;
                while (melhor && i>=0)
                {
                    if (i!=x)
                    {
                        cout << "\n" << getItem(x) << " e' melhor que " << getItem(i) << "?";
                        auxiliar = leValorInteiro(0,1,"\n1: SIM\n0: NAO\n");
                        melhor = (auxiliar==1);
                    }
                    i--;
                }
                i++;
                if (!melhor)
                {
                    i++;
                }
                
                trocarPosicao(x,i);
            }
        }

        void swapPosition (int x, bool subir)
        {
            if (x<length && x>=0)
            {
                if (subir && x>0)
                {
                    int aux = posicoes[x];
                    posicoes[x] = posicoes[x-1];
                    posicoes[x-1] = aux;
                }
                else
                {
                    if (!subir && x<(length-1))
                    {
                        int aux = posicoes[x];
                        posicoes[x] = posicoes[x+1];
                        posicoes[x+1] = aux;
                    }
                }
            }
        }

        const int getPosition (int valor)
        {
            int posicao = -1;
            if (valor>=0 && valor<length)
            {
                bool result = false;
                int i = 0;
                result = (valor == posicoes[i]);
                if (result)
                {
                    posicao = i;
                }
                i++;
                while ( !result && i<=length)
                {
                    result = (valor == posicoes[i]);
                    if (result)
                    {
                        posicao = i;
                    }
                    i++;
                }
            }

            return posicao;
        }

        bool operator!= (const Array<T> other)
        {
            bool result = true;
            int x       = 0;

            if (other.length == 0 || length!=other.length)
            {
                cout << "\nERROR: Missing data.\n" << endl;
            }
            else
            {
                x = 0;
                while (x<this->length && result)
                {
                    result = result && (data[x] == other.data[x]);
                    x++;
                } // end while
            } // end if
            return (!result);
        } // end operator!=()

        Array & operator- (const Array<T> other)
        {
            static Array <T> result (other);

            if (other.length<=0)
            {
                cout << "\nERROR: Missing data.\n" << endl;
            }
            else
            {
                for (int x=0; x<length; x++)
                {
                    result.data[x] = this->data[x] - result.data[x];
                } // end for
            } // end if
            return (result);
        } // end operator-()
};

// ----------------------- OUTROS METODO E FUNCOES -----------------------



// string nomeTela (string nome)
// {
//     string nova = nome;

//     for (int i=0; i<nova.length(); i++)
//     {
//         if (nova[i] == '_')
//         {
//             nova[i] = ' ';
//         }
//     }

//     return nova;
// }

// -----------------------------------------------------------------------

#endif