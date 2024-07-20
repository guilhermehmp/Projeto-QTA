// veriricar buzzer e depois ver para integrar na web
#define redeon 13
#define releger 7
#define relerede 8
#define desliga_ger 10
#define liga_ger 9
#define autom 12
#define man 11
#define partida 6
#define ger_on 5
#define buzzer 4
int i,j,b1,b2= 0;

void setup() {
  pinMode(releger, OUTPUT);
  pinMode(relerede, OUTPUT);
  pinMode(redeon, INPUT);
  pinMode(autom, INPUT);
  pinMode(man, INPUT);
  pinMode(desliga_ger, INPUT);
  pinMode(liga_ger, INPUT);
  pinMode(ger_on, INPUT);
  pinMode(buzzer, OUTPUT);
  Serial.begin(115200);
}


void manual(){
//=============================== (MODO MANUAL) REDE DESLIGADA ======================================================
   if(digitalRead(redeon) == LOW){  //REDE DESLIGADA
   digitalWrite(relerede,LOW);    //DESLIGA RELE DA REDE 
   if(b1==0){
    tone(buzzer,400,75);			  //4 BEEPS INDICAM SEM REDE
    delay(500);
    tone(buzzer,400,75);
    delay(500);
    tone(buzzer,400,75);			  
    delay(500);
    tone(buzzer,400,75);
    b2=0;
    b1++;
    }
      if(digitalRead(ger_on) == HIGH){    //GERADOR JÁ ESTA LIGADO 
      Serial.println("GERADOR LIGADO");
  		}
       if(digitalRead(ger_on) == LOW){ //GERADOR DESLIGADO 
       Serial.println("(MODO MANUAL)- SEM REDE LIGUE O GERADOR"); // AGUARDA A OPERAÇÃO MANUAL
       if(digitalRead(liga_ger) == HIGH){ // BOTÃO DE LIGA GERADOR
       digitalWrite(partida, HIGH);
       delay(3000);
       Serial.println("TENTANDO DAR PARTIDA");
       digitalWrite(partida, LOW);
       delay(1000);
         if(digitalRead(ger_on) == HIGH){
       	digitalWrite(releger, HIGH);
      }
    }
  }
       if(digitalRead(desliga_ger) == HIGH){  //BOTÃO DE DESLIGA GERADOR
       digitalWrite(releger,LOW);
       Serial.println("DESLIGANDO GERADOR"); 
  }
  }
  //=============================== (MODO MANUAL)REDE LIGADA ======================================================
  if(digitalRead(redeon)== HIGH){   //REDE LIGADA
  digitalWrite(relerede, HIGH);    //LIGA RELE DA REDE
  Serial.println("(MODO MANUAL)- REDE LIGADA");
  if(b2==0){
  tone(buzzer,400,50);			  //2 BEEPS INDICAM REDE LIGADA
  delay(500);
  tone(buzzer,400,50);
  b1=0;
  b2++;  
  }
        if(digitalRead(liga_ger) == HIGH){ // BOTÃO DE LIGA GERADOR
        digitalWrite(partida, HIGH);
        delay(3000);
        Serial.println("TENTANDO DAR PARTIDA");
        tone(buzzer,400,300);
      	delay(500);
        digitalWrite(partida, LOW);
        delay(1000);
        }
    	if(digitalRead(ger_on) == HIGH){
        digitalWrite(releger, HIGH);
        Serial.println("GERADOR E REDE OPERANDO JUNTOS DESLIGUE O GERADOR");
        }
    } 
          if(digitalRead(desliga_ger) == HIGH){  //BOTÃO DE DESLIGA GERADOR
          digitalWrite(releger,LOW);
          Serial.println("DESLIGANDO GERADOR, APENAS REDE LIGADA");
  }
}

void automatico(){
//============================== (MODO AUTO)REDE DESLIGADA ======================================================
  while(digitalRead(redeon) == LOW & i<3){ 
   delay(1000);
   i++;
   Serial.println("VERIFICANDO FALHA NA REDE OU FALTA DE ENERGIA");
  }
   if(digitalRead(redeon) == LOW){  //REDE DESLIGADA
    digitalWrite(relerede, LOW);    // TIRA RELE DA REDE
    if(b1==0){
    tone(buzzer,400,75);			  //4 BEEPS INDICAM SEM REDE
    delay(500);
    tone(buzzer,400,75);
    delay(500);
    tone(buzzer,400,75);			  
    delay(500);
    tone(buzzer,400,75);
    b2=0;
    b1++;
    }
     while(digitalRead(ger_on) == LOW & j<3){
      digitalWrite(partida, HIGH);
      delay(3000);
      digitalWrite(partida, LOW);
      j++;
      Serial.print(j);
      Serial.println("x PARTIDA NO GERADOR");
      tone(buzzer,400,300);
      delay(500);
     }
     if(digitalRead(ger_on) == HIGH){
      digitalWrite(releger, HIGH);   // LIGA RELE DO GERADOR
      Serial.println("AUTO GERADOR ON");
     }else{
      Serial.println("!!! ATENCAO GERADOR NAO LIGOU VERIFICAR !!!");
      tone(buzzer,400,1000);
      delay(5000);
     }
    }
//============================== (MODO AUTO)REDE LIGADA ======================================================
    if(digitalRead(redeon) == HIGH){  //REDE LIGADA
    digitalWrite(relerede, HIGH);     //LIGA RELE DA REDE
    Serial.println("AUTO REDE ON");
    i,j=0;
    delay(3000);   
    digitalWrite(releger, LOW);       //TIRA O RELE DO GERADOR
    if(b2==0){
    tone(buzzer,400,50);			  //2 BEEPS INDICAM REDE LIGADA
    delay(500);
    tone(buzzer,400,50);
    b1=0;
    b2++;  
    }
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