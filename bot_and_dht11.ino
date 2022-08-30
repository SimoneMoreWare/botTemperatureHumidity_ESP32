#include <WiFi.h> 
#include <WiFiClientSecure.h> 
#include <UniversalTelegramBot.h> 

#define WIFI_SSID "insertNameWIFI" 
#define PASSWORD_WIFI "insertPassword" 
#define BOT_API_TOKEN "insertAPI" 
#define chat_id "insertChatID" //nel readme è presente la guida su come ottenere il chat id del bot

const unsigned long intervallo = 10000; //pausa per la ricezione dei messaggi 
unsigned long ultima_chiamata = 0; //gestione del millis

WiFiClientSecure s_client; //wifi client
UniversalTelegramBot bot(BOT_API_TOKEN, s_client); //telegram client 

void setup() {
  WiFi.begin(WIFI_SSID, PASSWORD_WIFI); //connetto al wifi
  s_client.setCACert(TELEGRAM_CERTIFICATE_ROOT); //creo una connessione con Telegram utilizzando un certificato di sicurezza
 
  while (WiFi.status() != WL_CONNECTED) { //finchè il wifi non è connesso attendi
    delay(500);
  }
}

void loop() {
  if (millis() - ultima_chiamata > intervallo) { //se il valore del timer "millis" - l'ultimo valore in millisecondi di quando abbiamo eseguito le istruzioni, è maggiore del tempo di attesa "intervallo", allora esegui le istruzioni
    bot.sendMessage(chat_id, "Benvenuto");
    ultima_chiamata = millis(); //aggiorna l'ultimo periodo in millisecondi in cui sono state eseguite le istruzioni all'interno del ciclo while
  }
}
