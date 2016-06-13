//
// Created by marcos on 05/06/16.
//

#include "EditorApp.h"
#include "EditorMainWindow.h"
#include "ChamberLevel.h"
#include <iostream>
#include <giomm.h>
#include <gtkmm/dialog.h>
#include <gtkmm/filechooserdialog.h>
#include <gtkmm/aboutdialog.h>

#define MAIN_WINDOW 0

EditorApp::EditorApp()
        : Gtk::Application("Megaman.Editor") {
    open_file_name = "";
    Glib::set_application_name("Megaman Begins - Level Editor");
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
    add_action("saveas",
               sigc::mem_fun(*this, &EditorApp::on_menu_file_save_as));
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
                    "        <item>"
                    "          <attribute name='label' translatable='yes'>Save As...</attribute>"
                    "          <attribute name='action'>app.saveas</attribute>"
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
                    "          <attribute name='action'>app.about</attribute>"
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

    //About
    about.set_program_name("Megaman Begins - Level Editor");
    about.set_logo(Gdk::Pixbuf::create_from_file("../sprites/items/life.png"));
    about.set_comments("This is a tool for level creation and editing "
                               "for \nMegaman Begins.\n The full game can be found "
                               "in our");

    about.set_website("https://github.com/FedericoAmura/Taller2016C1TP4MegamanInicia");
    about.set_website_label("Github");
    std::vector<Glib::ustring> list_authors;
    list_authors.push_back("Marcos Vrljicak");
    list_authors.push_back("Federico Amura");
    list_authors.push_back("Lucas Nicolas Dominguez");
    about.set_authors(list_authors);
    about.signal_response().connect(
            sigc::mem_fun(*this, &EditorApp::on_about_dialog_response) );
}

void EditorApp::on_activate() {
    create_window();
}

void EditorApp::create_window() {
    Level* main = new Level;
    ChamberLevel* chamber = new ChamberLevel;
    main_ws = new Workspace(main);
    chamber_ws = new Workspace(chamber);
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
    main_ws->replaceLevel();
    chamber_ws->replaceLevel();
}

void EditorApp::on_menu_file_open() {
    Gtk::FileChooserDialog open("Open file",
                                  Gtk::FILE_CHOOSER_ACTION_OPEN);
    open.set_transient_for(*win);

    //buttons
    open.add_button("_Cancel", Gtk::RESPONSE_CANCEL);
    open.add_button("Open", Gtk::RESPONSE_OK);

    //filter
    Glib::RefPtr<Gtk::FileFilter> filter_json = Gtk::FileFilter::create();
    filter_json->set_name("JSON files");
    filter_json->add_pattern("*.json");
    open.add_filter(filter_json);

    int result = open.run();
    switch(result) {
        case(Gtk::RESPONSE_OK): {
            open_file_name = open.get_filename();
            main_ws->replaceLevel(open_file_name);
            chamber_ws->replaceLevel(open_file_name);
            break;
        } case(Gtk::RESPONSE_CANCEL): {
            break;
        } default: {
            break;
        }
    }
}

void EditorApp::on_menu_file_save() {
    if (open_file_name == "") {
        on_menu_file_save_as();
    } else {
        main_ws->save(open_file_name);
        chamber_ws->save(open_file_name);
    }
}

void EditorApp::on_menu_file_save_as() {
    Gtk::FileChooserDialog open("Save file",
                                Gtk::FILE_CHOOSER_ACTION_SAVE);
    open.set_transient_for(*win);

    //buttons:
    open.add_button("_Cancel", Gtk::RESPONSE_CANCEL);
    open.add_button("Save", Gtk::RESPONSE_OK);

    int result = open.run();
    switch(result) {
        case(Gtk::RESPONSE_OK): {
            open_file_name = open.get_filename();
            on_menu_file_save();
            break;
        } case(Gtk::RESPONSE_CANCEL): {
            break;
        } default: {
            break;
        }
    }
}

void EditorApp::on_menu_help_about() {
    about.set_transient_for(*win);
    about.show();
}

void EditorApp::on_menu_file_quit() {
    quit();
    std::vector<Gtk::Window*> windows = get_windows();
    for (uint i = 0; i < windows.size(); ++i){
        windows[i]->hide();
    }
}

void EditorApp::on_about_dialog_response(int response_id) {
    if((response_id == Gtk::RESPONSE_CLOSE) ||
       (response_id == Gtk::RESPONSE_CANCEL) ) {
        about.hide();
    }
}


