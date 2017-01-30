/* -*-c++-*- */
/* osgEarth - Dynamic map generation toolkit for OpenSceneGraph
 * Copyright 2016 Pelican Mapping
 * http://osgearth.org
 *
 * osgEarth is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>
 */
#include <osgEarthFeatures/FeatureSourceLayer>

#define LC "[FeatureSourceLayer] " << getName() << ": "

using namespace osgEarth;
using namespace osgEarth::Features;
using namespace osgEarth::Symbology;
using namespace OpenThreads;

namespace osgEarth {
    namespace Features {
        REGISTER_OSGEARTH_LAYER(feature_source, FeatureSourceLayer);
    }
}

FeatureSource*
FeatureSourceLayer::getFeatureSource() const
{ 
    return _featureSource.get();
}

/**
 * Open the feature source set this layer's status to its status.
 */
const Status& 
FeatureSourceLayer::open()
{
    _featureSource = FeatureSourceFactory::create(options());
    if (!_featureSource.valid())
        return setStatus(Status::Error(Status::ServiceUnavailable, "Unable to create feature source"));

    Status fsStatus = _featureSource->open(_readOptions.get());
    if (fsStatus.isError())
    {
        setStatus(fsStatus);
        _featureSource = 0L;
    }
    
    OE_INFO << LC << "Opened feature source OK.\n";
    return getStatus();
}

Config
FeatureSourceLayer::getConfig() const
{
    Config conf = Layer::getConfig();
    conf.key() = "feature_source";
    return conf;
}
