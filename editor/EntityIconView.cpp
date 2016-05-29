//
// Created by marcos on 29/05/16.
//

#include <iostream>
#include <gtkmm/treemodel.h>
#include "EntityIconView.h"
#include "ToolboxModelColumns.h"

void EntityIconView::on_drag_data_get(const Glib::RefPtr<Gdk::DragContext>&,
                                      Gtk::SelectionData& selection_data,
                                      guint, guint) {
    std::vector<Gtk::TreePath> selected = get_selected_items();
    std::vector<Gtk::TreePath>::iterator iter = selected.begin();
    uint id = getIconFromPath(*iter);
    selection_data.set_text(std::to_string(id));
}

EntityIconView::EntityIconView() {
    //signal_drag_begin().connect(sigc::mem_fun(*this, &EntityIconView::on_drag_begin));
    signal_drag_data_get().connect(sigc::mem_fun(*this, &EntityIconView::on_drag_data_get));
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





