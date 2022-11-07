//LEDs
#define azul 12 
#define verde 11
#define vermelho 10
#define branco 9

//botões
#define b1 4
#define b2 5

//buzzer
int buzzer = 18;
//ldr
int ldr = 1;


int binario[4];
int freq[15] = {50, 100, 150, 200, 250, 300, 350, 400, 450, 500, 550, 600, 650, 700, 750};
int x = 0;
int valorNormalizado;

void converter_binario(int valor){
  int i = 0;
  while (i != 4)
  {
    binario[i] = valor % 2;
    valor = valor / 2;
    i++;
  }
}
int normalizado(int valor)
{
  int novoValor = (valor * 15) / 4095;
  return novoValor;  
}

void setup() {
  pinMode(azul, OUTPUT);
  pinMode(verde, OUTPUT);
  pinMode(vermelho, OUTPUT);
  pinMode(branco, OUTPUT);
  pinMode(b1, INPUT_PULLUP);
  pinMode(b2, INPUT_PULLUP);
  pinMode(ldr, INPUT);
  pinMode(buzzer, OUTPUT);
  Serial.begin(115200);
}

void som(char buzzer, int frequencia, int tempo){
  float duracao = 1000.0/frequencia;
  for (int i = 0; i < tempo/(duracao); i++){
    digitalWrite(buzzer, HIGH);
    delayMicroseconds(duracao*500);
    digitalWrite(buzzer, LOW);
    delayMicroseconds(duracao*500);
  }
}

void somBinario(int valorLDR) {
  switch(valorLDR) {
    case 1:
      som(buzzer, 50, 500);
    break;
    case 2:
      som(buzzer, 100, 500);
    break;
    case 3:
      som(buzzer, 150, 500);
    break;
    case 4:
      som(buzzer, 200, 500);
    break;
    case 5:
      som(buzzer, 250, 500);
    break;
    case 6:
      som(buzzer, 300, 500);
    break;
    case 7:
      som(buzzer, 350, 500);
    break;
    case 8:
      som(buzzer, 400, 500);
    break;
    case 9:
      som(buzzer, 450, 500);
    break;
    case 10:
      som(buzzer, 500, 500);
    break;
    case 11:
      som(buzzer, 550, 500);
    break;
    case 12:
      som(buzzer, 600, 500);
    break;
    case 13:
      som(buzzer, 650, 500);
    break;
    case 14:
      som(buzzer, 700, 500);
    break;
    case 15:
      som(buzzer, 750, 500);
    break;

  }
}

void acenderLed()
{
  digitalWrite(azul, binario[0]);
  digitalWrite(verde, binario[1]);
  digitalWrite(vermelho, binario[2]);
  digitalWrite(branco, binario[3]);
  delay(100);
  digitalWrite(azul, LOW);
  digitalWrite(verde, LOW);
  digitalWrite(vermelho, LOW);
  digitalWrite(branco, LOW);
  binario[0] = 0;
  binario[1] = 0;
  binario[2] = 0;
  binario[3] = 0;
}

void executar()
{
  for (int i = 0; i < sizeof(freq)/4; i ++)
  {
    somBinario(freq[i]);
    converter_binario(freq[i]);
    acenderLed();
  }
  x = 0;
}

void loop() {
  int b1Read = digitalRead(b1);
  int b2Read = digitalRead(b2);
  if (b1Read == 0)
  {
    if (x < 10)
    {
      Serial.println("gravando");
      int ldrValor = analogRead(ldr);
      valorNormalizado = normalizado(ldrValor);
      freq[x] = valorNormalizado;
      x += 1;
      converter_binario(valorNormalizado);
      somBinario(valorNormalizado);
      acenderLed();
    }
    else
    {
      som(buzzer, 4095, 500);
      delay(150);
      som(buzzer, 4095, 500);
      delay(150);
      som(buzzer, 4095, 500);
    }
  }
  if (b2Read == 0)
  {
    Serial.println("reproduzindo");
    executar();
  }
}