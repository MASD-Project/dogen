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
#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>
#include <boost/serialization/string.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/serialization/shared_ptr.hpp>
#include <boost/archive/polymorphic_iarchive.hpp>
#include <boost/archive/polymorphic_oarchive.hpp>
#include "dogen.physical/serialization/entities/artefact_ser.hpp"
#include "dogen.physical/serialization/entities/operation_ser.hpp"
#include "dogen.physical/serialization/entities/path_properties_ser.hpp"
#include "dogen.variability/serialization/entities/configuration_ser.hpp"
#include "dogen.identification/serialization/entities/physical_name_ser.hpp"
#include "dogen.physical/serialization/entities/relation_properties_ser.hpp"
#include "dogen.identification/serialization/entities/technical_space_ser.hpp"
#include "dogen.physical/serialization/entities/enablement_properties_ser.hpp"
#include "dogen.identification/serialization/entities/logical_provenance_ser.hpp"
#include "dogen.identification/serialization/entities/physical_meta_name_ser.hpp"
#include "dogen.identification/serialization/entities/logical_meta_physical_id_ser.hpp"

namespace boost {
namespace serialization {

template<class Archive>
void serialize(Archive& ar, boost::filesystem::path& p, const unsigned int/*v*/)
{
    std::string s;
    if(Archive::is_saving::value)
        s = p.generic_string();
    ar & boost::serialization::make_nvp("path", s);
    if(Archive::is_loading::value)
        p = s;
}

} }

namespace boost {
namespace serialization {

template<typename Archive>
void save(Archive& ar,
    const dogen::physical::entities::artefact& v,
    const unsigned int /*version*/) {
    ar << make_nvp("meta_name", v.meta_name_);
    ar << make_nvp("configuration", v.configuration_);
    ar << make_nvp("provenance", v.provenance_);
    ar << make_nvp("name", v.name_);
    ar << make_nvp("id", v.id_);
    ar << make_nvp("technical_space", v.technical_space_);
    ar << make_nvp("file_path", v.file_path_);
    ar << make_nvp("content", v.content_);
    ar << make_nvp("path_properties", v.path_properties_);
    ar << make_nvp("dependencies", v.dependencies_);
    ar << make_nvp("unified_diff", v.unified_diff_);
    ar << make_nvp("operation", v.operation_);
    ar << make_nvp("enablement_properties", v.enablement_properties_);
    ar << make_nvp("formatting_input", v.formatting_input_);
    ar << make_nvp("relations", v.relations_);
}

template<typename Archive>
void load(Archive& ar,
    dogen::physical::entities::artefact& v,
    const unsigned int /*version*/) {
    ar >> make_nvp("meta_name", v.meta_name_);
    ar >> make_nvp("configuration", v.configuration_);
    ar >> make_nvp("provenance", v.provenance_);
    ar >> make_nvp("name", v.name_);
    ar >> make_nvp("id", v.id_);
    ar >> make_nvp("technical_space", v.technical_space_);
    ar >> make_nvp("file_path", v.file_path_);
    ar >> make_nvp("content", v.content_);
    ar >> make_nvp("path_properties", v.path_properties_);
    ar >> make_nvp("dependencies", v.dependencies_);
    ar >> make_nvp("unified_diff", v.unified_diff_);
    ar >> make_nvp("operation", v.operation_);
    ar >> make_nvp("enablement_properties", v.enablement_properties_);
    ar >> make_nvp("formatting_input", v.formatting_input_);
    ar >> make_nvp("relations", v.relations_);
}

} }

namespace boost {
namespace serialization {

template void save(archive::polymorphic_oarchive& ar, const dogen::physical::entities::artefact& v, unsigned int version);
template void load(archive::polymorphic_iarchive& ar, dogen::physical::entities::artefact& v, unsigned int version);

template void save(archive::text_oarchive& ar, const dogen::physical::entities::artefact& v, unsigned int version);
template void load(archive::text_iarchive& ar, dogen::physical::entities::artefact& v, unsigned int version);

template void save(archive::binary_oarchive& ar, const dogen::physical::entities::artefact& v, unsigned int version);
template void load(archive::binary_iarchive& ar, dogen::physical::entities::artefact& v, unsigned int version);

template void save(archive::xml_oarchive& ar, const dogen::physical::entities::artefact& v, unsigned int version);
template void load(archive::xml_iarchive& ar, dogen::physical::entities::artefact& v, unsigned int version);

} }
