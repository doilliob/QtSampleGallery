#include "imagefileiterator.h"

#include <QDir>

#include <exception>
#include <sstream>
#include <utility>

ImageFileIterator::ImageFileIterator(const QString& folder) {
    if (folder.isEmpty()) {
        return;
    }

    try
    {
        QDir directory(folder);

        QStringList filters;
        filters << "*.png" << "*.jpeg" << "*.jpg" << "*.gif" << "*.bmp";
        directory.setNameFilters(filters);

        QFileInfoList fileInfoList = directory.entryInfoList(QDir::Files | QDir::NoSymLinks);

        files_.clear();
        files_.reserve(fileInfoList.size());
        for (const auto& item : std::as_const(fileInfoList)) {
            files_.emplace_back(
                item.filesystemAbsoluteFilePath().string());
        }

        current_ = files_.empty() ? files_.end() : files_.begin();
    }
    catch (const std::exception& ex)
    {
        std::ostringstream ss;
        ss << "Error reading folder: " << folder.toStdString() << "."
           << "Error: " << ex.what();

        throw std::runtime_error(ss.str());
    }
}

bool ImageFileIterator::Empty() const {
    return files_.empty();
}

bool ImageFileIterator::Next() {
    if (Empty() || current_ + 1 == files_.end()) {
        return false;
    }

    ++current_;
    return true;
}


bool ImageFileIterator::Previous() {
    if (Empty() || current_ == files_.begin()) {
        return false;
    }

    --current_;
    return true;
}

std::string ImageFileIterator::GetFilePath() const {
    if (Empty()) {
        return {};
    }

    return *current_;
}
