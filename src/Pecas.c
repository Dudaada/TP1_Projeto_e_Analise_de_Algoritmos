#include "../include/Pecas.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void ConcertarNave(Mapa *mapa){

    if(mapa->qtdPecas == 4){
        printf("Nave concertada não precisamos de mais peças.\n");//tira talvez
    }
    else{
        mapa->qtdPecas++;
        mapa->D += mapa->Againho;

    }
}
int AndarnoMapa(Mapa *mapa){
    if(mapa->qtdPecas == 4){
        printf("Nave concertada não gastamos mais durabilidade.\n");//tira talvez
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
void UmMeteoroAcertou(Mapa *mapa);
void RouboExtraterrestre(Mapa *mapa);