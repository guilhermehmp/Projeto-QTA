#define redeon 13             // Verifica se a rede está on/off
#define releger 27            // Rele de carga do gerador  
#define relerede 14           // Rele de carga da rede
#define desliga_ger 33        // Botão desliga gerador manual
#define liga_ger 25           // Botão liga gerador manual 
#define autom 12              // Define modo automatico 
#define man 26                // Define modo manual
#define ger_on 35             // Sensor para verificar se o gerador foi ligado
#define emergencia 32		      // Botão de emergencia
#define partida 21            // Rele para dar partida no gerador
#define buzzer 18             // Buzzer de alertas
#define alert_ger 19          // Led de alerta indicando que o gerador não ligou

#include <WiFi.h>
#include <PubSubClient.h>

// Configuração da Rede Wifi
const char* ssid = "Guilherme_HMP";
const char* password = "paulino@";
const char* mqtt_server = "192.168.1.101";

// Variaveis para ESP32 Receber (Assinar ao topico) e o Node-Red (Publica)
String my_payload;
String my_topic;
// Variaveis para EPS32 Enviar (Publicar ao topico) e o Node-Red (Assinar)
int count = 0;                // Contador de vezes em que o gerador foi utilizado
unsigned long starttime = 0;  // Variável para registrar o tempo de início
unsigned long endtime = 0;    // Variável para registrar o tempo de término
unsigned long elapsedtime = 0; // Variável para registrar o tempo decorrido

WiFiClient QTA_IoT;
PubSubClient client(QTA_IoT);

int i, aux, aux1 = 0;         // Variáveis auxiliares
int j = 1;                    // Variáveis auxiliares

void setup() {
  pinMode(releger, OUTPUT);
  pinMode(relerede, OUTPUT);
  pinMode(redeon, INPUT);
  pinMode(autom, INPUT);
  pinMode(man, INPUT);
  pinMode(desliga_ger, INPUT);
  pinMode(liga_ger, INPUT);
  pinMode(ger_on, INPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(alert_ger, OUTPUT);
  pinMode(emergencia, INPUT);
  pinMode(partida, OUTPUT);
  pinMode(2, OUTPUT);  
  Serial.begin(115200); 
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
}
void setup_wifi() {

  delay(10);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

