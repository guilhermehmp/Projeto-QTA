void manual() {
  //=============================== (MODO MANUAL) REDE DESLIGADA ======================================================
  if (digitalRead(redeon) != LOW) {  // REDE DESLIGADA
    digitalWrite(relerede, LOW);  // DESLIGA RELE DA REDE
    if (aux == 0) {
      client.publish("QTA_IoT_Envia_status_rede", String("Rede Desligada").c_str()); //verificar qual valor retorna se der errado retire a função c_str
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
      digitalWrite(buzzer,HIGH);      // 4 BEEPS INDICAM SEM REDE
      delay(100);
      digitalWrite(buzzer,LOW);
      delay(100);
      aux1 = 0;
      aux++;
      i = 0;
      delay(1000);
    }
    if (digitalRead(ger_on) != LOW) {  // GERADOR DESLIGADO
      Serial.println("(MODO MANUAL) - SEM REDE, LIGUE O GERADOR"); // AGUARDA A OPERAÇÃO MANUAL
      client.publish("QTA_IoT_Envia_status_rede", String("Rede Desligada").c_str()); 
      client.publish("QTA_IoT_Envia_status_gerador", String("Gerador Desligado").c_str()); 
      if (digitalRead(liga_ger) == HIGH) { // BOTÃO DE LIGA GERADOR
        digitalWrite(partida, HIGH);
        client.publish("QTA_IoT_Envia_status_gerador", String("Partindo Gerador").c_str()); 
        Serial.println("TENTANDO DAR PARTIDA");
        digitalWrite(buzzer,HIGH);      // 1 BEEPS INDICAM PARTIDA
        delay(1500);
        digitalWrite(buzzer,LOW);
        delay(1000);      
        digitalWrite(partida, LOW);
        delay(1000);
        if (digitalRead(ger_on) != HIGH) {
          digitalWrite(releger, HIGH);
          client.publish("QTA_IoT_Envia_status_rede", String("Rede Desligada").c_str()); 
          client.publish("QTA_IoT_Envia_status_gerador", String("Gerador Ligado").c_str());
          Serial.println("GERADOR LIGADO");
          if (i == 0) {
            digitalWrite(buzzer,HIGH);     
            delay(100);
            digitalWrite(buzzer,LOW);
            delay(100);
            count++;
            starttime = millis();
            i++;
            client.publish("QTA_IoT_Envia_contagem", String(count).c_str()); 
          }
        }
      }
    }
    if (digitalRead(desliga_ger) == HIGH) { // BOTÃO DE DESLIGA GERADOR
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
      client.publish("QTA_IoT_Envia_tempo", String(elapsedtime/1000).c_str()); 
    }
  }
  //=============================== (MODO MANUAL) REDE LIGADA ======================================================
  if (digitalRead(redeon) != HIGH) {   // REDE LIGADA
    digitalWrite(relerede, HIGH);  // LIGA RELE DA REDE
    Serial.println("(MODO MANUAL) - REDE LIGADA");
    client.publish("QTA_IoT_Envia_status_rede", String("Rede Ligada").c_str()); 
    digitalWrite(releger, LOW);  // LIGA RELE DA REDE
    client.publish("QTA_IoT_Envia_status_gerador", String("Gerador Desligado").c_str());
    if (aux1 == 0) {
      digitalWrite(buzzer,HIGH);      // 2 BEEPS INDICAM LIGA REDE
      delay(100);
      digitalWrite(buzzer,LOW);
      delay(100);
      digitalWrite(buzzer,HIGH);      // 2 BEEPS INDICAM LIGA REDE
      delay(100);
      digitalWrite(buzzer,LOW);
      delay(100);
      aux = 0;
      i = 0;
      aux1++;
      delay(1000);
    }
  if(digitalRead(ger_on) != HIGH){
     digitalWrite(buzzer,HIGH);
      digitalWrite(alert_ger,HIGH);
      delay(100);
      digitalWrite(alert_ger,LOW);
      digitalWrite(buzzer,LOW);
      delay(100);
      digitalWrite(alert_ger,HIGH); 
      digitalWrite(buzzer,HIGH);
      delay(100);
      digitalWrite(alert_ger,LOW);
      digitalWrite(buzzer,LOW);
      delay(100);
      client.publish("QTA_IoT_Envia_status_gerador", String("Gerador nao desligou verificar").c_str());
  }
  }
}