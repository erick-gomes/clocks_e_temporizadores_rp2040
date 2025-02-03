# Semaforo e Temporizadores com Raspberry Pi Pico

Este projeto implementa duas funcionalidades principais utilizando o Raspberry Pi Pico W: um semáforo com temporização e um sistema de temporização para acionamento de LEDs via botão. Todas as funcionalidades estão no arquivo `clocks_e_temporizadores_rp2040.c`

---

## Funcionalidade 1: Semáforo com Temporização

### O que faz?
O semáforo alterna entre as cores vermelha, amarela e verde, com intervalos de 3 segundos para cada mudança de estado.

### Como funciona?
1. Inicia com o LED vermelho aceso.
2. Após 3 segundos, o LED amarelo é aceso.
3. Após mais 3 segundos, o LED verde é aceso.
4. O ciclo se repete indefinidamente.

### Componentes
- Raspberry Pi Pico W.
- 03 LEDs (vermelho, amarelo e verde).
- 03 Resistores de 330 Ω.

### Código
A lógica do semáforo está implementada na função `semaforo_callback()` dentro do arquivo `clocks_e_temporizadores_rp2040.c`.

---

## Funcionalidade 2: Temporizador de Um Disparo (One Shot)

### O que faz?
Ao pressionar um botão, todos os LEDs são acesos. Após 3 segundos, dois LEDs permanecem acesos, e após mais 3 segundos, apenas um LED fica aceso. O botão só pode ser acionado novamente após o último LED ser desligado.

### Como funciona?
1. Pressione o botão para acender todos os LEDs.
2. Após 3 segundos, dois LEDs permanecem acesos.
3. Após mais 3 segundos, apenas um LED fica aceso.
4. O botão só pode ser usado novamente após o ciclo terminar.

### Componentes
- Raspberry Pi Pico W.
- 03 LEDs (azul, vermelho e verde).
- 03 Resistores de 330 Ω.
- 01 Botão (Pushbutton).

### Código
A lógica do temporizador de um disparo está implementada na função `btn_action()` e nas funções de callback dentro do arquivo `clocks_e_temporizadores_rp2040.c`.

---

## Como usar?
1. Compile o código usando o Pico SDK.
2. Carregue o arquivo `.uf2` no Raspberry Pi Pico.
3. Conecte os componentes conforme descrito nas funcionalidades.

---

Este projeto foi desenvolvido como parte do **EmbarcaTech**, uma iniciativa do **CEPEDI** (Centro de Pesquisa, Desenvolvimento e Inovação) que oferece capacitação em tecnologia embarcada por meio de uma plataforma Moodle. O objetivo é consolidar conceitos de temporizadores, interrupções e controle de GPIOs, aplicando-os em um semáforo automático e um sistema de temporização por botão.
