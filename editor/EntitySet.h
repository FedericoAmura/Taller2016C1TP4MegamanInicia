//
// Created by marcos on 22/05/16.
//

#ifndef MEGAMAN_ENTITYSET_H
#define MEGAMAN_ENTITYSET_H

#include "ToolboxModelColumns.h"
#include <string>
#include <vector>

using std::vector;
using std::string;
typedef Glib::ustring ustring;
typedef Glib::RefPtr<Gtk::ListStore> ListStore;
typedef Glib::RefPtr<Gdk::Pixbuf> Pixbuf;

struct IconEntry {
    IconEntry(const uint id, const string& filename, const ustring& description)
            : m_id(id),
              m_filename(filename),
              m_description(description) {}
    const uint m_id;
    const string m_filename;
    const Glib::ustring m_description;
};

class EntitySet {
public:
    EntitySet(Gtk::IconView* view);
    void fill(vector<IconEntry> entries);
private:
    void addIcon(const uint id, const string& file, const ustring& descript);
    Gtk::IconView* m_IconView;
    ListStore model;
    ToolboxModelColumns m_Columns;
};




#endif //MEGAMAN_ENTITYSET_H
