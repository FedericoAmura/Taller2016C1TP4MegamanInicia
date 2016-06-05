//
// Created by marcos on 28/05/16.
//

#include <gtkmm/iconview.h>
#include <iostream>
#include "Selector.h"
#include "../common/SpriteDispenser.h"
#include "EntitySet.h"
#include "../entities.h"

#define ICON_WIDTH 62

Selector::Selector() {
    set_size_request(300, -1);
    SpriteDispenser sprites;
    m_TilesLabel.set_text("Tiles");
    m_MobsLabel.set_text("Spawners");
    m_TilesView.set_item_width(ICON_WIDTH);
    m_MobsView.set_item_width(ICON_WIDTH);
    EntitySet tiles(&m_TilesView);
    EntitySet mobs(&m_MobsView);
    vector<IconEntry> tile_entries = {
            IconEntry(STONE_WALL, sprites.get(STONE_WALL), "Wall"),
            IconEntry(SPIKE, sprites.get(SPIKE), "Spike"),
            IconEntry(STONE_LADDER, sprites.get(STONE_LADDER), "Ladder"),
            IconEntry(SKY_PLATFORM, sprites.get(SKY_PLATFORM), "Platform"),
            IconEntry(BOSS_DOOR, sprites.get(BOSS_DOOR), "Boss Door"),
            //IconEntry(STONE_FLOOR, sprites.get(STONE_FLOOR), "Floor")
    };
    vector<IconEntry> mob_entries = {
            IconEntry(MEGAMAN_IDLE_0, sprites.get(MEGAMAN_IDLE_0), "Megaman"),
            IconEntry(BUMBY_0, sprites.get(BUMBY_0), "Bumby"),
            IconEntry(MET_VULNERABLE, sprites.get(MET_VULNERABLE), "Met"),
            IconEntry(SNIPER_ATTACK, sprites.get(SNIPER_ATTACK), "Sniper"),
            IconEntry(JUMPING_SNIPER, sprites.get(JUMPING_SNIPER), "Jumping Sniper"),
            IconEntry(BOMBMAN_ATTACK, sprites.get(BOMBMAN_ATTACK), "Bombman"),
            IconEntry(FIREMAN_CAST_0, sprites.get(FIREMAN_CAST_0), "Fireman"),
            IconEntry(MAGNETMAN_IDLE, sprites.get(MAGNETMAN_IDLE), "Magnetman"),
            IconEntry(SPARKMAN_IDLE, sprites.get(SPARKMAN_IDLE), "Sparkman")
    };
    tiles.fill(tile_entries);
    mobs.fill(mob_entries);
    append_page(m_TilesView, m_TilesLabel);
    append_page(m_MobsView, m_MobsLabel);
    show();
    show_all_children(true);
}

void Selector::setDraggable(vector<Gtk::TargetEntry>& list_targets) {
    this->list_targets = list_targets;
    m_TilesView.enable_model_drag_source(list_targets);
    m_MobsView.enable_model_drag_source(list_targets);

}

void Selector::connect(WorkspaceEventManager* manager) {
    m_TilesView.signal_selection_change()
            .connect(sigc::mem_fun(manager, &WorkspaceEventManager::on_selection_change));
    m_MobsView.signal_selection_change()
            .connect(sigc::mem_fun(manager, &WorkspaceEventManager::on_selection_change));
}






