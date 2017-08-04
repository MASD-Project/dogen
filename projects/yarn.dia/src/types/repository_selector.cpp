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
#include "dogen/utility/log/logger.hpp"
#include "dogen/yarn.dia/types/selection_error.hpp"
#include "dogen/yarn.dia/types/repository_selector.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("yarn.dia.repository_selector"));

const std::string empty_package_id("Supplied package id is empty");
const std::string missing_module_for_name("Missing module for name: ");
const std::string missing_name_for_id("Missing name for dia object ID: ");
const std::string empty_parent_container(
    "Object has an entry in child to parent container but its empty: ");
const std::string parent_not_found("Object has a parent but its not defined: ");

}

namespace dogen {
namespace yarn {
namespace dia {

const_repository_selector::const_repository_selector(const repository& rp)
    : repository_(rp) {}

void const_repository_selector::validate_id(const std::string& id) const {
    if (id.empty()) {
        BOOST_LOG_SEV(lg, error) << empty_package_id;
        BOOST_THROW_EXCEPTION(selection_error(empty_package_id));
    }
}

const meta_model::module& const_repository_selector::
module_for_name(const meta_model::name& n) const {
    const auto i(repository_.model().modules().find(n.id()));
    if (i == repository_.model().modules().end()) {
        const auto sn(n.simple());
        BOOST_LOG_SEV(lg, error) << missing_module_for_name << sn;
        BOOST_THROW_EXCEPTION(selection_error(missing_module_for_name + sn));
    }
    return *i->second;
}

const meta_model::module& const_repository_selector::
module_for_id(const std::string& id) const {
    const auto n(name_for_id(id));
    return module_for_name(n);
}

std::list<meta_model::name> const_repository_selector::
parent_names_for_id(const std::string& id) const {
    validate_id(id);

    std::list<meta_model::name> r;
    const auto i(repository_.child_id_to_parent_ids().find(id));
    if (i == repository_.child_id_to_parent_ids().end())
        return r;

    const auto& pids(i->second);
    if (pids.empty()) {
        BOOST_LOG_SEV(lg, error) << empty_parent_container << id;
        BOOST_THROW_EXCEPTION(selection_error(empty_parent_container + id));
    }

    for (const auto& pid : pids) {
        const auto j(repository_.id_to_name().find(pid));
        if (j == repository_.id_to_name().end()) {
            BOOST_LOG_SEV(lg, error) << "Object has a parent but "
                                     << " there is no name mapping."
                                     << " Child ID: '" << id
                                     << "' Parent ID: '" << pid << "'";

            BOOST_THROW_EXCEPTION(selection_error(parent_not_found + pid));
        }
        const auto& parent_name(j->second);
        r.push_back(parent_name);
    }
    return r;
}

meta_model::name
const_repository_selector::name_for_id(const std::string& id) const {
    validate_id(id);
    const auto i(repository_.id_to_name().find(id));
    if (i == repository_.id_to_name().end()) {
        BOOST_LOG_SEV(lg, error) << missing_name_for_id << id;
        BOOST_THROW_EXCEPTION(selection_error(missing_name_for_id + id));
    }
    return i->second;
}

repository_selector::repository_selector(repository& rp)
    : repository_(rp) {}

meta_model::module&
repository_selector::module_for_name(const meta_model::name& n) {
    const auto i(repository_.model().modules().find(n.id()));
    if (i == repository_.model().modules().end()) {
        const auto sn(n.simple());
        BOOST_LOG_SEV(lg, error) << missing_module_for_name << sn;
        BOOST_THROW_EXCEPTION(selection_error(missing_module_for_name + sn));
    }
    return *i->second;
}

meta_model::module& repository_selector::module_for_id(const std::string& id) {
    const_repository_selector crs(repository_);
    const auto n(crs.name_for_id(id));
    return module_for_name(n);
}

} } }
