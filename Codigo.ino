#include <LiquidCrystal.h>   
#include <Keypad.h>
int a=0, b=0, c=0, d=0;
int var=0; 
int C1=1,C2=2,C3=3,C4=4; //aqui definimos la clave
char f='*';  
const byte filas = 4; //numero de filas.
const byte columnas = 4; //numero de colunas.
char tecla[filas][columnas] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

LiquidCrystal lcd(A1,A0,A2,12,11,10); //D7,D6,D4,E,RS

byte pinFilas[filas] = {9, 8, 7, 6}; //pines conectados a filas del keypad
byte pinColumnas[columnas] = {5, 4, 3, 2}; //pines conectados a columnas del keypad

Keypad keypad = Keypad( makeKeymap(tecla), pinFilas, pinColumnas, filas, columnas );

// se declara la variable para el proyecto
int sensorluz = 0; 
#define InSen  A5
#define OutSen 18
#define star 17

void setup(){
  Serial.begin(9600);
  lcd.begin(16, 2); 
  //Configuramos como salidas los pines donde se conectan los led
  pinMode(OutSen,   OUTPUT);
  pinMode(star, OUTPUT);
  
  /// Iniciamos las salidas en apagado
  digitalWrite(star,   LOW);
  digitalWrite(OutSen, LOW);
  
}

void loop(){
 

  //////// FUNCION CLAVE DE SEGURIDAD/////////////////
  FuncionClave();
  //////// FUNCION SENSOR DE LUZ/////////////////
  FuncionLuz();
  
}

/////////// VOID DE FUNCIONES DEL PROYECTO //////
void FuncionLuz(){
    ////////////////FUNCION SENSOR DE LUZ //////////// 
  // Guardamos el valor leido del ADC en una variable
  // El valor leido por el ADC (voltaje) aumenta de manera directamente proporcional
  // con respecto a la luz percibida por el LDR
  sensorluz = analogRead(InSen);
  // imprimimos el valor leido en monitor serial
  Serial.println(sensorluz);
  
  ///// CONDICION SI ES DE DIA O NOCHE ////
  if (sensorluz > 700)
    { 
     // se encienden las luces del carro 
      digitalWrite(OutSen, HIGH);
    
      //lcd.setCursor(9,2);          
      //lcd.print("LUZ:"); 
      //lcd.setCursor(13,2);           
      //lcd.print("ONN"); 
    } 
  else
    { 
    // se apagan las luces del carro
      digitalWrite(OutSen, LOW);
    
      //lcd.setCursor(9,2);          
      //lcd.print("LUZ:"); 
      //lcd.setCursor(13,2);           
      //lcd.print("OFF"); 
    }
}

void FuncionClave(){

  // Guardamos el valor de la techa precionada 
  // en variable key
  char key = keypad.getKey();
  
  if (key){
   lcd.setCursor(0,0),lcd.print("Inserte Password");
   lcd.setCursor(6+var,1);
   lcd.print(key),lcd.setCursor(6+var,1),lcd.print(f);
   key=key-48; //
   var++; 
   switch(var){
    case 1:
    a=key; //almacenar primer digito
    break;
    case 2:
    b=key; //almacenar segundo digito
    break;
    case 3:
    c=key; //almacenar tercer digito
    break;
    case 4:
    d=key; //almacenar cuarto digito
   delay(100);
  
     if(a==C1 && b==C2 && c==C3 && d==C4){
    lcd.clear();
    lcd.setCursor(4,0);
    lcd.print("Password");
    lcd.setCursor(4,1);
    lcd.print("Correcto");
    digitalWrite(star,HIGH);//LED Verde enciende
    delay(1000); 
    lcd.clear();
    lcd.setCursor(1,0);
    lcd.print("Puede Encender");
    lcd.setCursor(2,1);
    lcd.print("su vehiculo");
    delay(2000); 
    lcd.clear();
    }
  else{
    lcd.clear();
    lcd.setCursor(4,0);
    lcd.print("Password");
    lcd.setCursor(2,1);
    lcd.print("Incorrecto");
    digitalWrite(star,LOW); // con LOW led rojo encendido
    delay(1000);
    lcd.clear();
    lcd.setCursor(1,0);
    lcd.print("No puede iniciar");
    lcd.setCursor(2,1);
    lcd.print("su vehiculo");
    delay(2000); 
    lcd.clear();
    lcd.setCursor(5,0);
    lcd.print("intente");
    lcd.setCursor(4,1);
    lcd.print("otra vez");
    delay(2000); 
    lcd.clear();
    }
}
    if (var == 4){var=0;}
}
}
