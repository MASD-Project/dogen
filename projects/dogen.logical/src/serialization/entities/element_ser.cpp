/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * These files are code-generated via overrides to test dogen. Do not commit them.
 *
 * Generation timestamp: 2022-10-20T10:20:30
 * WARNING: do not edit this file manually.
 * Generated by MASD Dogen v1.0.33
 *
 * Copyright (C) 2012-2015 Marco Craveiro <marco.craveiro@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 *
 */
#include <boost/serialization/nvp.hpp>
#include <boost/serialization/list.hpp>
#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>
#include <boost/serialization/string.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/serialization/optional.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/serialization/shared_ptr.hpp>
#include <boost/serialization/unordered_map.hpp>
#include <boost/archive/polymorphic_iarchive.hpp>
#include <boost/archive/polymorphic_oarchive.hpp>
#include "dogen.logical/serialization/entities/element_ser.hpp"
#include "dogen.logical/serialization/entities/stereotypes_ser.hpp"
#include "dogen.identification/serialization/entities/label_ser.hpp"
#include "dogen.logical/serialization/entities/physical/part_ser.hpp"
#include "dogen.logical/serialization/entities/physical/facet_ser.hpp"
#include "dogen.logical/serialization/entities/physical/helper_ser.hpp"
#include "dogen.logical/serialization/entities/build/cmakelists_ser.hpp"
#include "dogen.logical/serialization/entities/physical/backend_ser.hpp"
#include "dogen.identification/serialization/entities/logical_id_ser.hpp"
#include "dogen.logical/serialization/entities/helper_properties_ser.hpp"
#include "dogen.logical/serialization/entities/structural/module_ser.hpp"
#include "dogen.logical/serialization/entities/structural/object_ser.hpp"
#include "dogen.variability/serialization/entities/configuration_ser.hpp"
#include "dogen.logical/serialization/entities/decoration/licence_ser.hpp"
#include "dogen.logical/serialization/entities/physical/archetype_ser.hpp"
#include "dogen.logical/serialization/entities/structural/builtin_ser.hpp"
#include "dogen.logical/serialization/entities/structural/visitor_ser.hpp"
#include "dogen.identification/serialization/entities/logical_name_ser.hpp"
#include "dogen.logical/serialization/entities/decoration/modeline_ser.hpp"
#include "dogen.logical/serialization/entities/generability_status_ser.hpp"
#include "dogen.logical/serialization/entities/variability/profile_ser.hpp"
#include "dogen.logical/serialization/entities/structural/assistant_ser.hpp"
#include "dogen.logical/serialization/entities/structural/exception_ser.hpp"
#include "dogen.logical/serialization/entities/structural/primitive_ser.hpp"
#include "dogen.logical/serialization/entities/visual_studio/project_ser.hpp"
#include "dogen.identification/serialization/entities/technical_space_ser.hpp"
#include "dogen.logical/serialization/entities/mapping/fixed_mappable_ser.hpp"
#include "dogen.logical/serialization/entities/orm/common_odb_options_ser.hpp"
#include "dogen.logical/serialization/entities/structural/entry_point_ser.hpp"
#include "dogen.logical/serialization/entities/structural/enumeration_ser.hpp"
#include "dogen.logical/serialization/entities/visual_studio/solution_ser.hpp"
#include "dogen.identification/serialization/entities/codec_provenance_ser.hpp"
#include "dogen.logical/serialization/entities/physical/archetype_kind_ser.hpp"
#include "dogen.logical/serialization/entities/variability/initializer_ser.hpp"
#include "dogen.identification/serialization/entities/logical_meta_name_ser.hpp"
#include "dogen.logical/serialization/entities/decoration/modeline_group_ser.hpp"
#include "dogen.logical/serialization/entities/structural/object_template_ser.hpp"
#include "dogen.logical/serialization/entities/variability/feature_bundle_ser.hpp"
#include "dogen.logical/serialization/entities/mapping/extensible_mappable_ser.hpp"
#include "dogen.logical/serialization/entities/decoration/generation_marker_ser.hpp"
#include "dogen.logical/serialization/entities/serialization/type_registrar_ser.hpp"
#include "dogen.logical/serialization/entities/variability/profile_template_ser.hpp"
#include "dogen.logical/serialization/entities/decoration/element_properties_ser.hpp"
#include "dogen.logical/serialization/entities/visual_studio/msbuild_targets_ser.hpp"
#include "dogen.logical/serialization/entities/templating/logic_less_template_ser.hpp"
#include "dogen.logical/serialization/entities/variability/feature_template_bundle_ser.hpp"

BOOST_CLASS_TRACKING(
    dogen::logical::entities::element,
    boost::serialization::track_selectively)

namespace boost {
namespace serialization {

template<typename Archive>
void save(Archive& ar,
    const dogen::logical::entities::element& v,
    const unsigned int /*version*/) {
    ar << make_nvp("name", v.name_);
    ar << make_nvp("documentation", v.documentation_);
    ar << make_nvp("provenance", v.provenance_);
    ar << make_nvp("contained_by", v.contained_by_);
    ar << make_nvp("in_global_module", v.in_global_module_);
    ar << make_nvp("stereotypes", v.stereotypes_);
    ar << make_nvp("meta_name", v.meta_name_);
    ar << make_nvp("intrinsic_technical_space", v.intrinsic_technical_space_);
    ar << make_nvp("configuration", v.configuration_);
    ar << make_nvp("labels", v.labels_);
    ar << make_nvp("generability_status", v.generability_status_);
    ar << make_nvp("decoration", v.decoration_);
    ar << make_nvp("helper_properties", v.helper_properties_);
}

template<typename Archive>
void load(Archive& ar,
    dogen::logical::entities::element& v,
    const unsigned int /*version*/) {
    ar >> make_nvp("name", v.name_);
    ar >> make_nvp("documentation", v.documentation_);
    ar >> make_nvp("provenance", v.provenance_);
    ar >> make_nvp("contained_by", v.contained_by_);
    ar >> make_nvp("in_global_module", v.in_global_module_);
    ar >> make_nvp("stereotypes", v.stereotypes_);
    ar >> make_nvp("meta_name", v.meta_name_);
    ar >> make_nvp("intrinsic_technical_space", v.intrinsic_technical_space_);
    ar >> make_nvp("configuration", v.configuration_);
    ar >> make_nvp("labels", v.labels_);
    ar >> make_nvp("generability_status", v.generability_status_);
    ar >> make_nvp("decoration", v.decoration_);
    ar >> make_nvp("helper_properties", v.helper_properties_);
}

} }

namespace boost {
namespace serialization {

template void save(archive::polymorphic_oarchive& ar, const dogen::logical::entities::element& v, unsigned int version);
template void load(archive::polymorphic_iarchive& ar, dogen::logical::entities::element& v, unsigned int version);

template void save(archive::text_oarchive& ar, const dogen::logical::entities::element& v, unsigned int version);
template void load(archive::text_iarchive& ar, dogen::logical::entities::element& v, unsigned int version);

template void save(archive::binary_oarchive& ar, const dogen::logical::entities::element& v, unsigned int version);
template void load(archive::binary_iarchive& ar, dogen::logical::entities::element& v, unsigned int version);

template void save(archive::xml_oarchive& ar, const dogen::logical::entities::element& v, unsigned int version);
template void load(archive::xml_iarchive& ar, dogen::logical::entities::element& v, unsigned int version);

} }
