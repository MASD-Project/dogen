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
#include <boost/make_shared.hpp>
#include <boost/throw_exception.hpp>
#include "dogen/utility/log/logger.hpp"
#include "dogen/yarn/types/name_factory.hpp"
#include "dogen/yarn/types/expansion_error.hpp"
#include "dogen/quilt.cpp/types/formatters/workflow.hpp"
#include "dogen/quilt.cpp/types/fabric/registrar_factory.hpp"
#include "dogen/quilt.cpp/types/fabric/build_files_factory.hpp"
#include "dogen/quilt.cpp/types/fabric/odb_options_factory.hpp"
#include "dogen/quilt.cpp/types/fabric/master_header_factory.hpp"
#include "dogen/quilt.cpp/types/fabric/visual_studio_factory.hpp"
#include "dogen/quilt.cpp/types/fabric/forward_declarations_factory.hpp"
#include "dogen/quilt.cpp/types/fabric/injector.hpp"

namespace {

const std::string id("quilt.cpp.fabric.injector");

using namespace dogen::utility::log;
static logger lg(logger_factory(id));

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
    yarn::intermediate_model& im) const {
    im.injected_elements().push_back(e);
}

void injector::
add_elements(const std::list<boost::shared_ptr<yarn::element>>& elements,
    yarn::intermediate_model& im) const {
    for (auto& e : elements)
        add_element(e, im);
}

void injector::inject_registrar(yarn::intermediate_model& im) const {
    registrar_factory f;
    const auto elements(f.make(im));
    add_elements(elements, im);
}

void injector::inject_build_files(yarn::intermediate_model& im) const {
    build_files_factory f;
    const auto elements(f.make(im));
    add_elements(elements, im);
}

void injector::inject_odb_options(yarn::intermediate_model& im) const {
    odb_options_factory f;
    const auto elements(f.make(im));
    add_elements(elements, im);
}

void injector::inject_master_headers(yarn::intermediate_model& im) const {
    const auto& rg(formatters::workflow::registrar());
    const auto& frp(rg.formatter_repository());
    master_header_factory f;
    const auto e(f.make(frp, im));
    add_element(e, im);
}

void injector::inject_visual_studio(const annotations::type_repository& atrp,
    yarn::intermediate_model& im) const {
    visual_studio_factory f;
    const auto e(f.make(atrp, im));
    add_elements(e, im);
}

void injector::inject_forward_declarations(yarn::intermediate_model& im) const {
    forward_declarations_factory f;
    const auto e(f.make(im));
    add_elements(e, im);
}

void injector::expand(const annotations::type_repository& atrp,
    const dogen::formatters::decoration_properties_factory& /*dpf*/,
    yarn::intermediate_model& im) const {
    inject_registrar(im);
    inject_build_files(im);
    inject_odb_options(im);
    inject_master_headers(im);
    inject_visual_studio(atrp, im);
    inject_forward_declarations(im);
}

} } } }
