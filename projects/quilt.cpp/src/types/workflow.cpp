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
#include <boost/algorithm/string/join.hpp>
#include "dogen/utility/log/logger.hpp"
#include "dogen/utility/filesystem/path.hpp"
#include "dogen/formatters/types/hydration_workflow.hpp"
#include "dogen/dynamic/types/workflow.hpp"
#include "dogen/quilt.cpp/types/formatters/workflow.hpp"
#include "dogen/quilt.cpp/types/properties/workflow.hpp"
#include "dogen/quilt.cpp/types/annotations/directory_names_annotations_factory.hpp"
#include "dogen/quilt.cpp/types/annotations/aspect_annotations_repository_factory.hpp"
#include "dogen/quilt.cpp/types/annotations/streaming_annotations_repository_factory.hpp"
#include "dogen/quilt.cpp/types/annotations/element_annotations_repository_factory.hpp"
#include "dogen/quilt.cpp/types/workflow_error.hpp"
#include "dogen/quilt.cpp/types/workflow.hpp"

namespace {

const std::string id("quilt.cpp.workflow");

using namespace dogen::utility::log;
static logger lg(logger_factory(id));

const std::string dot(".");

}

namespace dogen {
namespace quilt {
namespace cpp {

workflow::~workflow() noexcept { }

dogen::formatters::repository workflow::create_formatters_repository(
    const std::forward_list<boost::filesystem::path>& dirs) const {
    dogen::formatters::hydration_workflow hw;
    return hw.hydrate(dirs);
}

dogen::formatters::file_properties_workflow
workflow::create_file_properties_workflow(const dynamic::repository& drp,
    const dogen::formatters::repository& frp,
    const dynamic::object& root_object) const {
    dogen::formatters::file_properties_workflow r(drp, frp, root_object);
    return r;
}

annotations::opaque_annotations_builder workflow::
create_opaque_annotations_builder(const dynamic::repository& drp) const {
    annotations::opaque_annotations_builder r;
    r.setup(drp);
    r.validate();
    return r;
}

annotations::streaming_annotations_repository workflow::
create_streaming_annotations_repository(const dynamic::repository& drp,
    const yarn::model& m) const {
    annotations::streaming_annotations_repository_factory f;
    return f.make(drp, m);
}

annotations::element_annotations_repository
workflow::create_element_annotations_repository(
    const annotations::opaque_annotations_builder& osb, const yarn::model& m) const {
    annotations::element_annotations_repository_factory f;
    return f.make(osb, m);
}

properties::element_properties_repository workflow::create_properties(
    const options::cpp_options& opts,
    const dynamic::repository& srp,
    const dynamic::object& root_object,
    const dogen::formatters::file_properties_workflow& fpwf,
    const formatters::container& fc,
    const annotations::streaming_annotations_repository& ssrp,
    const yarn::model& m) const {

    properties::workflow fw;
    return fw.execute(opts, srp, root_object, fpwf, fc, ssrp, m);
}

std::forward_list<boost::shared_ptr<yarn::element> >
workflow::extract_generatable_elements(const yarn::model& m) const {
    std::forward_list<boost::shared_ptr<yarn::element> > r;

    for (const auto& e : m.elements()) {
        if (e->generation_type() != yarn::generation_types::no_generation)
            r.push_front(e);
    }
    return r;
}

std::forward_list<dogen::formatters::file> workflow::
format(const annotations::streaming_annotations_repository& ssrp,
    const annotations::element_annotations_repository& esrp,
    const properties::element_properties_repository& eprp,
    const std::forward_list<
    boost::shared_ptr<yarn::element> >& elements) const {
    formatters::workflow wf;
    return wf.execute(ssrp, esrp, eprp, elements);
}

std::string workflow::name() const {
    return ::id;
}

std::forward_list<boost::filesystem::path>
workflow::managed_directories(const options::knitting_options& ko,
    const dynamic::repository& rp, const yarn::model& m) const {
    const auto ro(m.root_module().extensions());
    annotations::directory_names_annotations_factory f(rp);
    const auto dn(f.make(ro));
    const auto& mm(m.name().location().model_modules());
    const auto mn(boost::algorithm::join(mm, dot));
    std::forward_list<boost::filesystem::path> r;
    r.push_front(ko.cpp().project_directory_path() / mn);
    return r;
}

std::forward_list<dynamic::ownership_hierarchy>
workflow::ownership_hierarchy() const {
    using formatters::workflow;
    return workflow::registrar().ownership_hierarchy();
}

std::forward_list<dogen::formatters::file>
workflow::generate(const options::knitting_options& ko,
    const dynamic::repository& drp,
    const yarn::model& m) const {
    BOOST_LOG_SEV(lg, debug) << "Started C++ backend.";

    const auto dir(dogen::utility::filesystem::data_files_directory());
    const auto dirs(std::forward_list<boost::filesystem::path> { dir });
    const auto frp(create_formatters_repository(dirs));

    const auto ro(m.root_module().extensions());
    const auto fpwf(create_file_properties_workflow(drp, frp, ro));

    const auto osb(create_opaque_annotations_builder(drp));
    auto esrp(create_element_annotations_repository(osb, m));
    auto ssrp(create_streaming_annotations_repository(drp, m));

    formatters::workflow::registrar().validate();
    const auto& fc(formatters::workflow::registrar().formatter_container());

    const auto& cpp(ko.cpp());
    const auto eprp(create_properties(cpp, drp, ro, fpwf, fc, ssrp, m));

    const auto elements(extract_generatable_elements(m));
    auto r(format(ssrp, esrp, eprp, elements));

    BOOST_LOG_SEV(lg, debug) << "Finished C++ backend.";
    return r;
}

} } }
