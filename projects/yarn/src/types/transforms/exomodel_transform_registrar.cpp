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
#include <unordered_set>
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
const std::string id_already_registered(
    "Exomodel transform with this id has already been registered: ");
const std::string ext_already_registered(
    "Exomodel transform for this extension has already been registered: ");
const std::string null_transformer("Exomodel transform supplied is null.");

}

namespace dogen {
namespace yarn {
namespace transforms {

void exomodel_transform_registrar::validate() {
    /*
     * There must at least be one transformer.
     */
    if (exomodel_transforms_.empty()) {
        BOOST_LOG_SEV(lg, debug) << no_transforms;
        BOOST_THROW_EXCEPTION(registrar_error(no_transforms));
    }

    /*
     * A transformer with the same ID must not have already been
     * registered.
     */
    std::unordered_set<std::string> ids;
    for (const auto& pair : exomodel_transforms_) {
        const auto& et(*pair.second);
        const auto id(et.id());
        const auto inserted(ids.insert(id).second);

        if (!inserted) {
            BOOST_LOG_SEV(lg, error) << id_already_registered << id;
            BOOST_THROW_EXCEPTION(registrar_error(id_already_registered + id));
        }
    }

    BOOST_LOG_SEV(lg, debug) << "Registrar is in a valid state.";
    BOOST_LOG_SEV(lg, debug) << "Found "
                             << exomodel_transforms_.size()
                             << " registered exomodel transforms. Details: ";
}

void exomodel_transform_registrar::register_exomodel_transform(
    std::shared_ptr<exomodel_transform_interface> et) {
    BOOST_LOG_SEV(lg, debug) << "Registring exomodel transform: " << et->id();

    /*
     * Transform must not be null.
     */
    if (!et) {
        BOOST_LOG_SEV(lg, error) << null_transformer;
        BOOST_THROW_EXCEPTION(registrar_error(null_transformer));
    }

    /*
     * Register transform against all supported extensions.
     */

    for (const auto ext : et->supported_extensions()) {
        BOOST_LOG_SEV(lg, debug) << "Registering against extension: " << ext;

        const auto pair(std::make_pair(ext, et));
        const auto inserted(exomodel_transforms_.insert(pair).second);
        if (!inserted) {
            BOOST_LOG_SEV(lg, error) << ext_already_registered << ext;
            BOOST_THROW_EXCEPTION(
                registrar_error(ext_already_registered + ext));
        }
    }

    BOOST_LOG_SEV(lg, debug) << "Registrered exomodel transform.";
}

exomodel_transform_interface& exomodel_transform_registrar::
transform_for_model(const boost::filesystem::path& p) {
    const auto gs(p.generic_string());
    const auto ext(p.extension().generic_string());
    BOOST_LOG_SEV(lg, debug) << "Looking for exomodel transform for path: "
                             << gs << ". Extension: '" << ext << "'";

    const auto i(exomodel_transforms_.find(ext));
    if (i == exomodel_transforms_.end()) {
        BOOST_LOG_SEV(lg, error) << unsupported_model << gs;
        BOOST_THROW_EXCEPTION(registrar_error(unsupported_model + gs));
    }

    auto& r(*i->second);
    const auto& id(r.id());
    BOOST_LOG_SEV(lg, debug) << "Found transform: '" << id << "'";
    return r;
}

} } }
