#include <stdio.h>
#include <string.h>
#include <math.h>
#include "tools.h"


// extraction d'un IGCRecord depuis une chaine
IGCRecord extractIGC(char chaineEnregistrement[]){
    IGCRecord locRecord;
    unsigned lat_deg, lat_min, lon_deg, lon_min;
    char lat_NS, lon_EW;

    if ((strlen(chaineEnregistrement) < 35) || (chaineEnregistrement[0] != 'B'))
        return NULLRecord;

    // Extraction des données IGC :
    unsigned nbLu = sscanf(chaineEnregistrement, "B %6c %2d %5d %1c %3d %5d %1c A %5d %5d"
            ,&(locRecord.time), &lat_deg, &lat_min, &lat_NS, &lon_deg, &lon_min, &lon_EW
            , &(locRecord.altitudeBaro), &(locRecord.altitudeGPS));

    if (nbLu < 7) // le point n'est pas bon.
        locRecord = NULLRecord;
    else {
        if (nbLu < 9){
            // les altitudes ne sont pas valides
            // par convention on y stock -1
            locRecord.altitudeBaro = -1;
            locRecord.altitudeGPS = -1;
        }
        // mise en flotant des coordonnées
        // la partie entière est en degrés et la partie décimale en milièmes de minutes d'arc
        locRecord.latitude = (float)lat_deg - (lat_min / 60);
        if (lat_NS == 'S' || lat_NS == 's') locRecord.latitude *= -1.0; // négatif au sud

        locRecord.longitude = (float)lon_deg - (lon_min / 60);
        if (lon_EW == 'O' || lon_EW == 'o') locRecord.longitude *= -1.0; // négatif à l'ouest
    }
    return locRecord;
}

// calcul d'écart entre deux Records
IGCDeltaRecord calculerEcart(IGCRecord depart, IGCRecord arrivee){
const float earthRadius = 6400.0;   // rayon terrestre pour le calcul des distances
    // ...

    // horodatage de référence = départ
    for (int i = 0; i < 6; i++)
        deltaRec.time[i] = depart.time[i];

    // durée
    sscanf(depart.time,"%2d %2d %2d", &Hd, &md, &sd);
    //... idem avec l'arrivée
    deltaRec.duree = 3600.0(Ha-Hd) + 60.0(ma-md) + (sa-sd);

    //distance horizontale
    meanLat = 0.5(arrivee.latitude + depart.latitude);     //latitude moyenne du lieu
    diffLat = arrivee.latitude - depart.latitude;
    ecartLong = arrivee.longitude - depart.longitude;
    // à  vous de jouée :
    // indication la distance horizotale est donnée par :
    distH = earthRadius sqrt(pow(tan(diffLat),2)+pow(cos(meanLat)*tan(ecartLong),2));

    //distance verticale
    // on vérifie si les altitudes sont valides (i.e. positives).
    if locRecord.altitudeBaro > 0 {

    }
    else locRecord.altitudeGPS > 0 {
        locRecord.altitudeBaro = -1;
    }
    else{
        locRecord.altitudeBaro = -1;
        locRecord.altitudeGPS = -1;
    }
    // On prend en priorité l'altitude Barométrique, sinon celle par le GPS, à défaut on met une valeur négative pour signifier que la distance verticale est invalide.

    //vitesse horizontale
        VitH = distH / deltaRec.duree;

    //vitesse verticale
        VitV = distV / deltaRec.duree;

    return deltaRec;
}
IGCDeltaRecord cumuleRecords(IGCDeltaRecord deltaRec[]){
    // à coder
    return NULLDeltaRecord;
}
void delta2csv(IGCDeltaRecord deltaRec, char csvString[]){

    // à coder
}
