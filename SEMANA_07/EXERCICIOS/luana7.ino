#include <WiFi.h>
#include <WiFiAP.h>
#include <WebServer.h>
#include <ESP2SOTA.h>

#define botao1 17
#define botao2 18
#define ledazul 37
#define ledverde 38

const char* ssid = "luana"; // nome da rede
const char* password = "lu123456"; // senha da rede de conexão

int x=0;
int y=0;

WebServer server(80);

void setup(void) {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  server.on("/", handleRoot);
  server.on("/on", handleOn);
  server.onNotFound(handleNotFound);
  server.begin();

  pinMode(botao1, INPUT_PULLUP);
  pinMode(ledazul, OUTPUT);

  pinMode(botao2, INPUT_PULLUP);
  pinMode(ledverde, OUTPUT);
}

void handleRoot(){
  String html = "";
  html+= "<style>a (font-size:40px; background-color: #DC143C	; font-family: Raleway, "Open Sans", sans-serif;)</style>";
  html+= "<meta charset='UTF-8'>";
  html+= "<h1>O jogador que apertar o botão 5 vezes mais rápido, vence.<h1/>";
  html+= "<a href=\"/on\">Clique aqui para começar o jogo</a>";
  server.send(200, "text/html", html);

}

void jogaodorA(){
  //html da minha pagina e quando jogador amarelo venceu
  String html = "";
  html+= "<style>a (font-size:40px; background-color: #DC143C	; font-family: Raleway, "Open Sans", sans-serif;)</style>";
  html+= "<meta charset='UTF-8'>";
  html+= "<h1>O jogador que apertar o botão 5 vezes mais rápido, vence.<h1/>";
  html+= "<a href=\"/on\">Clique aqui para começar o jogo</a>";
  html+= "<h1>Jogador azul ganhou!<h1/>";
  server.send(200, "text/html", html);

}

void jogadorB(){
  //html da minha pagina e quando jogador branco venceu
  String html = "";
  html+= "<style>a (font-size:40px; background-color: #DC143C	; font-family: Raleway, "Open Sans", sans-serif;)</style>";
  html+= "<meta charset='UTF-8'>";
  html+= "<h1>O jogador que apertar o botão 5 vezes mais rápido, vence.<h1/>";
  html+= "<a href=\"/on\">Clique aqui para começar o jogo</a>";
  html+= "<h1>Jogador verde ganhou!<h1/>";
  server.send(200, "text/html", html);
}

void handleNotFound(){
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i = 0; i < server.args(); i++){
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
}

void handleOn(){
  while(true){
  if (!digitalRead (botao1)){
    x++;
      if(x==5){
        digitalWrite(ledazul,HIGH);
        delay(500);
        digitalWrite(ledazul, LOW);
        x=0;
        y=0;
        jogaodorA(); 
        break;
      }
    Serial.print("botao1: ");
    Serial.println(x);
    delay(500);
  }

  if (!digitalRead (botao2)){
    y++;
      if(y==5){
        digitalWrite(ledverde,HIGH);
        delay(500);
        digitalWrite(ledverde, LOW);
        y=0;
        x=0;
        jogadorB();
        break;
      }
    Serial.print("botao2:");
    Serial.println(y);
    delay(500);
  }
  }
  handleRoot();
}

void loop(void) {
  server.handleClient();
  delay(500); 
}