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
#include <boost/lexical_cast.hpp>
#include <boost/throw_exception.hpp>
#include "dogen/utility/log/logger.hpp"
#include "dogen/yarn/io/languages_io.hpp"
#include "dogen/yarn/io/descriptor_io.hpp"
#include "dogen/yarn/types/building_error.hpp"
#include "dogen/yarn/types/descriptor_factory.hpp"
#include "dogen/yarn/types/intermediate_model_expander.hpp"
#include "dogen/yarn/types/intermediate_model_repository_factory.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("yarn.intermediate_model_repository_factory"));

const std::string expected_empty_repository(
    "Expected repository to be empty for language: ");
const std::string expected_target_model("Expcted only the target model but found: ");

}

namespace dogen {
namespace yarn {

intermediate_model
intermediate_model_repository_factory::intermediate_model_for_descriptor(
    frontend_registrar& rg, const descriptor& d) const {

    BOOST_LOG_SEV(lg, debug) << "Reading intermediate model from descriptor. "
                             << "Descriptor: " << d;

    auto& fe(rg.frontend_for_path(d.path()));
    auto r(fe.read(d));

    BOOST_LOG_SEV(lg, debug) << "Read intermediate model from descriptor.";
    return r;
}

void intermediate_model_repository_factory::
populate_target_model(const annotations::annotation_groups_factory& agf,
    const annotations::type_repository& atrp,
    const options::knitting_options& ko, frontend_registrar& rg,
    intermediate_model_repository& rp) const {
    BOOST_LOG_SEV(lg, error) << "Populating target model.";

    descriptor_factory f;
    const auto timd(f.make(ko.target()));
    auto tim(intermediate_model_for_descriptor(rg, timd));

    intermediate_model_expander ex;
    ex.expand(agf, atrp, tim);

    /*
     * Obtain the model container for the language of the target
     * model, ensure its empty - as there can only be one target per
     * language - and push the target into it.
     */
    const auto l(tim.input_language());
    auto& list(rp.by_language()[l]);
    if (!list.empty()) {
        BOOST_LOG_SEV(lg, error) << expected_empty_repository << l;
        BOOST_THROW_EXCEPTION(building_error(expected_empty_repository +
                boost::lexical_cast<std::string>(l)));
    }

    list.push_back(tim);
    BOOST_LOG_SEV(lg, error) << "Populated target model.";
}

intermediate_model_repository intermediate_model_repository_factory::
make(const std::vector<boost::filesystem::path>& dirs,
    const annotations::annotation_groups_factory& agf,
    const annotations::type_repository& atrp,
    const options::knitting_options& ko,
    frontend_registrar& rg) const {

    BOOST_LOG_SEV(lg, debug) << "Creating the intermediate model repository.";

    intermediate_model_repository r;
    /*
     * We need to first obtain the target intermediate model and
     * post-process it. This is done because we need to access the
     * annotations inside this model in order to figure out what the
     * user reference intermediate models are. In addition we also
     * need to know what languages we will need to support.
     */
    populate_target_model(agf, atrp, ko, rg, r);

    /*
     * Now obtain all of the descriptors for the reference models,
     * using the annotations object and the data directories; then
     * load all reference intermediate models and post-process them.
     */
    descriptor_factory f;
    intermediate_model_expander ex;
    const auto target_dir(ko.target().parent_path());
    for (auto& pair : r.by_language()) {
        const auto tl(pair.first);
        BOOST_LOG_SEV(lg, debug) << "Target model language: " << tl;

        /*
         * First we need to get our hands on the target model for this
         * language.
         */
        auto& list(pair.second);
        if (list.size() != 1) {
            BOOST_LOG_SEV(lg, error) << expected_target_model << list.size();
            BOOST_THROW_EXCEPTION(building_error(expected_target_model +
                    boost::lexical_cast<std::string>(list.size())));
        }

        const auto& tim(list.front());
        const auto& ra(tim.root_module().annotation());
        const auto rimd(f.make(dirs, target_dir, atrp, ra));

        /*
         * Now we need to load and filter all of the reference
         * intermediate models; we only want those which are
         * compatible with the language of the target model.
         */
        for (const auto& d : rimd) {
            auto rim(intermediate_model_for_descriptor(rg, d));
            if (ex.expand_if_compatible(agf, atrp, tl, rim))
                list.push_back(rim);
        }
    }

    BOOST_LOG_SEV(lg, debug) << "Created the intermediate model repository.";
    return r;
}

} }
