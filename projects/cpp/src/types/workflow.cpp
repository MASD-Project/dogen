/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda <info@kitanda.co.uk>
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
#include "dogen/dynamic/types/workflow.hpp"
#include "dogen/tack/types/string_converter.hpp"
#include "dogen/cpp/types/formatters/workflow.hpp"
#include "dogen/cpp/types/formattables/workflow.hpp"
#include "dogen/cpp/types/settings/directory_names_settings_factory.hpp"
#include "dogen/cpp/types/settings/bundle_repository_factory.hpp"
#include "dogen/cpp/types/workflow_error.hpp"
#include "dogen/cpp/types/workflow.hpp"

namespace {

const std::string id("cpp.workflow");

using namespace dogen::utility::log;
static logger lg(logger_factory(id));

const std::string model_module_not_found("Model module not found for model: ");

}

namespace dogen {
namespace cpp {

workflow::~workflow() noexcept { }

dynamic::object workflow::obtain_root_object(const tack::model& m) const {
    BOOST_LOG_SEV(lg, debug) << "Obtaining model's root object.";

    const auto i(m.modules().find(m.name()));
    if (i == m.modules().end()) {
        const auto n(tack::string_converter::convert(m.name()));
        BOOST_LOG_SEV(lg, error) << model_module_not_found << n;
        BOOST_THROW_EXCEPTION(workflow_error(model_module_not_found + n));
    }

    BOOST_LOG_SEV(lg, debug) << "Obtained model's root object.";
    return i->second.extensions();
}

dogen::formatters::repository workflow::create_formatters_repository(
    const std::forward_list<boost::filesystem::path>& dirs) const {
    dogen::formatters::hydration_workflow hw;
    return hw.hydrate(dirs);
}

dogen::formatters::general_settings_factory workflow::
create_general_settings_factory(const dogen::formatters::repository& frp,
    const dynamic::object& root_object) const {
    dogen::formatters::general_settings_factory r(frp, root_object);
    return r;
}

settings::opaque_settings_builder workflow::
create_opaque_settings_builder(const dynamic::repository& rp) const {
    settings::opaque_settings_builder r;
    r.setup(rp);
    r.validate();
    return r;
}

settings::bundle_repository workflow::create_bundle_repository(
    const dynamic::repository& rp, const dynamic::object& root_object,
    const dogen::formatters::general_settings_factory& gsf,
    const settings::opaque_settings_builder& osb, const tack::model& m) const {
    settings::bundle_repository_factory f;
    return f.make(rp, root_object, gsf, osb, m);
}

std::forward_list<std::shared_ptr<formattables::formattable> >
workflow::create_formattables_activty(
    const config::cpp_options& opts,
    const dynamic::repository& srp,
    const dynamic::object& root_object,
    const dogen::formatters::general_settings_factory& gsf,
    const formatters::container& fc,
    const settings::opaque_settings_builder& osb,
    const settings::bundle_repository& brp,
    const tack::model& m) const {

    formattables::workflow fw;
    return fw.execute(opts, srp, root_object, gsf, fc, osb, brp, m);
}

std::forward_list<dogen::formatters::file>
workflow::format_activty(const std::forward_list<
        std::shared_ptr<formattables::formattable>
        >& f) const {
    formatters::workflow w;
    return w.execute(f);
}

std::string workflow::name() const {
    return ::id;
}

std::forward_list<boost::filesystem::path>
workflow::managed_directories(const config::knitting_options& ko,
    const dynamic::repository& rp, const tack::model& m) const {
    const auto ro(obtain_root_object(m));
    settings::directory_names_settings_factory f(rp);
    const auto dn(f.make(ro));
    const auto mn(m.name().simple_name());

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
workflow::generate(const config::knitting_options& ko,
    const dynamic::repository& rp,
    const tack::model& m) const {
    BOOST_LOG_SEV(lg, debug) << "Started C++ backend.";

    const auto dir(dogen::utility::filesystem::data_files_directory());
    const auto dirs(std::forward_list<boost::filesystem::path> { dir });
    const auto frp(create_formatters_repository(dirs));

    const auto ro(obtain_root_object(m));
    const auto gsf(create_general_settings_factory(frp, ro));

    const auto osb(create_opaque_settings_builder(rp));
    const auto brp(create_bundle_repository(rp, ro, gsf, osb, m));

    formatters::workflow::registrar().validate();
    const auto& fc(formatters::workflow::registrar().formatter_container());

    const auto& kcpp(ko.cpp());
    const auto f(
        create_formattables_activty(kcpp, rp, ro, gsf, fc, osb, brp, m));
    const auto r(format_activty(f));

    BOOST_LOG_SEV(lg, debug) << "Finished C++ backend.";
    return r;
}

} }
