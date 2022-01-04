void inputProcessing();

/**
 * @brief Retorna se a leitura da string deve ou não ser finalizada
 * 
 * @param numSeparators número de separadores
 * @param separatorArray array com todos finalizadores
 * @param c caractere lido
 * @return int 1 para leitura finalizada, caso contrário, 0
 */
int stringEnd(int numSeparators, char separatorArray[], char c);

/**
 * @brief Função para leitura de strings
 * 
 * @return char* string
 */
char* readString();


/**
 * @brief Função mais completa para leitura de strings
 * 
 * @param num número de separadores que serão passados
 * @param ... separadores: EOF, quebra de linha etc...
 * @return char* string
 */
char* readString2(int num, ...);
