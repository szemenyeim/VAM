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

#include "CustomLabel.h"
#include "Utility.h"
#include <qpainter.h>

void CustomLabel::mousePressEvent( QMouseEvent* ev )
{
	// Emit position of mouse click
    const QPoint p = ev->pos();
	emit mousePressed( p );
}

void CustomLabel::mouseMoveEvent( QMouseEvent* ev )
{
	// Emit position of mouse move
    const QPoint p = ev->pos();
    emit mouseMoved( p );
}

void CustomLabel::paintEvent( QPaintEvent * ev )
{
	// Call parent paint event
	QLabel::paintEvent( ev );

	if( paintCrosshair )
	{
		// Create painter
		QPainter painter( this );

		// set pen to draw
		QPen CrosshairPen;
		CrosshairPen.setColor( QColor::fromRgb( 255, 255, 255 ) );
		CrosshairPen.setWidth( 1 );
		CrosshairPen.setJoinStyle( Qt::MiterJoin );
		painter.setPen( CrosshairPen );

		// Draw two lines
		painter.drawLine( QPointF( 0, y ), QPointF( size().width(), y ) );
		painter.drawLine( QPointF( x, 0 ), QPointF( x, size().height() ) );
	}
}

// Call parent constructors
CustomLabel::CustomLabel( QWidget * parent, Qt::WindowFlags f )
    : QLabel( parent, f ) 
{
	paintCrosshair = false;

	x = y = -1;

	setMouseTracking(true);
}

// Call parent constructors
CustomLabel::CustomLabel( const QString& text, QWidget* parent, Qt::WindowFlags f )
    : QLabel( text, parent, f ) 
{
	paintCrosshair = false;

	x = y = -1;

	setMouseTracking(true);
}

void CustomScrollArea::wheelEvent( QWheelEvent* event )
{
	// Get the number of turns
	double turns = event->angleDelta().ry() / 120.0;

	// Compute the resize factor
	double factor = turns > 0 ? turns * 1.1 : -turns* 0.909091;

	// Emit event
	emit wheelTurned( factor, event->posF() );

}
