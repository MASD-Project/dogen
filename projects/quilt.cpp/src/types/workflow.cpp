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
#include "dogen/utility/io/list_io.hpp"
#include "dogen/utility/io/optional_io.hpp"
#include "dogen/utility/filesystem/path.hpp"
#include "dogen/formatters/io/decoration_configuration_io.hpp"
#include "dogen/formatters/types/hydration_workflow.hpp"
#include "dogen/dynamic/types/workflow.hpp"
#include "dogen/quilt.cpp/types/formatters/workflow.hpp"
#include "dogen/quilt.cpp/types/formattables/workflow.hpp"
#include "dogen/quilt.cpp/io/formattables/aspect_configuration_io.hpp"
#include "dogen/quilt.cpp/io/formattables/helper_configuration_io.hpp"
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

dogen::formatters::decoration_configuration_factory
workflow::create_decoration_configuration_factory(
    const dynamic::repository& drp,
    const dogen::formatters::repository& frp,
    const dynamic::object& root_object) const {
    dogen::formatters::decoration_configuration_factory
        r(drp, frp, root_object);
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
    const annotations::opaque_annotations_builder& osb,
    const yarn::model& m) const {
    annotations::element_annotations_repository_factory f;
    return f.make(osb, m);
}

formattables::element_properties_repository workflow::create_properties(
    const options::cpp_options& opts,
    const dynamic::repository& drp,
    const dynamic::object& root_object,
    const dogen::formatters::decoration_configuration_factory& dcf,
    const formatters::container& fc,
    const annotations::streaming_annotations_repository& ssrp,
    const yarn::model& m) const {

    formattables::workflow fw;
    const auto r(fw.execute(opts, drp, root_object, dcf, fc, ssrp, m));

    test_new_formattables_workflow(opts, drp, root_object, dcf, fc, m, r);
    return r;
}

void workflow::test_new_formattables_workflow(const options::cpp_options& opts,
    const dynamic::repository& rp, const dynamic::object& root_object,
    const dogen::formatters::decoration_configuration_factory& dcf,
    const formatters::container& fc, const yarn::model& m,
    const formattables::element_properties_repository& legacy) const {

    formattables::workflow fw;
    const auto formattables(fw.execute_new(opts, rp, root_object, dcf, fc, m));

    /* check no longer works due to reduction.

    const auto fbl_sz(std::distance(formattables.begin(), formattables.end()));
    if (std::size_t(fbl_sz) != legacy.by_id().size()) {
        BOOST_LOG_SEV(lg, error) << "Main containers differ in size. Legacy: "
                                 << legacy.by_id().size()
                                 << " formattables: " << fbl_sz;
        BOOST_THROW_EXCEPTION(
            workflow_error("Containers have different sizes."));
    }
    */

    for (const auto& formattable: formattables) {
        for (const auto& segment : formattable.element_segments()) {
            const auto& e(*segment);
            const auto& id(e.name().id());
            const auto i(legacy.by_id().find(id));
            if (i == legacy.by_id().end()) {
                BOOST_LOG_SEV(lg, error)
                    << "Could not find element id in legacy: "
                    << id;
                BOOST_THROW_EXCEPTION(workflow_error(
                        "Could not find element id in legacy: " + id));
            }

            const auto& legacy_fmt_cfgs(i->second.formatter_configuration());
            const auto& elm_cfg(formattable.configuration());

            if (elm_cfg.decoration_configuration() !=
                i->second.decoration_configuration()) {
                BOOST_LOG_SEV(lg, error) << "Incorrect decoration. id: " << id
                                         << " Legacy: "
                                         << i->second.decoration_configuration()
                                         << " new: "
                                         << elm_cfg.decoration_configuration();
                BOOST_THROW_EXCEPTION(
                    workflow_error("Decoration is incorreact."));

            }

            if (elm_cfg.helper_configuration() !=
                i->second.helper_configuration()) {
                BOOST_LOG_SEV(lg, error) << "Incorrect helper cfg. id: " << id
                                         << " Legacy: "
                                         << i->second.helper_configuration()
                                         << " new: "
                                         << elm_cfg.helper_configuration();
                BOOST_THROW_EXCEPTION(
                    workflow_error("Helper is incorreact."));
            }

            if (elm_cfg.aspect_configuration() !=
                i->second.aspect_configuration()) {
                BOOST_LOG_SEV(lg, error) << "Incorrect aspect config. id: "
                                         << id << " Legacy: "
                                         << i->second.aspect_configuration()
                                         << " new: "
                                         << elm_cfg.aspect_configuration();
                BOOST_THROW_EXCEPTION(
                    workflow_error("Aspect config is incorreact."));

            }

            const auto& fmt_cfgs(elm_cfg.formatter_configuration());
            if (fmt_cfgs.size() > legacy_fmt_cfgs.size()) {
                BOOST_LOG_SEV(lg, error) << "Incorrect size. Legacy: "
                                         << legacy_fmt_cfgs.size()
                                         << " formattables: "
                                         << fmt_cfgs.size();
                BOOST_THROW_EXCEPTION(
                    workflow_error("New container has unexpected size."));
            }

            for (const auto& pair : fmt_cfgs) {
                const auto fmtn(pair.first);
                const auto k(legacy_fmt_cfgs.find(fmtn));
                if (k == legacy_fmt_cfgs.end()) {
                    BOOST_LOG_SEV(lg, error)
                        << "Formatter not found in legacy: "
                        << fmtn;
                    BOOST_THROW_EXCEPTION(
                        workflow_error("Missing formatter: " + fmtn));
                }

                if (pair.second.enabled() != k->second.enabled()) {
                    BOOST_LOG_SEV(lg, error) << "Enablement is different. Id: "
                                             << id << " formatter: " << fmtn
                                             << " new: "
                                             << pair.second.enabled()
                                             << " legacy: "
                                             << k->second.enabled();
                    BOOST_THROW_EXCEPTION(
                        workflow_error("Different enablement."));
                }

                if (pair.second.inclusion_dependencies() !=
                    k->second.inclusion_dependencies()) {
                    BOOST_LOG_SEV(lg, error) << "Dependencies are different. "
                                             << "Id: " << id << " new: "
                                             << pair.second.inclusion_dependencies()
                                             << " old: "
                                             << k->second.inclusion_dependencies();
                    BOOST_THROW_EXCEPTION(
                        workflow_error("Different inclusion."));
                }

                if (pair.second.file_path() != k->second.file_path()) {
                    BOOST_LOG_SEV(lg, error) << "File path is different. "
                                             << "Id: " << id << " new: "
                                             << pair.second.file_path()
                                             << " old: "
                                             << k->second.file_path();
                    BOOST_THROW_EXCEPTION(
                        workflow_error("Different file paths."));
                }

                if (pair.second.header_guard() != k->second.header_guard()) {
                    BOOST_LOG_SEV(lg, error) << "Header guard is different. "
                                             << "Id: " << id << " new: "
                                             << pair.second.header_guard()
                                             << " old: "
                                             << k->second.header_guard();
                    BOOST_THROW_EXCEPTION(
                        workflow_error("Different header guard."));
                }
            }
        }
    }
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
    const formattables::element_properties_repository& eprp,
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
    const auto dcf(create_decoration_configuration_factory(drp, frp, ro));

    const auto osb(create_opaque_annotations_builder(drp));
    auto esrp(create_element_annotations_repository(osb, m));
    auto ssrp(create_streaming_annotations_repository(drp, m));

    formatters::workflow::registrar().validate();
    const auto& fc(formatters::workflow::registrar().formatter_container());

    const auto& cpp(ko.cpp());
    const auto eprp(create_properties(cpp, drp, ro, dcf, fc, ssrp, m));

    const auto elements(extract_generatable_elements(m));
    auto r(format(ssrp, esrp, eprp, elements));

    BOOST_LOG_SEV(lg, debug) << "Finished C++ backend.";
    return r;
}

} } }
