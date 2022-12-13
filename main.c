#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include "tools.h"

#define nbLignesIGC 3350 // nombre maximal de lignes dans le fichier (le plus grand exemple en compte 3320)

const int stringLength = 255; // longueur maximale d'un enregistrement (on est large)

// les deux variables qui suivent sont disponibles dans tout votre main.c .
char *tableauEnreg[nbLignesIGC]; // Tableau de chaines de caractères qui contient tous les enregistrement du fichier que vous mettez en entrée.
int nbLignesLues;   //le nombre de lignes réellement lues dans le fichier.
// ces deux variables sont mises à jour par la fonction qui suit.
// **le code déjà écrit**.
void lireTableauEnreg();
void libererTableauEnreg();

// quelques procédures pratiques pour vos essais
// procédures d'affichage
void printRecord(IGCRecord);
void printDeltaRecord(IGCDeltaRecord);

int isNullRecord(IGCRecord record);
int isNullDeltaRecord(IGCDeltaRecord record);
void setArrayToNullDeltaRecord(IGCDeltaRecord tab[], size_t tab_size);

int main (int argc, char** argv){
    IGCDeltaRecord deltaRecords_tab[5] = { NULLDeltaRecord, NULLDeltaRecord, NULLDeltaRecord, NULLDeltaRecord, NULLDeltaRecord }; // à utiliser pour stocker les données qui seront moyennées par la fonction cumuleRecords.
    IGCDeltaRecord deltaRecord_temp;    // variable tampon pour stockage temporel
    // ******************************************
    //placez ici vos déclaration de variables supplémentaires
    IGCRecord record_temp, record_temp1 = NULLRecord, record_temp2 = NULLRecord;
    char csvString[20];

    // /!\_/!\_/!\_/!\_/!\_/!\_/!\_/!\_/!\_/!\_/!\_/!\_/!\_/!\_/!\_/!\_/!\_/!\_/!\_/!\_
    // mise à jour de tableauEnreg et nbLignesLues
    lireTableauEnreg();

    // ******************************************

    // Pour l'instant le code ne fait que recopier le fichier d'entrée vers la sortie.
    // ces deux lignes sont un exemple à remplacer par votre code
    for (int i = 0; i < nbLignesLues ; i++){
        record_temp = extractIGC(tableauEnreg[i]); // Convertir la chaine en un enregistrement

        if(isNullRecord(record_temp) == 1) continue; // Si l'enregistrement n'est pas bon.

        if(isNullRecord(record_temp1) == 1){
            record_temp1 = record_temp;
        }else{
            record_temp2 = record_temp;

            deltaRecord_temp = calculerEcart(record_temp1, record_temp2);

            //printDeltaRecord(deltaRecord_temp);

            record_temp1 = NULLRecord;

            for (unsigned j = 0; j < sizeof(deltaRecords_tab); j++)
            {
                if(isNullDeltaRecord(deltaRecords_tab[j]) == 1)
                    deltaRecords_tab[j] = deltaRecord_temp;
                
                if(j >= sizeof(deltaRecords_tab) - 1){
                    deltaRecord_temp = cumuleRecords(deltaRecords_tab, sizeof(deltaRecords_tab));
                    delta2csv(deltaRecord_temp, csvString);
                    fprintf(stdout, "%s\n", csvString);
                    setArrayToNullDeltaRecord(deltaRecords_tab, 5);
                }
            }
        }
    }

    // /!\_/!\_/!\_/!\_/!\_/!\_/!\_/!\_/!\_/!\_/!\_/!\_/!\_/!\_/!\_/!\_/!\_/!\_/!\_/!\_
    // libération de la mémoire allouée dans le tableau
    libererTableauEnreg();
    return 0;
}

void setArrayToNullDeltaRecord(IGCDeltaRecord tab[], size_t tab_size){
    for (size_t i = 0; i < tab_size - 1; i++)
    {
        for (size_t j = 0; j < 6; j++)
            tab[i].time[j] = NULLDeltaRecord.time[j];

        tab[i].duree = NULLDeltaRecord.duree;
        tab[i].distH = NULLDeltaRecord.distH;
        tab[i].distV = NULLDeltaRecord.distV;
        tab[i].vitesseH = NULLDeltaRecord.vitesseH;
        tab[i].vitesseV = NULLDeltaRecord.vitesseV;
    }
    
}

// Fonction pour comparer un record à nullRecord :
int isNullRecord(IGCRecord record){
    if(strcmp(record.time, NULLRecord.time) == 0 && record.latitude == NULLRecord.latitude && record.longitude == NULLRecord.longitude && record.altitudeBaro == NULLRecord.altitudeBaro && record.altitudeGPS == NULLRecord.altitudeGPS) return 1; else return 0;
}

int isNullDeltaRecord(IGCDeltaRecord record){
    if(strcmp(record.time, NULLDeltaRecord.time) == 0 && record.duree == NULLDeltaRecord.duree && record.distH == NULLDeltaRecord.distH && record.distV == NULLDeltaRecord.distV && record.vitesseH == NULLDeltaRecord.vitesseH && record.vitesseV == NULLDeltaRecord.vitesseV) return 1; else return 0;
}


// procédure pour remplir le tableau des enregistrements
// vous n'avez rien à modifier ...
// ... MAIS vous pouvez la lire et la comprendre.
void lireTableauEnreg(){
    while (!feof(stdin)){
        tableauEnreg[nbLignesLues] = (char*)malloc(stringLength+1*sizeof(char));
        fscanf(stdin, "%[^\n]\n", tableauEnreg[nbLignesLues++]);
    }
}

// procédure pour libérer la mémoire allouée par lireTableauEnreg
void libererTableauEnreg(){
    for (int i = 0; i < nbLignesLues ; i++)
        free(tableauEnreg[i]);
}

void printRecord(IGCRecord record){
    puts("** IGC Record **");
    printf(".time : %s\n", record.time);
    printf(".lat : %2f\n", record.latitude);
    printf(".long : %2f\n", record.longitude);   
    printf(".alt_baro : %d\n", record.altitudeBaro);
    printf(".alt_GPS : %d\n", record.altitudeGPS); 
    puts("****************");
}

void printDeltaRecord(IGCDeltaRecord record){
    puts("** IGC Delta Record **");
    printf(".time : %s\n", record.time);
    printf(".duree : %d\n", record.duree);
    printf(".distH : %2f\n", record.distH);
    printf(".distV : %d\n", record.distV);   
    printf(".vitesseH : %2f\n", record.vitesseH);
    printf(".vitesseV : %2f\n", record.vitesseV); 
    puts("**********************");
}
