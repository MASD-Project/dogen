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
#include <iterator>
#include <boost/throw_exception.hpp>
#include "dogen/utility/log/logger.hpp"
#include "dogen/utility/filesystem/path.hpp"
#include "dogen/annotations/io/type_io.hpp"
#include "dogen/formatters/types/repository_factory.hpp"
#include "dogen/quilt/types/configuration_factory.hpp"
#include "dogen/quilt/types/workflow_error.hpp"
#include "dogen/quilt/types/workflow.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("quilt.workflow"));

std::string empty;
const std::string null_registrar("Registrar is null");
const std::string no_generatable_model_modules(
    "No generatable model modules found.");
const std::string multiple_generatable_model_modules(
    "More than one model module is generatable: ");

}
namespace dogen {
namespace quilt {

std::shared_ptr<kernel_registrar> workflow::registrar_;

workflow::workflow(const options::knitting_options& o,
    const annotations::type_repository& atrp,
    const annotations::annotation_groups_factory& agf)
    : knitting_options_(o), repository_(atrp), annotation_factory_(agf) {}

std::list<annotations::archetype_location>
workflow::kernel_archetype_locations() const {
    std::list<annotations::archetype_location> r;
    const auto& rg(quilt::workflow::registrar());
    for (const auto k : rg.kernels())
        r.push_back(k->archetype_location());
    return r;
}

std::vector<boost::filesystem::path> workflow::
obtain_data_directories() const {
    const auto dir(dogen::utility::filesystem::data_files_directory());
    const auto r(std::vector<boost::filesystem::path> { dir });
    return r;
}

dogen::formatters::repository workflow::
create_formatters_decoration_repository(
    const std::vector<boost::filesystem::path>& data_directories) const {
    dogen::formatters::repository_factory hw;
    return hw.make(data_directories);
}

dogen::formatters::decoration_properties_factory
workflow::create_decoration_properties_factory(
    const annotations::type_repository& atrp,
    const dogen::formatters::repository& frp,
    const annotations::annotation& ra) const {
    using dogen::formatters::decoration_properties_factory;
    decoration_properties_factory r(atrp, frp, ra);
    return r;
}

kernel_registrar& workflow::registrar() {
    if (!registrar_)
        registrar_ = std::make_shared<kernel_registrar>();

    return *registrar_;
}

std::list<annotations::archetype_location> workflow::archetype_locations() {
    std::list<annotations::archetype_location> r;
    const auto& rg(quilt::workflow::registrar());
    for (const auto k : rg.kernels()) {
        // not splicing due to a mistmatch in the list types
        for (const auto al : k->archetype_locations())
            r.push_back(al);
    }
    return r;
}

std::forward_list<boost::filesystem::path>
workflow::managed_directories(const yarn::model& m) const {
    const auto& ko(knitting_options_);
    std::forward_list<boost::filesystem::path> r;
    for(const auto b : registrar().kernels()) {
        // not splicing due to a mistmatch in the list types
        const auto md(b->managed_directories(ko, m.name()));
        for (const auto& d : md)
            r.push_front(d);
    }
    return r;
}

std::forward_list<formatters::artefact>
workflow::execute(const yarn::model& m) const {
    const auto ra(m.root_module().annotation());
    const auto kals(kernel_archetype_locations());
    configuration_factory cf;
    const auto cfg(cf.make(repository_, kals, ra));

    const auto& atrp(repository_);
    const auto& af(annotation_factory_);

    const auto dd(obtain_data_directories());
    const auto drp(create_formatters_decoration_repository(dd));
    const auto dpf(create_decoration_properties_factory(repository_, drp, ra));

    std::forward_list<formatters::artefact> r;
    for(const auto k : registrar().kernels()) {
        const auto kn(k->archetype_location().kernel());
        BOOST_LOG_SEV(lg, debug) << "Generating files for: " << kn;

        const auto& ek(cfg.enabled_kernels());
        const auto is_enabled(ek.find(kn) != ek.end());
        if (!is_enabled) {
            BOOST_LOG_SEV(lg, warn) << "Kernel is not enabled: " << kn;
            continue;
        }

        const auto& ko(knitting_options_);
        const bool ekd(cfg.enable_kernel_directories());
        auto files(k->generate(ko, atrp, af, drp, dpf, ekd, m));
        BOOST_LOG_SEV(lg, debug) << "Generated files for : " << kn
                                 << ". Total files: "
                                 << std::distance(files.begin(), files.end());
        r.splice_after(r.before_begin(), files);
    }
    return r;
}

} }
