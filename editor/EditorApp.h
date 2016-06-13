//
// Created by marcos on 05/06/16.
//

#ifndef MEGAMAN_EDITORAPP_H
#define MEGAMAN_EDITORAPP_H


#include <gtkmm/application.h>
#include <gtkmm/builder.h>
#include "Level.h"
#include "EditorMainWindow.h"
#include <string>
#include <gtkmm/aboutdialog.h>

using std::string;

class EditorApp : public Gtk::Application {
protected:
    EditorApp();

public:
    static Glib::RefPtr<EditorApp> create();

protected:
    //Handler overrides
    void on_startup() override;
    void on_activate() override;

private:
    EditorMainWindow* win;
    Glib::RefPtr<Gtk::Builder> builder;
    string open_file_name;

    Gtk::AboutDialog about;

    Workspace* main_ws;
    Workspace* chamber_ws;

    void create_window();

    //Handlers
    void on_window_hide(Gtk::Window* window);
    void on_menu_file_new();
    void on_menu_file_open();
    void on_menu_file_save();
    void on_menu_file_save_as();
    void on_menu_file_quit();
    void on_menu_help_about();
    void on_about_dialog_response(int response_id);


};


#endif //MEGAMAN_EDITORAPP_H
