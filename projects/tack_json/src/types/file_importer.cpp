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
#include "dogen/tack_json/types/hydrator.hpp"
#include "dogen/tack_json/types/file_importer.hpp"

using namespace dogen::utility::log;

namespace {

const std::string id("tack_json.file_importer");
const std::list<std::string> extensions({ ".json" });
auto lg(logger_factory(id));
const std::string empty;

}

namespace dogen {
namespace tack_json {

file_importer::~file_importer() noexcept { }

std::string file_importer::id() const {
    return ::id;
}

std::list<std::string> file_importer::supported_extensions() const {
    return ::extensions;
}

tack::model file_importer::import(const dynamic::workflow& w,
    const tack::input_descriptor& d) {
    tack_json::hydrator h(w);
    return h.hydrate(d.path());
}

} }
