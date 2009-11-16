/*
  Copyright_License {

  XCSoar Glide Computer - http://www.xcsoar.org/
  Copyright (C) 2000 - 2009

  M Roberts (original release)
  Robin Birch <robinb@ruffnready.co.uk>
  Samuel Gisiger <samuel.gisiger@triadis.ch>
  Jeff Goodenough <jeff@enborne.f2s.com>
  Alastair Harrison <aharrison@magic.force9.co.uk>
  Scott Penrose <scottp@dd.com.au>
  John Wharington <jwharington@gmail.com>
  Lars H <lars_hn@hotmail.com>
  Rob Dunning <rob@raspberryridgesheepfarm.com>
  Russell King <rmk@arm.linux.org.uk>
  Paolo Ventafridda <coolwind@email.it>
  Tobias Lohner <tobias@lohner-net.de>
  Mirek Jezek <mjezek@ipplc.cz>
  Max Kellermann <max@duempel.org>

  This program is free software; you can redistribute it and/or
  modify it under the terms of the GNU General Public License
  as published by the Free Software Foundation; either version 2
  of the License, or (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program; if not, write to the Free Software
  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
  }
*/


#ifndef FAISECTORSTARTPOINT_HPP
#define FAISECTORSTARTPOINT_HPP

#include "Task/Tasks/BaseTask/StartPoint.hpp"
#include "ObservationZones/FAISectorZone.hpp"

class FAISectorStartPoint: 
  public StartPoint
{
public:
/** 
 * Constructor.  Must be followed with update_geometry()
 * after remainder of task is defined and links established.
 * 
 * @param tp Projection of entire task
 * @param wp Waypoint at which to locate task point origin
 * @param tb Task Behaviour defining options (esp safety heights)
 * 
 * @return Partially initialised object.
 */  
  FAISectorStartPoint(const TaskProjection&tp,
                      const Waypoint& wp,
                      const TaskBehaviour &tb):
    StartPoint(tp,wp,tb),
    oz(wp.Location) 
  {
  };

/** 
 * Updates sector geometry based on previous/next legs
 * 
 */  
  virtual void update_geometry() {
    oz.set_legs(NULL, this, get_next());
  }

/** 
 * Test whether aircraft is inside observation zone.
 * 
 * @param ref Aircraft state to test
 * 
 * @return True if aircraft is inside observation zone
 */
  virtual bool isInSector(const AIRCRAFT_STATE &ref) const
  {
    return oz.isInSector(ref);
  }

/** 
 * Calculate boundary point from parametric border
 * 
 * @param t t value (0,1) of parameter
 * 
 * @return Boundary point
 */
  GEOPOINT get_boundary_parametric(double t) ;

/** 
 * Calculate distance reduction for achieved task point,
 * to calcuate scored distance.
 * 
 * @return Distance reduction once achieved
 */
  virtual double score_adjustment();

protected:
  FAISectorZone oz;
};


#endif
