#include <unistd.h>
#include <string.h>
#include <math.h>

#include "orbisPad.h"
#include "cheats.h"
#include "common.h"
#include "menu.h"
#include "menu_gui.h"
#include "libfont.h"
#include "ttf_render.h"

extern game_list_t hdd_cheats;
extern game_list_t hdd_patches;
extern game_list_t online_cheats;
extern game_list_t update_cheats;

extern int close_app;

int menu_options_maxopt = 0;
int *menu_options_maxsel;

int menu_id = 0;												// Menu currently in
int menu_sel = 0;												// Index of selected item (use varies per menu)
int menu_old_sel[TOTAL_MENU_IDS] = { 0 };						// Previous menu_sel for each menu
int last_menu_id[TOTAL_MENU_IDS] = { 0 };						// Last menu id called (for returning)

game_entry_t* selected_entry;
code_entry_t* selected_centry;
int option_index = 0;


