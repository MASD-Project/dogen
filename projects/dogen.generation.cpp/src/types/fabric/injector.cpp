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
#include "dogen.utility/types/log/logger.hpp"
#include "dogen.generation.cpp/types/formatters/workflow.hpp"
#include "dogen.generation.cpp/types/fabric/build_files_factory.hpp"
#include "dogen.generation.cpp/types/fabric/odb_options_factory.hpp"
#include "dogen.generation.cpp/types/fabric/entry_point_factory.hpp"
#include "dogen.generation.cpp/types/fabric/injector.hpp"

namespace {

const std::string id("generation.cpp.fabric.injector");

using namespace dogen::utility::log;
static logger lg(logger_factory(id));

}

namespace dogen::generation::cpp::fabric {

injector::~injector() noexcept {}

void injector::
add_element(const boost::shared_ptr<assets::meta_model::element>& e,
    generation::meta_model::model& m) const {
    m.elements().push_back(e);
}

void injector::add_elements(
    const std::list<boost::shared_ptr<assets::meta_model::element>>& elements,
    generation::meta_model::model& m) const {
    for (auto& e : elements)
        add_element(e, m);
}

void injector::
inject_build_files(generation::meta_model::model& m) const {
    build_files_factory f;
    const auto elements(f.make(m));
    add_elements(elements, m);
}

void injector::
inject_odb_options(generation::meta_model::model& m) const {
    odb_options_factory f;
    const auto elements(f.make(m));
    add_elements(elements, m);
}

void injector::inject_entry_point(generation::meta_model::model& m) const {
    entry_point_factory f;
    const auto e(f.make(m));
    add_element(e, m);
}

void injector::inject(generation::meta_model::model& m) const {
    inject_build_files(m);
    inject_odb_options(m);
    inject_entry_point(m);
}

}
