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
#include "dogen.utility/log/logger.hpp"
#include "dogen.quilt.cpp/types/formatters/workflow.hpp"
#include "dogen.quilt.cpp/types/fabric/registrar_factory.hpp"
#include "dogen.quilt.cpp/types/fabric/build_files_factory.hpp"
#include "dogen.quilt.cpp/types/fabric/odb_options_factory.hpp"
#include "dogen.quilt.cpp/types/fabric/master_header_factory.hpp"
#include "dogen.quilt.cpp/types/fabric/visual_studio_factory.hpp"
#include "dogen.quilt.cpp/types/fabric/forward_declarations_factory.hpp"
#include "dogen.quilt.cpp/types/fabric/injector.hpp"

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

void injector::
add_element(const boost::shared_ptr<yarn::meta_model::element>& e,
    yarn::meta_model::model& m) const {
    m.elements().push_back(e);
}

void injector::add_elements(
    const std::list<boost::shared_ptr<yarn::meta_model::element>>& elements,
    yarn::meta_model::model& m) const {
    for (auto& e : elements)
        add_element(e, m);
}

void injector::
inject_registrar(yarn::meta_model::model& m) const {
    registrar_factory f;
    const auto elements(f.make(m));
    add_elements(elements, m);
}

void injector::
inject_build_files(yarn::meta_model::model& m) const {
    build_files_factory f;
    const auto elements(f.make(m));
    add_elements(elements, m);
}

void injector::
inject_odb_options(yarn::meta_model::model& m) const {
    odb_options_factory f;
    const auto elements(f.make(m));
    add_elements(elements, m);
}

void injector::
inject_master_headers(yarn::meta_model::model& m) const {
    const auto& rg(formatters::workflow::registrar());
    const auto& frp(rg.formatter_repository());
    master_header_factory f;
    const auto e(f.make(frp, m));
    add_element(e, m);
}

void injector::inject_visual_studio(const annotations::type_repository& atrp,
    yarn::meta_model::model& m) const {
    visual_studio_factory f;
    const auto e(f.make(atrp, m));
    add_elements(e, m);
}

void injector::
inject_forward_declarations(yarn::meta_model::model& m) const {
    forward_declarations_factory f;
    const auto e(f.make(m));
    add_elements(e, m);
}

void injector::inject(const annotations::type_repository& atrp,
    yarn::meta_model::model& m) const {
    inject_registrar(m);
    inject_build_files(m);
    inject_odb_options(m);
    inject_master_headers(m);
    inject_visual_studio(atrp, m);
    inject_forward_declarations(m);
}

} } } }
