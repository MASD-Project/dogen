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
#include "dogen/annotations/io/type_io.hpp"
#include "dogen/annotations/types/entry_selector.hpp"
#include "dogen/annotations/types/type_repository_selector.hpp"
#include "dogen/quilt/types/traits.hpp"
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

std::ostream&
operator<<(std::ostream& s, const workflow::type_group& v) {
    s << " { "
      << "\"__type__\": " << "\"dogen::quilt::workflow::type_group\"" << ", "
      << "\"requires_manual_default_constructor\": "
      << v.enabled
      << " }";

    return s;
}

std::shared_ptr<backend_registrar> workflow::registrar_;

std::list<workflow::type_group>
workflow::make_type_groups(const annotations::type_repository& atrp) const {
    std::list<type_group> r;

    const auto en(traits::enabled());
    const annotations::type_repository_selector rs(atrp);
    for (const auto b : registrar().backends()) {
        type_group tg;
        const auto kernel(b->archetype_location().kernel());
        tg.enabled = rs.select_type_by_name(kernel, en);
        r.push_back(tg);
    }

    return r;
}

std::unordered_set<std::string>
workflow::obtain_enabled_backends(const std::list<type_group>& tgs,
    const annotations::annotation& ra) const {

    std::unordered_set<std::string> r;
    const annotations::entry_selector s(ra);
    for (const auto& tg : tgs) {
        const bool enabled(s.get_boolean_content_or_default(tg.enabled));
        if (!enabled)
            continue;

        r.insert(tg.enabled.archetype_location().kernel());
    }

    return r;
}

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
        // not splicing due to a mistmatch in the list types
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
        // not splicing due to a mistmatch in the list types
        const auto md(b->managed_directories(ko, m.name()));
        for (const auto& d : md)
            r.push_front(d);
    }
    return r;
}

std::forward_list<formatters::artefact>
workflow::execute(const yarn::model& m) const {

    const auto tgs(make_type_groups(repository_));
    const auto ra(m.root_module().annotation());
    const auto eb(obtain_enabled_backends(tgs, ra));


    std::forward_list<formatters::artefact> r;
    for(const auto b : registrar().backends()) {
        const auto kernel(b->archetype_location().kernel());
        BOOST_LOG_SEV(lg, debug) << "Generating files for: " << kernel;

        const auto is_enabled(eb.find(kernel) != eb.end());
        if (!is_enabled) {
            BOOST_LOG_SEV(lg, warn) << "Backend is not enabled: " << kernel;
            return r;
        }

        const auto& ko(knitting_options_);
        auto files(b->generate(ko, repository_, annotation_factory_, m));
        BOOST_LOG_SEV(lg, debug) << "Generated files for : " << kernel
                                 << ". Total files: "
                                 << std::distance(files.begin(), files.end());
        r.splice_after(r.before_begin(), files);
    }
    return r;
}

} }
