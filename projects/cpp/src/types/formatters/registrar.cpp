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
#include "dogen/dynamic/schema/io/ownership_hierarchy_io.hpp"
#include "dogen/cpp/types/formatters/registrar_error.hpp"
#include "dogen/cpp/types/formatters/registrar.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("cpp.formatters.registrar"));

const std::string no_formatters("No formatters provided.");
const std::string null_formatter("Formatter supplied is null");

}

namespace dogen {
namespace cpp {
namespace formatters {

void registrar::validate() const {
    const auto& fc(formatter_container_);
    if (fc.class_formatters().empty()) {
        BOOST_LOG_SEV(lg, error) << no_formatters;
        BOOST_THROW_EXCEPTION(registrar_error(no_formatters));
    }

    BOOST_LOG_SEV(lg, debug) << "Found "
                             << std::distance(
                                 fc.class_formatters().begin(),
                                 fc.class_formatters().end())
                             << " registered class formatter(s): ";

    BOOST_LOG_SEV(lg, debug) << "Listing all class formatters.";
    for (const auto& f : fc.class_formatters())
        BOOST_LOG_SEV(lg, debug) << f->ownership_hierarchy();

    BOOST_LOG_SEV(lg, debug) << "Registrar is in a valid state.";
}

void registrar::register_formatter(
    std::shared_ptr<class_formatter_interface> f) {
    // note: not logging by design
    if (!f)
        BOOST_THROW_EXCEPTION(registrar_error(null_formatter));

    formatter_container_.class_formatters_.push_front(f);
    formatter_container_.all_formatters_.push_front(f);
}

const container& registrar::formatter_container() const {
    return formatter_container_;
}

} } }
