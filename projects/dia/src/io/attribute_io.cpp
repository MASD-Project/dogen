/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda
 *
 * This file is distributed under the Kitanda Proprietary Software
 * Licence. See doc/LICENCE.TXT for details.
 *
 */
#include <ostream>
#include <boost/variant/apply_visitor.hpp>
#include "dogen/utility/io/vector_io.hpp"
#include "dogen/dia/io/color_io.hpp"
#include "dogen/dia/io/point_io.hpp"
#include "dogen/dia/io/real_io.hpp"
#include "dogen/dia/io/integer_io.hpp"
#include "dogen/dia/io/boolean_io.hpp"
#include "dogen/dia/io/string_io.hpp"
#include "dogen/dia/io/composite_io.hpp"
#include "dogen/dia/io/attribute_io.hpp"
#include "dogen/dia/io/rectangle_io.hpp"
#include "dogen/dia/io/font_io.hpp"
#include "dogen/dia/io/enumeration_io.hpp"

namespace {

/**
 * @brief Writes all possible attribute value types into the stream.
 */
class attribute_value_visitor : public boost::static_visitor<> {
public:
    attribute_value_visitor(std::ostream& stream) : stream_(stream) {}

public:
    void operator()(const dogen::dia::color& value) const {
        stream_ << value;
    }

    void operator()(const dogen::dia::point& value) const {
        stream_ << value;
    }

    void operator()(const dogen::dia::real& value) const {
        stream_ << value;
    }

    void operator()(const dogen::dia::integer& value) const {
        stream_ << value;
    }

    void operator()(const dogen::dia::boolean& value) const {
        stream_ << value;
    }

    void operator()(const dogen::dia::string& value) const {
        stream_ << value;
    }

    void operator()(const dogen::dia::rectangle& value) const {
        stream_ << value;
    }

    void operator()(const dogen::dia::font& value) const {
        stream_ << value;
    }

    void operator()(const dogen::dia::enumeration& value) const {
        stream_ << value;
    }

    void operator()(const std::vector<dogen::dia::composite>& value) const {
        stream_ << "\"values\":" << value;
    }

    void operator()(const dogen::dia::empty&) const {
        stream_ << " \"value\": \"empty\"";
    }

private:
    std::ostream& stream_;
};
}

namespace dogen {
namespace dia {

std::ostream&
operator<<(std::ostream& stream, dogen::dia::attribute attribute) {
    stream << "\"attribute\": {"
           << " \"name\": \"" << attribute.name() << "\",";

    // we need to create a local variable here because the visitor
    // uses a non-const reference to the value and we cannot have
    // non-const references to temporaries.
    dogen::dia::attribute::attribute_value value(attribute.value());
    boost::apply_visitor(attribute_value_visitor(stream), value);

    stream << " }";
    return(stream);
}

} }
