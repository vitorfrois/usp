import pandas as pd
import os
from container import *

#define algumas variaveis globalmente para facilitar o retorno
turmaA = pd.read_csv("ListadeApoioaoDocente-SSC01032022101.csv", names=['nusp', 'nome'])
turmaB = pd.read_csv("ListadeApoioaoDocente-SSC01032022102.csv", names=['nusp', 'nome'])

#os containers sao objetos que facilitam a leitura e armazenamento dos dados
gruposTurmaA = Container("Grupos Turma A: ")
gruposTurmaB = Container("Grupos Turma B: ")
alunosSemGrupo = Container(
    "Alunos sem grupo: ", 
    turmaA['nome'].to_list() + turmaB['nome'].to_list())
grupoDuasTurmas = Container("Grupos com alunos das duas turmas: ")
diferenteQuatro = Container("Grupos com menos de 4 alunos: ")
arquivosErro = Container("Arquivos com erro: ")
grupoAlunoInexistente = Container("Grupos com alunos inexistentes: ")

dataFiles = os.listdir('grupos')

#carrega os arquivos e faz sua leitura
def carregarArquivos(filenames):
    for filename in filenames:
        lerGrupos(filename)
            
#le o arquivo de cada grupo e o classifica
def lerGrupos(filename):
    table = pd.read_csv(
        'grupos/' + filename, 
        on_bad_lines='error',
        header=None,
        sep=',',
        encoding='latin-1')
    
    if(len(table.columns) != 2):
        arquivosErro.adicionar(filename)         
    elif(table.isnull().values.any()):
        arquivosErro.adicionar(filename)         
    else:
        quantidadeA = 0
        quantidadeB = 0
        for tIndex, tRow in table.iterrows():
            for aIndex, aRow in turmaA.iterrows():
                if(tRow[0] == aRow[0]):
                    quantidadeA += 1
                    alunosSemGrupo.remover(aRow[1])


        for tIndex, tRow in table.iterrows():
            for bIndex, bRow in turmaB.iterrows():
                if(tRow[0] == bRow[0]):
                    quantidadeB += 1
                    alunosSemGrupo.remover(bRow[1])

        if(quantidadeA != 0 and quantidadeB == 0):
            gruposTurmaA.adicionar(filename)
        elif(quantidadeA == 0 and quantidadeB != 0):
            gruposTurmaB.adicionar(filename)
        elif(quantidadeA != 0 and quantidadeB != 0):
            grupoDuasTurmas.adicionar(filename)
        elif((quantidadeA + quantidadeB) != table.shape[0]):
            grupoAlunoInexistente.adicionar(filename)

        if(table.shape[0] != 4):
            diferenteQuatro.adicionar(filename)

def main(): 
    carregarArquivos(dataFiles)    
    print(gruposTurmaA)
    print(gruposTurmaB)
    print(alunosSemGrupo)
    print(grupoDuasTurmas)
    print(diferenteQuatro)
    print(arquivosErro)
    print(grupoAlunoInexistente)

main()