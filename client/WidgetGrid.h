/*
 * WidgetGrid.h
 *
 *  Created on: May 10, 2016
 *      Author: freddy
 */

#ifndef SRC_WIDGETGRID_H_
#define SRC_WIDGETGRID_H_

#include <gtkmm/fixed.h>

class WidgetGrid : public Gtk::Fixed {
public:
	WidgetGrid();
	virtual ~WidgetGrid();
};

#endif /* SRC_WIDGETGRID_H_ */
