# Folha de estilo

<p align='justify'>
Para esse projeto iremos utilizar a folha de estilo do Google, porém, com alterações que julgamos convenientes ao contexto da Universidade, da discplina de jogos e outros aspectos.
</p>
<p align='justify'>
Abaixo definiremos as regras particulares para esse projeto. Caso abaixo não esteja explícito que não iremos utilizar uma regra, ou não tenhamos uma que diga o contrário, iremos utilizar a regra presente no google style guide, presente no link

[Google C++ style guide](https://google.github.io/styleguide/cppguide.html)
</p>

## Operadores Booleanos
Iremos utilizar apenas os operadores booleanos __and__, __or__ e __not__ seguindo o padrão estabelecido por linguagens mais modernas. Não utilizaremos <b>&&</b>, <b>||</b> e <b>!</b>.

## Indentação
Iremos utilizar indentação de 4 espaços, não tabs.

## Comentários

### TODO's
Não serão utilizados comentários com a expressão TODO. TODO's serão rastreados  pelas issues no GitHub.

### Trechos de código
Todos os trechos de código comentados, deverão estar acompanhados por outro comentário como justificativa logo acima.

### Formatação
Todos os comentários deverão inicializar com letra maiúscula e não terão pontos finais.

## Copyright
Ao contrário da folha de estilo do Google, não será necessário adicionar linhas sobre copyright nos arquivos, pois não é conveniente ao nosso contexto.

## Estruturas de controle (condicionais e laços de repetição) e funções

### Corpos curtos
Mesmo em se a declaração couber em uma linha, ela deverá ser quebrarada após a chave de início e antes da de fim.

#### Exceções
As chaves deverão estar na mesma linha em caso do corpo da função estar vazio.

### Espaços dentro do argumento
Não deverá haver espaços depois do primeiro parêntese do argumento e nem antes do segundo.

### Espaço antes do argumento
Para estruturas de controle deverá ser dado espaço antes do primeiro parêntese do argumento da função. Porém, não para funções.

### Uso das chaves
Sempre usar chaves, mesmo em declarações de uma única linha.

## Operadores

### Aritméticos
Operadores em expressões algébricas deverão seguir as seguintes regras:
* Deverá conter espaços antes e depois dos operadores + e -;
* Não deverá conter espaços antes e depois dos operadores * e /;
* Operadores cujo um dos argumentos for um parêntese deverão ser cercados por espaços.

## Switch
Case Blocks não deverão usar chaves.
