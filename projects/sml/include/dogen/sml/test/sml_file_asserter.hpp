/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda
 *
 * This file is distributed under the Kitanda Proprietary Software
 * Licence. See doc/LICENCE.TXT for details.
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
