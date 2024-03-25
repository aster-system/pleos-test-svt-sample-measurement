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
#include <random>

// Déclaration de la structure permettant d'afficher des individus
struct Individual {
    // Dernières coordonnées de l'individu
    unsigned int last_x = 0;
    unsigned int last_y = 0;

    // Si l'individu est marqué ou non
    bool marked = false;

    // Coordonnées actuelles de l'individu
    unsigned int x = 0;
    unsigned int y = 0;

    // Couleur de l'individu
    unsigned char blue = 255;
    unsigned char green = 0;
    unsigned char red = 0;
};

// Déclaration de toutes les variables globales du programme

// Informations sur moi
static std::string developer_informations = "Matt Code";

// Variable nécessaire à la simulation
// Variable contenant le nombre d'individus capturé pendant la première capture
static unsigned short first_capture = 0;
// Variable contenant le nombre d'individus marqués durant la dernière capture
static unsigned short marked_individuals = 0;
// Variable contenant le pourcentage d'individus marqués durant la dernière capture
static double marked_individuals_purcentage = 0;
// Variable contenant les données des individus de la partie simulation
static std::vector<Individual> simulation_individuals = std::vector<Individual>();
// Variable contenant le nombre total d'individu non marqués dans la simulation
static double total_unmarked_simulation = 0;

// Textes d'explications
// Numéro de la page d'explication (0 = idée, 1 = pratique)
static char explaination_part = 0;
// Contenu de la première partie de l'explication ("idée")
static std::string explaination_1 = scls::to_utf_8("L'idée de la méthode est d'utiliser un ratio (une fraction) pour calculer le nombre d'individus.\nEn effet, si on sait qu'un certain nombre d'individus marqués représente un certain pourcentage\nd'individus marqués, on peut estimer le nombre total d'individus grâce aux équations suivantes :\n\n% individus marqués + % individus non marqués = 100%\nQu'on peut changer en :\n100% - % individus marqués = % individus non marqués\n\nOn peut donc calculer le pourcentage d'individus marqués et non marqués.\nOn peut ensuite calculer le nombre d'invidus non marqués grâce aux lois des statistiques :\n\n  % individus marqués             nombre individus marqués  \n----------------------------     =     ---------------------------------\n% individus non marqués         nombre individus non marqués\nQu'on peut modifier facilement comme ça :\n                                                        % individus non marqués\nnombre individus non marqués = nombre individus marqués X ----------------------------------\n                                                        % individus marqués\nNous pouvons calculer le nombre d'indivus non marqués, et aussi le nombre d'individus total.\n\nL'avantage de cette technique est la possibilité de la réaliser sur un nombre réduit\nd'individus (dans la mesure où l'on connait le coefficient de réduction d'une partie de l'équation), et\nd'estimer le résultat sur cette même population à plus grande échelle, en appliquant le coefficient.\nVoici le calcul pour le nombre d'individus total :\n\nnombre indivus total capturé X coefficient = nombre indivus total");
// Contenu de la deuxième partie de l'explication ("pratique")
static std::string explaination_2 = scls::to_utf_8("Dans la nature, il est impossible d'utiliser cette technique comme ça, car trop de paramètres de\nl'équation nous sont inconnus. Il faut donc les créer manuellement. Pour cela, les chercheurs vont\nréaliser une première capture de M individus, qui seront tous marqués.\n\nLes chercheurs vont ensuite attendre que ces individus se mélangent avec les autres individus de la\npopulation à étudier. Ensuite, une recapture est réalisée, où n individus sont recapturés. Dans cette\nrecapture, les chercheurs devrait trouver m individus marqués. On peut donc calculer\nla proportion p d'individus marqués :\n\np = m / n\n\nEn admettant que la population recapturée et la population totale sont hétérogènes, on peut donc\nestimer la proportion d'individus marqués dans la population totale : p. Grâce au calcul vu\nprécédemment, on peut estimer le nombre d'individus non marqués, puis total de la population :\n\n                                   1 - p\nnombre individus non marqués = M X ------\n                                   p\nnombre individus non marqués + nombre individus marqués = nombre d'individus total\n\nNous pouvons donc estimer le nombre d'individus total. Plusieurs modifications de ce calcul\npeuvent donner au même résultat, selon le contexte et la forme du résultat souhaitée. Il n'est\ncependant pas extrêmement fiable, car l'hétérogénité de la population n'est pas garantie.");
// Titre de la première partie de l'explication ("idée")
static std::string explaination_1_title = scls::to_utf_8("Idée");
// Titre de la deuxième partie de l'explication ("pratique")
static std::string explaination_2_title = scls::to_utf_8("Pratique");

// Textes de simulation
// Contenu du bouton pendant la simulation
static std::string simulation_next = "Suivant";
// Numéro de l'étape de simulation actuelle
static char simulation_part = 0;
// Contenu du bouton à la fin de la simulation
static std::string simulation_last_next = "Terminer";
// Contenu de l'avant siumlation
static std::string simulation_0 = "Lancer la simulation.";
// Contenu du bouton avant la simulation
static std::string simulation_0_next = "Commencer";
// Contenu de la première partie de la simulation
static std::string simulation_1 = scls::to_utf_8("Nous avons une population\n(en bleu) d'individus, avec\nentre 500 et 1000 individus,\nque nous souhaitons\nétudier.");
// Contenu de la deuxième partie de la simulation
static std::string simulation_2 = scls::to_utf_8("Nous capturons des individus,\ntous ceux dans la partie\njaune. Cela représente\nen tout _ individus.");
// Contenu de la troisième partie de la simulation
static std::string simulation_3 = scls::to_utf_8("Nous laissons les individus\nse remélanger entre eux\nde manière à ce que la\npopulation devienne hétérogène.");
// Contenu de la quatrième partie de la simulation
static std::string simulation_4 = scls::to_utf_8("Nous recapturons des individus,\ntous ceux dans la partie jaune.\nCela représente en tout _\nindividus. Sur ces individus, *\nsont marqués.\nOn calcul le pourcentage\nd'individus marqués :\n\n*   \np = ----- = $%\n_   ");
// Contenu de la cinquième partie de la simulation
static std::string simulation_5 = scls::to_utf_8("Environ $% d'individus sont\nmarqués dans la population. On\npeut appliquer le calcul\nd'individus non marqués\nO de la population :\n\n       1 - !  \nO = ; X ---------- = |\n         !   \n\nOn peut calculer le total\nd'individus T\n\nT = O + M = | + ; = ~\n\nIl y a environ ~ individus\n dans la population.\nLe nombre réel est <.");

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
// Variable contenant le bouton permettant de changer (passer à la prochaine) la partie explication de la page de la partie explication
static HUD_Button* explaination_page_part_after = 0;
// Variable contenant le bouton permettant de changer (passer à celle d'avant) la partie explication de la page de la partie explication
static HUD_Button* explaination_page_part_before = 0;
// Variable contenant le titre de la partie explication de la page de la partie explication
static HUD_Text* explaination_page_part_title = 0;
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

// Variable de la partie simulation
// Variable contenant la page de la partie simulation
static HUD_Object* simulation_page = 0;
// Variable contenant la simulation de la page de la partie simulation
static HUD_Text* simulation_page_image = 0;
// Variable contenant le bouton "suivant" de la page de la partie simulation
static HUD_Text* simulation_page_next = 0;
// Variable contenant le texte de la page de la partie simulation
static HUD_Text* simulation_page_text = 0;
// Variable contenant le titre de la page de la partie simulation
static HUD_Text* simulation_page_title = 0;

// Variable de la partie accueil
// Variable contenant la page de la partie accueil
static HUD_Object* welcome_page = 0;
// Variable contenant le texte de la page de la partie accueil
static HUD_Text* welcome_page_text = 0;
// Variable contenant le titre de la page de la partie accueil
static HUD_Text* welcome_page_title = 0;

// Fonction "create_window", créant et définissant chaque pages du programme
void create_window() {
    developer_informations = scls::read_file("creator");

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

    // Créer "explaination_page_part_after"
    explaination_page_part_after = main_hud->new_hud_object<HUD_Button>("explaination_page_part_after", explaination_page, 1, 1, glm::vec4(0, 0, 0, 255), "hud_default");
    explaination_page_part_after->set_background_color(glm::vec4(255, 255, 255, 255));
    explaination_page_part_after->set_cursor_overflighted(GLFW_HAND_CURSOR);
    explaination_page_part_after->set_font_color(glm::vec4(0, 0, 0, 255));
    explaination_page_part_after->set_font_size(75);
    explaination_page_part_after->set_text(">");
    explaination_page_part_after->set_position(glm::vec3(0.5, 0.4, 0));
    explaination_page_part_after->set_height(0.035);
    explaination_page_part_after->set_height(explaination_page_part_after->scale()[1] * 2.5, false);

    // Créer "explaination_page_part_before"
    explaination_page_part_before = main_hud->new_hud_object<HUD_Button>("explaination_page_part_before", explaination_page, 1, 1, glm::vec4(0, 0, 0, 255), "hud_default");
    explaination_page_part_before->set_background_color(glm::vec4(255, 255, 255, 255));
    explaination_page_part_before->set_cursor_overflighted(GLFW_HAND_CURSOR);
    explaination_page_part_before->set_font_color(glm::vec4(0, 0, 0, 255));
    explaination_page_part_before->set_font_size(75);
    explaination_page_part_before->set_text("<");
    explaination_page_part_before->set_position(glm::vec3(-0.5, 0.4, 0.1));
    explaination_page_part_before->set_height(0.035);
    explaination_page_part_before->set_height(explaination_page_part_before->scale()[1] * 2.5, false);

    // Créer "explaination_page_part_title"
    explaination_page_part_title = main_hud->new_hud_object<HUD_Text>("explaination_page_part_title", explaination_page, 1, 1, glm::vec4(0, 0, 0, 255), "hud_default");
    explaination_page_part_title->set_background_color(glm::vec4(0, 0, 0, 0));
    explaination_page_part_title->set_font_color(glm::vec4(0, 0, 0, 255));
    explaination_page_part_title->set_font_size(300);
    explaination_page_part_title->set_text(explaination_1_title);
    explaination_page_part_title->set_position(glm::vec3(0, 0.4, 0));
    explaination_page_part_title->set_height(0.035);
    explaination_page_part_title->set_height(explaination_page_part_title->scale()[1] * 2.5, false);

    // Créer "explaination_page_text"
    explaination_page_text = main_hud->new_hud_object<HUD_Text>("explaination_page_text", explaination_page, 1, 1, glm::vec4(0, 0, 0, 255), "hud_default");
    explaination_page_text->set_background_color(glm::vec4(0, 0, 0, 0));
    explaination_page_text->set_font_color(glm::vec4(0, 0, 0, 255));
    explaination_page_text->set_font_size(30);
    explaination_page_text->set_text(explaination_1);
    explaination_page_text->set_position(glm::vec3(0, -0.35, 0));
    explaination_page_text->set_width(0.59);
    explaination_page_text->set_height(explaination_page_text->scale()[1] * 2.5, false);

    // Créer "explaination_page_title"
    explaination_page_title = main_hud->new_hud_object<HUD_Text>("explaination_page_title", explaination_page, 1, 1, glm::vec4(0, 0, 0, 255), "hud_default");
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
    information_page_text->set_text(scls::to_utf_8(license + "\n|\n|\nCe logiciel est réalisé avec un langage de programmation appelé C++, plus complexe mais\nplus rapide et logique que Python. Il utilise l'API graphique \"SCLS Graphic Benoit\"\n(développé par moi même), utilisant les APIs GLFW, GlaD, GLM et OpenGL 3.3. Il utilise aussi\nles bibliothèques C++ \"SCLS Foundation Leonhard\" (développé par moi même),\nutilisant les bibliothèques FreeType et ZLib.\nAllez sur mon site web https://aster-system.github.io/aster-system/ pour plus d'informations.\n|\n|\nCe logiciel est un prototype d'un futur ensemble de logiciel appelé PLEOS pour Pack de\nLogiciels Éducatifs Open Source. Même si ce projet n'est qu'au stade d'idée, il permettrai\nde grandement faciliter l'enseignement par les professeurs et l'apprentissage par les élèves.\nPour plus d'infos, allez sur mon site web https://aster-system.github.io/aster-system/projects/pleos.html."));
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

    // Créer "simulation_page"
    simulation_page = main_hud->new_hud_object<HUD_Object>("simulation_page", main_hud, 1, 1, glm::vec4(192, 192, 192, 255), "hud_default");
    simulation_page->set_height(1.0, false);
    simulation_page->set_position(glm::vec3(0.25, 0, 0));
    simulation_page->set_width((750.0/1000.0) * (10.0/6.0), false);

    // Crée "simulation_page_image"
    simulation_page_image = main_hud->new_hud_object<HUD_Text>("simulation_page_image", simulation_page, 1000, 1000, glm::vec4(255, 255, 255, 255), "hud_default");
    simulation_page_image->set_border_width(0.015);
    simulation_page_image->set_position(glm::vec3(0.2, -0.25, 0));
    simulation_page_image->set_height(0.45);
    simulation_page_image->set_height(simulation_page_image->scale()[1] * 2.5, false);

    // Créer "simulation_page_next"
    simulation_page_next = main_hud->new_hud_object<HUD_Button>("simulation_page_next", simulation_page, 1, 1, glm::vec4(0, 0, 0, 255), "hud_default");
    simulation_page_next->set_background_color(glm::vec4(1, 1, 1, 1));
    simulation_page_next->set_border_width(0.025);
    simulation_page_next->set_cursor_overflighted(GLFW_HAND_CURSOR);
    simulation_page_next->set_font_color(glm::vec4(0, 0, 0, 255));
    simulation_page_next->set_font_size(100);
    simulation_page_next->set_ouf_offset(0.05);
    simulation_page_next->set_text("Commencer");
    simulation_page_next->set_position(glm::vec3(-0.375, 0.375, 0));
    simulation_page_next->set_width(0.2);
    simulation_page_next->set_height(simulation_page_next->scale()[1] * 2.5, false);

    // Créer "simulation_page_text"
    simulation_page_text = main_hud->new_hud_object<HUD_Text>("simulation_page_text", simulation_page, 1, 1, glm::vec4(0, 0, 0, 255), "hud_default");
    simulation_page_text->set_background_color(glm::vec4(0, 0, 0, 0));
    simulation_page_text->set_font_color(glm::vec4(0, 0, 0, 255));
    simulation_page_text->set_font_size(50);
    simulation_page_text->set_text(simulation_0);
    simulation_page_text->set_position(glm::vec3(-0.375, 0, 0));
    simulation_page_text->set_width(0.2);
    simulation_page_text->set_height(simulation_page_text->scale()[1] * 2.5, false);


    // Créer "simulation_page_title"
    simulation_page_title = main_hud->new_hud_object<HUD_Text>("simulation_page_title", simulation_page, 1, 1, glm::vec4(0, 0, 0, 255), "hud_default");
    simulation_page_title->set_background_color(glm::vec4(0, 0, 0, 0));
    simulation_page_title->set_font_color(glm::vec4(0, 0, 0, 255));
    simulation_page_title->set_font_size(300);
    simulation_page_title->set_text("Simulation");
    simulation_page_title->set_position(glm::vec3(0, 0.65, 0));
    simulation_page_title->set_width(0.35);
    simulation_page_title->set_height(simulation_page_title->scale()[1] * 2.5, false);

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
    welcome_page_text->set_text(scls::to_utf_8("Bienvenue dans ce petit logiciel. Si vous lisez ceci, vous êtes soit un de mes professeurs, soit\nun de mes camarades de classe, soit une autre personne. Dans ce cas là, je vous recommande\nde ne pas vous baser sur ce logiciel pour avoir une idée de ce dont Aster Système est capable.\n|\n|\nCe logiciel est un outil de révision conçu pour la matière ES SVT. Il se concentre sur une partie\nd'un chapitre, la mesure d'une population par échantillonage. Pour cela, il incorpore les explications\nde la technique, ainsi qu'un outil de simulation, pour mieux la comprendre.\n|\n|\nCe logiciel vous est offert par " + developer_informations + ". Si vous voyez une quelconque erreur ou\ncomportement inattendu, contactez moi sur l'adresse e-mail : astersystemeoff@gmail.com.\nSi vous voulez quelques infos sur le logiciel, rendez vous dans la rubrique \"Informations\".\nJ'espère sincérement qu'il saura vous convaincre ! Bonne chance dans vos révisions !"));
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
    simulation_page->set_visible(false);
    welcome_page->set_visible(false);

    navigation_container->set_visible(true);
}

// Fonction "set_explaination_page", permettant d'afficher la page d'explication du programme.
// La variable "part" permet de savoir qu'elle partie de l'explication afficher.
void set_explaination_page() {
    // Cache toutes les pages potentiellements affichées et montre la bonne
    if(explaination_page->visible() == false || ((explaination_part == 0 && explaination_page_part_title->get_text() != explaination_1_title)) || (explaination_part == 1 && explaination_page_part_title->get_text() != explaination_2_title)) {
        unset_all_page();
        explaination_page->set_visible(true);

        if(explaination_part == 0) {
            explaination_page_part_title->set_text(explaination_1_title);
            explaination_page_text->set_text(explaination_1);
        }
        else if(explaination_part == 1) {
            explaination_page_part_title->set_text(explaination_2_title);
            explaination_page_text->set_text(explaination_2);
        }

        // Réinitialiser la taille des textes (bug de la librairie SCLS)
        explaination_page_part_title->set_height(0.035);
        explaination_page_part_title->set_height(explaination_page_part_after->scale()[1] * 1.25, false);

        explaination_page_text->set_width(0.59);
        explaination_page_text->set_height(explaination_page_text->scale()[1] * 2.5, false);
    }
}

// Fonction "set_information_page", permettant d'afficher la page d'information du programme.
void set_information_page() {
    // Cache toutes les pages potentiellements affichées et montre la bonne
    unset_all_page();
    information_page->set_visible(true);
}

// Fonction "set_simulation_page", permettant d'afficher la page d'accueil du programme
void set_simulation_page() {
    simulation_page_text->set_position(glm::vec3(-0.375, 0, 0));
    simulation_page_next->set_text(simulation_next);
    simulation_page_next->set_width(0.2);
    simulation_page_next->set_height(simulation_page_next->scale()[1] * 2.5, false);

    if(simulation_part == 0) {
        // Cache toutes les pages potentiellements affichées et montre la bonne
        unset_all_page();
        simulation_page->set_visible(true);

        simulation_page_next->set_text(simulation_0_next);
        simulation_page_next->set_width(0.2);
        simulation_page_next->set_height(simulation_page_next->scale()[1] * 2.5, false);

        simulation_page_text->set_text(simulation_0);
        simulation_page_text->set_width(0.2);
        simulation_page_text->set_height(simulation_page_text->scale()[1] * 2.5, false);

        // Remettre le tout à 0
        simulation_individuals.clear();
        simulation_page_image->get_texture()->get_image()->fill(255, 255, 255); simulation_page_image->get_texture()->change_texture();
    }
    else if(simulation_part == 1) {
        simulation_page_text->set_text(simulation_1);
        simulation_page_text->set_width(0.2);
        simulation_page_text->set_height(simulation_page_text->scale()[1] * 2.5, false);

        scls::Image* img = new scls::Image(1000, 1000, 255, 255, 255);

        // Création des individus
        unsigned short random_number = (rand() % 500) + 500;
        for(int i = 0;i<random_number;i++) {
            Individual individual;
            individual.x = (rand() % 1000);
            individual.y = (rand() % 1000);

            img->set_pixel(individual.x, individual.y, individual.red, individual.green, individual.blue, 255, 10);
            simulation_individuals.push_back(individual);
        }

        // Changer la texture de simulation
        simulation_page_image->get_texture()->set_image(img);
    }
    else if(simulation_part == 2) {
        scls::Image* img = new scls::Image(1000, 1000, 255, 255, 255);

        // Définissions de la zone de capture
        unsigned short x_capture = 250;
        unsigned short y_capture = 250;
        unsigned short width_capture = 500;
        unsigned short height_capture = 500;

        img->draw_rect(x_capture, y_capture, width_capture, height_capture, 255, 255, 0, 255);

        // Création des couleurs nécessaire
        first_capture = 0;
        unsigned char marked_blue = 0;
        unsigned char marked_green = 0;
        marked_individuals = 0;
        unsigned char marked_red = 255;

        // Affichage des individus
        for(int i = 0;i<simulation_individuals.size();i++) {
            Individual individual = simulation_individuals[i];
            unsigned short x = individual.x;
            unsigned short y = individual.y;

            if(x > x_capture && x < x_capture + width_capture && y > y_capture && y < y_capture + height_capture) {
                individual.blue = 0;
                individual.green = 0;
                individual.marked = true;
                individual.red = 255;

                first_capture++;
                marked_individuals++;

                simulation_individuals[i] = individual;
            }

            img->set_pixel(individual.x, individual.y, individual.red, individual.green, individual.blue, 255, 10);
        }

        // Changer la texture de simulation
        simulation_page_image->get_texture()->set_image(img);

        simulation_page_text->set_text(scls::replace(simulation_2, "_", std::to_string(marked_individuals)));
        simulation_page_text->set_width(0.2);
        simulation_page_text->set_height(simulation_page_text->scale()[1] * 2.5, false);
    }
    else if(simulation_part == 3) {
        scls::Image* img = new scls::Image(1000, 1000, 255, 255, 255);

        // Affichage des individus
        for(int i = 0;i<simulation_individuals.size();i++) {
            Individual individual = simulation_individuals[i];
            individual.x = (rand() % 1000);
            individual.y = (rand() % 1000);
            simulation_individuals[i] = individual;

            img->set_pixel(individual.x, individual.y, individual.red, individual.green, individual.blue, 255, 10);
        }

        // Changer la texture de simulation
        simulation_page_image->get_texture()->set_image(img);

        simulation_page_text->set_text(simulation_3);
        simulation_page_text->set_width(0.2);
        simulation_page_text->set_height(simulation_page_text->scale()[1] * 2.5, false);
    }
    else {
        scls::Image* img = new scls::Image(1000, 1000, 255, 255, 255);

        // Définissions de la zone de capture
        unsigned short x_capture = 250;
        unsigned short y_capture = 250;
        unsigned short width_capture = 500;
        unsigned short height_capture = 500;

        img->draw_rect(x_capture, y_capture, width_capture, height_capture, 255, 255, 0, 255);

        // Affichage des individus
        marked_individuals = 0;
        unsigned short total_captured = 0;
        for(int i = 0;i<simulation_individuals.size();i++) {
            Individual individual = simulation_individuals[i];
            unsigned short x = individual.x;
            unsigned short y = individual.y;

            if(x > x_capture && x < x_capture + width_capture && y > y_capture && y < y_capture + height_capture) {
                if(individual.marked)marked_individuals++;
                total_captured++;
            }

            img->set_pixel(individual.x, individual.y, individual.red, individual.green, individual.blue, 255, 10);
        }

        // Changer la texture de simulation
        simulation_page_image->get_texture()->set_image(img);

        if(simulation_part == 4)
        {
            marked_individuals_purcentage = (static_cast<double>(marked_individuals) / static_cast<double>(total_captured));
            unsigned short purcentage = floor(marked_individuals_purcentage * 100);

            simulation_page_text->set_text(scls::replace(scls::replace(scls::replace(simulation_4, "_", std::to_string(total_captured)), "*", std::to_string(marked_individuals)), "$", std::to_string(purcentage)));
            simulation_page_text->set_width(0.2);
            simulation_page_text->set_height(simulation_page_text->scale()[1] * 2.5, false);
        }
        else if(simulation_part == 5) {
            simulation_page_text->set_position(glm::vec3(-0.375, -0.25, 0));

            unsigned short purcentage = floor(marked_individuals_purcentage * 100);
            std::string purcentage_str = "";
            std::vector<std::string> cutted = scls::cut_string(std::to_string(marked_individuals_purcentage), ".");
            purcentage_str += cutted[0] + "." + cutted[1].substr(0, 2);

            total_unmarked_simulation = static_cast<double>(first_capture) * ((1.0 - marked_individuals_purcentage) / marked_individuals_purcentage);
            std::string result_str = std::to_string(static_cast<short>(floor(total_unmarked_simulation)));

            simulation_page_text->set_text(scls::replace(scls::replace(scls::replace(scls::replace(scls::replace(scls::replace(scls::replace(simulation_5, "_", std::to_string(total_captured)), ";", std::to_string(first_capture)), "!", purcentage_str), "|", result_str), "~", std::to_string(static_cast<int>(floor(first_capture + total_unmarked_simulation)))), "<", std::to_string(static_cast<int>(simulation_individuals.size()))), "$", std::to_string(purcentage)));
            simulation_page_text->set_width(0.2);
            simulation_page_text->set_height(simulation_page_text->scale()[1] * 2.5, false);

            simulation_page_next->set_text(simulation_last_next);
            simulation_page_next->set_width(0.2);
            simulation_page_next->set_height(simulation_page_next->scale()[1] * 2.5, false);
        }
    }
}

// Fonction "set_welcome_page", permettant d'afficher la page d'accueil du programme.
void set_welcome_page() {
    // Cache toutes les pages potentiellements affichées et montre la bonne
    unset_all_page();
    welcome_page->set_visible(true);
}

// Permet de changer la page d'explication actuelle
void change_explication_page(bool after) {
    if(after) {
        explaination_part++;
    }
    else {
        explaination_part--;
    }

    if(explaination_part < 0) explaination_part = 1;
    else if(explaination_part > 1) explaination_part = 0;

    set_explaination_page();
}

// Fonction "main", représentant la première (et seul) fonction appelé naturellement par le système d'exploitation au démarrage du programme.
// Tout par d'elle.
int main(int argc, char* argv[]) {
    // Création de la fenêtre graphique "core"
    core = new Game(1000, 600, argv[0], true);
    srand(time(0));

    // Crée la fenêtre
    create_window();

    // Mettre la page d'accueil au démarrage
    set_welcome_page();

    // Boucle infini permettant de mettre à jour la fenêtre, et de la rendre fonctionelle
    while(core->run()) {
        core->update_event();
        core->update();

        // Gérer les évènements de navigation
        if(navigation_explaination_button->is_clicked_during_this_frame()) {
            set_explaination_page();
        }
        else if(navigation_information_button->is_clicked_during_this_frame()) {
            set_information_page();
        }
        else if(navigation_simulation_button->is_clicked_during_this_frame()) {
            simulation_part = 0;
            set_simulation_page();
        }
        else if(navigation_welcome_button->is_clicked_during_this_frame()) {
            set_welcome_page();
        }

        // Gérer les boutons d'explication
        if(explaination_page_part_after->is_clicked_during_this_frame()) {
            change_explication_page(true);
        }
        else if(explaination_page_part_before->is_clicked_during_this_frame()) {
            change_explication_page(false);
        }

        // Gérer les boutons de simulation
        if(simulation_page_next->is_clicked_during_this_frame()) {
            simulation_part++;
            if(simulation_part > 5) simulation_part = 0;
            set_simulation_page();
        }

        core->render();
    }

    delete core; core = 0;
    return 0;
}
