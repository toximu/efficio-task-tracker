#ifndef NOTE_HPP
#define NOTE_HPP

#include <string>
#include <vector>
#include <algorithm>

class Note {
public:
    Note(int id, const std::string& title, const std::string& text);
    
    int GetId() const;
    const std::string& GetTitle() const;
    const std::string& GetText() const;
    const std::vector<std::string>& GetTags() const;
    
    void SetTitle(const std::string& title);
    void SetText(const std::string& text);
    void AddTag(const std::string& tag);
    void RemoveTag(const std::string& tag);

private:
    int id;
    std::string title;
    std::string text;
    std::vector<std::string> tags;
};

#endif
