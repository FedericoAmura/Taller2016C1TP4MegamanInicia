//
// Created by marcos on 29/05/16.
//

#ifndef MEGAMAN_ENTITYICONVIEW_H
#define MEGAMAN_ENTITYICONVIEW_H


#include <gtkmm/iconview.h>
#include "../common/SpriteDispenser.h"

typedef sigc::signal<bool, uint> type_signal_selection_change;

class EntityIconView : public Gtk::IconView {
public:
    EntityIconView();
    type_signal_selection_change signal_selection_change();

protected:
    //signals
    type_signal_selection_change m_signal_selection_change;

    //handlers
    void on_drag_begin(const Glib::RefPtr<Gdk::DragContext>& context);
    void on_drag_data_get(
            const Glib::RefPtr<Gdk::DragContext>&,
            Gtk::SelectionData& selection_data, guint, guint);
    void on_selection_change();

private:
    uint getIconFromPath(const Gtk::TreeModel::Path& path);
    SpriteDispenser sprites;
};


#endif //MEGAMAN_ENTITYICONVIEW_H
