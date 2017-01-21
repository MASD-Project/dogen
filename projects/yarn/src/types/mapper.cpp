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
#include <boost/lexical_cast.hpp>
#include "dogen/utility/log/logger.hpp"
#include "dogen/utility/io/list_io.hpp"
#include "dogen/yarn/io/languages_io.hpp"
#include "dogen/yarn/types/attribute.hpp"
#include "dogen/yarn/types/mapping_error.hpp"
#include "dogen/yarn/types/mapper.hpp"

namespace {

using namespace dogen::utility::log;
auto lg(logger_factory("yarn.mapper"));

const std::string unsupported_lanugage("Language is not supported: ");

}

namespace dogen {
namespace yarn {

mapper::mapper(const mapping_repository& mrp) : mapping_repository_(mrp) { }

const std::unordered_map<std::string, name>& mapper::
map_for_language(const languages from, const languages to) const {
    if (from == languages::upsilon) {
        const auto i(mapping_repository_.by_upsilon_id().find(to));
        if (i != mapping_repository_.by_upsilon_id().end())
            return i->second;

        const auto s(boost::lexical_cast<std::string>(to));
        BOOST_LOG_SEV(lg, error) << unsupported_lanugage << s;
        BOOST_THROW_EXCEPTION(mapping_error(unsupported_lanugage + s));
    } else if (from == languages::language_agnostic) {
        const auto i(mapping_repository_.by_language_agnostic_id().find(to));
        if (i != mapping_repository_.by_upsilon_id().end())
            return i->second;

        const auto s(boost::lexical_cast<std::string>(to));
        BOOST_LOG_SEV(lg, error) << unsupported_lanugage << s;
        BOOST_THROW_EXCEPTION(mapping_error(unsupported_lanugage + s));
    }

    const auto s(boost::lexical_cast<std::string>(from));
    BOOST_LOG_SEV(lg, error) << unsupported_lanugage << s;
    BOOST_THROW_EXCEPTION(mapping_error(unsupported_lanugage + s));
}

name_tree mapper::walk_name_tree(const std::unordered_map<std::string,
    name>& map, const name_tree& nt) const {
    name_tree r;
    const auto id(nt.current().id());
    const auto i(map.find(id));
    if (i != map.end()) {
        r.current(i->second);
        BOOST_LOG_SEV(lg, debug) << "Mapping from: " << id
                                 << " to: " << i->second.id();
    } else
        r.current(nt.current());

    for (const auto& c : nt.children())
        r.children().push_back(walk_name_tree(map, c));

    return r;
}

void mapper::map_attributes(const std::unordered_map<std::string,
    name>& map, std::list<attribute>& attrs) const {
    for (auto& attr : attrs)
        attr.parsed_type(walk_name_tree(map, attr.parsed_type()));
}

intermediate_model mapper::map(const languages from, const languages to,
    const intermediate_model& im) const {
    BOOST_LOG_SEV(lg, debug) << "Started mapping. Model: " << im.name().id();
    BOOST_LOG_SEV(lg, debug) << "Mapping from: " << from << " to: " << to;
    if (from == to) {
        BOOST_LOG_SEV(lg, debug) << "No mapping required";
        return im;
    }

    auto r(im);
    const auto& map(map_for_language(from, to));
    for (auto& pair : r.objects())
        map_attributes(map, pair.second.local_attributes());

    for (auto& pair : r.concepts())
        map_attributes(map, pair.second.local_attributes());

    r.input_language(to);
    r.output_languages().clear();
    r.output_languages().push_back(to);

    BOOST_LOG_SEV(lg, debug) << "Output language: " << r.output_languages();
    BOOST_LOG_SEV(lg, debug) << "Finished mapping.";

    return r;
}

} }
