/*
 * Fichier tools.h
 * pour plus de précisions vous reporter à l'énoncé du problème
 */

#ifndef TOOLS_H
#define TOOLS_H

// enregistrement d'une position
typedef struct _record {
    char time[6];   // horodatage au format hhmmss
    float latitude; // en degrés. Positive au nord
    float longitude;    // en degrés. Positive à l'est
    int altitudeBaro; // altitude barométrique en mètres
    int altitudeGPS;  // altitude GPS en mètres
} IGCRecord;

const IGCRecord NULLRecord; // l'enregistrement NULL.
// ex. pour signifier qu'un enregistrement est invalide. if (monEnregistrement == NULLRecord) printf("l'enregistrement est invalide\n");
// ou pour marquer le dernier élément d'une liste chaînée

// structure pour stocker les écarts entre 2 positions.
typedef struct _deltaRecord {
    char time[6];   // horodatage au format hhmmss
    int duree; // écart temporel en secondes
    float distH;    //distance horizontale en m
    int distV;    //distance verticale en m. positif vers le haut ; négatif vers le bas
    float vitesseH;    //vitesse horizontale en m/s
    float vitesseV;    //vitesse verticale en m/s. positif vers le haut ; négatif vers le bas
} IGCDeltaRecord;

const IGCDeltaRecord NULLDeltaRecord; // l'enregistrement NULL. idem NULLRecord.

// Fonction qui revoie les informations d'un point à partir du tableau de char contenant un enregistrement. 
// Si l'enregistrement n'est pas de type B, retourne NULLRecord
IGCRecord extractIGC(char chaineEnregistrement[]);

// Fonction qui calcule la durée entre deux enregistrements ainsi que les distances et vitesses *verticales* et *horizontales* correspondantes.
// l'horodatage sera celui de la position de départ.
IGCDeltaRecord calculerEcart(IGCRecord depart, IGCRecord arrivee);

// Fonction qui intègre plusieurs échantillons en un (voir énoncé)
IGCDeltaRecord cumuleRecords(IGCDeltaRecord [], size_t deltaRecSize);

// Fonction qui crée une chaine au format csv à partir d'un IGCDeltaRecord et la stock dans le tableau passé en paramètre. **Attention** : pour utiliser cette fonction vous penserez à passer un tableau assez grand.
void delta2csv(IGCDeltaRecord, char []);
#endif
