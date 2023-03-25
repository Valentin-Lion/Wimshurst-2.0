# Wimshurst-2.0
Code source de l'équipe du LGT Henri Matisse Nice pour le projet Wimshurst 2.0
Explication de code : 

Le fichier principal est le fichier INO sketch.

Tout d'abord nous importons les modules dont nous aurons besoin pour contrôller nos composants, ainsi que les diverses classes contenant le code source pour chaque composant.

Nous initialisons ensuite les pins, les variables, puis nous appellons toutes les classes.

Notre setup initialise le systemse, défini le pinMode pour chaque composant, puis appelle le constructeur de classe pour chaque classe.

Notre loop commence par une lecture de l'appui ou non sur le bouton de l'encodeur rotatif, et en cas d'appui met à jour le menu.

Il se poursuit ensuite une lecture du sens de rotation de l'encodeur rotatif, avec actualisation au besoin d'une des variables par la fonction updateSetting.

updateMenuState se charge d'actualiser ce qui est affiché sur l'écran en appelant diverses méthodes, mais aussi d'appliquer aux composants les changements défini par updateSetting.

updateSetting permet de modifier des paramètres sur nos composants. Pour cela, elle prend en compte le temps d'appuie sur le bouton de l'encodeur rotatif, notamment pour la modification de la vitesse du moteur principal.

De la même manière, elle modifie la position des servos-moteurs.

Code relatif aux bras : après avoir construit les objets servos-moteurs, le constructeur place les servos-moteurs à une position basique à l'allumage de la machine.

La méthode setArmsDistance convertir la nouvelle distance des bras en degrés, puis l'applique aux bras.

Code relatif à l'écran : Après avoir construit l'objet, nous initialisons nos propres caractères à afficher sur l'écran. Le constructeur établit des paramètres de base pour l'écran.
La méthode editCurrentSetting permet de réecrire les lignes de l'écran avec les nouveaux paramètres.

La méthode contenue dans la partie privée de la classe est utilisée dans la partie publique pour modifier les lignes.

Code relatif au moteur principal: Après avoir construit l'objet, le constructeur de classe lui attribue une vitesse de 0 (correspondant à un mode éteint). 
La méthode changeMotorState permet en cas d'activation d'appliquer la vitesse définie au moteur. En cas d'arrêt, la vitesse repasse à 0 (arrêt de rotation).

