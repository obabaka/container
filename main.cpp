#include <iostream>
#include <vector>
#include <string>

template <typename T>
class LegacyIterator {
public:
    virtual bool operator==(const LegacyIterator<T>& other) const = 0;
    virtual bool operator!=(const LegacyIterator<T>& other) const = 0;
    virtual T& operator*() const = 0;
    virtual LegacyIterator<T>& operator++() = 0;
    virtual LegacyIterator<T>& operator--() = 0;
};

template <typename T>
class Container {
public:
    virtual LegacyIterator<T>& begin() = 0;
    virtual LegacyIterator<T>& end() = 0;
};

class StudentIterator : public LegacyIterator<std::string> {
public:
    StudentIterator(std::vector<std::string>& students, size_t position)
        : students_(students), position_(position) {}

    bool operator==(const LegacyIterator<std::string>& other) const override {
        const StudentIterator& otherIterator = dynamic_cast<const StudentIterator&>(other);
        return position_ == otherIterator.position_;
    }

    bool operator!=(const LegacyIterator<std::string>& other) const override {
        return !(*this == other);
    }

    std::string& operator*() const override {
        return students_[position_];
    }

    StudentIterator& operator++() override {
        position_++;
        return *this;
    }

    StudentIterator& operator--() override {
        position_--;
        return *this;
    }

private:
    std::vector<std::string>& students_;
    size_t position_;
};

class StudentContainer : public Container<std::string> {
public:
    StudentContainer(std::vector<std::string> students)
        : students_(students) {}

    StudentIterator& begin() override {
        return *new StudentIterator(students_, 0);
    }

    StudentIterator& end() override {
        return *new StudentIterator(students_, students_.size());
    }

private:
    std::vector<std::string> students_;
};

int main() {
    // Создание контейнера со списком студентов
    std::vector<std::string> students = { "Andrew", "Kirill", "Alice", "Max" };
    StudentContainer container(students);

    // Использование контейнера и его итератора
    std::cout << "Students: ";
    for (auto it = container.begin(); it != container.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    return 0;
}
