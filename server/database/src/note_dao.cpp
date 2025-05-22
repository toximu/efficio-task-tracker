#include "note_dao.hpp"
#include <pqxx/pqxx>
#include "database_manager.hpp"
#include "tags_dialog.h"

namespace {

std::string format_members_array(
    const google::protobuf::RepeatedPtrField<std::string> &members
) {
    std::string result = "{";
    bool first = true;
    for (const auto &member : members) {
        if (!first) {
            result += ",";
        }
        result += "\"" + member + "\"";
        first = false;
    }
    return result + "}";
}

std::string format_tags_array(
    const google::protobuf::RepeatedPtrField<Efficio_proto::Note_tag> &tags
) {
    std::string result = "{";
    bool first = true;
    for (const auto &tag : tags) {
        if (!first) {
            result += ",";
        }
        std::string color_code =
            TagsDialog::get_color_by_code(tag.color()).toStdString();
        result += "\"{" + tag.text() + ":" + color_code + "}\"";
        first = false;
    }
    return result + "}";
}

}  // namespace

Note NoteDao::initialize_note_for_user(const std::string &login) {
    auto &connection = DatabaseManager::get_instance().get_connection();
    pqxx::work transaction(connection);

    const std::string query =
        "INSERT INTO notes (title, content) "
        "VALUES ($1, $2) "
        "RETURNING id, title, content";

    pqxx::params params;
    params.append("Пустая заметка");
    params.append("");

    const pqxx::result result = transaction.exec(query, params);

    if (result.empty()) {
        return {};
    }

    const pqxx::row row = result[0];
    Note note;
    note.set_id(row["id"].as<int>());
    note.set_title(row["title"].as<std::string>());

    transaction.commit();
    return note;
}

bool NoteDao::update_note(const Note &note) {
    auto &connection = DatabaseManager::get_instance().get_connection();
    pqxx::work transaction(connection);

    const std::string members_array = format_members_array(note.members());
    const std::string tags_array = format_tags_array(note.tags());

    const std::string query =
        "UPDATE notes SET "
        "title = $1, "
        "content = $2, "
        "members = $3::varchar(50)[], "
        "date = $4, "
        "tags = $5::varchar(50)[] "
        "WHERE id = $6";

    pqxx::params params;
    params.append(note.title());
    params.append(note.text());
    params.append(members_array);
    params.append(note.date());
    params.append(tags_array);
    params.append(note.id());

    const pqxx::result result = transaction.exec(query, params);
    transaction.commit();
    return result.affected_rows() > 0;
}

Efficio_proto::Note_tag::colors color_hex_to_enum(const std::string &hex) {
    static const std::unordered_map<
        std::string, Efficio_proto::Note_tag::colors>
        color_map = {
            {"e7624b", Efficio_proto::Note_tag::Red},
            {"165d7b", Efficio_proto::Note_tag::Blue},
            {"bd6dab", Efficio_proto::Note_tag::Pink},
            {"00b16b", Efficio_proto::Note_tag::Green},
            {"e69f00", Efficio_proto::Note_tag::Yellow}
        };
    auto it = color_map.find(hex);
    return it != color_map.end() ? it->second : Efficio_proto::Note_tag::Red;
}

Note NoteDao::get_note(const int note_id) {
    auto &connection = DatabaseManager::get_instance().get_connection();
    pqxx::work transaction(connection);

    const std::string query = "SELECT * FROM notes WHERE id = $1";
    pqxx::params params;
    params.append(note_id);

    const pqxx::result result = transaction.exec(query, params);

    if (result.empty()) {
        return {};
    }

    const pqxx::row row = result[0];
    Note note;

    note.set_id(row["id"].as<int>());
    note.set_title(row["title"].as<std::string>());
    note.set_text(row["content"].as<std::string>());

    if (!row["date"].is_null()) {
        note.set_date(row["date"].as<std::string>());
    }

    if (!row["members"].is_null()) {
        const auto members_as_string = row["members"].as<std::string>();

        if (members_as_string.size() > 2) {
            std::stringstream ss(
                members_as_string.substr(1, members_as_string.size() - 2)
            );
            std::string member;

            while (std::getline(ss, member, ',')) {
                std::erase(member, '"');
                if (!member.empty()) {
                    note.add_members(member);
                }
            }
        }
    }

    if (!row["tags"].is_null()) {
        const auto tags_as_string = row["tags"].as<std::string>();

        if (tags_as_string.size() > 2) {
            std::stringstream ss(
                tags_as_string.substr(1, tags_as_string.size() - 2)
            );
            std::string tag_item;

            while (std::getline(ss, tag_item, ',')) {
                std::erase(tag_item, '"');

                if (tag_item.size() > 3 && tag_item[0] == '{' &&
                    tag_item.back() == '}') {
                    const auto colon_position = tag_item.find(':');

                    if (colon_position != std::string::npos) {
                        auto *tag = note.add_tags();
                        tag->set_text(tag_item.substr(1, colon_position - 1));

                        const std::string color_hex = tag_item.substr(
                            colon_position + 2,
                            tag_item.size() - colon_position - 3
                        );
                        tag->set_color(color_hex_to_enum(color_hex));
                    }
                }
            }
        }
    }

    transaction.commit();
    return note;
}