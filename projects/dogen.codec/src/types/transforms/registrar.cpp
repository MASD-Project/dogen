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
#include "dogen.utility/types/log/logger.hpp"
#include "dogen.codec/types/transforms/registrar_error.hpp"
#include "dogen.codec/types/transforms/registrar.hpp"

namespace {

using namespace dogen::utility::log;
static logger
lg(logger_factory("codec.transforms.registrar"));

const std::string empty_extension("Extension cannot be empty.");
const std::string no_encoding_transforms("No encoding transforms provided.");
const std::string no_decoding_transforms("No decoding transforms provided.");
const std::string unsupported_extension(
    "No transform is available for extension: ");
const std::string extension_already_registered(
    "A transform with this id has already been registered: ");
const std::string null_transform("Transform supplied is null.");

}

namespace dogen::codec::transforms {

void registrar::validate_extension(const std::string& ext) const {
    if (ext.empty()) {
        BOOST_LOG_SEV(lg, debug) << empty_extension;
        BOOST_THROW_EXCEPTION(registrar_error(empty_extension));
    }
}

void registrar::validate() {
    /*
     * There must at least be one encoding transform.
     */
    if (encoding_transforms_.empty()) {
        BOOST_LOG_SEV(lg, debug) << no_encoding_transforms;
        BOOST_THROW_EXCEPTION(registrar_error(no_encoding_transforms));
    }

    /*
     * There must at least be one decoding transform.
     */
    if (encoding_transforms_.empty()) {
        BOOST_LOG_SEV(lg, debug) << no_decoding_transforms;
        BOOST_THROW_EXCEPTION(registrar_error(no_decoding_transforms));
    }

    BOOST_LOG_SEV(lg, debug) << "Registrar is in a valid state."
                             << " Encoding transforms found: "
                             << encoding_transforms_.size()
                             << " Decoding transforms found: "
                             << decoding_transforms_.size();
}

std::list<std::string> registrar::registered_encoding_extensions() const {
    std::list<std::string> r;
    for (const auto& p : encoding_transforms_)
        r.push_back(p.first);
    return r;
}

std::list<std::string> registrar::registered_decoding_extensions() const {
    std::list<std::string> r;
    for (const auto& p : decoding_transforms_)
        r.push_back(p.first);
    return r;
}

void registrar::
register_encoding_transform(std::shared_ptr<encoding_transform> t) {
    BOOST_LOG_SEV(lg, debug) << "Registering encoding transform.";

    /*
     * Transform must not be null.
     */
    if (!t) {
        BOOST_LOG_SEV(lg, error) << null_transform;
        BOOST_THROW_EXCEPTION(registrar_error(null_transform));
    }

    /*
     * Extension must not be empty.
     */
    const auto& e(t->extension());
    if (e.empty()) {
        BOOST_LOG_SEV(lg, debug) << empty_extension;
        BOOST_THROW_EXCEPTION(registrar_error(empty_extension));
    }

    /*
     * Extension must not yet be taken.
     */
    BOOST_LOG_SEV(lg, debug) << "Registering against extension: " << e;
    const auto pair(std::make_pair(e, t));
    const auto inserted(encoding_transforms_.insert(pair).second);
    if (inserted)
        return;

    BOOST_LOG_SEV(lg, error) << extension_already_registered << e;
    BOOST_THROW_EXCEPTION(registrar_error(extension_already_registered + e));
    BOOST_LOG_SEV(lg, debug) << "Registrered encoding transform.";
}

void registrar::
register_decoding_transform(std::shared_ptr<decoding_transform> t) {
    BOOST_LOG_SEV(lg, debug) << "Registering decoding transform.";

    /*
     * Transform must not be null.
     */
    if (!t) {
        BOOST_LOG_SEV(lg, error) << null_transform;
        BOOST_THROW_EXCEPTION(registrar_error(null_transform));
    }

    /*
     * Extension must not be empty.
     */
    const auto& e(t->extension());
    if (e.empty()) {
        BOOST_LOG_SEV(lg, debug) << empty_extension;
        BOOST_THROW_EXCEPTION(registrar_error(empty_extension));
    }

    /*
     * Extension must not yet be taken.
     */
    BOOST_LOG_SEV(lg, debug) << "Registering against extension: " << e;
    const auto pair(std::make_pair(e, t));
    const auto inserted(decoding_transforms_.insert(pair).second);
    if (inserted)
        return;

    BOOST_LOG_SEV(lg, error) << extension_already_registered << e;
    BOOST_THROW_EXCEPTION(registrar_error(extension_already_registered + e));
    BOOST_LOG_SEV(lg, debug) << "Registrered encoding transform.";
}

encoding_transform&
registrar::encoding_transform_for_extension(const std::string& ext) {
    validate_extension(ext);
    BOOST_LOG_SEV(lg, debug) << "Looking for encoding transform for extension: "
                             << ext;

    const auto i(encoding_transforms_.find(ext));
    if (i == encoding_transforms_.end()) {
        BOOST_LOG_SEV(lg, error) << unsupported_extension << ext;
        BOOST_THROW_EXCEPTION(registrar_error(unsupported_extension + ext));
    }

    auto& r(*i->second);
    BOOST_LOG_SEV(lg, debug) << "Found transform for extension.";
    return r;
}

decoding_transform&
registrar::decoding_transform_for_extension(const std::string& ext) {
    validate_extension(ext);
    BOOST_LOG_SEV(lg, debug) << "Looking for decoding transform for extension: "
                             << ext;

    const auto i(decoding_transforms_.find(ext));
    if (i == decoding_transforms_.end()) {
        BOOST_LOG_SEV(lg, error) << unsupported_extension << ext;
        BOOST_THROW_EXCEPTION(registrar_error(unsupported_extension + ext));
    }

    auto& r(*i->second);
    BOOST_LOG_SEV(lg, debug) << "Found transform for extension.";
    return r;
}

encoding_transform&
registrar::encoding_transform_for_path(const boost::filesystem::path& p) {
    const auto gs(p.generic_string());
    const auto ext(p.extension().generic_string());
    BOOST_LOG_SEV(lg, debug) << "Looking for an encoding transform for path: "
                             << gs << ". Extension: '" << ext << "'";

    return encoding_transform_for_extension(ext);
}

decoding_transform&
registrar::decoding_transform_for_path(const boost::filesystem::path& p) {
    const auto gs(p.generic_string());
    const auto ext(p.extension().generic_string());
    BOOST_LOG_SEV(lg, debug) << "Looking for an decoding transform for path: "
                             << gs << ". Extension: '" << ext << "'";

    return decoding_transform_for_extension(ext);
}

}
