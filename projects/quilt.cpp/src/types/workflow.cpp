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
    const annotations::element_annotations_repository& esrp,
    const yarn::model& m) const {

    formattables::workflow fw;
    auto r(fw.execute(opts, drp, root_object, dcf, fc, ssrp, m));

    for (const auto& pair : esrp.by_id()) {
        const auto i(r.by_id().find(pair.first));
        if (i != r.by_id().end()) {
            auto& fmt_cfgs(i->second.formatter_configuration());
            const auto& ea(pair.second);
            for (const auto& pair : ea.opaque_annotations()) {
                BOOST_LOG_SEV(lg, debug) << "Found opaque annotation.";

                const auto fmtn(pair.first);
                const auto k(fmt_cfgs.find(fmtn));
                if (k != fmt_cfgs.end()) {
                    BOOST_LOG_SEV(lg, debug) << "Found fmt: " << fmtn;
                    k->second.opaque_configuration().top_level(pair.second);
                } else
                    BOOST_LOG_SEV(lg, debug) << "Did not find fmt: " << fmtn;
            }

            for (const auto& pair : ea.opaque_annotations_for_property()) {
                BOOST_LOG_SEV(lg, debug) << "Found opaque annotation for prop.";
                const auto propid(pair.first);
                for (const auto& pair2 : pair.second) {
                    const auto fmtn(pair2.first);
                    const auto k(fmt_cfgs.find(fmtn));
                    if (k != fmt_cfgs.end()) {
                        BOOST_LOG_SEV(lg, debug) << "Found fmt (prop): "
                                                 << fmtn;

                        k->second.opaque_configuration().property_level()
                            [propid] = pair2.second;
                    } else {
                        BOOST_LOG_SEV(lg, debug) << "Did not find fmt (prop): "
                                                 << fmtn << " prop: " << propid;
                    }
                }
            }
        }
    }
    return r;
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
    const formattables::element_properties_repository& eprp,
    const std::forward_list<
    boost::shared_ptr<yarn::element> >& elements) const {
    formatters::workflow wf;
    return wf.execute(ssrp, eprp, elements);
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
    const auto& fc(formatters::workflow::registrar().formatter_container());

    // const auto osb(create_opaque_annotations_builder(drp));
    // auto esrp(create_element_annotations_repository(osb, m));
    // auto ssrp(create_streaming_annotations_repository(drp, m));

    // formatters::workflow::registrar().validate();

    // const auto& cpp(ko.cpp());
    // const auto eprp(create_properties(cpp, drp, ro, dcf, fc, ssrp, esrp, m));

    // const auto elements(extract_generatable_elements(m));
    // auto r(format(ssrp, eprp, elements));

    formattables::workflow fw;
    const auto fm(fw.execute_new(ko.cpp(), drp, ro, dcf, fc, m));

    formatters::workflow wf;
    const auto r(wf.execute_new(fm));

    BOOST_LOG_SEV(lg, debug) << "Finished C++ backend.";
    return r;
}

} } }
