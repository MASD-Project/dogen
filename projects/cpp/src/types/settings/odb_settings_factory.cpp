/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda <info@kitanda.co.uk>
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
#include <boost/throw_exception.hpp>
#include "dogen/utility/log/logger.hpp"
#include "dogen/dynamic/types/field_selector.hpp"
#include "dogen/dynamic/types/repository_selector.hpp"
#include "dogen/cpp/types/formatters/odb/traits.hpp"
#include "dogen/cpp/types/settings/odb_settings.hpp"
#include "dogen/cpp/types/settings/odb_settings_factory.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("cpp.settings.odb_settings_factory"));

}

namespace dogen {
namespace cpp {
namespace settings {

odb_settings_factory::odb_settings_factory(const dynamic::repository& rp)
    : field_definitions_(make_field_definitions(rp)) {}

odb_settings_factory::field_definitions odb_settings_factory::
make_field_definitions(const dynamic::repository& rp) const {
    field_definitions r;
    const dynamic::repository_selector s(rp);
    const auto& cc(formatters::odb::traits::odb_pragma());
    r.odb_pragma = s.select_field_by_name(cc);
    return r;
}

std::string odb_settings_factory::settings_key() const {
    return formatters::odb::traits::class_header_formatter_name();
}

boost::shared_ptr<opaque_settings> odb_settings_factory::
make(const dynamic::object& o) const {
    const dynamic::field_selector fs(o);
    const auto& fd(field_definitions_.odb_pragma);
    if (!fs.has_field(fd))
        return boost::shared_ptr<opaque_settings>();

    boost::shared_ptr<odb_settings> r(new odb_settings());
    r->pragmas(fs.get_text_collection_content(fd));
    return r;
}

} } }
