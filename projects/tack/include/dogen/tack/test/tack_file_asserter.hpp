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
#ifndef DOGEN_TACK_TEST_TACK_FILE_ASSERTER_HPP
#define DOGEN_TACK_TEST_TACK_FILE_ASSERTER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include "dogen/tack/types/model.hpp"
#include "dogen/utility/test/file_asserter.hpp"

namespace dogen {
namespace tack {
namespace test {

class tack_file_asserter : public utility::test::file_asserter {
public:
    tack_file_asserter() = default;
    tack_file_asserter(const tack_file_asserter&) = default;
    tack_file_asserter(tack_file_asserter&&) = default;
    tack_file_asserter& operator=(const tack_file_asserter&) = default;

public:
    virtual ~tack_file_asserter() noexcept {}

private:
    tack::model read_xml(boost::filesystem::path path) const;

public:
    virtual bool is_assertable(boost::filesystem::path path) const override;
    virtual bool assert_file(boost::filesystem::path expected,
        boost::filesystem::path actual) const override;
};

} } }

#endif
