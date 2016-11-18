/*
ARDUINO DECODIFICADOR HT6P20B

CRIADO POR: JACQUES DANIEL MORESCO
DATA: 28/02/2012 USANDO ARDUINO 0022.
FONES:54 3324 2251 54 9206 7168
E-MAIL: ibisul@ibisul.com.br
Modificado por Sérgio Navarro Brasil

Adaptado por Jonathas Fujii incluindo para funcionar como LIB e incluida função de emissão 03/10/2016
E-mial: jonathasfujii@gmail.com
*/
#ifndef RF433_h
#define RF433_h

#include "Arduino.h"

class RF433 {

  public:
    RF433(byte pinRx, byte pinTx);
    boolean codigoRecebido();
	unsigned long getCodigo();
	void enviarCodigo(long codigo);
	
  private:
    byte _pinRx;
	byte _pinTx;
	//variaveis do receptor
	int startbit,ctr,dataok,larpulso,larpulso1,larpulso2,larpulso3,larpulso4,antcode=0;
	unsigned long _data=0; 
	unsigned long _dur,_dur1;    
	//variaveis do emissor
	int larpulsoEmissor = 476; //define tempo de 1 comprimento de onda em microsegundos
	unsigned long dados=0;   // SET de 28 bits que identificará o controle. Pode ser alterado como queira, desde que os 4 últimos não mudem
	String decimalToBinary(long n);
};

#endif
