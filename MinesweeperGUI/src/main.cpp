#define _CRT_SECURE_NO_WARNINGS

#include "gui.hpp"
#include "display.hpp"
#include "GUI/dir.hpp"
using namespace std;
using namespace minesweeper;
using namespace gui;
int main(int argc, char* argv[]) {
    gui::util::dir::set_exec_dir(argv[0]);
	form& f = form::get_instance();
    f.set_fps(60).set_title(u8"MinesweeperGUI");
    
    display d = display();

    d.display_scene(SCENE_MENU);
    
    f.draw_until_window_closed();

    
    return 0;
}
