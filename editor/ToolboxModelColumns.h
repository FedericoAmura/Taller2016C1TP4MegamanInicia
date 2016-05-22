//
// Created by marcos on 22/05/16.
//

#ifndef MEGAMAN_TOOLBOXMODELCOLUMNS_H
#define MEGAMAN_TOOLBOXMODELCOLUMNS_H


#include <gtkmm.h>

typedef unsigned int uint;

class ToolboxModelColumns : public Gtk::TreeModelColumnRecord {
public:
    ToolboxModelColumns() {
        add(m_col_id);
        add(m_col_filename);
        add(m_col_description);
        add(m_col_pixbuf);
    }
    Gtk::TreeModelColumn<uint> m_col_id;
    Gtk::TreeModelColumn<Glib::ustring> m_col_filename;
    Gtk::TreeModelColumn<Glib::ustring> m_col_description;
    Gtk::TreeModelColumn<Glib::RefPtr<Gdk::Pixbuf> > m_col_pixbuf;
};


#endif //MEGAMAN_TOOLBOXMODELCOLUMNS_H
