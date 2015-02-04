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
#include "dogen/utility/log/logger.hpp"
#include "dogen/utility/io/forward_list_io.hpp"
#include "dogen/utility/io/unordered_map_io.hpp"
#include "dogen/dynamic/io/field_definition_io.hpp"
#include "dogen/dynamic/types/indexer.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("dynamic.indexer"));

}

namespace dogen {
namespace dynamic {

const std::unordered_map<std::string, std::forward_list<field_definition> >&
indexer::field_definitions_by_facet_name() const {
    return field_definitions_by_facet_name_;
}

const std::unordered_map<std::string, std::forward_list<field_definition> >&
indexer::field_definitions_by_formatter_name() const {
    return field_definitions_by_formatter_name_;
}

void indexer::index(const std::forward_list<field_definition>& fds) {
    BOOST_LOG_SEV(lg, debug) << "Indexing field definitions.";
    for (const auto& fd : fds) {
        const auto oh(fd.ownership_hierarchy());

        const auto fmt(oh.formatter_name());
        if (!fmt.empty()) {
            field_definitions_by_formatter_name_[fmt].push_front(fd);
            // fields that have a formatter cannot be in the facet
            // container too.
            continue;
        } else {
            BOOST_LOG_SEV(lg, debug) << "Field has no formatter: "
                                     << fd.name().qualified();
        }

        const auto fct(oh.facet_name());
        if (!fct.empty())
            field_definitions_by_facet_name_[fct].push_front(fd);
        else {
            BOOST_LOG_SEV(lg, debug) << "Field has no facet: "
                                     << fd.name().qualified();
        }
    }
    BOOST_LOG_SEV(lg, debug) << "Indexed field definitions.";
    BOOST_LOG_SEV(lg, debug) << "Field definitions by facet name: "
                             << field_definitions_by_facet_name_;
    BOOST_LOG_SEV(lg, debug) << "Field definitions by formatter name: "
                             << field_definitions_by_formatter_name_;
}

} }
