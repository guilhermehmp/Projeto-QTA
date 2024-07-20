void automatico() {
  //============================== (MODO AUTO) REDE DESLIGADA ======================================================
  while (digitalRead(redeon) != LOW & i < 3) {
    delay(1000);
    i++;
    j = 0;
    Serial.println("VERIFICANDO FALHA NA REDE OU FALTA DE ENERGIA");
    client.publish("QTA_IoT_Envia_status_rede", String("Verificando falha na rede ou falta de energia").c_str());  
    delay(1000);
  }
  if (digitalRead(redeon) != LOW) {  // REDE DESLIGADA
    digitalWrite(relerede, LOW);  // TIRA RELE DA REDE
    client.publish("QTA_IoT_Envia_status_rede", String("Rede Desligada").c_str());
    if (aux == 0) {
      client.publish("QTA_IoT_Envia_status_rede", String("Rede Desligada").c_str());  
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
      delay(1000);
    }
    while (digitalRead(ger_on) != LOW & digitalRead(releger) == LOW & j < 3) {
      j++;
      Serial.print(j);
      Serial.println("x PARTIDA NO GERADOR");
      client.publish("QTA_IoT_Envia_status_gerador", String("Ligando Gerador partida automatica").c_str());  
      digitalWrite(partida, HIGH);
      digitalWrite(buzzer,HIGH);      // 1 BEEPS INDICAM PARTIDA
      delay(1500);
      digitalWrite(buzzer,LOW);
      delay(1500);
      digitalWrite(partida, LOW);
      delay(1000);    
    }
    if (digitalRead(ger_on) != HIGH) {
      digitalWrite(releger, HIGH);   // LIGA RELE DO GERADOR
      if (i == 3) {
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
      Serial.println("AUTO GERADOR ON");
      client.publish("QTA_IoT_Envia_status_gerador", String("Gerador Ligado").c_str());
      client.publish("QTA_IoT_Envia_tempo", String("Aguardando gerador desligar para contabilizar").c_str());  
    } else {
      if(j<=6){
      delay(1000);
      j++;
      client.publish("QTA_IoT_Envia_status_gerador", String("!!! Atenção Gerador Não ligou Verificar !!! ").c_str());  
      Serial.println("!!! ATENCAO, GERADOR NAO LIGOU VERIFICAR OU NAO ESTA ALIMENTANDO O SISTEMA !!!");
      digitalWrite(alert_ger, HIGH);
      digitalWrite(buzzer,HIGH);      // 1 BEEPS INDICAM GER NAO LIGOU
      delay(1500);
      digitalWrite(buzzer,LOW);
      delay(100);
      digitalWrite(alert_ger, LOW);
      delay(500);
      }else{
      client.publish("QTA_IoT_Envia_status_gerador", String("!!! Gerador não ligou na partida automatica  !!! ").c_str());  
      Serial.println("GERADOR NAO LIGOU NA PARTIDA AUTOMATICA VERIFIQUE");
      Serial.println("SE FOR O CASO MUDE A CHAVE PARA MANUAL E LIGUE MANUALMENTE");
      digitalWrite(alert_ger, HIGH);
      delay(1000);
      digitalWrite(alert_ger, LOW);
      delay(1000);
      }
    }
  }
  //============================== (MODO AUTO) REDE LIGADA ======================================================
  if (digitalRead(redeon) != HIGH) {  // REDE LIGADA
    digitalWrite(releger, LOW);   // TIRA O RELE DO GERADOR
    client.publish("QTA_IoT_Envia_status_rede", String("Rede Ligada").c_str());  
    if (aux1 == 0) {
      client.publish("QTA_IoT_Envia_status_rede", String("Rede Ligada").c_str());  
      digitalWrite(buzzer,HIGH);      // 2 BEEPS INDICAM LIGA REDE
      delay(100);
      digitalWrite(buzzer,LOW);
      delay(100);
      digitalWrite(buzzer,HIGH);      // 2 BEEPS INDICAM LIGA REDE
      delay(100);
      digitalWrite(buzzer,LOW);
      delay(100);
      aux = 0;
      aux1++;
      i = 0;
      delay(1000);
      client.publish("QTA_IoT_Envia_status_gerador", String("Gerador Desligado").c_str());  
    }
    Serial.println("AUTO REDE ON");
    delay(1500);
    digitalWrite(relerede, HIGH);   // LIGA RELE DA REDE
    if (j == 0) {
      endtime = millis();
      elapsedtime += endtime - starttime;
      j++;
      client.publish("QTA_IoT_Envia_tempo", String(elapsedtime/1000).c_str());  
    }
    if(digitalRead(ger_on) != HIGH){ //GERADOR PERMANECEU LIGADO
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