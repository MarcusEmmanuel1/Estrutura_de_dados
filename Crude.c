#include<stdio.h>
#include<stdlib.h>
typedef struct no{
    int chave;
    char *nome;
    char *especie;
    char *sexo;
    //Varia de especie, bovinos produzem leite, suinos para abate, galinhas pondo ovos
    char *estado;
    float peso;

    
    //dados dependem da aplicacao
    struct no * dir;
    struct no * esq;
}NO;
NO *raiz = NULL;

/////////////////////////////////////////////Funções principais da ABB(3)////////////////////////////////////////////////////////////
NO * busca_arvore(int x, NO *pt){
    if(pt == NULL){ //arv. vazia
        return NULL;
    }else if(x == pt->chave){ //encontrado
        return pt;
    }else if(x < pt->chave){
        //esq! :D
        if(pt->esq == NULL){
            return pt;
        }else{
            return busca_arvore(x, pt->esq);
        }
    }else{
        //dir
        if(pt->dir == NULL){
            return pt;
        }else{
            return busca_arvore(x, pt->dir);
        }
    }
}

void insercao_arvore(int x){
    NO * pt = busca_arvore(x, raiz);
    if(pt != NULL){ //arvore nao ta vazia
        if(pt->chave == x){
            printf("Chave duplicada!\n");
        }else{
            NO *pt1 = malloc(sizeof(NO));
            pt1->chave = x;
            pt1->esq = NULL;
            pt1->dir = NULL;
            if(x <pt->chave){
                pt->esq = pt1;
            }else{
                pt->dir = pt1;
            }
        }
    }else{//arvore vazia
        NO *pt1 = malloc(sizeof(NO));
        pt1->chave = x;
        pt1->esq = NULL;
        pt1->dir = NULL;
        raiz = pt1;
        
    }
}

void pre(NO *pt){
if(pt!= NULL){
    printf("%d ", pt->chave);
    if(pt->esq != NULL){
        pre(pt->esq);
    }
    if(pt->dir != NULL){
        pre(pt->dir);
    }
}
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////// Funções do CRUD//////////////////////////////////////////////
void read(int chave){
NO * temp = busca_arvore(chave, raiz);
    if(temp == NULL ){
    printf("Chave nao localizada na Arvore\n\n");
    }
    else{
    printf("Identificador:%d\nNome:%s\nTipo:%s\nPeso:%2.fKG\nSexo:%s\nEstado:%s\n\n" ,temp->chave,temp->nome,temp->especie,temp->peso,temp->sexo,temp->estado);
    }
}

void create(int chave){
    insercao_arvore(chave);
    NO * temp = busca_arvore(chave, raiz);
    
    printf("Digite a especie do animal{bovino, oviparo, suino}.\n");
   temp->especie= malloc(sizeof(char) * 20);
    scanf("%s", temp->especie);
    
    printf("Digite o sexo do animal\n");
    temp->sexo= malloc(sizeof(char) * 20);
    scanf("%s", temp->sexo);

     printf("Digite o estado do animal {Prenha,Produzindo leite,abate, Pondo, Reprodutor}\n");
    temp->estado=malloc(sizeof(char) * 20);
    scanf("%s", temp->estado);
     
     printf("Digite o nome do animal\n");
    temp->nome= malloc(sizeof(char) * 20);
    scanf("%s", temp->nome);
    
     printf("Digite o peso do animal\n");
     scanf("%f", &temp->peso);
}

void update(int chave){
    if(raiz != NULL){
    NO * temp = busca_arvore(chave, raiz);
    printf("Atualize a especia{bovino, oviparo, suino}.\n");
    scanf("%s", temp->especie);
    
    printf("Atualize o sexo do animal\n");
    scanf("%s", temp->sexo);

     printf("Atualize o estado{Prenha,Produzindo leite,abate, Pondo, Reprodutor}\n");
    scanf("%s", temp->estado);
     
     printf("Atualize o nome\n");
    scanf("%s", temp->nome);
    
     printf("Atualize o peso\n");
     scanf("%f", &temp->peso);
     }
     else{
        printf("Nao existem indentificadoes para atualizar\n\n");
     }
}

NO * delete(int chave, NO * pt){
    if(pt == NULL){
        printf ("Não ha dados a serem removidos");
        return NULL;
    }
    else if(pt->chave > chave){
        pt->esq= delete(chave,pt->esq );
        }
    else if(pt->chave < chave){
        pt->dir= delete(chave, pt->dir);
        }
    else{
        //No sem filho
        if(pt->esq == NULL && pt->dir == NULL){
            free(pt);
            pt=NULL;
        }
        //So um filho
        //Filho a direita
        else if(pt->esq == NULL){
        NO * t = pt;
        pt = pt->dir;
        free(t);
        }
        //Filho a esquerda
        else if(pt->dir == NULL){
            NO * t= pt;
            pt = pt->esq;
            free(t);
        }
        //No tem dois filho
        
        else{
        NO * f = pt->esq;
        
        while(f->dir != NULL){
            f = f->dir;
        }
        pt->chave = f->chave;
        f->chave = chave;
        pt->esq = delete(chave, pt->esq);
        }
}
return pt;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main(){
    int i,c;
    while(1){
    printf("Escolha oque deseja realizar:\n[0]Sair\n[1]Read\n[2]Create\n[3]Update\n[4]Delete\n");
    scanf("%d", &i);
        switch (i){
    //Sair do crude
    case 0:
    printf("CRUD finalizado");
    return 0;
        break;
    //Read
    case 1:
    printf("Lista de identificadores\n");
    printf("{");
    pre(raiz);
    printf("}\n");
    printf("Digite o identificador do animal.\n");
    scanf("%d", &c);
    read(c);
        break;
    //Create
    case 2:
    printf("Digite o numero que representa o animal.\n");
    scanf("%d", &c);
    create(c);
    printf("Criado com sucesso!\n\n");
        break;
    //Update
    case 3:
    printf("Lista de identificadores\n");
    printf("{");
    pre(raiz);
    printf("}\n");
    printf("Digite o identificador do animal a ter os dados atualizados\n\n");
    scanf("%d", &c);
    update(c);
        break;
    //Delete
   case 4:
    printf("Lista de identificadores\n");
    printf("{");
    pre(raiz);
    printf("}\n");
    printf("Digite o identificador que deseja apagar.\n");
    scanf("%d", &c);
    delete(c,raiz);
    printf("Deletado com suceso!\n\n");
    break;
    
    default:
        break;
        }
    }
}
