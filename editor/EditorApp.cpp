//
// Created by marcos on 05/06/16.
//

#include "EditorApp.h"
#include "EditorMainWindow.h"
#include "ChamberLevel.h"
#include <iostream>
#include <giomm.h>

#define MAIN_WINDOW 0

EditorApp::EditorApp()
        : Gtk::Application("Megaman.Editor") {
    Glib::set_application_name("Megaman Begins Level Editor");
}

Glib::RefPtr<EditorApp> EditorApp::create() {
    return Glib::RefPtr<EditorApp>(new EditorApp());
}

void EditorApp::on_startup() {
    Gtk::Application::on_startup();

    //Menu:
    add_action("new",
               sigc::mem_fun(*this, &EditorApp::on_menu_file_new));
    add_action("open",
               sigc::mem_fun(*this, &EditorApp::on_menu_file_open));
    add_action("save",
               sigc::mem_fun(*this, &EditorApp::on_menu_file_save));
    add_action("quit", sigc::mem_fun(*this, &EditorApp::on_menu_file_quit));
    add_action("about", sigc::mem_fun(*this, &EditorApp::on_menu_help_about));

    builder = Gtk::Builder::create();
    Glib::ustring ui_info =
            "<interface>"
                    "  <!-- menubar -->"
                    "  <menu id='menu-editor'>"
                    "    <submenu>"
                    "      <attribute name='label' translatable='yes'>_File</attribute>"
                    "      <section>"
                    "        <item>"
                    "          <attribute name='label' translatable='yes'>New</attribute>"
                    "          <attribute name='action'>app.new</attribute>"
                    "          <attribute name='accel'>&lt;Primary&gt;n</attribute>"
                    "        </item>"
                    "        <item>"
                    "          <attribute name='label' translatable='yes'>Open</attribute>"
                    "          <attribute name='action'>app.open</attribute>"
                    "          <attribute name='accel'>&lt;Primary&gt;o</attribute>"
                    "        </item>"
                    "        <item>"
                    "          <attribute name='label' translatable='yes'>Save</attribute>"
                    "          <attribute name='action'>app.save</attribute>"
                    "          <attribute name='accel'>&lt;Primary&gt;s</attribute>"
                    "        </item>"
                    "      </section>"
                    "      <section>"
                    "        <item>"
                    "          <attribute name='label' translatable='yes'>_Quit</attribute>"
                    "          <attribute name='action'>app.quit</attribute>"
                    "          <attribute name='accel'>&lt;Primary&gt;q</attribute>"
                    "        </item>"
                    "      </section>"
                    "    </submenu>"
                    "    <submenu>"
                    "      <attribute name='label' translatable='yes'>_Help</attribute>"
                    "      <section>"
                    "        <item>"
                    "          <attribute name='label' translatable='yes'>_About</attribute>"
                    "          <attribute name='action'>win.about</attribute>"
                    "        </item>"
                    "      </section>"
                    "    </submenu>"
                    "  </menu>"
                    ""
                    "</interface>";
    try {
        builder->add_from_string(ui_info);
    } catch (const Glib::Error& ex) {
        std::cerr << "Building menus failed: " << ex.what();
    }

    //Get the menubar and the app menu, and add them to the application:
    Glib::RefPtr<Glib::Object> object = builder->get_object("menu-editor");
    Glib::RefPtr<Gio::Menu> gmenu = Glib::RefPtr<Gio::Menu>::cast_dynamic(object);
    if (!gmenu) {
        g_warning("GMenu or AppMenu not found");
    } else {
        set_menubar(gmenu);
    }
}

void EditorApp::on_activate() {
    create_window();
}

void EditorApp::create_window() {
    Level* main = new Level;
    Level* chamber = new ChamberLevel;
    Workspace* main_ws = new Workspace(main);
    Workspace* chamber_ws = new Workspace(chamber);
    win = new EditorMainWindow(main_ws, chamber_ws);
    add_window(*win);
    win->signal_hide().connect(sigc::bind<Gtk::Window*>(
            sigc::mem_fun(*this, &EditorApp::on_window_hide), win));
    win->show();
}

void EditorApp::on_window_hide(Gtk::Window* window) {
    delete window;
}

void EditorApp::on_menu_file_new() {
    win->new_file();
}

void EditorApp::on_menu_file_open() {
    std::cout << "A File|Open menu item was selected." << std::endl;
}

void EditorApp::on_menu_file_save() {
    std::cout << "A File|Save menu item was selected." << std::endl;
}

void EditorApp::on_menu_help_about() {
    std::cout << "App|Help|About was selected." << std::endl;
}

void EditorApp::on_menu_file_quit() {
    quit();
    std::vector<Gtk::Window*> windows = get_windows();
    if (windows.size() > 0){
        windows[MAIN_WINDOW]->hide();
    }
}




