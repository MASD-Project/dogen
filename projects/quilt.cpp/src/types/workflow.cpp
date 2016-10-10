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
#include "dogen/quilt.cpp/types/workflow.hpp"

namespace {

const std::string name("quilt.cpp.workflow");

using namespace dogen::utility::log;
static logger lg(logger_factory(name));

const std::string dot(".");

}

namespace dogen {
namespace quilt {
namespace cpp {

workflow::~workflow() noexcept { }

std::forward_list<boost::filesystem::path> workflow::
make_data_directories() const {
    const auto dir(dogen::utility::filesystem::data_files_directory());
    const auto r(std::forward_list<boost::filesystem::path> { dir });
    return r;
}

dogen::formatters::repository workflow::
create_formatters_repository(
    const std::forward_list<boost::filesystem::path>& data_directories) const {
    dogen::formatters::hydration_workflow hw;
    return hw.hydrate(data_directories);
}

dogen::formatters::decoration_configuration_factory
workflow::create_decoration_configuration_factory(
    const dynamic::repository& drp,
    const dogen::formatters::repository& frp,
    const dynamic::object& root_object) const {

    using dogen::formatters::decoration_configuration_factory;
    decoration_configuration_factory r(drp, frp, root_object);
    return r;
}

formattables::model workflow::create_formattables_model(
    const std::forward_list<boost::filesystem::path>& data_directories,
    const options::cpp_options& opts,
    const dynamic::repository& drp, const dynamic::object& root_object,
    const dogen::formatters::decoration_configuration_factory& dcf,
    const formatters::container& fc, const yarn::model& m) const {

    formattables::workflow fw;
    return fw.execute(data_directories, opts, drp, root_object, dcf, fc, m);
}

std::string workflow::name() const {
    return ::name;
}

std::forward_list<boost::filesystem::path>
workflow::managed_directories(const options::knitting_options& ko,
    const yarn::name& model_name) const {
    const auto& mm(model_name.location().model_modules());
    const auto mn(boost::algorithm::join(mm, dot));
    std::forward_list<boost::filesystem::path> r;
    r.push_front(ko.cpp().project_directory_path() / mn);
    return r;
}

std::forward_list<dogen::formatters::file>
workflow::format(const formattables::model& fm) const {
    formatters::workflow wf;
    return wf.execute(fm);
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
    BOOST_LOG_SEV(lg, debug) << "Started backend.";

    const auto dd(make_data_directories());
    const auto frp(create_formatters_repository(dd));
    const auto ro(m.root_module().extensions());
    const auto dcf(create_decoration_configuration_factory(drp, frp, ro));
    const auto& fc(formatters::workflow::registrar().formatter_container());
    const auto fm(create_formattables_model(dd, ko.cpp(), drp, ro, dcf, fc, m));
    const auto r(format(fm));

    BOOST_LOG_SEV(lg, debug) << "Finished backend.";
    return r;
}

} } }
