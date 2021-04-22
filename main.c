#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct DDMMAAAA *Date;
struct DDMMAAAA
{
    unsigned short int Day;
    unsigned short int Month;
    unsigned short int Year;
};

typedef struct SaleRegister *Sale;
struct SaleRegister
{
    unsigned int id;
    unsigned int quantity;
};

typedef struct SNode *Ptr_SNo;
struct SNode
{
    Ptr_SNo Ptr_Seg;
    Sale Ptr_Elem;
};

typedef struct Item *StockItem;
struct Item
{
    unsigned int id;
    char farmacyName[20];
    unsigned int lotNumber;
    unsigned int quantity;
    unsigned int recivedQtt;
    Date expirationDate;
    Ptr_SNo sales;
};

typedef struct Node *Ptr_No;
struct Node
{
    Ptr_No Ptr_Seg;
    StockItem Ptr_Elem;
};

// Prototype's available on Main
void ioPrintFullStock(Ptr_No *Ptr);
void ioAddStock(Ptr_No *list);
void ioEditStock(Ptr_No *list);
Ptr_No searchById(Ptr_No *list, unsigned int lotNumber);

void ioAddSale(Ptr_No *list);
void ioRemoveSale(Ptr_No *list);
void ioTotalStockAmount(Ptr_No *list);
void ioSearchById(Ptr_No *list);
void ioSearchByLotNumber(Ptr_No *list);
void ioAvailableStockByFarmacyName(Ptr_No *list);
void ioAvailableStockByDate(Ptr_No *list);
void ioImportFile(Ptr_No *list);

int main()
{
    short int op;
    Ptr_No list = NULL;

    while(op != 0)
    {
        printf("\n\n ***** MENU ******");
        printf("\n [ 01 ] Ver stocke existente");
        printf("\n [ 02 ] Inserir vacina do stock");
        printf("\n [ 03 ] Alterar registo de entrada");
        printf("\n [ 04 ] Declarar saida de stock");
        printf("\n [ 05 ] Remover saida de stock");
        printf("\n [ 06 ] Quantidade total de vacinas disponíveis");
        printf("\n [ 07 ] Pesquisar por Nº de receção");
        printf("\n [ 08 ] Pesquisar por Nº de Lote");
        printf("\n [ 09 ] Pesquisar vacinas disponiveis de farmaceutica");
        printf("\n [ 10 ] Pesquisar vacinas disponiveis ate a uma data");
        printf("\n [ 11 ] *Ver stock mensal da vacinas");
        printf("\n [ 12 ] *Importar dados de ficheiro csv");
        printf("\n [ 00 ] Sair do programa");
        printf("\n\n >>>> Escolher uma opcao (0,1,2,3,..): ");
        scanf("%hd", &op);

        switch (op) {
            case 1:
                printf("\n <<< Conteudo da Lista >>>");
                ioPrintFullStock(&list);
                break;
            case 2:
                printf("\n <<< Inserir Vacina >>>");
                ioAddStock(&list);
                break;
            case 3:
                printf("\n <<< Editar item em stock >>>");
                ioEditStock(&list);
                break;
            case 4:
                printf("\n <<< Adicionar venda >>>");
                ioAddSale(&list);
                break;
            case 5:
                printf("\n <<< Remover venda >>>");
                ioRemoveSale(&list);
                break;
            case 6:
                printf("\n <<< Total de vacinas disponíveis >>>");
                ioTotalStockAmount(&list);
                break;
            case 7:
                printf("\n <<< Pesquisa por nº de receção >>>");
                ioSearchById(&list);
                break;
            case 8:
                printf("\n <<< Pesquisa por nº de lote >>>");
                ioSearchByLotNumber(&list);
                break;
            case 9:
                printf("\n <<< Pesquisar vacinas disponiveis de farmaceutica >>>");
                ioAvailableStockByFarmacyName(&list);
                break;
            case 10:
                printf("\n <<< Pesquisar vacinas disponiveis ate a uma data >>>");
                ioAvailableStockByDate(&list);
                break;
            case 11:
                break;
            case 12:
                printf("\n <<< Importar lista de ficheiro >>>");
                ioImportFile(&list);
                break;
            case 0:
                break;
            default:
                printf("\n opção não valida \n");
                break;
        }
    }

    free(list);

    printf("\n\n ##### BEIJINHO NO OMBRO PRAS INIMIGAS ##### \n\n");

    return 0;
}

///////////////////////////////////////////////////////////////////

void ioPrintStockNode(Ptr_No *Ptr)
{
    Ptr_No currentNode = *Ptr;

    printf(
            "\n\tNº de recepção: %u \n\tNome da farmacêutica: %s \n\tNº do lote: %u\n\tQuantidade recebida: %u"
            "\n\tQuantidade disponivel: %u\n\tData de validade: %hu/%hu/%hu\n",
            currentNode->Ptr_Elem->id, currentNode->Ptr_Elem->farmacyName, currentNode->Ptr_Elem->lotNumber,
            currentNode->Ptr_Elem->recivedQtt, currentNode->Ptr_Elem->quantity,
            currentNode->Ptr_Elem->expirationDate->Day, currentNode->Ptr_Elem->expirationDate->Month, currentNode->Ptr_Elem->expirationDate->Year
    );
}

void ioPrintFullSales(Ptr_No item) {
    Ptr_SNo currentNode = item->Ptr_Elem->sales;

    if (currentNode != NULL) {
        printf("\n\tVendas (Nº de requisição | Quantidade)");
    }

    while (currentNode != NULL)
    {
        printf("\n\t\t\t Nº %d | %d vacinas vendidas", currentNode->Ptr_Elem->id, currentNode->Ptr_Elem->quantity);
        currentNode = currentNode->Ptr_Seg;
    }
}

// Ver conteúdo de uma Lista
void ioPrintFullStock(Ptr_No *Ptr)
{
    Ptr_No currentNode = *Ptr;

    if (currentNode == NULL) {
        printf("\nLista vazia"); return;
    }

    while (currentNode != NULL)
    {
        ioPrintStockNode(&currentNode);
        ioPrintFullSales(currentNode);
        currentNode = currentNode->Ptr_Seg;

        if(currentNode != NULL) {
            printf("\n -----------------------------------\n");
        }
    }
}

Ptr_No createNewNode(Ptr_No *list) {
    Ptr_No newNode;

    // Alocate dynamic space to the new objects
    if ((newNode =(Ptr_No) malloc (sizeof(struct Node))) == NULL ) return NULL;

    if ((newNode->Ptr_Elem=(StockItem) malloc (sizeof(struct Item))) == NULL ) {
        free(newNode);
        return NULL;
    }

    if ((newNode->Ptr_Elem->expirationDate=(Date) malloc (sizeof(struct DDMMAAAA))) == NULL ) {
        free(newNode->Ptr_Elem);
        free(newNode);
        return NULL;
    }

    // Fill data
    printf("\nNº de recepção: ");
    scanf("%u", &newNode->Ptr_Elem->id);

    if(searchById(list, newNode->Ptr_Elem->id) != NULL) {
        return NULL;
    }

    printf("Nome da farmacêutica: ");
    scanf("%20s", newNode->Ptr_Elem->farmacyName);
    printf("Nº do lote: ");
    scanf("%u", &newNode->Ptr_Elem->lotNumber);
    printf("Quantidade recebida: ");
    scanf("%u", &newNode->Ptr_Elem->recivedQtt);
    newNode->Ptr_Elem->quantity = newNode->Ptr_Elem->recivedQtt;
    printf("Data de validade \n DIA: ");
    scanf("%hu", &newNode->Ptr_Elem->expirationDate->Day);
    printf(" MES: ");
    scanf("%hu", &newNode->Ptr_Elem->expirationDate->Month);
    printf(" ANO: ");
    scanf("%hu", &newNode->Ptr_Elem->expirationDate->Year);

    newNode->Ptr_Elem->sales = NULL;
    newNode->Ptr_Seg = NULL;

    return newNode;
}

Ptr_SNo newSale(unsigned int stock) {
    Ptr_SNo newNode;

    // Alocate dynamic space to the new objects
    if ((newNode =(Ptr_SNo) malloc (sizeof(struct SNode))) == NULL ) return NULL;

    if ((newNode->Ptr_Elem = (Sale) malloc (sizeof(struct SaleRegister))) == NULL ) {
        free(newNode);
        return NULL;
    }

    printf("Nº de requisição: ");
    scanf("%u", &newNode->Ptr_Elem->id);
    printf("Quantidade (max: %d): ", stock);
    scanf("%u", &newNode->Ptr_Elem->quantity);

    newNode->Ptr_Seg = NULL;

    if(newNode->Ptr_Elem->quantity > stock) {
        return NULL;
    }

    return newNode;
}

void ioAddSale(Ptr_No *list) {
    unsigned int index;
    printf("\nNº de recepção: ");
    scanf("%u", &index);

    Ptr_No item;
    if((item = searchById(list, index)) == NULL) {
        printf("ERRO: Nº de recepção não encontrado.\n");
        return;
    }

    Ptr_SNo newNode = newSale(item->Ptr_Elem->quantity);
    if(newNode != NULL) {
        item->Ptr_Elem->quantity -= newNode->Ptr_Elem->quantity;
        newNode->Ptr_Seg = item->Ptr_Elem->sales;
        item->Ptr_Elem->sales = newNode;
    }else {
        printf("\nERRO: Respeite o stock limitado.\n");
        return;
    }
}

unsigned int removeSaleNodeById(Ptr_SNo *Ptr, int valor)
{
    // Declaração dos ponteiros
    Ptr_SNo NoAnterior = *Ptr;
    Ptr_SNo NoActual = *Ptr;
    Ptr_SNo NoRemover = NULL;

    // Verificar se a lista está vazia
    if (NoActual == NULL) return 0;

    // Elemento no início da lista
    if (valor == NoActual->Ptr_Elem->id)
    {
        unsigned int qtt = NoActual->Ptr_Elem->quantity;
        NoRemover=NoActual;
        *Ptr = (*Ptr)->Ptr_Seg;

        free(NoRemover->Ptr_Elem);
        free(NoRemover);
        NoRemover = NULL;
        return qtt;
    }
    else
    {
        NoActual=NoActual->Ptr_Seg;
    }

    // Procurar o elemento na lista
    while (NoActual != NULL)
    {
        if(NoActual->Ptr_Elem->id == valor)
        {
            unsigned int qtt = NoActual->Ptr_Elem->quantity;
            NoAnterior->Ptr_Seg = NoActual->Ptr_Seg;
            NoRemover = NoActual;

            free(NoRemover->Ptr_Elem);
            free(NoRemover);
            NoRemover = NULL;
            return qtt;
        }
        else
        {
            NoAnterior = NoActual;
            NoActual = NoActual->Ptr_Seg;
        }
    }

    return 0;
}

void ioRemoveSale(Ptr_No *list) {
    unsigned int item_id;
    unsigned int sale_id;
    printf("\nNº de recepção: ");
    scanf("%u", &item_id);
    printf("\nNº de requisição: ");
    scanf("%u", &sale_id);

    Ptr_No item;
    if((item = searchById(list, item_id)) == NULL) {
        printf("ERRO: Nº de recepção não encontrado.\n");
        return;
    }

    unsigned int removedQuantity = removeSaleNodeById(&item->Ptr_Elem->sales, sale_id);
    item->Ptr_Elem->quantity += removedQuantity;
}

void ioEditNode(Ptr_No *node) {

    Ptr_No newNode;
    Ptr_No currentNode = *node;

    // Alocate dynamic space to the new objects
    if ((newNode =(Ptr_No) malloc (sizeof(struct Node))) == NULL ) return;

    if ((newNode->Ptr_Elem=(StockItem) malloc (sizeof(struct Item))) == NULL ) {
        free(newNode);
        return;
    }

    if ((newNode->Ptr_Elem->expirationDate=(Date) malloc (sizeof(struct DDMMAAAA))) == NULL ) {
        free(newNode->Ptr_Elem);
        free(newNode);
        return;
    }

    unsigned int recivedQttBeforeChanges = currentNode->Ptr_Elem->recivedQtt;

    // Fill data
    printf("Nome da farmacêutica (%s): ", currentNode->Ptr_Elem->farmacyName);
    scanf("%20s", currentNode->Ptr_Elem->farmacyName);
    printf("Nº do lote (%u): ", currentNode->Ptr_Elem->lotNumber);
    scanf("%u", &currentNode->Ptr_Elem->lotNumber);
    printf("Quantidade recebida (%u): ", currentNode->Ptr_Elem->recivedQtt);
    scanf("%u", &currentNode->Ptr_Elem->recivedQtt);
    printf("Data de validade (%hu/%hu/%hu)\n DIA: ",
           currentNode->Ptr_Elem->expirationDate->Day,
           currentNode->Ptr_Elem->expirationDate->Month,
           currentNode->Ptr_Elem->expirationDate->Year);
    scanf("%hu", &currentNode->Ptr_Elem->expirationDate->Day);
    printf(" MES: ");
    scanf("%hu", &currentNode->Ptr_Elem->expirationDate->Month);
    printf(" ANO: ");
    scanf("%hu", &currentNode->Ptr_Elem->expirationDate->Year);

    if(recivedQttBeforeChanges != currentNode->Ptr_Elem->recivedQtt) {
        int change = (int) currentNode->Ptr_Elem->recivedQtt - (int) recivedQttBeforeChanges;
        if(currentNode->Ptr_Elem->quantity + change < 0) {
            currentNode->Ptr_Elem->quantity = 0;
        }else {
            currentNode->Ptr_Elem->quantity = currentNode->Ptr_Elem->quantity + change;
        }
    }
}

// Inserir Elemento numa Lista pelo utilizador
void ioAddStock(Ptr_No *list)
{
    Ptr_No newNode = createNewNode(list);

    if(newNode == NULL) {
        printf("\nERRO: Item já existe na lista.\n");
        return;
    }

    // Validação de dados por parte do user
    ioPrintStockNode(&newNode);
    char validator = 0;
    printf("\nDeseja guardar estes dados? (s - Sim; n - Não)");
    scanf(" %c", &validator);

    if (validator == 's') {
        newNode->Ptr_Seg = *list;
        *list = newNode;
    } else {
        free(newNode);
    }
}

void ioEditStock(Ptr_No *list)
{
    Ptr_No currentNode = *list;
    unsigned short int index;

    printf("\nNº de recepção: ");
    scanf("%hu", &index);

    currentNode = searchById(list, index);

    if(currentNode != NULL) {
        ioEditNode(&currentNode);
    }else {
        printf("\nNº de recepção %hu não foi encontrado!", index);
    }
}

Ptr_No searchById(Ptr_No *list, unsigned int id) {
    Ptr_No currentNode = *list;

    // check for empty list
    if (currentNode == NULL) {
        return NULL;
    }

    // check if id is the head of the list
    if (id == currentNode->Ptr_Elem->id)
    {
        return currentNode;
    } else {
        currentNode = currentNode->Ptr_Seg;
    }

    // Seach on list
    while (currentNode != NULL)
    {
        if(currentNode->Ptr_Elem->id == id)
        {
            return currentNode;
        } else {
            currentNode = currentNode->Ptr_Seg;
        }
    }

    return NULL;
}

Ptr_No searchByLotNumber(Ptr_No *list, unsigned int lotNumber) {
    Ptr_No currentNode = *list;

    // check for empty list
    if (currentNode == NULL) {
        return NULL;
    }

    // check if lotNumber is the head of the list
    if (lotNumber == currentNode->Ptr_Elem->lotNumber)
    {
        return currentNode;
    } else {
        currentNode = currentNode->Ptr_Seg;
    }

    // Seach on list
    while (currentNode != NULL)
    {
        if(currentNode->Ptr_Elem->lotNumber == lotNumber)
        {
            return currentNode;
        } else {
            currentNode = currentNode->Ptr_Seg;
        }
    }

    return NULL;
}

void ioTotalStockAmount(Ptr_No *list) {
    Ptr_No currentNode = *list;
    unsigned int total = 0;

    while (currentNode != NULL)
    {
        total += currentNode->Ptr_Elem->quantity;
        currentNode = currentNode->Ptr_Seg;
    }

    printf("\n\nExistem %u vacinas disponiveis\n", total);
}

void ioSearchById(Ptr_No *list) {
    unsigned int index;

    printf("\nNº de recepção: ");
    scanf("%u", &index);

    Ptr_No currentNode = searchById(list, index);

    ioPrintStockNode(&currentNode);
}

void ioSearchByLotNumber(Ptr_No *list) {
    Ptr_No currentNode = *list;
    unsigned int index;

    printf("\nNº de lote: ");
    scanf("%u", &index);

    if (currentNode == NULL) {
        return;
    }

    // Seach on list
    while (currentNode != NULL) {
        if(currentNode->Ptr_Elem->lotNumber == index) {
            ioPrintStockNode(&currentNode);
        }

        currentNode = currentNode->Ptr_Seg;
    }
}

void ioAvailableStockByFarmacyName(Ptr_No *list) {
    Ptr_No currentNode = *list;
    unsigned char name[20];

    printf("\nNome da farmaceutica: ");
    scanf("%20s", name);

    if (currentNode == NULL) {
        return;
    }

    // Seach on list
    while (currentNode != NULL) {
        if(strcmp(currentNode->Ptr_Elem->farmacyName, name) == 0) {
            ioPrintStockNode(&currentNode);
        }

        currentNode = currentNode->Ptr_Seg;
    }
}

int compare_dates (Date d1, Date d2) {
    if (d1->Year < d2->Year) {
        return -1;
    } else if (d1->Year > d2->Year) {
        return 1;
    }

    if (d1->Year == d2->Year) {
        if (d1->Month < d2->Month)
            return -1;
        else if (d1->Month > d2->Month)
            return 1;
        else if (d1->Day < d2->Day)
            return -1;
        else if(d1->Day > d2->Day)
            return 1;
        else
            return 0;
    }
}

void ioAvailableStockByDate(Ptr_No *list) {
    Ptr_No currentNode = *list;
    Date searchDate;

    printf("Data de validade \n DIA: ");
    scanf("%hu", &searchDate->Day);
    printf(" MES: ");
    scanf("%hu", &searchDate->Month);
    printf(" ANO: ");
    scanf("%hu", &searchDate->Year);

    if (currentNode == NULL) {
        return;
    }

    // Seach on list
    while (currentNode != NULL) {
        if(compare_dates(currentNode->Ptr_Elem->expirationDate, searchDate) <= 0) {
            ioPrintStockNode(&currentNode);
        }
        currentNode = currentNode->Ptr_Seg;
    }
}

const char* getfield(char* line, int num)
{
    const char* tok;
    for (tok = strtok(line, ";");
         tok && *tok;
         tok = strtok(NULL, ";\n"))
    {
        if (!--num)
            return tok;
    }
    return NULL;
}

void importListFromFile(char filename[40], Ptr_No *list){
    FILE* stream = fopen(filename, "r");

    char line[1024];
    while (fgets(line, 1024, stream))
    {
        char* tmp = strdup(line);

        Ptr_No newNode;

        // Alocate dynamic space to the new objects
        if ((newNode =(Ptr_No) malloc (sizeof(struct Node))) == NULL ) return;

        if ((newNode->Ptr_Elem=(StockItem) malloc (sizeof(struct Item))) == NULL ) {
            free(newNode);
            return;
        }

        if ((newNode->Ptr_Elem->expirationDate=(Date) malloc (sizeof(struct DDMMAAAA))) == NULL ) {
            free(newNode->Ptr_Elem);
            free(newNode);
            return;
        }

        // Fill data
        newNode->Ptr_Elem->id = atoi(getfield(tmp, 1));

        if(searchById(list, newNode->Ptr_Elem->id) == NULL) {
            //strncpy(newNode->Ptr_Elem->farmacyName, getfield(tmp, 2), sizeof(newNode->Ptr_Elem->farmacyName) );
            newNode->Ptr_Elem->lotNumber = atoi(getfield(tmp, 3));
            newNode->Ptr_Elem->recivedQtt = atoi(getfield(tmp, 4));
            newNode->Ptr_Elem->quantity = atoi(getfield(tmp, 5));
            newNode->Ptr_Elem->expirationDate->Day = atoi(getfield(tmp, 6));
            newNode->Ptr_Elem->expirationDate->Month = atoi(getfield(tmp, 7));
            newNode->Ptr_Elem->expirationDate->Year = atoi(getfield(tmp, 8));
            newNode->Ptr_Elem->sales = NULL;
            newNode->Ptr_Seg = NULL;


            newNode->Ptr_Seg = *list;
            *list = newNode;
        }
        free(tmp);
    }
}

void ioImportFile(Ptr_No *list) {
    unsigned char fileName[40];

    printf("\nCaminho para o ficheiro: ");
    scanf("%40s", fileName);

    importListFromFile(fileName, list);
}