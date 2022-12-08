#include <stdio.h>
#include <stdlib.h>
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

int main (int argc, char** argv){
    IGCDeltaRecord deltaRecords_tab[5]; // à utiliser pour stocker les données qui seront moyennées par la fonction cumuleRecords.
    IGCDeltaRecord deltaRecord_temp;    // variable tampon pour stockage temporel
    // ******************************************
    //placez ici vos déclaration de variables supplémentaires
    IGCRecord record_temp;    // ( variable tampon pour stockage temporel )

    // /!\_/!\_/!\_/!\_/!\_/!\_/!\_/!\_/!\_/!\_/!\_/!\_/!\_/!\_/!\_/!\_/!\_/!\_/!\_/!\_
    // mise à jour de tableauEnreg et nbLignesLues
    lireTableauEnreg();

    // ******************************************
    


    // Pour l'instant le code ne fait que recopier le fichier d'entrée vers la sortie.
    // ces deux lignes sont un exemple à remplacer par votre code
    for (int i = 0; i < nbLignesLues ; i++){
        record_temp = extractIGC(tableauEnreg[i]);
        printRecord(record_temp);
    }

    /* votre code doit :
    parcourir toutes les nbLignesLues lignes de tableauEnreg.
    Au long de ce parcours, il faudra :
    X - transformer les chaines de caractères en IGCRecords grâce à la fonction adéquat de tools.h
    - créer des IGCDeltaRecords pour chaque couple d'IGCRecord consécutifs. Fonction calculerEcart(...). ATTENTION, tous les enregistrements ne donnent pas une position.
    - regrouper les IGCDeltaRecords par paquets de 5 et en calculer un représentant moyen grâce à cumuleRecords(...).
    - écrire ce représentant moyen dans le fichier de sortie après l'avoir transformé en chaine de caractère csv (fonction delta2csv() et à l'aide de l'instruction suivante :)
        fprintf(stdout, "%s\n", ma_chaine_csv);
    */
    // ******************************************
    

    // /!\_/!\_/!\_/!\_/!\_/!\_/!\_/!\_/!\_/!\_/!\_/!\_/!\_/!\_/!\_/!\_/!\_/!\_/!\_/!\_
    // libération de la mémoire allouée dans le tableau
    libererTableauEnreg();
    return 0;
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
