#include <WiFi.h> 
#include <WiFiClientSecure.h>
#include <DHT.h>
#include <UniversalTelegramBot.h> 

#define WIFI_SSID "insertWIFI" 
#define PASSWORD_WIFI "password" 
#define BOT_API_TOKEN "insertapitoken" 
#define chat_id "insertChatID" //nel readme è presente la guida su come ottenere il chat id del bot

#define DHT_SENSOR_PIN  13 // ESP32 pin GIOP21 connesso al dht11
#define DHT_SENSOR_TYPE DHT11
DHT dht_sensor(DHT_SENSOR_PIN, DHT_SENSOR_TYPE);

const unsigned long intervallo = 10000; //pausa per la ricezione dei messaggi 
unsigned long ultima_chiamata = 0; //gestione del millis

WiFiClientSecure s_client; //wifi client
UniversalTelegramBot bot(BOT_API_TOKEN, s_client); //telegram client 

void setup() {
  WiFi.begin(WIFI_SSID, PASSWORD_WIFI); //connetto al wifi
  s_client.setCACert(TELEGRAM_CERTIFICATE_ROOT); //creo una connessione con Telegram utilizzando un certificato di sicurezza
  
  dht_sensor.begin(); // initialize the DHT sensor

  while (WiFi.status() != WL_CONNECTED) { //finchè il wifi non è connesso attendi
    delay(500);
  }
}

void loop() {
  String msg="Ciao, la temperatura e' pari a  ";;
  if (millis() - ultima_chiamata > intervallo) { //se il valore del timer "millis" - l'ultimo valore in millisecondi di quando abbiamo eseguito le istruzioni, è maggiore del tempo di attesa "intervallo", allora esegui le istruzioni
    float humi  = dht_sensor.readHumidity();// leggo l'umidità
    float tempC = dht_sensor.readTemperature();//leggo la temperatura in gradi celsius
    // controllo se la lettura e' stata effetuata con successo
    if ( isnan(tempC) || isnan(humi)) {
      bot.sendMessage(chat_id, "Errore nella lettura");
    } else {
      //eseguo varie concatenazioni per l'output
      msg += msg.concat(tempC);
      msg += " C";
      msg += " e l'umidita' e del ";
      msg += msg.concat(humi);
      msg += "%"; 
      bot.sendMessage(chat_id,msg);
    }
    ultima_chiamata = millis(); //aggiorna l'ultimo periodo in millisecondi in cui sono state eseguite le istruzioni all'interno del ciclo while
  }
}
