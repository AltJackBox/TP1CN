La table des symboles sous format txt possède la syntaxe suivante :

nombre_de_symboles
symbole probabilité borne_inférieure(flottant) borne_supérieure(flottant)

Il y a déjà une table disponible (table_symboles.txt)

Vous pouvez compiler les fonctions de test de compression et de décompression arithmétique en faisant make, puis au choix :

./test_compression nom_fichier_table.txt message_a_compresser 
./test_decompression nom_fichier_table.txt Vmessage taille_message(entier)

ex : ./test_compression table_symboles.txt KIWIKIKW 
     ./test_decompression table_symboles.txt 0.834534 8

Les programmes de test correspondent aux fichiers compression.c et decompression.c.
Nous y réalisons la lecture et le stockage des informations contenues dans la table dans des tableaux afin de les utiliser pour les executions
des fonctions présentes dans codage_arithmetique.c (algorithmes de compression et de decompression arithmétique)