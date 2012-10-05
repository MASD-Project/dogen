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
 * You should have received a copy of the GNU General PublicLicense
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 *
 */
#ifndef DOGEN_SML_TEST_SML_FILE_ASSERTER_HPP
#define DOGEN_SML_TEST_SML_FILE_ASSERTER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include "dogen/sml/domain/model.hpp"
#include "dogen/utility/test/file_asserter.hpp"

namespace dogen {
namespace sml {
namespace test {

class sml_file_asserter : public utility::test::file_asserter {
public:
    sml_file_asserter() = default;
    sml_file_asserter(const sml_file_asserter&) = default;
    sml_file_asserter(sml_file_asserter&&) = default;
    sml_file_asserter& operator=(const sml_file_asserter&) = default;

public:
    virtual ~sml_file_asserter() noexcept {}

private:
    sml::model read_xml(boost::filesystem::path path) const;

public:
    virtual bool is_assertable(boost::filesystem::path path) const override;
    virtual bool assert_file(boost::filesystem::path expected,
        boost::filesystem::path actual) const override;
};

} } }

#endif
