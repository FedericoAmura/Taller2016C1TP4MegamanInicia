//
// Created by marcos on 11/06/16.
//

#ifndef MEGAMAN_BACKGROUNDCOMBOBOX_H
#define MEGAMAN_BACKGROUNDCOMBOBOX_H

#include <gtkmm/combobox.h>
#include <gtkmm/liststore.h>
#include "../common/SpriteDispenser.h"

typedef Glib::RefPtr<Gdk::Pixbuf> Pixbuf;

class BackgroundComboBox : public Gtk::ComboBox {
public:
    BackgroundComboBox(SpriteDispenser& sprites);
    string getSelected();

private:
    class ModelColumns : public Gtk::TreeModel::ColumnRecord {
    public:
        ModelColumns() {
            add(m_col_img);
            add(m_col_name);
            add(m_col_filepath);
        }
        Gtk::TreeModelColumn<Pixbuf> m_col_img;
        Gtk::TreeModelColumn<Glib::ustring> m_col_name;
        Gtk::TreeModelColumn<Glib::ustring> m_col_filepath;
    };

    ModelColumns columns;
    Gtk::CellRendererText m_cell;
    Glib::RefPtr<Gtk::ListStore> m_refTreeModel;


};


#endif //MEGAMAN_BACKGROUNDCOMBOBOX_H
