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
#include "dogen/yarn/types/validation_error.hpp"
#include "dogen/yarn/types/elements_traversal.hpp"
#include "dogen/yarn/types/intermediate_model_validator.hpp"

namespace {

using namespace dogen::utility::log;
auto lg(logger_factory("yarn.intermediate_model_validator"));

const std::string multiple_inheritance_not_supported(
    "Multiple inheritance is not supported on target models: ");

}

namespace dogen {
namespace yarn {

class validator {
public:
    validator(const bool is_proxy_reference);

public:
    void operator()(const yarn::concept& c) const;
    void operator()(const yarn::primitive& p) const;
    void operator()(const dogen::yarn::visitor& v) const;
    void operator()(const yarn::enumeration& e) const;
    void operator()(const yarn::object& o) const;
    void operator()(const yarn::exception& e) const;
    void operator()(const yarn::module& m) const;

private:
    const bool is_proxy_reference_;
};

validator::validator(const bool is_proxy_reference)
    : is_proxy_reference_(is_proxy_reference) {}

void validator::operator()(const yarn::concept& /*c*/) const {
}

void validator::operator()(const yarn::primitive& /*p*/) const {
}

void validator::operator()(const dogen::yarn::visitor& /*v*/) const {
}

void validator::operator()(const yarn::enumeration& /*e*/) const {
}

void validator::operator()(const yarn::object& o) const {
    /*
     * Only proxy reference models can have multiple inheritance.
     */
    if (o.parents().size() > 1 && !is_proxy_reference_) {
        const auto id(o.name().id());
        BOOST_LOG_SEV(lg, error) << multiple_inheritance_not_supported << id;
        BOOST_THROW_EXCEPTION(validation_error(
                multiple_inheritance_not_supported + id));
    }
}

void validator::operator()(const yarn::exception& /*e*/) const {
}

void validator::operator()(const yarn::module& /*m*/) const {
}

void intermediate_model_validator::
validate(const intermediate_model& im) const {
    BOOST_LOG_SEV(lg, debug) << "Started validation. Model: " << im.name().id();

    const bool ipr(im.origin_type() == origin_types::proxy_reference);
    validator v(ipr/*is_proxy_reference*/);
    yarn::elements_traversal(im, v);

    BOOST_LOG_SEV(lg, debug) << "Finished validation.";
}

} }
