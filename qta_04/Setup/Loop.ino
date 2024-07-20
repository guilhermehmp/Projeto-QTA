void loop() {
  if (digitalRead(emergencia) == HIGH){
  	if (digitalRead(autom) == HIGH) {
     automatico();
     delay(1000);
     Serial.println("----------------------------------------------");
     Serial.print("QUANTIDADE DE ACIONAMENTOS DO GERADOR = ");
     Serial.print(count);
     Serial.println("x");
     Serial.print("E O TEMPO TOTAL QUE ELE FICOU ACIONADO FOI = ");
     Serial.print(elapsedtime / 1000);
     Serial.println("s");
     Serial.println("----------------------------------------------");
  }
  	if (digitalRead(man) == HIGH) {
   	 manual();
     delay(1000);
     Serial.println("----------------------------------------------");
     Serial.print("QUANTIDADE DE ACIONAMENTOS DO GERADOR = ");
     Serial.print(count);
     Serial.println("x");
     Serial.print("E O TEMPO TOTAL QUE ELE FICOU ACIONADO FOI = ");
     Serial.print(elapsedtime / 1000);
     Serial.println("s");
     Serial.println("----------------------------------------------");
  }
}
  if (digitalRead(emergencia) == LOW){
    digitalWrite(relerede, LOW);
    digitalWrite(releger, LOW);
   	Serial.println("BOTAO DE EMERGENCIA PRESSIONADO");
    Serial.println("SISTEMA INOPERANTE");
    delay(1000);
  }
}