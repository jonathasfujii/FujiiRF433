/*
ARDUINO DECODIFICADOR HT6P20B COM RESISTOR DE 2M2 NO OSC.
ESTE CÓDIGO NÃO USA TIMER, INTERRUPÇÃO EXTERNA E NEM PINO DEFINIDO DE ENTRADA.
ELE MEDE O TEMPO DO PILOT PERIOD E COMPARA SE ESTÁ DENTRO DA FAIXA DEFINIDA,
SE TIVER ELE PASSA PARA CODE PERIOD E FAZ AS MEDIDÇÕES DE TEMPO EM NIVEL ALTO
SE TIVER DENTRO DA FAIXA ACRECENTA BIT 1 OU 0 NA VARIAVEL _DATA CASO NÃO ZERA AS VARIÁVEIS E RE-INICIA
APOS RECEBER TODOS OS BITS ELE PEGA OS 4 BITS DO ANTE CODE E TESTA PARA SABER SE O CÓDIGO FOI RECEBIDO
CORRETAMENTE, CASO RECEBIDO CERTO ELE COLOCA A VARIAVEL ANTCODE EM 1.

CRIADO POR: JACQUES DANIEL MORESCO
DATA: 28/02/2012 USANDO ARDUINO 0022.
FONES:54 3324 2251 54 9206 7168
E-MAIL: ibisul@ibisul.com.br
Permitido o uso público, mas deve-se manter o nome do autor.
//Segunda modificação Sérgio Navarro Brasil

// Adaptado por Jonathas Fujii para funcionar como LIB 03/10/2016
*/
#ifndef RF433Fujii_h
#define RF433Fujii_h

#include "Arduino.h"

class RF433Fujii {

  public:
    RF433Fujii(byte pinRx, byte pinTx);
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
	void decimalToBinary(long n, char *codigo);
};

#endif
