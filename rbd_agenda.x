struct contato {
    char nome[50];
    char cpf[14];
    char telefone[15];
    char endereco[50];
};

struct agenda{
	contato contatos[100];
	int tam;
};

program RBDPROG {
    version RDBVERS {
        void INICIALIZAR(void) = 1;
        int INSERE(contato) = 2;
        int REMOVE(string) = 3;
        contato BUSCA(string) = 4;
        agenda LISTA(void) = 5;
    } = 1;
} = 0x30090949;
