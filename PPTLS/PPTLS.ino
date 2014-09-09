//Tarea1
//lagartija: mata spock y a papel y la matan tijera y la piedra
//Spock: mata a tijera y a piedra y lo matan papel y la lagartija

#include "EEPROM.h";
const char* opciones[] = {"Piedra", "Papel", "Tijera", "Lagartija", "´pock"};

class comp
{
	public:
    comp();
	uint8_t victorias;
	uint8_t perdidas;
	float ratio();
	uint8_t juegopc();
};

comp::comp()
{
	victorias = 0;
	perdidas = 0;
}


uint8_t comp::juegopc()                                    // porque esta no puede ser una funcion normal y se tiene que hacer con pc::juegopc
{
	uint8_t pcseleccion = random(0, 4.99);
	Serial.print("Su oponente selecciono: ");
	Serial.println(opciones[pcseleccion]);
	return pcseleccion;
}


comp AI = comp();

uint8_t numpartidas()
{
	uint8_t intpartidas = 0;
	Serial.print("Ingrese el numero de partidas a jugar (1, 3 o 5)");
	while(Serial.available())
	{
		String partidas = leeropcion();
	  if(partidas == "1"){
	    intpartidas = 1;   
	    }  // statement
	   
	   if(partidas == "3"){
	     	intpartidas = 3;   
	   }
	   if (partidas == "5"){
	    	intpartidas ==5;
	    }
	}
	return intpartidas;
}

void setup()
{
	Serial.begin(115200);
	AI.victorias = EEPROM.read(10);
	AI.perdidas = EEPROM.read(11);
}

String preguntar()
{
	Serial.println(".....Haga su movimiento....");
	String jugada = "";
	while(jugada=="")
	{
	  jugada = leeropcion();  // statement
	}
	return jugada;
}

String leeropcion()
{
	String movimiento = "";
	while(Serial.available())                        // que diferencia hay si pongo un if o un while???
	{                    
	   movimiento.concat(char(Serial.read()));                   // statement
	   delay(10);
	}
	return movimiento;
}

int ganoperdio()                                   // que diferencia hay entre bool y boolean?????
{
	String usuario = preguntar();

	if(usuario=="estado")
	{
	Serial.println("sus resultados son:");  
	Serial.println("El numero total de partidas jugadas es:  totalpartidas");
	Serial.println("el numero de victorias es: " + String(EEPROM.read(10)));
	Serial.println("el numero de perdidas es: " + String(EEPROM.read(11)));
	Serial.println("Buena suerte");
	Serial.print("\n");
	}
	else
	{
	uint8_t pc = AI.juegopc();
	

if (usuario=="piedra")
 {
 	if ((pc==2)||(pc==3))
 	{
 		Serial.println ("Ganaste");
 		return 1;
 	}
 	if (pc==0)
 	{
 		Serial.println ("Empate");
 		return 0;
 	}
 	else
 	{
 		Serial.println ("Perdiste");
 		return -1;
 	}
 }
  else if (usuario=="papel")
 {
 	if ((pc==0)||(pc==4))
 	{
 		Serial.println ("Ganaste");
 		return 1;
 	}
 	if (pc==1)
 	{
 		Serial.println ("Empate");
 		return 0;
 	}
 	else
 	{
 		Serial.println ("Perdiste");
 		return -1;
 	}
 }
   else if (usuario=="tijera")
 {
 	if ((pc==1)||(pc==3))
 	{
 		Serial.println ("Ganaste");
 		return 1;
 	}
 	if (pc==2)
 	{
 		Serial.println ("Empate");
 		return 0;
 	}
 	else
 	{
 		Serial.println ("Perdiste");
 		return -1;
 	}
 }
   else if (usuario=="lagartija")
 {
 	if ((pc==1)||(pc==4))
 	{
 		Serial.println ("Ganaste");
 		return 1;
 	}
 	if (pc==3)
 	{
 		Serial.println ("Empate");
 		return 0;
 	}
 	else
 	{
 		Serial.println ("Perdiste");
 		return -1;
 	}
 }
    else if (usuario=="spock")
 {
 	if ((pc==0)||(pc==2))
 	{
 		Serial.println ("Ganaste");
 		return 1;
 	}
 	if (pc==4)
 	{
 		Serial.println ("Empate");
 		return 0;
 	}
 	else
 	{
 		Serial.println ("Perdiste");
 		return -1;
 	}
 }

}
}

void loop()
{

uint8_t cont = 0;
uint8_t numeropartidas = numpartidas();
bool playing = true;
while (playing == true)
{

	int resultado = ganoperdio();

	if(resultado==1)
	{
	   AI.victorias++;
	   cont++;
	   EEPROM.write(10, AI.victorias);
	}    
	else if (resultado==-1)
	{
		AI.perdidas++;
		cont++;
		 EEPROM.write(11, AI.perdidas);
	}

if(cont == numeropartidas)
{
   playing = false; 
}
	}

}
