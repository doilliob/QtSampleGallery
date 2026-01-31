#ifndef IMAGEFILEITERATOR_H
#define IMAGEFILEITERATOR_H

#include <QString>

#include <string>
#include <vector>

/// @brief Class to iterating over the image files in the specified folder.
class ImageFileIterator
{
public:
    /// @brief Class ctor.
    /// @param folder absolute path to the folder with image files.
    /// @throws std::runtime_error in the case of reading folder error.
    explicit ImageFileIterator(const QString& folder);

    /// @brief Check if iterator contains image files.
    /// @return true if the folder does not contain image files.
    bool Empty() const;

    /// @brief Move to the next image file in folder.
    /// @return true if the transition to another file was successful,
    /// otherwise false.
    bool Next();

    /// @brief Move to the previous image file in folder.
    /// @return true if the transition to another file was successful,
    /// otherwise false.
    bool Previous();

    /// @returns absolute path to the current image file.
    std::string GetFilePath() const;

private:
    using Files = std::vector<std::string>;

    Files files_;                               ///< list of files
    Files::iterator current_{ files_.end() };   ///< current image file
};

#endif // IMAGEFILEITERATOR_H
