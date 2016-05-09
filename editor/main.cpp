#include <gtkmm.h>

typedef Glib::RefPtr<Gtk::Application> App;

int main(int argc, char *argv[])
{
    App app = Gtk::Application::create(argc, argv, "org.gtkmm.examples.base");
    Gtk::Window window;
    window.set_default_size(200, 200);

    return app->run(window);
}