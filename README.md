# puissance4
Puissance4 écrit en C accompagné d'une intelligence artificielle
Le programme `puissance4` est la compilation du fichier `puissance4.c`, et le programme `puissance4IA` permet de réaliser plein de tests sur la version Intelligence Artificielle
Toutes les Intelligences Artificielles à tester doivent être placées dans le dossier `strats`
Un exemple de code compatible est démontré et commenté dans `MaStrategie.c`
Si besoin de compiler, il est recommandé d'utiliser `gcc nom_du_fichier.c -o nom_de_fichier_de_sortie -Wall`

## Le projet
Nous avons été missionnées de réaliser un Puissance4 de A à Z, depuis l'idée jusqu'au codage en passant par la conception dont le maquettage. Le code du jeu est commenté et documenté et tout est fonctionnel depuis une machine Ubuntu 20.04.

## Ce qui a été réalisé
Nous avons d'abord commencé par les idées globales sur le fonctionnement du puissance4, et nous avons maquetté le fonctionnement de celui-ci. Ensuite, le jeu a été réalisé suivant le maquettage précédent, puis documenté en utilisant Doxygen. Le résultat est le fichier `puissance4.c`
Après cela, la nouvelle mission était de créer la meilleure Intelligence Artificielle possible en suivant différents critères : La rapidité, le nombre de coups pour gagner, et le nombre de parties gagnantes. Il fallait donc élaborer une stratégie capable d'obtenir les meilleurs scores, nous avons donc commencé par réfléchir aux meilleurs comportements possibles sans en impacter le temps de réponse. Ainsi est née `UtilMidEtBloq2`, une stratégie jouant principalement au milieu du plateau et bloque tout alignement de deux pions ennemis tout en s'assurant que les siens lui permettent une victoire.

## Les acquis
