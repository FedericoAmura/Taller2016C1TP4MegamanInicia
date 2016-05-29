//
// Created by marcos on 29/05/16.
//

#ifndef MEGAMAN_ENTITYICONVIEW_H
#define MEGAMAN_ENTITYICONVIEW_H


#include <gtkmm/iconview.h>

class EntityIconView : public Gtk::IconView {
public:
    EntityIconView();
protected:
    void on_drag_data_get(
            const Glib::RefPtr<Gdk::DragContext>&,
            Gtk::SelectionData& selection_data, guint, guint);
    uint getIconFromPath(const Gtk::TreeModel::Path& path);
};


#endif //MEGAMAN_ENTITYICONVIEW_H
