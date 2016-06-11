//
// Created by marcos on 11/06/16.
//

#include "BackgroundComboBox.h"
#include "../entities.h"

BackgroundComboBox::BackgroundComboBox(SpriteDispenser& sprites) {
    m_refTreeModel = Gtk::ListStore::create(columns);
    set_model(m_refTreeModel);

    //Fill the ComboBox's Tree Model:
    Gtk::TreeModel::Row row = *(m_refTreeModel->append());
    row[columns.m_col_filepath] = sprites.get(SNOW);
    row[columns.m_col_img] = Gdk::Pixbuf::create_from_file(sprites.get(SNOW))
            ->scale_simple(30, 20, Gdk::INTERP_BILINEAR);
    row[columns.m_col_name] = "Snow";
    set_active(row);

    row = *(m_refTreeModel->append());
    row[columns.m_col_filepath] = sprites.get(SPOOKY);
    row[columns.m_col_img] = Gdk::Pixbuf::create_from_file(sprites.get(SPOOKY))
            ->scale_simple(30, 20, Gdk::INTERP_BILINEAR);
    row[columns.m_col_name] = "Spooky";
    set_active(row);

    row = *(m_refTreeModel->append());
    row[columns.m_col_filepath] = sprites.get(ROCK);
    row[columns.m_col_img] = Gdk::Pixbuf::create_from_file(sprites.get(ROCK))
            ->scale_simple(30, 20, Gdk::INTERP_BILINEAR);
    row[columns.m_col_name] = "Rock";
    set_active(row);

    row = *(m_refTreeModel->append());
    row[columns.m_col_filepath] = sprites.get(CITY);
    row[columns.m_col_img] = Gdk::Pixbuf::create_from_file(sprites.get(CITY))
            ->scale_simple(30, 20, Gdk::INTERP_BILINEAR);
    row[columns.m_col_name] = "City";
    set_active(row);

    row = *(m_refTreeModel->append());
    row[columns.m_col_filepath] = sprites.get(VALLEY);
    row[columns.m_col_img] = Gdk::Pixbuf::create_from_file(sprites.get(VALLEY))
            ->scale_simple(30, 20, Gdk::INTERP_BILINEAR);
    row[columns.m_col_name] = "Valley";
    set_active(row);

    pack_start(columns.m_col_img);
    pack_start(columns.m_col_name);

    /*
    set_cell_data_func(m_cell, sigc::mem_fun(*this, &ExampleWindow::on_cell_data_extra));
    pack_start(m_cell);*/

    /*
    //Connect signal handler:
    m_Combo.signal_changed().connect( sigc::mem_fun(*this, &ExampleWindow::on_combo_changed) );
     */

    show_all_children();
}

string BackgroundComboBox::getSelected() {
    Gtk::TreeModel::iterator iter = get_active();
    if (iter) {
        Gtk::TreeModel::Row row = *iter;
        ModelColumns columns;
        Glib::ustring str = row[columns.m_col_filepath];
        return str.raw();
    } else {
        return "";
    }
}



