void callback(char* topic, byte* payload, unsigned int length) {
    String conc_payload;
    for (int i = 0; i < length; i++) {
    conc_payload += ((char)payload[i]);
  }
  my_topic = topic;
  my_payload = conc_payload;
}

void reconnect() {
    while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    if (client.connect("QTA_IoT")) {
      Serial.println("connected");
      client.subscribe("QTA_IoT_Recebe");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}

void Status_Wifi(){
  if(WiFi.status() == WL_CONNECTED){
    digitalWrite(2, HIGH);
  }else{
    digitalWrite(2, LOW);
  }
}
void Analogico(){
  //verificar
  if(startime <= 2000){
    cliente.publish("QTA_IoT_Envia contagem",String(count).c_str());
    cliente.publish("QTA_IoT_Envia tempo",String(elapsedtime/1000).c_str());
    //Implementar dentro das funções ja existentes
  }
}
void Controle(){
  if(my_payload == "A"){
    digitalWrite(partida, HIGH);
    delay(3000);
    digitalWrite(partida,LOW);
    delay(1000);
  }
  if(my_payload == "a"){
    digitalWrite(releger, LOW);
  }
}
