#!/bin/bash
echo "[+] compilation des fichiers de recherche et de génération de texte"
echo
make

echo
echo "[+] compilation terminée"

nom_dossier="fichier_generes"

if ! [ -d "$nom_dossier" ]; then
    mkdir "$nom_dossier"
    echo "Le dossier '$nom_dossier' a été créé."
fi



echo "Générations  des mots et des textes en fonction des alphabets 2, 4, 20, 70"

./genere-texte 5000000 2 > fichier_generes/texte2.txt
./genere-mots 100 5 15 2 > fichier_generes/mots_2_5_15.txt
./genere-mots 100 15 30 2 > fichier_generes/mots_2_15_30.txt
./genere-mots 100 30 60 2 > fichier_generes/mots_2_30_60.txt

./genere-texte 5000000 4 > fichier_generes/texte4.txt
./genere-mots 100 5 15 4 > fichier_generes/mots_4_5_15.txt
./genere-mots 100 15 30 4 > fichier_generes/mots_4_15_30.txt
./genere-mots 100 30 60 4 > fichier_generes/mots_4_30_60.txt

./genere-texte 5000000 20 > fichier_generes/texte20.txt
./genere-mots 100 5 15 20 > fichier_generes/mots_20_5_15.txt
./genere-mots 100 15 30 20 > fichier_generes/mots_20_15_30.txt
./genere-mots 100 30 60 20 > fichier_generes/mots_20_30_60.txt

./genere-texte 5000000 70 > fichier_generes/texte70.txt
./genere-mots 100 5 15 70 > fichier_generes/mots_70_5_15.txt
./genere-mots 100 15 30 70 > fichier_generes/mots_70_15_30.txt
./genere-mots 100 30 60 70 > fichier_generes/mots_70_30_60.txt

echo "Generation des mots et des textes terminée"
echo



echo "Recherche des mots dans les textes"


./ac-matrice fichier_generes/mots_2_5_15.txt fichier_generes/texte2.txt > fichier_generes/res-ac-matrice2_5_15.txt
./ac-matrice fichier_generes/mots_2_15_30.txt fichier_generes/texte2.txt > fichier_generes/res-ac-matrice2_15_30.txt
./ac-matrice fichier_generes/mots_2_30_60.txt fichier_generes/texte2.txt > fichier_generes/res-ac-matrice2_30_60.txt

./ac-hachage fichier_generes/mots_2_5_15.txt fichier_generes/texte2.txt > fichier_generes/res-ac-hachage2_5_15.txt
./ac-hachage fichier_generes/mots_2_15_30.txt fichier_generes/texte2.txt > fichier_generes/res-ac-hachage2_15_30.txt
./ac-hachage fichier_generes/mots_2_30_60.txt fichier_generes/texte2.txt > fichier_generes/res-ac-hachage2_30_60.txt


./ac-matrice fichier_generes/mots_4_5_15.txt fichier_generes/texte4.txt > fichier_generes/res-ac-matrice4_5_15.txt
./ac-matrice fichier_generes/mots_4_15_30.txt fichier_generes/texte4.txt > fichier_generes/res-ac-matrice4_15_30.txt
./ac-matrice fichier_generes/mots_4_30_60.txt fichier_generes/texte4.txt > fichier_generes/res-ac-matrice4_30_60.txt

./ac-hachage fichier_generes/mots_4_5_15.txt fichier_generes/texte4.txt > fichier_generes/res-ac-hachage4_5_15.txt
./ac-hachage fichier_generes/mots_4_15_30.txt fichier_generes/texte4.txt > fichier_generes/res-ac-hachage4_15_30.txt
./ac-hachage fichier_generes/mots_4_30_60.txt fichier_generes/texte4.txt > fichier_generes/res-ac-hachage4_30_60.txt


./ac-matrice fichier_generes/mots_20_5_15.txt fichier_generes/texte20.txt > fichier_generes/res-ac-matrice20_5_15.txt
./ac-matrice fichier_generes/mots_20_15_30.txt fichier_generes/texte20.txt > fichier_generes/res-ac-matrice20_15_30.txt
./ac-matrice fichier_generes/mots_20_30_60.txt fichier_generes/texte20.txt > fichier_generes/res-ac-matrice20_30_60.txt

./ac-hachage fichier_generes/mots_20_5_15.txt fichier_generes/texte20.txt > fichier_generes/res-ac-hachage20_5_15.txt
./ac-hachage fichier_generes/mots_20_15_30.txt fichier_generes/texte20.txt > fichier_generes/res-ac-hachage20_15_30.txt
./ac-hachage fichier_generes/mots_20_30_60.txt fichier_generes/texte20.txt > fichier_generes/res-ac-hachage20_30_60.txt

./ac-matrice fichier_generes/mots_70_5_15.txt fichier_generes/texte70.txt > fichier_generes/res-ac-matrice70_5_15.txt
./ac-matrice fichier_generes/mots_70_15_30.txt fichier_generes/texte70.txt > fichier_generes/res-ac-matrice70_15_30.txt
./ac-matrice fichier_generes/mots_70_30_60.txt fichier_generes/texte70.txt > fichier_generes/res-ac-matrice70_30_60.txt

./ac-hachage fichier_generes/mots_70_5_15.txt fichier_generes/texte70.txt > fichier_generes/res-ac-hachage70_5_15.txt
./ac-hachage fichier_generes/mots_70_15_30.txt fichier_generes/texte70.txt > fichier_generes/res-ac-hachage70_15_30.txt
./ac-hachage fichier_generes/mots_70_30_60.txt fichier_generes/texte70.txt > fichier_generes/res-ac-hachage70_30_60.txt

echo "recherche des mots dans les textes terminée"

echo "Voir les résultats dans le dossier $nom_dossier"