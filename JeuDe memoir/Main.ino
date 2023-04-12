#include <LiquidCrystal.h>
#include <EEPROM.h>

int Rouge =0;
int Vert=1;
int Bleu=2;
int Jaune=3;
int ledVies1=13;
int ledVies2=A0;

int seconds = 0;

LiquidCrystal lcd(10, 11, 6, 8, 9, 12);

int BUT_RED = A5;
int BUT_G = A4;
int BUT_AZ = A3;
int BUT_AM = A2;

int BUZZ = 7;
int pot=A1;
int valor_pot;

int NUMS[]={2,3,4,5};
const int Maximum = 30;
int Sec[Maximum];
int augmenter=0;
int GenerarSec=0;
int remise_a_zero=0;
int comparateur=0;

int Vies=3;

int record;



void setup()
{
  pinMode(pot,INPUT);
  lcd.begin(16, 2);
  Serial.begin(9600);
  
  pinMode(BUT_RED, OUTPUT);
  
  pinMode(BUT_G, OUTPUT);
  
  pinMode(BUT_AZ, OUTPUT);
  
  pinMode(BUT_AM, OUTPUT);

   digitalWrite(ledVies1, HIGH);
   digitalWrite(ledVies2, HIGH);
  int check=EEPROM.read(1);
  
   if(check != 100 )
   {
      EEPROM.write(1,100); 
      EEPROM.write(2,0); 
   }
record=  EEPROM.read(2); 

}
//Crear secuencia desde el inicio 
void secuencias()
{
  
  
  
  
  remise_a_zero=0;
  comparateur=0;

  
  delay(1000);
  
  for(int S = 0; S < augmenter+1; S++){
      digitalWrite(NUMS[Sec[S]], HIGH);
    
    if(NUMS[Sec[S]]==2){tone(BUZZ, 500);}
    if(NUMS[Sec[S]]==3){tone(BUZZ, 400);}
    if(NUMS[Sec[S]]==4){tone(BUZZ, 300);}
    if(NUMS[Sec[S]]==5){tone(BUZZ, 200);}
    delay(300);
    noTone(BUZZ);
    delay(valor_pot);
    digitalWrite(NUMS[Sec[S]], LOW);
    
    delay(400/augmenter+1);
      }
  
  augmenter++;
}

void GenerarS(){
  GenerarSec=1;
  
  
  randomSeed(analogRead(A0)); //Cambiar el random
    for(int S = 0; S < Maximum; S++){
      Sec[S] = random(0,4);
      Serial.println(Sec[S]); 
      }
    }

void loop()
{
  
 	valor_pot=analogRead(A1);
  //analogWrite(valor_pot,constrain(analogRead(pot),0,250));
  Serial.println(valor_pot);
  lcd.clear();
  lcd.print("niveau: ");
  lcd.print(augmenter);
  lcd.setCursor(0,1);
  lcd.print(Vies);
  lcd.print(" vie");
  lcd.print(" record: ");
  lcd.print(EEPROM.read(2));

  
  if(digitalRead(BUT_RED) == HIGH)
  {
    digitalWrite(NUMS[Rouge], HIGH);

    if(0==Sec[remise_a_zero]){
    comparateur++;
    tone(BUZZ, 500);
    remise_a_zero++;
    delay(200);
    noTone(BUZZ); 
    digitalWrite(NUMS[Rouge], LOW);
    }
    
    
    else{
      if (augmenter > record)
      {record = augmenter;EEPROM.write(2,record);}
    remise_a_zero=0;
    
      //reset
      Vies--;
        digitalWrite(ledVies1, LOW);
      if(Vies == 1){
      digitalWrite(ledVies2, LOW);
      }
     
     // comparateur=0;
    //augmenter=0;
    //GenerarSec=0;
      
      tone(BUZZ, 50);
      delay(500);
      noTone(BUZZ);
      digitalWrite(NUMS[Rouge], LOW);
      
     
    }
	
    
    
  } 
  //green
  if(digitalRead(BUT_G) == HIGH)
  {
    digitalWrite(NUMS[Vert], HIGH);
 
    if(1==Sec[remise_a_zero]){
    comparateur++;
    remise_a_zero++;
          tone(BUZZ, 400);
      delay(200);
    noTone(BUZZ);
      digitalWrite(NUMS[Vert], LOW);

    }
    else{
   if (augmenter > record)
      {record = augmenter;EEPROM.write(2,record);}
    //comparateur=0;
    //augmenter=0;
      Vies--;
      digitalWrite(ledVies1, LOW);
      if(Vies == 1){
      digitalWrite(ledVies2, LOW);
      }
    //GenerarSec=0;
      tone(BUZZ, 50);
      delay(500);
      noTone(BUZZ);
      digitalWrite(NUMS[Vert], LOW);
    }
    
  } 
  //Bleu
  if(digitalRead(BUT_AZ) == HIGH)
  {
    digitalWrite(NUMS[Bleu], HIGH);
  
    if(2==Sec[remise_a_zero]){
    comparateur++;
    remise_a_zero++;
          tone(BUZZ, 300);
      delay(200);
    noTone(BUZZ);
      digitalWrite(NUMS[Bleu], LOW);

    }
    else{
     if (augmenter > record)
      {record = augmenter;EEPROM.write(2,record);}
    remise_a_zero=0;
    //comparateur=0;
    //augmenter=0;
    //GenerarSec=0;
      Vies--;
      digitalWrite(ledVies1, LOW);
      if(Vies == 1){
      digitalWrite(ledVies2, LOW);
        }
      tone(BUZZ, 50);
      delay(500);
      noTone(BUZZ);
      digitalWrite(NUMS[Bleu], LOW);
    }
    
  } 
  //Jaune
  if(digitalRead(BUT_AM) == HIGH)
  {
    digitalWrite(NUMS[Jaune], HIGH);
   
    if(3==Sec[remise_a_zero]){
    comparateur++;
    remise_a_zero++;
          tone(BUZZ, 250);
      delay(200);
    noTone(BUZZ);
      digitalWrite(NUMS[Jaune], LOW);

    }
    else{
   if (augmenter > record)
      {record = augmenter;EEPROM.write(2,record);}
    remise_a_zero=0;
    //comparateur=0;
    //augmenter=0;
    //GenerarSec=0;
      Vies--;
      
      
      
      digitalWrite(ledVies1, LOW);
      if(Vies == 1){
      digitalWrite(ledVies2, LOW);
         }
      tone(BUZZ, 50);
      delay(500);
      noTone(BUZZ);
      digitalWrite(NUMS[Jaune], LOW);
      
      
      
    }
    
  } 
  
  if(Vies<=0)
  {
    perder();
  }
  
    if(GenerarSec==0){GenerarS(); }

  
  if(comparateur==augmenter){comparateur=0;secuencias();}
  delay(100);
}


void perder(){lcd.clear();
  lcd.print("niveau: ");
  lcd.print(augmenter);
  lcd.setCursor(0,1);
  lcd.print(Vies);
  lcd.print(" vie");
  lcd.print(" record: ");
  lcd.print(record);
    delay(500);
    lcd.clear();
      lcd.print("Tu as perdu");

    tone(BUZZ, 494);
  delay(300);
  tone(BUZZ, 466);
  delay(300);
  tone(BUZZ, 440);
  delay(300);
  tone(BUZZ, 415);
  delay(1000);
  noTone(BUZZ); 
    comparateur=0;
    augmenter=0;
    GenerarSec=0;
    Vies=3;digitalWrite(ledVies1, HIGH);
   digitalWrite(ledVies2, HIGH);
             }