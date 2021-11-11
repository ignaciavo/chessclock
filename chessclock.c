const int clockPin = 7;    
const int latchPin = 8;    
const int dataPin = 12;    
const int digit[4] = {128,256,512,1024};
const int number[10] = {64, 121, 36, 48, 25, 18, 2, 120, 0, 24}; //numeros binarios en decimal para anodo comun
int estado1 = LOW;
int estado2= LOW;
int i=0, j=0, k=0;
int a=0, b=0, c=0;
int play1[5] = {0,0,0,0,0};
int play2[5] = {0,0,0,0,0};

void setup(){               
  //Init
  pinMode(2, INPUT);
  pinMode(3, INPUT);
  pinMode(1, OUTPUT);
  pinMode(13, OUTPUT);
  pinMode(0, OUTPUT);
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT); 
}

void player1(int v1, int v2, int v3, int v4, int v5) {
  
  v4= play1[3];
  v5=play1[4];    
     for (k=v1;k<5;k++){
        for(i=v2;i<6;i++){
            for (j=v3;j<10;j++){

                //segundos(unidades)
                digitalWrite(latchPin, LOW);
                shiftOut(dataPin, clockPin, MSBFIRST, number[j]+digit[0] >>7);
                shiftOut(dataPin, clockPin, MSBFIRST, number[j]+digit[0]);
                digitalWrite(latchPin, HIGH);
                delay(15);
                
                //segundos(decenas)
                digitalWrite(latchPin, LOW);
                shiftOut(dataPin, clockPin, MSBFIRST, number[i]+digit[1] >>7);
                shiftOut(dataPin, clockPin, MSBFIRST, number[i]+digit[1]);
                digitalWrite(latchPin, HIGH);
                delay(15);
                
                //minutos(unidades)
                digitalWrite(latchPin, LOW);
                shiftOut(dataPin, clockPin, MSBFIRST, number[k]+digit[2] >>7);
                shiftOut(dataPin, clockPin, MSBFIRST, number[k]+digit[2]);
                digitalWrite(latchPin, HIGH);
                delay(15);
                
                //minutos(decenas) se dejan en 0 porque el conteo es hasta los 5min
                digitalWrite(latchPin, LOW);
                shiftOut(dataPin, clockPin, MSBFIRST, number[0]+digit[3] >>7);
                shiftOut(dataPin, clockPin, MSBFIRST, number[0]+digit[3]);
                digitalWrite(latchPin, HIGH);
                delay(15);
               
                
                estado1= digitalRead(2);
                estado2= digitalRead(3);
                if( estado2 == HIGH){
                    play1[0]=k;
                    play1[1]=i;
                    play1[2]=j;
                    return ;
                }
                if (j==9){
                    if (play1[3]==0){
                        play1[3]=1;
                        play1[2]=0;
                        player1(play1[0],play1[1],play1[2], play1[3], play1[4]);
                    }
                }
            }
            if (i==5){
                if (play1[4]==0){
                    play1[4]=1;
                    play1[1]=0;
                    player1(play1[0],play1[1],play1[2],play1[3], play1[4]);
                }
            }
        }
     }
}

void player2(int b1, int b2, int b3, int b4, int b5) {

   b4= play2[3];
   b5= play2[4]; 
     for (c=b1;c<5;c++){
        for(b=b2;b<6;b++){
            for (a=b3;a<10;a++){

            //segundos(unidades)
            digitalWrite(latchPin, LOW);
            shiftOut(dataPin, clockPin, MSBFIRST, number[a]+digit[0] >>7);
            shiftOut(dataPin, clockPin, MSBFIRST, number[a]+digit[0]);
            digitalWrite(latchPin, HIGH);
            delay(15);
            
            //segundos(decenas)
            digitalWrite(latchPin, LOW);
            shiftOut(dataPin, clockPin, MSBFIRST, number[b]+digit[1] >>7);
            shiftOut(dataPin, clockPin, MSBFIRST, number[b]+digit[1]);
            digitalWrite(latchPin, HIGH);
            delay(15);
            
            //minutos(unidades)
            digitalWrite(latchPin, LOW);
            shiftOut(dataPin, clockPin, MSBFIRST, number[c]+digit[2] >>7);
            shiftOut(dataPin, clockPin, MSBFIRST, number[c]+digit[2]);
            digitalWrite(latchPin, HIGH);
            delay(15);
            
            //se dejan en 0 porque el conteo es hasta los 5min
            digitalWrite(latchPin, LOW);
            shiftOut(dataPin, clockPin, MSBFIRST, number[0]+digit[3] >>7);
            shiftOut(dataPin, clockPin, MSBFIRST, number[0]+digit[3]);
            digitalWrite(latchPin, HIGH);
            delay(15);

                estado1= digitalRead(2);
                estado2= digitalRead(3);
                if( estado1 == HIGH){
                    play2[0]=c;
                    play2[1]=b;
                    play2[2]=a;
                  return;
                }
                if (a==9){
                    if (play2[3]==0){
                        play2[3]=1;
                        play2[2]=0;
                        player2(play2[0],play2[1],play2[2], play2[3], play2[4]);
                    }
                }
            }
            if (b==5){
                    if (play2[4]==0){
                        play2[4]=1;
                        play2[1]=0;
                        player2(play2[0],play2[1],play2[2], play2[3], play2[4]);
                    }
                }
                
        }
     }
}


void loop() {
    estado1= digitalRead(2); // lee el estado del Boton
    estado2=digitalRead(3);
    if (estado1 == HIGH) {
        digitalWrite(1, HIGH); 
        digitalWrite(0, LOW);
        digitalWrite(13, LOW); 
        player1(play1[0], play1[1], play1[2],play1[3],play1[4]);
        play1[3] = 0;
        play1[4] = 0;

    } else if (estado2 == HIGH) {
        digitalWrite(13, HIGH); 
        digitalWrite(0, LOW);
        digitalWrite(1, LOW); 
        player2(play2[0], play2[1], play2[2], play2[3], play2[4]);
        play2[3] = 0;
        play2[4] = 0;
    } else {
      digitalWrite(0, HIGH);
      digitalWrite(1, LOW);
      digitalWrite(13, LOW);
      digitalWrite(latchPin, LOW);
      shiftOut(dataPin, clockPin, MSBFIRST, number[0]+digit[0] >>7);
      shiftOut(dataPin, clockPin, MSBFIRST, number[0]+digit[0]);
      digitalWrite(latchPin, HIGH);
      delay(10);

      digitalWrite(latchPin, LOW);
      shiftOut(dataPin, clockPin, MSBFIRST, number[0]+digit[1] >>7);
      shiftOut(dataPin, clockPin, MSBFIRST, number[0]+digit[1]);
      digitalWrite(latchPin, HIGH);
      delay(10);

      digitalWrite(latchPin, LOW);
      shiftOut(dataPin, clockPin, MSBFIRST, number[0]+digit[2] >>7);
      shiftOut(dataPin, clockPin, MSBFIRST, number[0]+digit[2]);
      digitalWrite(latchPin, HIGH);
      delay(10);

      digitalWrite(latchPin, LOW);
      shiftOut(dataPin, clockPin, MSBFIRST, number[0]+digit[3] >>7);
      shiftOut(dataPin, clockPin, MSBFIRST, number[0]+digit[3]);
      digitalWrite(latchPin, HIGH);
      delay(10);
    }
  
    delay(15);
  
}