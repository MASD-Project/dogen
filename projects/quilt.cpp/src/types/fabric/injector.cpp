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
#include "dogen/yarn/types/injection_error.hpp"
#include "dogen/quilt.cpp/types/formatters/workflow.hpp"
#include "dogen/quilt.cpp/types/fabric/registrar_factory.hpp"
#include "dogen/quilt.cpp/types/fabric/master_header_factory.hpp"
#include "dogen/quilt.cpp/types/fabric/injector.hpp"

namespace {

const std::string id("quilt.cpp.fabric.injector");

using namespace dogen::utility::log;
static logger lg(logger_factory(id));

const std::string duplicate_qualified_name("Duplicate qualified name: ");

}

namespace dogen {
namespace quilt {
namespace cpp {
namespace fabric {

injector::~injector() noexcept {}

std::string injector::id() const {
    return ::id;
}

void injector::add_element(const boost::shared_ptr<yarn::element>& e,
    yarn::model& m) const {
    const auto id(e->name().id());
    const auto pair(m.elements().insert(std::make_pair(id, e)));
    if (!pair.second) {
        using yarn::injection_error;
        BOOST_LOG_SEV(lg, error) << duplicate_qualified_name << id;
        BOOST_THROW_EXCEPTION(injection_error(duplicate_qualified_name + id));
    }
}

void injector::
add_elements(const std::list<boost::shared_ptr<yarn::element>>& elements,
    yarn::model& m) const {
    for (auto& e : elements)
        add_element(e, m);
}

void injector::inject_registrar(yarn::model& m) const {
    registrar_factory f;
    const auto elements(f.build(m));
    add_elements(elements, m);
}

void injector::inject_master_headers(yarn::model& m) const {
    const auto& rg(formatters::workflow::registrar());
    const auto& fc(rg.formatter_container());
    master_header_factory f;
    const auto e(f.build(fc, m));
    add_element(e, m);
}

void injector::inject(yarn::model& m) const {
    inject_registrar(m);
    inject_master_headers(m);
}

} } } }
