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

const std::string no_all_formatters("All formatters container is empty.");
const std::string no_object_formatters("No object formatters provided.");
const std::string no_forward_declarations_formatters(
    "No forward declarations formatters provided.");
const std::string null_formatter("Formatter supplied is null");
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
    const auto& fc(formatter_container_);
    if (fc.object_formatters().empty()) {
        BOOST_LOG_SEV(lg, error) << no_object_formatters;
        BOOST_THROW_EXCEPTION(registrar_error(no_object_formatters));
    }

    if (fc.forward_declarations_formatters().empty()) {
        BOOST_LOG_SEV(lg, error) << no_forward_declarations_formatters;
        BOOST_THROW_EXCEPTION(
            registrar_error(no_forward_declarations_formatters));
    }

    if (fc.all_file_formatters().empty()) {
        BOOST_LOG_SEV(lg, error) << no_all_formatters;
        BOOST_THROW_EXCEPTION(registrar_error(no_all_formatters));
    }

    BOOST_LOG_SEV(lg, debug) << "Registrar is in a valid state. Container: "
                             << fc;
    BOOST_LOG_SEV(lg, debug) << "Ownership hierarchy: " << ownership_hierarchy_;
}

void registrar::
common_registration(std::shared_ptr<formatters::file_formatter_interface> f) {
    ownership_hierarchy_.push_front(f->ownership_hierarchy());
    formatter_container_.all_file_formatters_.push_front(f);
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

    const auto eti(f->element_type_index());
    if (eti == std::type_index(typeid(yarn::enumeration)))
        formatter_container_.enumeration_formatters_.push_front(f);
    else if (eti == std::type_index(typeid(yarn::object)))
        formatter_container_.object_formatters_.push_front(f);
    else if (eti == std::type_index(typeid(yarn::exception)))
        formatter_container_.exception_formatters_.push_front(f);
    else if (eti == std::type_index(typeid(yarn::module)))
        formatter_container_.module_formatters_.push_front(f);
    else if (eti == std::type_index(typeid(yarn::visitor)))
        formatter_container_.visitor_formatters_.push_front(f);
    else if (eti == std::type_index(typeid(yarn::visitor)))
        formatter_container_.visitor_formatters_.push_front(f);
    else if (eti == std::type_index(typeid(fabric::forward_declarations)))
        formatter_container_.forward_declarations_formatters_.push_front(f);
    else if (eti == std::type_index(typeid(fabric::odb_options)))
        formatter_container_.odb_options_formatters_.push_front(f);
    else if (eti == std::type_index(typeid(fabric::cmakelists)))
        formatter_container_.cmakelists_formatters_.push_front(f);
    else if (eti == std::type_index(typeid(fabric::registrar)))
        formatter_container_.registrar_formatters_.push_front(f);
    else if (eti == std::type_index(typeid(fabric::master_header)))
        formatter_container_.master_header_formatters_.push_front(f);
    else
        BOOST_THROW_EXCEPTION(registrar_error(unsupported_element_type));

    common_registration(f);
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
