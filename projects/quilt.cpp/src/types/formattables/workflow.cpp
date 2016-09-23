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
#include <memory>
#include <algorithm>
#include <forward_list>
#include "dogen/utility/log/logger.hpp"
#include "dogen/utility/io/memory_io.hpp"
#include "dogen/utility/io/unordered_map_io.hpp"
#include "dogen/utility/io/forward_list_io.hpp"
#include "dogen/yarn/types/element_visitor.hpp"
#include "dogen/quilt.cpp/types/annotations/path_annotations_factory.hpp"
#include "dogen/quilt.cpp/types/annotations/helper_annotations_repository_factory.hpp"
#include "dogen/quilt.cpp/types/annotations/aspect_annotations_repository_factory.hpp"
#include "dogen/quilt.cpp/types/formattables/path_derivatives_repository_factory.hpp"
#include "dogen/quilt.cpp/types/formattables/element_properties_repository_factory.hpp"
#include "dogen/quilt.cpp/types/formattables/formatter_properties_repository_factory.hpp"
#include "dogen/quilt.cpp/types/formattables/workflow.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("quilt.cpp.formattables.workflow"));

}

namespace dogen {
namespace quilt {
namespace cpp {
namespace formattables {

std::shared_ptr<formattables::registrar> workflow::registrar_;

formattables::registrar& workflow::registrar() {
    if (!registrar_)
        registrar_ = std::make_shared<formattables::registrar>();

    return *registrar_;
}

std::unordered_map<std::string, annotations::path_annotations>
workflow::create_path_annotations(const dynamic::repository& drp,
    const dynamic::object& root_object,
    const formatters::container& fc) const {

    BOOST_LOG_SEV(lg, debug) << "Creating path annotations for root object.";
    annotations::path_annotations_factory f(drp, fc.file_formatters());
    const auto r(f.make(root_object));
    BOOST_LOG_SEV(lg, debug) << "Created path annotations for root object.";
    return r;
}

annotations::helper_annotations_repository workflow::
create_helper_annotations_repository(const dynamic::repository& drp,
    const yarn::model& m) const {
    annotations::helper_annotations_repository_factory f;
    return f.make(drp, m);
}

std::unordered_map<std::string, std::string> workflow::
facet_directory_for_facet(const formatters::container& fc,
    const std::unordered_map<std::string,
    annotations::path_annotations>& ps) const {

    std::unordered_map<std::string, std::string> r;
    for (const auto& f : fc.file_formatters()) {
        const auto i(ps.find(f->ownership_hierarchy().formatter_name()));
        if ( i != ps.end()) {
            const auto fn(f->ownership_hierarchy().facet_name());
            r[fn] = i->second.facet_directory();
        }
    }
    BOOST_LOG_SEV(lg, debug) << "Facet directory for facet: " << r;
    return r;
}

annotations::aspect_annotations_repository
workflow::create_aspect_annotations_repository(
    const dynamic::repository& drp, const yarn::model& m) const {
    annotations::aspect_annotations_repository_factory f;
    return f.make(drp, m);
}

path_derivatives_repository workflow::
create_path_derivatives_repository(const formatters::container& fc,
    const locator& l, const yarn::model& m) const {
    path_derivatives_repository_factory f;
    return f.make(fc, l, m);
}

formatter_properties_repository workflow::
create_formatter_properties(const dynamic::repository& drp,
    const dynamic::object& root_object,
    const std::unordered_map<std::string, std::string>& fdff,
    const path_derivatives_repository& pdrp,
    const locator& l,
    const formatters::container& fc,
    const yarn::model& m) const {

    formatter_properties_repository_factory f;
    return f.make(drp, root_object, fdff, pdrp, l, fc, m);
}

element_properties_repository workflow::create_element_properties_repository(
    const dogen::formatters::decoration_configuration_factory& dcf,
    const annotations::helper_annotations_repository& hsrp,
    const annotations::aspect_annotations_repository& asrp,
    const annotations::streaming_annotations_repository& ssrp,
    const formatters::container& fc,
    const formatter_properties_repository& fprp,
    const yarn::model& m) const {
    element_properties_repository_factory f;
    return f.make(dcf, hsrp, asrp, ssrp, fc, fprp, m);
}

element_properties_repository workflow::execute(const options::cpp_options& opts,
    const dynamic::repository& drp,
    const dynamic::object& root_object,
    const dogen::formatters::decoration_configuration_factory& dcf,
    const formatters::container& fc,
    const annotations::streaming_annotations_repository& ssrp,
    const yarn::model& m) const {
    BOOST_LOG_SEV(lg, debug) << "Started creating properties.";

    const auto& ro(root_object);
    const auto ps(create_path_annotations(drp, ro, fc));
    const locator l(opts, m, ps);
    const auto pdrp(create_path_derivatives_repository(fc, l, m));
    const auto fdff(facet_directory_for_facet(fc, ps));
    auto fprp(create_formatter_properties(drp, ro, fdff, pdrp, l, fc, m));

    const auto hsrp(create_helper_annotations_repository(drp, m));
    const auto asrp(create_aspect_annotations_repository(drp, m));
    const auto eprp(create_element_properties_repository(
            dcf, hsrp, asrp, ssrp, fc, fprp, m));

    BOOST_LOG_SEV(lg, debug) << "Finished creating properties.";
    return eprp;
}

} } } }
