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
  if(digitalRead(man) == HIGH & digitalRead(redeon) != LOW){
  if(my_payload == "A"){
    client.publish("QTA_IoT_Envia status_gerador", String("Ligando Gerador").c_str());
    digitalWrite(partida, HIGH);
    Serial.println("TENTANDO DAR PARTIDA VIA WEB");
    digitalWrite(buzzer,HIGH);      // 1 BEEPS INDICAM PARTIDA
    delay(1500);
    digitalWrite(buzzer,LOW);
    delay(1000);      
    digitalWrite(partida, LOW);
    delay(1000);
     if (digitalRead(ger_on) != HIGH) {
      digitalWrite(releger, HIGH);   // LIGA RELE DO GERADOR
        digitalWrite(buzzer,HIGH);     
        delay(100);
        digitalWrite(buzzer,LOW);
        delay(100);
        count++;
        starttime = millis();
        i++;
        j = 0;
        client.publish("QTA_IoT_Envia_contagem", String(count).c_str());  
      }
      Serial.println("GERADOR ON VIA WEB");
      client.publish("QTA_IoT_Envia_status_gerador", String("Gerador Ligado").c_str());
      client.publish("QTA_IoT_Envia_tempo", String("Aguardando gerador desligar para contabilizar").c_str());  
    }
    my_payload ="b";
  }
  if(my_payload == "a"){
    client.publish("QTA_IoT_Envia status_gerador", String("Desligando Gerador").c_str()); 
    digitalWrite(releger, LOW);
    digitalWrite(buzzer,HIGH);      // 4 BEEPS INDICAM SEM REDE
      delay(100);
      digitalWrite(buzzer,LOW);
      delay(100);
      digitalWrite(buzzer,HIGH);      // 4 BEEPS INDICAM SEM REDE
      delay(100);
      digitalWrite(buzzer,LOW);
      delay(100);
      digitalWrite(buzzer,HIGH);      // 4 BEEPS INDICAM SEM REDE
      delay(100);
      digitalWrite(buzzer,LOW);
      delay(100);
    endtime = millis();
    elapsedtime += endtime - starttime;
    Serial.println("DESLIGANDO GERADOR");
    i = 0;
    my_payload ="b";
  }
  }
