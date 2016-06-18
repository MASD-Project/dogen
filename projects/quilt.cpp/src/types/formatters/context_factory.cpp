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
#include "dogen/quilt.cpp/types/formatters/building_error.hpp"
#include "dogen/quilt.cpp/types/formatters/context_factory.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("quit.cpp.formatters.context_factory"));

const std::string formatter_properties_not_found(
    "Could not find properties for formatter: ");
const std::string bundle_not_found(
    "Could not find settings bundle for: ");

}

namespace dogen {
namespace quilt {
namespace cpp {
namespace formatters {

const settings::bundle context_factory::empty_bundle_ = settings::bundle();
const std::unordered_map<std::string, settings::helper_settings>
context_factory::empty_helper_settings_ =
    std::unordered_map<std::string, settings::helper_settings>();
const std::unordered_map<std::string,
                         properties::formatter_properties>
context_factory::empty_formatter_properties_ =
    std::unordered_map<std::string, properties::formatter_properties>();
const std::unordered_map<
    std::string,
    std::unordered_map<
        std::string,
        std::shared_ptr<formatter_helper_interface>>> context_factory::
    empty_helpers_ = std::unordered_map<
    std::string,
    std::unordered_map<
        std::string,
        std::shared_ptr<formatter_helper_interface>>>();

context_factory::context_factory(const settings::bundle_repository& brp,
    const settings::helper_settings_repository& hsrp,
    const properties::formatter_properties_repository& fprp,
    const std::unordered_map<
    std::string, std::unordered_map<
    std::string,
    std::shared_ptr<formatter_helper_interface>>>& helpers)
    : bundle_(brp), helper_settings_(hsrp),
      formatter_properties_(fprp), formatter_helpers_(helpers) {}

const std::unordered_map<std::string, properties::formatter_properties>&
context_factory::properties_for_name(const std::string& n) const {
    const auto& fp(formatter_properties_.formatter_properties_by_name());
    const auto i(fp.find(n));
    if (i == fp.end()) {
        BOOST_LOG_SEV(lg, error) << formatter_properties_not_found << n;
        BOOST_THROW_EXCEPTION(
            workflow_error(formatter_properties_not_found + n));
    }
    return i->second;
}

const settings::bundle& context_factory::
bundle_for_name(const std::string& n) const {
    const auto& b(bundle_.bundles_by_name());
    const auto i(b.find(n));
    if (i == b.end()) {
        BOOST_LOG_SEV(lg, error) << bundle_not_found << n;
        BOOST_THROW_EXCEPTION(workflow_error(bundle_not_found + n));
    }
    return i->second;
}

context context_factory::make_empty_context() const {
    return context(empty_bundle_, empty_helper_settings_,
        empty_formatter_properties_, empty_helpers_);
}

context context_factory::make(const std::string& n) const {
    const auto& fp(properties_for_name(n));
    const auto& hs(helper_settings_.helper_settings_by_name());
    const auto& b(bundle_for_name(n));
    return context(b, hs, fp, formatter_helpers_);
}

} } } }
