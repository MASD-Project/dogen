/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda <info@kitanda.co.uk>
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
#include "dogen/tack/types/registrar_error.hpp"
#include "dogen/tack/types/file_importer_registrar.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("tack.file_importer_registrar"));

const std::string exension_registerd_more_than_once(
    "Extension was registered more than once");
const std::string no_importers("No file importers provided.");
const std::string extension_unsupported(
    "No file importer is available for extension:");
const std::string already_registered("Extension has already been registered: ");

const std::string null_importer("File importer supplied is null");

}

namespace dogen {
namespace tack {

const std::unordered_map<std::string,
                         std::shared_ptr<file_importer_interface>>&
file_importer_registrar::file_importers_by_extension() const {
    return file_importers_by_extension_;
}

void file_importer_registrar::validate() const {
    if (file_importers_by_extension_.empty()) {
        BOOST_LOG_SEV(lg, debug) << no_importers;
        BOOST_THROW_EXCEPTION(registrar_error(no_importers));
    }
    BOOST_LOG_SEV(lg, debug) << "Registrar is in a valid state.";
}

void file_importer_registrar::
register_file_importer_for_extension(const std::string& extension,
    std::shared_ptr<file_importer_interface> fi) {

    // note: not logging by design
    if (!fi)
        BOOST_THROW_EXCEPTION(registrar_error(null_importer));

    auto& c(file_importers_by_extension_);
    const auto i(c.insert(std::make_pair(extension, fi)));
    if (!i.second)
        BOOST_THROW_EXCEPTION(registrar_error(already_registered + extension));
}

file_importer_interface& file_importer_registrar::
file_importer_for_extension(const std::string& extension) {
    BOOST_LOG_SEV(lg, debug) << "Looking for file importer for extension: "
                             << extension;

    auto& c(file_importers_by_extension_);
    const auto i(c.find(extension));
    if (i != c.end()) {
        BOOST_LOG_SEV(lg, debug) << "Found file importer for extension. "
                                 << "Extension: " << extension
                                 << "' file importer: '" << i->second->id()
                                 << "'";
        return *i->second;
    }
    BOOST_LOG_SEV(lg, error) << extension_unsupported  << extension;
    BOOST_THROW_EXCEPTION(registrar_error(extension_unsupported + extension));
}

} }
