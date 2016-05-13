#include <gtkmm.h>
#include <iostream>

typedef Glib::RefPtr<Gtk::Builder> Builder;
typedef Glib::RefPtr<Gtk::Application> App;

using std::cerr;
using std::endl;



int main(int argc, char *argv[]) {
    App app = Gtk::Application::create(argc, argv, "org.gtkmm.example");
    //Load the GtkBuilder file and instantiate its widgets:
    Builder refBuilder = Gtk::Builder::create();
    Gtk::ApplicationWindow* appWindow = NULL;
    try {
        refBuilder->add_from_file("editor_main_window.glade");
    }
    catch(const Glib::FileError& ex) {
        cerr << "FileError: " << ex.what() << endl;
        return 1;
    }
    catch(const Glib::MarkupError& ex) {
        cerr << "MarkupError: " << ex.what() << endl;
        return 1;
    }
    catch(const Gtk::BuilderError& ex) {
        cerr << "BuilderError: " << ex.what() << endl;
        return 1;
    }
    //Get the GtkBuilder-instantiated Dialog:
    refBuilder->get_widget("EditorWindow", appWindow);
    if(appWindow) {
        app->run(*appWindow);
    }
    delete appWindow;
    return 0;
}