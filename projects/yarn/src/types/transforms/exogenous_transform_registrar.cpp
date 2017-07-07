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
#include "dogen/utility/log/logger.hpp"
#include "dogen/yarn/types/transforms/registrar_error.hpp"
#include "dogen/yarn/types/transforms/exogenous_transform_registrar.hpp"

namespace {

using namespace dogen::utility::log;
static logger
lg(logger_factory("yarn.transforms.exogenous_transform_registrar"));

const std::string no_transforms("No exogenous transforms provided.");
const std::string multiple_transforms(
    "More than one exognerous transform available for model: ");
const std::string unsupported_model(
    "No exogenous transformer is available for model: ");
const std::string already_registered(
    "Exogenous transformer has already been registered: ");
const std::string null_transformer("Exogenous transformer supplied is null.");

}

namespace dogen {
namespace yarn {
namespace transforms {

void exogenous_transform_registrar::validate() {
    if (exogenous_transforms_.empty()) {
        BOOST_LOG_SEV(lg, debug) << no_transforms;
        BOOST_THROW_EXCEPTION(registrar_error(no_transforms));
    }

    BOOST_LOG_SEV(lg, debug) << "Registrar is in a valid state.";

    BOOST_LOG_SEV(lg, debug) << "Found "
                             << exogenous_transforms_.size()
                             << " registered exogenous transforms. Details: ";

    for (const auto& pair : exogenous_transforms_) {
        const auto& et(*pair.second);
        BOOST_LOG_SEV(lg, debug) << "id: '" << et.id() << "'";
    }
}

void exogenous_transform_registrar::register_exogenous_transform(
    std::shared_ptr<exogenous_transform_interface> et) {

    /*
     * Note: not logging by design as this method is intended to be
     * called before the log has been initialised.
     */

    /*
     * Transformer must not be null.
     */
    if (!et)
        BOOST_THROW_EXCEPTION(registrar_error(null_transformer));

    /*
     * A transformer with the same ID must not have already been
     * registered.
     */
    const auto i(exogenous_transforms_.insert(std::make_pair(et->id(), et)));
    if (!i.second)
        BOOST_THROW_EXCEPTION(registrar_error(already_registered + et->id()));
}

exogenous_transform_interface& exogenous_transform_registrar::
transform_for_model(const std::string& model_identifier) {
    BOOST_LOG_SEV(lg, debug) << "Looking for exogenous transformer for model: "
                             << model_identifier << ".";

    /*
     * We must do a linear search for the transform because the match
     * with the model identifier is not always obvious - e.g. not just
     * an extension, etc. However, since there are very few
     * transforms, this is not a huge problem for now.
     */
    bool found(false);
    std::shared_ptr<exogenous_transform_interface> r;
    for (const auto& pair : exogenous_transforms_) {
        const auto& et(pair.second);

        if (!et->can_transform(model_identifier))
            continue;

        const auto& id(pair.first);
        BOOST_LOG_SEV(lg, debug) << "Found transform: '" << id << "'";

        if (found) {
            BOOST_LOG_SEV(lg, error) << multiple_transforms << model_identifier
                                     << " Transformer: '" << id << "'";
            BOOST_THROW_EXCEPTION(
                registrar_error(multiple_transforms + model_identifier));
        }
        found = true;
        r = pair.second;
    }

    if (found)
        return *r;

    BOOST_LOG_SEV(lg, error) << unsupported_model << model_identifier;
    BOOST_THROW_EXCEPTION(
        registrar_error(unsupported_model + model_identifier));
}

} } }
