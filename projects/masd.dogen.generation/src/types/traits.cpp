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
#include "masd.dogen.generation/types/traits.hpp"

namespace masd::dogen::generation {

std::string traits::enabled() {
    static std::string r("enabled");
    return r;
}

std::string traits::directory() {
    static std::string r("directory");
    return r;
}

std::string traits::postfix() {
    static std::string r("postfix");
    return r;
}

std::string traits::supported() {
    static std::string r("supported");
    return r;
}

std::string traits::overwrite() {
    static std::string r("overwrite");
    return r;
}

std::string traits::input_language() {
    static std::string r("yarn.input_language");
    return r;
}

std::string traits::output_language() {
    static std::string r("yarn.output_language");
    return r;
}

std::string traits::is_proxy_model() {
    static std::string r("yarn.is_proxy_model");
    return r;
}

std::string traits::reference() {
    static std::string r("yarn.reference");
    return r;
}

std::string traits::external_modules() {
    static std::string r("yarn.external_modules");
    return r;
}

std::string traits::model_modules() {
    static std::string r("yarn.model_modules");
    return r;
}

std::string traits::enable_backend_directories() {
    // FIXME: rename to yarn
    static std::string r("quilt.enable_backend_directories");
    return r;
}

std::string traits::force_backend_directory() {
    static std::string r("yarn.force_backend_directory");
    return r;
}

}
