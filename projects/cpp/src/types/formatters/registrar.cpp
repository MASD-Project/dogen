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
#include "dogen/utility/io/forward_list_io.hpp"
#include "dogen/dynamic/io/ownership_hierarchy_io.hpp"
#include "dogen/cpp/types/formatters/registrar_error.hpp"
#include "dogen/cpp/types/formatters/registrar.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("cpp.formatters.registrar"));

const std::string no_all_formatters("All formatters container is empty.");
const std::string no_class_formatters("No class formatters provided.");
const std::string no_forward_declarations_formatters(
    "No forward declarations formatters provided.");
const std::string null_formatter("Formatter supplied is null");

}

namespace dogen {
namespace cpp {
namespace formatters {

void registrar::validate() const {
    const auto& fc(formatter_container_);
    if (fc.class_formatters().empty()) {
        BOOST_LOG_SEV(lg, error) << no_class_formatters;
        BOOST_THROW_EXCEPTION(registrar_error(no_class_formatters));
    }

    if (fc.forward_declarations_formatters().empty()) {
        BOOST_LOG_SEV(lg, error) << no_forward_declarations_formatters;
        BOOST_THROW_EXCEPTION(
            registrar_error(no_forward_declarations_formatters));
    }

    if (fc.all_formatters().empty()) {
        BOOST_LOG_SEV(lg, error) << no_all_formatters;
        BOOST_THROW_EXCEPTION(registrar_error(no_all_formatters));
    }

    BOOST_LOG_SEV(lg, debug) << "Registrar is in a valid state.";
    BOOST_LOG_SEV(lg, debug) << "Found "
                             << std::distance(
                                 fc.all_formatters().begin(),
                                 fc.all_formatters().end())
                             << " registered formatter(s): ";
    BOOST_LOG_SEV(lg, debug) << "Ownership hierarchy: "
                             << ownership_hierarchy_;
}

void registrar::
common_registration(std::shared_ptr<formatters::formatter_interface> f) {
    ownership_hierarchy_.push_front(f->ownership_hierarchy());
    formatter_container_.all_formatters_.push_front(f);
}

void registrar::register_formatter(
    std::shared_ptr<class_formatter_interface> f) {
    // note: not logging by design
    if (!f)
        BOOST_THROW_EXCEPTION(registrar_error(null_formatter));

    formatter_container_.class_formatters_.push_front(f);
    common_registration(f);
}

void registrar::register_formatter(
    std::shared_ptr<forward_declarations_formatter_interface> f) {
    // note: not logging by design
    if (!f)
        BOOST_THROW_EXCEPTION(registrar_error(null_formatter));

    formatter_container_.forward_declarations_formatters_.push_front(f);
    common_registration(f);
}

const container& registrar::formatter_container() const {
    return formatter_container_;
}

const std::forward_list<dynamic::ownership_hierarchy>&
registrar::ownership_hierarchy() const {
    return ownership_hierarchy_;
}

} } }
