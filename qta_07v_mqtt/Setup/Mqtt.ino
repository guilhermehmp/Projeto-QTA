void callback(char* topic, byte* payload, unsigned int length) {
  String conc_payload;
  for (int i = 0; i < length; i++) {
    conc_payload  += ((char)payload[i]);
  }
  my_payload = conc_payload;
  my_topic = topic;
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
void comando_mqtt (){
  if(my_payload == "A"){
    client.publish("QTA_IoT_Envia status_gerador", String("Ligando Gerador").c_str()); //verificar qual valor retorna, se der errado retire a função c_str
    digitalWrite(partida, HIGH);
    Serial.println("TENTANDO DAR PARTIDA VIA WEB");
    digitalWrite(buzzer,HIGH);      // 1 BEEPS INDICAM PARTIDA
    delay(1500);
    digitalWrite(buzzer,LOW);
    delay(1000);      
    digitalWrite(partida, LOW);
    delay(1000);
  }
  if(my_payload == "a"){
    client.publish("QTA_IoT_Envia status_gerador", String("Desligando Gerador").c_str()); //verificar qual valor retorna se der errado retire a função c_str
    digitalWrite(releger, LOW);
    endtime = millis();
    elapsedtime += endtime - starttime;
    Serial.println("DESLIGANDO GERADOR");
    i = 0;
  }
}