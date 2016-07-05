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
#include "dogen/utility/filesystem/path.hpp"
#include "dogen/formatters/types/hydration_workflow.hpp"
#include "dogen/quilt.cpp/types/settings/element_settings_factory.hpp"
#include "dogen/quilt.cpp/types/settings/bundle_factory.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("quilt.cpp.settings.bundle_factory"));

const std::string cpp_modeline_name("cpp");

}

namespace dogen {
namespace quilt {
namespace cpp {
namespace settings {

bundle_factory::bundle_factory(const dynamic::repository& rp,
    const dynamic::object& root_object,
    const dogen::formatters::file_properties_factory& fpf,
    const opaque_settings_builder& osb) :
    dynamic_repository_(rp), root_object_(root_object),
    file_properties_factory_(fpf), opaque_settings_builder_(osb) { }

dogen::formatters::file_properties bundle_factory::
create_file_properties(const dynamic::object& o) const {
    return file_properties_factory_.make(cpp_modeline_name, o);
}

element_settings bundle_factory::
create_element_settings(const dynamic::object& o) const {
    element_settings_factory f(dynamic_repository_, root_object_);
    return f.make(o);
}

std::unordered_map<
    std::string,
    boost::shared_ptr<opaque_settings>
> bundle_factory::create_opaque_settings(const dynamic::object& o) const {
    return opaque_settings_builder_.build(o);
}

bundle bundle_factory::make(const dynamic::object& o) const {
    bundle r;
    r.file_properties(create_file_properties(o));
    r.opaque_settings(create_opaque_settings(o));
    r.element_settings(create_element_settings(o));
    return r;
}

bundle bundle_factory::make() const {
    bundle r;
    r.file_properties(create_file_properties(root_object_));

    element_settings_factory f(dynamic_repository_, root_object_);
    r.element_settings(f.make());
    return r;
}

} } } }
