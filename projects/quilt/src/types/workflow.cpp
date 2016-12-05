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

std::shared_ptr<backend_registrar> workflow::registrar_;

workflow::workflow(const options::knitting_options& o,
    const annotations::type_repository& atrp,
    const annotations::annotation_groups_factory& agf)
    : knitting_options_(o), repository_(atrp), annotation_factory_(agf) {}

backend_registrar& workflow::registrar() {
    if (!registrar_)
        registrar_ = std::make_shared<backend_registrar>();

    return *registrar_;
}

std::list<annotations::archetype_location> workflow::archetype_locations() {
    std::list<annotations::archetype_location> r;
    const auto& rg(quilt::workflow::registrar());
    for (const auto b : rg.backends()) {
        // Note: not splicing due to a mistmatch in the list types
        // (forward list vs regular list.)
        for (const auto al : b->archetype_locations())
            r.push_back(al);
    }
    return r;
}

std::forward_list<boost::filesystem::path>
workflow::managed_directories(const yarn::model& m) const {
    const auto& ko(knitting_options_);
    std::forward_list<boost::filesystem::path> r;
    for(const auto b : registrar().backends()) {
        const auto md(b->managed_directories(ko, m.name()));
        for (const auto& d : md)
            r.push_front(d);
    }
    return r;
}

std::forward_list<formatters::artefact>
workflow::execute(const yarn::model& m) const {
    std::forward_list<formatters::artefact> r;
    for(const auto b : registrar().backends()) {
        const auto n(b->name());
        BOOST_LOG_SEV(lg, debug) << "Generating files for: '" << n << "'";
        const auto& ko(knitting_options_);
        auto files(b->generate(ko, repository_, annotation_factory_, m));
        BOOST_LOG_SEV(lg, debug) << "Generated files for : '" << n
                                 << "'. Total files: "
                                 << std::distance(files.begin(), files.end());
        r.splice_after(r.before_begin(), files);
    }
    return r;
}

} }
