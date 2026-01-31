#ifndef IMAGEFILEMANIPULATOR_H
#define IMAGEFILEMANIPULATOR_H

#include <QPixmap>

#include <opencv2/opencv.hpp>

/// @brief Class to read and manipulate image file.
class ImageFileManipulator
{
public:
    /// @brief Class ctor;
    /// @param filePath absolute path to image file.
    /// @throws std::runtime_error in the case of image reading error.
    explicit ImageFileManipulator(const std::string& filePath);

    /// @returns image file content.
    /// @throws std::runtime_error in the case of converting error.
    QPixmap GetImage() const;

    /// @brief Change image brightness.
    /// @param brightness brightness value.
    void SetBrightness(int brightness);

    /// @returns Returns image brightnes value.
    int GetBrightness() const { return brightness_; };

    /// @returns true if class contains image.
    bool Empty() const { return image_.empty(); }

private:
    cv::Mat image_;        ///< image file content
    int brightness_{ 0 };  ///< image brightness
};

#endif // IMAGEFILEMANIPULATOR_H
