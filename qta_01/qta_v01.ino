#define redeon 13 
#define releger 27
#define relerede 14 
#define desliga_ger 33 
#define liga_ger 25
#define autom 12 
#define man 26


void setup() { 

  pinMode(releger, OUTPUT); 
  pinMode(relerede, OUTPUT); 
  pinMode(redeon, INPUT); 
  pinMode(autom, INPUT); 
  pinMode(man, INPUT); 
  pinMode(desliga_ger, INPUT); 
  pinMode(liga_ger, INPUT); 
  Serial.begin(9600); 
  int i;

} 

void manual(){ 

  if(digitalRead(redeon) == LOW){  //REDE DESLIGADA 
  digitalWrite(relerede,LOW);    //DESLIGA RELE DA REDE  
      if(digitalRead(releger) == HIGH){    //GERADOR JÁ ESTA LIGADO  
      Serial.println("GERADOR LIGADO"); 
  } 
        if(digitalRead(releger) == LOW){ //GERADOR DESLIGADO  
          Serial.println("(MODO MANUAL)SEM REDE LIGUE O GERADOR"); // AGUARDA A OPERAÇÃO MANUAL 
          if(digitalRead(liga_ger) == HIGH){ // BOTÃO DE LIGA GERADOR 
          digitalWrite(releger, HIGH); 

    } 
  } 
              if(digitalRead(desliga_ger) == HIGH){  //BOTÃO DE DESLIGA GERADOR 
              digitalWrite(releger,LOW); 
              Serial.println("DESLIGANDO GERADOR");  
  } 
  } 
  if(digitalRead(redeon)== HIGH){   //REDE LIGADA 
  digitalWrite(relerede, HIGH);    //LIGA RELE DA REDE 
  Serial.println("APENAS REDE LIGADA"); 
        if(digitalRead(liga_ger) == HIGH){ // BOTÃO DE LIGA GERADOR 
        digitalWrite(releger, HIGH); 
    } 
         if(digitalRead(releger) == HIGH){   //GERADOR LIGADO 
         Serial.println("GERADOR E REDE OPERANDO JUNTOS DESLIGUE O GERADOR");  
  }  
            if(digitalRead(desliga_ger) == HIGH){  //BOTÃO DE DESLIGA GERADOR 
            digitalWrite(releger,LOW); 
            Serial.println("DESLIGANDO GERADOR, APENAS REDE LIGADA"); 
  } 
} 
} 

void automatico(){ 
    if(digitalRead(redeon) == LOW){  //REDE DESLIGADA 
      digitalWrite(releger, HIGH);   // LIGA GERADOR 
      digitalWrite(relerede, LOW);    // TIRA REDE 
      Serial.println("AUTO GERADOR ON"); 
    }
    if(digitalRead(redeon) == HIGH){  //REDE LIGADA 
    digitalWrite(relerede, HIGH);     //LIGA REDE  
    digitalWrite(releger, LOW);       //TIRA GERADOR 
    Serial.println("AUTO REDE ON"); 
    } 
} 
void loop() { 
  if(digitalRead(autom)== HIGH){ 
  automatico(); 
  delay(1000); 
  } 
  if(digitalRead(man) == HIGH){ 
  manual(); 
  delay(1000); 
  } 
} 