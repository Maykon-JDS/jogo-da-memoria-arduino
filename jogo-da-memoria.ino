#include <LinkedList.h>

#define pinoLedVermelho 13
#define pinoLedAzul 12
#define pinoLedAmarelo 11
#define pinoLedVerde 10

#define pinoBtnVermelho 7
#define pinoBtnAzul 6
#define pinoBtnAmarelo 5
#define pinoBtnVerde 4

#define pinoBuzzer 2


class Buzzer
{
  private:
  int pino;
  int pos;

public:
  Buzzer(int pino, int pos)
  {
    this->pino = pino;
    this->pos = pos;
  }

  void tocarEParar(int tom, int tempo){
    this->ligar(tom);
    delay(tempo);
    this->desligar();
  }

  void ligar(int tom)
  {
     tone(this->pino, tom);
  }

  void desligar(){
    noTone(this->pino);  
  }
};

class Botao
{

private:
  int pino;
  int pos;

public:
  Botao(int pino, int pos)
  {
    this->pino = pino;
    this->pos = pos;
  }

  int click()
  {
    return !digitalRead(this->pino);
  }

  int getPos()
  {
    return pos;
  }

  int getPino()
  {
    return pino;
  }
};

class Potenciometro
{

private:
  int pino;
  int pos;

public:
  Potenciometro(int pino)
  {
    this->pino = pino;
  }

  int getValor()
  {
    return analogRead(this->pino);
  }

  int getPos()
  {
    return pos;
  }
};

class Led
{

private:
  int pino;
  int pos;
  int tempoDeDelay = 100;

public:
  Led()
  {
  }

  Led(int pino, int pos)
  {
    this->pino = pino;
    this->pos = pos;
  }

  Led(int pino, int pos, int tempoDeDelay)
  {
    this->pino = pino;
    this->pos = pos;
    this->tempoDeDelay = tempoDeDelay;
  }

  void piscar()
  {
    this->acender();
    delay(this->tempoDeDelay);
    this->apagar();
  }

  void acender()
  {
    digitalWrite(this->pino, HIGH);
  }

  void apagar()
  {
    digitalWrite(this->pino, LOW);
  }

  int getPos()
  {
    return pos;
  }
};

class JogoDaMemoria
{

private:
  String estado = "setup";
  int contagemCliques = 0;
  LinkedList<Led> setupListaLed = LinkedList<Led>();

  Botao *arrayBotoes;
  Led *arrayLeds;
  int tons[6] = {888, 666, 444, 555, 2000, 4000};
  Buzzer *buzzer;
  Potenciometro *potenciometro;

public:
  JogoDaMemoria(Led *arrayLeds, Botao *arrayBotoes)
  {
    this->arrayLeds = arrayLeds;
    this->arrayBotoes = arrayBotoes;
  }

  JogoDaMemoria(Led *arrayLeds, Botao *arrayBotoes, Buzzer * buzzer)
  {
    this->arrayLeds = arrayLeds;
    this->arrayBotoes = arrayBotoes;
    this->buzzer = buzzer;
  }

  JogoDaMemoria(Led *arrayLeds, Botao *arrayBotoes, Potenciometro *potenciometro)
  {
    this->arrayLeds = arrayLeds;
    this->arrayBotoes = arrayBotoes;
    this->potenciometro = potenciometro;
  }

  JogoDaMemoria(Led *arrayLeds, Botao *arrayBotoes, Potenciometro *potenciometro, Buzzer * buzzer)
  {
    this->arrayLeds = arrayLeds;
    this->arrayBotoes = arrayBotoes;
    this->potenciometro = potenciometro;
    this->buzzer = buzzer;
  }

  void piscarLedComBotao(Led led, Botao botao)
  {
    if (botao.click())
    {
      validarBotaoPressionado(botao);
      buzzer->tocarEParar(tons[led.getPos()], 100);
      led.piscar();
    }
  }

  void validarBotaoPressionado(Botao botao)
  {
    if (botao.getPos() == setupListaLed.get(contagemCliques).getPos())
    {
      contagemCliques++;
    }
    else
    {
      estado = "erro";
    }
  }

  Led getLedAleatorio()
  {
    int indiceAleatorio = random(0, 4);

    return arrayLeds[indiceAleatorio];
  }

  void addLedSetupListaLed(Led novoLed)
  {
    setupListaLed.add(novoLed);
  }

  void piscarSetupListaLed(int tempoDeDelay = 500)
  {
    for (int i = 0; i < setupListaLed.size(); i++)
    {
      buzzer->ligar(tons[setupListaLed.get(i).getPos()]);
      setupListaLed.get(i).piscar();
      buzzer->desligar();
      delay(tempoDeDelay);
      
    }
  }

  void setup(int tempoDeDelay = 500)
  {
    delay(tempoDeDelay);
    addLedSetupListaLed(getLedAleatorio());
    piscarSetupListaLed();
    contagemCliques = 0;
    this->estado = "partida";
  }

  void partida()
  {

    if (contagemCliques < setupListaLed.size())
    {
      piscarLedComBotao(arrayLeds[0], arrayBotoes[0]);
      piscarLedComBotao(arrayLeds[1], arrayBotoes[1]);
      piscarLedComBotao(arrayLeds[2], arrayBotoes[2]);
      piscarLedComBotao(arrayLeds[3], arrayBotoes[3]);
    }
    else
    {
      sinalizarProximoNivel();
      estado = "setup";
    }
  }

  void gameplay()
  {
    if (estado == "setup")
    {
      this->setup();
    }
    else if (estado == "partida")
    {
      this->partida();
    }
    else if (estado == "erro")
    {
      this->erro();
    }
  }

  void erro()
  {
    this->sinalizarErro();
    reiniciar(arrayBotoes[0]);
    reiniciar(arrayBotoes[1]);
    reiniciar(arrayBotoes[2]);
    reiniciar(arrayBotoes[3]);
  }

  void sinalizarProximoNivel(int tempoDeDelay = 100)
  {
    acenderTodosLeds();
    buzzer->tocarEParar(tons[5],50);
    buzzer->tocarEParar(tons[5],50);
    buzzer->tocarEParar(tons[5],50);
    buzzer->tocarEParar(tons[5],50);
    buzzer->tocarEParar(tons[5],50);
    buzzer->tocarEParar(tons[5],50);
    buzzer->tocarEParar(tons[5],50);
    buzzer->tocarEParar(tons[5],50);
    delay(tempoDeDelay);
    apagarTodosLeds();
  }

  void sinalizarErro()
  {
    int timeDelay = 100;
    acenderTodosLeds();
    buzzer->tocarEParar(tons[5],timeDelay);
    delay(timeDelay);
    apagarTodosLeds();
    delay(timeDelay);
  }

  void reiniciar(Botao botao)
  {
    if (botao.click())
    {
      setupListaLed.clear();
      this->estado = "setup";
    }
  }

  void acenderTodosLeds()
  {
    for (int i = 0; i < 4; i++)
      arrayLeds[i].acender();
  }

  void apagarTodosLeds()
  {

    for (int i = 0; i < 4; i++)
    {
      arrayLeds[i].apagar();
    }
  }
};

Led ledVermelho(pinoLedVermelho, 0);
Led ledAzul(pinoLedAzul, 1);
Led ledAmarelo(pinoLedAmarelo, 2);
Led ledVerde(pinoLedVerde, 3);

Led arrayLeds[] = {ledVermelho, ledAzul, ledAmarelo, ledVerde};

Botao btnVermelho(pinoBtnVermelho, 0);
Botao btnAzul(pinoBtnAzul, 1);
Botao btnAmarelo(pinoBtnAmarelo, 2);
Botao btnVerde(pinoBtnVerde, 3);

Botao arrayBotoes[] = {btnVermelho, btnAzul, btnAmarelo, btnVerde};

Buzzer buzzer(pinoBuzzer, 0);

JogoDaMemoria jogoDaMemoria(arrayLeds, arrayBotoes, &buzzer);

void setup()
{

  Serial.begin(9600);
  randomSeed(analogRead(0));

  pinMode(pinoLedVermelho, OUTPUT);
  pinMode(pinoLedAzul, OUTPUT);
  pinMode(pinoLedAmarelo, OUTPUT);
  pinMode(pinoLedVerde, OUTPUT);

  pinMode(pinoBuzzer, OUTPUT);

  pinMode(pinoBtnVermelho, INPUT_PULLUP);
  pinMode(pinoBtnAzul, INPUT_PULLUP);
  pinMode(pinoBtnAmarelo, INPUT_PULLUP);
  pinMode(pinoBtnVerde, INPUT_PULLUP);
}

void loop()
{
  jogoDaMemoria.gameplay();
}
