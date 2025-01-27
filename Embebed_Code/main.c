#include <main.h>
#fuses XT, NOWDT,NOPROTECT,NOLVP
#include <HDM64GS12.c> //Manejo del display gr�fico
#include <graphics.c> //Funciones para dibujar y escribir en el display
#include <srcomLIB.c>

#byte trisb=0x86

///Defines

#define escala -2 //Escala negativa para que crezca hacia arriba.
#define limpiarGrafico limpiarPorcion(0,20,128,44) //Limpia el area del grafico
#define offset 120 //es el offset para la altura de la grafica
#define TMR1 0x0BDC //Este es el valor para 500ms en el timer1 (0,5s=(4/4000000)8(65536-TMR1))=>TMR1=3036
#define TMR0 0x40 //Este es el valor para 50ms en el timer0
#define nMediciones 80 //Numero de mediciones

///Fin Defines

///Variables Globales

int x=0; //Posicion inicial de x para graficar la temperatura
float y; //Temperatura anterior
float t; //Temperatura actual
int16 iAn; //Lectura del sensor de temperatura
int registro[nMediciones]; //registro de las ultimas nMediciones mediciones
int1 habilitarLectura=0; //Variable para habilitar o deshabilitar la captura de datos del sensor
int ciclos=10; //Variable que cuenta los ciclos que debe hacer el timer0 antes de ejecutar su codigo
int ciclosT1=6; //Variable que cuenta los ciclos que debe hacer el timer1 antes de ejecutar su codigo
short int btST = 0;
char r_;
///Fin Variables Globales

///Funciones

void limpiarPorcion(int x1, int y1, int x2, int y2){ //(x1, y1) = posici�n del primer pixel. (x2, y2) = cantididad de pixeles hacia la derecha y hacia abajo
   for(int i=x1;i<x1+x2;i++)
      for(int j=y1;j<y1+y2;j++)
         glcd_pixel(i, j, OFF); //Apagamos el pixel.
}

void nuevaLinea(float temp){ //Funcion para graficar las nuevas lineas de temperatura
   int x1=x+1;
   if(x1>=128){ //Revisamos si sobrepasamos el tama�o de la pantalla
      limpiarGrafico; //Limpiamos el area del grafico
      x=0;
      x1=1;
   }
   glcd_line(x, (y*escala)+offset, x1, (temp*escala)+offset, ON);   //multiplicamos por la escala para que la grafica entre en el area del grafico. El offset esta explicado arriba
   y=temp;
   x=x1;
}
void toggleBT(char c_) {
   if(c_ == 'a') {
      btST = !ON;
      glcd_text57(110,0,(char*)"BT",1,ON); //Mostramos BT
   }
   else if(c_ == 'i') {
      btST = !OFF;
      glcd_text57(110,0,(char*)"BT",1, OFF); //Apagamos BT
   }
}
///Fin Funciones

///Interrupciones

#INT_TIMER0
void TIMER0_isr(){ //Timer para hacer sonar el buzzer cada 500ms
   ciclos--;
   if(ciclos==0){
      ciclos=10;
      output_low(PIN_B3);
      delay_ms(50);
      output_high(PIN_B3);
   }
   set_timer0(TMR0);
}

#INT_TIMER1
void TIMER1_isr(){ //Timer para almacenar, en un array, la temepratura actual cada 3 segundos
   ciclosT1--;
   if(ciclosT1==0){
      ciclosT1=6;
      //Aca hay que hacer el guardado en sd
      //Con este bloque de codigo guardamos en un array las ultimas N mediciones
      //Las cuales podemos guardar despues donde querramos
      for(int i=0; i<nMediciones-1;i++)
         registro[i]=registro[i+1];
      registro[nMediciones-1]=iAn;
   }
   set_timer1(TMR1);
}

#INT_RB
void RB_isr(){ //Prueba de interrupciones
   if(input(PIN_B6)){ //Habilita o deshabilita la captura de datos
      habilitarLectura=~habilitarLectura;
      disable_interrupts(INT_TIMER0);
      if(habilitarLectura){
         glcd_text57(128/2-30, 0, (char*)"Capturando", 1, ON);
         sprintf(str, "%3.2fC", y);
         glcd_text57(12*6, 10, str, 1, ON); //Escribimos la temperatura.
         enable_interrupts(INT_TIMER1);
         set_timer1(TMR1);
      }
      else {
         glcd_text57(128/2-30, 0, (char*)"Capturando", 1, OFF);
         glcd_text57(128/2-30, 0, (char*)"Limpiando", 1, ON);
         limpiarGrafico;
         glcd_text57(128/2-30, 0, (char*)"Limpiando", 1, OFF);
         sprintf(str, "%3.2fC", t);
         glcd_text57(12*6, 10, str, 1, OFF);
         x=0;
         disable_interrupts(INT_TIMER1);
         glcd_text57(128/2-30, 0, (char*)"Guardando", 1, ON);
         for(int pos=0; pos<nMediciones; pos++)
            write_eeprom(pos, registro[pos]);
         glcd_text57(128/2-30, 0, (char*)"Guardando", 1, OFF);
      }
   }
   if(input(PIN_B7)){
      habilitarLectura=0;
      glcd_text57(128/2-30, 0, (char*)"Capturando", 1, OFF);
      disable_interrupts(INT_TIMER1);
      disable_interrupts(INT_TIMER0);
      for(int pos=0; pos<nMediciones; pos++){
         registro[pos]=read_eeprom(pos);
         float dato=(5.0*registro[pos]*100.0)/1024.0;
         if(dato>=28 && dato<=50)
            nuevaLinea(dato);
         if(dato<28)
            nuevaLinea(29);
         if(dato>50)
            nuevaLinea(50);
         registro[pos]=0;
      }
      glcd_text57(128/2-30, 0, (char*)"Guardando", 1, ON);
      for(int pos=0; pos<nMediciones; pos++)
         write_eeprom(pos, registro[pos]);
      glcd_text57(128/2-30, 0, (char*)"Guardando", 1, OFF);
   }
}

#INT_RDA
void serial_interrupt() {
   r_ = getc();
   toggleBT(r_);
}

///Fin Interrupciones

void main()
{
   trisb=0b01000000;
   
   setup_adc_ports(AN0); //seteamos el pin A0 como analogico
   setup_adc(ADC_CLOCK_INTERNAL); //Establecemos el reloj interno
   setup_timer_0(RTCC_INTERNAL|RTCC_DIV_256); //setup del timer0
   setup_timer_1(T1_INTERNAL|T1_DIV_BY_8); //setup del timer1
   set_timer0(TMR0); //seteamos el timer0
   set_timer1(TMR1); //setemaos el timer1
   
   glcd_init(ON); //Inicializamos el lcd
   
   enable_interrupts(INT_RB); //Habilitamos las interrupciones del RB4-7
   enable_interrupts(INT_RDA);//Habilitamos las interrupciones del RDA
   enable_interrupts(GLOBAL); //Habilitamos las interrupciones globales

   glcd_text57(0,10,(char*)"Temperatura:",1,ON); //Escribimos el texto "Tempreatura:" en la posicion 0,10
   glcd_line(0, 8, 128, 8, ON); //Pintamos una linea por debajo del barra de notificaciones
   glcd_line(0, 19, 128, 19, ON); //Pintamos una linea por debajo de la temperatura
   
   set_adc_channel(0); //Seteamos el canal que vamos a leer
   delay_ms(250); //Esperamos 250 ms para tener una captura mas real de la primera temperatura
   iAn=read_adc(); //Levantamos el dato
   y=(5.0*iAn*100.0)/1024.0; //Lo convertemos a temperatura. Esta es la primera captura
   delay_ms(250);
   
   set_SERIALsr();
   
   while(TRUE) {
      if(habilitarLectura){
         set_adc_channel(0); //Seteamos el canal que vamos a leer
         delay_us(10); //Esperamos 10 us
         iAn=read_adc(); //Levantamos el dato
         t=(5.0*iAn*100.0)/1024.0; //Lo convertemos a temperatura
         
         if(!btST)
            sendINT('t', iAn, SEP); //Funcion para enviar datos via el Modulo Bt
         
         if(t!=y){ //Si t es != al dato anterior refrescamos la temperatura y la enviamos al bluetooth
            sprintf(str, "%3.2fC", y); //Convertimos la temperatura float en un char*
            glcd_text57(12*6, 10, str, 1, OFF); //borramos del lcd la temperatura anterior
            sprintf(str, "%3.2fC", t); //Convertimos la temperatura float en un char*
            glcd_text57(12*6, 10, str, 1, ON); //Escribimos la temperatura.
         }
         if(t<=40 && t>=35)
            disable_interrupts(INT_TIMER0);
         if(t>40 || t<35)
            enable_interrupts(INT_TIMER0);
         if(t<=50 && t>=28){ //Si t es menor o igual a 50 la agregamos al grafico
            nuevaLinea(t); //Dibujamos la nueva linea en el grafico.
            glcd_text57(3, 0, (char*)"T>50", 1, OFF); //ocultamos la notificacion de t>50
            glcd_text57(3, 0, (char*)"T<28", 1, OFF); //ocultamos la notificacion de t>50
         }
         if(t>50){
            glcd_text57(3, 0, (char*)"T>50", 1, ON); //Esto significa que no graficamos temperaturas superiores a 50
            y=t; //igualamos el dato anterior al valor de temperatura para no refrescar otra vez el valor de la temperatura
         }
         if(t<28){
            glcd_text57(3, 0, (char*)"T<28", 1, ON); //Esto significa que no graficamos temperaturas superiores a 50
            y=t; //igualamos el dato anterior al valor de temperatura para no refrescar otra vez el valor de la temperatura
         }
         delay_ms(250);
      }
   }
}
