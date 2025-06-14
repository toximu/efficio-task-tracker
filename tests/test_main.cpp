#include <grpcpp/create_channel.h>
#include <gtest/gtest.h>
#include "client_implementation.h"

#define REGISTRATE_USER_TEST ;
#define AUTHENTICATE_USER_TEST ;
#define CREATE_PROJECT_TEST ;
#define GET_PROJECT_WITHOUT_NOTES_TEST ;
#define CREATE_NOTE_TEST ;
#define UPDATE_NOTE_TEST ;
#define FETCH_NOTE_TEST ;
#define GET_PROJECT_WITH_NOTES_TEST ;
#define TRY_LEAVE_PROJECT_TEST ;
#define TRY_DELETE_USER_TEST ;

struct ClientTest : ::testing::Test {
protected:
    ClientImplementation *client = nullptr;

    void SetUp() override {
        client = new ClientImplementation(
            CreateChannel("localhost:50051", grpc::InsecureChannelCredentials())
        );
    }

    void TearDown() override {
        delete client;
    }
};

User *test_user = nullptr;
Project *test_project = nullptr;
Note *test_note = nullptr;
#ifdef REGISTRATE_USER_TEST
TEST_F(ClientTest, registration_user) {
    User user_reg;
    user_reg.set_login("testuser");
    user_reg.set_hashed_password("testpassword1");

    EXPECT_EQ(client->try_register_user(&user_reg), true)
        << "Error registering user. Maybe you have done it twice.";
}
#endif

#ifdef AUTHENTICATE_USER_TEST
TEST_F(ClientTest, authenticate_user) {
    User *user_auth = new User();
    user_auth->set_login("testuser");
    user_auth->set_hashed_password("testpassword1");

    EXPECT_EQ(client->try_authenticate_user(user_auth), true)
        << "Error authenticating user";

    test_user = user_auth;

    User user_incorrect;
    user_incorrect.set_login("testuser");
    user_incorrect.set_hashed_password("wrongpassword");
    EXPECT_EQ(client->try_authenticate_user(&user_incorrect), false)
        << "Authenticate incorrect user";
}

#endif

#ifdef CREATE_PROJECT_TEST

TEST_F(ClientTest, create_project) {
    ASSERT_EQ(client->try_authenticate_user(test_user), true)
        << "Error authenticating user";

    Project *project_to_create = new Project();

    ASSERT_EQ(
        client->create_project(project_to_create, "testproject", *test_user),
        true
    ) << "Error creating project";
    EXPECT_EQ(project_to_create->title(), "testproject")
        << "Incorrect project title";

    bool has_user = false;
    for (auto member : project_to_create->members()) {
        has_user |= member == test_user->login();
    }
    EXPECT_EQ(has_user, true) << "User has not been added to the project";
    test_project = project_to_create;
}

#endif

#ifdef GET_PROJECT_WITHOUT_NOTES_TEST

TEST_F(ClientTest, get_project_without_notes) {
    ASSERT_EQ(client->try_authenticate_user(test_user), true);

    Project project_to_get;
    EXPECT_EQ(client->get_project(&project_to_get, test_project->code()), true)
        << "Error getting project";
    EXPECT_EQ(project_to_get.title(), test_project->title())
        << "Incorrect title of got project";
    EXPECT_EQ(project_to_get.code(), test_project->code())
        << "Incorrect code of got project";
}

#endif

#ifdef CREATE_NOTE_TEST
TEST_F(ClientTest, create_note) {
    Note *note = new Note();
    ASSERT_EQ(client->try_create_note(note, test_project->code()), true);
    EXPECT_EQ(note->title(), std::string("Пустая заметка"))
        << "Incorrect title of note";
    ASSERT_EQ(client->get_project(test_project, test_project->code()), true);

    bool has_note = false;
    for (const auto &pr_note : test_project->notes()) {
        has_note |= note->id() == pr_note.id();
    }
    EXPECT_EQ(has_note, true) << "Note has not been added to the project";

    test_note = note;
}
#endif

#ifdef FETCH_NOTE_TEST
TEST_F(ClientTest, fetch_note) {
    test_note->set_title("incorrect title");
    test_note->set_text("incorrect text");
    ASSERT_EQ(client->try_fetch_note(test_note), true) << "Error fetching note";
    EXPECT_EQ(test_note->title(), "Пустая заметка")
        << "Did not fetch title of note";
    EXPECT_EQ(test_note->text(), "") << "Did not fetch text of note";
}
#endif

#ifdef UPDATE_NOTE_TEST
TEST_F(ClientTest, update_note) {
    *test_note->mutable_title() = "changed title";
    *test_note->mutable_text() = "changed text";
    ASSERT_EQ(client->try_update_note(test_note), true)
        << "Error updating note";

    Note *changed_note = new Note();
    changed_note->set_id(test_note->id());
    ASSERT_EQ(client->try_fetch_note(changed_note), true)
        << "Error updating note";

    EXPECT_EQ(changed_note->id(), test_note->id());
    EXPECT_EQ(changed_note->text(), "changed text")
        << "Incorrect text of updated note";
    EXPECT_EQ(changed_note->text(), "changed text")
        << "Incorrect text of updated note";
}
#endif

#ifdef GET_PROJECT_WITH_NOTES_TEST
TEST_F(ClientTest, get_project_with_notes) {
    Note *note_to_add1 = new Note();
    Note *note_to_add2 = new Note();

    ASSERT_EQ(
        client->try_create_note(note_to_add1, test_project->code()), true
    );
    ASSERT_EQ(
        client->try_create_note(note_to_add2, test_project->code()), true
    );

    note_to_add1->set_title("custom title");
    ASSERT_EQ(client->try_update_note(note_to_add1), true);

    Project *project_to_get = new Project();
    ASSERT_EQ(client->get_project(project_to_get, test_project->code()), true);
    EXPECT_EQ(project_to_get->title(), test_project->title())
        << "Incorrect title of project";
    EXPECT_EQ(project_to_get->code(), test_project->code())
        << "Incorrect code of project";

    bool has_note1 = false;
    bool has_note2 = false;
    for (const Note &pr_note : project_to_get->notes()) {
        if (pr_note.id() == note_to_add1->id() &&
            pr_note.text() == note_to_add1->text() &&
            pr_note.title() == note_to_add1->title()) {
            has_note1 = true;
        }
        if (pr_note.id() == note_to_add2->id() &&
            pr_note.text() == note_to_add2->text() &&
            pr_note.title() == note_to_add2->title()) {
            has_note2 = true;
        }
    }
    EXPECT_EQ(has_note1, true) << "Did not get note 1 in project";
    EXPECT_EQ(has_note2, true) << "Did not get note 2 in project";
}
#endif

#ifdef TRY_LEAVE_PROJECT_TEST
TEST_F(ClientTest, try_leave_project) {
    ASSERT_EQ(client->try_leave_project(test_project->code(), *test_user), true)
        << "Error trying to leave project";

    ASSERT_EQ(client->try_authenticate_user(test_user),true);

    bool has_not_test_project = true;
    for (const auto &project : test_user->mutable_storage()->projects()) {
        if (project.code() == test_project->code()) {
            has_not_test_project = false;
        }
    }
    EXPECT_EQ(has_not_test_project, true) << "Did not leave the project";
}
#endif

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    auto result = RUN_ALL_TESTS();
    return result;
}