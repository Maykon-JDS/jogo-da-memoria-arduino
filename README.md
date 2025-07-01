# Jogo da Memória com Arduino

![Foto de Capa](assets/imgs/foto-de-capa.png)

[![licence mit](https://img.shields.io/badge/licence-MIT-blue.svg)](./LICENSE)
[![Conventional Commits](https://img.shields.io/badge/Conventional%20Commits-1.0.0-%23FE5196?logo=conventionalcommits&logoColor=white)](https://conventionalcommits.org)

## Sumário
- [Jogo da Memória com Arduino](#jogo-da-memória-com-arduino)
  - [Sumário](#sumário)
  - [Introdução](#introdução)
  - [Tecnologias Usadas](#tecnologias-usadas)
  - [Funcionamento](#funcionamento)
  - [Componentes Utilizados](#componentes-utilizados)
  - [Como Executar o Projeto](#como-executar-o-projeto)
  - [Licença](#licença)

## Introdução
Este projeto consiste em um jogo da memória implementado com **Arduino UNO**, utilizando LEDs, botões, um buzzer e um potenciômetro. O jogo apresenta uma sequência de luzes e sons, que o jogador precisa repetir corretamente. A cada rodada, a sequência aumenta em dificuldade.

## Tecnologias Usadas

![Arduino](https://img.shields.io/badge/Arduino-00979D?style=for-the-badge&logo=arduino&logoColor=white)
![C++](https://img.shields.io/badge/C%2B%2B-00599C?style=for-the-badge&logo=c%2B%2B&logoColor=white)

## Funcionamento

1. O Arduino gera uma sequência de LEDs acesos, com som.
2. O jogador deve repetir a sequência utilizando os botões correspondentes.
3. Se a sequência for correta, um novo nível é iniciado com um LED adicional.
4. Em caso de erro, o jogo sinaliza e reinicia ao pressionar qualquer botão.

## Componentes Utilizados

- 1 Arduino UNO
- 4 LEDs (vermelho, azul, amarelo, verde)
- 4 botões com resistores de pull-down ou INPUT_PULLUP
- 1 buzzer
- 1 potenciômetro (opcional)
- Cabos e protoboard

## Como Executar o Projeto

1. Faça o upload do código `main.ino` para o seu Arduino.
2. Conecte os componentes conforme os pinos definidos no código:

   | Componente     | Pino |
   |----------------|------|
   | LED Vermelho   | 13   |
   | LED Azul       | 12   |
   | LED Amarelo    | 11   |
   | LED Verde      | 10   |
   | Botão Vermelho | 7    |
   | Botão Azul     | 6    |
   | Botão Amarelo  | 5    |
   | Botão Verde    | 4    |
   | Buzzer         | 2    |

3. Abra o monitor serial a 9600 baud para depuração (opcional).
4. Jogue! Siga as sequências e avance de nível.

## Licença

Este projeto está licenciado sob a [Licença MIT](LICENSE.md).
