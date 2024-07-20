void manual() {
  //=============================== (MODO MANUAL) REDE DESLIGADA ======================================================
  if (digitalRead(redeon) == LOW) {  // REDE DESLIGADA
    digitalWrite(relerede, LOW);  // DESLIGA RELE DA REDE
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
      i = 0;
      delay(1000);
    }
    if (digitalRead(ger_on) == HIGH) {  // GERADOR JÁ ESTÁ LIGADO
      Serial.println("GERADOR LIGADO");
    }
    if (digitalRead(ger_on) == LOW) {  // GERADOR DESLIGADO
      Serial.println("(MODO MANUAL) - SEM REDE, LIGUE O GERADOR"); // AGUARDA A OPERAÇÃO MANUAL
      if (digitalRead(liga_ger) == HIGH) { // BOTÃO DE LIGA GERADOR
        digitalWrite(partida, HIGH);
        Serial.println("TENTANDO DAR PARTIDA");
        digitalWrite(buzzer,HIGH);      // 1 BEEPS INDICAM PARTIDA
        delay(1500);
        digitalWrite(buzzer,LOW);
        delay(1000);      
        digitalWrite(partida, LOW);
        delay(1000);
        if (digitalRead(ger_on) == HIGH) {
          digitalWrite(releger, HIGH);
          if (i == 0) {
            count++;
            starttime = millis();
            i++;
          }
        }
      }
    }
    if (digitalRead(desliga_ger) == HIGH) { // BOTÃO DE DESLIGA GERADOR
      digitalWrite(releger, LOW);
      endtime = millis();
      elapsedtime += endtime - starttime;
      Serial.println("DESLIGANDO GERADOR");
      i = 0;
    }
  }
  //=============================== (MODO MANUAL) REDE LIGADA ======================================================
  if (digitalRead(redeon) == HIGH) {   // REDE LIGADA
    digitalWrite(relerede, HIGH);  // LIGA RELE DA REDE
    Serial.println("(MODO MANUAL) - REDE LIGADA");
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
    if (digitalRead(liga_ger) == HIGH) { // BOTÃO DE LIGA GERADOR
      digitalWrite(partida, HIGH);
      Serial.println("TENTANDO DAR PARTIDA");
      digitalWrite(buzzer,HIGH);      // 1 BEEPS INDICAM PARTIDA
      delay(1500);
      digitalWrite(buzzer,LOW);
      delay(1000);
      digitalWrite(partida, LOW);
      delay(1000);
    }
    if (digitalRead(ger_on) == HIGH) {
      digitalWrite(releger, HIGH);
      if (i == 0) {
        count++;
        starttime = millis();
        i++;
      }
      Serial.println("GERADOR E REDE OPERANDO JUNTOS, DESLIGUE O GERADOR");
    }
    if (digitalRead(desliga_ger) == HIGH) { // BOTÃO DE DESLIGA GERADOR
      digitalWrite(releger, LOW);
      endtime = millis();
      elapsedtime += endtime - starttime;
      Serial.println("DESLIGANDO GERADOR, APENAS REDE LIGADA");
      i = 0;
    }
  }
}