void loop() {
  reconnect();
  client.loop();
  comando_mqtt();
  if (digitalRead(emergencia) == HIGH){
  	if (digitalRead(autom) == HIGH) {
     client.publish("QTA_IoT_Envia_modo", String("Automatico").c_str()); 
     automatico();
     delay(1000);
  }
  	if (digitalRead(man) == HIGH) {
     client.publish("QTA_IoT_Envia_modo", String("Manual").c_str());  
   	 manual();
     delay(1000);
  }
  client.publish("QTA_IoT_Envia_emergencia", String("...").c_str()); 
   Serial.println("----------------------------------------------");
     Serial.print("QUANTIDADE DE ACIONAMENTOS DO GERADOR = ");
     Serial.print(count);
     Serial.println("x");
     Serial.print("E O TEMPO TOTAL QUE ELE FICOU ACIONADO FOI = ");
     Serial.print(elapsedtime / 1000);
     Serial.println("s");
     Serial.println("----------------------------------------------");
    client.publish("QTA_IoT_Envia_contagem", String(count).c_str());  
    client.publish("QTA_IoT_Envia_tempo", String(elapsedtime/1000).c_str());  
}
  if (digitalRead(emergencia) == LOW){
    digitalWrite(relerede, LOW);
    digitalWrite(releger, LOW);
    client.publish("QTA_IoT_Envia_emergencia", String("!!! SISTEMA INOPERANTE !!!").c_str()); 
    client.publish("QTA_IoT_Envia_status_rede", String("Rede desligada pelo botão de emergencia ").c_str()); 
    client.publish("QTA_IoT_Envia_status_gerador", String("Gerador desligado pelo botão de emergencia ").c_str());
    client.publish("QTA_IoT_Envia_modo", String("!!! Botão de emergencia pressionado !!! ").c_str());  
    client.publish("QTA_IoT_Envia_contagem", String(count).c_str());  
    client.publish("QTA_IoT_Envia_tempo", String(elapsedtime/1000).c_str());   
   	Serial.println("BOTAO DE EMERGENCIA PRESSIONADO");
    Serial.println("SISTEMA INOPERANTE");
    delay(1000);
  }
}