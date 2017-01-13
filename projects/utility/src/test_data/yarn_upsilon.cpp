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
#include "dogen/utility/test_data/resolver.hpp"
#include "dogen/utility/test_data/validating_resolver.hpp"
#include "dogen/utility/test_data/yarn_upsilon.hpp"

using boost::filesystem::path;

namespace {

path data_set("yarn.upsilon");
path input("yarn.upsilon/input");

path input_phi_model_xml("yarn.upsilon/input/Phi.Model.xml");
path input_phi_model_xml_typeinfos(
    "yarn.upsilon/input/Phi.Model.xml.typeinfos");
path input_test_model_configuration_xml(
    "yarn.upsilon/input/Test.Model.Configuration.xml");
path input_dodgy_model_configuration_xml(
    "yarn.upsilon/input/Dodgy.Model.Configuration.xml");
path input_zeta_model_xml("yarn.upsilon/input/Zeta.Model.xml");
path input_zeta_model_xml_typeinfos(
    "yarn.upsilon/input/Zeta.Model.xml.typeinfos");

path expected("yarn.upsilon/expected");
path actual("yarn.upsilon/actual");

}

namespace dogen {
namespace utility {
namespace test_data {

path yarn_upsilon::data_set() {
    return validating_resolver::resolve(::data_set);
}

path yarn_upsilon::input() {
    return validating_resolver::resolve(::input);
}

path yarn_upsilon::input_phi_model_xml() {
    return validating_resolver::resolve(::input_phi_model_xml);
}

path yarn_upsilon::input_phi_model_xml_typeinfos() {
    return validating_resolver::resolve(::input_phi_model_xml_typeinfos);
}

path yarn_upsilon::input_test_model_configuration_xml() {
    return validating_resolver::resolve(::input_test_model_configuration_xml);
}

path yarn_upsilon::input_dodgy_model_configuration_xml() {
    return validating_resolver::resolve(::input_dodgy_model_configuration_xml);
}

path yarn_upsilon::input_zeta_model_xml() {
    return validating_resolver::resolve(::input_zeta_model_xml);
}

path yarn_upsilon::input_zeta_model_xml_typeinfos() {
    return validating_resolver::resolve(::input_zeta_model_xml_typeinfos);
}

path yarn_upsilon::expected() {
    return validating_resolver::resolve(::expected);
}

path yarn_upsilon::actual() {
    return validating_resolver::resolve(::actual);
}

} } }
