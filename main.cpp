//TRABALHO
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <locale.h>
#include <string.h>
//#include "funcoes.h"
//#include <conio.h>

using namespace std;

//GLOBAIS
const int TAM = 1000;
int totalProd = 0;

/*AS DUAS FUNÇÕES QUE PODEM ALTERAR SÃO A FUNÇÃO CADASTRAR E REMOVER*/
//obs: a função menu está recebendo &totalProd para a função Cadastrar poder modificar a variável

struct Produto
{
    unsigned int cod;
    //char descricao[1000];
    char nome[1000];
    long double preco;
    unsigned int quant;

};

//FUNÇÕES

//Muda o código do produto com indice n
void Codigo(Produto *p, int n)
{
    char aux[100];

    do
    {
        cout << "\nCódigo: ";
        cin >> aux;
        fflush(stdin);

        p[n].cod = atoi(aux);

        if(p[n].cod == 0) cout << "\nCódigo inválido.\n";

        else
        {

            for(int i = 0; i < totalProd; i++)  // verifica se o código digitado existe para outro produto
            {
                if(p[i].cod == p[n].cod)
                {
                    p[n].cod = 0;
                    cout << "\nJá existe um produto com esse código.\n";
                    break;
                }
            }
        }

    }
    while(p[n].cod == 0);

}

//Muda o nome do produto com indice n
void Nome(Produto *p, int n)
{

    cout << "\nNome: ";
    gets(p[n].nome);
    fflush(stdin);

}

//Muda a quantidade do produto com indice n
void Quantidade(Produto *p, int n)
{
    char aux[100];

    do
    {
        cout << "\nQuantidade: ";
        cin >> aux;
        fflush(stdin);

        p[n].quant = atoi(aux);

    }
    while(p[n].quant == 0);


}

//Muda o preço do produto com indice n
void Preco(Produto *p, int n)
{
    char aux[100];

    do
    {
        cout << "\nPreço: ";
        cin >> aux;
        fflush(stdin);

        p[n].preco = atof(aux);

    }
    while(p[n].preco == 0);

}

//Ordena os produtos em ordem alfabética
//e coloca todos os produtos com código = 0 nas últimas posições
void Ordenar(Produto *p)
{

    unsigned int codAux;
    char nomeAux[1000];
    long double precoAux;
    unsigned int quantAux;


    for(int i = 0; i < totalProd; i++)
    {

        for(int j = i+1; j <= totalProd; j++)
        {

            if(stricmp(p[i].nome, p[j].nome) > 0 || p[i].cod == 0)
            {

                codAux = p[j].cod;
                p[j].cod = p[i].cod;
                p[i].cod = codAux;

                strcpy(nomeAux, p[j].nome);
                strcpy(p[j].nome, p[i].nome);
                strcpy(p[i].nome, nomeAux);

                precoAux = p[j].preco;
                p[j].preco = p[i].preco;
                p[i].preco = precoAux;

                quantAux = p[j].quant;
                p[j].quant = p[i].quant;
                p[i].quant = quantAux;

            }

        }

    }
}

//Cadastra novo produto
void Cadastrar ( Produto *p, int &totalProd)
{
    if(totalProd < TAM - 1) //VERIFICAÇÃO DE LIMITE
    {

        if(totalProd == 0) cout << "\n\tAVISO\n"
                                    << "\nNão existem produtos cadastrados."
                                    <<"\nPor favor, cadastre um produto\n";

        else
        {
            cout << "\n\tCADASTRAR\n";
        }

        Codigo(p, totalProd);
        Nome(p, totalProd);
        Quantidade(p, totalProd);
        Preco(p, totalProd);

        Ordenar(p);

        totalProd++;

        cout << "\n";
        system("PAUSE");
    }

    else
    {
        cout << "\nFalha no cadastro do produto. Quantidade de produtos máximos cadastrados.";
        system("PAUSE");
    }

}

//Busca um produto especifico pelo código.
//Se o código foi encontrado, retorna seu índice
//Se o código não for encontrado, retorna -1
int BuscarIndice (Produto *p)
{
    unsigned int c = 0, op, n; // "n" é o índice do produto
    bool encontrado = false;
    char aux[100];

    do
    {
        op = 0;

        do
        {

            cout << "\nDigite o código do produto: ";
            cin >> aux;
            fflush (stdin);

            c = atof(aux);

            if(c == 0) cout << "\nCódigo inválido";

        }
        while(c == 0);

        for(int i = 0; i <= totalProd; i++)
        {

            if(p[i].cod == c)
            {
                n = i;
                encontrado = true;
                break;
            }

        }

        if(!encontrado)
        {
            do
            {
                cout << "\nCódigo não encontrado."
                     << "\nTentar novamente? 1.Sim  2.Não"
                     <<"\nOpção: ";
                cin>> aux;
                fflush(stdin);

                op = atoi(aux);

                if(op < 1 || op > 2) cout << "\nOpção inválida!\n";

            }
            while(op < 1 || op > 2);
        }

    }
    while(op == 1);

    if(op == 2) return -1;
    else return n;

}

//Exibe menu para usuario escolher o que quer editar do produto
//e retorna a opção do usuário
int MenuEditar()
{
    char aux[100];
    int op;

    do
    {
        cout << "\n1. Código"
             << "\n2. Descrição"
             << "\n3. Quantidade"
             << "\n4. Preço"
             << "\n5. Sair"
             << "\nDigite a opção que deseja alterar no produto: ";

        cin >> aux;
        fflush(stdin);

        op = atoi(aux);

        if(op < 1 || op > 5) cout << "\nOpção inválida!\n";

    }
    while(op < 1 || op > 5);

    return op;

}

//Função para editar dados do produto
void Editar (Produto *p)
{
    char aux[100];
    int n, op; // "n" é o indice do produto

    system("cls");
    cout << "\n\tEDITAR\n";
    n = BuscarIndice(p);

    if(n > -1)
    {
        do
        {
            op = MenuEditar();

            if(op != 5) cout << "\nNovos dados"; // op = 5 é opção sair

            switch(op)
            {

            case 1:
                Codigo(p, n);
                break;

            case 2:
                Nome(p, n);
                break;

            case 3:
                Quantidade(p, n);
                break;

            case 4:
                Preco(p, n);
                break;


            }

            if(op != 5)  // a opção 5 é para sair do menu editar
            {

                do
                {
                    cout << "\nDeseja editar algo mais deste produto? 1.Sim  2.Não"
                         << "\nOpção: ";
                    cin >> aux;
                    fflush(stdin);

                    op = atoi(aux);

                    if(op < 1 || op > 2) cout << "\nOpção inválida!";

                }
                while(op < 1 || op > 2);

                if(op != 1)
                {
                    do
                    {
                        cout << "\nDeseja editar outro produto? 1.Sim  2.Não"
                             << "\nOpção: ";

                        cin >> aux;
                        fflush(stdin);

                        op = atoi(aux);

                        if(op < 1 || op > 2) cout << "\nOpção inválida!";

                    }
                    while(op < 1 || op > 2);

                    if(op == 1)
                    {
                        Editar(p);

                    }
                }
                else
                {
                    system("cls");
                    cout << "\n\tEDITAR\n";
                }
            }
        }
        while(op == 1);
    }
}

//Função que busca um produto pelo código
//e exibe seus dados
void Buscar(Produto *p)
{

    int n; // "n" é o indice do produto

    cout << "\n\tBUSCAR\n";

    n = BuscarIndice(p);

    if(n > -1)
    {
        cout << "\nCódigo: " << p[n].cod
             << "\nNome: " << p[n].nome
             << "\nQuantidade: " << p[n].quant
             << "\nPreço: " << p[n].preco
             << "\n\n";

        system("PAUSE");
    }
}

//Função que remove um produto
void Remover(Produto *p)
{
    int n, op; // "n" é o indice do produto

    cout << "\n\tREMOVER\n";

    n = BuscarIndice(p);

    if(n > -1)
    {

        //Mostra as informações do produto antes de oferecer confirmação da remoção
        cout << "\nCódigo: " << p[n].cod
             << "\nNome: " << p[n].nome
             << "\nPreço: " <<  p[n].preco
             << "\nQuantidade: " <<  p[n].quant;

        //CONFIRMAÇÃO
        cout << "\n\nConfirme a remoção:"
             <<"\n1. CONFIRMAR"
             <<"\n2. CANCELAR"
             <<"\nOpção: ";
        cin >> op;

        if(op == 1)
        {
            //IRÁ ZERAR TODOS OS VALORES PARA O PRODUTO
            p[n].cod = 0;
            p[n].quant = 0;
            p[n].preco = 0;
            strcpy(p[n].nome, "");

            Ordenar(p);
        }
        else cout << "\nCancelado.";

    }
    else cout << "\nProduto não encontrado.";

}

//LISTAR TODOS OS PRODUTOS
void ListarTodos(Produto * p)
{

    cout << "\n\tPRODUTOS EM ESTOQUE:";

    for(int i = 0; i < totalProd; i++) //
    {
        cout << "\n\nCódigo do produto:\t" << p[i].cod
             << "\nNome do produto:\t" << p[i].nome
             << "\nQuantidade:\t" << p[i].quant
             << "\nPreço:\t" << p[i].preco;
    }
    cout << "\n";
    system("PAUSE");
}

// LISTAR PRODUTOS COM BAIXO ESTOQUE
void BaixoEstoque (Produto *p)
{

    for (int i=0; i < totalProd ;  i++)
    {
        if (p[i].quant < 10)
        {
            cout<<"\nO produto de codigo "<<p[i].cod<< " " << "nome "<< p[i].nome << "possui" << p[i].quant  << " produtos no estoque";
        }

        else
        {
            cout << "\nNão existem produtos com baixo estoque.";
        }

    }

    system("PAUSE");
}

//Valor total em estoque.
void ValorTotal(Produto *p)
{
    int soma = 0, produto = 0;

    //Valor total dos produtos no estoque
    for(int i=0; i < totalProd ; i++)
    {
        produto = p[i].quant * p[i].preco;
        soma = produto + soma;
    }

    cout<<"\n O valor total(preço) de produtos no estoque é: " << soma << "\n";
}

//Total de produtos no estoque
void TotalProdutos (Produto *p)
{

    int soma = 0;

    for(int i=0; i < totalProd ; i++)
    {

        soma += p[i].quant;
    }

    cout << "\n\tTOTAL EM ESTOQUE\n";
    cout<<"\n O total de produtos no estoque é: "<< soma;

    ValorTotal(p);

    system("PAUSE");

}


int Menu(){

    int op = 0;
    char aux[100];

    do{
        cout << "\n\t\tMENU"
             <<"\nEscola a opção: "
             <<"\n1 - Cadastrar"
             <<"\n2 - Editar/Alterar Produto"
             <<"\n3 - Buscar Produto"
             <<"\n4 - Remover Produto"
             <<"\n5 - Listar Todos os Produtos"
             <<"\n6 - Listar Todos os Produtos com Baixo Estoque"
             <<"\n7 - Total de Produtos e Valor Total"
             <<"\n8 - Limpar Tela"
             <<"\n0 - Sair"
             <<"\nOpção: ";
         cin >> aux;

        op = atoi(aux);
    }while(op < 0 || op > 8);


    return op;
}


//Tela inicial

void Inicial ()
{

    cout<<"\n"<<endl;

    cout<<"\n     -------  -------   -         --------  -------   -------            -------"
        <<"\n    /        /      /  / |     /     /     /      /  /      /  /        /"
        <<"\n   /        /      /  /  |    /     /     /      /  /      /  /        /"
        <<"\n  /        /      /  /   |   /     /     /______/  /      /  /        /----"
        <<"\n /        /      /  /    |  /     /     /   |     /      /  /        /"
        <<"\n/        /      /  /     | /     /     /    |    /      /  /        /"
        <<"\n-------  -------  /      |/     /     /     |    ------    -------  -------";
    cout<<"\n"<<endl;

    cout<<"\n\t\t\t   ----------  -------"
        <<"\n\t\t\t      /     / /"
        <<"\n\t\t\t     /     / /"
        <<"\n\t\t\t    /     / /---"
        <<"\n\t\t\t   /     / /"
        <<"\n\t\t\t  /     / /"
        <<"\n\t\t\t--------  -------";
    cout<<"\n"<<endl;

    cout<<"\n     -------  -------  ---------  ---------   ---------               -------"
        <<"\n    /        /            /      /        /  /        /  /        /  /"
        <<"\n   /        /            /      /        /  /        /  /        /  /"
        <<"\n  /---      -------     /      /        /  /        /  /        /  /----"
        <<"\n /                /    /      /        /  /  ___   /  /        /  /"
        <<"\n/                /    /      /        /  /  /   | /  /        /  /"
        <<"\n-------  -------     /       --------   --------|-   --------    -------";

    cout<<"\n"<<endl;

    system ("pause");

}



// ------------------------------------------------------------------
int main()
{
    //FUNDO TELA BRANCA
    system("color F0");

    //MENSAGEM TELA INICIAL
    Inicial();

    //ACENTUAÇÃO e CARACTERES EM PT-BR
    setlocale(LC_ALL, "Portuguese");

    //VARIÁVEIS
    int menu_op = 1;
    Produto estoque[TAM];  //VETOR DE PRODUTOS

    //OBS: PRODUTOS COM COD 0 'NÃO EXISTEM'

    //COMEÇO DO PROGRAMA
    while(menu_op != 0)
    {
        if (totalProd == 0)
        {
            Cadastrar(estoque, totalProd);
        }

        //INICIALIZAR O MENU
        menu_op = Menu();

        switch (menu_op)
        {
        case 1:
            Cadastrar(estoque, totalProd);
            break;

        case 2:
            Editar(estoque);
            break;

        case 3:
            Buscar(estoque);
            break;

        case 4:
            Remover(estoque);
            break;

        case 5:
            ListarTodos(estoque);
            break;

        case 6:
            BaixoEstoque(estoque);
            break;

        case 7:
            TotalProdutos(estoque);
            break;

        case 8:
            system("cls");
            break;

        case 0:
            cout << "\nObrigado por utilizar nosso software.\n";
            break;
        }
    }//Fim do while-programa

    system("pause");
}
