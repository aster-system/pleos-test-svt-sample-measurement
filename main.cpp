//******************
//
// main.cpp
//
//******************
// Présentation :
//
// Ce fichier correspond au fichier de base du programme.
//

// "include" en C++ est similaire à "impor" en python
#include "../scls-graphic-benoit/headers/game.h"
#include <iostream>

// Déclaration de toutes les variables globales du programme

// Informations sur moi
static std::string developer_informations = "Matt Code";

// Variable contenant la fenêtre graphique
static Game* core = 0;
// Variable permettant d'utiliser la fenêtre du programme.
static HUD* main_hud = 0;

// Variable de la partie navigation
// Variable contenant la partie de navigation de la fenêtre
static HUD_Object* navigation_container = 0;
// Variable contenant le bouton de navigation permettant d'atteindre la page d'explications
static HUD_Button* navigation_explaination_button = 0;
// Variable contenant le bouton de navigation permettant d'atteindre la page d'informations
static HUD_Button* navigation_information_button = 0;
// Variable contenant le bouton de navigation permettant d'atteindre la page de simulation
static HUD_Button* navigation_simulation_button = 0;
// Variable contenant le bouton de navigation permettant d'atteindre l'accueil
static HUD_Button* navigation_welcome_button = 0;

// Variable de la partie d'explication
// Variable contenant la page de la partie explication
static HUD_Object* explaination_page = 0;
// Variable contenant le texte de la page de la partie explication
static HUD_Text* explaination_page_text = 0;
// Variable contenant le titre de la page de la partie explication
static HUD_Text* explaination_page_title = 0;

// Variable de la partie d'informations
// Variable contenant la page de la partie information
static HUD_Object* information_page = 0;
// Variable contenant le texte de la page de la partie information
static HUD_Text* information_page_text = 0;
// Variable contenant le titre de la page de la partie information
static HUD_Text* information_page_title = 0;

// Variable de la partie accueil
// Variable contenant la page de la partie accueil
static HUD_Object* welcome_page = 0;
// Variable contenant le texte de la page de la partie accueil
static HUD_Text* welcome_page_text = 0;
// Variable contenant le titre de la page de la partie accueil
static HUD_Text* welcome_page_title = 0;

// Fonction "create_window", créant et définissant chaque pages du programme
void create_window() {
    // Variable nécessaire à la création de la fenêtre
    std::string license = "PLEOS  Copyright (C) 2023  " + developer_informations + "\nCe programme est Open-Source, sous licence \"GNU General Public License V3.0\".\nCela veut dire que vous êtes libre de faire tout ce que vous voulez avec. Si vous voulez\npartager ce logiciel, je vous serai fortement reconnaissant de me citer en tant que créateur.\nVisitez le site https://www.gnu.org/licenses/gpl-3.0.en.html pour plus d'informations.";

    // Créer "main_hud"
    main_hud = core->new_hud("main");
    main_hud->set_position(glm::vec3(0, 0, 0));
    main_hud->set_height(1, false);
    main_hud->set_width(1, false);
    main_hud->set_sized_according_to_ratio(false);
    main_hud->set_use_parent_rescaling(false);

    // Créer "explaination_page"
    explaination_page = main_hud->new_hud_object("explaination_page", main_hud, 1, 1, glm::vec4(192, 192, 192, 255), "hud_default");
    explaination_page->set_height(1.0, false);
    explaination_page->set_position(glm::vec3(0.25, 0, 0));
    explaination_page->set_width((750.0/1000.0) * (10.0/6.0), false);

    // Créer "explaination_page_text"
    std::string explaination_1 = scls::to_utf_8("L'idée de la méthode est d'utiliser un ratio (une fraction) pour calculer le nombre d'individus.\nEn effet, si on sait qu'un certain nombre d'indivu marqués représente un certain pourcentage\nd'individu marqués,on peut estimer le nombre total d'individus grâce aux équations suivantes :\n% individus marqués + % individus non marqués = 100%\nQu'on peut changer en :\n100% - % individus marqués = % individus non marqués\nOn peut donc calculer le pourcentage d'individus marqués et non marqués.\nOn peut ensuite calculer le nombre d'invidus non marqués grâce aux lois des statistiques :\n  % individus marqués             nombre individus marqués  \n----------------------------     =     ---------------------------------\n% individus non marqués         nombre individus non marqués\nQu'on peut modifier facilement comme ça :\n                                                        % individus non marqués\nnombre individus non marqués = nombre individus marqués X ----------------------------------\n                                                        % individus marqués\n");
    explaination_1 += scls::to_utf_8("Nous pouvons calculer le nombre d'indivus non marqués, et aussi le nombre d'individus total.");
    explaination_page_text = main_hud->new_hud_object<HUD_Text>("explaination_page_text", explaination_page, 1, 1, glm::vec4(0, 0, 0, 255), "hud_default");
    explaination_page_text->set_background_color(glm::vec4(0, 0, 0, 0));
    explaination_page_text->set_font_color(glm::vec4(0, 0, 0, 255));
    explaination_page_text->set_font_size(30);
    explaination_page_text->set_text(explaination_1);
    explaination_page_text->set_position(glm::vec3(0, -0.35, 0));
    explaination_page_text->set_width(0.59);
    explaination_page_text->set_height(explaination_page_text->scale()[1] * 2.5, false);

    // Créer "explaination_page_title"
    explaination_page_title= main_hud->new_hud_object<HUD_Text>("explaination_page_title", explaination_page, 1, 1, glm::vec4(0, 0, 0, 255), "hud_default");
    explaination_page_title->set_background_color(glm::vec4(0, 0, 0, 0));
    explaination_page_title->set_font_color(glm::vec4(0, 0, 0, 255));
    explaination_page_title->set_font_size(300);
    explaination_page_title->set_text("Explications");
    explaination_page_title->set_position(glm::vec3(0, 0.65, 0));
    explaination_page_title->set_width(0.35);
    explaination_page_title->set_height(explaination_page_title->scale()[1] * 2.5, false);

    // Créer "information_page"
    information_page = main_hud->new_hud_object("information_page", main_hud, 1, 1, glm::vec4(192, 192, 192, 255), "hud_default");
    information_page->set_height(1.0, false);
    information_page->set_position(glm::vec3(0.25, 0, 0));
    information_page->set_width((750.0/1000.0) * (10.0/6.0), false);

    // Créer "information_page_text"
    information_page_text = main_hud->new_hud_object<HUD_Text>("information_page_text", information_page, 1, 1, glm::vec4(0, 0, 0, 255), "hud_default");
    information_page_text->set_background_color(glm::vec4(0, 0, 0, 0));
    information_page_text->set_font_color(glm::vec4(0, 0, 0, 255));
    information_page_text->set_font_size(30);
    information_page_text->set_text(scls::to_utf_8(license + "\n|\n|\nCe logiciel est réalisé avec un langage de programmation appelé C++, plus complexe mais\nplus rapide et logique que Python. Il utilise l'API graphique \"SCLS Graphic Benoit\"\n(développé par moi même), utilisant les APIs GLFW, GlaD, GLM et OpenGL 3.3. Il utilise aussi\nles bibliothèques C++ \"SCLS Foundation Leonhard\" (développé par moi même),\nutilisant les librairies FreeType et ZLib.\nAllez sur mon site web https://aster-system.github.io/aster-system/ pour plus d'informations.\n|\n|\nCe logiciel est un prototype d'un futur ensemble de logiciel appelé PLEOS pour Pack de\nLogiciel Éducatifs Open Source. Même si ce projet n'est qu'au stade d'idée, il permettrai\nde grandement faciliter l'enseignement par les professeurs et l'apprentissage par les élèves.\nPour plus d'infos, allez sur mon site web https://aster-system.github.io/aster-system/projects/pleos.html."));
    information_page_text->set_position(glm::vec3(0, -0.35, 0));
    information_page_text->set_width(0.59);
    information_page_text->set_height(information_page_text->scale()[1] * 2.5, false);

    // Créer "information_page_title"
    information_page_title = main_hud->new_hud_object<HUD_Text>("information_page_title", information_page, 1, 1, glm::vec4(0, 0, 0, 255), "hud_default");
    information_page_title->set_background_color(glm::vec4(0, 0, 0, 0));
    information_page_title->set_font_color(glm::vec4(0, 0, 0, 255));
    information_page_title->set_font_size(300);
    information_page_title->set_text("Informations");
    information_page_title->set_position(glm::vec3(0, 0.65, 0));
    information_page_title->set_width(0.35);
    information_page_title->set_height(information_page_title->scale()[1] * 2.5, false);

    // Créer "navigation_container"
    navigation_container = main_hud->new_hud_object("navigation_container", main_hud, 1, 1, glm::vec4(32, 32, 70, 255), "hud_default");
    navigation_container->set_height(1.0, false);
    navigation_container->set_position(glm::vec3(-0.75, 0, 0));
    navigation_container->set_width((250.0/1000.0) * (10.0/6.0), false);

    // Créer "navigation_explaination_button"
    navigation_explaination_button = main_hud->new_hud_object<HUD_Button>("navigation_explaination_button", navigation_container, 1, 1, glm::vec4(0, 0, 0, 255), "hud_default");
    navigation_explaination_button->set_background_color(glm::vec4(255, 255, 255, 255));
    navigation_explaination_button->set_cursor_overflighted(GLFW_HAND_CURSOR);
    navigation_explaination_button->set_font_color(glm::vec4(255, 255, 255, 255));
    navigation_explaination_button->set_font_size(75);
    navigation_explaination_button->set_text("Explications");
    navigation_explaination_button->set_position(glm::vec3(0, -0.25, 0));
    navigation_explaination_button->set_width(0.5);
    navigation_explaination_button->set_height(navigation_explaination_button->scale()[1] * 2.5, false);

    // Créer "navigation_information_button"
    navigation_information_button = main_hud->new_hud_object<HUD_Button>("navigation_information_button", navigation_container, 1, 1, glm::vec4(0, 0, 0, 255), "hud_default");
    navigation_information_button->set_background_color(glm::vec4(255, 255, 255, 255));
    navigation_information_button->set_cursor_overflighted(GLFW_HAND_CURSOR);
    navigation_information_button->set_font_color(glm::vec4(255, 255, 255, 255));
    navigation_information_button->set_font_size(75);
    navigation_information_button->set_text("Informations");
    navigation_information_button->set_position(glm::vec3(0, -0.75, 0));
    navigation_information_button->set_width(0.5);
    navigation_information_button->set_height(navigation_information_button->scale()[1] * 2.5, false);

    // Créer "navigation_simulation_button"
    navigation_simulation_button = main_hud->new_hud_object<HUD_Button>("navigation_simulation_button", navigation_container, 1, 1, glm::vec4(0, 0, 0, 255), "hud_default");
    navigation_simulation_button->set_background_color(glm::vec4(255, 255, 255, 255));
    navigation_simulation_button->set_cursor_overflighted(GLFW_HAND_CURSOR);
    navigation_simulation_button->set_font_color(glm::vec4(255, 255, 255, 255));
    navigation_simulation_button->set_font_size(75);
    navigation_simulation_button->set_text("Simulation");
    navigation_simulation_button->set_position(glm::vec3(0, 0.25, 0));
    navigation_simulation_button->set_width(0.5);
    navigation_simulation_button->set_height(navigation_simulation_button->scale()[1] * 2.5, false);

    // Créer "navigation_welcome_button"
    navigation_welcome_button = main_hud->new_hud_object<HUD_Button>("navigation_welcome_button", navigation_container, 1, 1, glm::vec4(0, 0, 0, 255), "hud_default");
    navigation_welcome_button->set_background_color(glm::vec4(255, 255, 255, 255));
    navigation_welcome_button->set_cursor_overflighted(GLFW_HAND_CURSOR);
    navigation_welcome_button->set_font_color(glm::vec4(255, 255, 255, 255));
    navigation_welcome_button->set_font_size(100);
    navigation_welcome_button->set_text("Accueil");
    navigation_welcome_button->set_position(glm::vec3(0, 0.75, 0));
    navigation_welcome_button->set_width(0.5);
    navigation_welcome_button->set_height(navigation_welcome_button->scale()[1] * 2.5, false);

    // Créer "welcome_page"
    welcome_page = main_hud->new_hud_object<HUD_Object>("welcome_page", main_hud, 1, 1, glm::vec4(192, 192, 192, 255), "hud_default");
    welcome_page->set_height(1.0, false);
    welcome_page->set_position(glm::vec3(0.25, 0, 0));
    welcome_page->set_width((750.0/1000.0) * (10.0/6.0), false);

    // Créer "welcome_page_text"
    welcome_page_text = main_hud->new_hud_object<HUD_Text>("welcome_page_text", welcome_page, 1, 1, glm::vec4(0, 0, 0, 255), "hud_default");
    welcome_page_text->set_background_color(glm::vec4(0, 0, 0, 0));
    welcome_page_text->set_font_color(glm::vec4(0, 0, 0, 255));
    welcome_page_text->set_font_size(30);
    welcome_page_text->set_text(scls::to_utf_8("Bienvenue dans ce petit logiciel. Si vous lisez ceci, vous êtes soit un de mes professeurs, soit\nun de mes camarades de classe, soit une autre personne. Dans ce cas là, je vous recommande\nde ne pas vous baser sur ce logiciel pour avoir une idée de ce dont Aster Système est capable.\n|\n|\nCe logiciel est un outil de révision conçu pour la matière ES SVT. Il se concentre sur une partie\nd'un chapitre, la mesure d'une population par échantillonage. Pour cela, il incorpore les explications\nde la technique, ainsi qu'un outil de simulation, pour mieux la comprendre.\n|\n|\nCe logiciel vous est offert par " + developer_informations + ". Si vous voyez une quelconque erreur ou\ncomportement inatendus, contactez moi sur l'adresse e-mail : astersystemeoff@gmail.com.\nSi vous voulez quelques infos sur le logiciel, rendez vous dans la rubrique \"Informations\".\nJ'espère sincérement qu'il saura vous convaincre ! Bonne chance dans vos révisions !"));
    welcome_page_text->set_position(glm::vec3(0, -0.35, 0));
    welcome_page_text->set_width(0.59);
    welcome_page_text->set_height(welcome_page_text->scale()[1] * 2.5, false);

    // Créer "welcome_page_title"
    welcome_page_title = main_hud->new_hud_object<HUD_Text>("welcome_page_title", welcome_page, 1, 1, glm::vec4(0, 0, 0, 255), "hud_default");
    welcome_page_title->set_background_color(glm::vec4(0, 0, 0, 0));
    welcome_page_title->set_font_color(glm::vec4(0, 0, 0, 255));
    welcome_page_title->set_font_size(300);
    welcome_page_title->set_text("Accueil");
    welcome_page_title->set_position(glm::vec3(0, 0.65, 0));
    welcome_page_title->set_width(0.35);
    welcome_page_title->set_height(welcome_page_title->scale()[1] * 2.5, false);

    // Afficher proprement la fenêtre
    core->set_current_hud("main");
    core->set_current_scene("");

    // Rend la souris utilisable
    core->enable_cursor();
}

// Fonction "unset_all_page", cachant toutes les pages du programme.
void unset_all_page() {
    // Cacher les pages
    explaination_page->set_visible(false);
    information_page->set_visible(false);
    welcome_page->set_visible(false);

    navigation_container->set_visible(true);
}

// Fonction "set_explaination_page", permettant d'afficher la page d'explication du programme.
// La variable "part" permet de savoir qu'elle partie de l'explication afficher.
void set_explaination_page(unsigned char part = false) {
    // Cache toutes les pages potentiellements affichées et montre la bonne
    unset_all_page();
    explaination_page->set_visible(true);


}

// Fonction "set_information_page", permettant d'afficher la page d'information du programme.
void set_information_page() {
    // Cache toutes les pages potentiellements affichées et montre la bonne
    unset_all_page();
    information_page->set_visible(true);
}

// Fonction "set_welcome_page", permettant d'afficher la page d'accueil du programme.
void set_welcome_page() {
    // Cache toutes les pages potentiellements affichées et montre la bonne
    unset_all_page();
    welcome_page->set_visible(true);
}

// Fonction "main", représentant la première (et seul) fonction appelé naturellement par le système d'exploitation au démarrage du programme.
// Tout par d'elle.
int main(int argc, char* argv[])
{
    // Création de la fenêtre graphique "core"
    core = new Game(1000, 600, argv[0], true);

    // Crée la fenêtre
    create_window();

    // Mettre la page d'accueil au démarrage
    set_welcome_page();

    // Boucle infini permettant de mettre à jour la fenêtre, et de la rendre fonctionelle
    while(core->run()) {
        core->update_event();
        core->update();

        // Gérer les évènements de navigation
        if(navigation_explaination_button->is_clicked()) {
            set_explaination_page();
        }
        else if(navigation_information_button->is_clicked()) {
            set_information_page();
        }
        else if(navigation_simulation_button->is_clicked()) {

        }
        else if(navigation_welcome_button->is_clicked()) {
            set_welcome_page();
        }

        core->render();
    }

    delete core; core = 0;
    return 0;
}
