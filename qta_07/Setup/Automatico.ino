void automatico() {
  //============================== (MODO AUTO) REDE DESLIGADA ======================================================
  while (digitalRead(redeon) == LOW & i < 3) {
    delay(1000);
    i++;
    j = 0;
    Serial.println("VERIFICANDO FALHA NA REDE OU FALTA DE ENERGIA");
    delay(1000);
  }
  if (digitalRead(redeon) == LOW) {  // REDE DESLIGADA
    digitalWrite(relerede, LOW);  // TIRA RELE DA REDE
    if (aux == 0) {
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
    while (digitalRead(ger_on) == LOW & digitalRead(releger) == LOW & j < 3) {
      j++;
      Serial.print(j);
      Serial.println("x PARTIDA NO GERADOR");
      digitalWrite(partida, HIGH);
      digitalWrite(buzzer,HIGH);      // 1 BEEPS INDICAM PARTIDA
      delay(1500);
      digitalWrite(buzzer,LOW);
      delay(1500);
      digitalWrite(partida, LOW);
      delay(1000);    
    }
    if (digitalRead(ger_on) == HIGH) {
      digitalWrite(releger, HIGH);   // LIGA RELE DO GERADOR
      if (i == 3) {
        count++;
        starttime = millis();
        i++;
        j = 0;
      }
      Serial.println("AUTO GERADOR ON");
    } else {
      if(j<=6){
      delay(1000);
      j++;
      Serial.println("!!! ATENCAO, GERADOR NAO LIGOU, VERIFICAR OU NAO ESTA ALIMENTANDO O SISTEMA !!!");
      digitalWrite(alert_ger, HIGH);
      digitalWrite(buzzer,HIGH);      // 1 BEEPS INDICAM GER NAO LIGOU
      delay(1500);
      digitalWrite(buzzer,LOW);
      delay(100);
      digitalWrite(alert_ger, LOW);
      delay(500);
      }else{
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
  if (digitalRead(redeon) == HIGH) {  // REDE LIGADA
    digitalWrite(relerede, HIGH);   // LIGA RELE DA REDE
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
      aux1++;
      i = 0;
      delay(1000);
    }
    Serial.println("AUTO REDE ON");
    delay(3000);
    digitalWrite(releger, LOW);   // TIRA O RELE DO GERADOR
    if (j == 0) {
      endtime = millis();
      elapsedtime += endtime - starttime;
      j++;
    }
  }
}


