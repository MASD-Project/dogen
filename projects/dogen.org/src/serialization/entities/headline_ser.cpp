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
#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/polymorphic_iarchive.hpp>
#include <boost/archive/polymorphic_oarchive.hpp>
#include "dogen.org/serialization/entities/tag_ser.hpp"
#include "dogen.org/serialization/entities/drawer_ser.hpp"
#include "dogen.org/serialization/entities/section_ser.hpp"
#include "dogen.org/serialization/entities/headline_ser.hpp"
#include "dogen.org/serialization/entities/todo_keyword_ser.hpp"
#include "dogen.org/serialization/entities/priority_cookie_ser.hpp"
#include "dogen.org/serialization/entities/affiliated_keyword_ser.hpp"

namespace boost {
namespace serialization {

template<typename Archive>
void save(Archive& ar,
    const dogen::org::entities::headline& v,
    const unsigned int /*version*/) {
    ar << make_nvp("line_number", v.line_number_);
    ar << make_nvp("affiliated_keywords", v.affiliated_keywords_);
    ar << make_nvp("drawers", v.drawers_);
    ar << make_nvp("section", v.section_);
    ar << make_nvp("headlines", v.headlines_);
    ar << make_nvp("level", v.level_);
    ar << make_nvp("priority", v.priority_);
    ar << make_nvp("title", v.title_);
    ar << make_nvp("tags", v.tags_);
    ar << make_nvp("todo_keyword", v.todo_keyword_);
}

template<typename Archive>
void load(Archive& ar,
    dogen::org::entities::headline& v,
    const unsigned int /*version*/) {
    ar >> make_nvp("line_number", v.line_number_);
    ar >> make_nvp("affiliated_keywords", v.affiliated_keywords_);
    ar >> make_nvp("drawers", v.drawers_);
    ar >> make_nvp("section", v.section_);
    ar >> make_nvp("headlines", v.headlines_);
    ar >> make_nvp("level", v.level_);
    ar >> make_nvp("priority", v.priority_);
    ar >> make_nvp("title", v.title_);
    ar >> make_nvp("tags", v.tags_);
    ar >> make_nvp("todo_keyword", v.todo_keyword_);
}

} }

namespace boost {
namespace serialization {

template void save(archive::polymorphic_oarchive& ar, const dogen::org::entities::headline& v, unsigned int version);
template void load(archive::polymorphic_iarchive& ar, dogen::org::entities::headline& v, unsigned int version);

template void save(archive::text_oarchive& ar, const dogen::org::entities::headline& v, unsigned int version);
template void load(archive::text_iarchive& ar, dogen::org::entities::headline& v, unsigned int version);

template void save(archive::binary_oarchive& ar, const dogen::org::entities::headline& v, unsigned int version);
template void load(archive::binary_iarchive& ar, dogen::org::entities::headline& v, unsigned int version);

template void save(archive::xml_oarchive& ar, const dogen::org::entities::headline& v, unsigned int version);
template void load(archive::xml_iarchive& ar, dogen::org::entities::headline& v, unsigned int version);

} }