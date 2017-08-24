/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
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
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/serialization/utility.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/serialization/shared_ptr.hpp>
#include <boost/archive/polymorphic_iarchive.hpp>
#include <boost/archive/polymorphic_oarchive.hpp>
#include "dogen/yarn/serialization/meta_model/name_ser.hpp"
#include "dogen/yarn/serialization/meta_model/module_ser.hpp"
#include "dogen/yarn/serialization/meta_model/object_ser.hpp"
#include "dogen/yarn/serialization/meta_model/builtin_ser.hpp"
#include "dogen/yarn/serialization/meta_model/concept_ser.hpp"
#include "dogen/yarn/serialization/meta_model/exomodel_ser.hpp"
#include "dogen/yarn/serialization/meta_model/exception_ser.hpp"
#include "dogen/yarn/serialization/meta_model/primitive_ser.hpp"
#include "dogen/annotations/serialization/scribble_group_ser.hpp"
#include "dogen/yarn/serialization/meta_model/enumeration_ser.hpp"

namespace boost {
namespace serialization {

template<typename Archive>
void save(Archive& ar,
    const dogen::yarn::meta_model::exomodel& v,
    const unsigned int /*version*/) {
    ar << make_nvp("name", v.name_);
    ar << make_nvp("meta_name", v.meta_name_);
    ar << make_nvp("modules", v.modules_);
    ar << make_nvp("concepts", v.concepts_);
    ar << make_nvp("builtins", v.builtins_);
    ar << make_nvp("enumerations", v.enumerations_);
    ar << make_nvp("primitives", v.primitives_);
    ar << make_nvp("objects", v.objects_);
    ar << make_nvp("exceptions", v.exceptions_);
    ar << make_nvp("root_module", v.root_module_);
}

template<typename Archive>
void load(Archive& ar,
    dogen::yarn::meta_model::exomodel& v,
    const unsigned int /*version*/) {
    ar >> make_nvp("name", v.name_);
    ar >> make_nvp("meta_name", v.meta_name_);
    ar >> make_nvp("modules", v.modules_);
    ar >> make_nvp("concepts", v.concepts_);
    ar >> make_nvp("builtins", v.builtins_);
    ar >> make_nvp("enumerations", v.enumerations_);
    ar >> make_nvp("primitives", v.primitives_);
    ar >> make_nvp("objects", v.objects_);
    ar >> make_nvp("exceptions", v.exceptions_);
    ar >> make_nvp("root_module", v.root_module_);
}

} }

namespace boost {
namespace serialization {

template void save(archive::polymorphic_oarchive& ar, const dogen::yarn::meta_model::exomodel& v, unsigned int version);
template void load(archive::polymorphic_iarchive& ar, dogen::yarn::meta_model::exomodel& v, unsigned int version);

template void save(archive::text_oarchive& ar, const dogen::yarn::meta_model::exomodel& v, unsigned int version);
template void load(archive::text_iarchive& ar, dogen::yarn::meta_model::exomodel& v, unsigned int version);

template void save(archive::binary_oarchive& ar, const dogen::yarn::meta_model::exomodel& v, unsigned int version);
template void load(archive::binary_iarchive& ar, dogen::yarn::meta_model::exomodel& v, unsigned int version);

template void save(archive::xml_oarchive& ar, const dogen::yarn::meta_model::exomodel& v, unsigned int version);
template void load(archive::xml_iarchive& ar, dogen::yarn::meta_model::exomodel& v, unsigned int version);

} }
