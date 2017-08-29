# Folha de estilo

<p align='justify'>
Para esse projeto iremos utilizar a folha de estilo do Google, porém, com alterações que julgamos convenientes ao contexto da Universidade, da discplina de jogos e outros aspectos.
</p>
<p align='justify'>
Abaixo definiremos as regras particulares para esse projeto. Caso abaixo não esteja explícito que não iremos utilizar uma regra, ou não tenhamos uma que diga o contrário, iremos utilizar a regra presente no google style guide, presente no link

[Google C++ style guide](https://google.github.io/styleguide/cppguide.html)
</p>

## Operadores Booleanos
Iremos utilizar apenas os operadores booleanos __and__, __or__ e __not__ seguindo o padrão estabelecido por linguagens mais modernas. Não utilizaremos <b>&&</b>, <b>||</b> e <b>!</b>. Exemplo de uso de operadores booleanos (arquivo src/OptionsState.cpp):

```
if (on_submenu and (i != static_cast<int>(options.size()) - 1) and
    (i != current_option)) {
    options[i]->set_color(DARK_GREY);
}
```

## Indentação
Iremos utilizar indentação de 4 espaços, não tabs. Exemplo (arquivo src/FighterMenu.cpp):

```
bool FighterMenu::is_skin_available(int idx) {
    return skin_available[idx];
}
```

## Comentários

### TODO's
Não serão utilizados comentários com a expressão TODO. TODO's serão rastreados  pelas issues no GitHub.

### Trechos de código
Todos os trechos de código comentados, deverão estar acompanhados por outro comentário como justificativa logo acima.

### Formatação
Todos os comentários deverão inicializar com letra maiúscula e não terão pontos finais. Exemplo (arquivo src/JoystickConfigState.cpp):

```
// Select and start
add_object(new JoystickButton(offset_x + SELECT_X, offset_y + SELECT_Y,
                              "select", InputManager::SELECT,
                              joystick_id,"select_start"));
```

## Estruturas de controle (condicionais e laços de repetição) e funções

### Corpos curtos
Mesmo em se a declaração couber em uma linha, ela deverá ser quebrarada após a chave de início e antes da de fim. Exemplo (src/OptionsState.cpp):

```
if (current_sub_option[current_option] != 0) {
    current_sub_option[current_option]--;
}
```

#### Exceções
As chaves deverão estar na mesma linha em caso do corpo da função estar vazio.

### Espaços dentro do argumento
Não deverá haver espaços depois do primeiro parêntese do argumento e nem antes do segundo.

### Espaço antes do argumento
Para estruturas de controle deverá ser dado espaço antes do primeiro parêntese do argumento da função. Porém, não para funções.

### Uso das chaves
Sempre usar chaves, mesmo em declarações de uma única linha. Exemplo (arquivo src/BattleEnd.cpp):

```
bool BattleEnd::is_dead() {
    return false;
}

bool BattleEnd::quit_requested() {
    return quitRequested;
}
```

## Operadores

### Aritméticos
Operadores em expressões algébricas deverão seguir as seguintes regras:
* Deverá conter espaços antes e depois dos operadores aritméticos;

Exemplo (arquivo src/OptionsState.cpp):

```
int prev_text_height = (TEXT_HEIGHT + TEXT_OFFSET * 2) * prev_text_size;
```

## Switch
Case Blocks não deverão usar chaves. Exemplo (arquivo src/InputManager.cpp):

Deve ser assim:
```
switch (event.type) {
    case SDL_KEYDOWN:
        if (event.key.repeat) {
            break;
        }
        key_id = event.key.keysym.sym;
        key_state[key_id] = true;
        key_update[key_id] = update_counter;
        emulate_joystick(key_id, true);
        break;
```
E não assim:
```
switch (event.type) {
    case SDL_KEYDOWN: {
        if (event.key.repeat) {
           break;
        }
        key_id = event.key.keysym.sym;
        key_state[key_id] = true;
        key_update[key_id] = update_counter;
        emulate_joystick(key_id, true);
        break;
    }
```
