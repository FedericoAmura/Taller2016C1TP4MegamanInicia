//
// Created by marcos on 29/05/16.
//

#include <iostream>
#include <gtkmm/treemodel.h>
#include "EntityIconView.h"
#include "ToolboxModelColumns.h"

#define SIDE 25

typedef Glib::RefPtr<Gdk::Pixbuf> Pixbuf_p;

using std::vector;

void EntityIconView::on_drag_data_get(const Glib::RefPtr<Gdk::DragContext>&,
                                      Gtk::SelectionData& selection_data,
                                      guint, guint) {
    vector<Gtk::TreePath> selected = get_selected_items();
    vector<Gtk::TreePath>::iterator iter = selected.begin();
    uint id = getIconFromPath(*iter);
    selection_data.set_text(std::to_string(id));
}

EntityIconView::EntityIconView() {
    signal_drag_data_get().connect(sigc::mem_fun(*this, &EntityIconView::on_drag_data_get));
    signal_selection_changed().connect(
            sigc::mem_fun(*this, &EntityIconView::on_selection_change));
}

uint EntityIconView::getIconFromPath(const Gtk::TreeModel::Path &path) {
    //Estas clases no cuentan con APIs que permitan realizar esta operacion
    //sin desencapsular.
    const Glib::RefPtr<Gtk::TreeModel>& model = get_model();
    Gtk::TreeModel::iterator model_iter = model->get_iter(path);
    Gtk::TreeModel::Row row = *model_iter;
    ToolboxModelColumns m_Columns;
    Gtk::TreeModelColumn<uint> m_col_id;
    uint id = row[m_Columns.m_col_id];
    return id;
}

void EntityIconView::on_drag_begin(const Glib::RefPtr<Gdk::DragContext>& context) {
    vector<Gtk::TreePath> selected = get_selected_items();
    vector<Gtk::TreePath>::iterator iter = selected.begin();
    uint id = getIconFromPath(*iter);
    Pixbuf_p img = Gdk::Pixbuf::create_from_file(sprites.get(id),SIDE,SIDE,0);
    context->set_icon(img, SIDE, SIDE);
}

type_signal_selection_change EntityIconView::signal_selection_change() {
    return m_signal_selection_change;
}


void EntityIconView::on_selection_change() {
    uint id = 0;
    vector<Gtk::TreePath> selected = get_selected_items();
    if (!selected.empty()) {
        vector<Gtk::TreePath>::iterator iter = selected.begin();
        id = getIconFromPath(*iter);
    }
    m_signal_selection_change.emit(id);
}











