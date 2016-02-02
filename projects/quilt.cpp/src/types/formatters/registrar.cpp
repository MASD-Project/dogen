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
#include "dogen/utility/log/logger.hpp"
#include "dogen/utility/io/forward_list_io.hpp"
#include "dogen/dynamic/io/ownership_hierarchy_io.hpp"
#include "dogen/quilt.cpp/types/formatters/registrar_error.hpp"
#include "dogen/quilt.cpp/types/formatters/registrar.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("quilt.cpp.formatters.registrar"));

const std::string no_all_formatters("All formatters container is empty.");
const std::string no_class_formatters("No class formatters provided.");
const std::string no_forward_declarations_formatters(
    "No forward declarations formatters provided.");
const std::string null_formatter("Formatter supplied is null");
const std::string null_formatter_helper("Formatter helper supplied is null");
const std::string helper_already_registered("Helper already registered: ");

}

namespace dogen {
namespace quilt {
namespace cpp {
namespace formatters {

template<class Container>
unsigned long size(const Container& c) {
    return std::distance(c.begin(), c.end());
}

template<class Container>
void log_container_sizes(
    const std::string& formatter_type, const Container& c) {
    const auto sz(size(c));
    if (sz == 0) {
        BOOST_LOG_SEV(lg, warn) << "Registered formatters for '"
                                << formatter_type << "': "
                                << sz;
    } else {
        BOOST_LOG_SEV(lg, debug) << "Registered formatters for '"
                                 << formatter_type << "': "
                                 << sz;
    }
}

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
    BOOST_LOG_SEV(lg, debug) << "Found a total of "
                             << size(fc.all_formatters())
                             << " registered formatter(s).";

    log_container_sizes("class formatters", fc.class_formatters());
    log_container_sizes("enum formatters", fc.enum_formatters());
    log_container_sizes("exception formatters", fc.exception_formatters());
    log_container_sizes("namespace formatters", fc.namespace_formatters());
    log_container_sizes("visitor formatters", fc.visitor_formatters());
    log_container_sizes("forward declarations formatters",
        fc.forward_declarations_formatters());
    log_container_sizes("odb options formatters", fc.odb_options_formatters());
    log_container_sizes("cmakelists formatters", fc.cmakelists_formatters());
    log_container_sizes("registrar formatters", fc.registrar_formatters());
    log_container_sizes("Includers formatters", fc.includers_formatters());

    BOOST_LOG_SEV(lg, debug) << "Ownership hierarchy: "
                             << ownership_hierarchy_;
}

void registrar::
common_registration(std::shared_ptr<formatters::formatter_interface> f) {
    ownership_hierarchy_.push_front(f->ownership_hierarchy());
    formatter_container_.all_formatters_.push_front(f);
    using ot = formattables::origin_types;
    if (f->formattable_origin_type() == ot::internal)
        formatter_container_.all_internal_formatters_.push_front(f);
    else if (f->formattable_origin_type() == ot::external)
        formatter_container_.all_external_formatters_.push_front(f);
}

void registrar::register_formatter_helper(
    std::shared_ptr<formatter_helper_interface> fh) {

    // note: not logging by design
    if (!fh)
        BOOST_THROW_EXCEPTION(registrar_error(null_formatter_helper));

    auto& c(formatter_helpers_[fh->owning_formatter()]);
    const auto result(c.insert(std::make_pair(fh->family(), fh)));
    if (!result.second) {
        BOOST_THROW_EXCEPTION(
            registrar_error(helper_already_registered + fh->helper_name()));
    }
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
    std::shared_ptr<enum_formatter_interface> f) {
    // note: not logging by design
    if (!f)
        BOOST_THROW_EXCEPTION(registrar_error(null_formatter));

    formatter_container_.enum_formatters_.push_front(f);
    common_registration(f);
}

void registrar::register_formatter(
    std::shared_ptr<exception_formatter_interface> f) {
    // note: not logging by design
    if (!f)
        BOOST_THROW_EXCEPTION(registrar_error(null_formatter));

    formatter_container_.exception_formatters_.push_front(f);
    common_registration(f);
}

void registrar::register_formatter(
    std::shared_ptr<namespace_formatter_interface> f) {
    // note: not logging by design
    if (!f)
        BOOST_THROW_EXCEPTION(registrar_error(null_formatter));

    formatter_container_.namespace_formatters_.push_front(f);
    common_registration(f);
}

void registrar::register_formatter(
    std::shared_ptr<visitor_formatter_interface> f) {
    // note: not logging by design
    if (!f)
        BOOST_THROW_EXCEPTION(registrar_error(null_formatter));

    formatter_container_.visitor_formatters_.push_front(f);
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

void registrar::register_formatter(
    std::shared_ptr<odb_options_formatter_interface> f) {
    // note: not logging by design
    if (!f)
        BOOST_THROW_EXCEPTION(registrar_error(null_formatter));

    formatter_container_.odb_options_formatters_.push_front(f);
    common_registration(f);
}

void registrar::register_formatter(
    std::shared_ptr<cmakelists_formatter_interface> f) {
    // note: not logging by design
    if (!f)
        BOOST_THROW_EXCEPTION(registrar_error(null_formatter));

    formatter_container_.cmakelists_formatters_.push_front(f);
    common_registration(f);
}

void registrar::register_formatter(
    std::shared_ptr<registrar_formatter_interface> f) {
    // note: not logging by design
    if (!f)
        BOOST_THROW_EXCEPTION(registrar_error(null_formatter));

    formatter_container_.registrar_formatters_.push_front(f);
    common_registration(f);
}

void registrar::register_formatter(
    std::shared_ptr<includers_formatter_interface> f) {
    // note: not logging by design
    if (!f)
        BOOST_THROW_EXCEPTION(registrar_error(null_formatter));

    formatter_container_.includers_formatters_.push_front(f);
    common_registration(f);
}

const container& registrar::formatter_container() const {
    return formatter_container_;
}

const std::forward_list<dynamic::ownership_hierarchy>&
registrar::ownership_hierarchy() const {
    return ownership_hierarchy_;
}

} } } }
