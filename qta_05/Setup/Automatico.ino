void automatico() {
  //============================== (MODO AUTO) REDE DESLIGADA ======================================================
  while (digitalRead(redeon) == LOW & i < 3) {
    delay(1000);
    i++;
    j = 0;
    Serial.println("VERIFICANDO FALHA NA REDE OU FALTA DE ENERGIA");
  }
  if (digitalRead(redeon) == LOW) {  // REDE DESLIGADA
    digitalWrite(relerede, LOW);  // TIRA RELE DA REDE
    if (aux == 0) {
      tone(buzzer, 400, 75);      // 4 BEEPS INDICAM SEM REDE
      delay(500);
      tone(buzzer, 400, 75);
      delay(500);
      tone(buzzer, 400, 75);
      delay(500);
      tone(buzzer, 400, 75);
      aux1 = 0;
      aux++;
    }
    while (digitalRead(ger_on) == LOW & digitalRead(releger) == LOW & j < 3) {
      j++;
      Serial.print(j);
      Serial.println("x PARTIDA NO GERADOR");
      tone(buzzer, 400, 300);
      digitalWrite(partida, HIGH);
      delay(3000);
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
      delay(2000);
      tone(buzzer, 800, 1000);
      j++;
      Serial.println("!!! ATENCAO, GERADOR NAO LIGOU, VERIFICAR OU NAO ESTA ALIMENTANDO O SISTEMA !!!");
      digitalWrite(alert_ger, HIGH);
      delay(1000);
      digitalWrite(alert_ger, LOW);
      delay(1000);
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
      tone(buzzer, 400, 50);      // 2 BEEPS INDICAM REDE LIGADA
      delay(500);
      tone(buzzer, 400, 50);
      aux = 0;
      aux1++;
      i = 0;
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


