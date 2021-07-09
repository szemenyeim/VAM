//  VAM --- Video Assisted Measurement of Animals
//	Copyright( C ) 2016  Márton Szemenyei  

//	This program is free software : you can redistribute it and / or modify
//	it under the terms of the GNU General Public License as published by
//	the Free Software Foundation, either version 3 of the License, or
//	( at your option ) any later version.

//	This program is distributed in the hope that it will be useful,
//	but WITHOUT ANY WARRANTY; without even the implied warranty of
//	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
//	GNU General Public License for more details.

//	You should have received a copy of the GNU General Public License
//	along with this program.If not, see <http://www.gnu.org/licenses/>.

#pragma once

#include <qlabel.h >
#include <qevent.h>
#include <QtWidgets\qscrollarea.h>
#include "Utility.h"

// Custom QLabel class that can emit signals if the mouse is clicked on it or moved above it
class CustomLabel : public QLabel
{
	Q_OBJECT
		signals :
	// Emitted signals 
	void mousePressed( const QPoint& );
	void mouseReleased(const QPoint&);
	void mouseMoved( const QPoint& );

public:
	// Contructors
	CustomLabel( QWidget* parent = 0, Qt::WindowFlags f = 0 );
	CustomLabel( const QString& text, QWidget* parent = 0, Qt::WindowFlags f = 0 );

	// Variables for the crosshair
	bool paintCrosshair;
	int x;
	int y;

	// Variables for rectangle
	bool paintRect;
	int x2;
	int y2;

	// Functions that catch mouse events
	void mousePressEvent( QMouseEvent* ev );
	void mouseReleaseEvent(QMouseEvent* ev);
	void mouseMoveEvent( QMouseEvent* ev ); 

protected:
	// Paint event for crosshair painintg
	void paintEvent( QPaintEvent* ev );
};

// Custom QScrollArea class that can emit signals if the mouse wheel is used
class CustomScrollArea : public QScrollArea
{
	Q_OBJECT
		signals :
	// Emitted signals 
	void wheelTurned( double factor, const QPointF& );

public:

	// Constructor
	CustomScrollArea( QWidget * p ) :QScrollArea( p ) {}

	// Function to catch wheel event
	void wheelEvent( QWheelEvent* event );

};