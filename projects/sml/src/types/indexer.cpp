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
#include "dogen/sml/types/indexer_error.hpp"
#include "dogen/sml/types/indexer.hpp"

using namespace dogen::utility::log;

namespace {

auto lg(logger_factory("om_formatters.modeline_formatter"));
const std::string not_indexed("Attempt to query without indexing");

}

namespace dogen {
namespace sml {

indexer::indexer(const model& m) : model_(m), is_indexed_(false) {
}

void indexer::index() {
    is_indexed_ = true;
}

bool indexer::is_indexed() const {
    return is_indexed_;
}

void indexer::ensure_indexed() const {
    if (!is_indexed()) {
        BOOST_LOG_SEV(lg, error) << not_indexed;
        BOOST_THROW_EXCEPTION(indexer_error(not_indexed));
    }
}

std::list<property>
indexer::all_properties(const abstract_object& o) const {
    ensure_indexed();
    const auto i(all_properties_.find(o.name()));
    if (i != all_properties_.end())
        return i->second;
    return std::list<property>{};
}

std::list<property>
indexer::local_properties(const abstract_object& o) const {
    ensure_indexed();
    const auto i(local_properties_.find(o.name()));
    if (i != local_properties_.end())
        return i->second;
    return std::list<property>{};
}

std::unordered_map<qname, std::list<property> >
indexer::inehrited_properties(const abstract_object& o) const {
    ensure_indexed();
    std::unordered_map<qname, std::list<property> > r;

    if (o.parent_name()) {
        const auto i(inherited_properties_.find(*o.parent_name()));
        if (i != inherited_properties_.end())
            r.insert(std::make_pair(*o.parent_name(), i->second));
    }
    return r;
}

} }
