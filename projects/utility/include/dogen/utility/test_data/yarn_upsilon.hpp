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
#ifndef DOGEN_UTILITY_TEST_DATA_YARN_UPSILON_HPP
#define DOGEN_UTILITY_TEST_DATA_YARN_UPSILON_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <boost/filesystem/path.hpp>

namespace dogen {
namespace utility {
namespace test_data {

class yarn_upsilon {
public:
    yarn_upsilon() = delete;
    yarn_upsilon(const yarn_upsilon&) = delete;
    ~yarn_upsilon() = delete;
    yarn_upsilon(yarn_upsilon&&) = delete;
    yarn_upsilon& operator=(const yarn_upsilon&) = delete;

public:
    static boost::filesystem::path data_set();

    static boost::filesystem::path input();
    static boost::filesystem::path input_phi_model_xml();
    static boost::filesystem::path input_phi_model_xml_typeinfos();
    static boost::filesystem::path input_test_model_configuration_xml();
    static boost::filesystem::path input_dodgy_model_configuration_xml();
    static boost::filesystem::path input_zeta_model_xml();
    static boost::filesystem::path input_zeta_model_xml_typeinfos();

    static boost::filesystem::path expected();
    static boost::filesystem::path expected_test_model_upsilon_xml();
    static boost::filesystem::path expected_test_model_yarn_xml();

    static boost::filesystem::path actual();
    static boost::filesystem::path actual_test_model_upsilon_xml();
    static boost::filesystem::path actual_test_model_yarn_xml();
};

} } }

#endif
