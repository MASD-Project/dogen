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
#include "dogen/yarn/types/transforms/exomodel_transform_registrar.hpp"

namespace {

using namespace dogen::utility::log;
static logger
lg(logger_factory("yarn.transforms.exomodel_transform_registrar"));

const std::string no_transforms("No exomodel transforms provided.");
const std::string multiple_transforms(
    "More than one exomodel transform available for model: ");
const std::string unsupported_model(
    "No exomodel transform is available for model: ");
const std::string already_registered(
    "Exomodel transform has already been registered: ");
const std::string null_transformer("Exomodel transform supplied is null.");

}

namespace dogen {
namespace yarn {
namespace transforms {

void exomodel_transform_registrar::validate() {
    if (exomodel_transforms_.empty()) {
        BOOST_LOG_SEV(lg, debug) << no_transforms;
        BOOST_THROW_EXCEPTION(registrar_error(no_transforms));
    }

    BOOST_LOG_SEV(lg, debug) << "Registrar is in a valid state.";

    BOOST_LOG_SEV(lg, debug) << "Found "
                             << exomodel_transforms_.size()
                             << " registered exomodel transforms. Details: ";

    for (const auto& pair : exomodel_transforms_) {
        const auto& et(*pair.second);
        BOOST_LOG_SEV(lg, debug) << "id: '" << et.id() << "'";
    }
}

void exomodel_transform_registrar::register_exomodel_transform(
    std::shared_ptr<exomodel_transform_interface> et) {
    /*
     * Transformer must not be null.
     */
    if (!et) {
        BOOST_LOG_SEV(lg, error) << null_transformer;
        BOOST_THROW_EXCEPTION(registrar_error(null_transformer));
    }

    /*
     * A transformer with the same ID must not have already been
     * registered.
     */
    const auto i(exomodel_transforms_.insert(std::make_pair(et->id(), et)));
    if (!i.second) {
        BOOST_LOG_SEV(lg, error) << already_registered << et->id();
        BOOST_THROW_EXCEPTION(registrar_error(already_registered + et->id()));
    }

    BOOST_LOG_SEV(lg, debug) << "Registrered exomodel transform: "
                             << et->id();
}

exomodel_transform_interface& exomodel_transform_registrar::
transform_for_model(const std::string& model_identifier) {
    const auto& mid(model_identifier);
    BOOST_LOG_SEV(lg, debug) << "Looking for exomodel transform for model: "
                             << mid << ".";

    /*
     * We must do a linear search for the transform because the match
     * with the model identifier is not always obvious - e.g. not just
     * an extension, etc. However, since there are very few
     * transforms, this is not a huge problem for now.
     */
    bool found(false);
    std::shared_ptr<exomodel_transform_interface> r;
    for (const auto& pair : exomodel_transforms_) {
        const auto& et(pair.second);

        if (!et->can_transform(mid))
            continue;

        const auto& id(pair.first);
        BOOST_LOG_SEV(lg, debug) << "Found transform: '" << id << "'";

        if (found) {
            BOOST_LOG_SEV(lg, error) << multiple_transforms << mid
                                     << " Transformer: '" << id << "'";
            BOOST_THROW_EXCEPTION(registrar_error(multiple_transforms + mid));
        }
        found = true;
        r = pair.second;
    }

    if (found)
        return *r;

    BOOST_LOG_SEV(lg, error) << unsupported_model << mid;
    BOOST_THROW_EXCEPTION(registrar_error(unsupported_model + mid));
}

} } }
