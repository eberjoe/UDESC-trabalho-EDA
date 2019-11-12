# Trabalho: Conjuntos Disjuntos

Algumas aplicações tratam do agrupamento de n elementos distintos em uma coleção de conjuntos disjuntos. Há duas operações importantes nesse tipo de estrutura. A primeira consiste em encontrar em que conjunto um dado elemento pertence. A outra é a união de dois conjuntos. O foco deste trabalho é a implementação de um TAD (Tipo Abstrato de Dados) que implemente tal estrutura e suas operações.

Conjuntos disjuntos podem ser representados por uma estrutura que mantém uma coleção de conjuntos, onde cada conjunto é identificado por um representante, que é um de seus membros. Em algumas aplicações, o critério para a determinação do representante não é relevante. Em geral, pode-se utilizar o primeiro termo (que foi utilizado na criação do conjunto), ou mesmo o menor membro do conjunto
(assumindo, nesse caso, que exista alguma possibilidade de ordenação entre seus membros).

Tal estrutura pode ser implementada como uma multi-lista, ou seja, uma lista de listas. Cada elemento da lista principal aponta para o descritor de outra lista, que neste caso é um dos conjuntos. Por fim, cada elemento das listas secundárias representam os membros propriamente ditos. Além disso, tal como abordado ao longo da disciplina, considera-se que tal estrutura é genérica. Nesse sentido, cada membro é acessado através de um ponteiro do tipo ```void```.

Sendo x membro do conjunto (portanto, um ponteiro void), tal estrutura deve implementar três funções básicas:
1. ```Cria_Conjunto ( x )``` : cria um novo conjunto cujo único membro (e, portanto, seu representante) é x. Já que os conjuntos são disjuntos, x não pode pertencer a nenhum outro conjunto da estrutura. A dica aqui é usar a já conhecida função ```compara ()```, via call-back.
2. ```União ( x , y )``` : faz a união dos dois conjuntos cujos representantes são x e y (Sx e Sy) em um novo conjunto. O representante desse novo conjunto pode ser qualquer membro de Sx U Sy, embora muitas implementações dessa função escolham um dos representantes de Sx ou Sy. Como é necessário que os conjuntos sejam disjuntos, tal operação “destrói” os conjuntos Sx e Sy. Já que a implementação solicitada é usando listas, a operação pode ser facilmente implementada através de um simples ajuste de ponteiros fazendo um append
entre Sx e Sy.
3. ```Busca_Conjunto ( x )``` : retorna um ponteiro para o conjunto contendo x. Além dessas, outras operações gerais para TADs devem ser implementadas: inicialização, mostra conjuntos na tela, destrói um conjunto e desaloca toda a estrutura.

Finalmente, implemente uma aplicação que oferece um menu de texto para a manipulação do TAD *Conjuntos Disjuntos*. A aplicação deve oferecer todas as funções solicitadas. Se necessário, outras funções podem ser implementadas e detalhes de implementação podem ser alterados, sendo justificados durante a apresentação do trabalho. Embora o TAD deva ser genérico ```(void * )```, a aplicação poderá instanciá-lo para lidar com tipos simples, tais como números ou caracteres.

## Critérios de avaliação:
* Coletivos: execução correta e alinhamento com o que foi solicitado neste enunciado. Boas práticas para criação e uso de TADs também serão avaliadas.
* Individuais: domínio do assunto e do programa implementado.

## Informações importantes:
[-] Equipe: 2 ou 3 alunos.

[-] Entrega: por e-mail, até o dia 27/11.

[-] Apresentação: dia 27/11, no laboratório, durante o horário de aula. Alternativamente, as equipes que preferirem apresentar antes podem agendar um horário para apresentação na sala do professor.
