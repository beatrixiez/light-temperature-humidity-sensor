#include <DHT.h> // biblioteca para sensor dht
#include <ArduinoJson.h> // biblioteca para manipular no formato json

#define dhtpin 2 // define pino 2 como conectado ao dht
#define dhttype DHT22 // define o sensor utilizado
#define ldrpin A0 // define o pino a0 como conectado ao ldr

DHT dht(dhtpin, dhttype); // cria o objeto para acessar e manipular dht

void setup() {
  Serial.begin(9600); // iniciando comunicação serial em 9600b/s
  dht.begin(); // inicia o sensor para começar leitura de dados
  pinMode(ldrpin, INPUT); // configura ldr como entrada, para receber dados
}

void loop() {
  float temperature = dht.readTemperature(); // lê a temperatura e armazena na variável
  float humidity = dht.readHumidity(); // lê a umidade e armazena na variável
  int luminosity = analogRead(ldrpin); // leitura do valor do sensor e armazenamento na variável

  StaticJsonDocument<200> jsonDoc; // criar um objeto json, com tamanho de 200b, que armazena os dados
  jsonDoc["temperatura"] = temperature; // atribui o valor da váriavel à chave
  jsonDoc["umidade"] = humidity; // atribui o valor da váriavel à chave
  jsonDoc["luminosidade"] = luminosity; // atribui o valor da váriavel à chave

  String jsonString; // cria uma variavel do tipo string para armazenar os dados em texto
  serializeJson(jsonDoc, jsonString); // converte o objeto jsondoc em uma string de texto
  Serial.println(jsonString); // envia a string para o monitor serial

  delay(4000); // aguarda 4s antes de ler os sensores novamente
}