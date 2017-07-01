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
#include "dogen/utility/io/list_io.hpp"
#include "dogen/utility/io/unordered_map_io.hpp"
#include "dogen/utility/filesystem/file.hpp"
#include "dogen/yarn/io/languages_io.hpp"
#include "dogen/yarn/io/descriptor_io.hpp"
#include "dogen/yarn/io/mapping_io.hpp"
#include "dogen/yarn/io/mapping_set_io.hpp"
#include "dogen/yarn/io/mapping_set_repository_io.hpp"
#include "dogen/yarn/types/mapper.hpp"
#include "dogen/yarn/types/mappings_hydrator.hpp"
#include "dogen/yarn/types/building_error.hpp"
#include "dogen/yarn/types/descriptor_factory.hpp"
#include "dogen/yarn/types/mapping_set_repository_factory.hpp"
#include "dogen/yarn/types/mappings_validator.hpp"
#include "dogen/yarn/types/first_stage_expander.hpp"
#include "dogen/yarn/types/intermediate_model_repository_factory.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("yarn.intermediate_model_repository_factory"));

const std::string expected_empty_repository(
    "Expected repository to be empty for language: ");
const std::string expected_target_model(
    "Expcted only the target model but found: ");
const std::string non_absolute_target("Target path is not absolute: ");
const std::string duplicate_mapping_set(
    "Found more than one mapping set with name: ");

const std::string mappings_dir("mappings");

}

namespace dogen {
namespace yarn {

std::unordered_map<std::string, std::list<mapping>>
intermediate_model_repository_factory::
obtain_mappings(const std::vector<boost::filesystem::path>& dirs) const {
    BOOST_LOG_SEV(lg, debug) << "Reading all mappings.";

    mappings_hydrator h;
    std::unordered_map<std::string, std::list<mapping>> r;
    for (const auto& top_level_dir : dirs) {
        const boost::filesystem::path mdir(top_level_dir / mappings_dir);
        BOOST_LOG_SEV(lg, trace) << "Mapping directory: "
                                 << mdir.generic_string();

        using namespace dogen::utility::filesystem;
        const auto files(find_files(mdir));

        BOOST_LOG_SEV(lg, trace) << "Found " << files.size()
                                 << " mapping files.";

        for (const auto& f : files) {
            BOOST_LOG_SEV(lg, trace) << "Mapping file: " << f.generic_string();

            const auto n(f.stem().string());
            const auto mappings(h.hydrate(f));
            const auto pair(std::make_pair(n, mappings));
            const auto inserted(r.insert(pair).second);
            if (!inserted) {
                BOOST_LOG_SEV(lg, error) << duplicate_mapping_set << n;
                BOOST_THROW_EXCEPTION(
                    building_error(duplicate_mapping_set + n));
            }
        }
    }

    BOOST_LOG_SEV(lg, debug) << "Read all mappings. Result: " << r;
    return r;
}

void intermediate_model_repository_factory::validate_mappings(
    const std::unordered_map<std::string, std::list<mapping>>& mappings) const {
    mappings_validator v;
    v.validate(mappings);
}

mapping_set_repository
intermediate_model_repository_factory::
obtain_mapping_set_repository(const std::unordered_map<std::string,
    std::list<mapping>>& mappings) const {
    BOOST_LOG_SEV(lg, debug) << "Obtaining mapping repository.";
    mapping_set_repository_factory f;
    const auto r(f.make(mappings));
    BOOST_LOG_SEV(lg, debug) << "Obtained mapping repository. Result: " << r;
    return r;
}

intermediate_model
intermediate_model_repository_factory::intermediate_model_for_descriptor(
    frontend_registrar& rg, const descriptor& d) const {

    BOOST_LOG_SEV(lg, debug) << "Reading intermediate model from descriptor. "
                             << "Descriptor: " << d;

    auto& fe(rg.frontend_for_path(d.path()));
    const auto r(fe.read(d));

    BOOST_LOG_SEV(lg, debug) << "Read intermediate model from descriptor.";
    return r;
}

void intermediate_model_repository_factory::
populate_target_model(const annotations::annotation_groups_factory& agf,
    const annotations::type_repository& atrp,
    const options::knitting_options& ko,
    frontend_registrar& rg, const mapping_set_repository& msrp,
    intermediate_model_repository& rp) const {
    BOOST_LOG_SEV(lg, debug) << "Populating target model.";

    /*
     * We require the target path supplied to us to be an absolute
     * path. This is because we perform calculations off of it such as
     * locating the reference models and so forth. The end-user is not
     * required to have supplied an absolute path, but someone above
     * us must be responsible for ensuring we receive an absolute
     * path.
     */
    if (!ko.target().is_absolute()) {
        const auto gs(ko.target().generic_string());
        BOOST_LOG_SEV(lg, error) << non_absolute_target << gs;
        BOOST_THROW_EXCEPTION(building_error(non_absolute_target + gs));
    }

    descriptor_factory f;
    const auto timd(f.make(ko.target()));
    auto tim(intermediate_model_for_descriptor(rg, timd));

    first_stage_expander ex;
    ex.expand_target(agf, atrp, tim);

    const mapper mp(msrp);
    for (const auto ol : tim.output_languages()) {
        /*
         * Obtain the model container for the language of the target
         * model, ensure its empty - as there can only be one target per
         * language - and push the target into it.
         */
        auto& list(rp.by_language()[ol]);
        if (!list.empty()) {
            const auto s(boost::lexical_cast<std::string>(ol));
            BOOST_LOG_SEV(lg, error) << expected_empty_repository << s;
            BOOST_THROW_EXCEPTION(
                building_error(expected_empty_repository + s));
        }

        list.push_back(mp.map(tim.input_language(), ol, tim));
    }
    BOOST_LOG_SEV(lg, debug) << "Populated target model.";
}

intermediate_model_repository intermediate_model_repository_factory::
make(const std::vector<boost::filesystem::path>& dirs,
    const annotations::annotation_groups_factory& agf,
    const annotations::type_repository& atrp,
    const options::knitting_options& ko,
    frontend_registrar& rg) const {

    BOOST_LOG_SEV(lg, debug) << "Creating the intermediate model repository.";

    /*
     * We start by obtaining the mapping repository because it will be
     * used by all intermediate models.
     */
    const auto mappings(obtain_mappings(dirs));
    validate_mappings(mappings);
    const auto msrp(obtain_mapping_set_repository(mappings));

    intermediate_model_repository r;
    /*
     * Next we need to obtain the target intermediate model and
     * post-process it. This is done because we need to access the
     * annotations inside this model in order to figure out what the
     * user reference intermediate models are. In addition we also
     * need to know what languages we will need to support.
     */
    populate_target_model(agf, atrp, ko, rg, msrp, r);

    /*
     * Now obtain all of the descriptors for the reference models,
     * using the annotations object and the data directories; then
     * load all reference intermediate models and post-process them.
     */
    descriptor_factory f;
    const mapper mp(msrp);
    first_stage_expander ex;
    const auto target_dir(ko.target().parent_path());
    for (auto& pair : r.by_language()) {
        const auto ol(pair.first);
        BOOST_LOG_SEV(lg, debug) << "Output language: " << ol;

        /*
         * First we need to get our hands on the target model for this
         * language. We can only have one target model.
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
            if (ex.try_expand_reference(agf, atrp, ol, rim))
                list.push_back(mp.map(rim.input_language(), ol, rim));
        }
    }

    BOOST_LOG_SEV(lg, debug) << "Created the intermediate model repository.";
    return r;
}

} }
