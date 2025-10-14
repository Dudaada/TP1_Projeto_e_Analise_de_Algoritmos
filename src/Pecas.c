#include "../include/Pecas.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
//Função chamada toda vez que nave encontra uma peça
void ConcertarNave(Mapa *mapa){

    if(mapa->qtdPecas == 4){
        printf("Nave concertada não precisamos de mais peças.\n");//tira talvez
    }
    else{
        mapa->qtdPecas++;
        mapa->D += mapa->Againho;

    }
}

//função que subtrai em D toda vez que a Nave anda um setor
int AndarnoMapa(Mapa *mapa){
    if(mapa->qtdPecas == 4){
        printf("Nave concertada não gastamos mais durabilidade.\n");//tira talvez
		return 1;
    }
    else{
        if(mapa->D != 0){
            mapa->D -= mapa->Dperda;
            return 1;
        }
        else{
            return 0;
        }
    }
}

//Fução usada toda vez que encontra um meteoro
int UmMeteoroAcertou(Mapa *mapa){
	printf("Em meio à chuva de meteoros, um acertou a nave.\n");
	if(mapa->D != 0){
			//perde no D o que equivale a perde o dobro pois perde a andar e o meteoro tira Dperda
            mapa->D -= mapa->Dperda;
            return 1;
        }
        else{
            return 0;
        }
}
//função chamada quando encontra no mapa &
int RouboExtraterrestre(Mapa *mapa) {
    if (mapa->qtdPecas == 0) {
        printf("Invasão alienígena, mas não havia peças para roubar!\n");
        return 0;
    }

    int num = (rand() % 2) + 1;
    if (num == 1) {
        printf("Com muito esforço a tripulacao derrotou a invasão!\n");
        return 0;
    } else {
        int pegou = 0;
        if (mapa->qtdPecas == 1) {
            pegou = 1;
        } else {
            pegou = (rand() % mapa->qtdPecas) + 1;
        }
        mapa->qtdPecas -= pegou;
        printf("Os alienigenas roubaram = %d peça(s)!\n", pegou);
        return pegou;
    }
}
