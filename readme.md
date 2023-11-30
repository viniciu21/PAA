## Funcionamento

### Gerador de instâncias

Para gerar um conjunto de retângulos com valores aleatórios, execute o script `instance_generator.py` através do comando:

*python instance_generator.py* ou *python3 instance_generator.py*.

Esse comando vai gerar um arquivo `instance.txt` que poderá ser utilizado como entrada para os algoritmos desenvolvidos neste trabalho.

### Heuristica (FFDH)

Para testar a heuristica, execute no terminal:

*g++ -std=c++11 ffdh.cpp main.cpp -o main.out*

e 

*./main.out*

Escolha uma de nossas 500 instancias.

### Algoritmo exato branch and bound

Para testar a heuristica, execute no terminal:

*g++ -std=c++11 ffdh.cpp branch_and_bound.cpp -o main.out*

e 

*./main.out*

Todos os 500 testes serão executados.
