#include <boost/throw_exception.hpp>
#include <boost/lexical_cast.hpp>
#include "dogen/utility/log/logger.hpp"
#include "dogen/sml/types/meta_data/read_write_error.hpp"
#include "dogen/sml/types/tags.hpp"
#include "dogen/sml/types/meta_data/writer.hpp"

using namespace dogen::utility::log;

namespace {

auto lg(logger_factory("sml.meta_data.writer"));
const std::string duplicated_key(
    "Attempt to use a simple tag key which has already been used: ");

}

namespace dogen {
namespace sml {
namespace meta_data {

writer::writer(boost::property_tree::ptree& meta_data)
    : meta_data_(meta_data) { }

bool writer::is_container(const std::string& key) const {
    return key == tags::odb_pragma;
}

bool writer::has_key(const std::string& key) const {
    const auto node(meta_data_.get_optional<std::string>(key));
    return node;
}

void writer::add(const std::string& key, const std::string& value) {
    using boost::property_tree::ptree;
    if (is_container(key)) {
        const auto node(meta_data_.get_child_optional(key));
        unsigned int i(0);
        if (node)
            i = node->size();

        const std::string nk(key + "." + boost::lexical_cast<std::string>(i));
        meta_data_.put_child(nk, ptree(value));
        return;
    }

    if (has_key(key)) {
        BOOST_LOG_SEV(lg, error) << duplicated_key << key;
        BOOST_THROW_EXCEPTION(read_write_error(duplicated_key + key));
    }
    meta_data_.put(key, value);
}

void writer::add(const std::list<std::pair<std::string, std::string> >& kvps) {
    for (const auto& pair : kvps)
        add(pair.first, pair.second);
}

bool writer::add_if_marker_found(const std::string& key,
    const std::list<std::pair<std::string, std::string> >& kvps) {
    bool has_marker(false);
    for (const auto& kvp : kvps) {
        has_marker = kvp.first == key;
        if (has_marker)
            break;
    }

    if (!has_marker)
        return false;

    add(kvps);
    return true;
}

bool writer::
add_if_key_not_found(const std::string& key, const std::string& value) {
    if (has_key(key))
        return false;

    add(key, value);
    return true;
}

} } }
