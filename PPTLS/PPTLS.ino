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


uint8_t comp::juegopc()                                    
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
	Serial.println("Ingrese el numero de partidas a jugar (1, 3 o 5)");
	while(intpartidas==0)
	{
		String partidas = leeropcion();
		if(partidas == "1"){
			intpartidas = 1;   
	    }  // statement
	    
	    if(partidas == "3"){
	    	intpartidas = 3;   
	    }
	    if (partidas == "5"){
	    	intpartidas =5;
	    }
	    if (partidas != 0 && partidas != "1" && partidas != "3" && partidas != "5"){
	    	Serial.println("El numero de partidas("+partidas+") es invalido, deben ser 1, 3 o 5 partidas");
	    	intpartidas = 0;
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

String preguntarestado()
{
	Serial.println("Desea conocer sus estadisticas? (si / no)");
	String respuesta = "";
	while(respuesta=="")
	{
	  respuesta = leeropcion();  // statement
	}
	return respuesta;
}

String leeropcion()
{
	String respuestausuario = "";
	while(Serial.available())                        
	{                    
	   respuestausuario.concat(char(Serial.read()));                   // statement
	   delay(10);
	}
	return respuestausuario;
}

int ganoperdio()                                   // que diferencia hay entre bool y boolean?????
{

	String usuario = preguntar();
	while(usuario!="piedra" && usuario!="papel" && usuario!="tijera" && usuario!="lagartija" && usuario!="spock"){
		Serial.println("Su jugada es invalida");
	  usuario = preguntar();  // statement
	}
	uint8_t pc = AI.juegopc();

	if (usuario=="piedra")
	{
		if ((pc==2)||(pc==3))
		{
			Serial.println ("Has ganado");
			return 1;
		}
		if (pc==0)
		{
			Serial.println ("Ha habido un empate");
			return 0;
		}
		else
		{
			Serial.println ("Has perdido");
			return -1;
		}
	}
	else if (usuario=="papel")
	{
		if ((pc==0)||(pc==4))
		{
			Serial.println ("Has ganado");
			return 1;
		}
		if (pc==1)
		{
			Serial.println ("Ha habido un empate");
			return 0;
		}
		else
		{
			Serial.println ("Has perdido");
			return -1;
		}
	}
	else if (usuario=="tijera")
	{
		if ((pc==1)||(pc==3))
		{
			Serial.println ("Has ganado");
			return 1;
		}
		if (pc==2)
		{
			Serial.println ("Ha habido un empate");
			return 0;
		}
		else
		{
			Serial.println ("Has perdido");
			return -1;
		}
	}
	else if (usuario=="lagartija")
	{
		if ((pc==1)||(pc==4))
		{
			Serial.println ("Has ganado");
			return 1;
		}
		if (pc==3)
		{
			Serial.println ("Ha habido un empate");
			return 0;
		}
		else
		{
			Serial.println ("Has perdido");
			return -1;
		}
	}
	else if (usuario=="spock")
	{
		if ((pc==0)||(pc==2))
		{
			Serial.println ("Has ganado");
			return 1;
		}
		if (pc==4)
		{
			Serial.println ("Ha habido un empate");
			return 0;
		}
		else
		{
			Serial.println ("Has perdido");
			return -1;
		}
	}

}

void loop()
{

	uint8_t cont = 0;
	uint8_t numeropartidas = 0;
	uint8_t totalganado = 0;
	uint8_t totalperdido = 0;
	bool playing = false;
	uint8_t totalpartidas = EEPROM.read(10) + EEPROM.read(11);

	String estado ="";
	while(estado==""){
	 estado = preguntarestado();   // statement
	}

	if(estado=="si")
	{
		Serial.println("sus resultados son:");  
		Serial.print("El numero total de partidas jugadas es:  ");
		Serial.println(totalpartidas);
		Serial.println("el numero de victorias es: " + String(EEPROM.read(10)));
		Serial.println("el numero de perdidas es: " + String(EEPROM.read(11)));
		Serial.print("\n");
		Serial.println("Buena suerte");
		Serial.print("\n");
	}

	while(numeropartidas == 0){
  numeropartidas = numpartidas() ; // statement
  playing = true;
}

while (playing == true){

	int resultado = ganoperdio();

	if(resultado==1)
	{
		AI.victorias++;
		cont++;
		totalganado++;
		EEPROM.write(10, AI.victorias);
	}    
	else if (resultado==-1)
	{
		AI.perdidas++;
		cont++;
		totalperdido++;
		EEPROM.write(11, AI.perdidas);
	}

	if(cont == numeropartidas)
	{
		if(totalganado>totalperdido){
			Serial.println("has Ganado el juego");  
		}
		else{
			Serial.println("has perdido el juego, suerte para la proxima"); 
		}
		playing = false; 
	}
}

}
