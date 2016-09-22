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
#include <typeinfo>
#include <typeindex>
#include <boost/throw_exception.hpp>
#include "dogen/utility/log/logger.hpp"
#include "dogen/utility/io/forward_list_io.hpp"
#include "dogen/dynamic/io/ownership_hierarchy_io.hpp"
#include "dogen/quilt.cpp/io/formatters/container_io.hpp"
#include "dogen/quilt.cpp/types/formatters/registrar_error.hpp"
#include "dogen/quilt.cpp/types/formatters/registrar.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("quilt.cpp.formatters.registrar"));

const std::string no_file_formatters("File formatters container is empty.");
const std::string no_file_formatters_by_type_index(
    "No file formatters by type index provided.");
const std::string no_forward_declarations_formatters(
    "No forward declarations formatters provided.");
const std::string null_formatter("Formatter supplied is null.");
const std::string duplicate_formatter_id("Duplicate formatter id: ");
const std::string empty_family("Family cannot be empty.");
const std::string null_formatter_helper("Formatter helper supplied is null");
const std::string unsupported_element_type(
    "Element type is not supported by formatters.");

}

namespace dogen {
namespace quilt {
namespace cpp {
namespace formatters {

void registrar::validate() const {
    /*
     * We must have at least one registered formatter. This is a quick
     * way of troubleshooting validation errors.
     */
    const auto& fc(formatter_container_);
    if (fc.file_formatters_by_type_index().empty()) {
        BOOST_LOG_SEV(lg, error) << no_file_formatters_by_type_index;
        BOOST_THROW_EXCEPTION(
            registrar_error(no_file_formatters_by_type_index));
    }

    if (fc.file_formatters().empty()) {
        BOOST_LOG_SEV(lg, error) << no_file_formatters;
        BOOST_THROW_EXCEPTION(
            registrar_error(no_file_formatters));
    }

    /*
     * Formatter id must be unique.
     */
    std::unordered_set<std::string> formatter_ids;
    for (const auto& f : fc.file_formatters()) {
        const auto id(f->id());
        const auto i(formatter_ids.insert(id));
        if (!i.second) {
            BOOST_LOG_SEV(lg, error) << duplicate_formatter_id << id;
            BOOST_THROW_EXCEPTION(registrar_error(duplicate_formatter_id + id));
        }
    }

    BOOST_LOG_SEV(lg, debug) << "Registrar is in a valid state. Container: "
                             << fc;
    BOOST_LOG_SEV(lg, debug) << "Ownership hierarchy: " << ownership_hierarchy_;
}

void registrar::register_formatter_helper(
    std::shared_ptr<helper_formatter_interface> fh) {

    // note: not logging by design
    if (!fh)
        BOOST_THROW_EXCEPTION(registrar_error(null_formatter_helper));

    if(fh->family().empty())
        BOOST_THROW_EXCEPTION(registrar_error(empty_family));

    auto& f(formatter_container_.helper_formatters_[fh->family()]);
    for (const auto& of : fh->owning_formatters())
        f[of].push_back(fh);
}

void registrar::
register_formatter(std::shared_ptr<file_formatter_interface> f) {
    // note: not logging by design
    if (!f)
        BOOST_THROW_EXCEPTION(registrar_error(null_formatter));

    ownership_hierarchy_.push_front(f->ownership_hierarchy());
    formatter_container_.file_formatters_.push_front(f);

    auto& ffti(formatter_container_.file_formatters_by_type_index());
    auto& ti(ffti[f->element_type_index()]);
    ti.push_front(f);
}

const container& registrar::formatter_container() const {
    return formatter_container_;
}

const std::forward_list<dynamic::ownership_hierarchy>&
registrar::ownership_hierarchy() const {
    return ownership_hierarchy_;
}

const std::unordered_map<
    std::string, std::unordered_map<
                     std::string,
                     std::list<
                         std::shared_ptr<helper_formatter_interface>>>>&
registrar::formatter_helpers() const {
    return formatter_container_.helper_formatters();
}

} } } }
