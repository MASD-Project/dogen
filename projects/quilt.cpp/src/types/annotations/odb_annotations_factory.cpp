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
#include <boost/make_shared.hpp>
#include <boost/throw_exception.hpp>
#include "dogen/utility/log/logger.hpp"
#include "dogen/dynamic/types/field_selector.hpp"
#include "dogen/dynamic/types/repository_selector.hpp"
#include "dogen/quilt.cpp/types/formatters/odb/traits.hpp"
#include "dogen/quilt.cpp/types/annotations/building_error.hpp"
#include "dogen/quilt.cpp/types/annotations/odb_annotations.hpp"
#include "dogen/quilt.cpp/types/annotations/odb_annotations_factory.hpp"

namespace {

using namespace dogen::utility::log;
static logger
lg(logger_factory("quilt.cpp.annotations.odb_annotations_factory"));

const std::string factory_not_initialised("Factory has not been initialised.");

}

namespace dogen {
namespace quilt {
namespace cpp {
namespace annotations {

odb_annotations_factory::odb_annotations_factory() : initialised_(false) {}

odb_annotations_factory::~odb_annotations_factory() noexcept { }

std::string odb_annotations_factory::annotations_key() const {
    return formatters::odb::traits::class_header_formatter_name();
}

void odb_annotations_factory::setup(const dynamic::repository& drp) {
    const dynamic::repository_selector s(drp);
    const auto& cc(formatters::odb::traits::odb_pragma());
    field_definitions_.odb_pragma = s.select_field_by_name(cc);
    initialised_ = true;
}

boost::shared_ptr<opaque_annotations> odb_annotations_factory::
make(const dynamic::object& o) const {

    if (!initialised_) {
        BOOST_LOG_SEV(lg, error) << factory_not_initialised;
        BOOST_THROW_EXCEPTION(building_error(factory_not_initialised));
    }

    const dynamic::field_selector fs(o);
    if (!fs.has_field(field_definitions_.odb_pragma))
        return boost::shared_ptr<opaque_annotations>();

    boost::shared_ptr<odb_annotations> r(new odb_annotations());
    r->pragmas(fs.get_text_collection_content(field_definitions_.odb_pragma));
    return r;
}

} } } }
