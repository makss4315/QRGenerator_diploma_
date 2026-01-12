#include "qr_handler.h"
#include <opencv2/opencv.hpp>
#include "qrcodegen/qrcodegen.hpp"

using namespace qrcodegen;

void generateQrPng(
    const std::string& text,
    const std::string& outputPath
)
{
    QrCode qr = QrCode::encodeText(text.c_str(), QrCode::Ecc::LOW);

    int size = qr.getSize();
    int scale = 10;
    int border = 4;
    int imgSize = (size + border * 2) * scale;

    cv::Mat img(imgSize, imgSize, CV_8UC1, cv::Scalar(255));

    for (int y = 0; y < size; y++) {
        for (int x = 0; x < size; x++) {
            if (qr.getModule(x, y)) {
                cv::rectangle(
                    img,
                    cv::Point((x + border) * scale, (y + border) * scale),
                    cv::Point((x + border + 1) * scale, (y + border + 1) * scale),
                    cv::Scalar(0),
                    cv::FILLED
                );
            }
        }
    }

    cv::imwrite(outputPath, img);
}
