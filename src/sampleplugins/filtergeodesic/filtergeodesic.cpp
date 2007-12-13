/****************************************************************************
* MeshLab                                                           o o     *
* An extendible mesh processor                                    o     o   *
*                                                                _   O  _   *
* Copyright(C) 2005, 2006                                          \/)\/    *
* Visual Computing Lab                                            /\/|      *
* ISTI - Italian National Research Council                           |      *
*                                                                    \      *
* All rights reserved.                                                      *
*                                                                           *
* This program is free software; you can redistribute it and/or modify      *
* it under the terms of the GNU General Public License as published by      *
* the Free Software Foundation; either version 2 of the License, or         *
* (at your option) any later version.                                       *
*                                                                           *
* This program is distributed in the hope that it will be useful,           *
* but WITHOUT ANY WARRANTY; without even the implied warranty of            *
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the             *
* GNU General Public License (http://www.gnu.org/licenses/gpl.txt)          *
* for more details.                                                         *
*                                                                           *
****************************************************************************/
/****************************************************************************
  History

 filtergeodesic.cpp,v
 Revision 1.1  2007/12/13 00:33:55  cignoni
 New small samples

 Revision 1.1  2007/12/02 07:57:48  cignoni
 Added the new sample filter plugin that removes border faces

 
*****************************************************************************/
#include <Qt>
#include <QtGui>
#include "filtergeodesic.h"

#include <vcg/complex/trimesh/update/quality.h>
#include <vcg/complex/trimesh/update/color.h>
#include <vcg/complex/trimesh/clean.h>

using namespace vcg;

FilterGeodesic::FilterGeodesic() 
{
  typeList << FP_QUALITY_GEODESIC;
 
  FilterIDType tt;
  foreach(tt , types())
	    actionList << new QAction(filterName(tt), this);

}

FilterGeodesic::~FilterGeodesic() {
	for (int i = 0; i < actionList.count() ; i++ ) 
		delete actionList.at(i);
}

const QString FilterGeodesic::filterName(FilterIDType filter) 
{
 switch(filter)
  {
	  case FP_QUALITY_GEODESIC :								return QString("Colorize by border distance");
  	default: assert(0);
  }
  return QString("error!");
}

const QString FilterGeodesic::filterInfo(FilterIDType filterId)
{
  switch(filterId)
  {
		case FP_QUALITY_GEODESIC:	     return tr("Store in the quality field the geodesic distance from borders and color the mesh accordingly."); 
  	default: assert(0);
  }
  return QString("error!");
}

const FilterGeodesic::FilterClass FilterGeodesic::getClass(QAction *a)
{
  switch(ID(a))
  {
    case FP_QUALITY_GEODESIC :
      return MeshFilterInterface::VertexColoring;     
    default : return MeshFilterInterface::Generic;
  }
}


const PluginInfo &FilterGeodesic::pluginInfo()
{
   static PluginInfo ai;
   ai.Date=tr( __DATE__ );
	 ai.Version = tr("0.1");
	 ai.Author = ("Paolo Cignoni");
   return ai;
}

const int FilterGeodesic::getRequirements(QAction *action)
{
  switch(ID(action))
  {
    case FP_QUALITY_GEODESIC :	return MeshModel::MM_VERTFACETOPO | MeshModel::MM_BORDERFLAG;
    default: assert(0);
  }
  return 0;
}

bool FilterGeodesic::applyFilter(QAction *filter, MeshModel &m, FilterParameterSet & par, vcg::CallBackPos * cb) 
{
				CMeshO::FaceIterator fi;
				CMeshO::VertexIterator vi;
	if(filter->text() == filterName(FP_QUALITY_GEODESIC) )
	  {
		tri::UpdateQuality<CMeshO>::VertexGeodesicFromBorder(m.cm);
		tri::UpdateColor<CMeshO>::VertexQuality(m.cm);
	  }
	return true;
}


Q_EXPORT_PLUGIN(FilterGeodesic)
