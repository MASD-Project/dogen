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
#include "dogen.dia/serialization/diagram_ser.hpp"
#include "dogen/utility/serialization/xml_helper.hpp"
#include "dogen.dia/types/persister_error.hpp"
#include "dogen.dia/types/persister.hpp"

using namespace dogen::utility::log;

namespace {

auto lg(logger_factory("dia.persister"));

const std::string empty;
const std::string dia_xml_extension(".xml");
const std::string unsupported_extension("Extension is not supported: ");

}

namespace dogen {
namespace dia {

void persister::
persist(const dia::diagram& d, const boost::filesystem::path& p) const {
    const std::string extension(p.extension().string());
    if (extension != dia_xml_extension) {
        BOOST_LOG_SEV(lg, error) << unsupported_extension << extension;
        BOOST_THROW_EXCEPTION(
            persister_error(unsupported_extension + extension));
    }

    using dogen::utility::serialization::xml_serialize;
    xml_serialize<diagram>(p, d);
}

} }
