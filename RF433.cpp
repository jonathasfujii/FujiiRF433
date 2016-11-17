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
#include "Arduino.h"
#include "RF433.h"

RF433::RF433(byte pinRx, byte pinTx) {
  pinMode(pinRx, INPUT);
  pinMode(pinTx, INPUT);
  _pinRx = pinRx;
  _pinTx = pinTx;
}

boolean RF433::codigoRecebido() {  
	boolean retorno = false;
	if (startbit==0)
	 {// Testa o tempo piloto até o Bit de inicio;
	  _dur = pulseIn(_pinRx, LOW);
	  if(_dur > 8000 && _dur < 12000 && startbit==0)
	  {
		larpulso=_dur/23;
		larpulso1=larpulso-50;
		larpulso2=larpulso+50;
		larpulso3=larpulso+larpulso-50;
		larpulso4=larpulso+larpulso+50;
		startbit=1;
		_dur=0;
		_data=0;
		dataok=0;
		ctr=0;
	  }
	 }

	// Se o Bit de inicio OK ENTÃO Inicia a medição do tempo em Nivel ALTO dos sinais, e testa se o tempo está na faixa.
	if (startbit==1 && dataok==0 && ctr < 28)
	{
		++ctr;
		_dur1 = pulseIn(_pinRx, HIGH);
	   if(_dur1 > larpulso1 && _dur1 < larpulso2) {    // Se a largura de pulso é entre 1/4000 e 1/3000 segundos
		 _data = (_data << 1) + 1;      // anexar um * 1 * para a extremidade mais à direita do buffer
	   } else if(_dur1 > larpulso3 && _dur1 < larpulso4) {   // Se a largura de pulso é entre 2/4000 e 2/3000 segundos
	   	 _data = (_data << 1);       // anexar um * 0 * para a extremidade mais à direita do buffer
	   }
	   else
	   {
		 /* força finalização do laço */
			  startbit=0;
	   }
		  
	}
  
	if (ctr==28){ 
		if (bitRead(_data,0)==1) {
           if (bitRead(_data,1)==0){
                if (bitRead(_data,2)==1) {
					if (bitRead(_data,3)==0) {
					  antcode=1;
					}
				}
			}
		}   
		if (antcode==1) {// Se foram recebidos todos os 28 Bits, o valor vai para a variavel _data e pode ser usada como exemplo abaixo.
			dataok=1;
			//Serial.println(_data,DEC);
			//Serial.println(counter,DEC);
			retorno = true;
			ctr=0;
			startbit=0;
			antcode=0;
			//delay(100);
		}
    }
	return retorno;
}

unsigned long RF433::getCodigo(){
	return _data;
}

void RF433::enviarCodigo(long codigo_l){
  char *codigo;
  decimalToBinary(codigo_l, codigo);
  for (int k=0;k<2;k++){ // esse laço simplesmente repete o envio do código para certificar que será entregue 
    
	// envia o pilot code
    Serial.println("transmitindo...");
    digitalWrite(_pinTx,LOW);
    delayMicroseconds(larpulsoEmissor*23);
    digitalWrite(_pinTx,HIGH);
    delayMicroseconds(larpulsoEmissor); //fim do pilot code

    for (int i=0;i<28;i++){
      Serial.print(bitRead(dados,i),BIN);
      if (codigo[i] == '1') {
        bitWrite(dados, i, 1);
        digitalWrite(_pinTx,LOW);
        delayMicroseconds(larpulsoEmissor*2);
        digitalWrite(_pinTx,HIGH);
        delayMicroseconds(larpulsoEmissor);
      } 
      else { 
        bitWrite(dados, i, 0);
        digitalWrite(_pinTx,LOW);
        delayMicroseconds(larpulsoEmissor);
        digitalWrite(_pinTx,HIGH);
        delayMicroseconds(larpulsoEmissor*2);
      }
    }
  }
  digitalWrite(_pinTx,LOW);
  Serial.println ();
  Serial.println("dados transmitidos.");
}

void RF433::decimalToBinary(long n, char *pointer){
   int tamanho = 28;
   int c, d, count;
   //char *pointer;
 
   count = 0;
   pointer = (char*)malloc(tamanho+1);
 
   if ( pointer == NULL )
      exit(EXIT_FAILURE);
 
   for ( c = (tamanho-1) ; c >= 0 ; c-- )
   {
      d = n >> c;
 
      if ( d & 1 )
         *(pointer+count) = 1 + '0';
      else
         *(pointer+count) = 0 + '0';
 
      count++;
   }
   *(pointer+count) = '\0';
 
   //return  pointer;
}
