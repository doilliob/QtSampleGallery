#include "imagefilemanipulator.h"

#include <QImage>

#include <opencv2/highgui/highgui.hpp>

#include <exception>
#include <sstream>

namespace {

QImage convertToQImage(const cv::Mat& image) {
    return QImage(image.data, image.cols, image.rows, image.step, QImage::Format_RGB888);
}

} // 'anonymous' namespace

ImageFileManipulator::ImageFileManipulator(const std::string& filePath) {

    if (filePath.empty()) {
        return;
    }

    try
    {
        image_ = cv::imread(filePath, cv::IMREAD_COLOR);

        // See https://amin-ahmadi.com/2015/12/16/how-to-display-a-mat-image-in-qt/
        cv::cvtColor(image_, image_, cv::COLOR_BGR2RGB);

    }
    catch (const std::exception& ex)
    {
        std::ostringstream ss;
        ss << "Error reading file: " << filePath << "."
           << "Error: " << ex.what();

        throw std::runtime_error(ss.str());
    }
}

void ImageFileManipulator::SetBrightness(int brightness) {
    brightness_ = brightness;
}

QPixmap ImageFileManipulator::GetImage() const {

    QPixmap result;

    if (image_.empty()) {
        return result;
    }

    try
    {
        result.convertFromImage(convertToQImage(
                brightness_ == 0 ? image_ : image_ + cv::Scalar(brightness_, brightness_, brightness_)));
    }
    catch (const std::exception& ex)
    {
        std::ostringstream ss;
        ss << "Failed processing image content."
           << "Error: " << ex.what();

        throw std::runtime_error(ss.str());
    }

    return result;
}
