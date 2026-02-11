# µcontroleurs 4AE-SE 2025

Bienvenue dans le projet voilier en µcontroleurs 4AE-SE 2025.

Velkommen til seilbåtprosjektet i µkontrollere 4AE-SE 2025.

Bem vindo ao projeto veleiro de µcontroladores 4AE-SE 2025.

Welkom bij het microcontroller zeilbootproject 4AE-SE 2025.



License : CC-BY-NC-SA 4.0



## Les groupes et résponsabilités sont :
>>Nicolas et Jarno : Envoi de UART et PWM dans la bonne fréquence (canal), pour relier le voilier (3.5?) à l'ecran. (3.7)
Ils utilisent les broches PA9 (D8) et PA10 (D2) pour l'USART.

>>Aleksander et Brage : Acceleromètre par I2C (3.2). La chûte du voilier envoie la commande de faire lâcher les voiles.
Ils utilisent les broches PA4, PA5, PA6 et PA7 pour l'acceleromètre. 
PA2 pour la gestion de l'ADC.

>>Oskar et Tiago : Controler les voiles (3.4) avec les données de la girouette (3.1)
Ils utilisent les broches PA0, PA1 et PA8 pour la girouette et les broches PB8  pour controler les voiles.

>>En commun : Géstion de la pile avec l'ADC (3.6) et clock interne avec CMOS. (3.3)







# GIT dans le terminal

## Comment initialiser son GIT :
>> init git

>> git config --global user.email "[USER]@insa-toulouse.fr"

>> git config --global user.name "[NOM]"

>> git config --global credential.helper manager (Si Windows)

>> git remote add origin https://git.etud.insa-toulouse.fr/johnse/BE_VOILIER.git


## Comment PULL :

>> git pull

>> git switch [BRANCHE]


## Comment PUSH :

>> git add [NOMDUFICHIER]

>> git commit -m "[COMMENTAIRE]"

>> git push -u origin [BRANCHE]



# Inspiration

<img src="https://external-content.duckduckgo.com/iu/?u=https%3A%2F%2Fc2.staticflickr.com%2F6%2F5229%2F5681377563_4d4e274d51_b.jpg&f=1&nofb=1&ipt=cbe9495133b91e29c85ebc218df03cb9e58fc50148b045a8933418eb060146ad" alt="Le voilier Sørlandet au large des côtes canadiennes">

Le voilier Sørlandet au large des côtes canadiennes
