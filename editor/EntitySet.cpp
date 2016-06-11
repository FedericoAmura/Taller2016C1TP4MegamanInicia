//
// Created by marcos on 22/05/16.
//

#include "EntitySet.h"

EntitySet::EntitySet(Gtk::IconView* view) {
    m_IconView = view;
    ToolboxModelColumns m_Columns;
    model = Gtk::ListStore::create(m_Columns);
    model->set_sort_column(m_Columns.m_col_description, Gtk::SORT_ASCENDING);
    m_IconView->set_model(model);
    m_IconView->set_markup_column(m_Columns.m_col_description);
    m_IconView->set_pixbuf_column(m_Columns.m_col_pixbuf);
}

void EntitySet::fill(vector<IconEntry> entries, uint x, uint y) {
    for (uint i = 0; i < entries.size(); ++i){
        addIcon(entries[i].m_id,
                entries[i].m_filename,
                entries[i].m_description, x, y);
    }
}

void EntitySet::addIcon(const uint id, const string& file, const ustring& descript, uint x, uint y) {
    Gtk::TreeModel::Row row = *(model->append());
    row[m_Columns.m_col_id] = id;
    row[m_Columns.m_col_filename] = file;
    row[m_Columns.m_col_description] = descript;
    Pixbuf image = Gdk::Pixbuf::create_from_file(file)
            ->scale_simple(x, y, Gdk::INTERP_BILINEAR);
    row[m_Columns.m_col_pixbuf] = image;
}





