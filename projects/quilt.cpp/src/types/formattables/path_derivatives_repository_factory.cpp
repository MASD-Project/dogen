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
#include <boost/throw_exception.hpp>
#include <boost/algorithm/string.hpp>
#include "dogen/utility/log/logger.hpp"
#include "dogen/yarn/types/object.hpp"
#include "dogen/yarn/types/primitive.hpp"
#include "dogen/yarn/types/enumeration.hpp"
#include "dogen/yarn/types/concept.hpp"
#include "dogen/yarn/types/module.hpp"
#include "dogen/yarn/io/name_io.hpp"
#include "dogen/quilt.cpp/types/formattables/building_error.hpp"
#include "dogen/quilt.cpp/io/formattables/path_derivatives_io.hpp"
#include "dogen/quilt.cpp/io/formattables/path_derivatives_repository_io.hpp"
#include "dogen/quilt.cpp/types/formattables/path_derivatives_repository_factory.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory(
        "quilt.cpp.formattables.path_derivatives_repository_factory"));

const std::string empty;
const std::string underscore("_");
const std::string double_quote("\"");
const std::string dot(".");
const std::string separator("_");

const std::string duplicate_name("Duplicate name: ");
const std::string formatter_not_found_for_type(
    "Formatter not found for type: ");

}

namespace dogen {
namespace quilt {
namespace cpp {
namespace formattables {

std::string  path_derivatives_repository_factory::
to_header_guard_name(const boost::filesystem::path& p) const {
    bool is_first(true);
    std::ostringstream ss;
    for (const auto& token : p) {
        std::string s(token.string());
        boost::replace_all(s, dot, separator);
        boost::to_upper(s);
        ss << (is_first ? empty : separator) << s;
        is_first = false;
    }
    return ss.str();
}

void path_derivatives_repository_factory::populate_repository(
    const formatter_list_type& formatters, const locator& locator,
    const yarn::name& n, path_derivatives_repository& pdrp) const {

    BOOST_LOG_SEV(lg, debug) << "Processing name: " << n;
    auto& map(pdrp.by_name()[n]);
    for (const auto& fmt : formatters) {
        const auto fmtn(fmt->ownership_hierarchy().formatter_name());
        BOOST_LOG_SEV(lg, debug) << "Formatter: " << fmtn;

        path_derivatives pd;
        pd.file_path(fmt->full_path(locator, n));
        const auto ns(formatters::inclusion_support_types::not_supported);
        if (fmt->inclusion_support_type() != ns) {
            const auto ip(fmt->inclusion_path(locator, n));
            pd.header_guard(to_header_guard_name(ip));
        }

        BOOST_LOG_SEV(lg, debug) << "Path derivatives: " << pd;
        const auto pair(std::make_pair(fmtn, pd));
        const auto result(map.insert(pair));
        const bool inserted(result.second);
        if (!inserted) {
            BOOST_LOG_SEV(lg, error) << duplicate_name << n.id()
                                     << " formatter: " << fmtn;
            BOOST_THROW_EXCEPTION(building_error(duplicate_name + n.id()));
        }
    }
}

path_derivatives_repository path_derivatives_repository_factory::
make(const formatters::container& fc, const locator& l,
    const yarn::model& m) const {

    BOOST_LOG_SEV(lg, debug) << "Generating path derivatives repository.";

    path_derivatives_repository r;
    const auto ffti(fc.file_formatters_by_type_index());
    for (const auto& ptr : m.elements()) {
        const auto& e(*ptr);
        const auto id(e.name().id());

        const auto ti(std::type_index(typeid(e)));
        const auto i(ffti.find(ti));
        if (i == ffti.end()) {
            BOOST_LOG_SEV(lg, debug) << formatter_not_found_for_type << id;
            continue;
        }
        populate_repository(i->second, l, e.name(), r);
    }
    BOOST_LOG_SEV(lg, debug) << "Finished generating path derivatives"
                             << " repository. Result: " << r;
    return r;
}

} } } }
