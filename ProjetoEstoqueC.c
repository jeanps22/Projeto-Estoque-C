#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
	int cod;
    char nome[50];
    float qtd;
    float preco;
}produto;

produto *produtos;

void cadastro(produto *produtos, int *i,int *cap);
void salvarArquivo(produto *produtos, int i);
produto *abrirArquivo (int *i, int *cap);
void listartudo(produto *produtos, int i);
void Pesquisar(produto *produtos, int *i);
void Entrada(produto *produtos, int *i);
void Saida(produto *produtos, int *i);
void Excluir(produto *produtos, int *i);
void Alterar(produto *produtos, int *i);
void Nome(produto *produtos, int *i);
void Codigo(produto *produtos, int *i);

int cmpfunc (const void * a, const void * b) {
    produto *c1 = (produto *)a;
    produto *c2 = (produto *)b;
    int i=0;
    while (tolower(c1 -> nome[i])==tolower(c2->nome[i]))
           i++;
    return ( tolower (c1-> nome[i])- tolower(c2->nome[i]) );
}
int cmpfunc2 (const void * a, const void * b) {
    produto *c1 = (produto *)a;
    produto *c2 = (produto *)b;
    return (c1-> cod-c2->cod );
}


void flush_in()
{
   int ch;
   while( (ch = fgetc(stdin)) != EOF && ch != '\n' ){}
}

int main (void)
{
	int entrada,i=0,j=0;
	int cap;

 produtos = abrirArquivo(&i, &cap);

do{
	printf("***********************************************");
	printf("\n                   ESTOQUE");
	printf("\n***********************************************\n");
	printf("\n\nEscolha uma opcao: \n");
    printf(" 1. Cadastrar produtos\n 2. Entrada de Produtos\n 3. Saida de Produtos\n 4. Listar todos os produtos por codigo\n 5. Listar todos os produtos por nome\n 6. Listar produtos\n 7. Alterar Produtos\n 8. Pesquisar Produtos\n 9. Excluir Produtos\n 10. Sair\n\n");
    printf("\nEscolha: ");
	scanf("%i", &entrada);
    system("cls");
    
 switch(entrada){
 	case 1:
 	cadastro(produtos, &i,&cap);
 	break;
 	
 	case 2:
 	Entrada(produtos,&i);
 	break;
 	
 	case 3:
 	Saida(produtos,&i);
 	break;
 	
 	case 4:
 	Codigo(produtos, &i);
 	break;
 	
 	case 5:
 	Nome(produtos, &i);
 	break;
 	
 	case 6:
 	listartudo(produtos, i);
 	break;
 	
 	case 7:
 	Alterar(produtos, &i);	
 	break;
 	
 	case 8:
    Pesquisar(produtos, &i);
 	break;
 	
 	case 9:
 	Excluir(produtos,&i);	
 	break;
 }    
    
}while(entrada!=10);
  salvarArquivo(produtos, i);
	free(produtos);
}

//Funções
void cadastro (produto *produtos, int *i,int *cap){
	int g=0,var=0;
	if(*i==0)
		produtos[*i].cod=0;
	else{
	for(g=0;g<*i;g++)
		{
			if(produtos[g].cod>=var){
				var++;
				g=0;
			}	
		}
		produtos[*i].cod=var;	
	}
		   if(*i==*cap){
	      *cap = *cap * 2;
          produtos = (produto*)realloc(produtos, sizeof(produto) * (*cap));
      }
	flush_in();
	printf("Digite o Nome do Produto: \n");
	gets(produtos[*i].nome);
	printf("Digite a quantidade do Produto: \n");
	scanf("%f", &produtos[*i].qtd);
	printf("Digite o Preco do Produto: \n");
	scanf("%f", &produtos[*i].preco);
	printf("\n\nProduto Cadastrado! \n\nCodigo:%i \nNome:%s \nQuantidade:%.2f \nPreco:%.2f\n\n",produtos[*i].cod,produtos[*i].nome,produtos[*i].qtd,produtos[*i].preco); 
	(*i) ++;
}

void salvarArquivo(produto *produtos, int i){
    FILE *fp = fopen("produtos.dat","w");
    fwrite(&i, sizeof(int), 1, fp);
    if(i>0){
    	fwrite(produtos, sizeof(produto), i, fp);
	}
    fclose(fp);	
}
produto * abrirArquivo (int *i, int *cap){
produto *produtos;  
  FILE *fp = fopen("produtos.dat","r");
  if(fp==NULL){
    *i   = 0;   
    *cap = 20;
    produtos = (produto *)malloc(sizeof(produto)* (*cap));
  }
  else{
    fread(i, sizeof(int), 1, fp);
    *cap = (*i) * 2; 
    produtos = (produto *)malloc(sizeof(produto)* (*cap));
    fread(produtos, sizeof(produto), *i, fp);
    fclose(fp);
  }
  return produtos;	
}

void listartudo(produto *produtos,int i){
	int g;
	printf("*****Lista de Produtos*****");
	for (g=0;g<i;g++){
		printf("\nCodigo: %i: ---- %s",produtos[g].cod,produtos[g].nome);
	}
		printf("\n\n");
		system("pause");
		system("cls");
}

void Pesquisar(produto *produtos, int *i){
	char busca[50];
	int g;
	int achou=0;
	printf("Qual produto que deseja buscar?\n");
	flush_in();
	gets(busca);
	for(g=0;g<*i;g++){
		if(strcmp(produtos[g].nome,busca)==0){
			achou=1;
			printf("\n*****Produto encontrado!*****\n\nCodigo:%i\nProduto:%s\nQuantidade:%.2f\nPreco: %.2f\n",produtos[g].cod,produtos[g].nome, produtos[g].qtd, produtos[g].preco);
			break;	
		}
	}
		if(achou==0) {
			printf("Produto nao encontrado");	
		}
	}
void Entrada(produto *produtos, int *i){
	char busca[50];
	int g;
	int achou=0;
	float novo=0.00;
	printf("Qual produto que deseja buscar?\n");
	flush_in();
	gets(busca);
	for(g=0;g<*i;g++){
		if(strcmp(produtos[g].nome,busca)==0){
			achou=1;
			printf("\nQuantidade Atual do produto:%.2f\n",produtos[g].qtd);
			printf("\nQuantas quantidades deseja aumentar: \n");
			scanf("%f",&novo);
			produtos[g].qtd=produtos[g].qtd+novo;
			printf("\n*****Quantidade Alterada!*****\n\nCodigo:%i\nProduto:%s\nQuantidade:%.2f\nPreco: %.2f\n",produtos[g].cod,produtos[g].nome, produtos[g].qtd, produtos[g].preco);
			break;	
		}
	}
		if(achou==0) {
			printf("Produto nao encontrado");	
		}
	}	
void Saida(produto *produtos, int *i){
	char busca[50];
	int g;
	int achou=0;
	float novo=0.00;
	printf("Qual produto que deseja buscar?\n");
	flush_in();
	gets(busca);
	for(g=0;g<*i;g++){
		if(strcmp(produtos[g].nome,busca)==0){
			achou=1;
			printf("\nQuantidade Atual do produto:%.2f\n",produtos[g].qtd);
			printf("\nQuantas quantidades deseja diminuir: \n");
			scanf("%f",&novo);
			do{
			if((produtos[g].qtd-novo)<0){
			printf("Estoque nao pode ficar negativo, digite outro valor!:  ");	
			scanf("%f",&novo);
			}
			}while ((produtos[g].qtd-novo)<0);
			produtos[g].qtd=produtos[g].qtd-novo;	
			printf("\n*****Quantidade Alterada!*****\n\nCodigo:%i\nProduto:%s\nQuantidade:%.2f\nPreco: %.2f\n",produtos[g].cod,produtos[g].nome, produtos[g].qtd, produtos[g].preco);
			break;	
		}
	}
		if(achou==0) {
			printf("Produto nao encontrado");	
		}
	}
void Excluir(produto *produtos, int *i){
	char busca[50];
	int g,j,var;
	int achou=0;
	printf("Qual produto que deseja excluir?\n");
	flush_in();
	gets(busca);
	for(g=0;g<*i;g++){
		if(strcmp(produtos[g].nome,busca)==0){
			achou=1;
			printf("\n*****Produto Excluido!*****");
            strcpy(produtos[g].nome,produtos[*i-1].nome);
            produtos[g].cod=produtos[*i-1].cod;
			produtos[g].qtd=produtos[*i-1].qtd;
			produtos[g].preco=produtos[*i-1].preco;
		(*i)--;
	}
}
	if(achou==0) {
	printf("Produto nao encontrado");	
	}
}
void Alterar(produto *produtos, int *i){
	char busca[50];
	int g,achou=0,escolha=0;
	printf("Qual produto que deseja Alterar?\n");
	flush_in();
	gets(busca);
	for(g=0;g<*i;g++){
		if(strcmp(produtos[g].nome,busca)==0){
			achou=1;
			printf("\nO que voce quer alterar? ");
                printf("\n 1-Nome \n 2-Quantidade \n 3-Preco \n");
                scanf("%i", &escolha);
                  switch(escolha){
                  case 1:
                  flush_in();
                  printf("\nDigite o nome: \n");
                  gets(produtos[g].nome);
                  break;

                  case 2:
                    printf("\nDigite o Quantidade: \n");
                    scanf("%f",produtos[g].qtd);
                    break;

                  case 3:
                    printf("\nDigite o Preco: \n");
					scanf("%f",produtos[g].preco);
	                break;
                  }
            }
			printf("\n*****Produto Alterado!*****\n\nCodigo:%i\nProduto:%s\nQuantidade:%.2f\nPreco: %.2f\n",produtos[g].cod,produtos[g].nome, produtos[g].qtd, produtos[g].preco);
			break;	
		}
		if(achou==0) {
			printf("Produto nao encontrado");	
		}
}
void Nome(produto *produtos, int *i){
	qsort(produtos,*i,sizeof(produto),cmpfunc);
	int g;
	printf("*****Lista de Produtos*****");
	for (g=0;g<*i;g++){
		printf("\nCodigo: %i: ---- %s",produtos[g].cod,produtos[g].nome);
	}
		printf("\n\n");
		system("pause");
		system("cls");
}
void Codigo(produto *produtos, int *i){
	qsort(produtos,*i,sizeof(produto),cmpfunc2);
	int g;
	printf("*****Lista de Produtos*****");
	for (g=0;g<*i;g++){
		printf("\nCodigo: %i: ---- %s",produtos[g].cod,produtos[g].nome);
	}
		printf("\n\n");
		system("pause");
		system("cls");
}

